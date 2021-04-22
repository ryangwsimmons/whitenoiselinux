#include "wnlsound.h"

WNLSound::WNLSound()
{

}

WNLSound::WNLSound(QString title, QString filePath)
{
    this->title = title;
    this->filePath = filePath;
}

QString WNLSound::getTitle() const
{
    return this->title;
}

void WNLSound::setTitle(QString title)
{
    this->title = title;
}

QString WNLSound::getFilePath() const
{
    return this->filePath;
}

void WNLSound::setFilePath(QString filePath)
{
    this->filePath = filePath;
}
