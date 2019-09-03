#include "Login.h"
#include "MainWnd.h"
#include "CashierWnd.h"

//ASCII --> 7������λ

LoginWnd::LoginWnd(MySQL* pMySQL)
: m_pMySQL(pMySQL)
{}
//xml�ļ���Ӧ��Ŀ¼
CDuiString LoginWnd::GetSkinFolder(){
	return _T("");
};
//xml�ļ�������
CDuiString LoginWnd::GetSkinFile(){
	return _T("LoginWnd.xml");
};
//����������֣���ע�ᴰ��ʱ�����ṩ
LPCTSTR LoginWnd::GetWindowClassName(void) const{
	return _T("LoginWnd");
};

void LoginWnd::Notify(TNotifyUI& msg){
	CDuiString strName =  msg.pSender->GetName();
	if (msg.sType == _T("click")){
		if (strName == _T("BTN_MIN"))
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if (strName == _T("BTN_CLOSE"))
			LoginWnd::Close();
		else if (strName == _T("BTN_LOGIN"))
			LoginWnd::LogIn();
	}
}

void LoginWnd::LogIn(){
	//�ӱ༭���л�ȡ�û���������
	//m_PaintManager����ֵ������ָ�룬 CEditUI* pEditUserName�ǻ���ָ��
	CEditUI* pEditUserName = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_NAME"));
	CDuiString strUserName = pEditUserName->GetText();

	CEditUI* pEditPassword = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_PASSWORD"));
	CDuiString strUserPassword = pEditPassword->GetText();

	//�鿴�����û����Ƿ�Ϊ��
	if (strUserName.IsEmpty()){
		MessageBox(m_hWnd, _T("�������û���"), _T("Cashier"), IDOK);
		return;
	}

	if (strUserPassword.IsEmpty()){
		MessageBox(m_hWnd, _T("����������"), _T("Cashier"), IDOK);
		return;
	}
	//��ѯ���ݿ⣬�����û��Ƿ����
	string strSQL("select * from  employee where Name = '");
	strSQL += UnicodeToANSI(strUserName);
	strSQL += "';";

	vector<vector<string>> vRet = m_pMySQL->Select(strSQL);
	if (vRet.empty())
	{
		MessageBox(m_hWnd, _T("�û�������"), _T("Caisher"), IDOK);
		return;
	}

	string userpassward = UnicodeToANSI(strUserPassword);
	if (userpassward != vRet[0][4])
	{
		MessageBox(m_hWnd, _T("�û��������"), _T("Caisher"), IDOK);
		return;
	}
	//���ص�¼����
	ShowWindow(false);

	//����������
	int flag = 1;
	if (vRet[0][5] == "����Ա")
	{
		MainWnd mainWnd(m_pMySQL);
		mainWnd.Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		mainWnd.CenterWindow();
		mainWnd.ShowModal();
	}
	else
	{
		CCashierWnd mainWnd(m_pMySQL);
		mainWnd.Create(NULL, _T("CashierWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		mainWnd.CenterWindow();
		mainWnd.ShowModal();
	}

}