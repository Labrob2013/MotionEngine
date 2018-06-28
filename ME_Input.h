// -------------------------------------------------------- //
// ---------- // Работа с клавиатурой и мышью // ---------- //
// -------------------------------------------------------- //

#ifndef ME_INPUT
#define ME_INPUT

#include "ME_Main.h"

namespace ME
{
	class Input
	{
	public:
		Input();
		~Input();

		void updateEvenements();
		bool end() const;
		void showPointer(bool reponse) const;
		void capturePointer(bool reponse) const;

		bool getTouche(const SDL_Scancode touche) const;
		bool getMouseButton(const Uint8 bouton) const;
		bool mousemovement() const;

		int getX() const;
		int getY() const;

		int getXRel() const;
		int getYRel() const;


	private:
		SDL_Event m_evenements;
		bool m_touches[SDL_NUM_SCANCODES];
		bool m_getMouseButton[8];

		int m_x, m_y, m_xRel, m_yRel;
		bool m_terminer;
	};
}

#endif //- ME_INPUT

// -------------------------------------------------------- //