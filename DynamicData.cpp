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
	staticdata.InitDescriptors();
	int num = staticdata.vecDescriptorsInfo.size();
	int m_nCurrentPos = 0;
	//为每个描述符在分配的空间中占位，以enumtype
	for (int i = 0; i < num; ++i) {
		*(int*)(m_descriptorPtr + m_nCurrentPos) = staticdata.vecDescriptorsInfo[i].EnumType;
		m_nCurrentPos += sizeof(int);
	}
	*(int*)(m_descriptorPtr + m_nCurrentPos) = -1;

	GetEntitiesIDs(eEntityType);//每个周期，获取对应id实体的所有metid
	int num2 = EntitiesId.size();
	for (int i = 0; i < num2; i++) {
		if (theMonitorManager.GetEntityDynamicData(EntitiesId[i], m_descriptorPtr)) {
			GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
			char* ptr = (char*)p->GetBuffer();
			//对应的DataBufferPtr
			char* ptr1 = ptr;
			int bufferLength = *(int*)(ptr1); ptr1 += sizeof(int);//buffer长度
			//TODO dynamicdata.cs中 GetEntityTableData等函数使用到的 ReadRowFromIntPtr函数功能
			char a[10000];
			for (int i = 0; i < 10000; i++) {
				a[i] = *ptr1;
				ptr1++;
			}
			qDebug() << "hello";
		}
	}
	m_nCurrentPos = 0;
	qDebug() << "hello";
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
			m_nCurrentPos += 8;
		}
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
			m_nCurrentPos += 8;
		}
	case StaticData::FieldType::Boolean:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			bool a = *(bool*)(fieldPtr + m_nCurrentPos);
			m_nCurrentPos += 1;
		}
		else
		{
			m_nCurrentPos += 1;
		}
	case StaticData::FieldType::Char:
		if (m_nCurrentPos + 1 <= bufferLength)
		{
			bool a = *(fieldPtr + m_nCurrentPos);
			m_nCurrentPos += 1;
		}
		else
		{
			m_nCurrentPos += 1;
		}
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
			m_nCurrentPos += 8;
		}
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
			m_nCurrentPos += 4;
		}
	case StaticData::FieldType::Integer:
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
			m_nCurrentPos += 4;
		}
		//todo
	default:
		break;
	}
	return false;
}

DynamicData::~DynamicData()
{
}
