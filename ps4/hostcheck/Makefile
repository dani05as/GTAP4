# hostcheck -- builds the portable part of the port for the PC, with a fake
# native layer, so the menu framework and the pages can be tested without a
# console.  This is NOT how the plugin is built (see ../Makefile for that).
#
#   make -C ps4/hostcheck run

CXX      ?= g++
CXXFLAGS := -std=c++17 -O1 -g -Wall -Wextra -Wno-unused-parameter \
            -DPARADISE_HOSTCHECK -I../include
SRC      := main.cpp ../src/menu.cpp ../src/pages.cpp ../src/native_invoker.cpp \
            ../src/offsets.cpp ../src/platform.cpp
OUT      := build/hostcheck

all: $(OUT)

$(OUT): $(SRC) $(wildcard ../include/*.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

run: $(OUT)
	./$(OUT)

clean:
	rm -rf build

.PHONY: all run clean
