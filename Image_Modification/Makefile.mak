all: PhotoLab PhotoLabTest # all target to create non debug and debug executables

# creation of non debug executable
PhotoLab: PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o Test.o
	gcc -Wall -std=c11 -lm -g -o PhotoLab PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o Test.o

# creation of debug executable
PhotoLabTest: PhotoLabTest.o FileIOTest.o DIPsTest.o AdvancedTest.o ImageTest.o TestTest.o
	gcc -Wall -std=c11 -lm -g -o PhotoLabTest PhotoLabTest.o FileIOTest.o DIPsTest.o AdvancedTest.o ImageTest.o TestTest.o

# PhotoLab object file non-debug
PhotoLab.o: PhotoLab.c FileIO.h DIPs.h Advanced.h
	gcc -Wall -std=c11 -g -c PhotoLab.c -o PhotoLab.o

# Input Output object file non-debug
FileIO.o: FileIO.c FileIO.h
	gcc -Wall -std=c11 -g -c FileIO.c -o FileIO.o

# basic DIP object file non-debug
DIPs.o: DIPs.c DIPs.h
	gcc -Wall -std=c11 -g -c -lm DIPs.c -o DIPs.o

# advanced DIP oject file non-debug
Advanced.o: Advanced.c Advanced.h
	gcc -Wall -std=c11 -g -c -lm Advanced.c -o Advanced.o

# Image object file non-debug
Image.o: Image.c Image.h
	gcc -Wall -std=c11 -g -c Image.c -o Image.o

# Test object file non-debug
Test.o: Test.c Test.h
	gcc -Wall -std=c11 -g -c Test.c -o Test.o

# PhotoLab object file debug
PhotoLabTest.o: PhotoLab.c FileIO.h DIPs.h Advanced.h
	gcc -Wall -std=c11 -g -DDEBUG -c PhotoLab.c -o PhotoLabTest.o

# Input Output object file debug
FileIOTest.o: FileIO.c FileIO.h
	gcc -Wall -std=c11 -g -c -DDEBUG FileIO.c -o FileIOTest.o

# basic DIP object file debug
DIPsTest.o: DIPs.c DIPs.h
	gcc -Wall -std=c11 -g -c -lm -DDEBUG DIPs.c -o DIPsTest.o

# advanced DIP object file debug
AdvancedTest.o: Advanced.c Advanced.h
	gcc -Wall -std=c11 -g -c -lm -DDEBUG Advanced.c -o AdvancedTest.o

# Image object file debug
ImageTest.o: Image.c Image.o
	gcc -Wall -std=c11 -g -c -DDEBUG Image.c -o ImageTest.o

# Test object file debug
TestTest.o: Test.c Test.h
	gcc -Wall -std=c11 -g -c -DDEBUG Test.c -o TestTest.o

# removes all created file in a make all command
clean:
	rm -f PhotoLab PhotoLabTest PhotoLab.o PhotoLabTest.o FileIO.o DIPs.o Advanced.o FileIOTest.o DIPsTest.o AdvancedTest.o Image.o Test.o ImageTest.o TestTest.o
