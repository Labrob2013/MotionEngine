// ------------------------------------------------------------ //
// ---------- // Здесь все связанное с текстурами // ---------- //
// ------------------------------------------------------------ //

#ifndef ME_TEXTURES
#define ME_TEXTURES

#include "ME_Main.h"

namespace ME {
	class Textures
	{
	public:

		Textures();
		Textures(Textures const &textureCopy);
		Textures(string imagefile);
		~Textures();

		Textures& operator=(Textures const &textureCopy);
		bool charger();
		SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

		GLuint getID() const;
		void setFileImage(const string &imagefile);

	private:
		GLuint m_id;
		string m_FileImage;
	};
}

#endif //- ME_TEXTURES

// ------------------------------------------------------------ //