#include "ME_Console.h"

//- Создаем Ofstream
stringstream ME::Console::Log = stringstream();


// ------------------------------------------------- //
// --------- Функция: Создание лога в файл  -------- //
// ------------------------------------------------- //

void ME::Console::SaveInFile(const string &filename)
{
	ofstream File(filename);
	if (!File.is_open())
		return;

	File << Log.str();
	File.close();
}

// ------------------------------------------ //
// --------- Функция: Очишения лога  -------- //
// ------------------------------------------ //

void ME::Console::Clear()
{
	Log.clear();
}

// ------------------------------------------ //