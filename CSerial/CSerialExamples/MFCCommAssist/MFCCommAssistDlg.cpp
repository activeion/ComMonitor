// MFCCommAssistDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCCommAssist.h"
#include "MFCCommAssistDlg.h"
#include ".\mfccommassistdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCCommAssistDlg 对话框



CMFCCommAssistDlg::CMFCCommAssistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCCommAssistDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCommAssistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCCommAssistDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OC, OnBnClickedBtnOc)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBnClickedBtnSend)
	ON_WM_SERIAL(OnSerialMsg)
END_MESSAGE_MAP()


// CMFCCommAssistDlg 消息处理程序

BOOL CMFCCommAssistDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//////////////////////////////////////////////////////////////////////////
	// 
	// SERIAL

	//
	int n;
	CString* str;
	// PORTS
	n_portnum = 0;
	for (n=0;n<PORTNAME_MAX;n++)
	{
		str = new CString;
		str->Format("COM%d",n+1);
		if (CSerialMFC::CheckPort((LPCTSTR)(*str))
			==CSerialMFC::EPortAvailable)
		{
			m_lstStrPort[n] = str;
			n_portnum ++;
		}
	}

	// BAUDRATE

	m_lstBaudrate[0] = CSerialMFC::EBaud9600;
	m_lstBaudrate[1] = CSerialMFC::EBaud19200;
	m_lstBaudrate[2] = CSerialMFC::EBaud38400;

	m_lstStrBaudrate[0] = new CString("9600");
	m_lstStrBaudrate[1] = new CString("19200");
	m_lstStrBaudrate[2] = new CString("38400");


	m_lstDataBits[0] = CSerialMFC::EData8;
	m_lstDataBits[1] = CSerialMFC::EData6;
	m_lstDataBits[2] = CSerialMFC::EData7;
	m_lstDataBits[3] = CSerialMFC::EData5;

	m_lstStrDataBits[0] = new CString("8");
	m_lstStrDataBits[1] = new CString("7");
	m_lstStrDataBits[2] = new CString("6");
	m_lstStrDataBits[3] = new CString("5");

	m_lstParity[0] = CSerialMFC::EParNone;
	m_lstParity[1] = CSerialMFC::EParOdd;
	m_lstParity[2] = CSerialMFC::EParEven;

	m_lstStrParity[0] = new CString("None");
	m_lstStrParity[1] = new CString("Odd");
	m_lstStrParity[2] = new CString("Even");

	m_lstStopBits[0] = CSerialMFC::EStop1;
	m_lstStopBits[1] = CSerialMFC::EStop1_5;
	m_lstStopBits[2] = CSerialMFC::EStop2;

	m_lstStrStopBits[0] = new CString("1");
	m_lstStrStopBits[1] = new CString("1.5");
	m_lstStrStopBits[2] = new CString("2");

	CComboBox* p_ComboBox;
	p_ComboBox = 
		(CComboBox*)GetDlgItem(IDC_CBB_PORTNAME);
	for (n=0;n<n_portnum;n++)
		p_ComboBox->AddString((LPCTSTR)(*m_lstStrPort[n]));
	if(n_portnum>0) p_ComboBox->SetCurSel(0);

	p_ComboBox = 
		(CComboBox*)GetDlgItem(IDC_CBB_BAUDRATE);
	for (n=0;n<BAUDRATE_MAX;n++)
		p_ComboBox->AddString((LPCTSTR)(*m_lstStrBaudrate[n]));
	p_ComboBox->SetCurSel(0);

	p_ComboBox = 
		(CComboBox*)GetDlgItem(IDC_CBB_DATABITS);
	for (n=0;n<DATABITS_MAX;n++)
		p_ComboBox->AddString((LPCTSTR)(*m_lstStrDataBits[n]));
	p_ComboBox->SetCurSel(0);

	p_ComboBox = 
		(CComboBox*)GetDlgItem(IDC_CBB_PARITY);
	for (n=0;n<PARITY_MAX;n++)
		p_ComboBox->AddString((LPCTSTR)(*m_lstStrParity[n]));
	p_ComboBox->SetCurSel(0);

	p_ComboBox = 
		(CComboBox*)GetDlgItem(IDC_CBB_STOPBITS);
	for (n=0;n<STOPBITS_MAX;n++)
		p_ComboBox->AddString((LPCTSTR)(*m_lstStrStopBits[n]));
	p_ComboBox->SetCurSel(0);

	m_port_opened = false;
	UpdateButtonOC();

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CMFCCommAssistDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCommAssistDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMFCCommAssistDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCCommAssistDlg::UpdateButtonOC()
{
	CButton * p_button = (CButton*)GetDlgItem(IDC_BTN_OC);
	if (m_port_opened)
	{
		p_button->SetWindowText("&Close");
		p_button = (CButton*)GetDlgItem(IDC_BTN_SEND);
		p_button->EnableWindow(true);
	}
	else
	{
		p_button->SetWindowText("&Open");
		p_button = (CButton*)GetDlgItem(IDC_BTN_SEND);
		p_button->EnableWindow(false);
	}
}
void CMFCCommAssistDlg::OnBnClickedBtnOc()
{
	if (m_port_opened == false)
	{
		int nPortSel;
		int nBaudrateSel;
		int nDataBitsSel;
		int nParitySel;
		int nStopBitsSel;

		CComboBox* p_ComboBox;
		p_ComboBox = (CComboBox*)GetDlgItem(IDC_CBB_PORTNAME);
		nPortSel=p_ComboBox->GetCurSel();
		p_ComboBox = (CComboBox*)GetDlgItem(IDC_CBB_BAUDRATE);
		nBaudrateSel=p_ComboBox->GetCurSel();
		p_ComboBox = (CComboBox*)GetDlgItem(IDC_CBB_DATABITS);
		nDataBitsSel=p_ComboBox->GetCurSel();
		p_ComboBox = (CComboBox*)GetDlgItem(IDC_CBB_PARITY);
		nParitySel=p_ComboBox->GetCurSel();
		p_ComboBox = (CComboBox*)GetDlgItem(IDC_CBB_STOPBITS);
		nStopBitsSel=p_ComboBox->GetCurSel();


		if (m_port.IsOpen()) m_port.Close();

		LONG    lLastError = ERROR_SUCCESS;

		lLastError = m_port.Open(
			(LPCTSTR)(*m_lstStrPort[nPortSel]),
			this
		);

		if (lLastError != ERROR_SUCCESS)
		{
			DisplayError();
			return;
		}
		
		lLastError = m_port.Setup(
				m_lstBaudrate[nBaudrateSel],
				m_lstDataBits[nDataBitsSel],
				m_lstParity[nParitySel],
				m_lstStopBits[nStopBitsSel]
			);
		
		if (lLastError != ERROR_SUCCESS)
		{
			DisplayError();
			return;
		}

		lLastError = m_port.SetMask(CSerial::EEventBreak |
			CSerial::EEventCTS   |
			CSerial::EEventDSR   |
			CSerial::EEventError |
			CSerial::EEventRing  |
			CSerial::EEventRLSD  |
			CSerial::EEventRecv);

		if (lLastError != ERROR_SUCCESS)
		{
			DisplayError();
			return;
		}

		lLastError = m_port.SetupReadTimeouts(
			CSerial::EReadTimeoutNonblocking
			);

		if (lLastError != ERROR_SUCCESS)
		{
			DisplayError();
			return;
		}

		m_port_opened = true;
		UpdateButtonOC();
	}
	else
	{
		m_port.Close();
		m_port_opened = false;
		UpdateButtonOC();
	}
}

void CMFCCommAssistDlg::OnBnClickedBtnSend()
{
	CString str;
	GetDlgItemText(IDC_EDT_SEND,str);
	m_port.Write((LPCTSTR)str);
}

#define BUFFER_SIZE 64

LRESULT CMFCCommAssistDlg::OnSerialMsg( WPARAM wParam, LPARAM lParam )
{
	
	CSerial::EEvent eEvent = CSerial::EEvent(LOWORD(wParam));
	if (eEvent & CSerial::EEventRecv)
	{
		// Create a clean buffer
		DWORD dwRead;
		char szData[BUFFER_SIZE + 1];
		const int nBuflen = sizeof(szData)-1;
		CString str;
		CString strAll;

		// Obtain the data from the serial port
		do
		{
			m_port.Read(szData,nBuflen,&dwRead);
			szData[dwRead] = '\0';
			str.Format("%s",szData);
			strAll +=str;
			
		} while (dwRead == nBuflen);

		CString strData;
		GetDlgItemText(IDC_EDT_REC,strData);
		strData+=strAll;
		SetDlgItemText(IDC_EDT_REC,strData);
	}

	return 0;
}

void CMFCCommAssistDlg::DisplayError()
{
	DWORD errcode = ::GetLastError();
	TCHAR* buffer;
	::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errcode,
		0,
		( LPTSTR )&buffer,
		0,
		NULL );

	CString strAll;
	GetDlgItemText(IDC_EDT_ERROR,strAll);
	CString str;
	str.Format(_T("%s\n"),buffer);
	strAll += str;
	SetDlgItemText(IDC_EDT_ERROR,strAll);
	LocalFree(buffer);
}