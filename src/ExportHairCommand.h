#pragma once

#include <maya/MPxCommand.h>

class ExportHairCommand : public MPxCommand {
public:
	ExportHairCommand();
    virtual ~ExportHairCommand();

    MStatus doIt(const MArgList &args);
    bool isUndoable() const;
    
    static void *creator();
};