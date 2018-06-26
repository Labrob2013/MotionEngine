// ----------------------------------------- //
// ---------- // Примитив: Куб // ---------- //
// ----------------------------------------- //

#include "ME_Main.h"
#include "ME_Shaders.h"

namespace ME
{
	class pCube
	{
	public:
		pCube(float taille, string const vertexShader, string const fragmentShader);
		~pCube();

		void Display(mat4 &projection, mat4 &modelview);


	private:
		ME::Shaders m_shader;
		float m_vertices[108], m_colors[108];
	};
}

// ----------------------------------------- //