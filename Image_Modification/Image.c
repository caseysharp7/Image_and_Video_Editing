#include "Image.h"

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x,  unsigned int y)
{
    // Assertions to ensure that the image and R pointer are valid and that x and y are in bounds
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < (*image).W && x >= 0 && y < (*image).H && y >=0);

    // Temporary value to hold the 1D coordinates of x and y
    int temp = x + y * (*image).W;
    // Returning the value at those coordinates
    return (*image).R[temp];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const Image *image, unsigned int x,  unsigned int y)
{
    // Assertions to ensure that the image and G pointer are valid and that x and y are in bounds
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < (*image).W && x >= 0 && y < (*image).H && y >=0);

    // Temporary value to hold the 1D coordinates of x and y
    int temp = x + y * (*image).W;
    // Returning the value at those coordinates
    return (*image).G[temp];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const Image *image, unsigned int x,  unsigned int y)
{
    // Assertions to ensure that the image and B pointer are valid and that x and y are in bounds
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < (*image).W && x >= 0 && y < (*image).H && y >=0);

    // Temporary value to hold the 1D coordinates of x and y
    int temp = x + y * (*image).W;
    // Returning the value at those coordinates
    return (*image).B[temp];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(Image *image, unsigned int x,  unsigned int y, unsigned char r)
{
    // Assertions to ensure that the image and R pointer are valid and that x and y are in bounds
    assert(image != NULL);
    assert((*image).R != NULL);
    assert(x < (*image).W && x >= 0 && y < (*image).H && y >=0);

    // Temporary value to hold the 1D coordinates of x and y
    int temp = x + y * (*image).W;
    // Setting the value at those coordinates
    (*image).R[temp] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(Image *image, unsigned int x,  unsigned int y, unsigned char g)
{
    // Assertions to ensure that the image and G pointer are valid and that x and y are in bounds
    assert(image != NULL);
    assert((*image).G != NULL);
    assert(x < (*image).W && x >= 0 && y < (*image).H && y >=0);

    // Temporary value to hold the 1D coordinates of x and y
    int temp = x + y * (*image).W;
    // Setting the value at those coordinates
    (*image).G[temp] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(Image *image, unsigned int x,  unsigned int y, unsigned char b)
{
    // Assertions to ensure that the image and B pointer are valid and that x and y are in bounds
    assert(image != NULL);
    assert((*image).B != NULL);
    assert(x < (*image).W && x >= 0 && y < (*image).H && y >=0);

    // Temporary value to hold the 1D coordinates of x and y
    int temp = x + y * (*image).W;
    // Setting the value at those coordinates
    (*image).B[temp] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
Image *CreateImage(unsigned int Width, unsigned int Height)
{
    // Allocation of struct pointer
    Image *image = (Image *)malloc(sizeof(Image));
    // Check memory allocation
    if(!image){
        fprintf(stderr, "Failed to allocate memory for Image struct\n");
        return NULL;
    }

    (*image).W = Width;
    (*image).H = Height;

    // Allocation of color pointers
    (*image).R = (unsigned char *)malloc(Width*Height * sizeof(unsigned char));
    (*image).G = (unsigned char *)malloc(Width*Height * sizeof(unsigned char));
    (*image).B = (unsigned char *)malloc(Width*Height * sizeof(unsigned char));

    // Freeing all pointers if any are not valid
    if(!(*image).R || !(*image).G || !(*image).B){
        fprintf(stderr, "Failed to allocate memory for color channels\n");
        free((*image).R);
        free((*image).G);
        free((*image).B);
        free(image);
        return NULL;
    }

    return image;
}

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image)
{
    // Free all memory if image exists and is valid
    if(image){
        free((*image).R);
        free((*image).G);
        free((*image).B);
        free(image);
    }
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image)
{
    assert(image != NULL);
    return((*image).W);
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image)
{
    assert(image != NULL);
    return((*image).H);
}