#include <maya/MFnPfxGeometry.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MIOStream.h>
#include <maya/MItSelectionList.h>
#include <maya/MRenderLineArray.h>
#include <maya/MRenderLine.h>
#include <maya/MSimple.h>
#include <maya/MSelectionList.h>
#include <maya/MVectorArray.h>

#include <cmake_config.h>

#include <iostream>
#include <fstream>

DeclareSimpleCommand(exportHair, "Tizian Zeltner", "1.0");
MStatus exportHair::doIt(const MArgList &args) {
	MStatus status;
	std::string str;

	// Input arguments
	MString filename = "out";

	// Parse the arguments
	for (unsigned int i = 0; i < args.length(); i++) {
		if (MString("-o") == args.asString(i, &status) && status == MS::kSuccess) {
			MString tmp = args.asString(++i, &status);
			if (MS::kSuccess == status) {
				filename = tmp;
			}
		}
	}

	// Get selection list
	MSelectionList list;
	MGlobal::getActiveSelectionList(list);

	// Create selection list iterator for curves
	MItSelectionList listIter(list, MFn::kPfxHair, &status);
	if (status != MS::kSuccess) {
		displayError("Could not create selection list iterator");
		return status;
	}

	// Check number of selected curves
	if (listIter.isDone()) {
		displayError("No pfxHair selected");
		return MS::kFailure;
	}

	MDagPath dagPath;
	MObject object;
	MFnPfxGeometry node;
	listIter.getDagPath(dagPath, object);

	node.setObject(dagPath);

	MRenderLineArray mainLines, leafLines, flowerLines;
	status = node.getLineData(mainLines, leafLines, flowerLines, true, false, false, false, false, false, false, false, true);

	int nLines = mainLines.length();

	std::string path = FILE_OUTPUT_PATH;
	path += "/";
	path += filename.asChar();
	path += ".curves";

	MGlobal::displayInfo(path.c_str());
	std::ofstream file;
	file.open(path);

	for (int i = 0; i < nLines; ++i) {
		MRenderLine renderLine = mainLines.renderLine(i, &status);
		if (status == MS::kSuccess) {
			MVectorArray line = renderLine.getLine();
			int nVertices = line.length();
			for (int j = 0; j < nVertices; ++j) {
				MVector vec = line[j];
				file << vec[0] << " " << vec[1] << " " << vec[2] << "\n";
			}
			file << "\n";
		}
	}

	file.close();

	return MS::kSuccess;
}