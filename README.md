# maya-export

## Description

Collection of custom Maya export commands.

## Commands

Once the plugin is loaded, call one of these commands in the Maya command line.

### exportHair

Export a selected _pfxHair_ node to a given ASCII text file. The format consists of one hair vertex per line. An empty line signifies the beginning of the next hair. The file will be exported to `maya-export/output`. (See `maya-export/output/example.curves` for an example.)

Arguments:
* `-o <filename>`: specifiy filename (e.g. out.curves)

### exportCurves

Export a set of selected _nurbsCurve_ node to a given ASCII text file. The format consists of one curve vertex per line. An empty line signifies the beginning of the next curve. The file will be exported to `maya-export/output`. (See `maya-export/output/example.curves` for an example.)

Arguments:
* `-o <filename>`: specifiy filename (default: out.curves)
* `-n <nVertices>`: specifiy number of vertices per curve (default: 100)

## Building

Clone the repository and use CMake to generate project files for your favourite IDE or build system. An installed version of the Maya SDK is required.

Unix example using make:
```
git clone https://github.com/tizian/maya-export.git
cd maya-export
mkdir build
cd build
cmake ..
cmake --build . --config Release --target install
```

Additionally, set the following cmake variables:
* `MAYA_VERSION` to your version of Maya (e.g. 2016)
* `MAYA_INSTALL_BASE_PATH` to the Autodesk folder that contains the Maya installation (e.g. C:/Program Files/Autodesk)

The compiled plugin will be located at `maya-export/build/install/plug-ins/maya-export.mll`.

For more information, refer to one of these links:
* [Maya Plugin Tutorial](http://blog.josephkider.com/2015/09/17/using-cmake-to-create-your-first-maya-plug-in/) by Joe Kider
* [Official Maya API Documentation](http://help.autodesk.com/view/MAYAUL/2016/ENU/?guid=__files_Maya_API_introduction_htm)
