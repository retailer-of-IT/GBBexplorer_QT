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
#include <cmath>
#include<qtablewidget.h>
#include "StaticData.h"
#include "Utils.h"

class detail;

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
	detail* GridView;
	double m_dDoubleValue = 0.0;
	double m_dSpeedValue = 0;

public:
	DynamicData();
	//DynamicData(QString configPath);
	int GetEntityCount(int eEntityType);//每个周期，动态获取某个实体数量
	void GetEntitiesIDs(int eEntityType);//每个周期，获取实体的所有metid
	int GetEntityEnumType(long pEntityMet_ID);//每个周期，根据metid获取属于哪个实体enum
	int GetMessageCount(int eMessageType); //每个周期获取某个消息的数量
	int GetDescriptorCount(int eDescriptorType); //每个周期获取某个描述符的数量
	//void GetEntityDynamicData(int nEntityID); //根据id获取动态数据
	void GetEntityDynamicData(int eEntityType, detail*& GridView);//获取某个实体的全部动态数据
	bool ReadRowFromIntPtr(char * ptr, QTableWidget*& tableWidget, int ElementIndex, QVector<StaticData::M_FieldInfo> FieldsList, bool IsThisCompareTab, bool isThisEntity, int bufferLength);
	bool ReadFieldFromPtr(char*& fieldPtr, QTableWidgetItem*& item, StaticData::M_FieldInfo currentField, int bufferLength);//从字符流中切割某个出某个field,传入的是一个单元格
	void FinishReadRow(QTableWidgetItem*& item, QVector<StaticData::M_FieldInfo> FieldsList,int LoopIndex, int ColumnIndex, int RowIndex, bool IsThisCompareTab, bool AlsoLoop);
	void SetElementIndex(bool IsThisCompareTab, int ElementIndex, int& RowIndex, int& ColumnIndex, int& LoopIndex);
	void IncreaseLoopIndex(bool AlsoLoopIndex, bool IsVertical, int& RowIndex, int& ColumnIndex, int& LoopIndex);
	//bool ShowArrayField(char* ptr)
	double GetAltData(double Data, int DisplayState);
	double GetAzimuth(double Data, int DisplayState);
	QString GetBoolean(std::string Data, int DisplatState);
	QString GetEnum2String(int Data, int DislayState, std::string NestedName);
	QVariant GetLatLong(double Data, int DisplayState, Utils::CoordinateType Type);
	QVariant GetSpeed(double Data, int DisplayState);
	QVariant GetTime(long long Data, int DisplayState);
	double GetRange(double Data, int DisplayState, int DecimalPlaces);
	std::string GetString(char* CurrentPtr);//读取字符串
	void getAfterString(char* currentPtr, int bufferLength); //跳过，不读取字符串
	std::string ConvertIntToEnum2String(int Data, std::string NestedName);
	int SetStringFromPtr(char* CurrentIntPtr, std::string &StringName);
	double Mathround(double Data, int DecimalPlaces);//用于保留DecimalPlaces位小数
	~DynamicData();
};
