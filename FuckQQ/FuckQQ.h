
// FuckQQ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFuckQQApp:
// �йش����ʵ�֣������ FuckQQ.cpp
//

class CFuckQQApp : public CWinApp
{
public:
	CFuckQQApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual BOOL FirstInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFuckQQApp theApp;