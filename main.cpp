#include <QApplication>
#include <QWidget>
#include <QTableView>
#include<Widget.h>
#include<detail.h>
#include "ConfigurationManager/configurationmanager.h"
#include "TKBSchemaManager/TKBSchemaManager.h"
#include "processhelper.h"

#include "TKB/TKBManager.h"
#include<QDebug>
#include <QStandardItemModel>
#include"GBBMonitorManager\GBBMonitorManager.h"
#include"GBBMonitorManager\SerializedBuffer.h"
#include<AgentBase.h>
#include"Infra_HT_GBB_Defs.h"
#include"EntityFunc.h"
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
        if (theProcessHelper->startNotificationEngine() == SUCCESS)
        {
            bool flag = theMonitorManager.Init();
			qDebug() << flag;
			GBBMonitor::SerializedBuffer* p1 = NULL;
			//获取静态staticdata
			if (theMonitorManager.GetEntitiesData()) {
				//获取填充的数据
				std::list<Entity> m_lstAllEntities;
				p1 = theMonitorManager.GetSerializedBuffer();
				//GetAllEntities，获取系统中结构数目BufferLength
				const void* ptr = (const void*)p1->GetBuffer();
				EntityFunc entityfun;
				int num = entityfun.GetInteger(ptr);
				////SetAllEntities实现
				//for (int i = 0; i < NumOfEntities; ++i) {
				//	m_lstAllEntities.push_back(Entity());
				//}
				status_t status = SUCCESS;
				EntityIterator iter(HT_GBB::EntityMission, status);
				for (iter.begin(); !iter.end(); iter.next()) {
					id_t nMetId = INVALID_MET_ID;
					status = iter.getEntityID(nMetId);
				}
				
			}
            if (theProcessHelper->waitForBlackboardToStart() == SUCCESS)
            {
				
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
