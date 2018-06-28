#include "ME_Textures.h"
#include "ME_Initialize.h"
#include "ME_Console.h"


ME::Textures::Textures(Textures const &textureCopy)
{
	//- �������� ��������
	m_FileImage = textureCopy.m_FileImage;
	charger();
}


ME::Textures::Textures(string imagefile) : m_id(0), m_FileImage(imagefile)
{

}


ME::Textures::~Textures()
{
	//- �������� ��������
	glDeleteTextures(1, &m_id);
}


//- ������
ME::Textures& ME::Textures::operator=(Textures const &textureCopy)
{
	//- ����� ��������
	m_FileImage = textureCopy.m_FileImage;
	charger();

	return *this;
}


bool ME::Textures::charger()
{
	//- �������� ����������� �� ����������� SDL
	SDL_Surface *imageSDL = IMG_Load(m_FileImage.c_str());

	if (imageSDL == 0)
	{
		ME::Initialize Init;
		PRINT_LOG(Init.GetTime() << "[ERROR] " << SDL_GetError());
		return false;
	}


	//- ��������� �����������
	SDL_Surface *imageInversee = inverserPixels(imageSDL);
	SDL_FreeSurface(imageSDL);


	//- ����������� ����� ������ ��������
	if (glIsTexture(m_id) == GL_TRUE)
		glDeleteTextures(1, &m_id);


	//- ��������� ��������������
	glGenTextures(1, &m_id);


	//- ��������� ��������
	glBindTexture(GL_TEXTURE_2D, m_id);


	//- ������ �����������
	GLenum formatInterne(0), format(0);


	//- ����������� ������� � ����������� ������� ��� ���������������� �����������
	if (imageInversee->format->BytesPerPixel == 3)
	{
		//- ���������� ������
		formatInterne = GL_RGB;

		//- ������
		if (imageInversee->format->Rmask == 0xff)
			format = GL_RGB;
		else 
			format = GL_BGR;
	}


	//- ����������� ������� � ����������� ������� ��� 4-������������ �����������
	else if (imageInversee->format->BytesPerPixel == 4)
	{
		//- ���������� ������
		formatInterne = GL_RGBA;

		//- ������
		if (imageInversee->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}


	//- � ������ ������� �� ������������� ��������
	else
	{
		std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
		SDL_FreeSurface(imageInversee);

		return false;
	}


	//- �������� �������
	glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);


	//- ���������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	//- ��������� ��������
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(imageInversee);
	return true;
}


SDL_Surface* ME::Textures::inverserPixels(SDL_Surface *imageSource) const
{
	//- �������� ����� ��������� ����������� ��� ��������
	SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask,
		imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);


	//- ������������� ������� ��� ���������� ���������
	unsigned char* pixelsSources = (unsigned char*)imageSource->pixels;
	unsigned char* pixelsInverses = (unsigned char*)imageInversee->pixels;


	//- ������������ ��������
	for (int i = 0; i < imageSource->h; i++)
	{
		for (int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
			pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
	}

	//- ������� ������������� �����������
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