# OMSens_Qt
A GUI interface for OMSens which can be loaded into OMEdit as a plugin.

## Dependencies

- [OpenModelica](https://openmodelica.org) - Just the plugin interface header files are needed.

## Build instructions

If needed fix paths for the plugin interface headers files in `OMSensPlugin.h`.

### Unix
```bash
$ cd /path/to/OMSens_Qt
$ autoconf
# OPENMODELICAHOME is usually /usr, /opt, /opt/openmodelica, or /path/to/OpenModelica/build
$ ./configure --prefix=/path/to/OPENMODELICAHOME
$ make
$ make install
```

### Windows MinGW
- If you don't have OMDev then download it from the svn repository [here](https://openmodelica.org/svn/OpenModelicaExternal/trunk/tools/windows/OMDev).
- Follow the instructions in [INSTALL.txt](https://openmodelica.org/svn/OpenModelicaExternal/trunk/tools/windows/OMDev/INSTALL.txt).
- Open msys terminal. Either `$OMDEV/tools/msys/mingw32_shell.bat` OR `$OMDEV/tools/msys/mingw64_shell.bat`.
```bash
$ cd /path/to/OMSens_Qt
$ make -f Makefile.omdev.mingw omsens_qt
```

## Bug Reports

- Submit bugs through the [issues](../../issues)
- [Pull requests](../../pulls) are welcome.
