#ifndef WNLPLAYLIST_H
#define WNLPLAYLIST_H

#include <QObject>
#include <QString>
#include <QVector>

#include "wnlsound.h"

class WNLPlaylist
{
public:
    WNLPlaylist();
    WNLPlaylist(QString name, QString filePath);
    QString getName() const;
    void setName(QString name);
    QString getFilePath() const;
    void setFilePath(QString filePath);
    QVector<WNLSound> getSounds() const;
    void addSound(WNLSound sound);
    bool operator == (const WNLPlaylist& rhs) const;

private:
    QString name;
    QString filePath;
    QVector<WNLSound> sounds;
};
Q_DECLARE_METATYPE(WNLPlaylist)

#endif // WNLPLAYLIST_H
