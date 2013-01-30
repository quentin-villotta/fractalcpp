# Makefile for compiling on OS X with SDL installed via macports (install following ports : TODO)

# Compiler
CC=g++

# Objects
OBJECTS=App.o App_Cleanup.o App_Event.o App_Init.o App_Loop.o App_Render.o \
	Fractal.o FractalMandelbrot.o FractalJulia.o \
	SurfaceHelper.o

# Compiler flags
CPPFLAGS=-Wall -g -I/opt/local/include

# Linker flags
LDFLAGS=-L/opt/local/lib -lSDL -lSDLmain -framework Cocoa

main: App.cpp
	$(CC) $(CPPFLAGS) -c App.cpp App_Cleanup.cpp App_Event.cpp App_Init.cpp App_Loop.cpp App_Render.cpp \
		Fractal.cpp FractalMandelbrot.cpp FractalJulia.cpp \
		SurfaceHelper.cpp
	$(CC) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) #-o fractalcpp

# cleanup
clean:
	rm -rf $(OBJECTS)

# EOF
