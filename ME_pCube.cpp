#include "ME_pCube.h"

ME::pCube::pCube(float cX, float cY, float cZ, string const vertexShader, string const fragmentShader, string const texture) :
m_shader(vertexShader, fragmentShader), m_texture(texture)
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


ME::pCube::~pCube()
{

}


void ME::pCube::Display(Type type, mat4 &projection, mat4 &modelview)
{
	//- Активация шейдера
	glUseProgram(m_shader.getProgramID());


	//- Отправка вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);
	
	//- Отправка цвета
	if (Type::None == type)
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
		glEnableVertexAttribArray(1);
	}

	//- Отправка текстуры
	if (Type::Textured == type)
	{
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
		glEnableVertexAttribArray(2);
	}

	//- Отправка матриц
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	if (Type::Textured == type)
		glBindTexture(GL_TEXTURE_2D, m_texture.getID());

	//- Рендер
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	if (Type::Textured == type)
		glBindTexture(GL_TEXTURE_2D, 0);

	//- Отключение таблиц
	if (Type::Textured == type)
		glDisableVertexAttribArray(2);

	if (Type::None == type)
		glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(0);

	//- Отключаем шейдер
	glUseProgram(0);
}

