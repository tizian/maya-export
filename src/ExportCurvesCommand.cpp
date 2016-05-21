#include "ExportCurvesCommand.h"

#include <maya/MArgList.h>
#include <maya/MFnPfxGeometry.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MIOStream.h>
#include <maya/MItSelectionList.h>
#include <maya/MRenderLineArray.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MSelectionList.h>
#include <maya/MVectorArray.h>

#include <cmake_config.h>

#include <iostream>
#include <fstream>

MStatus ExportCurvesCommand::doIt(const MArgList &args) {
    MStatus status;
    std::string str;

    // Input arguments
    MString filename = "out.curves";
    int nVertices = 100;

    // Parse the arguments
    for (unsigned int i = 0; i < args.length(); i++) {
        if (MString("-o") == args.asString(i, &status) && status == MS::kSuccess) {
            MString tmp = args.asString(++i, &status);
            if (MS::kSuccess == status) {
                filename = tmp;
            }
        }

        if (MString("-n") == args.asString(i, &status) && status == MS::kSuccess) {
            int tmp = args.asInt(++i, &status);
            if (MS::kSuccess == status) {
                nVertices = tmp;
            }
        }
    }

    // Get selection list
    MSelectionList list;
    MGlobal::getActiveSelectionList(list);

    // Create selection list iterator for curves
    MItSelectionList listIter(list, MFn::kNurbsCurve, &status);
    if (status != MS::kSuccess) {
        displayError("Could not create selection list iterator");
        return status;
    }

    // Check number of selected curves
    if (listIter.isDone()) {
        displayError("No curve selected");
        return MS::kFailure;
    }

    std::string path = FILE_OUTPUT_PATH;
    path += "/";
    path += filename.asChar();

    MGlobal::displayInfo(path.c_str());
    std::ofstream file;
    file.open(path);

    MDagPath dagPath;
    MObject object;
    MFnNurbsCurve node;

    for (; !listIter.isDone(); listIter.next()) {
        listIter.getDagPath(dagPath, object);
        node.setObject(dagPath);

        double length = node.length();
        double ds = length / nVertices;

        MPoint p;
        for (int j = 0; j < nVertices; ++j) {
            double s = j * ds;
            double t = node.findParamFromLength(s);
            node.getPointAtParam(t, p);
            file << p[0] << " " << p[1] << " " << p[2] << "\n";
        }
        file << "\n";
    }

    file.close();

    return MS::kSuccess;
}

ExportCurvesCommand::ExportCurvesCommand() {}
ExportCurvesCommand::~ExportCurvesCommand() {}

bool ExportCurvesCommand::isUndoable() const {
    return false;
}

void *ExportCurvesCommand::creator() {
    return new ExportCurvesCommand();
}