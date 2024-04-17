#include "EntityFunc.h"
#include <algorithm>
#include <string>
#include <unordered_map>


EntityFunc::EntityFunc()
{
}

//变量定义
int CurrentPos = 0;
const char* EntityIntPtr;


int32_t EntityFunc::GetInteger(const void * CurrentPtr)
{
	CurrentPos += sizeof(int32_t);
	int NumOfEntities = *reinterpret_cast<const int32_t*>(static_cast<const char*>(CurrentPtr) + (CurrentPos - sizeof(int32_t)));
	return NumOfEntities;
}

void EntityFunc::SetStringFromPtr(const char* CurrentIntPtr, std::string& StringName)
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

bool EntityFunc::GetAllEntities()
{
	return false;
}

//
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
//	m_DicAllEntitiesEnum[CurrentEntity.m_sName] = CurrentEntity.EnumType;
//	m_DicAllEntitiesNameByEnum[CurrentEntity.EnumType] = CurrentEntity.m_sName;
//}


EntityFunc::~EntityFunc()
{
}
