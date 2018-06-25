#include "ME_Main.h"
#include "ME_Initialize.h"

int main(int argc, char **argv)
{
	ME::Initialize init;
	init.InitEngine();
	init.UpdateWindow();

	return 0;
}