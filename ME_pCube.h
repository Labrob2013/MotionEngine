// ----------------------------------------- //
// ---------- // Примитив: Куб // ---------- //
// ----------------------------------------- //

#ifndef ME_PCUBE
#define ME_PCUBE

#include "ME_Main.h"
#include "ME_Shaders.h"
#include "ME_Textures.h"

namespace ME {
	class pCube
	{
	public:

		//- Тип куба (Без текстуры, с текстурой)
		enum Type  { None, Textured };

		//- Инициализация и загрузка текстуры
		pCube(float cX, float cY, float cZ,
			string const vertexShader, string const fragmentShader, string const texture);

		~pCube();

		//- VBO - Загрузка
		void load();

		//- VBO - Обновление
		void ME::pCube::loadUpdate(void *donnees, int tailleBytes, int decalage);

		//- Отображение
		void Display(Type type, mat4 &projection, mat4 &modelview);

	protected:
		ME::Shaders m_shader;
		float m_vertices[108], m_colors[108];

		ME::Textures m_texture;
		float m_coordTexture[72];

		//- VBO
		GLuint m_vboID;
		int m_SizeVerticesBytes;
		int m_SizeColorsBytes;
		int m_SizeCoordTextureBytes;

		//- VAO
		GLuint m_vaoID;
	};
}

#endif //- ME_PCUBE

// ----------------------------------------- //