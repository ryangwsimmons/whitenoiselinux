from PyQt5.QtWidgets import (QDialog, QVBoxLayout, QLabel)
from PyQt5.QtCore import Qt

class WNLAboutDialog(QDialog):
    def __init__(self, appctxt, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # Set the title of the about dialog
        self.setWindowTitle("About White Noise Linux")

        # Set the fixed size of the about dialog
        self.setFixedSize(300, 200)

        # Create main layout for about dialog
        self.mainLayout = QVBoxLayout()
        self.mainLayout.setAlignment(Qt.AlignCenter)

        # Create elements for about dialog layout
        self.titleLabel = QLabel("<b>White Noise Linux</b>")
        self.titleLabel.setAlignment(Qt.AlignCenter)
        self.versionLabel = QLabel("Version " + appctxt.build_settings['version'])
        self.versionLabel.setAlignment(Qt.AlignCenter)
        self.authorLabel = QLabel("By Ryan Simmons")
        self.authorLabel.setAlignment(Qt.AlignCenter)
        self.authorLabel.setContentsMargins(0, 5, 0, 0)

        # Add elements to about dialog layout
        self.mainLayout.addWidget(self.titleLabel)
        self.mainLayout.addWidget(self.versionLabel)
        self.mainLayout.addWidget(self.authorLabel)

        # Set the main layout to be the layout for the dialog
        self.setLayout(self.mainLayout)