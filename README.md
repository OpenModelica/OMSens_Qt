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
- install git for windows https://git-scm.com/downloads
- make sure we git clone with the correct line endings, run in a terminal:
    ```bash
      git config --global core.eol lf
      git config --global core.autocrlf input
	```
- clone it from the git repository [here](https://openmodelica.org/git/OMDev.git)
  ```
  cd C:\
  git clone https://openmodelica.org/git/OMDev.git
  ```
- follow the instructions in OMDev/INSTALL.txt
- Open the mingw terminal. Either `$OMDEV/tools/msys/mingw32.exe` OR `$OMDEV/tools/msys/mingw64.exe`.
```bash
$ cd /path/to/OMSens_Qt
$ make -f Makefile.omdev.mingw omsens_qt
```

## Bug Reports

- Submit bugs through the [issues](../../issues)
- [Pull requests](../../pulls) are welcome.
