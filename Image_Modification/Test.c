
#include <stdio.h>
#include "Test.h"
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

int AutoTest(void) {
    int result;
    const char fname[SLEN] = "EngPlaza";
    const char watermarkImgName[SLEN] = "watermark_template";
    char color[SLEN] = "pink";

    Image *image = NULL;
    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 11); return 11;}
    image = BlackNWhite(image);
    if (! image) {printf("Autotest failed, error code %d.\n", 12); return 12;}
    result = SaveImage("bw", image);
    if (result) return result;
#ifdef DEBUG
    printf("Black and White tested!\n\n");
#endif
        DeleteImage(image);
        image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 13); return 13;}
    image = Negative(image);
    if (! image) {printf("Autotest failed, error code %d.\n", 14); return 14;}
    result = SaveImage("negative", image);
    if (result) return result;
#ifdef DEBUG
    printf("Negative tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 15); return 15;}
    image = ColorFilter(image, CF_TARGET_R, CF_TARGET_G, CF_TARGET_B, CF_THRESHOLD, CF_REPLACED_R, CF_REPLACED_G, CF_REPLACED_B);
    if (! image) {printf("Autotest failed, error code %d.\n", 16); return 16;}
    result = SaveImage("colorfilter", image);
    if (result) return result;
#ifdef DEBUG
    printf("Color Filter tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 17); return 17;}
    image = Edge(image);
    if (! image) {printf("Autotest failed, error code %d.\n", 18); return 18;}
    result = SaveImage("edge", image);
    if (result) return result;
#ifdef DEBUG
    printf("Edge Detection tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 19); return 19;}
    image = Shuffle(image);
    if (! image) {printf("Autotest failed, error code %d.\n", 20); return 20;}
    result = SaveImage("shuffle", image);
    if (result) return result;
#ifdef DEBUG
    printf("Shuffle tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 21); return 21;}
    image = VFlip(image);
    if (! image) {printf("Autotest failed, error code %d.\n", 22); return 22;}
    result = SaveImage("vflip", image);
    if (result) return result;
#ifdef DEBUG
    printf("VFlip tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 23); return 23;}
    image = HMirror(image);
    if (! image) {printf("Autotest failed, error code %d.\n", 24); return 24;}
    result = SaveImage("hmirror", image);
    if (result) return result;
#ifdef DEBUG
    printf("HMirror tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 25); return 25;}
    image = AddBorder(image, color, BORDER_WIDTH);
    if (! image) {printf("Autotest failed, error code %d.\n", 26); return 26;}
    result = SaveImage("border", image);
    if (result) return result;
#ifdef DEBUG
    printf("Add Border tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 27); return 27;}
    image = Pixelate(image, BLOCK_SIZE);
    if (! image) {printf("Autotest failed, error code %d.\n", 28); return 28;}
    result = SaveImage("pixelate", image);
    if (result) return result;
#ifdef DEBUG
    printf("Pixelate tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 29); return 29;}
    image = Shift(image, 160, 40);
    if (! image) {printf("Autotest failed, error code %d.\n", 30); return 30;}
    result = SaveImage("shift", image);
    if (result) return result;
#ifdef DEBUG
    printf("Shift tested!\n\n");
#endif
    /*
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 31;
    image = HistogramEqualization(image);
    if (! image) return 32;
    result = SaveImage("histE", image);
    if (result) return result;
#ifdef DEBUG
    printf("Histogram equalization tested!\n\n");
#endif */ 

    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 35); return 35;}
    image = Crop(image, CROP_X, CROP_Y, CROP_WIDTH, CROP_HEIGHT);
    if (! image) {printf("Autotest failed, error code %d.\n", 36); return 36;}
    result = SaveImage("crop", image);
    if (result) return result;
#ifdef DEBUG
    printf("Crop tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 37); return 37;}
    image = Resize(image, SMALL_RESIZE_WIDTH, SMALL_RESIZE_HEIGHT);
    if (! image) {printf("Autotest failed, error code %d.\n", 38); return 38;}
    result = SaveImage("smallresize", image);
    if (result) return result;
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 39); return 39;}
    image = Resize(image, BIG_RESIZE_WIDTH, BIG_RESIZE_HEIGHT);
    if (! image) {printf("Autotest failed, error code %d.\n", 40); return 40;}
    result = SaveImage("bigresize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Resize tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 41); return 41;}
    Image *watermark_Image = LoadImage(watermarkImgName);
    if (! watermark_Image) {printf("Autotest failed, error code %d.\n", 42); return 42;}
    image = Watermark(image, watermark_Image);
    DeleteImage(watermark_Image);
    watermark_Image = NULL;
    if (! image) {printf("Autotest failed, error code %d.\n", 43); return 43;}
    result = SaveImage("watermark", image);
    if (result) return result;
#ifdef DEBUG
    printf("Watermark tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) {printf("Autotest failed, error code %d.\n", 44); return 44;}
    image = RotateBy90(image, ROTATEDIRECTION);
    if (! image) {printf("Autotest failed, error code %d.\n", 45); return 45;}
    result = SaveImage("rotateby90", image);
    if (result) return result;
#ifdef DEBUG
    printf("RotateBy90 tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    return 0;
} 
