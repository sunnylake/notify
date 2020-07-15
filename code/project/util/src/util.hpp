#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <map>

static void log(std::string str)
{
	std::cout << str << std::endl;
}

//��stringת����wstring  
std::wstring string2wstring(const std::string& str)
{
	std::wstring result;
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.size(), NULL, 0);
	WCHAR* buffer = new WCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.size(), buffer, len);
	buffer[len] = '\0';             //����ַ�����β  
									//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}

//��wstringת����string  
std::string wstring2string(const std::wstring& wstr)
{
	std::string result;
	//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//���ֽڱ���ת���ɶ��ֽڱ���  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;

}

static std::map<std::string, std::string> parse_args(int argc, char** argv)
{
	std::map<std::string, std::string> args;
	//��1��ʼ ��Ϊ0�ǳ���·��
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
			log("error������Ӧ���ԡ�-����ͷ�������Ƿ����");
		}
	}
	return args;
};


