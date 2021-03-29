#include "wnlsoundgrabber.h"

namespace Vorbis = TagLib::Ogg::Vorbis;

WNLSoundGrabber::WNLSoundGrabber()
{

}

void WNLSoundGrabber::getSounds()
{
    // Create the sounds directory if it does not yet exist
    QString soundsPath(QDir::homePath() + QDir::separator() + ".whitenoiselinux" + QDir::separator() + "sounds");
    if (!QDir::home().mkpath(soundsPath))
    {
        qDebug() << "Unable to create sounds directory structure, do you have write permissions in your home folder?";
        return;
    }

    // Create a QDir object to represent the sounds directory
    QDir soundsDir(soundsPath);

    //Iterate over each file in the folder, getting its name and creating a structure for it, adding that structure to the vector
    QStringList soundFiles = soundsDir.entryList();
    for (QString soundFilePath : soundFiles)
    {
        if (soundFilePath != "." && soundFilePath != "..")
        {
            // Construct a TabLib Vorbis file for the sound, and check if opening the file succeeded
            Vorbis::File soundFile(soundsDir.absoluteFilePath(soundFilePath).toLatin1().data(), true);
            if (!soundFile.isOpen())
            {
                qDebug() << "Unable to open" << soundFilePath;
                continue;
            }

            // If a title is found, the title won't be null
            QString soundTitle;
            if (soundFile.tag()->title() != TagLib::String::null)
            {
                soundTitle = soundFile.tag()->title().toCString(true);
            }
            else
            {
                // If a title is not found, use the file name instead
                soundTitle = soundFilePath;
            }

            // Create a new WNLSound struct for the sound
            WNLSound sound = {soundTitle, soundsDir.absoluteFilePath(soundFilePath)};

            // Append the struct to the sounds vector
            this->sounds.append(sound);
        }
    }
}
