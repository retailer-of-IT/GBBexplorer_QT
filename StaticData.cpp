#include "StaticData.h"


StaticData::StaticData()
{
	//构造函数初始化
	InitLanguage();       
	InitEnumToString();   
	InitStructures();     
	InitDescriptors();    
	InitEntities();       
	InitMessages();  
	GetAckMessageEnum();
}

void StaticData::InitLanguage()
{
	QDomDocument config;
	QFile file(ConfigPath + "/GeneralConfig.xml");

	if (file.open(QIODevice::ReadOnly) && config.setContent(&file)) {
		file.close();
		QString language = config.firstChildElement("Application").firstChildElement("Language").text();
		AttributeLanguage = QStringLiteral("String%1").arg(language);
	}
	else {
		qDebug() << "Error loading language configuration.";
	}
}

void StaticData::InitEnumToString()
{
	QDir dir(ConfigPath + "/EnumToString/");
	QStringList AllXmlFilesNames = dir.entryList(QStringList() << "*.xml", QDir::Files);

	QStringList AllXmlFiles;
	for (QString &fileName : AllXmlFilesNames) {
		QString fullPath = dir.filePath(fileName); // filePath方法会为文件名添加目录路径
		AllXmlFiles.append(fullPath);
	}

	for (QString &filePath : AllXmlFiles) {
		QFile file(dir.filePath(filePath));
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			SetEnumFromFile(mapValueToEnumToStringIS, filePath);
			file.close();
		}
		else {
			qDebug() << "Error opening file:" << filePath;
		}
	}
}


void StaticData::InitDescriptors()
{
	if (theMonitorManager.GetDesriptorsMappingToStructures())
	{
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfDescriptors = *(int*)(ptr1); ptr1 += sizeof(int);// buff的总长度
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// 结构数据的总个数
		for (int i = 0; i < NumMax; ++i)
		{
			M_DescriptorsInfo &cInfo = M_DescriptorsInfo();
			ptr1 += SetStringFromPtr(ptr1, cInfo.DescriptorName);
			ptr1 += SetStringFromPtr(ptr1, cInfo.StructureName);
			cInfo.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.MaxMessageNum = *(int*)(ptr1); ptr1 += sizeof(int);
			// Define the first field as "first field"
			for each(StaticData::M_StructuresInfo structInfo in vecStructuresInfo)
			{
				if (structInfo.StructureName == cInfo.StructureName)
				{
					if (structInfo.NumOfFields > 0)
					{
						structInfo.vecField[0].IsThisFirstInDes = true;
					}
				}
			}
			//调试发现只有maxmessagenum!=0的才会显示在界面上，这里做修改
			if (cInfo.MaxMessageNum != 0) {
				vecDescriptorsInfoInGBBEx.push_back(cInfo);
			}
			vecDescriptorsInfo.push_back(cInfo);
		}
	}
}
void StaticData::InitStructures()
{
	if (theMonitorManager.GetStructuresData())
	{
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfStructures = *(int*)(ptr1); ptr1 += sizeof(int);// buff的总长度
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// 结构数据的总个数
		for (int i = 0; i < NumMax; ++i)
		{
			vecStructuresInfo.push_back(M_StructuresInfo());
			M_StructuresInfo &cInfo = vecStructuresInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.StructureName);
			cInfo.NumOfFields = *(int*)(ptr1); ptr1 += sizeof(int);
			int NumberOfArrays = 0;
			for (int j = 0; j < cInfo.NumOfFields; ++j)
			{
				cInfo.vecField.push_back(M_FieldInfo());
				M_FieldInfo &cInfo2 = cInfo.vecField[j + NumberOfArrays];
				ptr1 += SetStringFromPtr(ptr1, cInfo2.FieldName);
				cInfo2.FieldType = *(FieldType*)(ptr1); ptr1 += sizeof(int);
				ptr1 += SetStringFromPtr(ptr1, cInfo2.NestedName);
				cInfo2.ArrayMaxSize = *(int*)(ptr1); ptr1 += sizeof(int);
				cInfo2.ShowField = true;
				// Is this array field?
				if (cInfo2.ArrayMaxSize > 0)
				{
					//这个reference类型的作用是在array类型时，再赋复制一列，复制的那一列field类型为reference类型
					if (cInfo2.FieldType != Reference)
					{
						M_FieldInfo info;
						info.FieldType = cInfo2.FieldType;
						info.ShowField = true;
						cInfo2.FieldType = Array;
						cInfo.vecField.push_back(info);

						M_FieldInfo &cInfo3 = cInfo.vecField[j + 1 + NumberOfArrays];
						cInfo3.FieldName = cInfo.vecField[j + NumberOfArrays].FieldName;
						cInfo3.NestedName = cInfo.vecField[j + NumberOfArrays].NestedName;
						++NumberOfArrays;
					}
					// In case the array is reference type then the table don't display the array data, only if opening the "Array Dialog"
					else
					{
						cInfo2.FieldType = Array;
					}
				}
			}
		}
	}
}
void StaticData::InitEntities()
{
	if (theMonitorManager.GetEntitiesData()) {
		//获取填充的数据
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfEntities = *(int*)(ptr1); ptr1 += sizeof(int);// buff的总长度
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// 结构数据的总个数
		for (int i = 0; i < NumMax; ++i)
		{
			vecEntityInfo.push_back(M_EntityInfo());
			M_EntityInfo &cInfo = vecEntityInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.EntityName);
			cInfo.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.MaxEntityNum = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.NumOfDescriptors = *(int*)(ptr1); ptr1 += sizeof(int);
			for (int j = 0; j < cInfo.NumOfDescriptors; ++j)
			{
				std::string st1 = "";
				ptr1 += SetStringFromPtr(ptr1, st1);
				int EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
				cInfo.mapDescriptores[EnumType] = st1;
			}
		}
		for (int i = 0; i < NumMax; ++i)
		{
			if (vecEntityInfo[i].MaxEntityNum != 0)
				vecEntityInfoInGBBEx.push_back(vecEntityInfo[i]);
		}
	}
}
void StaticData::InitMessages()
{
	if (theMonitorManager.GetMessagesData()) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfMessages = *(int*)(ptr1); ptr1 += sizeof(int);// buff的总长度
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// 结构数据的总个数
		for (int i = 0; i < NumMax; ++i)
		{
			vecMessageInfo.push_back(M_MessageInfo());
			M_MessageInfo &cInfo = vecMessageInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.MessageName);
			cInfo.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.m_bIsDescAsMessage = *(bool*)(ptr1); ptr1 += sizeof(bool);
			cInfo.m_bWithAck = *(bool*)(ptr1); ptr1 += sizeof(bool);
			cInfo.MaxMessageNum = *(int*)(ptr1); ptr1 += sizeof(int);
			ptr1 += SetStringFromPtr(ptr1, cInfo.DescriptorName);
		}
		for (int i = 0; i < NumMax; ++i)
		{
			if (vecMessageInfo[i].MaxMessageNum != 0)
				vecMessageInfoInGBBEx.push_back(vecMessageInfo[i]);
		}
	}
}

void StaticData::GetAckMessageEnum()
{
	if (theMonitorManager.GetAckMessageEnum()) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		ptr1 += sizeof(int);// Get after buffer size
		AckMessageEnum = *(int*)(ptr1); ptr1 += sizeof(int);
	}
}

int StaticData::SetStringFromPtr(char* CurrentIntPtr, std::string &StringName)
{
	StringName = std::string(CurrentIntPtr);
	return StringName.length() + 1;
}

void StaticData::SetEnumFromFile(QMap<QString, QMap<int, QString>>& ValueToEnumTypesIS, QString & FilePath)
{
	QDomDocument enumToStringDocument;
	QFile file(FilePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qWarning() << "Failed to open file:" << FilePath;
		return;
	}

	if (!enumToStringDocument.setContent(&file)) {
		file.close();
		qWarning() << "Failed to load XML content from file";
		return;
	}
	file.close();

	QDomElement enumToStringNode = enumToStringDocument.firstChildElement("EnumToString").firstChildElement("EnumToString");
	if (!enumToStringNode.isNull())
	{
		QDomNodeList enumNodes = enumToStringNode.childNodes();
		for (int i = 0; i < enumNodes.count(); ++i)
		{
			QDomElement enumNode = enumNodes.at(i).toElement();
			if (enumNode.isNull()) continue;

			QMap<int, QString> valueToEnumItemIS;
			QDomNodeList items = enumNode.childNodes();
			for (int j = 0; j < items.count(); ++j)
			{
				QDomElement item = items.at(j).toElement();
				if (item.isComment()) continue;

				bool ok;
				int val = item.attribute("Val").toInt(&ok);
				if (!ok) {
					qWarning() << "Invalid value attribute for enum item";
					continue;
				}
				QString languageValue = item.attribute(AttributeLanguage);
				valueToEnumItemIS[val] = languageValue; 
			}
			ValueToEnumTypesIS[enumNode.tagName()] = valueToEnumItemIS;
		}
	}
}

StaticData::~StaticData()
{
}

