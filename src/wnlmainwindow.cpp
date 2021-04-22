// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlmainwindow.h"
#include "ui_wnlmainwindow.h"

WNLMainWindow::WNLMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::WNLMainWindow),
      dBusConn(QDBusConnection::sessionBus())
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
            QListWidgetItem* soundItem = new QListWidgetItem(sound.getTitle());
            soundItem->setData(Qt::UserRole, QVariant::fromValue<WNLSound>(sound));
            ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively)->addItem(soundItem);
        }

        // Setup D-Bus stuff
        this->setupDBus();

        delete soundsFutureWatcher;
    });
    soundsFutureWatcher->setFuture(soundsFuture);

    // Setup the playlists dropdown
    QtConcurrent::run(this, &WNLMainWindow::setupPlaylists);
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

void WNLMainWindow::on_aboutButton_clicked() const
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
        this->addSound(selectedIndex.row());
    }

    // Update the MPRIS track title value
    this->playerAdaptor->setTrackTitle(this->playbackManager.getCurrentlyPlayingString());
}

void WNLMainWindow::addSound(int row)
{
    // Get pointers to both lists
    QListWidget* availSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively);
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);

    // Remove item from the available sounds list
    QListWidgetItem* selectedItem = availSoundsSelect->takeItem(row);

    // Add the item to the currently playing list
    currSoundsSelect->addItem(selectedItem);

    // Open the sound and add it to the list of currently playing sounds
    this->playbackManager.addSound(selectedItem->data(Qt::UserRole).value<WNLSound>());
}

void WNLMainWindow::on_rmSoundButton_clicked()
{
    // Get pointers to both lists
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);
    QListWidget* availSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively);

    // Move all selected sounds to the "available sounds" list
    for (QModelIndex selectedIndex : currSoundsSelect->selectionModel()->selectedIndexes())
    {
        this->rmSound(selectedIndex.row());
    }

    // Update the MPRIS track title value
    this->playerAdaptor->setTrackTitle(this->playbackManager.getCurrentlyPlayingString());
}

void WNLMainWindow::rmSound(int row)
{
    // Get pointers to both lists
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);
    QListWidget* availSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively);

    // Remove item from the currently playing list
    QListWidgetItem* selectedItem = currSoundsSelect->takeItem(row);

    // Add the item to the available sounds list
    availSoundsSelect->addItem(selectedItem);

    // Remove the sound from the playback manager
    this->playbackManager.rmSound(row);
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

void WNLMainWindow::on_saveButton_clicked()
{
    // Get a pointer to the currently playing sounds list
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);

    // Get a pointer to the playlist combo box
    QComboBox* playlistComboBox = ui->topBarWidget->findChild<QComboBox *>("playlistComboBox", Qt::FindChildrenRecursively);

    // Make a new QVector to hold all the currently playing sounds
    QVector<WNLSound> playingSounds;

    // Add all the currently playing sounds to the vector
    for (int i = 0; i < currSoundsSelect->count(); i++)
    {
        QListWidgetItem* listItem = currSoundsSelect->item(i);
        WNLSound sound = listItem->data(Qt::UserRole).value<WNLSound>();
        playingSounds.append(sound);
    }

    // Save the currently playing sounds as a playlist
    this->playlistManager.savePlaylist(playlistComboBox->currentText(), playingSounds);

    // Clear focus
    this->ui->centralwidget->setFocus();
}

void WNLMainWindow::on_deleteButton_clicked()
{
    // Get a pointer for the playlist combo box
    QComboBox* playlistComboBox = ui->topBarWidget->findChild<QComboBox *>("playlistComboBox", Qt::FindChildrenRecursively);

    // Get the WNLPlaylist object for the currently selected playlist
    WNLPlaylist deletedPlaylist = playlistComboBox->currentData(Qt::UserRole).value<WNLPlaylist>();

    // Display a message box, where the user confirms whether or not they want to delete the playlist
    QMessageBox::StandardButton response;
    response = QMessageBox::question(this, "Delete Playlist", "Are you sure you wish to delete playlist \"" + deletedPlaylist.getName() + "\"?", QMessageBox::Yes | QMessageBox::No);

    // If the user clicked yes, delete the playlist
    if (response == QMessageBox::Yes)
    {
        // Remove the playlist from the playlist manager and delete it from disk
        if (this->playlistManager.deletePlaylist(deletedPlaylist))
        {
            // Remove the playlist from the playlist combo box
            playlistComboBox->removeItem(playlistComboBox->currentIndex());
        }
    }

    // Clear focus
    this->ui->centralwidget->setFocus();
}

void WNLMainWindow::addPlaylist(WNLPlaylist newPlaylist)
{
    // Get a pointer for the playlist combo box
    QComboBox* playlistComboBox = ui->topBarWidget->findChild<QComboBox *>("playlistComboBox", Qt::FindChildrenRecursively);

    // Add the new playlist to the combo box
    playlistComboBox->addItem(newPlaylist.getName(), QVariant::fromValue<WNLPlaylist>(newPlaylist));
}

void WNLMainWindow::setupPlaylists()
{
    // Setup directory structure
    this->playlistManager.setupDirStructure();

    // Grab playlists
    this->playlistManager.grabPlaylists();

    // Add each playlist to the playlists combo box
    QComboBox* playlistComboBox = ui->topBarWidget->findChild<QComboBox *>("playlistComboBox", Qt::FindChildrenRecursively);

    // Add each playlist to the combo box
    for (WNLPlaylist playlist : this->playlistManager.getPlaylists())
    {
        playlistComboBox->addItem(playlist.getName(), QVariant::fromValue<WNLPlaylist>(playlist));
    }

    // Connect the playlist added signal to the add playlist method
    connect(&(this->playlistManager), &WNLPlaylistManager::playlistAdded, this, &WNLMainWindow::addPlaylist);
}

void WNLMainWindow::on_loadButton_clicked()
{
    // Get a pointer for the playlist combo box
    QComboBox* playlistComboBox = ui->topBarWidget->findChild<QComboBox *>("playlistComboBox", Qt::FindChildrenRecursively);

    // Asynchronously run the method to load a playlist
    QtConcurrent::run(this, &WNLMainWindow::loadPlaylist, playlistComboBox->currentData().value<WNLPlaylist>());

    // Clear focus
    this->ui->centralwidget->setFocus();
}

void WNLMainWindow::loadPlaylist(WNLPlaylist playlist)
{
    // Get pointers to both lists
    QListWidget* currSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("currSoundsSelect", Qt::FindChildrenRecursively);
    QListWidget* availSoundsSelect = ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively);

    // Get a pointer for the playlist combo box
    QComboBox* playlistComboBox = ui->topBarWidget->findChild<QComboBox *>("playlistComboBox", Qt::FindChildrenRecursively);

    int currCount = currSoundsSelect->count();

    // Remove all sounds currently playing
    for (int i = 0; i < currCount; i++)
    {
        this->rmSound(0);
    }

    // Add all the available items in the list widget to a list (for some reason, Qt doesn't provide a function to get this)
    QVector<QListWidgetItem*> availableListItems;
    for (int i = 0; i < availSoundsSelect->count(); i++)
    {
        availableListItems.append(availSoundsSelect->item(i));
    }

    // Add all of the sounds in the selected playlist to the currently playing list
    for (WNLSound sound : playlistComboBox->currentData(Qt::UserRole).value<WNLPlaylist>().getSounds())
    {
        // Filter the list of items to get the item that corresponds to the current sound from the playlist
        // Since there's the possibility that two different sound files have the same title property, we need to compare their file paths as well, instead of just their titles
        // This unfortunately complicates the logic in this section since we can't just run availSoundsSelect->findItems()
        QVector<QListWidgetItem*> resultingSoundList = QVector<QListWidgetItem*>::fromList(QtConcurrent::blockingFiltered(availableListItems, [=](const QListWidgetItem* item)
        {
            return item->data(Qt::UserRole).value<WNLSound>() == sound;
        }).toList());

        // If the sound was not found, print an error message, otherwise add it to the currently playing sounds
        if (resultingSoundList.size() == 0)
        {
            qDebug() << "Unable to find file " << sound.getFilePath() << ".";
        }
        else
        {
            this->addSound(availSoundsSelect->row(resultingSoundList.at(0)));
        }
    }
}
