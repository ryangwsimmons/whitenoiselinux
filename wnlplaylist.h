#ifndef WNLPLAYLIST_H
#define WNLPLAYLIST_H

#include <QObject>
#include <QString>

struct WNLPlaylist
{
    QString name;
    QString filePath;
};
Q_DECLARE_METATYPE(WNLPlaylist)

#endif // WNLPLAYLIST_H
