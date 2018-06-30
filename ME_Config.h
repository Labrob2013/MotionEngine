// --------------------------------------------------------------- //
// ---------- // Здесь все связанное с конфигурацией // ---------- //
// --------------------------------------------------------------- //

#ifndef ME_CONFIG
#define ME_CONFIG

#include "ME_Main.h"

namespace ME
{
	class Config
	{
	public:
		
		//- Получить данные по запросу GET (String)
		string getConfig_str(string filename, string item);

		//- Получить данные по запросу GET (Int)
		int getConfig_int(string filename, string item);

	};
}

#endif //- ME_CONFIG

// --------------------------------------------------------------- //