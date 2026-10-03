.PHONY: all debug setup

all:
	meson compile -C build
	cd build && ./pengui

debug:
	meson compile -C build
	cd build && gdb ./pengui

setup:
	meson setup build
