
// FuckQQ.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "FuckQQ.h"
#include "FuckQQDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define one "0xbe8e2ce1, 0xdab6, 0x11d6, 0xad, 0xd0, 0x0, 0xe0, 0x4c, 0x53, 0xf6, 0xe6"

// CFuckQQApp

BEGIN_MESSAGE_MAP(CFuckQQApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFuckQQApp ����

CFuckQQApp::CFuckQQApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFuckQQApp ����

CFuckQQApp theApp;


// CFuckQQApp ��ʼ��

BOOL CFuckQQApp::InitInstance()
{
	HANDLE handle=::CreateMutex(NULL,FALSE,L"FuckQQ");
	if(GetLastError()==ERROR_ALREADY_EXISTS)       	   
	{      
		AfxMessageBox(TEXT("QQ�ػ�Ӧ�ó����Ѿ�������"));   
		return FALSE;      
	}   
	if (!FirstInstance())
			return FALSE; 
	
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CFuckQQDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CFuckQQApp::FirstInstance()
{
	CWnd *pWndPrev, *pWndChild; 

	// Determine if another window with our class name and Window title exists... 
	// The title "Instance " is set up latter, in the InitDialog function.
	if (pWndPrev = CWnd::FindWindow(NULL, L"FuckQQ"))
	{ 
		pWndChild = pWndPrev->GetLastActivePopup();
		if (pWndPrev->IsIconic())pWndPrev->ShowWindow(SW_RESTORE); 
			pWndChild->SetForegroundWindow(); 
			   return FALSE; 
	} 
	else 
		return TRUE; // First instance. Proceed as normal. 
}
