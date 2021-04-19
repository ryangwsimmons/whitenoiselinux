#ifndef WNLMAINWINDOW_H
#define WNLMAINWINDOW_H

#include <QtConcurrent/QtConcurrent>
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QIcon>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QString>
#include <QStringLiteral>
#include <QVariant>

#include "wnlaboutdialog.h"
#include "wnlmprismediaplayer2adaptor.h"
#include "wnlmprismediaplayer2playeradaptor.h"
#include "wnlplaybackmanager.h"
#include "wnlplaylist.h"
#include "wnlplaylistmanager.h"
#include "wnlsoundgrabber.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WNLMainWindow; }
QT_END_NAMESPACE

class WNLMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    WNLMainWindow(QWidget *parent = nullptr);
    ~WNLMainWindow();

private slots:
    void on_aboutButton_clicked() const;

    void on_addSoundButton_clicked();

    void on_rmSoundButton_clicked();

    void on_currSoundsSelect_itemSelectionChanged();

    void on_availSoundsSelect_itemSelectionChanged();

    void on_playPauseButton_clicked();

    void playAudio();

    void pauseAudio();

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void addPlaylist(WNLPlaylist newPlaylist);

private:
    Ui::WNLMainWindow *ui;
    WNLPlaybackManager playbackManager;
    WNLPlaylistManager playlistManager;
    QDBusConnection dBusConn;
    WNLMPRISMediaPlayer2PlayerAdaptor* playerAdaptor;

    void setupDBus();
    void setupPlaylists();
};
#endif // WNLMAINWINDOW_H
