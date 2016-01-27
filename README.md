Terminal
========

[![IRC Network](https://img.shields.io/badge/irc-freenode-blue.svg "IRC Freenode")](https://webchat.freenode.net/?channels=hawaii-desktop)
[![GitHub release](https://img.shields.io/github/release/hawaii-desktop/hawaii-terminal.svg)](https://github.com/hawaii-desktop/hawaii-terminal)
[![GitHub issues](https://img.shields.io/github/issues/hawaii-desktop/hawaii-terminal.svg)](https://github.com/hawaii-desktop/hawaii-terminal/issues)
[![Build Status](https://travis-ci.org/hawaii-desktop/hawaii-terminal.svg?branch=master)](https://travis-ci.org/hawaii-desktop/hawaii-terminal)

Terminal emulator for the Hawaii desktop environment.

## Dependencies

Qt >= 5.5 with at least the following modules is required:

* [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
* [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)
* [qtquickcontrols](http://code.qt.io/cgit/qt/qtquickcontrols.git)

The following modules and their dependencies are required:

* [ECM >= 1.4.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)

# License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

A copy of the license appears in the file LICENSE.GPLv2 included
with this software.

## Build and install

Before building you need to configure the build with cmake and
specify the installation prefix with the `-DCMAKE_INSTALL_PREFIX`
argument.

If you plan to install on ``/usr`` you will also need to enable
`KDE_INSTALL_USE_QT_SYS_PATHS` like this:

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DKDE_INSTALL_USE_QT_SYS_PATHS=ON
make
sudo make install
```

If you want to install on a custom path, let's say ``/opt/hawaii`` you
can build like this:

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/hawaii
make
sudo make install
```

### Build type

You can also specify the build type with the `-DCMAKE_BUILD_TYPE` argument to cmake,
which allows the following values:

* **Debug:** debug build
* **Release:** release build
* **RelWithDebInfo:** release build with debugging information

`CMAKE_BUILD_TYPE` defaults to *RelWithDebInfo*.

An example of debug build, installing under ``/opt/hawaii``:

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Debug
make
sudo make install
```

An example of release build, installing undef ``/opt/hawaii``:

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```
