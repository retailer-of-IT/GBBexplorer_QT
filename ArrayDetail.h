#pragma once

#include <QWidget>
#include <QTableWidget>
namespace Ui { class CArrayDetail; };

class CArrayDetail : public QWidget{	Q_OBJECT

public:
	CArrayDetail(QWidget *parent = Q_NULLPTR);
	~CArrayDetail();
	QTableWidget* table_ptr();
private:
	Ui::CArrayDetail *ui;
};
