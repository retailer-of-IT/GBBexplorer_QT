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
	//获取整个实体
	bool GetAllEntities();
	//按格式设置实体
	//void SetAllEntities();

	~EntityFunc();
};

//void SetStringFromPtr(const char * CurrentIntPtr, std::string & StringName);
