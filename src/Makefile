CC = g++
CC_FLAGS = -std=c++11 -Wall -Wextra

EXECUTABLE = calculator
BUILDDIR := build
DOXYFILE := Doxyfile
PROFILING := profile

ROOT_DIR := $(shell cd .. && pwd)
SRCDIR = $(ROOT_DIR)/src
LIB_SRCDIR = $(SRCDIR)/lib
CALCULATOR_SRCDIR = $(SRCDIR)/Calculator
TEST_SRCDIR = $(SRCDIR)/Tests
PROFILING_SRCDIR = $(SRCDIR)/Profiling

PROFILING_SRC := $(wildcard $(PROFILING_SRCDIR)/*.cpp)
LIB_SRC := $(wildcard $(LIB_SRCDIR)/*.cpp)
CALCULATOR_SRC := $(wildcard $(CALCULATOR_SRCDIR)/*.cpp)
LIB_HEADERS := $(wildcard $(LIB_SRCDIR)/*.h)

LIB_OBJ := $(patsubst $(LIB_SRCDIR)/%.cpp, $(BUILDDIR)/lib/%.o, $(LIB_SRC))
CALCULATOR_OBJ := $(patsubst $(CALCULATOR_SRCDIR)/%.cpp, $(BUILDDIR)/Calculator/%.o, $(CALCULATOR_SRC))
ALL_OBJ := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(LIB_OBJ) $(CALCULATOR_OBJ))

.PHONY: all pack clean test doc run profile install build_calculator

all: install build_calculator   

run:
	cd $(CALCULATOR_SRCDIR) && ./$(EXECUTABLE)

profile: 
	cd Profiling && cmake . && make
	
pack:
	zip -r xkovarj00_xsvancd00_xvanatv00.zip ../../../doc ../../../install ../../../repo

doc: Doxyfile
	rm -rf ../doc
	mkdir ../doc
	doxygen  $(DOXYFILE)

clean:

build_calculator: 
	cd $(CALCULATOR_SRCDIR) && cmake . && make 

install: qtest_download QT_libs

qtest_download:
	mkdir -p $(TEST_SRCDIR)/build
	cd $(TEST_SRCDIR)/build && cmake ..
	cmake --build $(TEST_SRCDIR)/build


test:
	cd $(TEST_SRCDIR)/build && ctest

QT_libs:
#for REDHOT
	sudo dnf install -y qt-devel
#	sudo dnf install qt5-devel
	sudo dnf install qt5-qtbase-devel
#	sudo dnf install qt6-devel   
#for Ubuntu   
#	sudo apt-get install qtbase5-dev qt5-default  
#	sudo apt-get install qtbase6-dev qt6-default

#$(BUILDDIR)/lib/%.o: $(LIB_SRC) $(LIB_HEADERS)
#	mkdir -p $(@D)
#	$(CC) $(CC_FLAGS) $(QTFLAGS) -c -o $@ $<

#%.o: %.cpp
#	$(CC) $(CC_FLAGS) -c $< -o $@

#$(profile): $(LIB_SRC) $(LIB_HEADERS) $(PROFILING_SRC)
#	$(CC) $(CC_FLAGS) -c -o $@ $<
