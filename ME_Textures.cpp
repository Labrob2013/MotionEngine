#include "ME_Textures.h"
#include "ME_Initialize.h"
#include "ME_Console.h"


ME::Textures::Textures(Textures const &textureCopy)
{
	//- Копируем текстуры
	m_FileImage = textureCopy.m_FileImage;
	charger();
}


ME::Textures::Textures(string imagefile) : m_id(0), m_FileImage(imagefile)
{

}


ME::Textures::~Textures()
{
	//- Удаление текстуры
	glDeleteTextures(1, &m_id);
}


//- Методы
ME::Textures& ME::Textures::operator=(Textures const &textureCopy)
{
	//- Копия текстуры
	m_FileImage = textureCopy.m_FileImage;
	charger();

	return *this;
}


bool ME::Textures::charger()
{
	//- Загрузка изображения на поверхность SDL
	SDL_Surface *imageSDL = IMG_Load(m_FileImage.c_str());

	if (imageSDL == 0)
	{
		ME::Initialize Init;
		PRINT_LOG(Init.GetTime() << "[ERROR] " << SDL_GetError());
		return false;
	}


	//- Обращение изображения
	SDL_Surface *imageInversee = inverserPixels(imageSDL);
	SDL_FreeSurface(imageSDL);


	//- Уничтожение любой старой текстуры
	if (glIsTexture(m_id) == GL_TRUE)
		glDeleteTextures(1, &m_id);


	//- Генерация идентификатора
	glGenTextures(1, &m_id);


	//- Фиксируем текстуру
	glBindTexture(GL_TEXTURE_2D, m_id);


	//- Формат изображения
	GLenum formatInterne(0), format(0);


	//- Определение формата и внутреннего формата для трехкомпонентных изображений
	if (imageInversee->format->BytesPerPixel == 3)
	{
		//- Внутренний формат
		formatInterne = GL_RGB;

		//- Формат
		if (imageInversee->format->Rmask == 0xff)
			format = GL_RGB;
		else 
			format = GL_BGR;
	}


	//- Определение формата и внутреннего формата для 4-компонентных изображений
	else if (imageInversee->format->BytesPerPixel == 4)
	{
		//- Внутренний формат
		formatInterne = GL_RGBA;

		//- Формат
		if (imageInversee->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}


	//- В других случаях мы останавливаем загрузку
	else
	{
		std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
		SDL_FreeSurface(imageInversee);

		return false;
	}


	//- Копируем пиксели
	glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);


	//- Применение фильтров
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	//- Фиксируем текстуру
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(imageInversee);
	return true;
}


SDL_Surface* ME::Textures::inverserPixels(SDL_Surface *imageSource) const
{
	//- Истинная копия исходного изображения без пикселей
	SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask,
		imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);


	//- Промежуточная таблица для управления пикселями
	unsigned char* pixelsSources = (unsigned char*)imageSource->pixels;
	unsigned char* pixelsInverses = (unsigned char*)imageInversee->pixels;


	//- Переключение пикселей
	for (int i = 0; i < imageSource->h; i++)
	{
		for (int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
			pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
	}

	//- Возврат перевернутого изображения
	return imageInversee;
}


GLuint ME::Textures::getID() const
{
	return m_id;
}


void ME::Textures::setFileImage(const std::string &imagefile)
{
	m_FileImage = imagefile;
}