# Compiler
CC = g++
# Qt Libraries
# Compiler flags
QT_LIBS := $(shell pkg-config --libs Qt5Widgets)

CC_FLAGS = -std=c++11 -Wall -Wextra
# Qt flags
QTFLAGS = $(shell pkg-config --cflags Qt5Widgets)
# Executable name
EXECUTABLE = calculator
TEST_EXEC = Tests
BUILDDIR := build
DOXYFILE := Doxyfile
PDF_OUTPUT := ../dokumentace.pdf

MAIN_EXEC = $(BUILDDIR)/$(EXECUTABLE)
TEST_EXEC = $(BUILDDIR)/Tests

DOC_OUTPUT_DIR := $(ROOT_DIR)/src/doxygen_output

GTEST_DIR := release-1.11.0

GTEST_INSTALLED := $(wildcard $(GTEST_DIR))
GTEST_URL := https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
CPPFLAGS += -isystem $(GTEST_DIR)/include
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

ROOT_DIR := $(shell cd .. && pwd)
SRCDIR = $(ROOT_DIR)/src
LIB_SRCDIR = $(SRCDIR)/lib
CALCULATOR_SRCDIR = $(SRCDIR)/Calculator
TEST_SRCDIR = $(SRCDIR)/Tests

LIB_SRC := $(wildcard $(LIB_SRCDIR)/*.cpp)
CALCULATOR_SRC := $(wildcard $(CALCULATOR_SRCDIR)/*.cpp)
TEST_SRC := $(wildcard $(TEST_SRCDIR)/*.cpp)
LIB_HEADERS := $(wildcard $(LIB_SRCDIR)/*.h)

LIB_OBJ := $(patsubst $(LIB_SRCDIR)/%.cpp, $(BUILDDIR)/lib/%.o, $(LIB_SRC))
CALCULATOR_OBJ := $(patsubst $(CALCULATOR_SRCDIR)/%.cpp, $(BUILDDIR)/Calculator/%.o, $(CALCULATOR_SRC))
TEST_OBJ := $(patsubst $(TEST_SRCDIR)/%.cpp, $(BUILDDIR)/Tests/%.o, $(TEST_SRC))
# Relative paths to object files
ALL_OBJ := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(LIB_OBJ) $(CALCULATOR_OBJ) $(TEST_OBJ))


SRC_DIRS := $(LIB_SRCDIR) $(CALCULATOR_SRCDIR) $(TEST_SRCDIR)
FILES_WITH_DOXYGEN_COMMENTS := $(shell grep -rl '/\*\*' $(SRC_DIRS))

PKG_CONFIG_URL := https://pkg-config.freedesktop.org/releases/pkg-config-0.29.2.tar.gz

.PHONY: all pack clean test doc run profile gtest_download

all: $(TEST_EXEC) $(MAIN_EXEC) 

# Compile rule for main executable
$(MAIN_EXEC): $(ALL_OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(CC_FLAGS) $(QT_LIBS) -o $@ $^

# Compile rule for test executable
$(TEST_EXEC): $(ALL_OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(CC_FLAGS) -o $@ $^ $(QT_LIBS)

run:
	cd $(CALCULATOR_SRCDIR) && ./calculator
#profile:
#	$(CC) -o profiling $(wildcard src/*.cpp) $(wildcard src/libs/*.cpp)
#	./profiling

profile: $()
	./$()


#	$(CC) -o profiling $(filter-out Tests/%,$(wildcard *.cpp)) && ./profiling
	
test: $(TEST_EXEC)
	./$(TEST_EXEC)

pack:

doc: Doxyfile
	rm -rf ../doc
	mkdir ../doc
	doxygen  $(DOXYFILE)
#	mv html/ ../doc




clean:


$(BUILDDIR)/lib/%.o: $(LIB_SRC) $(LIB_HEADERS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(QTFLAGS) -c -o $@ $<

$(BUILDDIR)/Calculator/%.o: $(CALCULATOR_SRCDIR)/%.cpp
	mkdir -p $(@D) 
	$(CC) $(CC_FLAGS) $(QTFLAGS) -c -o $@ $<

$(BUILDDIR)/Tests/%.o: $(TEST_SRCDIR)/%.cpp 
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(QTFLAGS) -c -o $@ $<


second: 
	cd $(CALCULATOR_SRCDIR) && cmake . && make 

install: gtest_download QT_libs

gtest_download:
	@if [ ! -d "$(GTEST_DIR)" ]; then \
		if [ ! -f "$(GTEST_DIR).tar.gz" ]; then \
			wget $(GTEST_URL); \
		fi; \
		tar xf $(GTEST_DIR).tar.gz; \
	fi



#	cd $(TEST_SRCDIR)
#	cmake -S . -B build
qtest_download2:
	mkdir -p $(TEST_SRCDIR)/build
	cd $(TEST_SRCDIR)/build && cmake ..


test2:
	cmake --build $(TEST_SRCDIR)/build
	cd $(TEST_SRCDIR)/build && ctest
#	cmake --build build
#	cd build && ctest

QT_libs:
#for REDHOT
	sudo dnf install -y qt-devel
#	sudo dnf install qt5-devel
	sudo dnf install qt5-qtbase-devel
#	sudo dnf install qt6-devel   
#for Ubuntu   
#	sudo apt-get install qtbase5-dev qt5-default  
#	sudo apt-get install qtbase6-dev qt6-default


