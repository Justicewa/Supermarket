#include "common.h"

class LoginWnd : public WindowImplBase{
public:
	LoginWnd(MySQL* pMySQL);
	//密码(拦截消息）
	virtual void Notify(TNotifyUI& msg);
	
	//登录
	void LogIn();
private:

	//xml文件对应的目录
	virtual CDuiString GetSkinFolder();

	//xml文件的名字
	virtual CDuiString GetSkinFile();

	//窗口类的名字：在注册窗口时必须提供
	virtual LPCTSTR GetWindowClassName(void) const;
	MySQL* m_pMySQL;
};