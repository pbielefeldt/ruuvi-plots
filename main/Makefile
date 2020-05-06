### SET-UP ###

# C++ Flags
CXFLAGS	= -std=c++11 -O2

# ROOT Flags
CFLAGS	= $(shell root-config --cflags)

# ROOT Libraries
LIBS	= $(shell root-config --libs)
GLIBS	= $(shell root-config --glibs) -lGeom
RDIR	= -I$(shell root-config --incdir)

# Sources are in src
# build directory is seperate
BLDDIR	= ../build
SRCDIR	= ../src
OBSDIR	= ../obj
MAIN	= ../main

# Objects to be created (in seperate directory)
COMM	=	$(OBSDIR)/SingleMeasurement.o \
			$(OBSDIR)/MeasurementCollection.o

TARGETS	=	plotting #test


### BUILDING TARGETS ###

all: $(TARGETS)

# Default build command
%: $(MAIN)/%.cxx $(COMM)
	g++ $(CXFLAGS) -o $(BLDDIR)/$@ $(CFLAGS) $(LIBS) $(GLIBS) $(addprefix -I,${SRCDIR}) $^

test: $(MAIN)/test.cxx $(COMM)
	g++ $(CXFLAGS) -o $(BLDDIR)/$@ $(CFLAGS) $(LIBS) $(GLIBS) $(addprefix -I,${SRCDIR}) $^ -Wall -ansi

../obj/%.o: $(SRCDIR)/%.cxx
	g++ $(CXFLAGS) -o $@ -c $< $(addprefix -I,${SRCDIR}) $(LIBS) $(GLIBS) $(RDIR)

# Removing the execs -- Note: rm $(BLDDIR)/* will also remove this MAKEFILE!
clean: 
	rm $(TARGETS) $(OBSDIR)/*.o

include $(wildcard ../obj/*.d)
