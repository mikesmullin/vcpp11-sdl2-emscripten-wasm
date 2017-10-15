@echo off

emcc ^
	src/Main.cpp ^
	src/test/GLES2Example1.cpp ^
	-std=c++1z ^
	-I include ^
	-O2 ^
	-s USE_SDL=2 ^
	-s USE_SDL_IMAGE=2 ^
	-s SDL2_IMAGE_FORMATS="[""png""]" ^
	--preload-file assets ^
	-s WASM=1 ^
	-o build/html5/release.html

