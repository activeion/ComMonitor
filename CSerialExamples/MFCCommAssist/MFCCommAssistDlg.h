// MFCCommAssistDlg.h : ͷ�ļ�
//

#pragma once
#include "..\CSerial\SerialMFC.h"
#include "stdafx.h"

#define PORTNAME_MAX 8
#define BAUDRATE_MAX 3
#define DATABITS_MAX 4
#define PARITY_MAX 3
#define STOPBITS_MAX 3

// CMFCCommAssistDlg �Ի���
class CMFCCommAssistDlg : public CDialog
{
// ����
public:
	CMFCCommAssistDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCCOMMASSIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CSerialMFC m_port;

	CString*  m_lstStrPort[PORTNAME_MAX];
	int n_portnum;
	CString*  m_lstStrBaudrate[BAUDRATE_MAX];
	CSerialMFC::EBaudrate m_lstBaudrate[BAUDRATE_MAX];
	CString*  m_lstStrDataBits[DATABITS_MAX];
	CSerialMFC::EDataBits m_lstDataBits[DATABITS_MAX];
	CString*  m_lstStrParity[PARITY_MAX];
	CSerialMFC::EParity m_lstParity[PARITY_MAX];
	CString*  m_lstStrStopBits[STOPBITS_MAX];
	CSerialMFC::EStopBits m_lstStopBits[STOPBITS_MAX];

	bool m_port_opened;
	void UpdateButtonOC();
	void DisplayError();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnSerialMsg (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOc();
	afx_msg void OnBnClickedBtnSend();
};
