# OMSens_Qt
A GUI interface for OMSens which can be loaded into OMEdit as a plugin.

## Dependencies

  - [OpenModelica Compiler](../OMCompiler) - Just the plugin interface header files are needed.

## Build instructions

If needed fix paths for the plugin interface headers files in `OMSensPlugin.h`.


Follow the instructions matching your OS:

  - [OMCompiler/README.Linux.md](../OMCompiler/README.Linux.md)
  - [OMCompiler/README.Windows.md](../OMCompiler/README.Windows.md)

### Windows MSYS Makefiles

If you used MSYS Makefiles to compile OpenModelica you need one additional step:

Start a MSYS terminal `$OMDEV\tools\msys\mingw64.exe` (64 bit) or
`$OMDEV\tools\msys\mingw32.exe` (32 bit) and run:

```bash
$ cd /path/to/OpenModelica
make -f Makefile.omdev.mingw omsens_qt -j<Nr. of cores>
```

## Bug Reports

  - Submit bugs through the [OpenModelica GitHub issues](https://github.com/OpenModelica/OpenModelica/issues/new).
  - [Pull requests](https://github.com/OpenModelica/OpenModelica/pulls) are welcome ❤️
