#ifndef WNLPLAYBACKMANAGER_H
#define WNLPLAYBACKMANAGER_H

#include <portaudio.h>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <sndfile.h>

#include "wnlsound.h"

struct WNLSoundInfo
{
    WNLSound sound;
    SNDFILE* file;
    SF_INFO fileInfo;
};

class WNLPlaybackManager
{
public:
    PaStream* stream;
    QVector<WNLSoundInfo> playingSounds;
    int numChannels;
    int sampleRate;

    WNLPlaybackManager();
    ~WNLPlaybackManager();
    static int paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
                          void* userData);
    int paMethod(float* out, unsigned long framesPerBuffer);
    void addSound(WNLSound sound);
    void rmSound(int index);
    void playAudio();
    void pauseAudio();
    bool isPaused();
    QString getCurrentlyPlayingString();

private:
    void setupAudio();
};

#endif // WNLPLAYBACKMANAGER_H
