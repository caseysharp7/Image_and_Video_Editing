// Includes necessary dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Constants.h"
#include "DIPs.h"
#include "FileIO.h"
#include "Advanced.h"
#include "Image.h"
#include "Test.h"
#include <string.h>

void PrintMenu();

// Image *Menu(Image *image);


int main(void) {
    Image *image = CreateImage(512, 288);
    // Runs just autotest if DEBUG is enabled and normal function if DEBUG is not enabled
#ifdef DEBUG
    AutoTest();
#else
    int target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b;
    int block_size;
    int user_input;
    int x, y, W, H;
    int newWidth, newHeight;
    int border_width;
    int direction;
    char color[10];
    char fname[SLEN];
    char sname[SLEN];

    PrintMenu();
    scanf("%d", &user_input);

    while (user_input != 18) {
        if (user_input == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            if (image != NULL) {
                DeleteImage(image);
            }
            image = LoadImage(fname);            
            scanf("%*[^\n]");
            scanf("%*c");
        }
        
        else if (user_input >= 2 && user_input <= 16) {
            if (image == NULL){
                printf("No image to process!\n");
            }
            else {
                switch(user_input) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", sname);
                        SaveImage(sname, image);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        break;
                    case 3:
                        BlackNWhite(image);
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        Negative(image);
                        printf("\"Negative\" operation is done!\n");
                        break;
                    case 5:
                        printf("Enter Red component for the target color: ");
                        scanf("%d", &target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d", &target_g);
                        printf("Enter Blue component for the target color: ");
                        scanf("%d", &target_b);
                        
                        printf("Enter threshold for the color difference: ");
                        scanf("%d", &threshold);
            
                        printf("Enter value for Red component in the target color: ");
                        scanf("%d", &replace_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%d", &replace_g);
                        printf("Enter value for Blue component in the target color: ");
                        scanf("%d", &replace_b);
            
                        ColorFilter(image, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        printf("\"Color Filter\" operation is done!\n");
                        break;
                    case 6:
                        Edge(image);
                        printf("\"Edge\" operation is done!\n");
                        break;
                    case 7:
                        Shuffle(image);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
                    case 8:
                        VFlip(image);
                        printf("\"VFlip\" operation is done!\n");
                        break;
                    case 9:
                        HMirror(image);
                        printf("\"HMirror\" operation is done!\n");
                        break;
                    case 10:
                        printf("Enter border width: ");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s", color);
                        image = AddBorder(image, color, border_width);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        printf("\"Border\" operation is done!\n");
                        break;
                    case 11:
                        printf("Enter block size: ");
                        scanf("%d", &block_size);
                        Pixelate(image, block_size);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        printf("\"Pixelate\" operation is done!\n");
                        break;
                    case 12:
                        image = Shift(image, 160, 40);
                        printf("\"Shift\" operation is done!\n");
                        break;
                    case 13:
                        printf("Please enter the X offset value: ");
                        scanf("%d", &x);
                        printf("Please enter the Y offset value: ");
                        scanf("%d", &y);
                        printf("Please input the crop width: ");
                        scanf("%d", &W);
                        printf("Please input the crop height: ");
                        scanf("%d", &H);
                        image = Crop(image, x, y, W, H);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        printf("\"Crop\" operation is done!\n");
                        break;
                    case 14:
                        printf("Please input the new image width: ");
                        scanf("%d", &newWidth);
                        printf("Please input the new image height: ");
                        scanf("%d", &newHeight);
                        image = Resize(image, newWidth, newHeight);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        printf("\"Resizing the image\" operation is done!\n");
                        break;
                    case 15:
                    {
                        Image *watermark_Image = LoadImage("watermark_template");
                        image = Watermark(image, watermark_Image);
                        DeleteImage(watermark_Image);
                        watermark_Image = NULL;
                        printf("\"Watermark\" operation is done!\n");
                        break;
                    }
                    case 16:
                        printf("Please input the direction of rotation (0:clockwise, 1:counterclockwise) : ");
                        scanf("%d", &direction);
                        image = RotateBy90(image, direction);
                        scanf("%*[^\n]");
                        scanf("%*c");
                        printf("\"RotateBy90\" operation is done!\n");
                        break;
                    default:
                        break;
                }
            }
        }
        else if (user_input == 17) {
            AutoTest();
        }
        else {
            printf("Invalid selection!\n");
        }

        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &user_input);
    }
    printf("You exit the program.\n");
    #endif
    DeleteImage(image);
    return 0;
}

void PrintMenu(void){
    printf("please make your choice: ");
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Make a negative of an image\n");
    printf(" 5: Color filter an image\n");
    printf(" 6: Sketch the edge of an image\n");
    printf(" 7: Shuffle an image\n");
    printf(" 8: Flip an image vertically\n");
    printf(" 9: Mirror an image horizontally\n");
    printf(" 10: Add border to an image\n");
    printf(" 11: Pixelate an image\n");
    printf(" 12: Shift an image\n");
    printf(" 13: Crop an image\n");
    printf(" 14: Resize an image\n");
    printf(" 15: Add Watermark to an image\n");
    printf(" 16: Rotate an image by 90 degree\n");
    printf(" 17: Test all functions\n");
    printf(" 18: Exit\n");
}
