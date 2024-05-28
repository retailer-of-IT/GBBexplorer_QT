#include "detail.h"
#include "ui_detail.h"
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QTableView>
#include <QAbstractItemView>
#include <qdebug.h>
#include <iostream>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
detail::detail(StaticData::M_EntityInfo ei, QWidget *parent) : QWidget(parent), ui(new Ui::detail){
	ui->setupUi(this);

	//tablewidget_2勾选列显示
	connect(ui->treeWidget_2, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_2_clicked);
	//tablewidget勾选行显示
	connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_clicked);
	//确定当前detail页所属实体类型
	
	//维护实体列表
	thread = new QThread();
	entityRp = new EntityRetriever(ei, ui->treeWidget, thread);
	connect(this, &detail::EntityRetrieve, entityRp, &EntityRetriever::doWork);
	entityRp->moveToThread(thread);
	thread->start();
	emit EntityRetrieve(); //参数为当前detail页所属实体类型。
}
detail::~detail(){
	delete ui;
	entityRp->flg = 0;
//	delete entityRp;
//	entityRp->thread->quit();  //未测试
}

void detail::creatNewTopItem(QString name)
{
	topItem = new QTreeWidgetItem(QStringList() << name);
	//当前tab界面的treewidget_2建立根节点
	ui->treeWidget_2->addTopLevelItem(topItem);
//	topItem->setCheckState(0, Qt::Unchecked);
}
void detail::creatNewItem(QTreeWidgetItem *parentItem, QString name)
{
	item = new QTreeWidgetItem(parentItem);
	item->setText(0, name);
	item->setCheckState(0, Qt::Unchecked);
}

void detail::on_treeWidget_2_clicked(QTreeWidgetItem * item)
{
	QString s = item->text(0), _s = s;
	if (item->parent() != Q_NULLPTR)
		_s = ((item->parent()->parent()!= Q_NULLPTR)?(item->parent()->parent()->text(0)):(item->parent()->text(0)))+"\n"+_s;
	Qt::CheckState ist = item->checkState(0);
	int columnCount = ui->tableWidget->columnCount();
//	qDebug() << QString("reach %1 when %2 columns").arg(s,QString(columnCount));
	if (item->child(0) == Q_NULLPTR) {	//最后一层节点，才展示
		if (ist == Qt::Checked) { //增加列表头
			ui->tableWidget->setColumnCount(columnCount + 1);
			ui->tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(_s));
			ui->tableWidget->horizontalHeader()->setSectionResizeMode(columnCount, QHeaderView::ResizeToContents);
			ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		}
		else { //删除列表头
			for (int i = 0; i< columnCount; i++) {
				QString name = ui->tableWidget->model()->headerData(i, Qt::Horizontal).toString();
				name.remove(0, name.lastIndexOf("\n")+1);
				if (name == s) {
					QAbstractItemModel *model = ui->tableWidget->model();
					model->removeColumn(i);
					break;
				}
			}
		}
	}
	if (item->checkState(0) == Qt::PartiallyChecked){ //子到父导致，继续向上
		if (item->parent() != Q_NULLPTR && item->parent()->checkState(0) != Qt::PartiallyChecked) {
			item->parent()->setCheckState(0, Qt::PartiallyChecked);
//			qDebug() << QString("\tcheckstate set on %1").arg(item->parent()->text(0));
		}
		return ; 
	}
	if (item->parent() != Q_NULLPTR) { //更新父节点
		QTreeWidgetItem *pp = item->parent(), *cp = pp->child(0);
		bool flg = 0;
		for (int i = 1; cp != Q_NULLPTR; i++) {
			if (ist != cp->checkState(0)) {
				flg = 1;
				break;
			}
			cp = pp->child(i);
		}
		if (flg) {
			if (pp->checkState(0) != Qt::PartiallyChecked)
				pp->setCheckState(0, Qt::PartiallyChecked);
//				qDebug() << QString("\tcheckstate set on %1").arg(pp->text(0));
		}
		else {
			pp->setCheckState(0,ist);
//			qDebug() << QString("\tcheckstate set on %1").arg(pp->text(0));
		}
	}
	// 更新子节点
	QTreeWidgetItem *sp = item->child(0);
	for (int i = 1; sp != Q_NULLPTR; i++) {
		if (ist != sp->checkState(0)) {
			sp->setCheckState(0, ist);
//			qDebug() << QString("\tcheckstate set on %1").arg(sp->text(0));
		}
		sp = item->child(i);
	}
}
void detail::on_treeWidget_clicked(QTreeWidgetItem * item)
{
	QString s = item->text(0);
	QAbstractItemModel *model = ui->tableWidget->model();
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
//	ui->tableWidget->setModel(model);
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

EntityRetriever::EntityRetriever(StaticData::M_EntityInfo ei, QTreeWidget *qtw, QThread *tp){
	entity_info = ei;
	tWidget = qtw;
	thread = tp;
}
void EntityRetriever::doWork(){  //开始工作
	flg = 1;
	qDebug() << QString("This function is in Thread : ") << QThread::currentThreadId() << QString(" for type : ") << entity_info.EnumType;
	QSet<int> rec;
	while (flg) {
		dD.EntitiesId.clear();
		dD.GetEntitiesIDs(entity_info.EnumType);
		qDebug() << entity_info.EnumType;
		if (dD.EntitiesId.size() == 1 && *(dD.EntitiesId.begin()) == -1) {
//			qDebug() << "This Type has no enitiy.";
			thread->sleep(1);  //间隔不少于1S
			continue;
		}
		qDebug() << "This Type has " << dD.EntitiesId.size() <<" enities.";
		for (int id : dD.EntitiesId) {  //检查是否增加了实体
			if (!rec.contains(id)) {  //若该id不存在于tWidget则插入
				rec.insert(id);
				QTreeWidgetItem *p = new QTreeWidgetItem(QStringList() << QString::number(id));
				p->setCheckState(0, Qt::Unchecked);
				tWidget->addTopLevelItem(p);
			}
		}
		for (int _id : rec)	{ //检查是否减少了实体
			bool _flg = 0;
			for (int id : dD.EntitiesId) {
				if (id != _id) continue;
				_flg = 1;
				break;
			}
			if (!_flg) { //没找到该实体
				rec.remove(_id);
				for (int i = 0;; i++) {
					QTreeWidgetItem *p = tWidget->topLevelItem(i);
					if (p == Q_NULLPTR) break;
					if (p->text(0) == QString::number(_id)) {
						delete p; //删除节点，未测试正确性
						break;
					}
				}
			}
		}
		thread->wait(1000);  //间隔不少于1S
	}
	thread->quit();
}

