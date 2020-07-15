#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <map>

static void log(std::string str)
{
	std::cout << str << std::endl;
}

//将string转换成wstring  
std::wstring string2wstring(const std::string& str)
{
	std::wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.size(), NULL, 0);
	WCHAR* buffer = new WCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
									//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

//将wstring转换成string  
std::string wstring2string(const std::wstring& wstr)
{
	std::string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;

}

static std::map<std::string, std::string> parse_args(int argc, char** argv)
{
	std::map<std::string, std::string> args;
	//从1开始 因为0是程序路径
	for (int i = 1; i < argc; i++)
	{
		std::string key = argv[i];
		std::string val = "";

		if (key[0] == '-')
		{
			key = argv[i] + 1;

			if (i + 1 < argc)
			{
				val = argv[i + 1];
				if (val[0] != '-')
				{
					val = argv[i + 1];
					i++;
				}
				else
				{
					val = "";
				}
			}

			args[key] = val;
		}
		else
		{
			log("error：命令应该以’-‘开头，请检查是否配对");
		}
	}
	return args;
};


