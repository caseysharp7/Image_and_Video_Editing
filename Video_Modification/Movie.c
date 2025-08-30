/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* Movie.c: source file for basic movie manipulations                */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

int clip(int x){
    if(x < 0)
        return 0;
    else if(x > 255)
        return 255;
    else
        return x;  
}
/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(void)
{
    Movie *movie = (Movie*)malloc(sizeof(Movie));
    assert(movie);

    movie->Frames = CreateImageList();
    assert(movie->Frames);
    return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie)
{
    assert(movie);
    assert(movie->Frames);
    DeleteImageList(movie->Frames);
    free(movie);

}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie)
{
    int Y, U, V;
    int R, G, B;
    int C, D, E;
    YUVImage *yuv;
    assert(movie);
    assert(movie->Frames);
    IENTRY *entry = movie->Frames->First;
    assert(entry);
    assert(entry->image);
    while(entry){
        yuv = (YUVImage*)entry->image;
        assert(yuv);
        Image *T_image = CreateImage(yuv->W, yuv->H);
        assert(T_image);
        for(int y = 0; y < T_image->H; y++){
            for(int x = 0; x < T_image->W; x++){
                Y = GetPixelY(yuv, x, y);
                U = GetPixelU(yuv, x, y);
                V = GetPixelV(yuv, x, y);

                C = Y - 16;
                D = U - 128;
                E = V - 128;

                R = clip((298*C + 409*E + 128) >> 8);
                G = clip((298*C - 100*D - 208*E + 128) >> 8);
                B = clip((298*C + 516*D + 128) >> 8);

                SetPixelR(T_image, x, y, R);
                SetPixelG(T_image, x, y, G);
                SetPixelB(T_image, x, y, B);
            }
        }
        DeleteYUVImage(yuv);
        entry->image = T_image;
        entry = entry->Next;
    }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie)
{
    int Y, U, V;
    int R, G, B;
    Image *rgb;
    assert(movie);
    assert(movie->Frames);
    IENTRY *entry = movie->Frames->First;
    assert(entry);
    assert(entry->image);
    while(entry){
        rgb = (Image*)entry->image;
        assert(rgb);
        YUVImage *T_image = CreateYUVImage(rgb->W, rgb->H);
        assert(T_image);
        for(int y = 0; y < T_image->H; y++){
            for(int x = 0; x < T_image->W; x++){
                R = GetPixelR(rgb, x, y);
                G = GetPixelG(rgb, x, y);
                B = GetPixelB(rgb, x, y);

                Y = clip(((66*R + 129*G + 25*B + 128) >> 8) + 16);
                U = clip(((-38 * R - 74*G + 112*B +128) >> 8) + 128);
                V = clip(((112*R - 94*G - 18*B + 128) >> 8) + 128);

                SetPixelY(T_image, x, y, Y);
                SetPixelU(T_image, x, y, U);
                SetPixelV(T_image, x, y, V);
            }
        }
        DeleteImage(rgb);
        entry->image = T_image;
        entry = entry->Next;
    }
}

/* EOF */
