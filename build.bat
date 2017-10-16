@echo off

del /s /q build\html5\*
rmdir /s /q build\html5
mkdir build\html5

emcc ^
	src/Main.cpp ^
	src/engine/GLES2Example1.cpp ^
	-std=c++1z ^
	-I include ^
	-O3 ^
	-s USE_SDL=2 ^
	-s USE_SDL_IMAGE=2 ^
	-s SDL2_IMAGE_FORMATS="[""png""]" ^
	-s WASM=1 ^
	--shell-file assets/index.html ^
	-o build/html5/release.html

REM	--preload-file assets ^
