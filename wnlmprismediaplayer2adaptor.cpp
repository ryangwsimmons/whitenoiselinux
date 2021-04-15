#include "wnlmprismediaplayer2adaptor.h"

WNLMPRISMediaPlayer2Adaptor::WNLMPRISMediaPlayer2Adaptor(QObject* object)
    : QDBusAbstractAdaptor(object),
      CanQuit(false),
      CanRaise(false),
      HasTrackList(false),
      Identity("WhiteNoiseLinux"),
      SupportedUriSchemes(QStringList()),
      SupportedMimeTypes(QStringList("application/ogg"))
{

}

bool WNLMPRISMediaPlayer2Adaptor::getCanQuit()
{
    return this->CanQuit;
}

bool WNLMPRISMediaPlayer2Adaptor::getCanRaise()
{
    return this->CanRaise;
}

bool WNLMPRISMediaPlayer2Adaptor::getHasTrackList()
{
    return this->HasTrackList;
}

QString WNLMPRISMediaPlayer2Adaptor::getIdentity()
{
    return this->Identity;
}

QStringList WNLMPRISMediaPlayer2Adaptor::getSupportedUriSchemes()
{
    return this->SupportedUriSchemes;
}

QStringList WNLMPRISMediaPlayer2Adaptor::getSupportedMimeTypes()
{
    return this->SupportedMimeTypes;
}
