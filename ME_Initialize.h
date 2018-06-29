// ---------------------------------------------------------- //
// ---------- // Инициализация всех компонентов // ---------- //
// ---------------------------------------------------------- //

#ifndef ME_INITIALIZE
#define ME_INITIALIZE

#include "ME_Main.h"

namespace ME
{
	class Initialize
	{
	public:
		//- Инициализация
		void InitEngine();

		//- Обновление окна
		void UpdateWindow();

		//- Сохранение лога
		void SaveLog();

		//- Вывод времени
		string GetTime();

		//- Вывод времени в м/c
		double GetMilliseconds(clock_t ticks);

		//- FPS
		void GetFPS(clock_t endFrame, clock_t beginFrame);

		//- Проверка на существованеи файла
		bool GetFileExist(const string& filename);

		//- SDL
		int w_width, w_height;
		SDL_Window* window;
		SDL_Renderer *render;
		SDL_Surface *gui_fps = NULL, *gui_texture = NULL;

		//- FPS
		clock_t FPS_deltaTime = 0;
		unsigned int FPS_frames = 0;
		double FPS_frameRate = 60, FPS_averageFrameTimeMS = 33.333;
		char FPS[20];

	private:
		//- Для проверки загружены ли?
			bool Loaded_SDL = false;
			bool Loaded_SDL_TTF = false;
			bool Loaded_Window = false;
			bool Loaded_GLEW = false;

		//- SDL
			//- Основные
			SDL_Event evenements;
			
			SDL_GLContext contexteOpenGL;

			//- Отображение проекции и предметов
			mat4 projection, modelview;

		//- Время
			time_t t;
			tm* t_now;
	};
}

#endif //- ME_INITIALIZE

// ---------------------------------------------------------- //