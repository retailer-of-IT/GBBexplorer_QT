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

void SetEntity(Entity CurrentEntity) {

}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Widget widget;
    QTabWidget tabWidget;
    LoggerUtil::Init();
    if (theConfigManager.Load("UI"))
    {
        theConfigManager.SetApplicationArgs(argc, argv);
        if (theProcessHelper->startNotificationEngine() == SUCCESS
			&&theProcessHelper->waitForBlackboardToStart() == SUCCESS
			&&theMonitorManager.Init())
        {
				StaticData staticdata;
				staticdata.InitDescriptors();
				staticdata.InitStructures();
				staticdata.InitEntities();
				staticdata.InitMessages();

				//初始化实体
				//entityfunc.InitEntities();
				status_t status = SUCCESS;
				EntityIterator iter(HT_GBB::EntityMission, status);
				for (iter.begin(); !iter.end(); iter.next()) {
					id_t nMetId = INVALID_MET_ID;
					status = iter.getEntityID(nMetId);
				}
				
			}
        }
    tabWidget.addTab(new QWidget(), "tab_1");
    tabWidget.addTab(new QWidget(), "tab_2");
    //detail detailpage;
    widget.setWindowTitle("GBBExplorer");
    widget.show();
    return a.exec();
}
