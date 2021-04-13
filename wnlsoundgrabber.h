#ifndef WNLSOUNDGRABBER_H
#define WNLSOUNDGRABBER_H

#include <QDebug>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QVector>
#include <taglib/vorbisfile.h>
#include <taglib/xiphcomment.h>

#include "wnlsound.h"

class WNLSoundGrabber
{
public:
    WNLSoundGrabber();

    // Declare a method for getting information on the sounds in the sound folder
    QVector<WNLSound> getSounds();
};

#endif // WNLSOUNDGRABBER_H
