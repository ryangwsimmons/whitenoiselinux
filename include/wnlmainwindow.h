// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

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
#include <QMessageBox>
#include <QString>
#include <QVariant>
#include <QVector>

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

    void on_loadButton_clicked();

private:
    Ui::WNLMainWindow *ui;
    WNLPlaybackManager playbackManager;
    WNLPlaylistManager playlistManager;
    QDBusConnection dBusConn;
    WNLMPRISMediaPlayer2PlayerAdaptor* playerAdaptor;

    void setupDBus();
    void setupPlaylists();
    void addSound(int row);
    void rmSound(int row);
    void loadPlaylist(WNLPlaylist playlist);
};
#endif // WNLMAINWINDOW_H
