#include "EGL/egl.h"
#include "GLES2/gl2.h"
//#include "shader_utils.h"
#include "SDL.h"
#include "SDL_syswm.h"
#include "SDL_egl.h"
#include <assert.h>
#include <iostream>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

// #define GL_GLEXT_PROTOTYPES 1
// #define CHECK_GL_ERROR \
// 	while ((error = glGetError()) != 0) { \
// 		printf("GL Error %x: %s:%d\n", error, __FILE__, __LINE__); \
// 		assert(false); \
// 	}


// see also:
// https://kripken.github.io/emscripten-site/docs/porting/multimedia_and_graphics/EGL-Support-in-Emscripten.html

namespace tests::GLES2Example1 {
	int quit = 0;

	auto start = std::chrono::high_resolution_clock::now();

	void cleanup();
	void one_iter();

	void setup()
	{
		std::cout << "init" << std::endl;










		GLenum error;

		int x = 1024;
		int y = 768;

		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

#ifndef __EMSCRIPTEN__

		SDL_Window * window = SDL_CreateWindow("Game!", 100, 100, x, y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL /*| SDL_WINDOW_ALLOW_HIGHDPI */);

		if (window == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return;
		}
#endif

		//EGLDisplay* eglDisplay;
		//EGLContext* eglContext;
		//EGLSurface* eglSurface;
		EGLint configAttribList[] =
		{
			EGL_RED_SIZE,       8,
			EGL_GREEN_SIZE,     8,
			EGL_BLUE_SIZE,      8,
			EGL_ALPHA_SIZE,     8 /*: EGL_DONT_CARE*/,
			EGL_DEPTH_SIZE,     EGL_DONT_CARE,
			EGL_STENCIL_SIZE,   EGL_DONT_CARE,
			EGL_SAMPLE_BUFFERS, 0,
			EGL_NONE
		};
		//EGLint surfaceAttribList[] =
		//{
		//	//EGL_POST_SUB_BUFFER_SUPPORTED_NV, 
		//	//flags & (ES_WINDOW_POST_SUB_BUFFER_SUPPORTED) ? EGL_TRUE : EGL_FALSE,		
		//	EGL_POST_SUB_BUFFER_SUPPORTED_NV,
		//	EGL_FALSE,
		//	EGL_NONE, EGL_NONE
		//};

		EGLint numConfigs;
		EGLint majorVersion;
		EGLint minorVersion;
		EGLDisplay display;
		EGLContext context;
		EGLSurface surface;
		EGLConfig config;
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE }; // EGL_CONTEXT_CLIENT_VERSION == 2 important for emscripten

#ifndef __EMSCRIPTEN__
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version); // initialize info structure with SDL version info 
		SDL_bool get_win_info = SDL_GetWindowWMInfo(window, &info);
		SDL_assert_release(get_win_info);
		EGLNativeWindowType hWnd = info.info.win.window;
#endif

		// Get Display 
		//display = eglGetDisplay(GetDC(hWnd)); // EGL_DEFAULT_DISPLAY 
		display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (display == EGL_NO_DISPLAY)
		{
			return;
		}

		// Initialize EGL 
		if (!eglInitialize(display, &majorVersion, &minorVersion))
		{
			return;
		}

		// Get configs 
		if (!eglGetConfigs(display, NULL, 0, &numConfigs))
		{
			return;
		}

		// Choose config 
		if (!eglChooseConfig(display, configAttribList, &config, 1, &numConfigs))
		{
			return;
		}

		// Create a surface
#ifdef __EMSCRIPTEN__
		surface = eglCreateWindowSurface(display, config, NULL, NULL); // emscripten says pass null here
#else
		surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, /*surfaceAttribList*/ NULL);
#endif
		if (surface == EGL_NO_SURFACE)
		{
			return;
		}

		// Create a GL context 
		context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
		if (context == EGL_NO_CONTEXT)
		{
			return;
		}

		// Make the context current 
		if (!eglMakeCurrent(display, surface, surface, context))
		{
			return;
		}

		printf("GL_VERSION: %s\n", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
		printf("GL_SHADING_LANGUAGE_VERSION: %s\n", reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));


		// // shader sources
		// const std::string vs = R"""(
		// attribute vec4 vPosition;
		// void main()
		// {
		// 	gl_Position = vPosition;
		// }
		// )""";

		// const std::string fs = R"""(
		// precision mediump float;
		// void main()
		// {
		// 	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
		// }
		// )""";

		// GLuint mProgram = CompileProgram(vs, fs);
		// if (!mProgram)
		// {
		// 	CHECK_GL_ERROR
		// 		return;
		// }

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


		std::cout << "loading" << std::endl;



		glViewport(0, 0, x, y);

		//// Use the program object
		//glUseProgram(mProgram);

		// Load the vertex data
//		glEnableVertexAttribArray(0);


		SDL_Event event;

#ifdef __EMSCRIPTEN__

//		EmscriptenWebGLContextAttributes attribs;
//		emscripten_webgl_init_context_attributes(&attribs);
//		attribs.alpha = false;
//		attribs.enableExtensionsByDefault = false;
//		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE em_context =
//			emscripten_webgl_create_context("canvas#display", &attribs);
//		emscripten_webgl_make_context_current(em_context);
//		emscripten_set_resize_callback("window", NULL, false, [](int eventType, const EmscriptenUiEvent *uiEvent, void *userData)->EM_BOOL { return true; });
//		emscripten_set_blur_callback("window", NULL, false, [](int eventType, const EmscriptenFocusEvent *focusEvent, void *userData)->EM_BOOL { return true; });
//		emscripten_set_focus_callback("window", NULL, false, [](int eventType, const EmscriptenFocusEvent *focusEvent, void *userData)->EM_BOOL { return true; });

		// void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
		emscripten_set_main_loop(one_iter, 0, false);

#else

		while (!quit)
		{
			one_iter();
			eglSwapBuffers(display, surface);

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					quit = 1;
				}
			}

			SDL_Delay(1000 / 60); // TODO: instead of fixed-rate, make more intelligent variable rate
		}
#endif
	}


	void cleanup() {
		SDL_Quit();
		std::cout << "done" << std::endl;
	}

	// The "main loop" function.
	void one_iter() {
		const float PERIOD = 5000.0f;
		const float SCALE = 100.0f;

		long long deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
		float r = (sin(deltaTime * 2 * M_PI / PERIOD) * (SCALE / 2) + (SCALE / 2)) / 100;
		float g = (sin(deltaTime * 2 * M_PI / PERIOD + 1000) * (SCALE / 2) + (SCALE / 2)) / 100;
		float b = (sin(deltaTime * 2 * M_PI / PERIOD + 2000) * (SCALE / 2) + (SCALE / 2)) / 100;

#ifdef __EMSCRIPTEN__

//		double w = 0.0;
//		double h = 0.0;
//		emscripten_get_element_css_size("canvas#display", &w, &h);
//		auto roundf = [](double n) -> int32_t {return (int)(n + 0.5); };
//		EM_ASM_({
//			const display = document.querySelector("canvas#display");
//			display.width = $0;
//			display.height = $1;
//			display.tabIndex = 0;
//		}, roundf(w), roundf(h));

#endif


		//			GLfloat vertices[] =
		//			{
		//				0.0f,  0.5f, 0.0f,
		//				r, g, 0.0f,
		//				0.5f, -0.5f, 0.0f,
		//			};
		//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);

		//printf("r %9.6f\n", r);

		glClearColor(r,
			g,
			b, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

	}

}