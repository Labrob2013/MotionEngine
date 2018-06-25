// ----------------------------------------------------------- //
// ---------- // Здесь все связанное с шейдерами // ---------- //
// ----------------------------------------------------------- //

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
		
		GLuint m_vertexID;
		GLuint m_fragmentID;
		GLuint m_programID;

		std::string m_vertexSource;
		std::string m_fragmentSource;
	};
}

// ----------------------------------------------------------- //