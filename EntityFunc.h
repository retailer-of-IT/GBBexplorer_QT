#pragma once

#include <QObject>
#include"entity.h"
#include<unordered_map>
#include"GBBMonitorManager\GBBMonitorManager.h"
#include"GBBMonitorManager\SerializedBuffer.h"

class EntityFunc : public QObject
{
	Q_OBJECT

public:
	int CurrentPos = 0;
	const int* EntityIntPtr;
	int32_t BufferLength;
	std::list<Entity> m_lstAllEntities;
	std::map<std::string, int> m_dicAllEntitiesEnum;
	std::map<int, std::string> m_DicAllEntitiesNameByEnum;

public:
	EntityFunc();
	int32_t  GetInteger(const void* CurrentPtr);
	void SetStringFromPtr(const int* CurrentIntPtr, std::string& StringName);
	void SetEntity(Entity& CurrentEntity);
	//��ȡ����ʵ��
	bool GetAllEntities();
	//����ʽ����ʵ��
	//void SetAllEntities();
	//��ʼ��ʵ��
	//void InitEntities();

	~EntityFunc();
};

