#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2024
#
# Initial author: Tim Schmidt
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Image.h ImageList.h Movie.h Constants.h
	gcc -Wall -std=c11 -lm -g -c MovieLab.c -o MovieLab.o
# Target for FileIO.o
FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -std=c11 -g -c FileIO.c -o FileIO.o
# Target for DIPs.o
DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -std=c11 -g -c -lm DIPs.c -o DIPs.o
# Target for Image.o
Image.o: Image.c Image.h
	gcc -Wall -std=c11 -g -c Image.c -o Image.o
# Target for ImageList.o
ImageList.o: ImageList.c ImageList.h
	gcc -Wall -std=c11 -g -c ImageList.c -o ImageList.o
# Target for Movie.o
Movie.o: Movie.c Movie.h
	gcc -Wall -std=c11 -g -c Movie.c -o Movie.o
######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o
	gcc -Wall -std=c11 -lm -g -o MovieLab MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o

###############################  others  ##############################
# Target for clean-up
clean:
	rm -f MovieLab MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o out.yuv