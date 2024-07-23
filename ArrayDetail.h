#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include "StaticData.h"
namespace Ui { class CArrayDetail; };

class CArrayDetail : public QWidget{	Q_OBJECT

public:
	CArrayDetail(QWidget *parent = Q_NULLPTR);
	~CArrayDetail();
	QTableWidget* table_ptr();
	QPushButton *ptb;
	void hide_show();
	bool setColumns(const QVector<StaticData::M_FieldInfo> &tFieldList);
private:
	Ui::CArrayDetail *ui;
};
