#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <Widget.h>
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
EntityIterator;


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	LoggerUtil::Init();
	if (theConfigManager.Load("UI"))
	{
		theConfigManager.SetApplicationArgs(argc, argv);
		if (theProcessHelper->startNotificationEngine() == SUCCESS
			&&theProcessHelper->waitForBlackboardToStart() == SUCCESS
			&&theMonitorManager.Init())
		{
			Widget widget;
			widget.setWindowTitle("GBBExplorer");
			widget.show();
			return a.exec();
		}
	}

}
