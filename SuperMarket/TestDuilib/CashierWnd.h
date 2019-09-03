#pragma once
#include "common.h"

class CCashierWnd : public WindowImplBase
{
public:
	CCashierWnd(MySQL* pMySQL);
	~CCashierWnd();

	virtual void Notify(TNotifyUI& msg);

protected:
	//WindowImplBase:提供的三个纯虚函数
	//xml文件对应的目录
	virtual CDuiString GetSkinFolder();

	//xml文件名
	virtual CDuiString GetSkinFile();

	//窗口类的名字: 在注册窗口师必须提供
	virtual LPCTSTR GetWindowClassName(void) const;

	void SelectGoods();
	void AddGoodsCount();
	void SubGoodsCount();
	void InsertGoodsList();
	void CancelOrder();
	void CommitOrder();

private:
	MySQL* m_pMySQL;
};