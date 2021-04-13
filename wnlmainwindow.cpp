#include "wnlmainwindow.h"
#include "ui_wnlmainwindow.h"

WNLMainWindow::WNLMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WNLMainWindow)
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

        delete soundsFutureWatcher;
    });
    soundsFutureWatcher->setFuture(soundsFuture);
}

WNLMainWindow::~WNLMainWindow()
{
    delete ui;
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
        // Change the icon
        ui->mediaControlsWidget->findChild<QPushButton *>("playPauseButton", Qt::FindChildrenRecursively)->setIcon(QIcon::fromTheme("media-playback-pause"));

        // Play audio
        this->playbackManager.playAudio();
    }
    else
    {
        // Change the icon
        ui->mediaControlsWidget->findChild<QPushButton *>("playPauseButton", Qt::FindChildrenRecursively)->setIcon(QIcon::fromTheme("media-playback-start"));

        // Pause audio
        this->playbackManager.pauseAudio();
    }
}
