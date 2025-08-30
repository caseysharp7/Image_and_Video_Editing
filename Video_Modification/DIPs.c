/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* DIPs.c: source file for DIP operations                            */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "DIPs.h"
#include "Constants.h"
#include "string.h"
#include "math.h"

/* Black and White */
Image *BlackNWhite(Image *image)
{
        assert(image);
        int x, y, tmp;

        for (y = 0; y < ImageHeight(image); y++) {
                for (x = 0; x < ImageWidth(image); x++) {
                tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
                        SetPixelR(image, x, y, tmp);
                        SetPixelG(image, x, y, tmp);
                SetPixelB(image, x, y, tmp);
                }
        }
        return image;
}

/* Mirror image horizontal  */
Image *HMirror(Image *image) {
        assert(image);
        int x, y;
        for (y = 0; y < ImageHeight(image); y++) {
                for (x = 0; x < ImageWidth(image)/2; x++) {
                        SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
                        SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
                        SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
                }
        }
        return image;
}

/* Edge detection */
Image *Edge(Image *image) {
        assert(image);
        Image *tmpImage = CreateImage(ImageWidth(image), ImageHeight(image));
        assert(tmpImage);

        int x, y, m, n;
        memcpy(tmpImage->R, image->R, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        memcpy(tmpImage->G, image->G, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        memcpy(tmpImage->B, image->B, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        for (y = 1; y < ImageHeight(image) - 1; y++) {
                for (x = 1; x < ImageWidth(image) - 1; x++) {
                        int tmpR = 0;
                        int tmpG = 0;
                        int tmpB = 0;
                        for (m = -1; m <= 1; m++) {
                                for (n = -1; n <= 1; n++) {
                                        tmpR += (GetPixelR(tmpImage, x, y) - GetPixelR(tmpImage, x + n, y + m));
                                        tmpG += (GetPixelG(tmpImage, x, y) - GetPixelG(tmpImage, x + n, y + m));
                                        tmpB += (GetPixelB(tmpImage, x, y) - GetPixelB(tmpImage, x + n, y + m));
                                }
                        }
                        SetPixelR(image, x, y, (tmpR > 255) ? 255 : (tmpR < 0) ? 0 : tmpR);
                        SetPixelG(image, x, y, (tmpG > 255) ? 255 : (tmpG < 0) ? 0 : tmpG);
                        SetPixelB(image, x, y, (tmpB > 255) ? 255 : (tmpB < 0) ? 0 : tmpB);
                }
        }
        for (y = 0; y < ImageHeight(image); y++) {
                x = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
                x = ImageWidth(image) - 1;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }
        for (x = 0; x < ImageWidth(image); x++) {
                y = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
                y = ImageHeight(image) - 1;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }
        DeleteImage(tmpImage);
        tmpImage = NULL;
        return image;
}


Image *Watermark(Image *image, const Image *watermark, unsigned int topLeftX, unsigned int topLeftY)
{
    assert(image);
    assert(watermark);
	
    for(int y = 0; y < ImageHeight(watermark); y++){
        for(int x = 0; x < ImageWidth(watermark); x++){
            int water_x = topLeftX + x;
            int water_y = topLeftY + y;

            if (GetPixelR(watermark, x, y) == 0 &&
                GetPixelG(watermark, x, y) == 0 &&
                GetPixelB(watermark, x, y) == 0) {

                int temp_r = GetPixelR(image, water_x, water_y) * 1.45;
                int temp_g = GetPixelG(image, water_x, water_y) * 1.45;
                int temp_b = GetPixelB(image, water_x, water_y) * 1.45;

                SetPixelR(image, water_x, water_y, (temp_r > 255) ? 255 : temp_r);
                SetPixelG(image, water_x, water_y, (temp_g > 255) ? 255 : temp_g);
                SetPixelB(image, water_x, water_y, (temp_b > 255) ? 255 : temp_b);
            }
        }
    }

    return image;
}

/* Spotlight */
Image *Spotlight(Image *image, int centerX, int centerY, unsigned int radius)
{
    assert(image);

    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageHeight(image); x++) {
            int dx = x - centerX;
            int dy = y - centerY;
            int sub_radius = sqrt(dx * dx + dy * dy);

            if (sub_radius > radius) {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
        }
    }
    return image;
}

/* EOF */
