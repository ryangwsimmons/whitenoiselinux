#ifndef WNLPLAYLIST_H
#define WNLPLAYLIST_H

#include <QObject>
#include <QString>
#include <QVector>

#include "wnlsound.h"

struct WNLPlaylist
{
    QString name;
    QString filePath;
    QVector<WNLSound> sounds;
};

Q_DECLARE_METATYPE(WNLPlaylist)

#endif // WNLPLAYLIST_H
