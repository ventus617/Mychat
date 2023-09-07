#include"UdpMediator.h"
#include"config.h"
#include"UdpNet.h"

int main()
{
	INetMediator* m_pNet = new UdpMediator();
	if (!m_pNet->OpenNet())
	{
		cout << "´ò¿ªÍøÂçÊ§°Ü" << endl;
		return 1;
	}
	char a[] = "hello world";
	m_pNet->SendData(a, sizeof(a), inet_addr("255.255.255.255"));

	while (1);
	return 0;
}