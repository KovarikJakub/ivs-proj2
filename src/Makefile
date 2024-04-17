# Compiler
CC = g++
# Qt Libraries
QT_LIBS = -lQt5Widgets -lQt5Core -lQt5Gui
# Compiler flags
CC_FLAGS = -std=c++11 -Wall -Wextra
# Qt flags
QTFLAGS = $(shell pkg-config --cflags Qt5Widgets)
# Executable name
EXECUTABLE = calculator

OBJ := $(SRC:.cpp=.o)

ROOT_DIR:=$(shell cd)\..

DOC_OUTPUT_DIR=$(ROOT_DIR)\src\doxygen_output

GTEST_DIR := googletest-release-1.11.0
GTEST_INSTALLED := $(wildcard $(GTEST_DIR))
GTEST_URL := https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz

SRCDIR = src
LIBDIR = $(SRCDIR)/lib
TESTDIR = $(SRCDIR)/Tests
SRC := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(LIBDIR)/*.cpp) $(wildcard $(TESTDIR)/*.cpp)
TEST_EXEC = Tests


.PHONY: all pack clean test doc run profile gtest_download

all:

run:

#profile:
#	$(CC) -o profiling $(wildcard src/*.cpp) $(wildcard src/libs/*.cpp)
#	./profiling

profile:
    $(CC) -o profiling $(filter-out src/Tests/%,$(wildcard $(shell find src -name '*.cpp')))
	./profiling

gtest_download:
	ifndef GTEST_INSTALLED
	wget $(GTEST_URL)
	tar xf $(GTEST_DIR).tar.gz
	endif

test: gtest_download
	$(TEST_EXEC)

pack:

#doc: Doxyfile #TODO - Soubory
#	cd .. && rm -rf doc
#	doxygen
#	mv doc ../doc

doc:
    doxygen $(DOXYFILE)
    @mv $(DOCDIR)/dox $(DOCDIR)/dox_old || true


clean:

# Linking
$(EXECUTABLE): $(OBJ)
	$(CC) $(CC_FLAGS) $(QT_LIBS) -o $@ $^

# Compilation
%.o: %.cpp
	$(CC) $(CC_FLAGS) $(QTFLAGS) -c -o $@ $<


