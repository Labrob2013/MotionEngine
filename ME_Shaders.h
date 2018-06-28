// ----------------------------------------------------------- //
// ---------- // Здесь все связанное с шейдерами // ---------- //
// ----------------------------------------------------------- //

#ifndef ME_SHADERS
#define ME_SHADERS

#include "ME_Main.h"

namespace ME
{
	class Shaders
	{
	public:

		Shaders();
		Shaders(Shaders const &shaderACopier);
		Shaders(std::string vertexSource, std::string fragmentSource);
		~Shaders();

		Shaders& operator=(Shaders const &shaderACopier);

		bool charger();
		bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
		GLuint getProgramID() const;


	private:
		GLuint m_vertexID, m_fragmentID, m_programID;
		string m_vertexSource, m_fragmentSource;
	};
}

#endif //- ME_SHADERS

// ----------------------------------------------------------- //