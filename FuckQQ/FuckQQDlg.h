
// FuckQQDlg.h : ͷ�ļ�
//

#pragma once


// CFuckQQDlg �Ի���
class CFuckQQDlg : public CDialogEx
{
// ����
public:
	CFuckQQDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FUCKQQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool isfuck;
	int  m_CurrentIconIndex;
	NOTIFYICONDATA    m_nid;
	HICON _pIcons[8];
	bool visible ;

	afx_msg void FuckQQ();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam); 
	afx_msg void OnDestroy();
	afx_msg void ShowAbout();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
