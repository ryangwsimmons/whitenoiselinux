#ifndef WNLPLAYLISTMANAGER_H
#define WNLPLAYLISTMANAGER_H

#include <stdexcept>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QTextStream>
#include <QVector>

#include "wnlplaylist.h"
#include "wnlsound.h"

class WNLPlaylistManager : public QObject
{
    Q_OBJECT
public:
    WNLPlaylistManager();
    void setupDirStructure();
    void grabPlaylists();
    void savePlaylist(QString name, QVector<WNLSound> sounds);
    bool deletePlaylist(WNLPlaylist deletedPlaylist);
    QVector<WNLPlaylist> getPlaylists();

signals:
    void playlistAdded(WNLPlaylist newPlaylist);

private:
    const QString playlistsPath;
    QVector<WNLPlaylist> playlists;

    bool grabPlaylistSounds(WNLPlaylist* playlist);
};

#endif // WNLPLAYLISTMANAGER_H
