#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


Image *FishEye(Image *image, double distortion_factor, double k, double scaling_factor);


Image *Rotate(Image *image, double Angle, double ScaleFactor,  int CenterX, int CenterY);


Image *Posterize(Image *image, int rbits, int gbits, int bbits);


Image *MotionBlur(Image *image, unsigned char BlurAmount);

/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H);

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight);

/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image);

/* Rotate by 90 */
Image *RotateBy90(Image *image, int rotateDirection);
#endif /* ADVANCED_H_INCLUDED_ */
