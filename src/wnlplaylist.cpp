#include "wnlplaylist.h"

WNLPlaylist::WNLPlaylist()
{

}

WNLPlaylist::WNLPlaylist(QString name, QString filePath)
{
    this->name = name;
    this->filePath = filePath;
}

QString WNLPlaylist::getName() const
{
    return this->name;
}

void WNLPlaylist::setName(QString name)
{
    this->name = name;
}

QString WNLPlaylist::getFilePath() const
{
    return this->filePath;
}

void WNLPlaylist::setFilePath(QString filePath)
{
    this->filePath = filePath;
}

QVector<WNLSound> WNLPlaylist::getSounds() const
{
    return this->sounds;
}

void WNLPlaylist::addSound(WNLSound sound)
{
    this->sounds.append(sound);
}

bool WNLPlaylist::operator == (const WNLPlaylist& rhs) const
{
    return this->getName() == rhs.getName() && this->getFilePath() == rhs.getFilePath();
}
