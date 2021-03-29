#include "wnlmainwindow.h"
#include "ui_wnlmainwindow.h"

WNLMainWindow::WNLMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WNLMainWindow)
{
    ui->setupUi(this);

    // Get the sounds from disk
    WNLSoundGrabber* soundGrabber = new WNLSoundGrabber;
    QFuture<void> soundsFuture = QtConcurrent::run(soundGrabber, &WNLSoundGrabber::getSounds);

    QFutureWatcher<void>* soundsFutureWatcher = new QFutureWatcher<void>;
    connect(soundsFutureWatcher, &QFutureWatcher<void>::finished, [=]()
    {
        // Once the available sounds have been read from disk, add them to the available sounds widget
        for (WNLSound sound : soundGrabber->sounds)
        {
            QListWidgetItem* soundItem = new QListWidgetItem(sound.name);
            soundItem->setData(Qt::UserRole, QVariant::fromValue<WNLSound>(sound));
            ui->soundSelectionWidget->findChild<QListWidget *>("availSoundsSelect", Qt::FindChildrenRecursively)->addItem(soundItem);
        }

        delete soundGrabber;
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
