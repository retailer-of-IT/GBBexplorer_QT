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
#include "StaticData.h"

class DynamicData : public QObject
{
	Q_OBJECT


public:
	QVector<int> EntitiesId;
	QVector<StaticData::M_FieldInfo> FieldsList;

	QString configPath = "D:/CHSim-TKE_GBBExplorer/Applications/SSGProduct/Config/GBBExplorerConfig.xml";
	char* m_descriptorPtr = nullptr;
	int m_descriptorBufferSize = 0;
	int m_nCurrentPos = 0;
	StaticData staticdata;

public:
	DynamicData();
	//DynamicData(QString configPath);
	int GetEntityCount(int eEntityType);//ÿ�����ڣ���̬��ȡĳ��ʵ������
	void GetEntitiesIDs(int eEntityType);//ÿ�����ڣ���ȡʵ�������metid
	int GetEntityEnumType(long pEntityMet_ID);//ÿ�����ڣ�����metid��ȡ�����ĸ�ʵ��enum
	int GetMessageCount(int eMessageType); //ÿ�����ڻ�ȡĳ����Ϣ������
	int GetDescriptorCount(int eDescriptorType); //ÿ�����ڻ�ȡĳ��������������
	//void GetEntityDynamicData(int nEntityID); //����id��ȡ��̬����
	void GetEntityDynamicData(int eEntityType);//��ȡĳ��ʵ���ȫ����̬����
	bool ReadRowFromIntPtr(char* ptr, QVector<StaticData::M_FieldInfo> FieldsList, bool isThisEntity, int bufferLength);
	bool ReadFieldFromPtr(char* fieldPtr, StaticData::M_FieldInfo currentField, int bufferLength);//���ַ������и�ĳ����ĳ��field
	//bool ShowArrayField(char* ptr)
	std::string GetString(char* CurrentPtr);//��ȡ�ַ���
	void getAfterString(char* currentPtr, int bufferLength); //����������ȡ�ַ���
	int SetStringFromPtr(char* CurrentIntPtr, std::string &StringName);
	~DynamicData();
};
