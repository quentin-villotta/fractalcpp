# Makefile for compiling on OS X with SDL and boost installed via macports
# (install following ports : boost, libsdl)

# Compiler
CC=g++

# Objects
OBJECTS=App.o \
	Fractal.o FractalMandelbrot.o FractalJulia.o \
	SurfaceHelper.o

# Compiler flags
CPPFLAGS=-Wall -g -I/opt/local/include -O2 -fopenmp

# Linker flags
LDFLAGS=-L/opt/local/lib -lSDL -lSDLmain -lboost_program_options-mt -lboost_timer-mt -framework Cocoa

main: App.cpp
	$(CC) $(CPPFLAGS) -c App.cpp \
		Fractal.cpp FractalMandelbrot.cpp FractalJulia.cpp \
		SurfaceHelper.cpp
	$(CC) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) #-o fractalcpp

# cleanup
clean:
	rm -rf $(OBJECTS)

# EOF
