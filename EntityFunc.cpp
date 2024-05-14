#include "EntityFunc.h"

EntityFunc::EntityFunc()
{
}


//获取当前指针，并进行按需递增（4位）
int32_t EntityFunc::GetInteger(const void* CurrentPtr)
{
	CurrentPos += sizeof(int32_t);
	int NumOfEntities = *reinterpret_cast<const int32_t*>(static_cast<const char*>(CurrentPtr) + (CurrentPos - sizeof(int32_t)));
	return NumOfEntities;
}

//设置string
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


//GetAllEntities，获取系统中结构数目BufferLength
bool EntityFunc::GetAllEntities()
{
	//获取静态staticdata
	if (theMonitorManager.GetEntitiesData()) {
		//获取填充的数据
		GBBMonitor::SerializedBuffer* p = theMonitorManager.GetSerializedBuffer();
		const void* ptr = (const void*)p->GetBuffer();
		BufferLength = GetInteger(ptr);
	}
	return true;
}


//void EntityFunc::SetEntity(Entity& CurrentEntity)
//{
//	//Entity结构在entity.cs中定义，如何在entity.h中引用,待解决
//	SetStringFromPtr(EntityIntPtr, &CurrentEntity.m_sName);                          // 从指针读取实体名称
//	CurrentEntity.EnumType = GetInteger(EntityIntPtr);                              // 从指针读取实体类型
//	CurrentEntity.MaxEntityNum = GetInteger(EntityIntPtr);                          // 从指针读取实体最大数量
//	CurrentEntity.NumOfDescriptors = GetInteger(EntityIntPtr);                      // 从指针读取描述符数量
//
//	for (int i = 0; i < CurrentEntity.NumOfDescriptors; ++i)
//	{
//		CurrentEntity.AllDescriptores.emplace_back();
//		SetStringFromPtr(EntityIntPtr, &CurrentEntity.AllDescriptores[i].m_sName);  // 从指针读取描述符名称
//		CurrentEntity.AllDescriptores[i].EnumType = GetInteger(EntityIntPtr);       // 从指针读取描述符类型
//
//																					// 获取描述符的字段列表和树节点
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
////设置实体实现
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
