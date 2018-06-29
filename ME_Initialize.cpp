#include "ME_Initialize.h"
#include "ME_Console.h"
#include "ME_Input.h"
#include "ME_pCube.h"
#include "ME_Camera.h"

// -------------------------------------------- //
// -------- // Инициализация движка // -------- //
// -------------------------------------------- //

//- Создаем объект для работы с клавиатурой и мышью
ME::Input m_input;

void ME::Initialize::InitEngine() {

	//- Включаем чтобы потом выключать если ошибки
	Loaded_SDL = true, Loaded_SDL_TTF = true, Loaded_Window = true, Loaded_GLEW = true;

	PRINT_LOG(" # - - - - - - - - - - - - - - - - - - - - - - - # ");
	PRINT_LOG(" # - - - - - - - - Motion Engine - - - - - - - - # ");
	PRINT_LOG(" # - - - - - - - - - - - - - - - - - - - - - - - # ");
	PRINT_LOG("");
	PRINT_LOG(GetTime() << "[Info] Initialization Motion Engine");

	//- Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PRINT_LOG(GetTime() << "[ERROR] SDL initialization error: " << SDL_GetError());
		SDL_Quit();

		Loaded_SDL = false;
		SaveLog();
		exit(-1);
	}
	if (Loaded_SDL)
		PRINT_LOG(GetTime() << "[Info] SDL was successfully launched");

	if (TTF_Init() == -1)
	{
		PRINT_LOG(GetTime() << "[ERROR] Initialization error of SDL_TTF: " << TTF_GetError());
		Loaded_SDL_TTF = false;

		exit(EXIT_FAILURE);
		exit(-1);
	}
	if (Loaded_SDL_TTF)
		PRINT_LOG(GetTime() << "[Info] Successfully started font resources");


	//- Назначаем версию OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	//- Двойной буффер
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//- Создание окна
	window = SDL_CreateWindow("Тестирование двигателя Motion Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	/* Create a Render */
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == 0) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		exit(-1);
	}


	if (window == 0)
	{
		PRINT_LOG(GetTime() << "[Error] Error creating window");
		SDL_Quit();

		Loaded_Window = false;
		SaveLog();
		exit(-1);
	}
	if (Loaded_Window)
		PRINT_LOG(GetTime() << "[Info] Window successfully created");

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
		PRINT_LOG(GetTime() << "[Error] GLEW initialization error");
		//- Закрываем
		SDL_GL_DeleteContext(contexteOpenGL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		Loaded_GLEW = false;
		SaveLog();
		exit(-1);
	}
	if (Loaded_GLEW)
		PRINT_LOG(GetTime() << "[Info] GLEW was successfully launched");

	//- Включаем Depth Buffer
	glEnable(GL_DEPTH_TEST);

	//- Вертикальная синхронизация
	SDL_GL_SetSwapInterval(1);

	PRINT_LOG(GetTime() << "[Info] Successfully started input devices");

	//- Основной цикл
	ME::Initialize::UpdateWindow();


	if (m_input.end())
		PRINT_LOG(GetTime() << "[Info] Successfully completed the Motion Engine");

	//- Закрытие
	TTF_Quit();
	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(window);
	SDL_Quit();

	SaveLog();
	exit(0);
}

// --------------------------------------- //
// -------- // Обновление Окна // -------- //
// --------------------------------------- //

void ME::Initialize::UpdateWindow()
{
	//- Создание объект
	ME::pCube pCube01(2, 4, 1, "shaders/textured.vme", "shaders/textured.fme", "Textures/01.jpg");
	ME::pCube pCube02(2, 4, 1, "shaders/textured.vme", "shaders/textured.fme", "Textures/02.jpg");

	ME::pCube pCube03(5, 0.01, 5, "shaders/textured.vme", "shaders/textured.fme", "Textures/03.jpg");
	ME::pCube pCube04(5, 0.01, 5, "shaders/textured.vme", "shaders/textured.fme", "Textures/03.jpg");
	ME::pCube pCube05(5, 0.01, 5, "shaders/textured.vme", "shaders/textured.fme", "Textures/03.jpg");

	ME::Camera Camera(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0), 0.5, 0.2);


	/*
	# Для текста FPS (В РАЗРАБОТКЕ)
	
	if (!GetFileExist("shaders/font.ttf")) { exit(-1); }
	//TTF_Font* font = TTF_OpenFont("shaders/font.ttf", 15);
	//gui_texture = IMG_Load("textures/04.png");*/

	//- Обновление окна
	while (!m_input.end())
	{
		/*
		# Для текста FPS (В РАЗРАБОТКЕ)

		SDL_Rect tRect = { 10, 5, 50, 50 };
		SDL_Color color{ 0, 255, 0 };
		SDL_Color bg{ 0, 0, 0 };
		gui_fps = TTF_RenderText_Shaded(font, FPS, color, bg);
		SDL_BlitSurface(gui_texture, NULL, SDL_GetWindowSurface(window), &tRect);
		SDL_BlitSurface(gui_fps, NULL, SDL_GetWindowSurface(window), &tRect);
		SDL_UpdateWindowSurface(window);*/

		clock_t beginFrame = clock();

		//- Управление событиями
		m_input.updateEvenements();

		if (m_input.getTouche(SDL_SCANCODE_ESCAPE))
			break;

		//- Матрицы проецирования и моделирования
		mat4 projection;
		mat4 modelview;

		projection = perspective(70.0, (double)w_width / w_height, 1.0, 100.0);

		//- Очишаем
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelview = mat4(1.0);
		Camera.move(m_input);
		Camera.lookAt(modelview);

		//- Сохраняем
		mat4 save_Modelview = modelview;

		// -------------------------------------- //
		// -------- // Создаем объекты // ------- //
		// -------------------------------------- //

			//## 1
				save_Modelview = modelview;

				//- Позиция объекта
				modelview = translate(modelview, vec3(0, 0, 0));

				//- Отображение объекта
				pCube01.Display(pCube01.Textured, projection, modelview);

				//- VBO и VAO
				pCube01.load();


				//- Вращение объекта
				modelview = rotate(modelview, 0.0f, vec3(0.0f, 0.0f, 1.0f));

				modelview = save_Modelview;
			//

			//## 2
				save_Modelview = modelview;

				//- Позиция объекта
				modelview = translate(modelview, vec3(0, 0, 8));

				//- Отображение объекта
				pCube02.Display(pCube02.Textured, projection, modelview);

				//- VBO и VAO
				pCube02.load();

				//- Вращение объекта
				modelview = rotate(modelview, 0.0f, vec3(0.0f, 0.0f, 1.0f));

				modelview = save_Modelview;
			//

			//## 3
				save_Modelview = modelview;

				//- Позиция объекта
				modelview = translate(modelview, vec3(0, -2, 0));

				//- Отображение объекта
				pCube03.Display(pCube03.Textured, projection, modelview);

				//- VBO и VAO
				pCube03.load();

				//- Вращение объекта
				modelview = rotate(modelview, 0.0f, vec3(0.0f, 0.0f, 1.0f));

				modelview = save_Modelview;
			//

			//## 4
				save_Modelview = modelview;

				//- Позиция объекта
				modelview = translate(modelview, vec3(0, -2, 5));

				//- Отображение объекта
				pCube04.Display(pCube04.Textured, projection, modelview);

				//- VBO и VAO
				pCube04.load();

				//- Вращение объекта
				modelview = rotate(modelview, 0.0f, vec3(0.0f, 0.0f, 1.0f));

				modelview = save_Modelview;
			//

			//## 5
				save_Modelview = modelview;

				//- Позиция объекта
				modelview = translate(modelview, vec3(5, -2, 0));

				//- Отображение объекта
				pCube05.Display(pCube05.Textured, projection, modelview);

				//- VBO и VAO
				pCube05.load();

				//- Вращение объекта
				modelview = rotate(modelview, 0.0f, vec3(0.0f, 0.0f, 1.0f));

				modelview = save_Modelview;
			//

		//

		//- Возвращаем вид
		modelview = save_Modelview;
		SDL_GL_SwapWindow(window);

		//- Получаем FPS
			clock_t endFrame = clock();

			GetFPS(endFrame, beginFrame);
		//
	}
}

// -------------------------------------- //
// -------- // Сохранение лога // ------- //
// -------------------------------------- //

void ME::Initialize::SaveLog()
{
	ME::Console::SaveInFile("Console.log");
}

// ---------------------------------------- //
// -------- // Получение времени // ------- //
// ---------------------------------------- //

string ME::Initialize::GetTime()
{
	//- Пример вывода: [15:50:02]
	time(&t);
	t_now = localtime(&t);

	stringstream stream;
	stream << "# " << t_now->tm_hour << ":" << t_now->tm_min << ":" << t_now->tm_sec << " | ";
	
	return stream.str();
}

// ---------------------------------------------- //
// -------- // Получение времени в м/c // ------- //
// ---------------------------------------------- //

double ME::Initialize::GetMilliseconds(clock_t ticks)
{
	return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
}

// ------------------------------------ //
// -------- // Получение FPS // ------- //
// ------------------------------------ //

void ME::Initialize::GetFPS(clock_t endFrame, clock_t beginFrame)
{
	FPS_deltaTime += endFrame - beginFrame;
	FPS_frames++;

	if (GetMilliseconds(FPS_deltaTime) > 1000.0){
		FPS_frameRate = (double)FPS_frames*0.5 + FPS_frameRate*0.5;
		FPS_frames = 0;
		FPS_deltaTime -= CLOCKS_PER_SEC;
		FPS_averageFrameTimeMS = 1000.0 / (FPS_frameRate == 0 ? 0.001 : FPS_frameRate);

		PRINT_LOG(GetTime() << "[Info] FPS: " << FPS_averageFrameTimeMS);

		sprintf(FPS, "FPS: %f ", FPS_averageFrameTimeMS);
	}
}

// ------------------------------------------------------ //
// -------- // Проверка файла на существование // ------- //
// ------------------------------------------------------ //

bool ME::Initialize::GetFileExist(const string& filename)
{
	if (FILE *file = fopen(filename.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

// ------------------------------------------------------ //