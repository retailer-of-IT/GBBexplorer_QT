#include "StaticData.h"


StaticData::StaticData()
{
}


void StaticData::InitDescriptors()
{
	if (theMonitorManager.GetDesriptorsMappingToStructures())
	{
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfDescriptors = *(int*)(ptr1); ptr1 += sizeof(int);// buff���ܳ���
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// �ṹ���ݵ��ܸ���
		for (int i = 0; i < NumMax; ++i)
		{
			//vecDescriptorsInfo.push_back(M_DescriptorsInfo());
			M_DescriptorsInfo &cInfo = M_DescriptorsInfo();
			//M_DescriptorsInfo &cInfo = vecDescriptorsInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.DescriptorName);
			ptr1 += SetStringFromPtr(ptr1, cInfo.StructureName);
			cInfo.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.MaxMessageNum = *(int*)(ptr1); ptr1 += sizeof(int);
			//���Է���ֻ��maxmessagenum!=0�ĲŻ���ʾ�ڽ����ϣ��������޸�
			if (cInfo.MaxMessageNum != 0) {
				vecDescriptorsInfo.push_back(cInfo);
			}
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
		int NumOfStructures = *(int*)(ptr1); ptr1 += sizeof(int);// buff���ܳ���
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// �ṹ���ݵ��ܸ���
		for (int i = 0; i < NumMax; ++i)
		{
			vecStructuresInfo.push_back(M_StructuresInfo());
			M_StructuresInfo &cInfo = vecStructuresInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.StructureName);
			cInfo.NumOfFields = *(int*)(ptr1); ptr1 += sizeof(int);
			for (int j = 0; j < cInfo.NumOfFields; ++j)
			{
				cInfo.vecField.push_back(M_FieldInfo());
				M_FieldInfo &cInfo2 = cInfo.vecField[j];
				ptr1 += SetStringFromPtr(ptr1, cInfo2.FieldName);
				cInfo2.FieldType = *(int*)(ptr1); ptr1 += sizeof(int);
				ptr1 += SetStringFromPtr(ptr1, cInfo2.NestedName);
				cInfo2.ArrayMaxSize = *(int*)(ptr1); ptr1 += sizeof(int);
			}
		}
	}
}
void StaticData::InitEntities()
{
	if (theMonitorManager.GetEntitiesData()) {
		//��ȡ��������
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfEntities = *(int*)(ptr1); ptr1 += sizeof(int);// buff���ܳ���
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// �ṹ���ݵ��ܸ���
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
	}
}
void StaticData::InitMessages()
{
	if (theMonitorManager.GetMessagesData()) {
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		char* ptr = (char*)p->GetBuffer();
		char* ptr1 = ptr;
		int NumOfMessages = *(int*)(ptr1); ptr1 += sizeof(int);// buff���ܳ���
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// �ṹ���ݵ��ܸ���
		for (int i = 0; i < NumMax; ++i)
		{
			vecMessageInfo.push_back(M_MessageInfo());
			M_MessageInfo &cInfo = vecMessageInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.MessageName);
			cInfo.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.m_bIsDescAsMessage = *(bool*)(ptr1); ptr1 += sizeof(bool);
			cInfo.m_bWithAck = *(bool*)(ptr1); ptr1 += sizeof(bool);
			cInfo.MaxMessageNum = *(int*)(ptr1); ptr1 += sizeof(int);
			//���Եó����滹��һ���ظ���messagename,�е���֣�����ָ�����ƶ�һ���ַ���name�ľ���
			ptr1 += SetStringFromPtr(ptr1, cInfo.MessageName2);

		}
		//char a[10000];
		//for (int i = 0; i < 10000; i++) {
		//	a[i] = *ptr1;
		//	ptr1++;
		//}
	}
}

int StaticData::SetStringFromPtr(char* CurrentIntPtr, std::string &StringName)
{
	StringName = std::string(CurrentIntPtr);
	return StringName.length() + 1;
}

StaticData::~StaticData()
{
}
