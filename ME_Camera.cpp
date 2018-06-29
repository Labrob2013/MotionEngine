#include "ME_Camera.h"

ME::Camera::Camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), m_position(), m_targetPoint(), m_sensitivity(0.0), m_speed(0.0)
{

}

ME::Camera::Camera(vec3 position, vec3 targetPoint, vec3 axeVertical, float sensitivity, float speed) : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(axeVertical), m_deplacementLateral(), m_position(position), m_targetPoint(targetPoint), m_sensitivity(sensitivity), m_speed(speed)
{
	//- Обновление целевой точки
	setTargetPoint(targetPoint);
}


ME::Camera::~Camera()
{

}


void ME::Camera::direct(int xRel, int yRel)
{
	//- Восстановление углов
	m_phi += -yRel * m_sensitivity;
	m_theta += -xRel * m_sensitivity;


	//- Ограничение угла phi
	if (m_phi > 89.0)
		m_phi = 89.0;

	else if (m_phi < -89.0)
		m_phi = -89.0;


	//- Преобразование углов в радиан
	float phiRadian = m_phi * M_PI / 180;
	float thetaRadian = m_theta * M_PI / 180;


	//- Если вертикальная ось является осью X
	if (m_axeVertical.x == 1.0)
	{
		//- Расчет сферических координат
		m_orientation.x = sin(phiRadian);
		m_orientation.y = cos(phiRadian) * cos(thetaRadian);
		m_orientation.z = cos(phiRadian) * sin(thetaRadian);
	}


	//- Если это ось Y
	else if (m_axeVertical.y == 1.0)
	{
		//- Расчет сферических координат
		m_orientation.x = cos(phiRadian) * sin(thetaRadian);
		m_orientation.y = sin(phiRadian);
		m_orientation.z = cos(phiRadian) * cos(thetaRadian);
	}


	//- В противном случае это ось Z
	else
	{
		//- Расчет сферических координат
		m_orientation.x = cos(phiRadian) * cos(thetaRadian);
		m_orientation.y = cos(phiRadian) * sin(thetaRadian);
		m_orientation.z = sin(phiRadian);
	}


	//- Расчет из нормального
	m_deplacementLateral = cross(m_axeVertical, m_orientation);
	m_deplacementLateral = normalize(m_deplacementLateral);


	//- Расчет целевой точки для OpenGL
	m_targetPoint = m_position + m_orientation;
}


void ME::Camera::move(Input const &input)
{
	//- Управление ориентацией
	if (input.mousemovement())
		direct(input.getXRel(), input.getYRel());


	//- Расширенная камера
	if (input.getTouche(SDL_SCANCODE_UP))
	{
		m_position = m_position + m_orientation * m_speed;
		m_targetPoint = m_position + m_orientation;
	}


	//- Задняя панель камеры
	if (input.getTouche(SDL_SCANCODE_DOWN))
	{
		m_position = m_position - m_orientation * m_speed;
		m_targetPoint = m_position + m_orientation;
	}


	//- Переместить влево
	if (input.getTouche(SDL_SCANCODE_LEFT))
	{
		m_position = m_position + m_deplacementLateral * m_speed;
		m_targetPoint = m_position + m_orientation;
	}


	//- Переместить вправо
	if (input.getTouche(SDL_SCANCODE_RIGHT))
	{
		m_position = m_position - m_deplacementLateral * m_speed;
		m_targetPoint = m_position + m_orientation;
	}
}


void ME::Camera::lookAt(mat4 &modelview)
{
	//- Обновление представления в матрице
	modelview = glm::lookAt(m_position, m_targetPoint, m_axeVertical);
}


void ME::Camera::setTargetPoint(vec3 targetPoint)
{
	//- Вычисление вектора ориентации
	m_orientation = m_targetPoint - m_position;
	m_orientation = normalize(m_orientation);


	//- Если вертикальная ось является осью X
	if (m_axeVertical.x == 1.0)
	{
		//- Расчет углов
		m_phi = asin(m_orientation.x);
		m_theta = acos(m_orientation.y / cos(m_phi));

		if (m_orientation.y < 0)
			m_theta *= -1;
	}


	//- Если это ось Y
	else if (m_axeVertical.y == 1.0)
	{
		//- Расчет углов
		m_phi = asin(m_orientation.y);
		m_theta = acos(m_orientation.z / cos(m_phi));

		if (m_orientation.z < 0)
			m_theta *= -1;
	}


	//- В противном случае это ось Z
	else
	{
		//- Расчет углов
		m_phi = asin(m_orientation.x);
		m_theta = acos(m_orientation.z / cos(m_phi));

		if (m_orientation.z < 0)
			m_theta *= -1;
	}


	//- Преобразование в градусы
	m_phi = m_phi * 180 / M_PI;
	m_theta = m_theta * 180 / M_PI;
}


void ME::Camera::setPosition(vec3 position)
{
	//- Обновить позицию
	m_position = position;


	//- Обновление целевой точки
	m_targetPoint = m_position + m_orientation;
}


float ME::Camera::getSensitivity() const
{
	return m_speed;
}


float ME::Camera::getSpeed() const
{
	return m_speed;
}


void ME::Camera::setSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}


void ME::Camera::setSpeed(float speed)
{
	m_sensitivity = speed;
}
