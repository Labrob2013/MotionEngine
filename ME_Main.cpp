#include "ME_Main.h"
#include "ME_Initialize.h"

int main(int argc, char **argv)
{
	//- ������� ������
	ME::Initialize init;

	//- ������ ������� ����
	init.w_width  =	1024;	//- Def: 800
	init.w_height = 600;	//- Def: 600

	//- ��������� �������������
	init.InitEngine();

	return 0;
}