#include "ArrayDetail.h"
#include "ui_ArrayDetail.h"

CArrayDetail::CArrayDetail(QWidget *parent)
	: QWidget(parent){
	ui = new Ui::CArrayDetail();
	ui->setupUi(this);
	setWindowTitle("This is it!");
}

CArrayDetail::~CArrayDetail(){
	delete ui;
}

QTableWidget* CArrayDetail::table_ptr() {
	return ui->tableWidget;
}
