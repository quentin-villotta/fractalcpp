# Makefile for compiling on OS X with SDL installed via macports (install following ports : TODO)

# Compiler
CC=g++

# Objects
OBJECTS=App.o \
	Fractal.o FractalMandelbrot.o FractalJulia.o \
	SurfaceHelper.o

# Compiler flags
CPPFLAGS=-Wall -g -I/opt/local/include

# Linker flags
LDFLAGS=-L/opt/local/lib -lSDL -lSDLmain -lboost_program_options-mt -framework Cocoa

main: App.cpp
	$(CC) $(CPPFLAGS) -c App.cpp \
		Fractal.cpp FractalMandelbrot.cpp FractalJulia.cpp \
		SurfaceHelper.cpp
	$(CC) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) #-o fractalcpp

# cleanup
clean:
	rm -rf $(OBJECTS)

# EOF
