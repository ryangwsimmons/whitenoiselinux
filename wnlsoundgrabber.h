#ifndef WNLSOUNDGRABBER_H
#define WNLSOUNDGRABBER_H

#include <QDebug>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QVector>
#include <taglib/vorbisfile.h>
#include <taglib/xiphcomment.h>

// Define a struct for storing sounds
struct WNLSound
{
    QString name;
    QString fileName;
};
Q_DECLARE_METATYPE(WNLSound)

class WNLSoundGrabber
{
public:
    // Declare a vector of sounds for storing all sounds the program detects on startup
    QVector<WNLSound> sounds;

    WNLSoundGrabber();

    // Declare a method for getting information on the sounds in the sound folder
    void getSounds();
};

#endif // WNLSOUNDGRABBER_H
