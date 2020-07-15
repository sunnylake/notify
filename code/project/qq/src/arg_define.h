#pragma once
#include <string>

namespace qq
{

	enum ARGTYPE
	{
		FIND_NAME,		//���Ҵ�������
		WND_NAME,		//��������
		SEND_MESSAGE,	//������Ϣ
		SEND_VOICE,		//��������
		SEND_VIDEO,		//������Ƶ
		HIDE_WND,		//���ش���

		ARG_COUNT,		//�����ܸ���
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