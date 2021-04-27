# WhiteNoiseLinux

A Linux application written using Qt that plays white noise (and other ambient sound) audio files in the background. Supports layering multiple sounds over one another. Sounds automatically loop indefinitely.

## Screenshots

<p float="left">
    <img src="screenshots/main.png?raw=true" width="400">
    <img src="screenshots/about.png?raw=true" width="400">
</p>

## Installation

### Distro Packages (Recommended)

Use the latest provided package for your distro, available from the [OpenSUSE Build Service](https://software.opensuse.org//download.html?project=home%3Aryangwsimmons%3AWhiteNoiseLinux&package=whitenoiselinux). Click the link, select your distro, and follow the instructions for adding the repository and installing manually. Unless you know what you're doing, don't just grab the binary packages, or else you won't get updates.

### AppImage

AppImages are also available from the GitHub [releases page](https://github.com/ryangwsimmons/WhiteNoiseLinux/releases). If your distro is not listed on the page at the OpenSUSE build service, this is the best option for using the application. To run the AppImage:

1. Download the latest `.AppImage` file from the GitHub releases page (linked above).

2. Open a terminal in the location the file downloaded to (usually your Downloads folder) and run the following:
   
   ```shell
   chmod +x <name_of_file>.AppImage
   ```
   
   After this, you should be able to run the program by simply opening the `.AppImage` file.

3. (Optional) Add a menu entry for the application using [`appimaged`](https://github.com/probonopd/go-appimage).

### Manual Installation

1. Ensure you have all the dependencies for the application installed (methods will vary depending upon your distribution of choice, you will need development files in addition to the normal library packages):
   
   - Qt 5 (including the Core, GUI, Widgets, D-Bus, and Concurrent components)
   
   - TagLib
   
   - PortAudio
   
   - LibSndFile

2. Clone the repo and `cd` into it:
   
   ```shell
   git clone https://github.com/ryangwsimmons/WhiteNoiseLinux.git
   cd WhiteNoiseLinux
   ```

3. Create a new directory (you can name it whatever you like, I'm naming it "build" here) and `cd` into it
   
   ```shell
   mkdir build
   cd build
   ```

4. Run `cmake`. If you've successfully satisfied all the dependencies, the following command shouldn't result in any errors:
   
   ```shell
   cmake ..
   ```

5. Run `make` to build the application:
   
   ```shell
   make
   ```

6. Once this process completes, you should have an executable called `WhiteNoiseLinux` in the `build` directory. From this point, while you should just be able to place this executable anywhere, I would strongly recommend using this executable to create a software package for your specific distro. Details regarding how to do this can be readily found online. If you really insist on not doing this, you can also run `sudo make install` to install the application files to the `/usr/local` installation prefix.

## Usage

On first run, the app creates a `.whitenoiselinux` directory in your home directory. Inside this directory, there is another directory called `sounds`.

Inside this directory, place the sounds you want. These sounds must be 2 channel (stereo) Ogg/Vorbis audio files. If an audio file has a title in its metadata, this title will be used instead of the file name in the interface.

To obtain sounds, I'd recommend the following process:

1. Go on YouTube, and search for "white noise".
2. Find a few different sounds you like, and download the audio for them with [youtube-dl](https://youtube-dl.org/).
3. Use [Audacity](https://www.audacityteam.org/) to trim the audio file down to around 2 minutes or so.
4. Export this new, trimmed audio as an Ogg file.
5. During the export process, you will be given the option to enter a "Track Title" for the file. You can enter the name you would like for the sound in this field.
6. Save this audio file in the `~/.whitenoiselinux/sounds` directory.

## Attributions

The following images were used to create the icon for this app:

- [Tux-flat.svg](https://commons.wikimedia.org/wiki/File:Tux-flat.svg) by Josef Norlin (Licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/legalcode))
- [Icon of black headphones](https://commons.wikimedia.org/wiki/File:Headphones_icon.svg) by Marek Mazurkiewicz (Licensed under [CC0 1.0](https://commons.wikimedia.org/wiki/File:Headphones_icon.svg))
- [waveform](https://thenounproject.com/term/waveform/165177/) by Jack Zwanenburg (Licensed under [CC BY 3.0 US](https://creativecommons.org/licenses/by/3.0/us/legalcode))

All of these images were modified in order to create the icon.
