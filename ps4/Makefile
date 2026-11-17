# ParadiseGTA -- PS4 / GoldHEN port
# ---------------------------------------------------------------
# Builds `paradise_gta.prx`, a GoldHEN plugin, from:
#   src/            the ported menu (menu.cpp, pages.cpp, ...)
#   include/        natives_ps4.h (generated), invoker, offsets, ...
#   sdk/goldhen/    vendored GoldHEN Plugin SDK (built from source in-tree,
#                   as its README recommends)
#
# Requirements:
#   OpenOrbis PS4 Toolchain (v0.5.4 tested)    export OO_PS4_TOOLCHAIN=/path
#   LLVM/clang 14+ (the toolchain's own bin/ also works)
#
#   make                 -> build/paradise_gta.prx
#   make natives         -> regenerate include/natives_ps4.h from the PS3 tree
#   make report          -> build/native_report.md (what mapped, what did not)
#   make clean
#
# The PS3 sources are NOT compiled: they are the reference this port is
# derived from (see docs/PORTING.md).

TARGET      := paradise_gta
OUTDIR      := build
INTDIR      := build/obj
TOOLCHAIN   ?= $(OO_PS4_TOOLCHAIN)

SRC_DIR     := src
SDK_DIR     := sdk/goldhen
INC_DIR     := include
PS3_DIR     ?= ../ParadiseGTA_optimized_2020

# ---- toolchain --------------------------------------------------------
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CC  := /usr/local/opt/llvm/bin/clang
  CXX := /usr/local/opt/llvm/bin/clang++
  LD  := /usr/local/opt/llvm/bin/ld.lld
  CDIR := macos
else
  CC  := clang
  CXX := clang++
  LD  := ld.lld
  CDIR := linux
endif

COMMONFLAGS := --target=x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c -O2 \
               -fcolor-diagnostics -Wall -Wno-unused-parameter \
               -isysroot $(TOOLCHAIN) -isystem $(TOOLCHAIN)/include \
               -I$(INC_DIR) -I$(SDK_DIR)/include
CXXFLAGS    := $(COMMONFLAGS) -std=c++17 -fno-exceptions -fno-rtti \
               -isystem $(TOOLCHAIN)/include/c++/v1
LDFLAGS     := -m elf_x86_64 -pie --script $(TOOLCHAIN)/link.x -e _init \
               --eh-frame-hdr -L$(TOOLCHAIN)/lib -lSceLibcInternal -lkernel -lSceSysmodule

# ---- sources ----------------------------------------------------------
CPP_SRC  := $(wildcard $(SRC_DIR)/*.cpp)
C_SRC    := $(wildcard $(SDK_DIR)/source/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp,$(INTDIR)/%.o,$(CPP_SRC)) \
            $(patsubst $(SDK_DIR)/source/%.c,$(INTDIR)/sdk_%.o,$(C_SRC))
CRTOBJ   := $(INTDIR)/crtprx.o

.PHONY: all natives report clean hostcheck check-toolchain
.DEFAULT_GOAL := all

all: check-toolchain $(OUTDIR)/$(TARGET).prx

$(OUTDIR)/$(TARGET).prx: $(OBJS) $(CRTOBJ)
	@mkdir -p $(OUTDIR)
	$(LD) $(CRTOBJ) $(OBJS) -o $(OUTDIR)/$(TARGET).elf $(LDFLAGS)
	$(TOOLCHAIN)/bin/$(CDIR)/create-fself -in=$(OUTDIR)/$(TARGET).elf \
		-out=$(OUTDIR)/$(TARGET).oelf --lib=$(OUTDIR)/$(TARGET).prx --paid 0x3800000000000011
	@echo
	@echo "built $(OUTDIR)/$(TARGET).prx"
	@echo "install: copy it to /data/GoldHEN/plugins/ on the PS4"

$(INTDIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/natives_ps4.h
	@mkdir -p $(INTDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(INTDIR)/sdk_%.o: $(SDK_DIR)/source/%.c
	@mkdir -p $(INTDIR)
	$(CC) $(COMMONFLAGS) -D__USE_KLOG__ -o $@ $<

$(CRTOBJ): $(SDK_DIR)/crt/crtprx.c
	@mkdir -p $(INTDIR)
	$(CC) -target x86_64-pc-linux-gnu -ffreestanding -nostdlib -fno-builtin -fPIC \
		-isysroot $(TOOLCHAIN) -isystem $(TOOLCHAIN)/include -c $< -o $@

# ---- generated native layer ------------------------------------------
natives:
	python3 tools/gen_natives_ps4.py \
		--ps3 $(PS3_DIR)/Natives.h \
		--nativedb tools/nativedb/natives.json.gz \
		--out $(INC_DIR)/natives_ps4.h \
		--report build/native_report.md \
		--map-out build/native_hash_map.json

report: natives
	@cat build/native_report.md | head -40

# ---- helpers ---------------------------------------------------------
hostcheck:
	$(MAKE) -C hostcheck run

check-toolchain:
	@if [ -z "$(TOOLCHAIN)" ]; then \
		echo "ERROR: OO_PS4_TOOLCHAIN is not set."; \
		echo "       export OO_PS4_TOOLCHAIN=/path/to/OpenOrbis-PS4-Toolchain"; \
		exit 1; \
	fi

clean:
	rm -rf $(OUTDIR)
