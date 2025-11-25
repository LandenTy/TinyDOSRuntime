/* stdimglib.h
   Simple 8-bit PCX loader (header-only)
   Designed for DOS / OpenWatcom / 16-bit C89 environments.
*/

#ifndef STDIMGLIB_H
#define STDIMGLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------
   PCX file header (always 128 bytes)
------------------------------------------------------------- */
#pragma pack(1)
typedef struct {
    unsigned char  Manufacturer;
    unsigned char  Version;
    unsigned char  Encoding;
    unsigned char  BitsPerPixel;
    unsigned short Xmin;
    unsigned short Ymin;
    unsigned short Xmax;
    unsigned short Ymax;
    unsigned short Hres;
    unsigned short Vres;
    unsigned char  ColorMap[48];
    unsigned char  Reserved;
    unsigned char  ColorPlanes;
    unsigned short BytesPerLine;
    unsigned short PaletteType;
    unsigned short HScreenSize;
    unsigned short VScreenSize;
    unsigned char  Filler[54];
} PCXHeader;
#pragma pack()

/* -------------------------------------------------------------
   Unified image object
------------------------------------------------------------- */
typedef struct Image {
    unsigned char *pixels;       /* allocated pixel buffer */
    unsigned char palette[768];  /* 256 * 3 RGB bytes */
    int width;
    int height;
} Image;

/* -------------------------------------------------------------
   load_pcx_8bit
   Loads an 8-bit PCX file and returns an Image*.

   RETURNS:
       Image* = success
       NULL   = failure

   The returned Image must be freed using free_image().
------------------------------------------------------------- */
static Image *load_pcx_8bit(const char *path)
{
    FILE        *f;
    PCXHeader    hdr;
    Image       *img = NULL;
    unsigned char *scanbuf = NULL;
    int          y;
    long         endpos;

    if (!path)
        return NULL;

    f = fopen(path, "rb");
    if (!f)
        return NULL;

    /* Read header */
    if (fread(&hdr, 1, sizeof(PCXHeader), f) != sizeof(PCXHeader)) {
        fclose(f);
        return NULL;
    }

    /* Validate PCX format */
    if (hdr.Manufacturer != 0x0A ||
        hdr.Encoding     != 1    ||
        hdr.BitsPerPixel != 8    ||
        hdr.ColorPlanes  != 1)
    {
        fclose(f);
        return NULL;
    }

    /* Allocate Image struct */
    img = (Image *)malloc(sizeof(Image));
    if (!img) {
        fclose(f);
        return NULL;
    }

    img->width  = hdr.Xmax - hdr.Xmin + 1;
    img->height = hdr.Ymax - hdr.Ymin + 1;

    if (img->width  <= 0 || img->height <= 0 ||
        img->width  > 640 || img->height > 480)
    {
        free(img);
        fclose(f);
        return NULL;
    }

    /* Allocate pixel buffer */
    img->pixels = (unsigned char *)malloc(img->width * img->height);
    if (!img->pixels) {
        free(img);
        fclose(f);
        return NULL;
    }

    /* Allocate scanline buffer */
    scanbuf = (unsigned char *)malloc(hdr.BytesPerLine);
    if (!scanbuf) {
        free(img->pixels);
        free(img);
        fclose(f);
        return NULL;
    }

    /* ---------------------------------------------------------
       Decode RLE PCX scanlines
    --------------------------------------------------------- */
    for (y = 0; y < img->height; ++y) {
        int x = 0;

        while (x < hdr.BytesPerLine) {
            int c = fgetc(f);

            if (c == EOF)
                goto fail;

            if ((c & 0xC0) == 0xC0) {
                int count = c & 0x3F;
                int val   = fgetc(f);

                if (val == EOF)
                    goto fail;

                while (count-- && x < hdr.BytesPerLine)
                    scanbuf[x++] = (unsigned char)val;
            } else {
                scanbuf[x++] = (unsigned char)c;
            }
        }

        memcpy(img->pixels + y * img->width, scanbuf, img->width);
    }

    /* ---------------------------------------------------------
       Read palette from last 769 bytes (0x0C + 768 palette bytes)
    --------------------------------------------------------- */
    fseek(f, 0, SEEK_END);
    endpos = ftell(f);

    if (endpos < 769L)
        goto fail;

    fseek(f, endpos - 769L, SEEK_SET);

    if (fgetc(f) != 0x0C)
        goto fail;

    if (fread(img->palette, 1, 768, f) != 768)
        goto fail;

    fclose(f);
    free(scanbuf);
    return img;

fail:
    fclose(f);

    if (scanbuf)
        free(scanbuf);

    if (img) {
        if (img->pixels)
            free(img->pixels);
        free(img);
    }

    return NULL;
}

/* -------------------------------------------------------------
   free_image
   Frees an Image* created by load_pcx_8bit
------------------------------------------------------------- */
static void free_image(Image *img)
{
    if (!img)
        return;

    if (img->pixels)
        free(img->pixels);

    free(img);
}

#endif /* STDIMGLIB_H */
