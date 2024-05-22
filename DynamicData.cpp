#include "DynamicData.h"
#include "qdebug.h"

//DynamicData::DynamicData()
//{
//}

DynamicData::DynamicData()
{
	QFile configFile(configPath);
	configFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QDomDocument configDoc;
	if (!configDoc.setContent(&configFile)) {
		// 处理解析XML失败的情况
		configFile.close();
		return;
	}
	QDomElement gbbExplorerElement = configDoc.documentElement();
	QDomElement dataElement = gbbExplorerElement.firstChildElement("Data");
	QString descriptorBufferSizeStr = dataElement.firstChildElement("DescriptorBufferSize").text();
	m_descriptorBufferSize = descriptorBufferSizeStr.toInt();

	// 分配内存
	m_descriptorPtr = static_cast<char*>(malloc(m_descriptorBufferSize));
	qDebug() << m_descriptorBufferSize;
}

int DynamicData::GetEntityCount(int eEntityType)
{
	if (theMonitorManager.GetEntityCount(eEntityType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
		int entityCount = *(int*)(ptr1);
		return entityCount;
	}
}

void DynamicData::GetEntitiesIDs(int eEntityType)
{
	if (theMonitorManager.GetEntitiesIDs(eEntityType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度

															 //将此周期内的entity_id全部压入
		EntitiesId.push_back(*(int*)(ptr1)); ptr1 += sizeof(int);
		int n = GetEntityCount(eEntityType);
		for (int i = 1; i < n; i++) {
			EntitiesId.push_back(*(int*)(ptr1));
			ptr1 += sizeof(int);
		}
		qDebug() << "hello";
	}
}

int DynamicData::GetEntityEnumType(long pEntityMet_ID)
{
	if (theMonitorManager.GetEntityEnumType(pEntityMet_ID)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
		int enumType = *(int*)(ptr1);
		return enumType;
	}
}

int DynamicData::GetMessageCount(int eMessageType)
{
	if (theMonitorManager.GetMessageCount(eMessageType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
		int messageCount = *(int*)(ptr1);
		return messageCount;
	}
}

int DynamicData::GetDescriptorCount(int eDescriptorType)
{
	if (theMonitorManager.GetDescriptorCount(eDescriptorType)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
		int descriptorCount = *(int*)(ptr1);
		return descriptorCount;
	}
}

//void DynamicData::GetEntityDynamicData(int nEntityID)
//{
//	if (theMonitorManager.GetEntityDynamicData(nEntityID)) {
//		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
//		char* ptr = (char*)p->GetBuffer();
//		char* ptr1 = ptr;
//		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
//		int NumOfBuffer2 = *(int*)(ptr1); ptr1 += sizeof(int);
//		char a[10000];
//		for (int i = 0; i < 10000; i++) {
//			a[i] = *ptr1;
//			ptr1++;
//		}
//		qDebug() << "hello";
//	}
//}

void DynamicData::GetEntityDynamicData(int eEntityType)
{
	staticdata.InitEntities();
	staticdata.InitDescriptors();
	staticdata.InitStructures();
	staticdata.InitMessages();
	m_nCurrentPos = 0;
	for each(StaticData::M_EntityInfo vecInfo in staticdata.vecEntityInfo)
	{
		if (vecInfo.EnumType == eEntityType)
		{
			//为每个描述符在分配的空间中占位，以enumtype
			for (const auto& key : vecInfo.mapDescriptores.keys()) {
				//*(int*)(m_descriptorPtr + m_nCurrentPos) = staticdata.vecDescriptorsInfo[i].EnumType;
				*(int*)(m_descriptorPtr + m_nCurrentPos) = key;
				m_nCurrentPos += sizeof(int);
				for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfoInGBBEx)
				{
					if (desInfo.EnumType == key)
					{
						for each(StaticData::M_StructuresInfo structInfo in staticdata.vecStructuresInfo)
						{
							if (structInfo.StructureName == desInfo.StructureName)
							{
								for each(StaticData::M_FieldInfo fieldInfo in structInfo.vecField)
								{
									FieldsList.push_back(fieldInfo);
								}
							}
						}
					}
				}
			}
			*(int*)(m_descriptorPtr + m_nCurrentPos) = -1;
		}
	}
	//staticdata.InitDescriptors();
	//int num = staticdata.vecDescriptorsInfo.size();
	//int m_nCurrentPos = 0;
	////为每个描述符在分配的空间中占位，以enumtype
	//for (int i = 0; i < num; ++i) {
	//	*(int*)(m_descriptorPtr + m_nCurrentPos) = staticdata.vecDescriptorsInfo[i].EnumType;
	//	m_nCurrentPos += sizeof(int);
	//}
	//*(int*)(m_descriptorPtr + m_nCurrentPos) = -1;

	GetEntitiesIDs(eEntityType);//每个周期，获取对应id实体的所有metid
	int num2 = EntitiesId.size();
	for (int i = 0; i < num2; i++) {
		if (theMonitorManager.GetEntityDynamicData(EntitiesId[i], m_descriptorPtr)) {
			GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
			char* ptr = (char*)p->GetBuffer();
			//对应的DataBufferPtr
			char* ptr1 = ptr;
			int bufferLength = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
			m_nCurrentPos = 0;
			//用于标识是开头的描述符
			bool DescriptorInitialized = *(bool*)ptr1; ptr1 += sizeof(bool);
			//int met_id = *(int*)ptr1; ptr1 += sizeof(int);
			//std::string network_name;
			//ptr1 += SetStringFromPtr(ptr1, network_name);
			//std::string network_obj;
			//ptr1 += SetStringFromPtr(ptr1, network_obj);
			//TODO dynamicdata.cs中 GetEntityTableData等函数使用到的 ReadRowFromIntPtr函数功能
			//用于读取对应id的所有field的值（一行）并进行切分，非数组array结构
			bool flag = ReadRowFromIntPtr(ptr1, FieldsList, true, bufferLength);
		}
	}
	m_nCurrentPos = 0;
	qDebug() << "hello";
}

bool DynamicData::ReadRowFromIntPtr(char * ptr, QVector<StaticData::M_FieldInfo> FieldsList, bool isThisEntity, int bufferLength)
{
	int LoopIndex = 0;
	bool DescriptorInitialized = false;
	for (LoopIndex = 0; LoopIndex < FieldsList.size(); ++LoopIndex)
	{
		if (isThisEntity)
		{
			DescriptorInitialized = true;

		}
		// In case the (descriptor is Init AND DescriptorShow) OR (this is message)
		if (DescriptorInitialized || !isThisEntity)
		{
			//普通的field(非数组array)
			if (FieldsList[LoopIndex].FieldType != StaticData::FieldType::Array)
			{
				if (!ReadFieldFromPtr(ptr, FieldsList[LoopIndex], bufferLength))
				{
					return false;
				}
			}
			//array类型，单独展示
			else
			{
				//
			}
		}
		else //The descriptor is not Init OR descriptor is not show
		{
			
		}
	}
	return true;
}


bool DynamicData::ReadFieldFromPtr(char * fieldPtr, StaticData::M_FieldInfo currentField,int bufferLength)
{
	switch (currentField.FieldType)
	{
	case StaticData::FieldType::Alt:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Azimuth:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Boolean:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			bool a = *(bool*)(fieldPtr + m_nCurrentPos);
			m_nCurrentPos += 1;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Char:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			bool a = *(fieldPtr + m_nCurrentPos);
			m_nCurrentPos += 1;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Double:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Enum2String:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			char a[4];
			for (int i = 0; i < 4; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Integer:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			int n = *(int*)(fieldPtr);
			m_nCurrentPos += 4;
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Latitude:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Longitude:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Long:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			char a[4];
			for (int i = 0; i < 4; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::LongLong:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::MET_ID:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			int n = *(int*)(fieldPtr);
			m_nCurrentPos += 4;
			//char a[4];
			//for (int i = 0; i < 4; i++) {
			//	a[i] = *(fieldPtr + m_nCurrentPos);
			//	m_nCurrentPos++;
			//}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Reference:
		if (m_nCurrentPos + 4 <= bufferLength)
		{
			char a[4];
			for (int i = 0; i < 4; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Short:
		if (m_nCurrentPos + 2 <= bufferLength)
		{
			char a[2];
			for (int i = 0; i < 2; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Speed:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::String:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			std::string s = DynamicData::GetString(fieldPtr);
			qDebug() << "1";
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Time:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Range:
		if (m_nCurrentPos + 8 <= bufferLength)
		{
			char a[8];
			for (int i = 0; i < 8; i++) {
				a[i] = *(fieldPtr + m_nCurrentPos);
				m_nCurrentPos++;
			}
		}
		else
		{
			return false;
		}
		break;
	case StaticData::FieldType::Default:
		break;
	default:
		break;
	}
	return true;
}

std::string DynamicData::GetString(char* currentPtr)
{
	std::string StringName = std::string(currentPtr + m_nCurrentPos);
	m_nCurrentPos += StringName.length() + 1;
	return StringName;
}

void DynamicData::getAfterString(char* currentPtr ,int bufferLength)
{
	int len = 0;
	if (!currentPtr || *currentPtr == '\0')
		return;

	while (*currentPtr != '\0')
	{
		++currentPtr;
		len++;
		if (*currentPtr == '\0' || len > bufferLength)
			return;
	}
}

int DynamicData::SetStringFromPtr(char* CurrentIntPtr, std::string &StringName)
{
	StringName = std::string(CurrentIntPtr);
	return StringName.length() + 1;
}

DynamicData::~DynamicData()
{
}
