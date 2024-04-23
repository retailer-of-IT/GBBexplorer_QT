#include "StaticData.h"
#include <QVector>
#include <QMap>

StaticData::StaticData()
{
}

struct M_DescriptorsInfo
{
	int EnumType;
	int MaxMessageNum;
	std::string DescriptorName = "";
	std::string StructureName = "";
};
struct M_FieldInfo
{
	int FieldType;
	int ArrayMaxSize;
	std::string FieldName = "";
	std::string NestedName = "";
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
	//M_DescriptorsInfo m_cCurrentDescriptor;
};


//获取Descriptors信息
QVector<M_DescriptorsInfo> vecDescriptorsInfo;
//获取Structures信息
QVector<M_StructuresInfo> vecStructuresInfo;
//获取Entity信息
QVector<M_EntityInfo> vecEntityInfo;
//获取Message信息
QVector<M_MessageInfo> vecMessageInfo;

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
			//vecDescriptorsInfo.push_back(M_DescriptorsInfo());
			M_DescriptorsInfo &cInfo = M_DescriptorsInfo();
			//M_DescriptorsInfo &cInfo = vecDescriptorsInfo[i];
			ptr1 += SetStringFromPtr(ptr1, cInfo.DescriptorName);
			ptr1 += SetStringFromPtr(ptr1, cInfo.StructureName);
			cInfo.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			cInfo.MaxMessageNum = *(int*)(ptr1); ptr1 += sizeof(int);
			//调试发现只有maxmessagenum!=0的才会显示在界面上，这里做修改
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
		int NumOfStructures = *(int*)(ptr1); ptr1 += sizeof(int);// buff的总长度
		int NumMax = *(int*)(ptr1); ptr1 += sizeof(int);// 结构数据的总个数
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
			//ptr1 += SetStringFromPtr(ptr1, cInfo.m_cCurrentDescriptor.DescriptorName);
			//ptr1 += SetStringFromPtr(ptr1, cInfo.m_cCurrentDescriptor.StructureName);
			//cInfo.m_cCurrentDescriptor.EnumType = *(int*)(ptr1); ptr1 += sizeof(int);
			//cInfo.m_cCurrentDescriptor.MaxMessageNum = *(int*)(ptr1); ptr1 += sizeof(int);

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
