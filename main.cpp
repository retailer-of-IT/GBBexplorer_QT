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
		// ����һ���첽�ȴ�����
		QProgressDialog* waitingDialog = new QProgressDialog(u8"������Դ������GBB...", u8"ȡ��", 0, 0, nullptr);
		waitingDialog->setWindowModality(Qt::ApplicationModal);
		waitingDialog->setCancelButton(nullptr); // ����ȡ����ť
		waitingDialog->setMinimumDuration(0); // ������ʾ�Ի���
		waitingDialog->setWindowTitle(u8"�Ⱥ�");
		waitingDialog->show();

		//���ó�ʱ
		int timeOut = 12;
		int m_nIntervalsSinceStart = 0;
		while (theProcessHelper->startNotificationEngine() != SUCCESS
			|| theProcessHelper->waitForBlackboardToStart() != SUCCESS
			|| !theMonitorManager.Init())
		{
			// ����Ƿ�ʱ
			if (m_nIntervalsSinceStart > timeOut)
			{
				QMessageBox::critical(nullptr, u8"����", u8"��ȷ����Դ������������������");
				return 1;
			}
			QCoreApplication::processEvents(); // �����¼�ѭ��,������濨��
			QThread::msleep(100); // ��ͣ100����
			m_nIntervalsSinceStart++;
		}

		// if��������,�رյȴ��Ի�����ʾ������
		waitingDialog->close();
		delete waitingDialog;

		Widget widget;
		widget.setWindowTitle("GBBExplorer");
		widget.show();
		return a.exec();
	}
}
