#pragma once
#include <string>
#include<windows.h>

namespace qq
{
	class qq_notify
	{

	public:
		// 根据参数执行
		bool exec_args(int argc, char** argv);
		// 发送语音请求
		bool send_voice();
		// 发送视频请求
		bool send_video();
		// 发送文字
		bool send_message(const std::string& msg);
		// 根据指定title查找窗口
		bool find_wnd(const std::string& title);
		// 查找桌面所有QQ聊天窗口
		bool find_name();
		// 隐藏窗口
		void hide();
	protected:
		int  arg_to_type(const std::string& arg);
	private:
		HWND m_hwnd;
		RECT m_wnd_rect;
	};
}