#include "qq_notify.h"
#include "../../util/src/util.hpp"
#include "arg_define.h"
#include <list>
#include <fstream>

static std::list<HWND> s_g_wnds;
BOOL CALLBACK OnWindowEnum(HWND hwnd, LPARAM lparam)
{
	char name[256] = {};
	GetClassName(hwnd,name , 256);
	std::string classname = name;
	if (classname == "TXGuiFoundation")
	{
		s_g_wnds.push_back(hwnd);
	}
	return true;
}

namespace qq
{
	
	bool qq_notify::exec_args(int argc, char** argv)
	{
		std::map<std::string, std::string> args = parse_args(argc, argv);
		auto find_iter = args.find(ARG_TYPE_STR[FIND_NAME]);
		if (find_iter != args.end())
		{
			find_name();
			return true;
		}
		auto hide_iter = args.find(ARG_TYPE_STR[HIDE_WND]);
		if (hide_iter != args.end())
		{
			hide();
			return true;
		}
		auto name_iter = args.find(ARG_TYPE_STR[WND_NAME]);
		if (name_iter != args.end())
		{
			bool ret = find_wnd(name_iter->second);
			if (ret)
			{
				for (auto iter = args.begin(); iter != args.end(); iter++)
				{
					if (iter == name_iter)
					{
						continue;
					}
					int arg_type = arg_to_type(iter->first);

					switch (arg_type)
					{
						break;
					case SEND_MESSAGE:
						send_message(iter->second);
						break;
					case SEND_VOICE:
						send_voice();
						break;
					case SEND_VIDEO:
						send_video();
						break;
					default:
						break;
					}
				}
				return true;
			}
			else
			{
				log("error:未找到对应qq窗口：" + name_iter->second);
			}
			
		}
		else
		{
			log("error：需要制定要操作的窗口名字");
			return false;
		}
		
		return true;
	}

	bool qq_notify::send_voice()
	{
		int width = m_wnd_rect.right - m_wnd_rect.left;
		PostMessage(m_hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(width - 270, 70));
		Sleep(50);
		PostMessage(m_hwnd, WM_LBUTTONUP, 0, MAKELPARAM(width - 270, 70));
		return true;
	}

	bool qq_notify::send_video()
	{
		int width = m_wnd_rect.right - m_wnd_rect.left;
		PostMessage(m_hwnd, WM_LBUTTONDOWN,0,MAKELPARAM(width - 220,70));
		Sleep(50);
		PostMessage(m_hwnd, WM_LBUTTONUP, 0, MAKELPARAM(width - 220, 70));
		return true;
	}

	bool qq_notify::send_message(const std::string& msg)
	{
		std::wstring str = string2wstring(msg);
		for (size_t i=0; i<str.length(); i++)
		{
			PostMessageW(m_hwnd, WM_CHAR,str[i],0 );
			Sleep(5);
		}
		int width = m_wnd_rect.right - m_wnd_rect.left;
		int height = m_wnd_rect.bottom - m_wnd_rect.top;
		PostMessage(m_hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(width - 200, height - 30));
		Sleep(50);
		PostMessage(m_hwnd, WM_LBUTTONUP, 0, MAKELPARAM(width - 200, height - 30));
		return true;
	}

	bool qq_notify::find_wnd(const std::string& title)
	{
		m_hwnd = FindWindowA("TXGuiFoundation", title.c_str());
		if (m_hwnd == nullptr)
		{
			return false;
		}
		GetWindowRect(m_hwnd, &m_wnd_rect);
		return true;
	}

	bool qq_notify::find_name()
	{
		s_g_wnds.clear();
		DWORD dwThreadId = GetCurrentThreadId(); // Get the current thread id
		HDESK hDesktop = GetThreadDesktop(dwThreadId);
		EnumDesktopWindows(hDesktop, OnWindowEnum, NULL);
		//EnumWindows(OnWindowEnum,0);
		std::string names;
		for (auto iter = s_g_wnds.begin(); iter != s_g_wnds.end(); iter++)
		{
			char name[64] = {};
			GetWindowText(*iter, name, 64);
			std::string temp = name;
			if (temp.length() > 0 && temp != "TXMenuWindow" && temp != "QQ" && temp.find("视频通话")==std::string::npos)
			{
				names = names + temp + "\n";
			}
		}
		std::cout << "查找到qq聊天窗口如下：" << std::endl <<std::endl;
		std::cout << names << std::endl;
		std::fstream fs;
		fs.open("qqname.txt", std::ios_base::out);
		fs << names;
		fs.flush();
		fs.close();
		return true;
	}

	void qq_notify::hide()
	{
		HWND hwnd;

		if (hwnd = FindWindow("ConsoleWindowClass", NULL)) //找到控制台句柄
		{
			::ShowWindow(hwnd, SW_HIDE); //隐藏控制台窗口
		}
	}

	int qq_notify::arg_to_type(const std::string& arg)
	{
		for (int i = 0; i < ARG_COUNT; i++)
		{
			if (arg == ARG_TYPE_STR[i])
			{
				return i;
			}
		}
		return 0;
	}

}