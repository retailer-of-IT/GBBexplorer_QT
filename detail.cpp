#include "detail.h"
#include "ui_detail.h"
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QTableView>
#include <QAbstractItemView>
#include "detail.h"
#include <qdebug.h>
#include <iostream>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
detail::detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);

	//tablewidget_2勾选列显示
	connect(ui->treeWidget_2, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_2_clicked);
	//tablewidget勾选行显示
	connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_clicked);
}

detail::~detail()
{
    delete ui;
}


void detail::creatNewTopItem(QString name)
{
	topItem = new QTreeWidgetItem(QStringList() << name);
	//当前tab界面的treewidget_2建立根节点
	ui->treeWidget_2->addTopLevelItem(topItem);
	topItem->setCheckState(0, Qt::Unchecked);
}

void detail::creatNewItem(QString name)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(topItem);
	item->setText(0, name);
	item->setCheckState(0, Qt::Unchecked);
}

void detail::on_pushButton_7_clicked()
{
	for (int i = 0; i < ui->treeWidget_2->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(i);
		if (item == nullptr) {
			return;
		}
		item->setCheckState(0, Qt::Unchecked);
		int count = item->childCount();
		for (int i = 0; i < count; ++i) {
			QTreeWidgetItem *child = item->child(i);
			child->setCheckState(0, Qt::Unchecked);
		}
	}
}

void detail::on_treeWidget_2_clicked(QTreeWidgetItem * item)
{
	QStandardItemModel* model = new QStandardItemModel(this);
	//QAbstractItemModel *model2 = ui->tableView->model();
	//不是根节点，才展示
	if (item->parent() != nullptr) {
		//计算当前列数
		int columnCount = ui->tableView->horizontalHeader()->count();
		//int columnnum = model->columnCount();
		qDebug() << columnCount;
		QString s = item->text(0);
		if (item->checkState(0) == Qt::Checked) {
			//设置列表头名
			model->setHorizontalHeaderItem(ui->tableView->horizontalHeader()->count(), new QStandardItem(s));
			ui->tableView->setModel(model);
			ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
			ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		}
		else {
			for (int i = 0; i<ui->tableView->horizontalHeader()->count(); i++) {
				if (ui->tableView->model()->headerData(i, Qt::Horizontal).toString() == s) {
					//ui->tableView->horizontalHeader()->setSectionHidden(i,true);
					QAbstractItemModel *model = ui->tableView->model();
					model->removeColumn(i);
				}
			}
			ui->tableView->setModel(model);
		}
	}
}

void detail::on_treeWidget_clicked(QTreeWidgetItem * item)
{
	QString s = item->text(0);
	QAbstractItemModel *model = ui->tableView->model();
	if (item->checkState(0) == Qt::Checked) {
		// 获取行数
		int rowCount = model->rowCount();
		model->insertRow(rowCount);
		model->setData(model->index(rowCount, 0), s);
	}
	else {
		for (int i = 0; i<model->rowCount(); i++) {
			QModelIndex index = model->index(i, 0);
			if (model->data(index) == s) {
				//ui->tableView->horizontalHeader()->setSectionHidden(i,true);
				model->removeRow(i);
			}
		}
	}
	ui->tableView->setModel(model);
}

void detail::on_pushButton_8_clicked()
{
	for (int i = 0; i < ui->treeWidget_2->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(i);
		if (item == nullptr) {
			return;
		}
		item->setCheckState(0, Qt::Checked);
		int count = item->childCount();
		for (int i = 0; i < count; ++i) {
			QTreeWidgetItem *child = item->child(i);
			child->setCheckState(0, Qt::Checked);
		}
	}
}
