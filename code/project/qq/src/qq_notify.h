#pragma once
#include <string>
#include<windows.h>

namespace qq
{
	class qq_notify
	{

	public:
		// ���ݲ���ִ��
		bool exec_args(int argc, char** argv);
		// ������������
		bool send_voice();
		// ������Ƶ����
		bool send_video();
		// ��������
		bool send_message(const std::string& msg);
		// ����ָ��title���Ҵ���
		bool find_wnd(const std::string& title);
		// ������������QQ���촰��
		bool find_name();
		// ���ش���
		void hide();
	protected:
		int  arg_to_type(const std::string& arg);
	private:
		HWND m_hwnd;
		RECT m_wnd_rect;
	};
}