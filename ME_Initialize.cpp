#include "ME_Initialize.h"
#include "ME_Console.h"
#include "ME_pCube.h"

// ---------------------------------------- //
// --------- Инициализация движка  -------- //
// ---------------------------------------- //

	//- Для создания окна
	SDL_Window* window(0);
	SDL_GLContext contexteOpenGL(0);

	//- Матрица
	mat4 projection, modelview;

void ME::Initialize::InitEngine() {

	//- Включаем чтобы потом выключать если ошибки
	Loaded_SDL = true;
	Loaded_Window = true;
	Loaded_GLEW = true;

	PRINT_LOG("- - - - - - - - - - - - - - -");
	PRINT_LOG("- - - - Motion Engine - - - -");
	PRINT_LOG("- - - - - - - - - - - - - - -");
	PRINT_LOG("");
	PRINT_LOG("[Info] Initialization Motion Engine");

	//- Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
		SDL_Quit();

		Loaded_SDL = false;
		SaveLog();
		exit(-1);
	}
	if (Loaded_SDL)
		PRINT_LOG("[Info] SDL was successfully launched");


	//- Назначаем версию OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	//- Двойной буффер
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//- Создание окна
	window = SDL_CreateWindow("Тестирование двигателя Motion Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (window == 0)
	{
		PRINT_LOG("[Error] Error creating window");
		SDL_Quit();

		Loaded_Window = false;
		SaveLog();
		exit(-1);
	}
	if (Loaded_Window)
		PRINT_LOG("[Info] Window successfully created");

	//- Создание контекста OpenGL
	contexteOpenGL = SDL_GL_CreateContext(window);

	if (contexteOpenGL == 0)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		SaveLog();
		exit(-1);
	}

	//- Инициализация GLEW
	GLenum initialisationGLEW(glewInit());

	//- Если инициализация завершилась с ошибкой:
	if (initialisationGLEW != GLEW_OK)
	{
		PRINT_LOG("[Error] GLEW initialization error:");
		//- Закрываем
		SDL_GL_DeleteContext(contexteOpenGL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		Loaded_GLEW = false;
		SaveLog();
		exit(-1);
	}
	if (Loaded_GLEW)
		PRINT_LOG("[Info] GLEW was successfully launched");
	
	//- Включаем Depth Buffer
	glEnable(GL_DEPTH_TEST);


	//- Основной цикл
	while (!WinСlosed)
	{
		//- Управление событиями
		SDL_WaitEvent(&evenements);

		if (evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			WinСlosed = true;

		//- Обновление Окна
		ME::Initialize::UpdateWindow();

		SDL_GL_SwapWindow(window);
	}
	if (WinСlosed)
		PRINT_LOG("[Info] Successfully completed the Motion Engine");

	//- Закрытие
	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(window);
	SDL_Quit();

	SaveLog();
	exit(0);
}

// ---------------------------------- //
// ---------- Обновление Окна ------- //
// ---------------------------------- //

void ME::Initialize::UpdateWindow()
{
	ME::pCube pCubeTest(2.0, "shaders/couleur3D.vme", "Shaders/couleur3D.fme");

	//- Матрицы проецирования и моделирования
	mat4 projection;
	mat4 modelview;

	projection = perspective(70.0, (double)w_width / w_height, 1.0, 100.0);

	//- Очишаем
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelview = mat4(1.0);
	modelview = lookAt(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));

	// Affichage du cube
	pCubeTest.Display(projection, modelview);
}

// ---------------------------------- //
// ---------- Сохранение лога ------- //
// ---------------------------------- //

void ME::Initialize::SaveLog()
{
	ME::Console::SaveInFile("Console.log");
}

// ---------------------------------- //