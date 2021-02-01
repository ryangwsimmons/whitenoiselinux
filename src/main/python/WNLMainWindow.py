from PyQt5.QtWidgets import (QMainWindow, QVBoxLayout, QHBoxLayout, QPushButton, QWidget, QGridLayout, QLabel, QListWidget, QListWidgetItem)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from WNLAboutDialog import WNLAboutDialog
from WNLSoundGrabber import WNLSoundGrabber
from WNLPlaybackManager import WNLPlaybackManager

# Class for main application window
class WNLMainWindow(QMainWindow):
    def __init__(self, appctxt, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # Set the application context variable
        self.appctxt = appctxt

        # Set window and application title
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

        # Create media controls layout
        self.controlsLayout = QHBoxLayout()
        self.controlsLayout.setAlignment(Qt.AlignCenter)
        self.controlsLayout.setContentsMargins(0, 10, 0, 10)

        # Populate media controls layout
        self.populateControls()

        # Add media controls layout to main layout
        self.mainLayout.addLayout(self.controlsLayout)

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

        self.getAvailableSounds()

        # Create and populate the QVBoxLayout for moving sounds to the currently playing box
        moveSoundsWidget = QWidget()
        moveSoundsWidget.setFixedHeight(100)

        moveSoundsLayout = QVBoxLayout()

        addSound = QPushButton()
        addSound.setFixedSize(75, 25)
        addSound.setIcon(QIcon.fromTheme("go-next"))
        addSound.setToolTip("Add Sound to Currently Playing")
        addSound.setEnabled(False)
        addSound.clicked.connect(self.addSound)

        rmSound = QPushButton()
        rmSound.setFixedSize(75, 25)
        rmSound.setIcon(QIcon.fromTheme("go-previous"))
        rmSound.setToolTip("Remove Sound from Currently Playing")
        rmSound.setEnabled(False)
        rmSound.clicked.connect(self.rmSound)

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

        # Set the slot for when an item in the available sounds list is selected, so that the add button is enabled
        self.soundSelectionLayout.itemAt(0).itemAt(1).widget().selectionModel().selectionChanged.connect(self.handleAvailListChange)

        # Set the slot for when an item in the currently playing sounds list is selected, so that the remove button is enabled
        self.soundSelectionLayout.itemAt(2).itemAt(1).widget().selectionModel().selectionChanged.connect(self.handlePlayingListChange)

        # Populate the list of sounds
        self.populateAvailableSounds()

    def getAvailableSounds(self):
        soundGrabber = WNLSoundGrabber()
        
        # Get the sounds from file
        self.sounds = soundGrabber.getSounds()

        # Instantiate the playback manager
        self.playbackManager = WNLPlaybackManager(self.sounds)

    def populateAvailableSounds(self):
        # Add sounds to the available sounds list
        for sound in self.sounds:
            newItem = QListWidgetItem()
            newItem.setText(sound.name)
            newItem.setData(Qt.UserRole, sound)
            self.soundSelectionLayout.itemAt(0).itemAt(1).widget().addItem(newItem)

    def addSound(self):
        # Get the sound item and remove it from the available sounds list
        soundItem = self.soundSelectionLayout.itemAt(0).itemAt(1).widget().takeItem(
            self.soundSelectionLayout.itemAt(0).itemAt(1).widget().selectionModel().selectedIndexes()[0].row()
        )

        # Add the sound to the list of currently playing sounds
        self.soundSelectionLayout.itemAt(2).itemAt(1).widget().addItem(soundItem)

        # If the currently playing list now has 8 sounds (the maximum), disable the "available" list
        if self.soundSelectionLayout.itemAt(2).itemAt(1).widget().count() >= 8:
            self.soundSelectionLayout.itemAt(0).itemAt(1).widget().selectionModel().clear()
            self.soundSelectionLayout.itemAt(0).itemAt(1).widget().setEnabled(False)

        # Tell the playback manager to add the sound to the list
        self.playbackManager.addSound(soundItem.data(Qt.UserRole))

    def rmSound(self):
        # Get the sound item and remove it from the currently playing sounds list
        soundItem = self.soundSelectionLayout.itemAt(2).itemAt(1).widget().takeItem(
            self.soundSelectionLayout.itemAt(2).itemAt(1).widget().selectionModel().selectedIndexes()[0].row()
        )

        # Add the sound to the list of available sounds
        self.soundSelectionLayout.itemAt(0).itemAt(1).widget().addItem(soundItem)

        # If the currently playing list now has less than 8 sounds (the maximum), enable the "available" list
        if self.soundSelectionLayout.itemAt(2).itemAt(1).widget().count() < 8:
            self.soundSelectionLayout.itemAt(0).itemAt(1).widget().setEnabled(True)

        # Tell the playback manager to remove the sound from the list
        self.playbackManager.rmSound(soundItem.data(Qt.UserRole))

    def handleAvailListChange(self, currentSelection):
        # If the number of selected sounds is greater than 0, enable the add button, otherwise disable it
        if len(currentSelection.indexes()) > 0:
            self.soundSelectionLayout.itemAt(1).widget().layout().itemAt(0).widget().setEnabled(True)
        else:
            self.soundSelectionLayout.itemAt(1).widget().layout().itemAt(0).widget().setEnabled(False)

    def handlePlayingListChange(self, currentSelection):
        # If the number of selected sounds is greater than 0, enable the remove button, otherwise disable it
        if len(currentSelection.indexes()) > 0:
            self.soundSelectionLayout.itemAt(1).widget().layout().itemAt(1).widget().setEnabled(True)
        else:
            self.soundSelectionLayout.itemAt(1).widget().layout().itemAt(1).widget().setEnabled(False)

    def populateControls(self):
        # Create the play/pause button
        playPause = QPushButton()
        playPause.setFixedSize(50, 50)
        playPause.setIcon(QIcon.fromTheme("media-playback-start"))
        playPause.setToolTip("Start Playing Audio")
        playPause.clicked.connect(self.handlePlayPauseClick)

        # Add the play/pause button to the media controls layout
        self.controlsLayout.addWidget(playPause)

    def handlePlayPauseClick(self):
        # Change the icon from play to pause, or vice versa, depending on the current status, and change playback accordingly
        if self.controlsLayout.itemAt(0).widget().icon().name() == "media-playback-start":
            # Change the icon
            self.controlsLayout.itemAt(0).widget().setIcon(QIcon.fromTheme("media-playback-pause"))
            self.controlsLayout.itemAt(0).widget().setToolTip("Pause Audio")

            # Play audio
            self.playbackManager.playAudio()
        else:
            # Change the icon
            self.controlsLayout.itemAt(0).widget().setIcon(QIcon.fromTheme("media-playback-start"))
            self.controlsLayout.itemAt(0).widget().setToolTip("Start Playing Audio")

            # Pause the audio
            self.playbackManager.pauseAudio()