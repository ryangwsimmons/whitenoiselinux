#include "wnlmprismediaplayer2playeradaptor.h"

WNLMPRISMediaPlayer2PlayerAdaptor::WNLMPRISMediaPlayer2PlayerAdaptor(QObject* object)
    : QDBusAbstractAdaptor(object),
      PlaybackStatus("Paused"),
      Rate(1.0),
      Metadata(QMap<QString, QVariant>()),
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
    qDBusRegisterMetaType<MetadataMap>();

    // Set up the initial metadata map
    this->Metadata.insert("mpris:trackid", QDBusObjectPath("/org/mpris/MediaPlayer2/CurrentlyPlaying"));
    this->Metadata.insert("xesam:artist", QStringList("WhiteNoiseLinux"));
    this->Metadata.insert("xesam:title", "No Sounds Selected");
}

QString WNLMPRISMediaPlayer2PlayerAdaptor::getPlaybackStatus()
{
    return this->PlaybackStatus;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setPlaybackStatus(QString status)
{
    this->PlaybackStatus = status;

    this->emitPropertyChanged("PlaybackStatus");
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getRate()
{
    return this->Rate;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setRate(double Rate)
{
    this->Rate = Rate;
}

QMap<QString, QVariant> WNLMPRISMediaPlayer2PlayerAdaptor::getMetadata()
{
    return this->Metadata;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setTrackTitle(QString title)
{
    this->Metadata.insert("xesam:title", title);

    this->emitPropertyChanged("Metadata");
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getVolume()
{
    return this->Volume;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::setVolume(double Volume)
{
    this->Volume = Volume;
}

qlonglong WNLMPRISMediaPlayer2PlayerAdaptor::getPosition()
{
    return this->Position;
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getMinimumRate()
{
    return this->MinimumRate;
}

double WNLMPRISMediaPlayer2PlayerAdaptor::getMaximumRate()
{
    return this->MaximumRate;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanGoNext()
{
    return this->CanGoNext;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanGoPrevious()
{
    return this->CanGoPrevious;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanPlay()
{
    return this->CanPlay;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanPause()
{
    return this->CanPause;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanSeek()
{
    return this->CanSeek;
}

bool WNLMPRISMediaPlayer2PlayerAdaptor::getCanControl()
{
    return this->CanControl;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Next()
{
    // Application does not allow seeking, so this method does nothing
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Previous()
{
    // Application does not allow seeking, so this method does nothing
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Pause()
{
    // Emit the wasPaused signal so that the application knows to pause the audio
    emit this->wasPaused();
}

void WNLMPRISMediaPlayer2PlayerAdaptor::PlayPause()
{
    // Emit the wasPlayPaused signal so that the application knows to either play or pause the audio
    emit this->wasPlayPaused();
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Stop()
{
    // "Stopping" audio doesn't really make sense in this context, so this method does nothing
    // I'm not 100% sure about this one, though. I may revisit this at a later date.
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Play()
{
    // Emit the wasPlayed signal so that the application knows the play the audio
    emit this->wasPlayed();
}

void WNLMPRISMediaPlayer2PlayerAdaptor::Seek(qlonglong Offset)
{
    // Application does not allow seeking, so this method does nothing
    // Prevent unused parameter warnings
    (void)Offset;
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::SetPosition(QDBusObjectPath TrackId, qlonglong Position)
{
    // Application does not allow seeking, so this method does nothing
    // Prevent unused parameter warnings
    (void)TrackId;
    (void)Position;
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::OpenUri(QString Uri)
{
    // Opening URIs doesn't really make sense in this context, so this method does nothing
    // Prevent unused parameter warnings
    (void)Uri;
    return;
}

void WNLMPRISMediaPlayer2PlayerAdaptor::emitPropertyChanged(QString propertyName)
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
