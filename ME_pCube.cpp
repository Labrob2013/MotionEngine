#include "ME_pCube.h"
#include "ME_Console.h"
#include "ME_Initialize.h"


/*

	*** VBO

	- GL_STATIC_DRAW : Для очень маленьких обновленных данных

	- GL_DYNAMIC_DRAW : Для частого обновления данных (несколько раз в секунду, но не для каждого кадра)

	- GL_STREAM_DRAW : Для данных, обновляемых все время (на каждом кадре на этот раз)


*/


//- Макрос, полезный для VBO
#ifndef BUFFER_OFFSET
	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif


ME::pCube::pCube(float cX, float cY, float cZ, string const vertexShader, string const fragmentShader, string const texture) :

//- Shader
m_shader(vertexShader, fragmentShader),

//- Texture
m_texture(texture), 

//- VBO
m_SizeVerticesBytes(108 * sizeof(float)),
m_SizeColorsBytes(108 * sizeof(float)),
m_SizeCoordTextureBytes(72 * sizeof(float)),

//- VAO
m_vaoID(0)
{
	//- Создание текстуры
		
		//- Проверка: Если пусто то будет перекрашен в цвет
		if (texture != "")
			m_texture.charger(); //- Загрузка текстуры

		//- Временные координаты текстуры
		float coordTextureTmp[] = {
			0, 0, 1, 0, 1, 1,     // Face 1		
			0, 0, 0, 1, 1, 1,     // Face 1

			0, 0, 1, 0, 1, 1,     // Face 2
			0, 0, 0, 1, 1, 1,     // Face 2

			0, 0, 1, 0, 1, 1,     // Face 3
			0, 0, 0, 1, 1, 1,     // Face 3

			0, 0, 1, 0, 1, 1,     // Face 4
			0, 0, 0, 1, 1, 1,     // Face 4

			0, 0, 1, 0, 1, 1,     // Face 5
			0, 0, 0, 1, 1, 1,     // Face 5

			0, 0, 1, 0, 1, 1,     // Face 6
			0, 0, 0, 1, 1, 1 };   // Face 6


		//- Копировать значения в итоговую таблицу
		if (texture != "")
			for (int i(0); i < 72; i++)
				m_coordTexture[i] = coordTextureTmp[i];

	//- Создание куба

		//- Загрузка шейдера
		m_shader.charger();


		//- Разделение размера
		cX /= 2; cY /= 2; cZ /= 2;


		//- Временные вершины
		float verticesTmp[] = {
			-cX, -cY, -cZ, cX, -cY, -cZ, cX, cY, -cZ,     // Face 1
			-cX, -cY, -cZ, -cX, cY, -cZ, cX, cY, -cZ,     // Face 1

			cX, -cY, cZ, cX, -cY, -cZ, cX, cY, -cZ,       // Face 2
			cX, -cY, cZ, cX, cY, cZ, cX, cY, -cZ,         // Face 2

			-cX, -cY, cZ, cX, -cY, cZ, cX, -cY, -cZ,      // Face 3
			-cX, -cY, cZ, -cX, -cY, -cZ, cX, -cY, -cZ,    // Face 3

			-cX, -cY, cZ, cX, -cY, cZ, cX, cY, cZ,        // Face 4
			-cX, -cY, cZ, -cX, cY, cZ, cX, cY, cZ,        // Face 4

			-cX, -cY, -cZ, -cX, -cY, cZ, -cX, cY, cZ,     // Face 5
			-cX, -cY, -cZ, -cX, cY, -cZ, -cX, cY, cZ,     // Face 5

			-cX, cY, cZ, cX, cY, cZ, cX, cY, -cZ,         // Face 6
			-cX, cY, cZ, -cX, cY, -cZ, cX, cY, -cZ	      // Face 6
		 };


		//- Цветные позиции (Цвет Дымчато-белый)
		float couleursTmp[] = {
			0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,			// Face 1
			0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,			// Face 1

			0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,			// Face 2
			0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,			// Face 2

			1, 1, 1, 1, 1, 1, 1, 1, 1,								// Face 3
			1, 1, 1, 1, 1, 1, 1, 1, 1,								// Face 3

			0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,			// Face 4
			0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7,			// Face 4

			0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,			// Face 5
			0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,			// Face 5

			1, 1, 1, 1, 1, 1, 1, 1, 1,								// Face 6
			1, 1, 1, 1, 1, 1, 1, 1, 1								// Face 6
		};		


		//- Копировать значения в финальные таблицы
		for (int i(0); i < 108; i++)
		{
			m_vertices[i] = verticesTmp[i];
			m_colors[i] = couleursTmp[i];
		}
}

//- Запуск VBO и VAO
void ME::pCube::load()
{
	//- VBO
		//- Уничтожение возможного старого VBO
		if (glIsBuffer(m_vboID) == GL_TRUE)
			glDeleteBuffers(1, &m_vboID);


		//- Генерация идентификатора
		glGenBuffers(1, &m_vboID);


		//- Блокировка VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


			//- Распределение памяти
			glBufferData(GL_ARRAY_BUFFER, m_SizeVerticesBytes + m_SizeColorsBytes, 0, GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, m_SizeVerticesBytes + m_SizeCoordTextureBytes, 0, GL_STATIC_DRAW);


			//- Передача данных
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_SizeVerticesBytes, m_vertices);

			glBufferSubData(GL_ARRAY_BUFFER, m_SizeVerticesBytes, m_SizeColorsBytes, m_colors);
			glBufferSubData(GL_ARRAY_BUFFER, m_SizeVerticesBytes, m_SizeCoordTextureBytes, m_coordTexture);


		//- Разблокировка VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	//- VAO
		//- Уничтожение старого VAO
		if (glIsVertexArray(m_vaoID) == GL_TRUE)
			glDeleteVertexArrays(1, &m_vaoID);

		//- Генерация идентификатора VAO
		glGenVertexArrays(1, &m_vaoID);

		//- Блокировка VAO
		glBindVertexArray(m_vaoID);


			//- Блокировка VBO
			glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


				//- Доступ к вершинам в видеопамяти
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(0);

				//- Доступ к цветам в видеопамяти
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_SizeVerticesBytes));
				glEnableVertexAttribArray(1);

				//- Доступ к текстурам в видеопамяти
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_SizeVerticesBytes));
				glEnableVertexAttribArray(2);


			//- Разблокировка VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);


		//- Разблокировка VAO
		glBindVertexArray(0);
}

//- Обновление VBO
void ME::pCube::loadUpdate(void *data, int sizeBytes, int lag)
{
	//- Блокировка VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


	//- Восстановление адреса VBO
	void *VBOaddress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);


	//- Если возвращаемый адрес равен нулю, то мы прекращаем передачу
	if (VBOaddress == NULL)
	{
		ME::Initialize Init;
		PRINT_LOG(Init.GetTime() << "[Info] Error in VBO recovery");

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return;
	}


	//- Обновление данных
	memcpy((char*)VBOaddress + lag, data, sizeBytes);


	//- Отказ от указателя
	glUnmapBuffer(GL_ARRAY_BUFFER);
	VBOaddress = 0;


	//- Разблокировка VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ME::pCube::~pCube()
{
	//- Уничтожение VBO
	glDeleteBuffers(1, &m_vboID);

	//- Уничтожение VAO
	glDeleteVertexArrays(1, &m_vaoID);
}


void ME::pCube::Display(Type type, mat4 &projection, mat4 &modelview)
{
	//- Активация шейдера
	glUseProgram(m_shader.getProgramID());

	// Verrouillage du VAO

	glBindVertexArray(m_vaoID);

		//- Отправка матриц
		glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

		if (Type::Textured == type)
			glBindTexture(GL_TEXTURE_2D, m_texture.getID());

		//- Рендер
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		if (Type::Textured == type)
			glBindTexture(GL_TEXTURE_2D, 0);

	//- Разблокировка VAO
	glBindVertexArray(0);

	//- Отключаем шейдер
	glUseProgram(0);
}

