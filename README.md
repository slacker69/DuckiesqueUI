# DuckiesqueUI
<img src="https://raw.githubusercontent.com/slacker69/DuckiesqueUI/main/image.png">

A tool for rapid protocoding DuckyScript programs. It provides syntax highlighting, inject.bin file generation, as well as on-the-fly sampling for parts of the code by simplely clicking an "EXEC" button. Not all code can be tested, but can still be a useful tool.

## Getting Started

Some pre-compiled binaries are made available which may just for for you (without installing anything) or may not work on your system, but compiling the code from source is the best way to use this program anyway. The target Qt version is 5.12, but other versions may work as well.

### Linux from source
To deploy this on Linux, your have to install the X11 X Test Extension library (```sudo apt-get install libxtst-dev```), as well at the Qt 5 Framework. Then follow the Qt instructions to build the application.

[linux deployment](https://doc.qt.io/qt-5/linux-deployment.html)
```
make clean
PATH=/path/to/Qt/bin:$PATH
export path
qmake -config release
make
```
Then just run as ```./DuckiesqueUI```

### Windows from source
On Windows you will need the Qt Framework, maybe also install Qt Creator as well, it's a nice IDE that makes compiling and running very easy.

### MacOS from source
On Mac you will also need the Qt Framework, and again Qt Creator makes compiling and running very easy.

## Operation

Starting a new page, type out the DuckyScript that you would like to test, then when you want to test it, click the EXEC button and it will try to execute that program on your computer. You can save the *.ds file with the save command, or you can export the compiled binary with the export command.

## Built With

* [Qt 5.12](https://www.qt.io/qt-5-12) - The Qt 5.12 Framework
* [libXtst](https://packages.debian.org/stable/libs/libxtst6) - X Test Extension Library (Linux only)
* [Hak5 USB-Rubber-Ducky](https://github.com/hak5darren/USB-Rubber-Ducky) - The USB Rubber Ducky software

## Versioning

We use [Git](https://git-scm.com/) for versioning. For the versions available, see the [tags on this repository](https://github.com/slacker69/DuckiesqueUI/tags). 

## Authors

* **kdodge** - *Initial work* - [DuckiesqueUI](https://github.com/slacker69/DuckiesqueUI)

See also the list of [contributors](https://github.com/slacker69/DuckiesqueUI/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v2.0 - see the [LICENSE.md](https://github.com/slacker69/DuckiesqueUI/blob/main/LICENSE) file for details

## Acknowledgments

* kdodge
* hak5
