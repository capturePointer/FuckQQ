
// FuckQQDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include <windows.h>
#include <iostream>
//#include <shellapi.h>
#include <psapi.h>
//#include <HIDLL/HIDll.h>
#include <tlhelp32.h>
#include <string.h>


#include "stdafx.h"
#include "FuckQQ.h"
#include "FuckQQDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define   WM_SHOWTASK   WM_USER+100
#define   WM_ABOUTBOX   WM_USER+101

using namespace std;
BOOL    CALLBACK    EnumProc(HWND,LPARAM);
unsigned    long    GetPidByName(LPCSTR    pname);
DWORD    PID=0;
char*    wname=NULL;
DWORD*    LPID=NULL;
UINT    NUMPID=0;
string    propmt;


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFuckQQDlg �Ի���



CFuckQQDlg::CFuckQQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFuckQQDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFuckQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFuckQQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFuckQQDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_COMMAND(WM_ABOUTBOX, ShowAbout)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CFuckQQDlg::OnBnClickedButton2)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CFuckQQDlg ��Ϣ�������

BOOL CFuckQQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_nid.cbSize = sizeof(m_nid);  
	m_nid.hWnd   = this->GetSafeHwnd();              //�Զ�����Ϣ���͵Ĵ���  
	m_nid.hIcon  = AfxGetApp()->LoadIcon(IDR_MAINFRAME);  //�����ICON,����������ʾ  
	m_nid.uCallbackMessage = WM_SHOWTASK;            //�Զ������Ϣ  
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;  
	m_nid.uID = 100;   /*WM_SHOWTASK*/               //ID,������㶨��ֵ��OK��  
	wcscpy_s(m_nid.szTip, TEXT("�ػ�QQ"));           //��Ϣ��ʾ��  
	Shell_NotifyIcon(NIM_ADD, &m_nid);               //�����������ͼ��

	m_CurrentIconIndex = 0;

	//����������atl+tab�б������أ�
	SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_HIDEWINDOW);   
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);   

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFuckQQDlg::ShowAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CFuckQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFuckQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFuckQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#define WINDOW_TEXT_LENGTH 256

BOOL CALLBACK EnumChildWindowCallBack(HWND hWnd, LPARAM lParam)  
{  
	DWORD dwPid = 0;  
	GetWindowThreadProcessId(hWnd, &dwPid); // ����ҵ����������Ľ���  
	if(dwPid == lParam) // �ж��Ƿ���Ŀ����̵Ĵ���  
	{  
		TRACE("0x%08X    \n", hWnd); // ���������Ϣ  
		TCHAR buf[WINDOW_TEXT_LENGTH];  
		SendMessage(hWnd, WM_GETTEXT, WINDOW_TEXT_LENGTH, (LPARAM)buf);  
		//TRACE(L"%s\n", buf);  
		EnumChildWindows(hWnd, EnumChildWindowCallBack, lParam);    // �ݹ�����Ӵ���  
	}  
	return TRUE;  
} 


BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)  
{  
	DWORD dwPid = 0;  
	GetWindowThreadProcessId(hWnd, &dwPid); // ����ҵ����������Ľ���  
	if(dwPid == lParam) // �ж��Ƿ���Ŀ����̵Ĵ���  
	{  
		TRACE("--0x%08X--", hWnd); // ���������Ϣ  
		TCHAR buf[WINDOW_TEXT_LENGTH];  
		SendMessage(hWnd, WM_GETTEXT, WINDOW_TEXT_LENGTH, (LPARAM)buf);  
		//TRACE(L"%s--\n", buf); 

		CString str = CString(buf);
		if(str.Find(_T("ϵͳ����"))!=-1){
			TRACE("ϵͳ����");
			ShowWindow(hWnd,FALSE);
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("�ٱ�"))!=-1){
			//ShowWindow(hWnd,TRUE);
			TRACE("�ٱ�");
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("�ļ�����"))!=-1){
			TRACE("�ļ�����");
			ShowWindow(hWnd,FALSE);
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("��"))!=-1){
			TRACE("��");
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("ѡ���ļ�"))!=-1){
			TRACE("ѡ���ļ�");
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("ɾ������"))!=-1){
			TRACE("ɾ������");
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("����������"))!=-1){
			TRACE("����������");
			ShowWindow(hWnd,FALSE);
			SendMessage(hWnd,WM_CLOSE,   0,   0);
			MessageBox(NULL,TEXT("��ֹ�������������������ϵ����Ա��"),TEXT("����"),MB_ICONINFORMATION|MB_OK);
		}else if(str.Find(_T("��Ѷ�������"))!=-1){
			TRACE("��Ѷ�������");
			SendMessage(hWnd,WM_CLOSE,   0,   0);	
			ShowWindow(hWnd,FALSE);
			//RECT rect;
			//::GetWindowRect(hWnd,&rect);			
			//mouseLeftClick(rect.right-25,rect.top+15);
			//TRACE("%d,%d,%d,%d -- ",rect.top,rect.left,rect.right,rect.bottom);
			///::GetClientRect(hWnd,&rect);
			//TRACE("%d,%d,%d,%d",rect.top,rect.left,rect.right,rect.bottom);
		}else if(str.Find(_T("��Ƶͨ��"))!=-1){
			TRACE("��Ƶͨ��");
			ShowWindow(hWnd,TRUE);
			RECT rect;
			::GetWindowRect(hWnd,&rect);	
			::SetWindowPos(hWnd,CWnd::wndTopMost,100,200,rect.right,rect.bottom,SWP_NOMOVE|SWP_NOSIZE);
			//::SetWindowPos(hWnd,CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);//�ö�
		}else if(str.Find(_T("��Ѷ������"))!=-1){
			TRACE("��Ѷ������");
			ShowWindow(hWnd,FALSE);
			SendMessage(hWnd,WM_CLOSE,   0,   0);
		}else if(str.Find(_T("��Ѷ��Ƶ�Ƽ�"))!=-1){
			TRACE("��Ѷ��Ƶ�Ƽ�");
			ShowWindow(hWnd,FALSE);
			SendMessage(hWnd,WM_CLOSE,   0,   0);
		}else if(str.Compare(_T("QQ"))==0){
			ShowWindow(hWnd,FALSE);
		}

		OutputDebugString(str);
		TRACE("\n");
		//EnumChildWindows(hWnd, EnumChildWindowCallBack, lParam);    // ���������Ӵ���  
	}  
	return TRUE;  
}  



void CFuckQQDlg::FuckQQ()
{

	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32* processInfo=new PROCESSENTRY32;
	processInfo->dwSize=sizeof(PROCESSENTRY32);
	int index=0;
	TRACE("****************��ʼ�оٽ���****************\n");
	while(Process32Next(hSnapShot,processInfo)!=FALSE)
	{
		///index++;
		//TRACE("****************** %d ******************\n",index);
		//TRACE("PID Name Current Threads\n");
		//TRACE("%-15d%-25s%-4d\n",processInfo->th32ProcessID,processInfo->szExeFile,processInfo->cntThreads);
		EnumWindows(EnumWindowCallBack, processInfo->th32ProcessID);
	}

	CloseHandle(hSnapShot);
	TRACE("****************�����оٽ���****************\n");
}

void CFuckQQDlg::OnBnClickedButton1()
{

	

	SetTimer(1,100,NULL);
	MessageBox(L"���óɹ�",L"QQ�ػ�");

	CWnd *pCwnd;
	pCwnd = (CWnd *)GetDlgItem(IDC_BUTTON1);
	pCwnd->EnableWindow(FALSE);

	pCwnd = (CWnd *)GetDlgItem(IDC_BUTTON2);
	pCwnd->EnableWindow(TRUE);

}

unsigned    long    GetPidByName(LPCSTR    pname){
	unsigned long    pid=0;
	string    name    =    pname;
	//char*    dname    =    NULL;
	name=::CharLowerA(    (char*)name.c_str() );

	PROCESSENTRY32    lp;
	HANDLE            lh=NULL;
	memset(&lp,0,sizeof(lp));
	lp.dwSize    =    sizeof(lp);

	lh  = ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	BOOL ok = ::Process32First( lh,&lp);

	while(ok){
		char* dname    =    new char[(int)((wcslen(lp.szExeFile)+1)*sizeof(wchar_t))];
		//wchar_t    dname[]    =lp.szExeFile;
		::WideCharToMultiByte(CP_ACP,0,lp.szExeFile,-1,dname,static_cast<int>(wcslen(lp.szExeFile)+1),NULL,NULL);
		dname    =    ::CharLowerA(dname);
		if    ( 0==name.compare(dname) ){
			pid    =    lp.th32ProcessID;        
			delete [] dname;dname=NULL;
			break;
		}
		delete [] dname;dname=NULL;
		ok        =    ::Process32NextW(lh,&lp);
	}
	return pid;
}


void CFuckQQDlg::OnTimer(UINT_PTR nIDEvent)
{

	//FuckQQ();
	this->isfuck = TRUE;

	CWnd *pCwnd;
	pCwnd = (CWnd *)GetDlgItem(IDC_BUTTON1);
	pCwnd->EnableWindow(FALSE);

	pCwnd = (CWnd *)GetDlgItem(IDC_BUTTON2);
	pCwnd->EnableWindow(TRUE);


	++m_CurrentIconIndex;
	if(m_CurrentIconIndex==8)m_CurrentIconIndex = 0;

	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; 
	m_nid.hIcon = _pIcons[m_CurrentIconIndex];
	this->SetIcon(m_nid.hIcon,FALSE);
	Shell_NotifyIcon(NIM_MODIFY,&m_nid);//���͸���ͼ�����Ϣ;
	Shell_NotifyIcon(NIM_ADD,&m_nid);//��������ϵͳ���̵���Ϣ;


	CDialogEx::OnTimer(nIDEvent);
}


LRESULT CFuckQQDlg::OnShowTask(WPARAM wParam, LPARAM lParam)  
{  
	switch(lParam)  
	{  
	case WM_RBUTTONUP:        //�Ҽ���ʱ�����˵�  
		{     
			CPoint point;  
			::GetCursorPos(&point);                    //�õ����λ�� 			
			
			CMenu menu;  
			menu.CreatePopupMenu();   //����һ������ʽ�˵�  
			menu.AppendMenu(MF_STRING, IDC_BUTTON1, L"�����ػ�");  
			menu.AppendMenu(MF_STRING, IDC_BUTTON2, L"�ر��ػ�");  
			menu.AppendMenu(MF_STRING, WM_DESTROY,  L"�˳�ϵͳ");  
			menu.AppendMenu(MF_SEPARATOR);  
			menu.AppendMenu(MF_STRING, WM_ABOUTBOX, L"����ϵͳ");  
			menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);  
			HMENU hmenu = menu.Detach();  
			menu.DestroyMenu(); 
			
			
		}  
		break;  
	case WM_LBUTTONDBLCLK:    //˫������Ĵ���  
		{  
			
			
			//menu.EnableMenuItem(IDC_BUTTON1,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			//menu.ModifyMenuW(menu.GetMenuItemID(0),MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			//SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_SHOWWINDOW);  
			//MessageBox(L"��Ҫ�ҵ����~~",L"QQ�ػ�");
			FuckQQ();
		}  
		break;  
	}  
	return 0;  
}

int CFuckQQDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	visible = false; 
	
	memset(_pIcons,0,sizeof(HICON));
	_pIcons[0] =  AfxGetApp()->LoadIcon(IDI_ICON1);
	_pIcons[1] =  AfxGetApp()->LoadIcon(IDI_ICON2);
	_pIcons[2] =  AfxGetApp()->LoadIcon(IDI_ICON3);
	_pIcons[3] =  AfxGetApp()->LoadIcon(IDI_ICON4);
	_pIcons[4] =  AfxGetApp()->LoadIcon(IDI_ICON5);
	_pIcons[5] =  AfxGetApp()->LoadIcon(IDI_ICON6);
	_pIcons[6] =  AfxGetApp()->LoadIcon(IDI_ICON7);
	_pIcons[7] =  AfxGetApp()->LoadIcon(IDI_ICON8);
	
	this->isfuck = FALSE;

	SetTimer(1,100,NULL);

	return 0;
}


void CFuckQQDlg::OnDestroy()
{
	CDialogEx::OnDestroy();


	Shell_NotifyIcon(NIM_DELETE, &m_nid);   // ��������ɾ��ͼ�� 
}


void CFuckQQDlg::OnBnClickedButton2()
{
	KillTimer(1);
	MessageBox(L"ȡ���ɹ�",L"QQ�ػ�");

	CWnd *pCwnd;
	pCwnd = (CWnd *)GetDlgItem(IDC_BUTTON1);
	pCwnd->EnableWindow(TRUE);

	pCwnd = (CWnd *)GetDlgItem(IDC_BUTTON2);
	pCwnd->EnableWindow(FALSE);
}


void CFuckQQDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	if(!visible) 
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
}
