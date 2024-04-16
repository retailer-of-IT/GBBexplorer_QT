#pragma once

#include <QObject>
#include"entity.h"
class EntityFunc : public QObject
{
	Q_OBJECT

private:
	int CurrentPos = 0;

public:
	EntityFunc(QWidget *parent);

	void SetStringFromPtr(const char* CurrentIntPtr, std::string& StringName);

	~EntityFunc();
};
