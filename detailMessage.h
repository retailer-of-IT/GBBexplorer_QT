#pragma once

#include <QWidget>
#include "ui_detailMessage.h"

class detailMessage : public QWidget
{
	Q_OBJECT

public:
	detailMessage(QWidget *parent = Q_NULLPTR);
	~detailMessage();

private:
	Ui::detailMessage ui;
};
