/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* MovieLab.c: source file for the main function                     */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
    unsigned int width, unsigned height);

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
    unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
        int x = 0;
        char *fin = NULL;
        char *fout = NULL;
		int frameNum = -1;
		int bw = 0;
		int hmirror = 0;
		int edge = 0;
		int crop = 0;
		unsigned int start, end;
		int fast = 0;
		int factor;
		int reverse = 0;
		int watermark = 0;
		char *wm = NULL;
		int spotlight = 0;


        unsigned int width = 512;
        unsigned int height = 288;

        /* the while loop to check options in the command line */
        while (x < argc) {
                /* the input file name */
                if (strcmp(argv[x], "-i") == 0) {
                        if (x < argc - 1) {
                                fin = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the input file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the output file name */
                if (strcmp(argv[x], "-o") == 0) {
                        if (x < argc - 1) {
                                fout = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the output file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the help option */
                if (strcmp(argv[x], "-h") == 0) {
                        PrintUsage();
                        return 0;
                } /*fi*/

                /* to be implemented */

                if (strcmp(argv[x], "-f") == 0){
                    if(x < argc - 1){
						frameNum = atoi(argv[x+1]);
						if(frameNum <= 0){
							printf("Invalid frame number\n");
							return 5;
						}
					}
					x += 2;
					continue;
                }

				if (strcmp(argv[x], "-s") == 0) {
					if (x < argc - 1 && sscanf(argv[x + 1], "%ux%u", &width, &height) == 2) {
						x += 2;
						continue;
					} else {
						printf("Invalid resolution format\n");
						return 5;
					}
				}

				if (strcmp(argv[x], "-bw") == 0) {
					bw = 1;
					x++;
					continue;
				}

				if (strcmp(argv[x], "-hmirror") == 0) {
					hmirror = 1;
					x++;
					continue;
				}

				if (strcmp(argv[x], "-edge") == 0) {
					edge = 1;
					x++;
					continue;
				}

				if (strcmp(argv[x], "-crop") == 0) {
					if (x < argc - 1 && sscanf(argv[x + 1], "%u-%u", &start, &end) == 2) {
						crop = 1;
					} else {
						printf("Invalid crop format\n");
						return 5;
					}
					x += 2;
					continue;
				}

				if (strcmp(argv[x], "-fast") == 0) {
					if (x < argc - 1) {
						fast = 1;
						factor = atoi(argv[x + 1]);
					}
					else {
						printf("Invalid fast format\n");
						return 5;
					}
					x += 2;
					continue;
				}

				if (strcmp(argv[x], "-reverse") == 0) {
					reverse = 1;
					x++;
					continue;
				}

				if (strcmp(argv[x], "-watermark") == 0) {
					if (x < argc - 1) {
						watermark = 1;
						wm = argv[x + 1];
					}
					else {
						printf("Missing argument for the watermark name!\n");
						return 5;
					}
					x += 2;
					continue;
				}

				if (strcmp(argv[x], "-spotlight") == 0) {
					spotlight = 1;
					x++;
					continue;
				}



                x++;
        } /*elihw*/

        if (fin == NULL) {
                printf("Missing argument for the input file name!\n");
                PrintUsage();
                return 5;
        }

        if (fout == NULL) {
                printf("Missing argument for the output file name!\n");
                PrintUsage();
                return 5;
        }

		if (frameNum == -1) {
			printf("Missing argument for the frame number!\n");
			PrintUsage();
			return 5;
		}

                /* to be implemented */

		Movie *movie = LoadMovie(fin, frameNum, width, height);
		assert(movie);
		
		if(bw){
			YUV2RGBMovie(movie);
			assert(movie);
			IENTRY *entry;
			entry = movie->Frames->First;
			assert(entry);
			while(entry){
				assert(entry);
				entry->image = BlackNWhite(entry->image);
				entry = entry->Next;
			}
			RGB2YUVMovie(movie);
			printf("Operation Black and White is done!\n");
		}

		if(hmirror){
			YUV2RGBMovie(movie);
			assert(movie);
			IENTRY *entry;
			entry = movie->Frames->First;
			assert(entry);
			while(entry){
				assert(entry);
				entry->image = HMirror(entry->image);
				entry = entry->Next;
			}
			RGB2YUVMovie(movie);
			printf("Operation HMirror is done!\n");
		}

		if(edge){
			YUV2RGBMovie(movie);
			assert(movie);
			IENTRY *entry;
			entry = movie->Frames->First;
			assert(entry);
			while(entry){
				assert(entry);
				entry->image = Edge(entry->image);
				entry = entry->Next;
			}
			RGB2YUVMovie(movie);
			printf("Operation Edge is done!\n");
		}

		if(crop){
			CropImageList(movie->Frames, start, end);
			printf("Operation Crop is done! New number of frames is %d.\n", movie->Frames->Length);
		}

		if(fast){
			FastImageList(movie->Frames, factor);
			printf("Operation Fast Forward is done! New number of frames is %d.\n", movie->Frames->Length);
		}

		if(reverse){
			ReverseImageList(movie->Frames);
			printf("Operation Reverse is done!\n");
		}

		if (watermark) {
			YUV2RGBMovie(movie);
			assert(movie);
			srand(time(NULL));
			Image *water_image = LoadImage(wm);
			assert(water_image);
			
			int water_w = ImageWidth(water_image);
			int water_h = ImageHeight(water_image);
			int x_max = width - water_w;
			int y_max = height - water_h;
			
			unsigned int topLeftX = rand() % (x_max + 1);
			unsigned int topLeftY = rand() % (y_max + 1);
			
			int frame_count = 0;
			IENTRY *entry = movie->Frames->First;
			
			while (entry) {
				if (frame_count % 15 == 0) {
					topLeftX = rand() % (x_max + 1);
					topLeftY = rand() % (y_max + 1);
				}
		
				entry->image = Watermark(entry->image, water_image, topLeftX, topLeftY);
				entry = entry->Next;
				frame_count++;
			}
		
			RGB2YUVMovie(movie);
			printf("Operation Watermark is done!\n");
			DeleteImage(water_image);
		}

		if (spotlight) {
			YUV2RGBMovie(movie);
			IENTRY *entry1 = movie->Frames->First;
			IENTRY *entry2 = movie->Frames->Last;
		
			int frame = sqrt((width / 2) * (width / 2) + (height / 2) * (height / 2)) / 20;
		
			for (int i = 20; i > 0; i--) {
				Image *newImage = CreateImage(ImageWidth(entry1->image), ImageHeight(entry1->image));
				assert(newImage);
		
				for (int y = 0; y < ImageHeight(entry1->image); y++) {
					for (int x = 0; x < ImageWidth(entry1->image); x++) {
						SetPixelR(newImage, x, y, GetPixelR(entry1->image, x, y));
						SetPixelG(newImage, x, y, GetPixelG(entry1->image, x, y));
						SetPixelB(newImage, x, y, GetPixelB(entry1->image, x, y));
					}
				}
				PrependRGBImage(movie->Frames, Spotlight(newImage, width / 2, height / 2, (i-1) * frame));
			}
		
			for (int i = 20; i > 0; i--) {
				Image *newImage = CreateImage(ImageWidth(entry2->image), ImageHeight(entry2->image));
				assert(newImage);
		
				for (int y = 0; y < ImageHeight(entry2->image); y++) {
					for (int x = 0; x < ImageWidth(entry2->image); x++) {
						SetPixelR(newImage, x, y, GetPixelR(entry2->image, x, y));
						SetPixelG(newImage, x, y, GetPixelG(entry2->image, x, y));
						SetPixelB(newImage, x, y, GetPixelB(entry2->image, x, y));
					}
				}
				AppendRGBImage(movie->Frames, Spotlight(newImage, width / 2, height / 2, (i-1) * frame));
			}
			RGB2YUVMovie(movie);
			printf("Operation Spotlight is done! New number of frames is %d.\n", movie->Frames->Length);
		}
		
		

		assert(movie);
		SaveMovie(fout, movie);
		
		fin = NULL;
        fout = NULL;



		DeleteMovie(movie);

        return 0;
}

void PrintUsage()
{
        printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> [options]\n"
               "Options:\n"
               "-s <WidthxHeight>     To set the resolution of the input stream (WidthxHeight)\n"
               "-bw                   Activate the black and white filter on every movie frame\n"
               "-hmirror              Activate horizontal mirror on every movie frame\n"
               "-edge                 Activate the edge filter on every movie frame\n"
               "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
               "-fast <factor>        Fast forward the movie by <factor>\n"
               "-reverse              Reverse the frame order of the input movie\n"
               "-watermark <file>     Add a watermark from <file> to every movie frame\n"
               "-spotlight            Spotlight the fade in and fade out\n"
               "-rotate               Rotate and zoom in/out the input movie\n"
               "-h                    Display this usage information\n"
              );
}

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
        unsigned int width, unsigned height)
{
        FILE *file;
        unsigned int x, y;
        unsigned char c;
        YUVImage* YUVimage;

        /* Check errors */
        assert(fname);
        assert(n >= 0);

        YUVimage = CreateYUVImage(width, height);
        if (YUVimage == NULL) {
                return NULL;
        }

        /* Open the input file */
        file = fopen(fname, "r");
        if (file == NULL) {
                DeleteYUVImage(YUVimage);
                return NULL;
        }

        /* Find the desired frame */
        fseek(file, 1.5 * n * width * height, SEEK_SET);

        for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                        c = fgetc(file);
                        SetPixelY(YUVimage, x, y, c);
                } /*rof*/
        }

        for (y = 0; y < height; y += 2) {
                for (x = 0; x < width; x += 2) {
                        c = fgetc(file);
                        SetPixelU(YUVimage, x, y, c);
                        SetPixelU(YUVimage, x + 1, y, c);
                        SetPixelU(YUVimage, x, y + 1, c);
                        SetPixelU(YUVimage, x + 1, y + 1, c);
                }
        }

        for (y = 0; y < height; y += 2) {
                for (x = 0; x < width; x += 2) {
                        c = fgetc(file);
                        SetPixelV(YUVimage, x, y, c);
                        SetPixelV(YUVimage, x + 1, y, c);
                        SetPixelV(YUVimage, x, y + 1, c);
                        SetPixelV(YUVimage, x + 1, y + 1, c);
                }
        }

        /* Check errors */
        assert(ferror(file) == 0);

        /* Close the input file and return */
        fclose(file);
        file = NULL;
        return YUVimage;
}

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum, unsigned int width, unsigned height)
{
    assert(fname);
	Movie *movie = CreateMovie();
	assert(movie);
	assert(movie->Frames);

	for(int i = 0; i < frameNum; i++){
		YUVImage *yuv = LoadOneFrame(fname, i, width, height);
		assert(yuv);
		AppendYUVImage(movie->Frames, yuv);
	}

	printf("The movie file %s has been read successfully!\n", fname);
	return movie;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie)
{
        int count;
        FILE *file;
        IENTRY *curr;

        /* Open the output file */
        file = fopen(fname, "w");
        if (file == NULL) {
                return 1;
        }

        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {

                SaveOneFrame(curr->image, fname, file);
                curr = curr->Next;
                count++;
        }

        fclose(file);
        file = NULL;

        printf("The movie file %s has been written successfully!\n", fname);
        printf("%d frames are written to the file %s in total.\n", count, fname);
        return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file)
{
        int x, y;
        for (y = 0; y < image->H; y++) {
                for (x = 0; x < image->W; x++) {
                        fputc(GetPixelY(image, x, y), file);
                }
        }

        for (y = 0; y < image->H; y += 2) {
                for (x = 0; x < image->W; x += 2) {
                        fputc(GetPixelU(image, x, y), file);
                }
        }

        for (y = 0; y < image->H; y += 2) {
                for (x = 0; x < image->W; x += 2) {
                        fputc(GetPixelV(image, x, y), file);
                }
        }
}


/* EOF */
