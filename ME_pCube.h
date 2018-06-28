// ----------------------------------------- //
// ---------- // ��������: ��� // ---------- //
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

		//- ��� ���� (��� ��������, � ���������)
		enum Type  { None, Textured };

		//- ������������� � �������� ��������
		pCube(float cX, float cY, float cZ,
			string const vertexShader, string const fragmentShader, string const texture);

		~pCube();

		//- �����������
		void Display(Type type, mat4 &projection, mat4 &modelview);

	protected:
		ME::Shaders m_shader;
		float m_vertices[108], m_colors[108];

		ME::Textures m_texture;
		float m_coordTexture[72];
	};
}

#endif //- ME_PCUBE

// ----------------------------------------- //