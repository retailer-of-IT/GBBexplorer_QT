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

class DynamicData : public QObject
{
	Q_OBJECT


public:
	QVector<int> EntitiesId;
public:
	DynamicData();
	int GetEntityCount(int eEntityType);//ÿ�����ڣ���̬��ȡĳ��ʵ������
	void GetEntitiesIDs(int eEntityType);//ÿ�����ڣ���ȡʵ�������metid
	int GetEntityEnumType(long pEntityMet_ID);//ÿ�����ڣ�����metid��ȡ�����ĸ�ʵ��enum
	void GetEntityDynamicData(long pEntityMet_ID); //����id��ȡ��̬����
	~DynamicData();
};
