CC = g++
CC_FLAGS = -std=c++11 -Wall -Wextra

EXECUTABLE = calculator
BUILDDIR := build
DOXYFILE := Doxyfile

ROOT_DIR := $(shell cd .. && pwd)
SRCDIR = $(ROOT_DIR)/src
LIB_SRCDIR = $(SRCDIR)/lib
CALCULATOR_SRCDIR = $(SRCDIR)/Calculator
TEST_SRCDIR = $(SRCDIR)/Tests
PROFILING_SRCDIR = $(SRCDIR)/Profiling


.PHONY: all pack clean test doc run profile install build_calculator remove_profiling remove_calculator remove_tests qtest_download QT_libs

all: install build_calculator   

run:
	cd $(CALCULATOR_SRCDIR)/$(BUILDDIR) && ./$(EXECUTABLE)

test:
	cd $(TEST_SRCDIR)/$(BUILDDIR) && ctest


profile: remove_profiling
	mkdir -p $(PROFILING_SRCDIR)/$(BUILDDIR)
	cd $(PROFILING_SRCDIR)/$(BUILDDIR) && cmake .. && make


doc: Doxyfile
	rm -rf ../../doc
	mkdir ../../doc
	doxygen $(DOXYFILE)



clean: remove_tests remove_profiling remove_calculator


pack:
	zip -r xkovarj00_xsvancd00_xvanatv00.zip ../../../doc ../../../install ../../../repo


build_calculator: remove_calculator
	mkdir -p $(CALCULATOR_SRCDIR)/$(BUILDDIR)
	cd $(CALCULATOR_SRCDIR)/$(BUILDDIR) && cmake .. && make


install: qtest_download QT_libs


qtest_download: remove_tests
	mkdir -p $(TEST_SRCDIR)/build
	cd $(TEST_SRCDIR)/build && cmake ..
	cmake --build $(TEST_SRCDIR)/build


QT_libs:
#for REDHOT
#	sudo dnf install -y qt-devel
#	sudo dnf install qt5-qtbase-devel
  
#for Ubuntu
#	sudo apt install -y qtbase5-dev
	sudo apt update
	sudo apt install -y qtcreator qtbase5-dev qt5-qmake cmake
#	sudo apt-get install qt5-default
#	sudo apt install -y qtbase5-dev
#	sudo apt-get install qtbase5-dev qt5-default  
#	sudo apt-get install qtbase6-dev qt6-default

remove_tests:
	rm -rf $(TEST_SRCDIR)/$(BUILDDIR) && rm -rf build


remove_profiling:
	rm -rf $(PROFILING_SRCDIR)/$(BUILDDIR) && rm -rf build


remove_calculator:
	rm -rf $(CALCULATOR_SRCDIR)/$(BUILDDIR) && rm -rf build
