#include <maya/MFnPlugin.h>

#include "ExportHairCommand.h"
#include "ExportCurvesCommand.h"

MStatus initializePlugin(MObject obj) {
    MFnPlugin plugin(obj, "Tizian Zeltner", "0.1", "Any");
    plugin.registerCommand("exportHair", ExportHairCommand::creator);
	plugin.registerCommand("exportCurves", ExportCurvesCommand::creator);
    return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj) {
    MFnPlugin plugin(obj);
    plugin.deregisterCommand("exportHair");
	plugin.deregisterCommand("exportCurves");
    return MS::kSuccess;
}