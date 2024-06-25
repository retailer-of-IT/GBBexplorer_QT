#pragma once
#include "ConfigurationManager/configurationmanager.h"
#include "TKBSchemaManager/TKBSchemaManager.h"
#include "processhelper.h"
#include "TKB/TKBManager.h"
#include "GBBMonitorManager\GBBMonitorManager.h"
#include "GBBMonitorManager\SerializedBuffer.h"
#include "AgentBase.h"
#include "Infra_HT_GBB_Defs.h"
#include "infrasim_ht_gbb_defs.h"
#include <QObject>
#include <QVector>
#include <QMap>
#include <QDir>
#include <QFile>
#include <QDomDocument>
#include <qdebug.h>


class StaticData : public QObject
{
	Q_OBJECT

public:
	//定义field的枚举类型
	enum FieldType {
		Default = -1,
		Integer = 0,
		Double = 1,
		Time = 2,
		MET_ID = 3,
		Latitude = 4,
		Longitude = 5,
		LongLong = 6,
		Alt = 7,
		Azimuth = 8,
		Speed = 9,
		Short = 10,
		Char = 11,
		Boolean = 12,
		String = 13,
		Reference = 14,
		Enum2String = 15,
		Long = 16,
		Range = 17,
		Array = 18,
		IndexColumn = 19
	};
	struct M_DescriptorsInfo
	{
		int EnumType;
		int MaxMessageNum;
		std::string DescriptorName = "";
		std::string StructureName = "";
	};
	struct M_FieldInfo
	{
		FieldType FieldType = Default;//源代码中默认为default
		int ArrayMaxSize = -1;
		std::string FieldName = "";
		std::string NestedName = "";// If the field is a structure – the name of it. Empty string if not a structure
		int DisplayState = 0;       // Define the display state for the current field
		std::string DescriptorName = ""; // The descriptor the field belong to
		bool ShowField = true;
		bool mDiscriptorShow = true;
		bool IsThisFirstInDes = false;
		std::string ReferenceStructureName = "";// In case the field is from type "Array of struct" this field holds the struct name
	};
	struct M_StructuresInfo
	{
		int NumOfFields;
		std::string StructureName = "";
		QVector<M_FieldInfo> vecField;
	};


	struct M_EntityInfo
	{
		int EnumType;
		int MaxEntityNum;
		int NumOfDescriptors;
		std::string EntityName = "";
		QMap<int, std::string> mapDescriptores;
	};

	struct M_MessageInfo
	{
		int EnumType;
		bool m_bIsDescAsMessage;
		bool m_bWithAck;
		int MaxMessageNum;
		std::string MessageName = "";
		std::string DescriptorName = "";
	};

	//获取Structures信息,重要
	QVector<M_StructuresInfo> vecStructuresInfo;
	//获取Descriptors信息
	QVector<M_DescriptorsInfo> vecDescriptorsInfo;
	//实际gbbexplorer界面展示出来的描述符信息,最大数量为0的不展示
	QVector<M_DescriptorsInfo> vecDescriptorsInfoInGBBEx;
	//获取Entity信息
	QVector<M_EntityInfo> vecEntityInfo;
	//实际gbbexplorer界面展示出来的描述符信息,最大数量为0的不展示
	QVector<M_EntityInfo> vecEntityInfoInGBBEx;
	//获取Message信息
	QVector<M_MessageInfo> vecMessageInfo;
	//实际gbbexplorer界面展示出来的描述符信息,最大数量为0的不展示
	QVector<M_MessageInfo> vecMessageInfoInGBBEx;
	//保存EnumToString值的字典
	QMap<QString, QMap<int, QString>> mapValueToEnumToStringIS;

	//config配置路径，根据需要修改
	QString ConfigPath = "D:/CHSim-TKE_GBBExplorer/Applications/SSGProduct/Config";
	//使用的语言
	QString AttributeLanguage;

public:
	StaticData();
	void InitLanguage();       // Set require language 
	void InitEnumToString();   // Set the EnumToString variable
	void InitStructures();     // Create the Structures Static List
	void InitDescriptors();    // Create the Descriptors Static List
	void InitEntities();       // Create the Entities Static List
	void InitMessages();      // Create the Messages Static List
	~StaticData();

private:
	int SetStringFromPtr(char* CurrentIntPtr, std::string &StringName); // 用于切割buffer，每到\0截至
	void SetEnumFromFile(QMap<QString, QMap<int, QString>>& ValueToEnumTypesIS, QString& FilePath);//用于读取EnumtoString
};
