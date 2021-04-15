#include "wnlplaybackmanager.h"

WNLPlaybackManager::WNLPlaybackManager()
    : numChannels(2),
      sampleRate(44100)
{
    // Setup audio stuff
    this->setupAudio();
}

WNLPlaybackManager::~WNLPlaybackManager()
{
    //Close the stream
    PaError err = Pa_CloseStream(this->stream);
    if (err != paNoError)
    {
        qDebug() << "PortAudio encountered an error:";
        qDebug() << Pa_GetErrorText(err);
        return;
    }

    // Terminate PortAudio
    err = Pa_Terminate();
    if (err != paNoError)
    {
        qDebug() << "PortAudio encountered an error:";
        qDebug() << Pa_GetErrorText(err);
    }

    // Close the files of any sounds that were currently playing when the program quit
    for (WNLSoundInfo sound : this->playingSounds)
    {
        int err = sf_close(sound.file);
        if (err != 0)
        {
            qDebug() << sf_strerror(sound.file);
        }
    }
}

int WNLPlaybackManager::paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
                      void* userData)
{
    // Get the playback manager from the user data pointer
    WNLPlaybackManager* playbackManager = (WNLPlaybackManager*)userData;

    // Cast the output buffer to the right type
    float* out = (float*)outputBuffer;

    // Suppress "unused variable" warning
    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;

    // Return the playback manager's PortAudio method
    return playbackManager->paMethod(out, framesPerBuffer);
}

int WNLPlaybackManager::paMethod(float* out, unsigned long framesPerBuffer)
{
    // Zero-out the output buffer
    for (unsigned long i = 0; i < framesPerBuffer * this->numChannels; i++)
    {
        out[i] = 0;
    }

    // Create temporary buffer for each of the sounds to be read to
    float tempBuffer[framesPerBuffer * this->numChannels];

    // Iterate over every sound file, adding the file to the buffer
    for (WNLSoundInfo sound : this->playingSounds)
    {
        // Read the sound file's data out as a float to the output buffer
        int bytesRead = sf_readf_float(sound.file, tempBuffer, framesPerBuffer);

        // Add the sound to the output buffer (reducing volume to prevent peaking)
        for (unsigned long i = 0; i < framesPerBuffer * this->numChannels; i++)
        {
            out[i] += tempBuffer[i] * (1.0 / this->playingSounds.size());
        }

        // If EOF has been reached, seek to the beginning of the file
        if (bytesRead == 0)
        {
            sf_seek(sound.file, 0, SEEK_SET);
        }
    }

    return 0;
}

void WNLPlaybackManager::addSound(WNLSound sound)
{
    // Create a new info struct with default values
    SF_INFO fileInfo = {0, 0, 0, 0, 0, 0};

    // Use libsndfile to open the sound file
    SNDFILE* file = sf_open(sound.fileName.toLatin1().data(), SFM_READ, &fileInfo);

    // If read was unsuccessful, print the reason why to console and return
    if (file == NULL)
    {
        qDebug() << "Encountered an error opening the file " << sound.fileName << ".";
        qDebug() << sf_strerror(NULL);
        return;
    }

    // Save the file and file info to a new WNLSoundInfo struct, then add it to the list of playing sounds
    WNLSoundInfo soundInfo = {sound, file, fileInfo};
    this->playingSounds.append(soundInfo);
}

void WNLPlaybackManager::rmSound(int index)
{
    // Get the WNLSoundInfo struct at the given index
    WNLSoundInfo sound = this->playingSounds.at(index);

    // Close the sound file
    int err = sf_close(sound.file);
    if (err != 0)
    {
        qDebug() << sf_strerror(sound.file);
    }

    // Remove the sound from the list of current playing sounds in the playback manager
    this->playingSounds.remove(index);
}

void WNLPlaybackManager::playAudio()
{
    // Start the stream
    PaError err = Pa_StartStream(this->stream);
    if (err != paNoError)
    {
        qDebug() << "PortAudio encountered an error:";
        qDebug() << Pa_GetErrorText(err);
    }
}

void WNLPlaybackManager::pauseAudio()
{
    PaError err = Pa_StopStream(this->stream);
    if (err != paNoError)
    {
        qDebug() << "PortAudio encountered an error:";
        qDebug() << Pa_GetErrorText(err);
    }
}

bool WNLPlaybackManager::isPaused()
{
    return Pa_IsStreamStopped(this->stream) == 1;
}

QString WNLPlaybackManager::getCurrentlyPlayingString()
{
    // If there are no currently playing sounds, return a message that says as such
    if (this->playingSounds.size() == 0)
    {
        return "No Sounds Selected";
    }

    // Declare a new QStringList for storing the names of the currently playing sounds
    QStringList playingNames;

    // Add the name of each currently playing sound to the string list
    for (WNLSoundInfo soundInfo : this->playingSounds)
    {
        playingNames.append(soundInfo.sound.name);
    }

    // Return a string containing the names of all the sounds playing, separated by ", "
    return playingNames.join(", ");
}

void WNLPlaybackManager::setupAudio()
{
    // Initialize PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        qDebug() << "PortAudio encountered an error:";
        qDebug() << Pa_GetErrorText(err);
        return;
    }

    // Open the default stream
    err = Pa_OpenDefaultStream(&(this->stream),
                               0,
                               this->numChannels,
                               paFloat32,
                               this->sampleRate,
                               paFramesPerBufferUnspecified,
                               &WNLPlaybackManager::paCallback,
                               this);
    if (err != paNoError)
    {
        qDebug() << "PortAudio encountered an error:";
        qDebug() << Pa_GetErrorText(err);
    }
}
