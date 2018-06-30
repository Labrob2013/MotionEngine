#include "ME_Config.h"
#include "ME_Console.h"
#include "ME_Initialize.h"


string ME::Config::getConfig_str(string filename, string item)
{
	ME::Initialize Init;

	if (Init.GetFileExist(filename))
	{
		ifstream ifs(filename);
		IStreamWrapper isw(ifs);

		Document document;
		document.ParseStream(isw);

		return document[item.c_str()].GetString();
	}
	else {
		PRINT_LOG(Init.GetTime() << "[ERROR] Could not open configuration file: " << filename);
		return "ERROR";
	}
}

int ME::Config::getConfig_int(string filename, string item)
{
	ME::Initialize Init;

	if (Init.GetFileExist(filename))
	{
		ifstream ifs(filename);
		IStreamWrapper isw(ifs);

		Document document;
		document.ParseStream(isw);

		return document[item.c_str()].GetInt();
	}
	else {
		PRINT_LOG(Init.GetTime() << "[ERROR] Could not open configuration file: " << filename);
		return 0;
	}
}