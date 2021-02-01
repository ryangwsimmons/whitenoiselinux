# WhiteNoiseLinux
A Linux application written using PyQt5 to play white noise audio files in the background. Supports layering multiple sounds over one another. Sounds automatically loop indefinitely.

## Screenshots
<p float="left">
    <img src="screenshots/main.png?raw=true" width="400">
    <img src="screenshots/about.png?raw=true" width="400">
</p>

## Usage
On first run, the app creates a `.whitenoiselinux` directory in your home directory. Inside this directory, there is another directory called `sounds`.

Inside this directory, place the sounds you want. These sounds must be OGG audio files. If an audio file has a title in its metadata, this title will be used instead of the file name in the interface.

To obtain sounds, I'd recommend the following process:

1. Go on YouTube, and search for "white noise".
2. Find a few different sounds you like, and download the audio for them with [youtube-dl](https://youtube-dl.org/).
3. Use [Audacity](https://www.audacityteam.org/) to trim the audio file down to around 2 minutes or so.
4. Export this new, trimmed audio as an OGG file.
5. During the export process, you will be given the option to enter a "Track Title" for the file. You can enter the name you would like for the sound in this field.
6. Save this audio file in the `~/.whitenoiselinux/sounds` directory.

## Installation
### Distro Packages (Recommended)
Use the latest provided package for your distro, available on the [releases](https://github.com/ryangwsimmons/WhiteNoiseLinux/releases) page.

### Manual Installation
This project makes use of [FBS](https://build-system.fman.io/), so in order to compile and install an executable, you'll need to do a few things:

1. Install Python 3.6.12. This is the latest version of Python that FBS supports as of me writing this. If your distro doesn't ship with Python 3.6, I'd recommend installing it using [pyenv](https://github.com/pyenv/pyenv).
    ```shell
    PYTHON_CONFIGURE_OPTS="--enable-shared" pyenv install 3.6.12
    ```

2. Clone the git repo

3. Enter the cloned folder, and tell pyenv to switch to Python 3.6:
    ```shell
    pyenv local 3.6.12
    ```

4. Create a new Python virtual environment, upgrade `pip` to the latest version, and install the required Python modules:
    ```Shell
    python3 -m venv venv
    source venv/bin/activate
    pip install pip --upgrade
    pip install fbs pyqt5 dataclasses audio-metadata pygame
    ```

5. Copy the code from [this GitHub issue comment](https://github.com/pyinstaller/pyinstaller/issues/3528#issuecomment-424146025), and paste it into a new file called `hook-pendulum.py` in the `venv/lib/python3.6/site-packages/PyInstaller/hooks` directory. This allows PyInstaller to work with the `pendulum` module needed by `audio-metadata`.

6. Run `fbs freeze` in the root of the cloned folder.

This will create an executable in the `target` folder. You can move this executable anywhere you want on your system, and it should work.

## Attribution
The following images were used to create the icon for this app:
- [Tux-flat.svg](https://commons.wikimedia.org/wiki/File:Tux-flat.svg) by Josef Norlin (Licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/legalcode))
- [Icon of black headphones](https://commons.wikimedia.org/wiki/File:Headphones_icon.svg) by Marek Mazurkiewicz (Licensed under [CC0 1.0](https://commons.wikimedia.org/wiki/File:Headphones_icon.svg))
- [waveform](https://thenounproject.com/term/waveform/165177/) by Jack Zwanenburg (Licensed under [CC BY 3.0 US](https://creativecommons.org/licenses/by/3.0/us/legalcode))

All of these images were modified in order to create the icon.
