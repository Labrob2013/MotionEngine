#include "ME_Initialize.h"
#include "ME_Shaders.h"
#include "ME_Console.h"


// ---------------------------------------- //
// --------- Инициализация движка  -------- //
// ---------------------------------------- //

	//- Для создания окна
	SDL_Window* window(0);
	SDL_GLContext contexteOpenGL(0);

	//- Импорт шейдеров
	ME::Shaders shaderBasique("shaders/basique2D.vme", "shaders/basique2D.fme");


void ME::Initialize::InitEngine() {

	//- Задаем папку и файл логов
	ME::Console::SetFilename("Console.log");

	//- Включаем чтобы потом выключать если ошибки
	Loaded_SDL = true;
	Loaded_Window = true;
	Loaded_GLEW = true;

	ME::Console::Log(Console::None, "- - - - - - - - - - - - - - -");
	ME::Console::Log(Console::None, "- - - - Motion Engine - - - -");
	ME::Console::Log(Console::None, "- - - - - - - - - - - - - - -");
	ME::Console::Log(Console::None, "");
	ME::Console::Log(Console::Info, "Initialization Motion Engine");

	//- Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
		SDL_Quit();

		Loaded_SDL = false;
		exit(-1);
	}
	if (Loaded_SDL)
		ME::Console::Log(Console::Info, "SDL was successfully launched");


	//- Назначаем версию OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	//- Двойной буффер
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//- Создание окна
	window = SDL_CreateWindow("Тестирование двигателя Motion Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (window == 0)
	{
		ME::Console::Log(Console::Error, "Error creating window");
		SDL_Quit();

		Loaded_Window = false;
		exit(-1);
	}
	if (Loaded_Window)
		ME::Console::Log(Console::Info, "Window successfully created");

	//- Создание контекста OpenGL
	contexteOpenGL = SDL_GL_CreateContext(window);

	if (contexteOpenGL == 0)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();

		exit(-1);
	}


	//- Инициализация GLEW
	GLenum initialisationGLEW(glewInit());

	//- Если инициализация завершилась с ошибкой:
	if (initialisationGLEW != GLEW_OK)
	{
		ME::Console::Log(Console::Error, "GLEW initialization error: ");

		//- Закрываем
		SDL_GL_DeleteContext(contexteOpenGL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		Loaded_GLEW = false;
		exit(-1);
	}
	if (Loaded_GLEW)
		ME::Console::Log(Console::Info, "GLEW was successfully launched");

	//- Запуск шейдеров
	shaderBasique.charger();

	//- Основной цикл
	while (!WinСlosed)
	{
		//- Управление событиями
		SDL_WaitEvent(&evenements);

		if (evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			WinСlosed = true;

		//- Обновление Окна
		ME::Initialize::UpdateWindow();

		//- Обновление окна
		SDL_GL_SwapWindow(window);
	}
	if (WinСlosed)
		ME::Console::Log(Console::Info, "Successfully completed the Motion Engine");


	//- Закрытие
	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(window);
	SDL_Quit();

	exit(0);
}

// ---------------------------------- //
// ---------- Обновление Окна ------- //
// ---------------------------------- //

void ME::Initialize::UpdateWindow(){

	//- Вершины и координаты
	float vertices[] = { -0.5, -0.5, 0.0, 0.5, 0.5, -0.5 };

	//- Очистка экрана
	glClear(GL_COLOR_BUFFER_BIT);

	//- Активируем шейдеры
	glUseProgram(shaderBasique.getProgramID());

	//- Заполните и затем активируйте таблицу Vertex Attrib 0
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);


	//- Мы показываем треугольник
	glDrawArrays(GL_TRIANGLES, 0, 3);


	//- Отключите массив Vertex Attrib, потому что он вам больше не нужен
	glDisableVertexAttribArray(0);

	//- Отключаем шейдеры
	glUseProgram(0);
}