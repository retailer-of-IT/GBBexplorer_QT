#pragma once

#include <QObject>
#include "ConfigurationManager/configurationmanager.h"
#include "TKBSchemaManager/TKBSchemaManager.h"
#include "processhelper.h"
#include "TKB/TKBManager.h"
#include "GBBMonitorManager\GBBMonitorManager.h"
#include "GBBMonitorManager\SerializedBuffer.h"
#include "AgentBase.h"
#include "Infra_HT_GBB_Defs.h"
#include "infrasim_ht_gbb_defs.h"
#include <QVector>
#include <QFile>
#include <QDomElement>
#include <QDomDocument>
#include <QDomNode>
#include <QTextStream>
#include <QDebug>

class DynamicData : public QObject
{
	Q_OBJECT


public:
	QVector<int> EntitiesId;
	QString configPath = "D:\\CHSim-TKE_GBBExplorer\\Applications\\SSGProduct\\Config\\GBBExplorerConfig.xml";
	char* m_descriptorBuffer = nullptr;
	int m_descriptorBufferSize = 0;

public:
	DynamicData();
	//DynamicData(QString configPath);
	int GetEntityCount(int eEntityType);//ÿ�����ڣ���̬��ȡĳ��ʵ������
	void GetEntitiesIDs(int eEntityType);//ÿ�����ڣ���ȡʵ�������metid
	int GetEntityEnumType(long pEntityMet_ID);//ÿ�����ڣ�����metid��ȡ�����ĸ�ʵ��enum
	void GetEntityDynamicData(long pEntityMet_ID); //����id��ȡ��̬����
	void GetEntityDynamicData(long pEntityMet_ID, char* m_descriptorBuffer);
	~DynamicData();
};
