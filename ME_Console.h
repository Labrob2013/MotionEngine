// -------------------------------------------------------- //
// ---------- // Здесь все связанное с логами // ---------- //
// -------------------------------------------------------- //

#ifndef ME_CONSOLE
#define ME_CONSOLE

#include "ME_Main.h"

//- Команда для выполнения
#define PRINT_LOG( X ) { ME::Console::Log << X << endl; cout << X << endl; }

namespace ME
{
	class Console
	{
	public:
		//- Сохранить лог в файл
		static void SaveInFile(const string& filename);

		//- Очистить лог
		static void Clear();

		static stringstream		Log;
	};
}

#endif //- ME_CONSOLE

// -------------------------------------------------------- //