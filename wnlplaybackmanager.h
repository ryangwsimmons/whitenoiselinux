#ifndef WNLPLAYBACKMANAGER_H
#define WNLPLAYBACKMANAGER_H

#include <portaudio.h>
#include <QDebug>
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

    WNLPlaybackManager();
    ~WNLPlaybackManager();
    static int paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
                          void* userData);
    void addSound(WNLSound sound);
    void rmSound(int index);
    void playAudio();
    void pauseAudio();
    bool isPaused();
};

#endif // WNLPLAYBACKMANAGER_H
