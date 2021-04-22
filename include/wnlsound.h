// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#ifndef WNLSOUND_H
#define WNLSOUND_H

#include <QObject>
#include <QString>

class WNLSound
{
public:
    WNLSound();
    WNLSound(QString title, QString filePath);
    QString getTitle() const;
    void setTitle(QString title);
    QString getFilePath() const;
    void setFilePath(QString filePath);
    bool operator == (const WNLSound& rhs);

private:
    QString title;
    QString filePath;
};
Q_DECLARE_METATYPE(WNLSound)

#endif // WNLSOUND_H
