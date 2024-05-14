#include "EntityFunc.h"

EntityFunc::EntityFunc()
{
}


//��ȡ��ǰָ�룬�����а��������4λ��
int32_t EntityFunc::GetInteger(const void* CurrentPtr)
{
	CurrentPos += sizeof(int32_t);
	int NumOfEntities = *reinterpret_cast<const int32_t*>(static_cast<const char*>(CurrentPtr) + (CurrentPos - sizeof(int32_t)));
	return NumOfEntities;
}

//����string
void EntityFunc::SetStringFromPtr(const int* CurrentIntPtr, std::string& StringName)
{
	StringName.clear();
	char temp;
	while (true)
	{
		temp = static_cast<char>(*(CurrentIntPtr + CurrentPos));
		if (temp != '\0')
		{
			StringName += temp;
			++CurrentPos;
		}
		else
		{
			++CurrentPos;
			break;
		}
	}
}


//GetAllEntities����ȡϵͳ�нṹ��ĿBufferLength
bool EntityFunc::GetAllEntities()
{
	//��ȡ��̬staticdata
	if (theMonitorManager.GetEntitiesData()) {
		//��ȡ��������
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		const void* ptr = (const void*)p->GetBuffer();
		BufferLength = GetInteger(ptr);
	}
	return true;
}


//void EntityFunc::SetEntity(Entity& CurrentEntity)
//{
//	//Entity�ṹ��entity.cs�ж��壬�����entity.h������,�����
//	SetStringFromPtr(EntityIntPtr, &CurrentEntity.m_sName);                          // ��ָ���ȡʵ������
//	CurrentEntity.EnumType = GetInteger(EntityIntPtr);                              // ��ָ���ȡʵ������
//	CurrentEntity.MaxEntityNum = GetInteger(EntityIntPtr);                          // ��ָ���ȡʵ���������
//	CurrentEntity.NumOfDescriptors = GetInteger(EntityIntPtr);                      // ��ָ���ȡ����������
//
//	for (int i = 0; i < CurrentEntity.NumOfDescriptors; ++i)
//	{
//		CurrentEntity.AllDescriptores.emplace_back();
//		SetStringFromPtr(EntityIntPtr, &CurrentEntity.AllDescriptores[i].m_sName);  // ��ָ���ȡ����������
//		CurrentEntity.AllDescriptores[i].EnumType = GetInteger(EntityIntPtr);       // ��ָ���ȡ����������
//
//																					// ��ȡ���������ֶ��б�����ڵ�
//		CurrentEntity.AllDescriptores[i].AllFields = GetNewDescriptorFields(CurrentEntity.AllDescriptores[i].m_sName);
//		CurrentEntity.AllDescriptores[i].theTreeNode = GetNewDescriptorTreeNodes(CurrentEntity.AllDescriptores[i].m_sName);
//	}
//
//	std::sort(CurrentEntity.AllDescriptores.begin(), CurrentEntity.AllDescriptores.end());
//
//	m_dicAllEntitiesEnum[CurrentEntity.m_sName] = CurrentEntity.EnumType;
//	m_DicAllEntitiesNameByEnum[CurrentEntity.EnumType] = CurrentEntity.m_sName;
//}
//
////����ʵ��ʵ��
//void EntityFunc::SetAllEntities()
//{
//	int32_t NumOfEntities = GetInteger(EntityIntPtr);
//
//	for (int i = 0; i < NumOfEntities; ++i)
//	{
//		m_lstAllEntities.push_back(Entity());
//		SetEntity(m_lstAllEntities.back());
//
//		// In case the entity doesn't define in the GBBConfig
//		if (m_lstAllEntities.back().MaxEntityNum == 0)
//		{
//			m_lstAllEntities.pop_back();
//		}
//	}
//
//	std::sort(m_lstAllEntities.begin(), m_lstAllEntities.end(),
//		[](const auto& e1, const auto& e2) { return e1->Compare(e2.get()); });
//}

//void EntityFunc::InitEntities()
//{
//	int* EntityIntPtr = nullptr;
//	CurrentPos = 0;
//	if (GetAllEntities())             // Get the pointer for all the Entities from the GBBMonitorManager
//	{
//		SetAllEntities();             // Read from pointer and create all the Entities
//	}
//}

EntityFunc::~EntityFunc()
{
}
