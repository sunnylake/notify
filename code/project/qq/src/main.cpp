#include <iostream>
#include "qq_notify.h"

// ��ִ̨��
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void help()
{
	std::cout << "    ʹ��˵����" << std::endl;
	std::cout << std::endl;
	std::cout << "-find     ����qq����д�뵽qqnames.txt��" << std::endl;
	std::cout << "-title    Ҫ������qq�������֣�������-find����" << std::endl;
	std::cout << "-voice    ������������" << std::endl;
	std::cout << "-video    ������Ƶ����" << std::endl;
	std::cout << "-msg      ����������Ϣ" << std::endl;
	std::cout << "-hide     ���ش���" << std::endl;
	std::cout << std::endl;

	std::cout << "���ӣ�-title sunny -msg ��ã� -voice -video" << std::endl<<std::endl;
}

int main(int argc, char** argv)
{
	qq::qq_notify qq;
	if (argc <= 1)
	{
		help();
		qq.find_name();
		system("pause");
		return 0;
	}

	if (qq.exec_args(argc, argv))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}