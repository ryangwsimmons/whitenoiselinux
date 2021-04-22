// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlplaylistmanager.h"

WNLPlaylistManager::WNLPlaylistManager()
    : QObject(),
      playlistsPath(QDir::homePath() + QDir::separator() + ".whitenoiselinux" + QDir::separator() + "playlists"),
      playlists(QVector<WNLPlaylist>())
{

}

void WNLPlaylistManager::setupDirStructure()
{
    // Check that the playlists folder exists, and if not, create it
    if (!QDir::home().mkpath(this->playlistsPath))
    {
        qDebug() << "Unable to setup directory structure for playlists";
        return;
    }
}

void WNLPlaylistManager::grabPlaylists()
{
    // Create a QDir object to represent the playlists directory
    QDir playlistsDir(this->playlistsPath);

    // Iterate over each file in the playlists folder, getting its name, adding it to the vector
    QFileInfoList playlistFiles = playlistsDir.entryInfoList();
    for (QFileInfo playlistFileInfo : playlistFiles)
    {
        if (playlistFileInfo.fileName() != "." && playlistFileInfo.fileName() != "..")
        {
            WNLPlaylist playlist(playlistFileInfo.baseName(), playlistFileInfo.absoluteFilePath());

            if (this->grabPlaylistSounds(&playlist))
                this->playlists.append(playlist);
        }
    }
}

void WNLPlaylistManager::savePlaylist(QString name, QVector<WNLSound> sounds)
{
    // Create a JSON array for holding the all the sounds in the playlist
    QJsonArray playlistSounds;

    // Insert every sound in the vector into the JSON array
    for (WNLSound sound : sounds)
    {
        // Create a JSON object for the sound
        QJsonObject soundObject;

        // Add the name of the sound and its path to the object
        soundObject.insert("title", QJsonValue(sound.getTitle()));
        soundObject.insert("filePath", QJsonValue(sound.getFilePath()));

        // Add the sound object to the JSON array
        playlistSounds.append(QJsonValue(soundObject));
    }

    // Create a new JSON document for the playlist
    QJsonDocument playlistDoc;

    // Set the array as the main object of the document
    playlistDoc.setArray(playlistSounds);

    // Create a new file for the playlist
    QFile playlistFile(this->playlistsPath + QDir::separator() + name + ".json");

    // Open the playlist file
    if (playlistFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Create a new text stream for writing to the file
        QTextStream playlistFileStream(&playlistFile);

        // Write the JSON document to the file
        playlistFileStream << playlistDoc.toJson();

        // Close the playlist file
        playlistFile.close();

        // Emit the playlist added signal
        WNLPlaylist playlist(name, this->playlistsPath + QDir::separator() + name + ".json");
        emit playlistAdded(playlist);
    }
    else
    {
        qDebug() << "Unable to open the playlist file for writing";
    }
}

bool WNLPlaylistManager::deletePlaylist(WNLPlaylist deletedPlaylist)
{
    // Remove the playlist from the vector of playlists in this object
    this->playlists.removeOne(deletedPlaylist);

    // Remove the playlist file from disk
    return QFile::remove(deletedPlaylist.getFilePath());
}

QVector<WNLPlaylist> WNLPlaylistManager::getPlaylists()
{
    return this->playlists;
}

bool WNLPlaylistManager::grabPlaylistSounds(WNLPlaylist* playlist)
{
    // Create a QFile object for the playlist file
    QFile playlistFile(playlist->getFilePath());

    // Open the playlist file (if this fails, print a debug message)
    if (!playlistFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Unable to read playlist " << playlist->getName() << ".";
        return false;
    }

    // Create a QTextStream for the playlist file
    QTextStream playlistStream(&playlistFile);

    // Create a JSON document from the file
    QJsonDocument playlistJson = QJsonDocument::fromJson(playlistStream.readAll().toUtf8());

    // Close the playlist file
    playlistFile.close();

    // Check that the playlist JSON isn't null
    if (playlistJson.isNull())
    {
        qDebug().nospace() << "Unable to parse playlist " << playlist->getName() << ".";
        return false;
    }

    if (!playlistJson.isArray())
    {
        qDebug().nospace() << "An error occurred while reading playlist " << playlist->getName() << ".";
        qDebug().nospace() << "Main JSON object of playlist " << playlist->getName() << " is not an array.";
        return false;
    }

    // Iterate over the JSON document's array, adding all of the sounds to the playlist struct's sounds vector
    for (QJsonValue soundJson : playlistJson.array())
    {
        try
        {
            if (!soundJson.isObject())
                throw std::ios_base::failure("Cannot parse array item as object");
            QJsonObject soundJsonObject = soundJson.toObject();

            WNLSound sound;

            if (soundJsonObject.value("title").isUndefined() || !soundJsonObject.value("title").isString())
                throw std::ios_base::failure("Cannot parse sound title, it is either undefined or not a string");
            sound.setTitle(soundJsonObject.value("title").toString());

            if (soundJsonObject.value("filePath").isUndefined() || !soundJsonObject.value("filePath").isString())
                throw std::ios_base::failure("Cannot parse sound file path, it is either undefined or not a string");
            sound.setFilePath(soundJsonObject.value("filePath").toString());

            playlist->addSound(sound);
        }
        catch (const std::ios_base::failure& e)
        {
            qDebug().nospace() << "An error occurred while reading playlist " << playlist->getName() << ".";
            qDebug().nospace() << e.what() << ".";
            qDebug() << "Manually modifying playlist files is not recommended.";
            continue;
        }
    }

    return true;
}
