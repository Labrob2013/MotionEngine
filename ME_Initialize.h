// ---------------------------------------------------------- //
// ---------- // Инициализация всех компонентов // ---------- //
// ---------------------------------------------------------- //

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


		//- SDL
		int w_width, w_height;

	private:
		//- Для проверки загружены ли?
			bool Loaded_SDL = false;
			bool Loaded_Window = false;
			bool Loaded_GLEW = false;

		//- SDL
			//- Основные
			SDL_Event evenements;
			SDL_Window* window;
			SDL_GLContext contexteOpenGL;

			//- Отображение проекции и предметов
			mat4 projection, modelview;
	};
}

// ---------------------------------------------------------- //