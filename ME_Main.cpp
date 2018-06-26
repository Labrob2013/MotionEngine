#include "ME_Main.h"
#include "ME_Initialize.h"

int main(int argc, char **argv)
{
	//- Создаем объект
	ME::Initialize init;

	//- Задаем размеры окна
	init.w_width  =	1024;	//- Def: 800
	init.w_height = 600;	//- Def: 600

	//- Запускаем инициализацию
	init.InitEngine();

	return 0;
}