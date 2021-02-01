import os
import audio_metadata as metadata
from WNLSound import WNLSound

class WNLSoundGrabber:
    def getSounds(self):
        # Define a class attribute for the set of sounds in the sound folder
        self.sounds = []

        # Get the home directory of the current user
        home = os.getenv("HOME")

        # If the WNL directory exists on the user's system, check for sounds, otherwise create the directory structure
        if ".whitenoiselinux" in os.listdir(home):
            if "sounds" in os.listdir(home + "/.whitenoiselinux"):
                soundsdir = home + "/.whitenoiselinux/sounds"

                for file in os.listdir(soundsdir):
                    if file.endswith(".ogg"):
                        sound = metadata.load(soundsdir + "/" + file)

                        self.sounds.append(WNLSound(sound.tags.title[0] if hasattr(sound.tags, "title") != False else file, soundsdir + "/" + file, None))
            else:
                os.mkdir(home + "/.whitenoiselinux/sounds")
        else:
            os.makedirs(home + "/.whitenoiselinux/sounds")

        # Return the list of sounds
        return self.sounds