#include "common.h"

class LoginWnd : public WindowImplBase{
public:
	LoginWnd(MySQL* pMySQL);
	//����(������Ϣ��
	virtual void Notify(TNotifyUI& msg);
	
	//��¼
	void LogIn();
private:

	//xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	//xml�ļ�������
	virtual CDuiString GetSkinFile();

	//����������֣���ע�ᴰ��ʱ�����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;
	MySQL* m_pMySQL;
};