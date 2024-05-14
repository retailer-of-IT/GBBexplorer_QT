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
	qDebug() << "hello";
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
		EntitiesId.push_back(*(int*)(ptr1));ptr1 += sizeof(int);
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

void DynamicData::GetEntityDynamicData(int nEntityID)
{
	if (theMonitorManager.GetEntityDynamicData(nEntityID)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
		int NumOfBuffer2 = *(int*)(ptr1); ptr1 += sizeof(int);
		char a[10000];
		for (int i = 0; i < 10000; i++) {
			a[i] = *ptr1;
			ptr1++;
		}
		qDebug() << "hello";
	}
}

void DynamicData::GetEntityDynamicData()
{
	int num = staticdata.vecDescriptorsInfo.size();
	int m = 0;
	//为每个描述符在分配的空间中占位，以enumtype
	for (int i = 0; i < num; ++i) {
		*(int*)(m_descriptorPtr + m) = staticdata.vecDescriptorsInfo[i].EnumType;
		m += sizeof(int);
	}
	*(int*)(m_descriptorPtr + m) = -1;

	staticdata.InitEntities();
	staticdata.InitStructures();
	staticdata.InitMessages();
	int num2 = staticdata.vecEntityInfo.size();
	for (int i = 0; i < num2; i++) {
		if (theMonitorManager.GetEntityDynamicData(staticdata.vecEntityInfo[i].EnumType, m_descriptorPtr)) {
			GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
			char* ptr = (char*)p->GetBuffer();
			char* ptr1 = ptr;
		}
	}
	qDebug() << "hello";
}

DynamicData::~DynamicData()
{
}
