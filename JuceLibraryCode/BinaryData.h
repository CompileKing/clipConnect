/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   CLIP_CONNECT_V1_1_png;
    const int            CLIP_CONNECT_V1_1_pngSize = 96847;

    extern const char*   SMPTE1_png;
    const int            SMPTE1_pngSize = 11067;

    extern const char*   SMPTE2Transparent_png;
    const int            SMPTE2Transparent_pngSize = 16742;

    extern const char*   SMPTE1Transparent_png;
    const int            SMPTE1Transparent_pngSize = 12694;

    extern const char*   SMPTE2_png;
    const int            SMPTE2_pngSize = 14006;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
