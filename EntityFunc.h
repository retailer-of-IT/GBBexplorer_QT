#pragma once

#include <QObject>
#include"entity.h"
#include<unordered_map>
class EntityFunc : public QObject
{
	Q_OBJECT


public:
	EntityFunc();
	int32_t  GetInteger(const void* CurrentPtr);
	void SetStringFromPtr(const char* CurrentIntPtr, std::string& StringName);
	void SetEntity(Entity& CurrentEntity);
	//��ȡ����ʵ��
	bool GetAllEntities();
	//����ʽ����ʵ��
	//void SetAllEntities();

	~EntityFunc();
};

//void SetStringFromPtr(const char * CurrentIntPtr, std::string & StringName);
