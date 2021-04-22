// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#ifndef WNLMPRISMEDIAPLAYER2ADAPTOR_H
#define WNLMPRISMEDIAPLAYER2ADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QString>
#include <QStringList>

class WNLMPRISMediaPlayer2Adaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2")
    Q_PROPERTY(bool CanQuit READ getCanQuit)
    Q_PROPERTY(bool CanRaise READ getCanRaise)
    Q_PROPERTY(bool HasTrackList READ getHasTrackList)
    Q_PROPERTY(QString Identity READ getIdentity)
    Q_PROPERTY(QString DesktopEntry READ getDesktopEntry)
    Q_PROPERTY(QStringList SupportedUriSchemes READ getSupportedUriSchemes)
    Q_PROPERTY(QStringList SupportedMimeTypes READ getSupportedMimeTypes)
public:
    WNLMPRISMediaPlayer2Adaptor(QObject* object);
    bool getCanQuit() const;
    bool getCanRaise() const;
    bool getHasTrackList() const;
    QString getIdentity() const;
    QString getDesktopEntry() const;
    QStringList getSupportedUriSchemes() const;
    QStringList getSupportedMimeTypes() const;

private:
    const bool CanQuit;
    const bool CanRaise;
    const bool HasTrackList;
    const QString Identity;
    const QString DesktopEntry;
    const QStringList SupportedUriSchemes;
    const QStringList SupportedMimeTypes;
};

#endif // WNLMPRISMEDIAPLAYER2ADAPTOR_H
