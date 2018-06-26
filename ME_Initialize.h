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
		SDL_Event evenements;

		//- Закрыто ли окно?
		bool WinСlosed = false;
	};
}

// ---------------------------------------------------------- //