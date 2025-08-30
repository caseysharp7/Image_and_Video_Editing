#include "DIPs.h"

Image *BlackNWhite(Image *image)
{
    assert(image);
    int temp;
    // For loop nest to convert each pixel into the average of its colors
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            // All pixels become average of their colors
            temp = 0;
            temp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
            SetPixelR(image, x, y, temp);
            SetPixelG(image, x, y, temp);
            SetPixelB(image, x, y, temp);
        }
    }
    return image;
}

Image *Negative(Image *image)
{
    assert(image);
    // For loop nest to invert each pixel
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            // Equal to the inverse of their color
            SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
            SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
            SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
        }
    }
    return image;
}

Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
    assert(image);
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            // Check if the pixel is within the range of color
            if(((GetPixelR(image, x, y) >= target_r - threshold) && (GetPixelR(image, x, y) <= target_r + threshold)) &&
               ((GetPixelG(image, x, y) >= target_g - threshold) && (GetPixelG(image, x, y) <= target_g + threshold)) &&
               ((GetPixelB(image, x, y) >= target_b - threshold) && (GetPixelB(image, x, y) <= target_b + threshold))){
                // replace checked pixels with replace colors
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
    }
    return image;
}

Image *Edge(Image *image)
{
    assert(image);
    // Temporary local variables
    int temp = 0;
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));

    // Set the border values to 0
    for(int x = 0; x < ImageWidth(image); x++){
        SetPixelR(image_T, x, 0, 0);
        SetPixelR(image_T, x, ImageHeight(image) - 1, 0);
        SetPixelG(image_T, x, 0, 0);
        SetPixelG(image_T, x, ImageHeight(image) - 1, 0);
        SetPixelB(image_T, x, 0, 0);
        SetPixelB(image_T, x, ImageHeight(image) - 1, 0);
    }
    for(int y = 0; y < ImageHeight(image); y++){
        SetPixelR(image_T, 0, y, 0);
        SetPixelR(image_T, ImageWidth(image) - 1, y, 0);
        SetPixelG(image_T, 0, y, 0);
        SetPixelG(image_T, ImageWidth(image) - 1, y, 0);
        SetPixelB(image_T, 0, y, 0);
        SetPixelB(image_T, ImageWidth(image) - 1, y, 0);
    }

    for (int y = 1; y < ImageHeight(image) - 1; y++) {
        for (int x = 1; x < ImageWidth(image) - 1; x++) {
            // Temp value to hold the internal addition of the pixels
            temp = (-GetPixelR(image, x-1, y-1) - GetPixelR(image, x, y-1) - GetPixelR(image, x+1, y-1) - GetPixelR(image, x-1, y) + 
                    8*GetPixelR(image, x, y) - GetPixelR(image, x+1, y) - GetPixelR(image, x-1, y+1) - GetPixelR(image, x, y+1) - 
                    GetPixelR(image, x+1, y+1));
            // Set to 255 or 0 if values too high or low, or set to addition
            if(temp > 255)
                SetPixelR(image_T, x, y, 255);
            else if(temp < 0)
                SetPixelR(image_T, x, y, 0);
            else
                SetPixelR(image_T, x, y, temp);

            // Repeat for other colors
            temp = (-GetPixelG(image, x-1, y-1) - GetPixelG(image, x, y-1) - GetPixelG(image, x+1, y-1) - GetPixelG(image, x-1, y) + 
                    8*GetPixelG(image, x, y) - GetPixelG(image, x+1, y) - GetPixelG(image, x-1, y+1) - GetPixelG(image, x, y+1) - 
                    GetPixelG(image, x+1, y+1));
            if(temp > 255)
                SetPixelG(image_T, x, y, 255);
            else if(temp < 0)
                SetPixelG(image_T, x, y, 0);
            else
                SetPixelG(image_T, x, y, temp);

            temp = (-GetPixelB(image, x-1, y-1) - GetPixelB(image, x, y-1) - GetPixelB(image, x+1, y-1) - GetPixelB(image, x-1, y) + 
                    8*GetPixelB(image, x, y) - GetPixelB(image, x+1, y) - GetPixelB(image, x-1, y+1) - GetPixelB(image, x, y+1) - 
                    GetPixelB(image, x+1, y+1));
            if(temp > 255)
                SetPixelB(image_T, x, y, 255);
            else if(temp < 0)
                SetPixelB(image_T, x, y, 0);
            else
                SetPixelB(image_T, x, y, temp);
            }
    }

    // Set actual variables to temporary variables
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, GetPixelR(image_T, x, y));
            SetPixelG(image, x, y, GetPixelG(image_T, x, y));
            SetPixelB(image, x, y, GetPixelB(image_T, x, y));
        }
    }
    DeleteImage(image_T);
    return image;
}


Image *Shuffle(Image *image)
{
    assert(image);
    int block_width = ImageWidth(image)/SHUFF_WIDTH_DIV;
    int block_height = ImageHeight(image)/SHUFF_HEIGHT_DIV;
    int i, j, x, y;
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));


    for (i = 0; i < SHUFF_HEIGHT_DIV/2; i++){ // only need to iterate throught half of the blocks
        for (j = 0; j < SHUFF_WIDTH_DIV; j++){
            for (x = 0; x < block_width; x++){
                for (y = 0; y < block_height; y++){
                    SetPixelR(image_T, x, y, GetPixelR(image, x + (j * block_width), y + (i * block_height)));
                    SetPixelG(image_T, x, y, GetPixelG(image, x + (j * block_width), y + (i * block_height)));
                    SetPixelB(image_T, x, y, GetPixelB(image, x + (j * block_width), y + (i * block_height)));

                    SetPixelR(image, x + (j * block_width), y + (i * block_height), GetPixelR(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)));
                    SetPixelG(image, x + (j * block_width), y + (i * block_height), GetPixelG(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)));
                    SetPixelB(image, x + (j * block_width), y + (i * block_height), GetPixelB(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)));

                    SetPixelR(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), GetPixelR(image_T, x, y));
                    SetPixelG(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), GetPixelG(image_T, x, y));
                    SetPixelB(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), GetPixelB(image_T, x, y));
                }
            }
        }
    }
    DeleteImage(image_T);
    return image;
} 

Image *VFlip(Image *image)
{
    assert(image);
    // Temporary arrays
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));

    // Swap height pixels while keeping the width pixels the same to flip the image vertically
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            // flip by height minus one minus i to get opposite height pixel with same width
            SetPixelR(image_T, x, y, GetPixelR(image, x, ImageHeight(image) - 1 - y));
            SetPixelG(image_T, x, y, GetPixelG(image, x, ImageHeight(image) - 1 - y));
            SetPixelB(image_T, x, y, GetPixelB(image, x, ImageHeight(image) - 1 - y));
        }
    }

    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, GetPixelR(image_T, x, y));
            SetPixelG(image, x, y, GetPixelG(image_T, x, y));
            SetPixelB(image, x, y, GetPixelB(image_T, x, y));
        }
    }
    DeleteImage(image_T);
    return image;
}

Image *HMirror(Image *image)
{
    assert(image);
    // The same as the vertical flip but only have to convert half the image to the other half using width minus on minus j
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = (ImageWidth(image)/2); x < ImageWidth(image); x++){
            SetPixelR(image, x, y, GetPixelR(image, ImageWidth(image) - 1 - x, y));
            SetPixelG(image, x, y, GetPixelG(image, ImageWidth(image) - 1 - x, y));
            SetPixelB(image, x, y, GetPixelB(image, ImageWidth(image) - 1 - x, y));
        }
    }
    return image;
}

Image *Pixelate(Image *image, int block_size)
{
    assert(image);
    int x, y, bx, by;
    int sumR, sumG, sumB;
    int count;

    for (y = 0; y < ImageHeight(image) - ImageHeight(image) % block_size; y += block_size) {
        for (x = 0; x < ImageWidth(image) - ImageWidth(image) % block_size; x += block_size) {
            sumR = sumG = sumB = 0; // initialize
            count = 0;

            for (by = 0; by < block_size; by++) {
                for (bx = 0; bx < block_size; bx++) {
                    sumR += GetPixelR(image, x + bx, y + by);
                    sumG += GetPixelG(image, x + bx, y + by);
                    sumB += GetPixelB(image, x + bx, y + by);
                    count++;
                }
            }

            // calculate average RGB value
            sumR = sumR / count;
            sumG = sumG / count;
            sumB = sumB / count;

            // write new values to pixels in the block
            for (by = 0; by < block_size; by++) {
                for (bx = 0; bx < block_size; bx++) {
                    SetPixelR(image, x+bx, y+by, sumR);
                    SetPixelG(image, x+bx, y+by, sumG);
                    SetPixelB(image, x+bx, y+by, sumB);
                }
            }
        }
    }
    return image;
} 

Image *AddBorder(Image *image, char *color, int border_width)
{
    assert(image);
    int border_R, border_G, border_B;

    // Find what color to use
    if (strcmp(color, "black") == 0) {
        border_R = 0; 
        border_G = 0; 
        border_B = 0;
    } else if (strcmp(color, "white") == 0) {
        border_R = 255; 
        border_G = 255; 
        border_B = 255;
    } else if (strcmp(color, "red") == 0) {
        border_R = 255; 
        border_G = 0; 
        border_B = 0;
    } else if (strcmp(color, "green") == 0) {
        border_R = 0; 
        border_G = 255; 
        border_B = 0;
    } else if (strcmp(color, "blue") == 0) {
        border_R = 0; 
        border_G = 0; 
        border_B = 255;
    } else if (strcmp(color, "yellow") == 0) {
        border_R = 255; 
        border_G = 255; 
        border_B = 0;
    } else if (strcmp(color, "cyan") == 0) {
        border_R = 0; 
        border_G = 255; 
        border_B = 255;
    } else if (strcmp(color, "pink") == 0) {
        border_R = 255; 
        border_G = 192; 
        border_B = 203;
    } else if (strcmp(color, "orange") == 0) {
        border_R = 255; 
        border_G = 165; 
        border_B = 0;
    }

    // Set border to the color if within the border distance from the top, bottom, or sides
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            if((x < border_width) || (x > ImageWidth(image) - border_width - 1) || (y < border_width) || (y > ImageHeight(image) - border_width - 1)){
                SetPixelR(image, x, y, border_R);
                SetPixelG(image, x, y, border_G);
                SetPixelB(image, x, y, border_B);
            }
        }
    }
    return image;
}

Image *Shift(Image *image, int shiftX, int shiftY) 
{
    assert(image);
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));
    
    // sets new x and y values for target image
    // This shifts the vertical portion of the image
    for (int y = 0; y < ImageHeight(image); y++) {
        int new_y = y + shiftY;

        while(new_y >= ImageHeight(image)){
            new_y -= ImageHeight(image);
        }
        while(new_y < 0){ 
            new_y += ImageHeight(image);
        }

        for (int x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image_T, x, new_y, GetPixelR(image, x, y));
            SetPixelG(image_T, x, new_y, GetPixelG(image, x, y));
            SetPixelB(image_T, x, new_y, GetPixelB(image, x, y));
        }
    }

    Image *image_TT = CreateImage(ImageWidth(image), ImageHeight(image));
    
    // sets new x and y values for target image
    // This shifts the horizontal portion of the image after the vertical is already done to create the final image
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            int new_x = x + shiftX;

            while(new_x >= ImageWidth(image)){
                new_x -= ImageWidth(image);
            }
            while (new_x < 0){
                new_x += ImageWidth(image);
            }

            SetPixelR(image_TT, new_x, y, GetPixelR(image_T, x, y));
            SetPixelG(image_TT, new_x, y, GetPixelG(image_T, x, y));
            SetPixelB(image_TT, new_x, y, GetPixelB(image_T, x, y));
        }
    }

    DeleteImage(image_T);
    DeleteImage(image);

    return image_TT;
}
