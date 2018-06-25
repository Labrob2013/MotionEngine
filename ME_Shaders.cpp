#include "ME_Shaders.h"
#include "ME_Console.h"


//- Конструктор и Деструктор
ME::Shaders::Shaders() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{
}


ME::Shaders::Shaders(Shaders const &shaderACopier)
{
	m_vertexSource = shaderACopier.m_vertexSource;
	m_fragmentSource = shaderACopier.m_fragmentSource;


	//- Загрузка нового шейдера
	charger();
}


ME::Shaders::Shaders(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}


ME::Shaders::~Shaders()
{

	//- Деструктор шейдера
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_programID);
}


//- Методы
ME::Shaders& ME::Shaders::operator=(Shaders const &shaderACopier)
{
	m_vertexSource = shaderACopier.m_vertexSource;
	m_fragmentSource = shaderACopier.m_fragmentSource;

	//- Загрузка нового шейдера
	charger();

	return *this;
}


bool ME::Shaders::charger()
{

	//- Уничтожение старого шейдера
	if (glIsShader(m_vertexID) == GL_TRUE)
		glDeleteShader(m_vertexID);

	if (glIsShader(m_fragmentID) == GL_TRUE)
		glDeleteShader(m_fragmentID);

	if (glIsProgram(m_programID) == GL_TRUE)
		glDeleteProgram(m_programID);


	//- Компиляция шейдеров
	if (!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
		return false;

	if (!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
		return false;


	m_programID = glCreateProgram();


	//- Ассоциация шейдеров
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);


	glBindAttribLocation(m_programID, 0, "in_Vertex");
	glBindAttribLocation(m_programID, 1, "in_Color");
	glBindAttribLocation(m_programID, 2, "in_TexCoord0");

	glLinkProgram(m_programID);


	//- Проверка линковки
	GLint erreurLink(0);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);


	//- Если произошла ошибка
	if (erreurLink != GL_TRUE)
	{
		//- Восстановление размера ошибки
		GLint tailleErreur(0);
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);


		//- Распределение памяти
		char *erreur = new char[tailleErreur + 1];

		glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		//- Отображение ошибок
		std::cout << erreur << std::endl;

		delete[] erreur;
		glDeleteProgram(m_programID);

		return false;
	}


	//- В противном случае все прошло хорошо
	else
		return true;
}

bool ME::Shaders::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
	//- Создание шейдера
	shader = glCreateShader(type);

	//- Шейдерная проверка
	if (shader == 0)
	{
		ME::Console::Log(Console::Error, "An error of the shader type that does not exist");
		return false;
	}

	//- Чтение потока
	std::ifstream fichier(fichierSource.c_str());


	//- Открытие файла
	if (!fichier)
	{
		ME::Console::Log(Console::Error, "Error File: " + fichierSource + " could not be found");
		glDeleteShader(shader);

		return false;
	}


	//- Строки для чтения исходного кода
	std::string ligne;
	std::string codeSource;


	//- Чтение
	while (getline(fichier, ligne))
		codeSource += ligne + '\n';


	//- Закрытие файла
	fichier.close();


	//- Восстановление строки C исходного кода
	const GLchar* chaineCodeSource = codeSource.c_str();


	//- Отправка исходного кода в шейдер
	glShaderSource(shader, 1, &chaineCodeSource, 0);


	//- Компиляция шейдера
	glCompileShader(shader);


	//- Проверка компиляции
	GLint erreurCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);


	//- Если произошла ошибка
	if (erreurCompilation != GL_TRUE)
	{
		//- Восстановление размера ошибки
		GLint tailleErreur(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

		//- Распределение памяти
		char *erreur = new char[tailleErreur + 1];

		glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		std::cout << erreur << std::endl;

		delete[] erreur;
		glDeleteShader(shader);

		return false;
	}


	//- В противном случае все прошло хорошо
	else
		return true;
}


//- Получение идентификатора
GLuint ME::Shaders::getProgramID() const
{
	return m_programID;
}
