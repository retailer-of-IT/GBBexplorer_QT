#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <Widget.h>
#include <detail.h>
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
#include "EntityFunc.h"
#include "StaticData.h"
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
			status_t status = SUCCESS;
			EntityIterator iter(HT_GBB::EntityMission, status);
			for (iter.begin(); !iter.end(); iter.next()) {
				id_t nMetId = INVALID_MET_ID;
				status = iter.getEntityID(nMetId);
			}
			Widget widget;
			widget.setWindowTitle("GBBExplorer");
			widget.show();
			return a.exec();
		}
	}

}
