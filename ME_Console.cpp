#include "ME_Console.h"

//- Создаем Ofstream
ofstream ME::Console::FileSave = ofstream();

// ---------------------------------------- //
// --------- Функция: Вывод логов  -------- //
// ---------------------------------------- //

void ME::Console::Log(const Type &Type, const string &Message)
{
	switch (Type)
	{
	case Type::None:
		FileSave << Message << endl;
		cout << Message << endl;
		break;

	case Type::Info:
		FileSave << "[Info] " << Message << endl;
		cout << "[Info] " << Message << endl;
		break;

	case Type::Warning:
		FileSave << "[Warning] " << Message << endl;
		cout << "[Warning] " << Message << endl;
		break;

	case Type::Error:
		FileSave << "[Error] " << Message << endl;
		cout << "[Error] " << Message << endl;
		break;
	}
}

// ------------------------------------------- //
// --------- Функция: Указание файла  -------- //
// ------------------------------------------- //

void ME::Console::SetFilename(const string &filename)
{
	FileSave.open(filename);
}

// ------------------------------------------- //