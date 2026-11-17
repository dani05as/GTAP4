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
# CDIR picks the per-OS helper directory inside the toolchain
# (bin/<CDIR>/create-fself).  It is detected here, but you can always
# override it on the command line:  make CDIR=windows
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CC  := /usr/local/opt/llvm/bin/clang
  CXX := /usr/local/opt/llvm/bin/clang++
  LD  := /usr/local/opt/llvm/bin/ld.lld
  CDIR := macos
  EXE  :=
  OSKIND := macos
else ifneq (,$(filter MINGW% MSYS% CYGWIN% Windows%,$(UNAME_S))$(filter MINGW% MSYS% CYGWIN%,$(shell uname -o 2>/dev/null)))
  # Git Bash / MSYS2 / Cygwin on Windows: the toolchain ships native helpers
  # in bin/windows, and they carry the .exe suffix.
  CC  := clang
  CXX := clang++
  LD  := ld.lld
  CDIR := windows
  EXE  := .exe
  OSKIND := windows
else
  CC  := clang
  CXX := clang++
  LD  := ld.lld
  CDIR := linux
  EXE  :=
  OSKIND := linux
endif

# MSYS2 hands native programs /c/foo paths; clang.exe and ld.lld.exe only
# understand C:/foo.  Normalise both styles so either works for the user.
ifneq ($(strip $(TOOLCHAIN)),)
  ifeq ($(OSKIND),windows)
    TOOLCHAIN := $(shell cygpath -m '$(TOOLCHAIN)' 2>/dev/null || echo '$(TOOLCHAIN)')
  endif
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

.PHONY: all natives report clean hostcheck check-toolchain syntax
.DEFAULT_GOAL := all

all: check-toolchain $(OUTDIR)/$(TARGET).prx

$(OUTDIR)/$(TARGET).prx: $(OBJS) $(CRTOBJ)
	@mkdir -p $(OUTDIR)
	$(LD) $(CRTOBJ) $(OBJS) -o $(OUTDIR)/$(TARGET).elf $(LDFLAGS)
	$(TOOLCHAIN)/bin/$(CDIR)/create-fself$(EXE) -in=$(OUTDIR)/$(TARGET).elf \
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
	@if [ ! -f "$(TOOLCHAIN)/link.x" ]; then \
		echo "ERROR: $(TOOLCHAIN)/link.x not found."; \
		echo "       OO_PS4_TOOLCHAIN must point at the toolchain root (the"; \
		echo "       folder that contains link.x, include/, lib/ and bin/)."; \
		exit 1; \
	fi
	@if [ ! -f "$(TOOLCHAIN)/bin/$(CDIR)/create-fself$(EXE)" ]; then \
		echo "ERROR: $(TOOLCHAIN)/bin/$(CDIR)/create-fself$(EXE) not found."; \
		echo "       detected platform: $(OSKIND) (CDIR=$(CDIR))"; \
		echo "       override it if needed:  make CDIR=windows"; \
		exit 1; \
	fi
	@if ! command -v $(CXX) >/dev/null 2>&1; then \
		echo "ERROR: $(CXX) is not in PATH."; \
		echo "       install LLVM/clang (on Windows: MSYS2 MINGW64 +"; \
		echo "       pacman -S mingw-w64-x86_64-clang mingw-w64-x86_64-lld make)"; \
		exit 1; \
	fi
	@echo "toolchain: $(TOOLCHAIN) ($(OSKIND), helpers in bin/$(CDIR))"

clean:
	rm -rf $(OUTDIR)
