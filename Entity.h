#pragma once

#include <QObject>

class Entity : public QObject
{
	Q_OBJECT

public:
	Entity(QWidget *parent);
	~Entity();
};
