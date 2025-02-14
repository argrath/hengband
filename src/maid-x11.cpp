﻿/* File: maid-x11.c */

/*
 * Copyright (c) 1997 Ben Harrison, and others
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */

#ifdef USE_X11

#include "main-unix/x11-gamma-builder.h"
#include <math.h>

/*
 * This file defines some "XImage" manipulation functions for X11.
 *
 * Original code by Desvignes Sebastien (desvigne@solar12.eerie.fr).
 *
 * BMP format support by Denis Eropkin (denis@dream.homepage.ru).
 *
 * Major fixes and cleanup by Ben Harrison (benh@phial.com).
 *
 * This file is designed to be "included" by "main-x11.c",
 * which will have already "included" several relevant header files.
 */

#ifndef IsModifierKey

/*
 * Keysym macros, used on Keysyms to test for classes of symbols
 * These were stolen from one of the X11 header files
 *
 * Also appears in "main-x11.c".
 */

#define IsKeypadKey(keysym) (((unsigned)(keysym) >= XK_KP_Space) && ((unsigned)(keysym) <= XK_KP_Equal))

#define IsCursorKey(keysym) (((unsigned)(keysym) >= XK_Home) && ((unsigned)(keysym) < XK_Select))

#define IsPFKey(keysym) (((unsigned)(keysym) >= XK_KP_F1) && ((unsigned)(keysym) <= XK_KP_F4))

#define IsFunctionKey(keysym) (((unsigned)(keysym) >= XK_F1) && ((unsigned)(keysym) <= XK_F35))

#define IsMiscFunctionKey(keysym) (((unsigned)(keysym) >= XK_Select) && ((unsigned)(keysym) < XK_KP_Space))

#define IsModifierKey(keysym) (((unsigned)(keysym) >= XK_Shift_L) && ((unsigned)(keysym) <= XK_Hyper_R))

#endif /* IsModifierKey */

/*
 * Checks if the keysym is a special key or a normal key
 * Assume that XK_MISCELLANY keysyms are special
 *
 * Also appears in "main-x11.c".
 */
#define IsSpecialKey(keysym) ((unsigned)(keysym) >= 0xFF00)

static bool gamma_table_ready = true;
static int gamma_val = 0;

/*
 * Hack -- Convert an RGB value to an X11 Pixel, or die.
 */
#ifdef USE_XFT
static XftColor create_pixel(Display *dpy, byte red, byte green, byte blue)
#else
static unsigned long create_pixel(Display *dpy, byte red, byte green, byte blue)
#endif
{
    Colormap cmap = DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy));
    XColor xcolour;
    if (!gamma_table_ready) {
        concptr str = getenv("ANGBAND_X11_GAMMA");
        if (str != nullptr) {
            gamma_val = atoi(str);
        }

        gamma_table_ready = true;

        /* Only need to build the table if gamma exists */
        if (gamma_val) {
            build_gamma_table(gamma_val);
        }
    }

    /* Hack -- Gamma Correction */
    if (gamma_val > 0) {
        red = gamma_table[red];
        green = gamma_table[green];
        blue = gamma_table[blue];
    }

    /* Build the color */

    xcolour.red = red * 255;
    xcolour.green = green * 255;
    xcolour.blue = blue * 255;
    xcolour.flags = DoRed | DoGreen | DoBlue;

#ifdef USE_XFT
    XftColor color;
    XRenderColor xcol;
    xcol.red = xcolour.red;
    xcol.green = xcolour.green;
    xcol.blue = xcolour.blue;
    xcol.alpha = 0xFFFF;
    if (!XftColorAllocValue(dpy, DefaultVisual(dpy, 0), cmap, &xcol, &color)) {
        quit_fmt("Couldn't allocate bitmap color '#%02x%02x%02x'\n", red, green, blue);
    }

    return color;
#else
    /* Attempt to Allocate the Parsed color */
    if (!(XAllocColor(dpy, cmap, &xcolour))) {
        quit_fmt("Couldn't allocate bitmap color '#%02x%02x%02x'\n", red, green, blue);
    }

    return xcolour.pixel;
#endif
}

#ifndef USE_XFT

/*
 * The Win32 "BITMAPFILEHEADER" type.
 */
struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

/*
 * The Win32 "BITMAPINFOHEADER" type.
 */
struct BITMAPINFOHEADER {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompresion;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportand;
};

/*
 * The Win32 "RGBQUAD" type.
 */
struct RGBQUAD {
    unsigned char b, g, r;
    unsigned char filler;
};

/*** Helper functions for system independent file loading. ***/

static byte get_byte(FILE *fff)
{
    /* Get a character, and return it */
    return getc(fff) & 0xFF;
}

static void rd_byte(FILE *fff, byte *ip)
{
    *ip = get_byte(fff);
}

static void rd_u16b(FILE *fff, uint16_t *ip)
{
    (*ip) = get_byte(fff);
    (*ip) |= ((uint16_t)(get_byte(fff)) << 8);
}

static void rd_u32b(FILE *fff, uint32_t *ip)
{
    (*ip) = get_byte(fff);
    (*ip) |= ((uint32_t)(get_byte(fff)) << 8);
    (*ip) |= ((uint32_t)(get_byte(fff)) << 16);
    (*ip) |= ((uint32_t)(get_byte(fff)) << 24);
}

/*
 * Read a Win32 BMP file.
 *
 * This function replaces the old ReadRaw and RemapColors functions.
 *
 * Assumes that the bitmap has a size such that no padding is needed in
 * various places.  Currently only handles bitmaps with 3 to 256 colors.
 */
static XImage *ReadBMP(Display *dpy, char *Name)
{
    Visual *visual = DefaultVisual(dpy, DefaultScreen(dpy));

    int depth = DefaultDepth(dpy, DefaultScreen(dpy));

    FILE *f;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;

    XImage *Res = nullptr;

    char *Data;

    int ncol;

    int total;

    int i, j;

    int x, y;

    unsigned long clr_pixels[256];

    /* Open the BMP file */
    f = fopen(Name, "r");

    /* No such file */
    if (f == nullptr) {
        return nullptr;
    }

    /* Read the "BITMAPFILEHEADER" */
    rd_u16b(f, &(fileheader.bfType));
    rd_u32b(f, &(fileheader.bfSize));
    rd_u16b(f, &(fileheader.bfReserved1));
    rd_u16b(f, &(fileheader.bfReserved2));
    rd_u32b(f, &(fileheader.bfOffBits));

    /* Read the "BITMAPINFOHEADER" */
    rd_u32b(f, &(infoheader.biSize));
    rd_u32b(f, &(infoheader.biWidth));
    rd_u32b(f, &(infoheader.biHeight));
    rd_u16b(f, &(infoheader.biPlanes));
    rd_u16b(f, &(infoheader.biBitCount));
    rd_u32b(f, &(infoheader.biCompresion));
    rd_u32b(f, &(infoheader.biSizeImage));
    rd_u32b(f, &(infoheader.biXPelsPerMeter));
    rd_u32b(f, &(infoheader.biYPelsPerMeter));
    rd_u32b(f, &(infoheader.biClrUsed));
    rd_u32b(f, &(infoheader.biClrImportand));

    /* Verify the header */
    if (feof(f) || (fileheader.bfType != 19778) || (infoheader.biSize != 40)) {
        quit_fmt("Incorrect BMP file format %s", Name);
    }

    /* The two headers above occupy 54 bytes total */
    /* The "bfOffBits" field says where the data starts */
    /* The "biClrUsed" field does not seem to be reliable */
    /* Compute number of colors recorded */
    ncol = (fileheader.bfOffBits - 54) / 4;

    for (i = 0; i < ncol; i++) {
        RGBQUAD clrg;

        /* Read an "RGBQUAD" */
        rd_byte(f, &(clrg.b));
        rd_byte(f, &(clrg.g));
        rd_byte(f, &(clrg.r));
        rd_byte(f, &(clrg.filler));

        /* Analyze the color */
        clr_pixels[i] = create_pixel(dpy, clrg.r, clrg.g, clrg.b);
    }

    /* Determine total bytes needed for image */
    i = 1;
    j = (depth - 1) >> 2;
    while (j >>= 1) {
        i <<= 1;
    }
    total = infoheader.biWidth * infoheader.biHeight * i;

    /* Allocate image memory */
    Data = (char *)malloc(total);

    Res = XCreateImage(dpy, visual, depth, ZPixmap, 0 /*offset*/, Data, infoheader.biWidth, infoheader.biHeight, 8 /*bitmap_pad*/, 0 /*bytes_per_line*/);

    /* Failure */
    if (Res == nullptr) {
        free(Data);
        fclose(f);
        return nullptr;
    }

    for (y = 0; y < static_cast<int>(infoheader.biHeight); y++) {
        int y2 = infoheader.biHeight - y - 1;

        for (x = 0; x < static_cast<int>(infoheader.biWidth); x++) {
            int ch = getc(f);

            /* Verify not at end of file XXX XXX */
            if (feof(f)) {
                quit_fmt("Unexpected end of file in %s", Name);
            }

            if (infoheader.biBitCount == 24) {
                int c2 = getc(f);
                int c3 = getc(f);

                /* Verify not at end of file XXX XXX */
                if (feof(f)) {
                    quit_fmt("Unexpected end of file in %s", Name);
                }

                XPutPixel(Res, x, y2, create_pixel(dpy, ch, c2, c3));
            } else if (infoheader.biBitCount == 8) {
                XPutPixel(Res, x, y2, clr_pixels[ch]);
            } else if (infoheader.biBitCount == 4) {
                XPutPixel(Res, x, y2, clr_pixels[ch / 16]);
                x++;
                XPutPixel(Res, x, y2, clr_pixels[ch % 16]);
            } else {
                /* Technically 1 bit is legal too */
                quit_fmt("Illegal biBitCount %d in %s", infoheader.biBitCount, Name);
            }
        }
    }

    fclose(f);

    return Res;
}

/* ========================================================*/
/* Code for smooth icon rescaling from Uwe Siems, Jan 2000 */
/* ========================================================*/

/*
 * to save ourselves some labour, define a maximum expected icon width here:
 */
#define MAX_ICON_WIDTH 32

/* some static variables for composing and decomposing pixel values into
 * red, green and blue values
 */
static unsigned long redMask, greenMask, blueMask;
static int redShift, greenShift, blueShift;

/*
 * Use smooth rescaling?
 */
static bool smoothRescaling = true;

/*
 * GetScaledRow reads a scan from the given XImage, scales it smoothly
 * and returns the red, green and blue values in arrays.
 * The values in this arrays must be divided by a certain value that is
 * calculated in ScaleIcon.
 * x, y is the position, iw is the input width and ow the output width
 * redScan, greenScan and blueScan must be sufficiently sized
 */
static void GetScaledRow(XImage *Im, int x, int y, int iw, int ow, unsigned long *redScan, unsigned long *greenScan, unsigned long *blueScan)
{
    int xi, si, sifrac, ci, cifrac, addWhole, addFrac;
    unsigned long pix;
    int prevRed, prevGreen, prevBlue, nextRed, nextGreen, nextBlue;
    bool getNextPix;

    if (iw == ow) {
        /* unscaled */
        for (xi = 0; xi < ow; xi++) {
            pix = XGetPixel(Im, x + xi, y);
            redScan[xi] = (pix >> redShift) & redMask;
            greenScan[xi] = (pix >> greenShift) & greenMask;
            blueScan[xi] = (pix >> blueShift) & blueMask;
        }
    } else if (iw < ow) {
        /* scaling by subsampling (grow) */
        iw--;
        ow--;
        /* read first pixel: */
        pix = XGetPixel(Im, x, y);
        nextRed = (pix >> redShift) & redMask;
        nextGreen = (pix >> greenShift) & greenMask;
        nextBlue = (pix >> blueShift) & blueMask;
        prevRed = nextRed;
        prevGreen = nextGreen;
        prevBlue = nextBlue;
        /* si and sifrac give the subsampling position: */
        si = x;
        sifrac = 0;
        /* getNextPix tells us, that we need the next pixel */
        getNextPix = true;

        for (xi = 0; xi <= ow; xi++) {
            if (getNextPix) {
                prevRed = nextRed;
                prevGreen = nextGreen;
                prevBlue = nextBlue;
                if (xi < ow) {
                    /* only get next pixel if in same icon */
                    pix = XGetPixel(Im, si + 1, y);
                    nextRed = (pix >> redShift) & redMask;
                    nextGreen = (pix >> greenShift) & greenMask;
                    nextBlue = (pix >> blueShift) & blueMask;
                }
            }

            /* calculate subsampled color values: */
            /* division by ow occurs in ScaleIcon */
            redScan[xi] = prevRed * (ow - sifrac) + nextRed * sifrac;
            greenScan[xi] = prevGreen * (ow - sifrac) + nextGreen * sifrac;
            blueScan[xi] = prevBlue * (ow - sifrac) + nextBlue * sifrac;

            /* advance sampling position: */
            sifrac += iw;
            if (sifrac >= ow) {
                si++;
                sifrac -= ow;
                getNextPix = true;
            } else {
                getNextPix = true;
            }
        }
    } else {
        /* scaling by averaging (shrink) */
        /* width of an output pixel in input pixels: */
        addWhole = iw / ow;
        addFrac = iw % ow;
        /* start position of the first output pixel: */
        si = x;
        sifrac = 0;
        /* get first input pixel: */
        pix = XGetPixel(Im, x, y);
        nextRed = (pix >> redShift) & redMask;
        nextGreen = (pix >> greenShift) & greenMask;
        nextBlue = (pix >> blueShift) & blueMask;
        for (xi = 0; xi < ow; xi++) {
            /* find endpoint of the current output pixel: */
            ci = si + addWhole;
            cifrac = sifrac + addFrac;
            if (cifrac >= ow) {
                ci++;
                cifrac -= ow;
            }
            /* take fraction of current input pixel (starting segment): */
            redScan[xi] = nextRed * (ow - sifrac);
            greenScan[xi] = nextGreen * (ow - sifrac);
            blueScan[xi] = nextBlue * (ow - sifrac);
            si++;
            /* add values for whole pixels: */
            while (si < ci) {
                pix = XGetPixel(Im, si, y);
                redScan[xi] += ((pix >> redShift) & redMask) * ow;
                greenScan[xi] += ((pix >> greenShift) & greenMask) * ow;
                blueScan[xi] += ((pix >> blueShift) & blueMask) * ow;
                si++;
            }
            /* add fraction of current input pixel (ending segment): */
            if (xi < ow - 1) {
                /* only get next pixel if still in icon: */
                pix = XGetPixel(Im, si, y);
                nextRed = (pix >> redShift) & redMask;
                nextGreen = (pix >> greenShift) & greenMask;
                nextBlue = (pix >> blueShift) & blueMask;
            }
            sifrac = cifrac;
            if (sifrac > 0) {
                redScan[xi] += nextRed * sifrac;
                greenScan[xi] += nextGreen * sifrac;
                blueScan[xi] += nextBlue * sifrac;
            }
        }
    }
}

/*
 * PutRGBScan takes arrays for red, green and blue and writes pixel values
 * according to this values in the XImage-structure. w is the number of
 * pixels to write and div is the value by which all red/green/blue values
 * are divided first.
 */
static void PutRGBScan(XImage *Im, int x, int y, int w, int div, unsigned long *redScan, unsigned long *greenScan, unsigned long *blueScan)
{
    int xi;
    unsigned long pix;
    unsigned long adj = div / 2;
    for (xi = 0; xi < w; xi++) {
        pix = (((((redScan[xi] + adj) / div) & redMask) << redShift) + ((((greenScan[xi] + adj) / div) & greenMask) << greenShift) + ((((blueScan[xi] + adj) / div) & blueMask) << blueShift));
        XPutPixel(Im, x + xi, y, pix);
    }
}

/*
 * ScaleIcon transfers an area from XImage ImIn, locate (x1,y1) to ImOut,
 * locate (x2, y2).
 * Source size is (ix, iy) and destination size is (ox, oy).
 * It does this by getting icon scan line from GetScaledScan and handling
 * them the same way as pixels are handled in GetScaledScan.
 * This even allows icons to be scaled differently in horizontal and
 * vertical directions (eg. shrink horizontal, grow vertical).
 */
static void ScaleIcon(XImage *ImIn, XImage *ImOut, int x1, int y1, int x2, int y2, int ix, int iy, int ox, int oy)
{
    int div;
    int xi, yi, si, sifrac, ci, cifrac, addWhole, addFrac;

    /* buffers for pixel rows: */
    unsigned long prevRed[MAX_ICON_WIDTH];
    unsigned long prevGreen[MAX_ICON_WIDTH];
    unsigned long prevBlue[MAX_ICON_WIDTH];
    unsigned long nextRed[MAX_ICON_WIDTH];
    unsigned long nextGreen[MAX_ICON_WIDTH];
    unsigned long nextBlue[MAX_ICON_WIDTH];
    unsigned long tempRed[MAX_ICON_WIDTH];
    unsigned long tempGreen[MAX_ICON_WIDTH];
    unsigned long tempBlue[MAX_ICON_WIDTH];

    bool getNextRow;

    /* get divider value for the horizontal scaling: */
    if (ix == ox) {
        div = 1;
    } else if (ix < ox) {
        div = ox - 1;
    } else {
        div = ix;
    }

    if (iy == oy) {
        /* no scaling needed vertically: */
        for (yi = 0; yi < oy; yi++) {
            GetScaledRow(ImIn, x1, y1 + yi, ix, ox, tempRed, tempGreen, tempBlue);
            PutRGBScan(ImOut, x2, y2 + yi, ox, div, tempRed, tempGreen, tempBlue);
        }
    } else if (iy < oy) {
        /* scaling by subsampling (grow): */
        iy--;
        oy--;
        div *= oy;
        /* get first row: */
        GetScaledRow(ImIn, x1, y1, ix, ox, nextRed, nextGreen, nextBlue);
        /* si and sifrac give the subsampling position: */
        si = y1;
        sifrac = 0;
        /* getNextRow tells us, that we need the next row */
        getNextRow = true;
        for (yi = 0; yi <= oy; yi++) {
            if (getNextRow) {
                for (xi = 0; xi < ox; xi++) {
                    prevRed[xi] = nextRed[xi];
                    prevGreen[xi] = nextGreen[xi];
                    prevBlue[xi] = nextBlue[xi];
                }
                if (yi < oy) {
                    /* only get next row if in same icon */
                    GetScaledRow(ImIn, x1, si + 1, ix, ox, nextRed, nextGreen, nextBlue);
                }
            }

            /* calculate subsampled color values: */
            /* division by oy occurs in PutRGBScan */
            for (xi = 0; xi < ox; xi++) {
                tempRed[xi] = (prevRed[xi] * (oy - sifrac) + nextRed[xi] * sifrac);
                tempGreen[xi] = (prevGreen[xi] * (oy - sifrac) + nextGreen[xi] * sifrac);
                tempBlue[xi] = (prevBlue[xi] * (oy - sifrac) + nextBlue[xi] * sifrac);
            }

            /* write row to output image: */
            PutRGBScan(ImOut, x2, y2 + yi, ox, div, tempRed, tempGreen, tempBlue);

            /* advance sampling position: */
            sifrac += iy;
            if (sifrac >= oy) {
                si++;
                sifrac -= oy;
                getNextRow = true;
            } else {
                getNextRow = true;
            }
        }
    } else {
        /* scaling by averaging (shrink) */
        div *= iy;
        /* height of a output row in input rows: */
        addWhole = iy / oy;
        addFrac = iy % oy;
        /* start position of the first output row: */
        si = y1;
        sifrac = 0;
        /* get first input row: */
        GetScaledRow(ImIn, x1, y1, ix, ox, nextRed, nextGreen, nextBlue);
        for (yi = 0; yi < oy; yi++) {
            /* find endpoint of the current output row: */
            ci = si + addWhole;
            cifrac = sifrac + addFrac;
            if (cifrac >= oy) {
                ci++;
                cifrac -= oy;
            }
            /* take fraction of current input row (starting segment): */
            for (xi = 0; xi < ox; xi++) {
                tempRed[xi] = nextRed[xi] * (oy - sifrac);
                tempGreen[xi] = nextGreen[xi] * (oy - sifrac);
                tempBlue[xi] = nextBlue[xi] * (oy - sifrac);
            }
            si++;
            /* add values for whole pixels: */
            while (si < ci) {
                GetScaledRow(ImIn, x1, si, ix, ox, nextRed, nextGreen, nextBlue);
                for (xi = 0; xi < ox; xi++) {
                    tempRed[xi] += nextRed[xi] * oy;
                    tempGreen[xi] += nextGreen[xi] * oy;
                    tempBlue[xi] += nextBlue[xi] * oy;
                }
                si++;
            }
            /* add fraction of current input row (ending segment): */
            if (yi < oy - 1) {
                /* only get next row if still in icon: */
                GetScaledRow(ImIn, x1, si, ix, ox, nextRed, nextGreen, nextBlue);
            }
            sifrac = cifrac;
            for (xi = 0; xi < ox; xi++) {
                tempRed[xi] += nextRed[xi] * sifrac;
                tempGreen[xi] += nextGreen[xi] * sifrac;
                tempBlue[xi] += nextBlue[xi] * sifrac;
            }
            /* write row to output image: */
            PutRGBScan(ImOut, x2, y2 + yi, ox, div, tempRed, tempGreen, tempBlue);
        }
    }
}

static XImage *ResizeImageSmooth(Display *dpy, XImage *Im, int ix, int iy, int ox, int oy)
{
    Visual *visual = DefaultVisual(dpy, DefaultScreen(dpy));

    int width1, height1, width2, height2;
    int x1, x2, y1, y2;

    XImage *Tmp;

    char *Data;

    width1 = Im->width;
    height1 = Im->height;

    width2 = ox * width1 / ix;
    height2 = oy * height1 / iy;

    Data = (char *)malloc(width2 * height2 * Im->bits_per_pixel / 8);

    Tmp = XCreateImage(dpy, visual, Im->depth, ZPixmap, 0, Data, width2, height2, 32, 0);

    /* compute values for decomposing pixel into color values: */
    redMask = Im->red_mask;
    redShift = 0;
    while ((redMask & 1) == 0) {
        redShift++;
        redMask >>= 1;
    }
    greenMask = Im->green_mask;
    greenShift = 0;
    while ((greenMask & 1) == 0) {
        greenShift++;
        greenMask >>= 1;
    }
    blueMask = Im->blue_mask;
    blueShift = 0;
    while ((blueMask & 1) == 0) {
        blueShift++;
        blueMask >>= 1;
    }

    /* scale each icon: */
    for (y1 = 0, y2 = 0; (y1 < height1) && (y2 < height2); y1 += iy, y2 += oy) {
        for (x1 = 0, x2 = 0; (x1 < width1) && (x2 < width2); x1 += ix, x2 += ox) {
            ScaleIcon(Im, Tmp, x1, y1, x2, y2, ix, iy, ox, oy);
        }
    }

    return Tmp;
}

/*
 * Resize an image.
 */
static XImage *ResizeImage(Display *dpy, XImage *Im, int ix, int iy, int ox, int oy)
{
    Visual *visual = DefaultVisual(dpy, DefaultScreen(dpy));

    int width1, height1, width2, height2;
    int x1, x2, y1, y2, Tx, Ty;
    int dx1, dx2, dy1, dy2;

    XImage *Tmp;

    char *Data;

    if (smoothRescaling && (ix != ox || iy != oy) && visual->c_class == TrueColor) {
        return ResizeImageSmooth(dpy, Im, ix, iy, ox, oy);
    }

    width1 = Im->width;
    height1 = Im->height;

    width2 = ox * width1 / ix;
    height2 = oy * height1 / iy;

    Data = (char *)malloc(width2 * height2 * Im->bits_per_pixel / 8);

    Tmp = XCreateImage(dpy, visual, Im->depth, ZPixmap, 0, Data, width2, height2, 32, 0);

    if (ix > ox) {
        dx1 = ix;
        dx2 = ox;
    } else {
        dx1 = ox;
        dx2 = ix;
    }

    if (iy > oy) {
        dy1 = iy;
        dy2 = oy;
    } else {
        dy1 = oy;
        dy2 = iy;
    }

    Ty = dy1 / 2;

    for (y1 = 0, y2 = 0; (y1 < height1) && (y2 < height2);) {
        Tx = dx1 / 2;

        for (x1 = 0, x2 = 0; (x1 < width1) && (x2 < width2);) {
            XPutPixel(Tmp, x2, y2, XGetPixel(Im, x1, y1));

            if (ix > ox) {
                ++x1;
            } else {
                ++x2;
            }

            Tx -= dx2;
            if (Tx < 0) {
                Tx += dx1;
                if (ix > ox) {
                    ++x2;
                } else {
                    ++x1;
                }
            }
        }

        if (iy > oy) {
            ++y1;
        } else {
            ++y2;
        }

        Ty -= dy2;
        if (Ty < 0) {
            Ty += dy1;
            if (iy > oy) {
                ++y2;
            } else {
                ++y1;
            }
        }
    }

    return Tmp;
}

#endif /* !USE_XFT */

#endif /* USE_X11 */
