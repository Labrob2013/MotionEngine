// --------------------------------------------------------- //
// ---------- // Подключение Главных Библеотек // ---------- //
// --------------------------------------------------------- //

//- Сторонние:

	//- Glew
	#include <GL/glew.h>

	//- SDL 
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>

	//- GLM
	#include <glm.hpp>
	#include <gtx/transform.hpp>
	#include <gtc/type_ptr.hpp>

	//- JSON
	#include "document.h"
	#include "writer.h"
	#include "stringbuffer.h"
	#include "istreamwrapper.h"

//- Основные

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <cstdio>
	#include <cstdlib>
	#include <ctime>
	#include <vector>

//- Использование пространств
	using namespace std;
	using namespace glm;
	using namespace rapidjson;


// --------------------------------------------------------- //