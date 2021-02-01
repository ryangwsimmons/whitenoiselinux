from WNLSound import WNLSound
import pygame

class WNLPlaybackManager:
    def __init__(self, sounds):
        self.sounds = sounds
        self.playing = False

        # Instantiate the sound mixer
        pygame.mixer.init()
        pygame.init()

    def addSound(self, sound):
        # Instantiate the new player
        sound.sound = pygame.mixer.Sound(sound.fileName)
        sound.sound.play(loops = -1)

        # If the audio is currently paused, prevent the new sound from playing
        if self.playing == False:
            pygame.mixer.pause()

    def rmSound(self, sound):
        sound.sound.stop()
        del sound.sound

    def playAudio(self):
        # Tell the mixer to unpause all audio channels
        pygame.mixer.unpause()

        # Set the "playing" variable to True
        self.playing = True

    def pauseAudio(self):
        # Tell the mixer to pause all audio channels
        pygame.mixer.pause()

        # Set the "playing" variable to False
        self.playing = False