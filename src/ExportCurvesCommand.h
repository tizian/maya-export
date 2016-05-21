#pragma once

#include <maya/MPxCommand.h>

class ExportCurvesCommand : public MPxCommand {
public:
	ExportCurvesCommand();
    virtual ~ExportCurvesCommand();

    MStatus doIt(const MArgList &args);
    bool isUndoable() const;
    
    static void *creator();
};