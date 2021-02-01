from dataclasses import dataclass
import pygame

@dataclass
class WNLSound:
    name: str
    fileName: str
    sound: pygame.mixer.Sound

    def __eq__(self, other):
        if (self.name == other.name and self.fileName == other.fileName):
            return True
        else:
            return False

    def __ne__(self, other):
        if (self.name == other.name and self.fileName == other.fileName):
            return False
        else:
            return True

    def __str__(self):
        return self.name