#ifndef GDKRAPSDIMPORTER_H
#define GDKRAPSDIMPORTER_H

#include <Godot.hpp>
#include <Reference.hpp>
#include <Directory.hpp>
#include <ProjectSettings.hpp>
#include <Magick++.h>

#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <map>

// the main include that always needs to be included in every translation unit that uses the PSD library
#include "Psd/Psd.h"

// for convenience reasons, we directly include the platform header from the PSD library.
// we could have just included <Windows.h> as well, but that is unnecessarily big, and triggers lots of warnings.
#include "Psd/PsdPlatform.h"

#include "Psd/PsdMallocAllocator.h"
#include "Psd/PsdNativeFile.h"

#include "Psd/PsdDocument.h"
#include "Psd/PsdColorMode.h"
#include "Psd/PsdLayer.h"
#include "Psd/PsdChannel.h"
#include "Psd/PsdChannelType.h"
#include "Psd/PsdLayerMask.h"
#include "Psd/PsdVectorMask.h"
#include "Psd/PsdLayerMaskSection.h"
#include "Psd/PsdImageDataSection.h"
#include "Psd/PsdImageResourcesSection.h"
#include "Psd/PsdParseDocument.h"
#include "Psd/PsdParseLayerMaskSection.h"
#include "Psd/PsdParseImageDataSection.h"
#include "Psd/PsdParseImageResourcesSection.h"
#include "Psd/PsdLayerCanvasCopy.h"
#include "Psd/PsdInterleave.h"
#include "Psd/PsdPlanarImage.h"
#include "Psd/PsdExport.h"
#include "Psd/PsdExportDocument.h"
#include "Psd/PsdLayerType.h"

#include "Kra/KraDocument.h"
#include "Kra/KraExportedLayer.h"
#include "Kra/KraParseDocument.h"
#include "Kra/KraExportDocument.h"

PSD_PUSH_WARNING_LEVEL(0)
// disable annoying warning caused by xlocale(337): warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
#pragma warning(disable : 4530)
#include <string>
#include <sstream>
PSD_POP_WARNING_LEVEL

namespace godot {

class KRAPSDImporter : public Reference {
    GODOT_CLASS(KRAPSDImporter, Reference)

typedef enum
{
    PNG,
    TGA
} exportType;

typedef enum
{
    KRA,
    PSD
} importType;

typedef enum
{
    MONOCHROME,
    RGB,
    RGBA
} colorSpaceName;

private:
    String rawFilePath;
    String targetFolderPath;
    String errorMessage;

    bool verboseMode;
    bool cropToCanvas;
    bool mirrorUniverse;

    int exportType;
    int importType;
    int channelType;

    float resizeFactor;

    bool ExportAllPSDLayers();
    bool ExportAllKRALayers();
    std::wstring ExportLayer(const wchar_t* name, unsigned int width, unsigned int height, const uint8_t* data);
    bool EmitPSDTextureProperties(std::wstring filename, psd::Layer* layer);
    bool EmitKRATextureProperties(std::wstring filename, kra::KraExportedLayer* layer);
    bool SaveTexture(const wchar_t* filename, unsigned int width, unsigned int height, const uint8_t* data);

public:
    static void _register_methods();

    KRAPSDImporter();
    ~KRAPSDImporter();

    void _init();

    bool ExportAllLayers();
};

}

#endif