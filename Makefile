CC := g++
SRCDIR := src
BINDIR := bin
BUILDDIR := build
EXECUTABLES := $(BINDIR)/TargetOptimizer

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g
LIB := -L -lm -lpthread -lX11
INC := -I include/ -I ./

all: ${EXECUTABLES}

$(BINDIR)/TargetOptimizer: $(BUILDDIR)/main.o $(BUILDDIR)/source.o $(BUILDDIR)/model.o $(BUILDDIR)/dataio.o
	@echo " Linking" $@ "... "
	@echo " $(CC) $^ -o $@ $(LIB)"; $(CC) $^ -o $@ $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)
	@echo " $(CC) $(CFLAGS) -Wall $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/source.o: dlib/all/source.cpp
	@echo " $(CC) $(CFLAGS) dlib/all/source.cpp -c -o build/source.o"; $(CC) $(CFLAGS) dlib/all/source.cpp -c -o build/source.o

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(BINDIR) $(QTAF0)"; $(RM) -r $(BUILDDIR) $(BINDIR) $(QTAF0)/qta*

test: all
	@echo " Testing TargetOptimizer..."; 
	@echo " bin/TargetOptimizer -c -g -p test/data/Abderhalden.TextGrid test/data/Abderhalden.PitchTier"; bin/TargetOptimizer -c -g -p test/data/Abderhalden.TextGrid test/data/Abderhalden.PitchTier

.PHONY: clean test

