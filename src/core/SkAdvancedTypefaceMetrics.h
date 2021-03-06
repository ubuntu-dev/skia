/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkAdvancedTypefaceMetrics_DEFINED
#define SkAdvancedTypefaceMetrics_DEFINED

#include "SkRect.h"
#include "SkRefCnt.h"
#include "SkString.h"
#include "SkTDArray.h"
#include "SkTemplates.h"
#include "SkSinglyLinkedList.h"

/** \class SkAdvancedTypefaceMetrics

    The SkAdvancedTypefaceMetrics class is used by the PDF backend to correctly
    embed typefaces. This class is created and filled in with information by
    SkTypeface::getAdvancedTypefaceMetrics.
*/

class SkAdvancedTypefaceMetrics : public SkRefCnt {
public:

    SkAdvancedTypefaceMetrics()
        : fType(SkAdvancedTypefaceMetrics::kOther_Font)
        , fFlags(SkAdvancedTypefaceMetrics::kEmpty_FontFlag)
        , fLastGlyphID(0)
        , fEmSize(0)
        , fStyle(0)
        , fItalicAngle(0)
        , fAscent(0)
        , fDescent(0)
        , fStemV(0)
        , fCapHeight(0)
        , fBBox(SkIRect::MakeEmpty()) {}

    ~SkAdvancedTypefaceMetrics() {}

    SkString fFontName;

    enum FontType {
        kType1_Font,
        kType1CID_Font,
        kCFF_Font,
        kTrueType_Font,
        kOther_Font,
    };
    // The type of the underlying font program.  This field determines which
    // of the following fields are valid.  If it is kOther_Font the per glyph
    // information will never be populated.
    FontType fType;

    enum FontFlags {
        kEmpty_FontFlag          = 0x0,  //!<No flags set
        kMultiMaster_FontFlag    = 0x1,  //!<May be true for Type1, CFF, or TrueType fonts.
        kNotEmbeddable_FontFlag  = 0x2,  //!<May not be embedded.
        kNotSubsettable_FontFlag = 0x4,  //!<May not be subset.
    };
    // Global font flags.
    FontFlags fFlags;

    uint16_t fLastGlyphID; // The last valid glyph ID in the font.
    uint16_t fEmSize;  // The size of the em box (defines font units).

    // These enum values match the values used in the PDF file format.
    enum StyleFlags {
        kFixedPitch_Style  = 0x00001,
        kSerif_Style       = 0x00002,
        kScript_Style      = 0x00008,
        kItalic_Style      = 0x00040,
        kAllCaps_Style     = 0x10000,
        kSmallCaps_Style   = 0x20000,
        kForceBold_Style   = 0x40000
    };
    uint16_t fStyle;        // Font style characteristics.
    int16_t fItalicAngle;   // Counterclockwise degrees from vertical of the
                            // dominant vertical stroke for an Italic face.
    // The following fields are all in font units.
    int16_t fAscent;       // Max height above baseline, not including accents.
    int16_t fDescent;      // Max depth below baseline (negative).
    int16_t fStemV;        // Thickness of dominant vertical stem.
    int16_t fCapHeight;    // Height (from baseline) of top of flat capitals.

    SkIRect fBBox;  // The bounding box of all glyphs (in font units).

    // The names of each glyph, only populated for postscript fonts.
    SkTArray<SkString> fGlyphNames;

    // The mapping from glyph to Unicode, only populated if
    // kToUnicode_PerGlyphInfo is passed to GetAdvancedTypefaceMetrics.
    SkTDArray<SkUnichar> fGlyphToUnicode;

private:
    typedef SkRefCnt INHERITED;
};


#endif
