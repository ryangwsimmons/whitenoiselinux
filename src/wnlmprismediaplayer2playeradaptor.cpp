// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlmprismediaplayer2playeradaptor.h"

WNLMPRISMediaPlayer2PlayerAdaptor::WNLMPRISMediaPlayer2PlayerAdaptor(QObject* object)
    : QDBusAbstractAdaptor(object),
      PlaybackStatus("Paused"),
      Rate(1.0),
      Metadata(),
      Volume(1.0),
      Position(0),
      MinimumRate(1.0),
      MaximumRate(1.0),
      CanGoNext(false),
      CanGoPrevious(false),
      CanPlay(true),
      CanPause(true),
      CanSeek(false),
      CanControl(true)
{
    // Register metadata map meta type with Qt D-Bus
    qDBusRegisterMetaType<WNLMPRISMetadataMap>();

    // Set up the initial metadata map
    this->Metadata.insert("mpris:trackid", QDBusVariant(QDBusObjectPath("/org/mpris/MediaPlayer2/CurrentlyPlaying")));
    this->Metadata.insert("xesam:artist", QDBusVariant(QStringList("WhiteNoiseLinux")));
    this->Metadata.insert("xesam:title", QDBusVariant("No Sounds Selected"));
}

QString WNLMPRISMediaPlayer2PlayerAdaptor::getPlaybackStatus() const
{
    return this->PlaybackStatus;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setPlaybackStatus(QString status)
{
    this->PlaybackStatus = status;

    this->emitPropertyChanged("PlaybackStatus");
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getRate() const
{
    return this->Rate;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setRate(double Rate)
{
    this->Rate = Rate;
}

WNLMPRISMetadataMap WNLMPRISMediaPlayer2PlayerAdaptor::getMetadata() const
{
    return this->Metadata;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setTrackTitle(QString title)
{
    this->Metadata.insert("xesam:title", QDBusVariant(title));

    this->emitPropertyChanged("Metadata");
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getVolume() const
{
    return this->Volume;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setVolume(double Volume)
{
    this->Volume = Volume;
}

qlonglong WNLMPRISMediaPlayer2PlayerAdaptor::getPosition() const
{
    return this->Position;
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getMinimumRate() const
{
    return this->MinimumRate;
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getMaximumRate() const
{
    return this->MaximumRate;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanGoNext() const
{
    return this->CanGoNext;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanGoPrevious() const
{
    return this->CanGoPrevious;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanPlay() const
{
    return this->CanPlay;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanPause() const
{
    return this->CanPause;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanSeek() const
{
    return this->CanSeek;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanControl() const
{
    return this->CanControl;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Next() const
{
    // Application does not allow seeking, so this method does nothing
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Previous() const
{
    // Application does not allow seeking, so this method does nothing
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Pause() const
{
    // Emit the wasPaused signal so that the application knows to pause the audio
    emit this->wasPaused();
}

void WNLMPRISMediaPlayer2PlayerAdaptor::PlayPause() const
{
    // Emit the wasPlayPaused signal so that the application knows to either play or pause the audio
    emit this->wasPlayPaused();
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Stop() const
{
    // "Stopping" audio doesn't really make sense in this context, so this method does nothing
    // I'm not 100% sure about this one, though. I may revisit this at a later date.
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Play() const
{
    // Emit the wasPlayed signal so that the application knows the play the audio
    emit this->wasPlayed();
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Seek(qlonglong Offset) const
{
    // Application does not allow seeking, so this method does nothing
    // Prevent unused parameter warnings
    (void)Offset;
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::SetPosition(QDBusObjectPath TrackId, qlonglong Position) const
{
    // Application does not allow seeking, so this method does nothing
    // Prevent unused parameter warnings
    (void)TrackId;
    (void)Position;
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::OpenUri(QString Uri) const
{
    // Opening URIs doesn't really make sense in this context, so this method does nothing
    // Prevent unused parameter warnings
    (void)Uri;
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::emitPropertyChanged(QString propertyName) const
{
    // Create the signal message
    QDBusMessage signal = QDBusMessage::createSignal("/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", "PropertiesChanged");

    // Indicate the interface whose properties have changed
    signal << "org.mpris.MediaPlayer2.Player";

    // Create a variant map for storing the property name and the new value of the property
    QVariantMap changedProps;

    // Insert the property changed and the new property value into the variant map
    changedProps.insert(propertyName, this->property(propertyName.toLatin1().data()));

    // Marshall the changed properties into the signal
    signal << changedProps;

    // No properties have been invalidated, so an empty string list can be marshalled into the signal for that parameter
    signal << QStringList();

    // Send the properties changed signal
    QDBusConnection::sessionBus().send(signal);
}
