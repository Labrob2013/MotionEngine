#include "ME_pCube.h"

//- Проблема pCube
ME::pCube::pCube(float size, string const vertexShader, string const fragmentShader) : m_shader(vertexShader, fragmentShader)
{
	//- Загрузка шейдера
	m_shader.charger();


	//- Разделение размера
	size /= 2;


	//- Временные вершины
	float verticesTmp[] = { -size, -size, -size, size, -size, -size, size, size, -size,     // Face 1
		-size, -size, -size, -size, size, -size, size, size, -size,     // Face 1

		size, -size, size, size, -size, -size, size, size, -size,       // Face 2
		size, -size, size, size, size, size, size, size, -size,         // Face 2

		-size, -size, size, size, -size, size, size, -size, -size,      // Face 3
		-size, -size, size, -size, -size, -size, size, -size, -size,    // Face 3

		-size, -size, size, size, -size, size, size, size, size,        // Face 4
		-size, -size, size, -size, size, size, size, size, size,        // Face 4

		-size, -size, -size, -size, -size, size, -size, size, size,     // Face 5
		-size, -size, -size, -size, size, -size, -size, size, size,     // Face 5

		-size, size, size, size, size, size, size, size, -size,         // Face 6
		-size, size, size, -size, size, -size, size, size, -size };      // Face 6


	// Couleurs temporaires

	float couleursTmp[] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 1
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 1

		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 2
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 2

		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,           // Face 3
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,           // Face 3

		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 4
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,           // Face 4

		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 5
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,           // Face 5

		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,           // Face 6
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 };          // Face 6


	// Copie des valeurs dans les tableaux finaux

	for (int i(0); i < 108; i++)
	{
		m_vertices[i] = verticesTmp[i];
		m_colors[i] = couleursTmp[i];
	}
}


ME::pCube::~pCube()
{

}


// Mйthodes

void ME::pCube::Display(mat4 &projection, mat4 &modelview)
{
	//- Активация шейдера
	glUseProgram(m_shader.getProgramID());


	//- Отправка вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);


	//- Отправка цвета
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
	glEnableVertexAttribArray(1);


	//- Отправка матриц
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	//- Рендер
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//- Отключение таблиц
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	//- Отключаем шейдер
	glUseProgram(0);
}

