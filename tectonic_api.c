/* Copyright 2017 the Tectonic Project
 * Licensed under the MIT License.
 */

/* This file implements the FreeType rendering API that is exposed to
 * JavaScript. The details are documented in a place TBD.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <emscripten.h>


static const char *
get_ft_error_message(FT_Error err)
{
    #undef __FTERRORS_H__
    #define FT_ERRORDEF(e, v, s) case e: return s;
    #define FT_ERROR_START_LIST switch (err) {
    #define FT_ERROR_END_LIST }
    #include FT_ERRORS_H
    return "(unknown freetype error)";
}


EMSCRIPTEN_KEEPALIVE
int
render(int font_size, const unsigned char *font, int img_width, int img_height, unsigned char *img)
{
    FT_Library library;
    FT_Face face;
    FT_GlyphSlot slot;
    FT_Error error;
    FT_UInt glyph_index;
    FT_Int i, j, p, q, x, y;
    FT_Int x_max;
    FT_Int y_max;

    if (FT_Init_FreeType(&library))
        return 1;

    if (FT_New_Memory_Face(library, font, font_size, 0, &face))
        return 2;

    if (FT_Set_Char_Size(face, 0, 32 << 6, 0, 100))
        return 3;

    glyph_index = 1245;

    if ((error = FT_Load_Glyph(face, glyph_index, FT_LOAD_NO_BITMAP)) != 0) {
        printf("error: %s\n", get_ft_error_message(error));
        return 4;
    }

    slot = face->glyph;

    if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
        return 5;

    x = slot->bitmap_left;
    y = img_height - slot->bitmap_top;
    x_max = x + slot->bitmap.width;
    y_max = y + slot->bitmap.rows;

    printf("s: imw=%d imh=%d bml=%d bmt=%d bmw=%d bmh=%d x=%d y=%d xm=%d ym=%d\n",
           img_width, img_height, slot->bitmap_left,
           slot->bitmap_top, slot->bitmap.width, slot->bitmap.rows, x, y, x_max, y_max);

    for (i = x, p = 0; i < x_max; i++, p++) {
        for (j = y, q = 0; j < y_max; j++, q++) {
            if (i < 0 || j < 0 || i >= img_width || j >= img_height)
                continue;

            img[j * img_width * 4 + 4 * i + 3] = slot->bitmap.buffer[q * slot->bitmap.width + p];
        }
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
}
