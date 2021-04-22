// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#ifndef WNLMPRISMEDIAPLAYER2PLAYERADAPTOR_H
#define WNLMPRISMEDIAPLAYER2PLAYERADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QString>
#include <QStringList>
#include <QVariantMap>

#include "wnlmprismetadatamap.h"

class WNLMPRISMediaPlayer2PlayerAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
    Q_PROPERTY(QString PlaybackStatus READ getPlaybackStatus)
    Q_PROPERTY(double Rate READ getRate WRITE setRate)
    Q_PROPERTY(WNLMPRISMetadataMap Metadata READ getMetadata)
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
    WNLMPRISMediaPlayer2PlayerAdaptor(QObject* object);
    QString getPlaybackStatus() const;
    void setPlaybackStatus(QString status);
    double getRate() const;
    void setRate(double Rate);
    WNLMPRISMetadataMap getMetadata() const;
    void setTrackTitle(QString title);
    double getVolume() const;
    void setVolume(double Volume);
    qlonglong getPosition() const;
    double getMinimumRate() const;
    double getMaximumRate() const;
    bool getCanGoNext() const;
    bool getCanGoPrevious() const;
    bool getCanPlay() const;
    bool getCanPause() const;
    bool getCanSeek() const;
    bool getCanControl() const;

signals:
    void Seeked(qlonglong Position) const;
    void wasPaused() const;
    void wasPlayed() const;
    void wasPlayPaused() const;

public slots:
    void Next() const;
    void Previous() const;
    void Pause() const;
    void PlayPause() const;
    void Stop() const;
    void Play() const;
    void Seek(qlonglong Offset) const;
    void SetPosition(QDBusObjectPath TrackId, qlonglong Position) const;
    void OpenUri(QString Uri) const;

private:
    QString PlaybackStatus;
    double Rate;
    WNLMPRISMetadataMap Metadata;
    double Volume;
    const qlonglong Position;
    const double MinimumRate;
    const double MaximumRate;
    const bool CanGoNext;
    const bool CanGoPrevious;
    const bool CanPlay;
    const bool CanPause;
    const bool CanSeek;
    const bool CanControl;

    void emitPropertyChanged(QString propertyName) const;
};

#endif // WNLMPRISMEDIAPLAYER2PLAYERADAPTOR_H
