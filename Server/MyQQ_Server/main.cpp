#include <iostream>
#include"../myqq/kernel/kernel.h"

using namespace std;

int main()
{
    CKernel * pKernel=CKernel::GetInstance();
    pKernel->startServer();
    pKernel->EventLoop();
    delete pKernel;
    return 0;
}
