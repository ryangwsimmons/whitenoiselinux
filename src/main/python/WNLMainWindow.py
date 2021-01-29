from PyQt5.QtWidgets import (QMainWindow, QVBoxLayout, QHBoxLayout, QPushButton, QWidget, QGridLayout, QLabel, QListWidget)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from WNLAboutDialog import WNLAboutDialog

# Class for main application window
class WNLMainWindow(QMainWindow):
    def __init__(self, appctxt, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # Set the application context variable
        self.appctxt = appctxt

        # Set window title
        self.setWindowTitle("White Noise Linux")

        # Set default main window size
        self.resize(800, 600)

        # Set main window minimum size
        self.setMinimumSize(800, 600)

        # Create the central widget for the window
        self.centralWidget = QWidget()

        # Create main layout widget
        self.mainLayout = QVBoxLayout()
        self.mainLayout.setAlignment(Qt.AlignTop)

        # Create top bar layout
        self.topBarLayout = QHBoxLayout()
        self.topBarLayout.setAlignment(Qt.AlignRight)

        # Populate top bar with buttons
        self.populateTopBar()

        # Add the top bar to the main layout
        self.mainLayout.addLayout(self.topBarLayout)

        # Create sound selection layout
        self.soundSelectionLayout = QGridLayout()
        self.soundSelectionLayout.setAlignment(Qt.AlignHCenter)

        # Populate sound selection layout
        self.populateSoundSelect()

        # Add sound selection to main layout
        self.mainLayout.addLayout(self.soundSelectionLayout)

        # Set the main layout as the layout for the window
        self.centralWidget.setLayout(self.mainLayout)
        self.setCentralWidget(self.centralWidget)

    def populateTopBar(self):
        # Add the "About" button
        about = QPushButton()
        about.setFixedSize(25, 25)
        about.setIcon(QIcon.fromTheme("help-about"))
        about.setToolTip("About")
        about.clicked.connect(self.openAboutDialog)
        self.topBarLayout.addWidget(about)

    def openAboutDialog(self):
        aboutDialog = WNLAboutDialog(self.appctxt)
        aboutDialog.exec_()

    def populateSoundSelect(self):
        # Create and populate the QVBoxLayout for selecting available sounds
        availSoundsLayout = QVBoxLayout()

        availSoundsLabel = QLabel("Available Sounds:")
        availSoundsSelect = QListWidget()

        availSoundsLayout.addWidget(availSoundsLabel)
        availSoundsLayout.addWidget(availSoundsSelect)

        # Create and populate the QVBoxLayout for moving sounds to the currently playing box
        moveSoundsWidget = QWidget()
        moveSoundsWidget.setFixedHeight(100)

        moveSoundsLayout = QVBoxLayout()

        addSound = QPushButton()
        addSound.setFixedSize(75, 25)
        addSound.setIcon(QIcon.fromTheme("go-next"))
        addSound.setToolTip("Add Sound to Currently Playing")
        addSound.setEnabled(False)

        rmSound = QPushButton()
        rmSound.setFixedSize(75, 25)
        rmSound.setIcon(QIcon.fromTheme("go-previous"))
        rmSound.setToolTip("Remove Sound from Currently Playing")
        rmSound.setEnabled(False)

        moveSoundsLayout.addWidget(addSound)
        moveSoundsLayout.addWidget(rmSound)

        moveSoundsWidget.setLayout(moveSoundsLayout)

        # Create and populate the QVBoxLayout for displaying currently playing sounds
        currSoundsLayout = QVBoxLayout()

        currSoundsLabel = QLabel("Currently Playing:")
        currSoundsSelect = QListWidget()

        currSoundsLayout.addWidget(currSoundsLabel)
        currSoundsLayout.addWidget(currSoundsSelect)

        # Add all the layouts to the sound selection layout
        self.soundSelectionLayout.addLayout(availSoundsLayout, 0, 0, 1, 1)
        self.soundSelectionLayout.addWidget(moveSoundsWidget, 0, 1, 1, 1)
        self.soundSelectionLayout.addLayout(currSoundsLayout, 0, 2, 1, 1)

