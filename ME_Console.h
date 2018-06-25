// -------------------------------------------------------- //
// ---------- // Здесь все связанное с логами // ---------- //
// -------------------------------------------------------- //

#include "ME_Main.h"

namespace ME
{
	class Console
	{
	public:
		enum Type
		{
			None,
			Info,
			Warning,
			Error
		};

		static void Log(const Type& TypeLog, const string& Message);

		static void SetFilename(const string& filename);

	private:
		static ofstream			FileSave;
	};
}

// -------------------------------------------------------- //