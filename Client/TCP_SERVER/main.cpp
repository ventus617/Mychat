#include "kernel/kernel.h"


int main()
{
	CKernel kernel;
	if (!kernel.startServer())
	{
		cout << "open server failed" << endl;
		return 0;
	}
	while (1)
	{
		Sleep(5000);
		cout << "server is running..." << endl;
	}
	return 0;
}