// --------------------------------------------------------------- //
// ---------- // ����� ��� ��������� � ������������� // ---------- //
// --------------------------------------------------------------- //

#ifndef ME_CONFIG
#define ME_CONFIG

#include "ME_Main.h"

namespace ME
{
	class Config
	{
	public:
		
		//- �������� ������ �� ������� GET (String)
		string getConfig_str(string filename, string item);

		//- �������� ������ �� ������� GET (Int)
		int getConfig_int(string filename, string item);

	};
}

#endif //- ME_CONFIG

// --------------------------------------------------------------- //