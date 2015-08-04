Terminal
========

[![GitHub release](https://img.shields.io/github/release/hawaii-desktop/hawaii-terminal.svg)](https://github.com/hawaii-desktop/hawaii-terminal)
[![GitHub issues](https://img.shields.io/github/issues/hawaii-desktop/hawaii-terminal.svg)](https://github.com/hawaii-desktop/hawaii-terminal/issues)
[![Build Status](https://travis-ci.org/hawaii-desktop/hawaii-terminal.svg?branch=master)](https://travis-ci.org/hawaii-desktop/hawaii-terminal)

Terminal emulator for the Hawaii desktop environment.

## Dependencies

Qt >= 5.1 with at least the following modules is required:

* [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
* [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)
* [qtquickcontrols](http://code.qt.io/cgit/qt/qtquickcontrols.git)

The following modules and their dependencies are required:

* [ECM >= 1.4.0](http://quickgit.kde.org/?p=extra-cmake-modules.git)

## Build

Building this project is a piece of cake.

Assuming you are in the source directory, just create a build directory
and run cmake:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii ..
```

To do a debug build the last command can be:

```sh
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Debug ..
```

To do a release build instead it can be:

```sh
cmake -DCMAKE_INSTALL_PREFIX=/opt/hawaii -DCMAKE_BUILD_TYPE=Release ..
```

If not passed, the `CMAKE_INSTALL_PREFIX` parameter defaults to /usr/local.
You have to specify a path that fits your needs, /opt/hawaii is just an example.

Package maintainers would pass `-DCMAKE_INSTALL_PREFIX=/usr`.

The `CMAKE_BUILD_TYPE` parameter allows the following values:

* **Debug:** debug build
* **Release:** release build
* **RelWithDebInfo:** release build with debugging information

## Installation

It's really easy, it's just a matter of typing:

```sh
make install
```

from the build directory.
