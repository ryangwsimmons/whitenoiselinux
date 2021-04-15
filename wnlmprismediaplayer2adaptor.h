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
    Q_PROPERTY(QStringList SupportedUriSchemes READ getSupportedUriSchemes)
    Q_PROPERTY(QStringList SupportedMimeTypes READ getSupportedMimeTypes)
public:
    const bool CanQuit;
    const bool CanRaise;
    const bool HasTrackList;
    const QString Identity;
    const QStringList SupportedUriSchemes;
    const QStringList SupportedMimeTypes;

    WNLMPRISMediaPlayer2Adaptor(QObject* object);
    bool getCanQuit();
    bool getCanRaise();
    bool getHasTrackList();
    QString getIdentity();
    QStringList getSupportedUriSchemes();
    QStringList getSupportedMimeTypes();
};

#endif // WNLMPRISMEDIAPLAYER2ADAPTOR_H
