#ifndef WNLMPRISMEDIAPLAYER2PLAYERADAPTOR_H
#define WNLMPRISMEDIAPLAYER2PLAYERADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

typedef QMap<QString, QVariant> MetadataMap;
Q_DECLARE_METATYPE(MetadataMap)

class WNLMPRISMediaPlayer2PlayerAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
    Q_PROPERTY(QString PlaybackStatus READ getPlaybackStatus)
    Q_PROPERTY(double Rate READ getRate WRITE setRate)
    Q_PROPERTY(MetadataMap Metadata READ getMetadata)
    Q_PROPERTY(double Volume READ getVolume WRITE setVolume)
    Q_PROPERTY(qlonglong Position READ getPosition)
    Q_PROPERTY(double MinimumRate READ getMinimumRate)
    Q_PROPERTY(double MaximumRate READ getMaximumRate)
    Q_PROPERTY(bool CanGoNext READ getCanGoNext)
    Q_PROPERTY(bool CanGoPrevious READ getCanGoPrevious)
    Q_PROPERTY(bool CanPlay READ getCanPlay)
    Q_PROPERTY(bool CanPause READ getCanPause)
    Q_PROPERTY(bool CanSeek READ getCanSeek)
    Q_PROPERTY(bool CanControl READ getCanControl)
public:
    QString PlaybackStatus;
    double Rate;
    MetadataMap Metadata;
    double Volume;
    qlonglong Position;
    double MinimumRate;
    double MaximumRate;
    bool CanGoNext;
    bool CanGoPrevious;
    bool CanPlay;
    bool CanPause;
    bool CanSeek;
    bool CanControl;

    WNLMPRISMediaPlayer2PlayerAdaptor(QObject* object);
    QString getPlaybackStatus();
    void setPlaybackStatus(QString status);
    double getRate();
    void setRate(double Rate);
    MetadataMap getMetadata();
    void setTrackTitle(QString title);
    double getVolume();
    void setVolume(double Volume);
    qlonglong getPosition();
    double getMinimumRate();
    double getMaximumRate();
    bool getCanGoNext();
    bool getCanGoPrevious();
    bool getCanPlay();
    bool getCanPause();
    bool getCanSeek();
    bool getCanControl();

signals:
    void Seeked(qlonglong Position);
    void wasPaused();
    void wasPlayed();
    void wasPlayPaused();

public slots:
    void Next();
    void Previous();
    void Pause();
    void PlayPause();
    void Stop();
    void Play();
    void Seek(qlonglong Offset);
    void SetPosition(QDBusObjectPath TrackId, qlonglong Position);
    void OpenUri(QString Uri);

private:
    void emitPropertyChanged(QString propertyName);
};

#endif // WNLMPRISMEDIAPLAYER2PLAYERADAPTOR_H
