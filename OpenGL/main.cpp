#define SDL_MAIN_HANDLED
//------------------------------/
#define WIN_HEIGHT 600
#define WIN_WIDTH 800
//Third-party include--------------------/
#include "glad.h"
#include "third_party/Include/SDL2/SDL.h"
#include "third_party/Include/glm/glm.hpp"
#include "third_party/Include/glm/gtc/matrix_transform.hpp"
#include "third_party/Include/glm/gtc/type_ptr.hpp"
//-------------------------------/
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
//-------------------------------/
#include <iostream>
#include <ctime>
using namespace std;
// ------------------------------/
SDL_Window *window;
SDL_GLContext context;
Shader shader;
Mesh mesh;
Texture texture;
Camera camera;
// ------------------------------/
bool Init();
void SetupRs();
void Render();
void Destroy();
void popup(char *p);
// ------------------------------/
//Input process
void win_event_pro(SDL_Event& e,float _duration);
void key_pro(float _duration);
void key_event_pro(SDL_Event& e, float _duration);
void mouse_event_pro(SDL_Event& e, float _duration);
//-------------------------------/
int main()
{
	Init();
	SetupRs();
	SDL_Event e;
	bool quit = 0;
	clock_t last = clock();
	while (!quit) 
	{
		clock_t now = clock();
		float duration = float(now - last) / float(CLOCKS_PER_SEC);
		last = now;
		key_pro(duration);
		Render();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
				break;
			}
			switch (e.type)
			{
			case SDL_WINDOWEVENT:
				win_event_pro(e,duration);
				break;
				//window event
				break;
			case SDL_MOUSEMOTION:
				mouse_event_pro(e, duration);
				break;
			case SDL_KEYDOWN:
				key_event_pro(e, duration);
				break;
			default:
				break;
			}
		}
	}
	Destroy();
	return 1;
}


// ------------Init------------/
bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cerr << "Failed to init sdl" << endl;
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window =
		SDL_CreateWindow("SDL2-OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		cerr << "Failed to create window" << endl;
		return 0;
	}

	context = SDL_GL_CreateContext(window);
	// Check OpenGL properties
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_ShowCursor(SDL_DISABLE);
	return 1;
}
// ------------------------------/

// ----------SetupRs-----------/
void SetupRs()
{
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glClearColor(0.78f, 0.87f, 0.98f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	//camera---------------------
	camera.set_speed(2.0f);
	camera.set_mouse_sensitivity(0.05f);
	camera.set_position(0.0f, 0.0f, -3.0f);
	// shader--------------------
	shader.build_from_file("shader/v_world.vs", "shader/f_world.fs");
	shader.use();
	//projection
	glm::mat4 proj;
	proj = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH) / float(WIN_HEIGHT), 0.1f, 100.0f);
	shader.set_mat4f("projection", glm::value_ptr(proj));
	// ·­×ª
	stbi_set_flip_vertically_on_load(true);
	texture.load_from_file("tex/hello.jpg", 0, 0);
	texture.use();
	shader.set_int("sampler", 0);
	make_tex_cube(&mesh);
}
// ------------------------------/

// -----------Render-----------/
void Render() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glm::mat4 model,view;
	static float angle = 0.0f;
	model =glm::rotate(model, glm::radians(++angle), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.set_mat4f("model", glm::value_ptr(model));
	view = camera.get_view_matrix();
	shader.set_mat4f("view", glm::value_ptr(view));
	mesh.draw(GL_TRIANGLES);
	SDL_GL_SwapWindow(window);
}

// ------------------------------/
// -------Destroy----------/
void Destroy()
{
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}

// ------------------------------/
// -------popup----------/
void popup(char *p)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL2", p, window);
}

void win_event_pro(SDL_Event & e, float _duration)
{
	switch (e.window.event)
	{
	case SDL_WINDOWEVENT_RESIZED:
		glViewport(0, 0, e.window.data1, e.window.data2);
		break;
	}
}

void mouse_event_pro(SDL_Event & e, float _duration)
{
	static bool first_time = true;
	if (first_time)
	{
		SDL_WarpMouseInWindow(window, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		first_time = false;
	}
	else
	{
		camera.ratate_camera(e.motion.x -WIN_WIDTH / 2, e.motion.y -WIN_HEIGHT / 2, true);
		SDL_WarpMouseInWindow(window, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
}

void key_pro(float _duration)
{
	auto state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W])
	{
		camera.move_camera(CAMERA_FORWARD, _duration);
	}
	if (state[SDL_SCANCODE_S])
	{
		camera.move_camera(CAMERA_BACKWARD, _duration);
	}
	if (state[SDL_SCANCODE_A])
	{
		camera.move_camera(CAMERA_LEFT, _duration);
	}
	if (state[SDL_SCANCODE_D])
	{
		camera.move_camera(CAMERA_RIGHT, _duration);
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		camera.move_camera(CAMERA_UP, _duration);
	}
	if (state[SDL_SCANCODE_LCTRL])
	{
		camera.move_camera(CAMERA_DOWN, _duration);
	}
	if (state[SDL_SCANCODE_ESCAPE])
	{
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
	}
}

void key_event_pro(SDL_Event & e, float _duration)
{
	/*switch (e.key.keysym.scancode)
	{
	default:
		break;
	}*/
}
