#include "ME_Input.h"

// --------------------------------------- //
// ---------- // Конструктор // ---------- //
// --------------------------------------- //

ME::Input::Input() : m_x(0), m_y(0), m_xRel(0), m_yRel(0), m_terminer(false)
{
	//- Инициализация таблицы m_touches[]
	for (int i(0); i < SDL_NUM_SCANCODES; i++)
		m_touches[i] = false;

	//- Инициализация таблицы m_m_getMouseButton[]
	for (int i(0); i < 8; i++)
		m_getMouseButton[i] = false;
}

// -------------------------------------- //
// ---------- // Деструктор // ---------- //
// -------------------------------------- //

ME::Input::~Input()
{

}


// ---------------------------------- //
// ---------- // Методы // ---------- //
// ---------------------------------- //

void ME::Input::updateEvenements()
{
	//- Чтобы избежать фиктивных движений мыши, относительные координаты сбрасываются
	m_xRel = 0;
	m_yRel = 0;


	//- Цикл
	while (SDL_PollEvent(&m_evenements))
	{
		//- Типы событий
		switch (m_evenements.type)
		{
			//- Случай нажатой клавиши

		case SDL_KEYDOWN:
			m_touches[m_evenements.key.keysym.scancode] = true;
			break;


			//- Случай с выпущенным ключом

		case SDL_KEYUP:
			m_touches[m_evenements.key.keysym.scancode] = false;
			break;


			//- Случай нажатия кнопки мыши

		case SDL_MOUSEBUTTONDOWN:

			m_getMouseButton[m_evenements.button.button] = true;

			break;


			//- При отпускании кнопки мыши

		case SDL_MOUSEBUTTONUP:

			m_getMouseButton[m_evenements.button.button] = false;

			break;


			//- Случай движения мыши

		case SDL_MOUSEMOTION:

			m_x = m_evenements.motion.x;
			m_y = m_evenements.motion.y;

			m_xRel = m_evenements.motion.xrel;
			m_yRel = m_evenements.motion.yrel;

			break;


			//- Случай закрытия окна

		case SDL_WINDOWEVENT:

			if (m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
				m_terminer = true;

			break;


		default:
			break;
		}
	}
}


bool ME::Input::end() const
{
	return m_terminer;
}


void ME::Input::showPointer(bool reponse) const
{
	if (reponse)
		SDL_ShowCursor(SDL_ENABLE);

	else
		SDL_ShowCursor(SDL_DISABLE);
}


void ME::Input::capturePointer(bool reponse) const
{
	if (reponse)
		SDL_SetRelativeMouseMode(SDL_TRUE);

	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

//- Получить
bool ME::Input::getTouche(const SDL_Scancode touche) const
{
	return m_touches[touche];
}


bool ME::Input::getMouseButton(const Uint8 bouton) const
{
	return m_getMouseButton[bouton];
}


bool ME::Input::mousemovement() const
{
	if (m_xRel == 0 && m_yRel == 0)
		return false;

	else
		return true;
}

// ------------------------------------------------- //
// ---------- // Получить относительно // ---------- //
// ---------- // Позиции курсора       // ---------- //
// ------------------------------------------------- //

	int ME::Input::getX() const
	{	 return m_x;	}

	int ME::Input::getY() const
	{	 return m_y;	}

	int ME::Input::getXRel() const
	{	 return m_xRel;		}

	int ME::Input::getYRel() const
	{	 return m_yRel;		}

// ------------------------------------------------- //