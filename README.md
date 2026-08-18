# OMSens_Qt

A GUI interface for OMSens which can be loaded into OMEdit as a plugin.

## Dependencies

* [OpenModelica](https://github.com/OpenModelica/OpenModelica) - Just the plugin interface header files are needed.

## Build instructions

If needed fix paths for the plugin interface headers files in `OMSensPlugin.h`.

Follow the instructions matching your OS:

* [OMCompiler/README.Linux.md](https://github.com/OpenModelica/OpenModelica/blob/master/OMCompiler/README.Linux.md)
* [OMCompiler/README.Windows.md](https://github.com/OpenModelica/OpenModelica/blob/master/OMCompiler/README.Windows.md)

On Windows, OMSens_Qt is built as part of the normal CMake `install` target (see
`OM_ENABLE_GUI_CLIENTS` in [README.cmake.md](https://github.com/OpenModelica/OpenModelica/blob/master/README.cmake.md)); no extra step is needed.

## Bug Reports

* Submit bugs through the [OpenModelica GitHub issues](https://github.com/OpenModelica/OpenModelica/issues/new).
* [Pull requests](../../pulls) are welcome ❤️

## License

See [OSMC-License.txt](OSMC-License.txt).
