// MFCCommAssist.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMFCCommAssistApp:
// �йش����ʵ�֣������ MFCCommAssist.cpp
//

class CMFCCommAssistApp : public CWinApp
{
public:
	CMFCCommAssistApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCCommAssistApp theApp;
