#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <Widget.h>
#include <QProgressDialog>
#include <qmessagebox.h>
#include "ConfigurationManager/configurationmanager.h"
#include "TKBSchemaManager/TKBSchemaManager.h"
#include "processhelper.h"

#include "TKB/TKBManager.h"
#include <QDebug>
#include <QStandardItemModel>
#include "GBBMonitorManager\GBBMonitorManager.h"
#include "GBBMonitorManager\SerializedBuffer.h"
#include "AgentBase.h"
#include "Infra_HT_GBB_Defs.h"
#include "StaticData.h"
#include "DynamicData.h"
#include "detail.h"


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	LoggerUtil::Init();
	if (theConfigManager.Load("UI"))
	{
		theConfigManager.SetApplicationArgs(argc, argv);
		// 创建一个异步等待窗口
		QProgressDialog* waitingDialog = new QProgressDialog(u8"启动资源管理器GBB...", u8"取消", 0, 0, nullptr);
		waitingDialog->setWindowModality(Qt::ApplicationModal);
		waitingDialog->setCancelButton(nullptr); // 禁用取消按钮
		waitingDialog->setMinimumDuration(0); // 立即显示对话框
		waitingDialog->setWindowTitle(u8"等候");
		waitingDialog->show();

		//设置超时
		int timeOut = 12;
		int m_nIntervalsSinceStart = 0;
		while (theProcessHelper->startNotificationEngine() != SUCCESS
			|| theProcessHelper->waitForBlackboardToStart() != SUCCESS
			|| !theMonitorManager.Init())
		{
			// 检查是否超时
			if (m_nIntervalsSinceStart > timeOut)
			{
				QMessageBox::critical(nullptr, u8"错误", u8"请确认资源管理器已启动并运行");
				return 1;
			}
			QCoreApplication::processEvents(); // 处理事件循环,避免界面卡死
			QThread::msleep(100); // 暂停100毫秒
			m_nIntervalsSinceStart++;
		}

		// if条件成立,关闭等待对话框并显示主界面
		waitingDialog->close();
		delete waitingDialog;

		Widget widget;
		widget.setWindowTitle("GBBExplorer");
		widget.show();
		return a.exec();
	}
}
