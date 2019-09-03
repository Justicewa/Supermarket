#include "Login.h"
#include "MainWnd.h"
#include "CashierWnd.h"

//ASCII --> 7个比特位

LoginWnd::LoginWnd(MySQL* pMySQL)
: m_pMySQL(pMySQL)
{}
//xml文件对应的目录
CDuiString LoginWnd::GetSkinFolder(){
	return _T("");
};
//xml文件的名字
CDuiString LoginWnd::GetSkinFile(){
	return _T("LoginWnd.xml");
};
//窗口类的名字：在注册窗口时必须提供
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
	//从编辑框中获取用户名和密码
	//m_PaintManager返回值是子类指针， CEditUI* pEditUserName是基类指针
	CEditUI* pEditUserName = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_NAME"));
	CDuiString strUserName = pEditUserName->GetText();

	CEditUI* pEditPassword = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_PASSWORD"));
	CDuiString strUserPassword = pEditPassword->GetText();

	//查看输入用户名是否为空
	if (strUserName.IsEmpty()){
		MessageBox(m_hWnd, _T("请输入用户名"), _T("Cashier"), IDOK);
		return;
	}

	if (strUserPassword.IsEmpty()){
		MessageBox(m_hWnd, _T("请输入密码"), _T("Cashier"), IDOK);
		return;
	}
	//查询数据库，检测该用户是否存在
	string strSQL("select * from  employee where Name = '");
	strSQL += UnicodeToANSI(strUserName);
	strSQL += "';";

	vector<vector<string>> vRet = m_pMySQL->Select(strSQL);
	if (vRet.empty())
	{
		MessageBox(m_hWnd, _T("用户名错误"), _T("Caisher"), IDOK);
		return;
	}

	string userpassward = UnicodeToANSI(strUserPassword);
	if (userpassward != vRet[0][4])
	{
		MessageBox(m_hWnd, _T("用户密码错误"), _T("Caisher"), IDOK);
		return;
	}
	//隐藏登录窗口
	ShowWindow(false);

	//创建主窗口
	int flag = 1;
	if (vRet[0][5] == "管理员")
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