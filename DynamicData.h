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
	int GetEntityCount(int eEntityType);//每个周期，动态获取某个实体数量
	void GetEntitiesIDs(int eEntityType);//每个周期，获取实体的所有metid
	int GetEntityEnumType(long pEntityMet_ID);//每个周期，根据metid获取属于哪个实体enum
	void GetEntityDynamicData(long pEntityMet_ID); //根据id获取动态数据
	void GetEntityDynamicData(long pEntityMet_ID, char* m_descriptorBuffer);
	~DynamicData();
};
