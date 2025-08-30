#include "Advanced.h" // Include header file

Image *FishEye(Image *image, double distortion_factor, double k, double scaling_factor)
{
    assert(image);
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));

    // Establishes the centers of the image and other variable declarations
    double center_x = (ImageWidth(image)/2);
    double center_y = (ImageHeight(image)/2);
    double dx, dy, radius, distortion, theta, new_radius;
    int x_src, y_src;

    // Nested for loop to iterate through arrays
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            // changes in y and x in relation to the center of the image
            dx = ((x - center_x) / center_x);
            dy = ((y - center_y) / center_y);

            // Finds the distance from the center of the image
            radius = sqrt((dx * dx) + (dy * dy));
            // Calculations for fisheye affect
            distortion = (1 + (k * (radius * radius)));
            theta = atan2(dy, dx);
            new_radius = ((radius*distortion_factor)/(distortion*scaling_factor));
            x_src = center_x + (new_radius*cos(theta)*center_x);
            y_src = center_y + (new_radius*sin(theta)*center_y);

            // If pixels fall into fisheye affect then place them in target arrays and if not just set to 0
            if((x_src >= 0) && (x_src < ImageWidth(image)) && (y_src >= 0) && (y_src < ImageHeight(image))){
                SetPixelR(image_T, x, y, GetPixelR(image, x_src, y_src));
                SetPixelG(image_T, x, y, GetPixelG(image, x_src, y_src));
                SetPixelB(image_T, x, y, GetPixelB(image, x_src, y_src));                    
            } else{
                SetPixelR(image_T, x, y, 0);
                SetPixelG(image_T, x, y, 0);
                SetPixelB(image_T, x, y, 0);
            }
        }
    }

    // Copies temporary arrays back into original arrays
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, GetPixelR(image_T, x, y));
            SetPixelG(image, x, y, GetPixelG(image_T, x, y));
            SetPixelB(image, x, y, GetPixelB(image_T, x, y));
        }
    }
    #ifndef DEBUG
    printf("\"FishEye\" operation is done!\n");
    #endif
    DeleteImage(image_T);
    return image;
} 

Image *Posterize(Image *image, int rbits, int gbits, int bbits)
{
    assert(image);
    // The ands are to set all bits at and past the rbit to zero and keep all bits that are more significant
    // The ors are to set all bits past the rbit to 1
    // Together they set the rbit to 0, keep all more significant bits the same and set all less significant bits to 1
    unsigned int r_and = pow(2, 8) - pow(2, rbits);
    unsigned int r_or = pow(2, (rbits - 1)) - 1;
    unsigned int g_and = pow(2, 8) - pow(2, gbits);
    unsigned int g_or = pow(2, (gbits - 1)) - 1;
    unsigned int b_and = pow(2, 8) - pow(2, bbits);
    unsigned int b_or = pow(2, (bbits - 1)) - 1;
    // For loop nest to perform operations on each pixel
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            SetPixelR(image, x, y, GetPixelR(image, x, y) & r_and);
            SetPixelR(image, x, y, GetPixelR(image, x, y) | r_or);
            SetPixelG(image, x, y, GetPixelG(image, x, y) & g_and);
            SetPixelG(image, x, y, GetPixelG(image, x, y) | g_or);
            SetPixelB(image, x, y, GetPixelB(image, x, y) & b_and);
            SetPixelB(image, x, y, GetPixelB(image, x, y) | b_or);
        }
    }
    // Only print if DEBUG is not enabled
    #ifndef DEBUG
    printf("\"Posterize\" operation is done!\n");
    #endif
    return image;
}

Image *Rotate(Image *image, double Angle, double ScaleFactor,  int CenterX, int CenterY)
{
    assert(image);
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));

    // Convert angle to radians
    double rad_Angle = Angle * (3.14159265359 / 180.0);
    int new_x, new_y;
    // Variable declaration for trigonometric calculations
    double cosine = cos(rad_Angle) / ScaleFactor;
    double sine = sin(rad_Angle) / ScaleFactor;

    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            // Calculations done according to matrix formula
            new_x = ((cosine * (x - CenterX)) + (sine * (y - CenterY)) + CenterX);
            new_y = ((-sine * (x - CenterX)) + (cosine * (y - CenterY)) + CenterY);

            // Target matrix gets values only if within bounds of the image
            if((new_x < ImageWidth(image)) && (new_x >= 0) && (new_y < ImageHeight(image)) && (new_y >= 0)){
                SetPixelR(image_T, x, y, GetPixelR(image, new_x, new_y));
                SetPixelG(image_T, x, y, GetPixelG(image, new_x, new_y));
                SetPixelB(image_T, x, y, GetPixelB(image, new_x, new_y)); 
            } else{
                SetPixelR(image_T, x, y, 0);
                SetPixelG(image_T, x, y, 0);
                SetPixelB(image_T, x, y, 0);
            }
        }
    }

    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, GetPixelR(image_T, x, y));
            SetPixelG(image, x, y, GetPixelG(image_T, x, y));
            SetPixelB(image, x, y, GetPixelB(image_T, x, y));
        }
    }
    #ifndef DEBUG
    printf("\"Rotate\" operation is done!\n");
    #endif
    DeleteImage(image_T);
    return image;
}

Image *MotionBlur(Image *image, unsigned char BlurAmount)
{
    assert(image);
    Image *image_T = CreateImage(ImageWidth(image), ImageHeight(image));
    // Establish needed variables
    double sum_r, sum_g, sum_b;
    int count = 0;
    double average_r, average_g, average_b;

    // Nested for loop for array iteration
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            // Reset all variables back to zero for each iteration
            sum_r = 0;
            sum_g = 0;
            sum_b = 0;
            average_r = 0;
            average_g = 0;
            average_b = 0;
            count = 0;
            // for if not within BlurAmount of edge
            if(x < (ImageWidth(image) - BlurAmount)){
                for(int i = x + 1; i <= x + BlurAmount; i++){
                    sum_r += GetPixelR(image, i, y);
                    sum_g += GetPixelG(image, i, y);
                    sum_b += GetPixelB(image, i, y);
                }
                // Averages out the BlurAmount of pixels past the target pixel
                average_r = sum_r / BlurAmount;
                average_g = sum_g / BlurAmount;
                average_b = sum_b / BlurAmount;

                // Pixel is weighted half and the average is weighted half
                SetPixelR(image_T, x, y, (unsigned char)(((double)GetPixelR(image, x, y) / 2.0) + (average_r / 2.0)));
                SetPixelG(image_T, x, y, (unsigned char)(((double)GetPixelG(image, x, y) / 2.0) + (average_g / 2.0)));
                SetPixelB(image_T, x, y, (unsigned char)(((double)GetPixelB(image, x, y) / 2.0) + (average_b / 2.0)));
            } else if(x != ImageWidth(image) - 1){ // For if within BlurAmount of edge
                for(int i = x + 1; i < ImageWidth(image); i++){
                    sum_r += GetPixelR(image, i, y);
                    sum_g += GetPixelG(image, i, y);
                    sum_b += GetPixelB(image, i, y);
                    count++;
                }
                // Averages the amount of pixels past the target pixel until the edge
                average_r = sum_r / count;
                average_g = sum_g / count;
                average_b = sum_b / count;
                // Same as previous
                SetPixelR(image_T, x, y, (unsigned char)(((double)GetPixelR(image, x, y) / 2.0) + (average_r / 2.0)));
                SetPixelG(image_T, x, y, (unsigned char)(((double)GetPixelG(image, x, y) / 2.0) + (average_g / 2.0)));
                SetPixelB(image_T, x, y, (unsigned char)(((double)GetPixelB(image, x, y) / 2.0) + (average_b / 2.0)));
            } else{
                SetPixelR(image_T, x, y, GetPixelR(image, x, y));
                SetPixelG(image_T, x, y, GetPixelG(image, x, y));
                SetPixelB(image_T, x, y, GetPixelB(image, x, y));
            }
        }
    }

    // Copies target array back to original
    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, GetPixelR(image_T, x, y));
            SetPixelG(image, x, y, GetPixelG(image_T, x, y));
            SetPixelB(image, x, y, GetPixelB(image_T, x, y));
        }
    }
    #ifndef DEBUG
    printf("\"motion blur\" operation is done!\n");
    #endif
    DeleteImage(image_T);
    return image;
}

Image *Crop(Image *image, int x, int y, int W, int H)
{
    assert(image);

    int x_T = 0;
    int y_T = 0;
    // Correcting the bounds
    if (x < 0) 
        x = 0;
    if (y < 0) 
        y = 0;
    if((x + W) > ImageWidth(image))
        W = ImageWidth(image) - x;
    if((y + H) > ImageHeight(image))
        H = ImageHeight(image) - y;
    
    Image *image_T = CreateImage(W, H);
    
    // This for loop nest iterates from the starting point to the x and y dimensions to create the crop
    for (int dy = y; dy < H + y; dy++) {
        for (int dx = x; dx < W + x; dx++) {
            SetPixelR(image_T, x_T, y_T, GetPixelR(image, dx, dy));
            SetPixelG(image_T, x_T, y_T, GetPixelG(image, dx, dy));
            SetPixelB(image_T, x_T, y_T, GetPixelB(image, dx, dy));
            // x_T and y_T are for the new image as they start from 0
            x_T++;
        }
        x_T = 0;
        y_T++;
    }

    DeleteImage(image);
    return image_T;
}

Image *Resize(Image *image, int newWidth, int newHeight)
{
    assert(image);
    int new_x, new_y;
    // Variable declaration for calculations
    float scale_x = (float)newWidth / ImageWidth(image);
    float scale_y = (float)newHeight / ImageHeight(image);

    Image *image_T = CreateImage(newWidth, newHeight);

    for(double y = 0; y < newHeight; y++){
        for(double x = 0; x < newWidth; x++){

            // Calculations done according to matrix formula
            new_x = (int)(x * 1/scale_x);
            new_y = (int)(y * 1/scale_y);

            // Assures that new values are within range
            if (new_x >= ImageWidth(image)) 
                new_x = ImageWidth(image) - 1;
            if (new_y >= ImageHeight(image)) 
                new_y = ImageHeight(image) - 1;

            // Sets values to target structure
            SetPixelR(image_T, x, y, GetPixelR(image, new_x, new_y));
            SetPixelG(image_T, x, y, GetPixelG(image, new_x, new_y));
            SetPixelB(image_T, x, y, GetPixelB(image, new_x, new_y));
        }
    }

    DeleteImage(image);
    return image_T;
} 

Image *Watermark(Image *image, const Image *watermark_image)
{
    assert(image);
    int water_x, water_y;
    int temp_r, temp_g, temp_b;
    for(int y = 0; y < ImageHeight(image); y++){
        for(int x = 0; x < ImageWidth(image); x++){
            // Modulo allows watermark image to wrap around image
            water_x = x % ImageWidth(watermark_image);
            water_y = y % ImageHeight(watermark_image);

            // Checks for where watermark_image is black and then sets image accordingly
            if(GetPixelR(watermark_image, water_x, water_y) == 0 &&
               GetPixelG(watermark_image, water_x, water_y) == 0 &&
               GetPixelB(watermark_image, water_x, water_y) == 0){
                temp_r = GetPixelR(image, x, y) * 1.45;
                temp_g = GetPixelG(image, x, y) * 1.45;
                temp_b = GetPixelB(image, x, y) * 1.45;
                // Saturated overflow handling
                if(temp_r > 255)
                    temp_r = 255;
                if(temp_g > 255)
                    temp_g = 255;
                if(temp_b > 255)
                    temp_b = 255;
                
                SetPixelR(image, x, y, temp_r);
                SetPixelG(image, x, y, temp_g);
                SetPixelB(image, x, y, temp_b);
            }
        }
    }
    return image;
}

Image *RotateBy90(Image *image, int direction) {
    assert(image);

    // Makes target image vertical
    Image *image_T = CreateImage(ImageHeight(image), ImageWidth(image));

    for (int y = 0; y < ImageHeight(image); y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            // Rotates the image by 90 degrees depending on direction
            if (direction == 0) {
                SetPixelR(image_T, ImageHeight(image) - y - 1, x, GetPixelR(image, x, y));
                SetPixelG(image_T, ImageHeight(image) - y - 1, x, GetPixelG(image, x, y));
                SetPixelB(image_T, ImageHeight(image) - y - 1, x, GetPixelB(image, x, y));
            } else if(direction == 1) {
                SetPixelR(image_T, y, ImageWidth(image) - x - 1, GetPixelR(image, x, y));
                SetPixelG(image_T, y, ImageWidth(image) - x - 1, GetPixelG(image, x, y));
                SetPixelB(image_T, y, ImageWidth(image) - x - 1, GetPixelB(image, x, y));
            }
        }
    }

    DeleteImage(image);
    return image_T;
}
