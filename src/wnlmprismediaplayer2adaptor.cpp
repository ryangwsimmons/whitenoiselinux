// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlmprismediaplayer2adaptor.h"

WNLMPRISMediaPlayer2Adaptor::WNLMPRISMediaPlayer2Adaptor(QObject* object)
    : QDBusAbstractAdaptor(object),
      CanQuit(false),
      CanRaise(false),
      HasTrackList(false),
      Identity("WhiteNoiseLinux"),
      DesktopEntry("WhiteNoiseLinux"),
      SupportedUriSchemes(QStringList()),
      SupportedMimeTypes(QStringList("application/ogg"))
{

}

bool WNLMPRISMediaPlayer2Adaptor::getCanQuit() const
{
    return this->CanQuit;
}

bool WNLMPRISMediaPlayer2Adaptor::getCanRaise() const
{
    return this->CanRaise;
}

bool WNLMPRISMediaPlayer2Adaptor::getHasTrackList() const
{
    return this->HasTrackList;
}

QString WNLMPRISMediaPlayer2Adaptor::getIdentity() const
{
    return this->Identity;
}

QString WNLMPRISMediaPlayer2Adaptor::getDesktopEntry() const
{
    return this->DesktopEntry;
}

QStringList WNLMPRISMediaPlayer2Adaptor::getSupportedUriSchemes() const
{
    return this->SupportedUriSchemes;
}

QStringList WNLMPRISMediaPlayer2Adaptor::getSupportedMimeTypes() const
{
    return this->SupportedMimeTypes;
}
