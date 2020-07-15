#include <iostream>
#include "qq_notify.h"

// 后台执行
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void help()
{
	std::cout << "    使用说明：" << std::endl;
	std::cout << std::endl;
	std::cout << "-find     查找qq窗口写入到qqnames.txt中" << std::endl;
	std::cout << "-title    要操作的qq窗口名字，可以用-find查找" << std::endl;
	std::cout << "-voice    发送语音请求" << std::endl;
	std::cout << "-video    发送视频请求" << std::endl;
	std::cout << "-msg      发送文字消息" << std::endl;
	std::cout << "-hide     隐藏窗口" << std::endl;
	std::cout << std::endl;

	std::cout << "例子：-title sunny -msg 你好！ -voice -video" << std::endl<<std::endl;
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