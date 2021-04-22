// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

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

bool WNLSound::operator == (const WNLSound& rhs)
{
    return this->getTitle() == rhs.getTitle() && this->getFilePath() == rhs.getFilePath();
}
