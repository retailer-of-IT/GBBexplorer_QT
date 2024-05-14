#include "DynamicData.h"
#include "qdebug.h"

//DynamicData::DynamicData()
//{
//}

DynamicData::DynamicData()
{
	QDomDocument ConfigFile;
	ConfigFile.setContent(new QFile(configPath));
	QDomElement root = ConfigFile.documentElement();
	QDomNode node = root.firstChild();
	while (!node.isNull()) {
		if (node.nodeName() == "Data") {
			QDomNode childNode = node.firstChild();
			while (!childNode.isNull()) {
				if (childNode.nodeName() == "DescriptorBufferSize") {
					m_descriptorBufferSize = childNode.toElement().text().toInt();
					m_descriptorBuffer = static_cast<char*>(malloc(m_descriptorBufferSize));
					break;
				}
				childNode = childNode.nextSibling();
			}
		}
		node = node.nextSibling();
	}
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

void DynamicData::GetEntityDynamicData(long pEntityMet_ID)
{
	if (theMonitorManager.GetEntityDynamicData(pEntityMet_ID)) {
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

void DynamicData::GetEntityDynamicData(long pEntityMet_ID, char* m_descriptorBuffer)
{
	if (theMonitorManager.GetEntityDynamicData(pEntityMet_ID, m_descriptorBuffer)) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfBuffer = *(int*)(ptr1); ptr1 += sizeof(int);
		int NumOfBuffer2 = *(int*)(ptr1); ptr1 += sizeof(int);
	}
}

DynamicData::~DynamicData()
{
}
