#pragma once
#include <string>

namespace qq
{

	enum ARGTYPE
	{
		FIND_NAME,		//查找窗口名字
		WND_NAME,		//窗口名字
		SEND_MESSAGE,	//发送消息
		SEND_VOICE,		//发送语音
		SEND_VIDEO,		//发送视频
		HIDE_WND,		//隐藏窗口

		ARG_COUNT,		//参数总个数
	};

	std::string ARG_TYPE_STR[] =
	{
		"find",
		"title",
		"msg",
		"voice",
		"video",
		"hide"
	};

}