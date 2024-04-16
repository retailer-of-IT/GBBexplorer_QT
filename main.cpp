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
            bool b = theMonitorManager.Init();
			qDebug() << b;
			GBBMonitor::SerializedBuffer* p1 = NULL;
			GBBMonitor::SerializedBuffer* p2 = NULL;
			GBBMonitor::SerializedBuffer* p3 = NULL;
			GBBMonitor::SerializedBuffer* p4 = NULL;
			//获取静态staticdata
			if (theMonitorManager.GetEntitiesData()) {
				//获取填充的数据
				std::list<Entity> m_lstAllEntities;
				p1 = theMonitorManager.GetSerializedBuffer();
				//for (const char* p = p1->GetBuffer(); *p != '\0'; ++p) {
 				//	qDebug() << *p;
				//}
				//GetAllEntities，获取系统中结构数目BufferLength
				void* ptr = (void*)p1->GetBuffer();
				int CurrentPos = 0;
				CurrentPos	+= sizeof(int32_t);
				int NumOfEntities = *reinterpret_cast<const int32_t*>(static_cast<const char*>(ptr) + (CurrentPos - sizeof(int32_t)));
				//SetAllEntities实现
				for (int i = 0; i < NumOfEntities; ++i) {
					m_lstAllEntities.push_back(Entity());
					EntityFunc::SetStringFromPtr
				}
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
