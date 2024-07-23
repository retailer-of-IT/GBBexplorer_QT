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

void CArrayDetail::hide_show(){
	if (isHidden()) 
		show();
	else 
		hide();
}

bool CArrayDetail::setColumns(const QVector<StaticData::M_FieldInfo> &tFieldList) {
	ui->tableWidget->setColumnCount(tFieldList.size());
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->verticalHeader()->setVisible(0);
	for (int i = 0; i < tFieldList.size(); i++) {
		ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
		ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(tFieldList[i].FieldName)));
	}
	return 1;
}