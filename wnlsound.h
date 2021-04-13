#ifndef WNLSOUND_H
#define WNLSOUND_H

#include <QString>

// Define a struct for storing sounds
struct WNLSound
{
    QString name;
    QString fileName;
};
Q_DECLARE_METATYPE(WNLSound)

#endif // WNLSOUND_H
