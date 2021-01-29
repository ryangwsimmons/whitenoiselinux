from PyQt5.QtWidgets import (QMainWindow, QVBoxLayout, QHBoxLayout, QPushButton, QWidget)
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

