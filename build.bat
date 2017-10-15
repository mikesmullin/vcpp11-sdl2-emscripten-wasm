@echo off

emcc ^
	src/Main.cpp ^
	src/test/GLES2Example1.cpp ^
	-std=c++1z ^
	-I include ^
	-O2 ^
	-g4 ^
	-s USE_SDL=2 ^
	-s USE_SDL_IMAGE=2 ^
	-s SDL2_IMAGE_FORMATS="[""png""]" ^
	-s WASM=1 ^
	--source-map-base http://localhost:8080/ ^
	-o build/html5/release.html

REM	--preload-file assets ^
