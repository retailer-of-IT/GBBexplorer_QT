#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
namespace Ui { class CArrayDetail; };

class CArrayDetail : public QWidget{	Q_OBJECT

public:
	CArrayDetail(QWidget *parent = Q_NULLPTR);
	~CArrayDetail();
	QTableWidget* table_ptr();
	QPushButton *ptb;
	void hide_show();
private:
	Ui::CArrayDetail *ui;
};
