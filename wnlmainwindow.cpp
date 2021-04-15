#include "wnlmainwindow.h"
#include "ui_wnlmainwindow.h"

WNLMainWindow::WNLMainWindow(QWidget *parent)
    : QMainWindow(parent),
      dBusConn(QDBusConnection::sessionBus()),
      ui(new Ui::WNLMainWindow)
{
    ui->setupUi(this);

    // Get the sounds from disk
    WNLSoundGrabber soundGrabber;
    QFuture<QVector<WNLSound>> soundsFuture = QtConcurrent::run(soundGrabber, &WNLSoundGrabber::getSounds);

    QFutureWatcher<QVector<WNLSound>>* soundsFutureWatcher = new QFutureWatcher<QVector<WNLSound>>;
    connect(soundsFutureWatcher, &QFutureWatcher<QVector<WNLSound>>::finished, [=]()
    {
        // Once the available sounds have been read from disk, add them to the available sounds widget
        for (WNLSound sound : soundsFutureWatcher->result())
        {
            QListWidgetItem* soundItem = new QListWidgetItem(sound.name);
            soundItem->setData(Qt::UserRole, QVariant::fromValue<WNLSound>(sound));
            ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively)->addItem(soundItem);
        }

        // Setup D-Bus stuff
        this->setupDBus();

        delete soundsFutureWatcher;
    });
    soundsFutureWatcher->setFuture(soundsFuture);
}

WNLMainWindow::~WNLMainWindow()
{
    delete ui;

    // Unregister the MPRIS object
    this->dBusConn.unregisterObject("/org/mpris/MediaPlayer2");

    // Unregister the MPRIS service
    bool unregisteredSuccessfully = this->dBusConn.unregisterService(QStringLiteral("org.mpris.MediaPlayer2.whitenoiselinux.instance%1").arg(QCoreApplication::applicationPid()));
    if (unregisteredSuccessfully == false)
    {
        qDebug() << "Unable to unregister MPRIS service.";
    }
}

void WNLMainWindow::playAudio()
{
    // Change the icon
    ui->mediaControlsWidget->findChild<QPushButton *>("playPauseButton", Qt::FindChildrenRecursively)->setIcon(QIcon::fromTheme("media-playback-pause"));

    // Play audio
    this->playbackManager.playAudio();

    // Tell MPRIS that audio has started playing
    this->playerAdaptor->setPlaybackStatus("Playing");
}

void WNLMainWindow::pauseAudio()
{
    // Change the icon
    ui->mediaControlsWidget->findChild<QPushButton *>("playPauseButton", Qt::FindChildrenRecursively)->setIcon(QIcon::fromTheme("media-playback-start"));

    // Pause audio
    this->playbackManager.pauseAudio();

    // Tell MPRIS that the audio has been paused
    this->playerAdaptor->setPlaybackStatus("Paused");
}

void WNLMainWindow::on_aboutButton_clicked()
{
    // Create new about dialog that deletes itself on close
    WNLAboutDialog *aboutDialog = new WNLAboutDialog();
    aboutDialog->setAttribute(Qt::WA_DeleteOnClose);

    // Position the about dialog in the centre of the parent window
    aboutDialog->move(this->geometry().center() - aboutDialog->rect().center());

    // Show the dialog (modal)
    aboutDialog->exec();
}

void WNLMainWindow::on_addSoundButton_clicked()
{
    // Get pointers to both lists
    QListWidget* availSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively);
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);

    // Move all selected sounds to the "currently playing" list
    for (QModelIndex selectedIndex : availSoundsSelect->selectionModel()->selectedIndexes())
    {
        // Remove item from the available sounds list
        QListWidgetItem* selectedItem = availSoundsSelect->takeItem(selectedIndex.row());

        // Add the item to the currently playing list
        currSoundsSelect->addItem(selectedItem);

        // Open the sound and add it to the list of currently playing sounds
        this->playbackManager.addSound(selectedItem->data(Qt::UserRole).value<WNLSound>());
    }

    // Update the MPRIS track title value
    this->playerAdaptor->setTrackTitle(this->playbackManager.getCurrentlyPlayingString());
}

void WNLMainWindow::on_rmSoundButton_clicked()
{
    // Get pointers to both lists
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);
    QListWidget* availSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively);

    // Move all selected sounds to the "available sounds" list
    for (QModelIndex selectedIndex : currSoundsSelect->selectionModel()->selectedIndexes())
    {
        // Remove item from the currently playing list
        QListWidgetItem* selectedItem = currSoundsSelect->takeItem(selectedIndex.row());

        // Add the item to the available sounds list
        availSoundsSelect->addItem(selectedItem);

        // Remove the sound from the playback manager
        this->playbackManager.rmSound(selectedIndex.row());
    }

    // Update the MPRIS track title value
    this->playerAdaptor->setTrackTitle(this->playbackManager.getCurrentlyPlayingString());
}

void WNLMainWindow::on_currSoundsSelect_itemSelectionChanged()
{
    // If the number of items selected in the list is greater than 0, enable the button for moving sounds back to the available list
    if (ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively)->selectedItems().count() > 0)
    {
        ui->soundSelectionWidget->findChild<QPushButton *>("rmSoundButton", Qt::FindChildrenRecursively)->setEnabled(true);
    }
    else // Otherwise, disable it
    {
        ui->soundSelectionWidget->findChild<QPushButton *>("rmSoundButton", Qt::FindChildrenRecursively)->setEnabled(false);
    }
}

void WNLMainWindow::on_availSoundsSelect_itemSelectionChanged()
{
    // If the number of items selected in the list is greater than 0, enable the button for moving sounds to the currently playing list
    if (ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively)->selectedItems().count() > 0)
    {
        ui->soundSelectionWidget->findChild<QPushButton *>("addSoundButton", Qt::FindChildrenRecursively)->setEnabled(true);
    }
    else // Otherwise, disable it
    {
        ui->soundSelectionWidget->findChild<QPushButton *>("addSoundButton", Qt::FindChildrenRecursively)->setEnabled(false);
    }
}

void WNLMainWindow::on_playPauseButton_clicked()
{
    // Change the icon from play to pause, or vice versa, depending on the current status, and change playback accordingly
    if (this->playbackManager.isPaused())
    {
        // Call the playAudio method
        this->playAudio();
    }
    else
    {
        // Call the pauseAudio method
        this->pauseAudio();
    }
}

void WNLMainWindow::setupDBus()
{
    // Instantiate both adaptors (multiple are needed to implement multiple interfaces)
    // The first adaptor's pointer doesn't need to be saved to a variable since we won't need to access it again
    // Qt will handle the memory management
    new WNLMPRISMediaPlayer2Adaptor(this);
    this->playerAdaptor = new WNLMPRISMediaPlayer2PlayerAdaptor(this);

    //Connect the player adaptor's signals to slots in the application so that the application can react when various events occur
    connect(this->playerAdaptor, &WNLMPRISMediaPlayer2PlayerAdaptor::wasPaused, this, &WNLMainWindow::pauseAudio);
    connect(this->playerAdaptor, &WNLMPRISMediaPlayer2PlayerAdaptor::wasPlayPaused, this, &WNLMainWindow::on_playPauseButton_clicked);
    connect(this->playerAdaptor, &WNLMPRISMediaPlayer2PlayerAdaptor::wasPlayed, this, &WNLMainWindow::playAudio);

    // Register the MPRIS service
    bool registeredSuccessfully = this->dBusConn.registerService(QStringLiteral("org.mpris.MediaPlayer2.whitenoiselinux.instance%1").arg(QCoreApplication::applicationPid()));
    if (registeredSuccessfully == false)
    {
        qDebug() << "Unable to register MPRIS service, media controls from Linux won't work.";
    }

    // Register the MPRIS object
    registeredSuccessfully = this->dBusConn.registerObject("/org/mpris/MediaPlayer2", this);
    if (registeredSuccessfully == false)
    {
        qDebug() << "Unable to register MPRIS object, media controls from Linux won't work.";
    }
}
