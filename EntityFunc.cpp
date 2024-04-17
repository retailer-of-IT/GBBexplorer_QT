#include "EntityFunc.h"
#include <algorithm>
#include <string>
#include <unordered_map>


EntityFunc::EntityFunc()
{
}

//��������
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
//	m_DicAllEntitiesEnum[CurrentEntity.m_sName] = CurrentEntity.EnumType;
//	m_DicAllEntitiesNameByEnum[CurrentEntity.EnumType] = CurrentEntity.m_sName;
//}


EntityFunc::~EntityFunc()
{
}
