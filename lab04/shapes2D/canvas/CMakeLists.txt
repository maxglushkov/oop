find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

add_library(
	canvas OBJECT
	CCanvas.cpp
)
