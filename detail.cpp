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

	//tablewidget_2��ѡ����ʾ
	connect(ui->treeWidget_2, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_2_clicked);
	//tablewidget��ѡ����ʾ
	connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_clicked);
	//ȷ����ǰdetailҳ����ʵ������
	
	//ά��ʵ���б�
	thread = new QThread();
	entityRp = new EntityRetriever(ei, ui->treeWidget, thread);
	connect(this, &detail::EntityRetrieve, entityRp, &EntityRetriever::doWork);
	entityRp->moveToThread(thread);
	thread->start();
	emit EntityRetrieve(); //����Ϊ��ǰdetailҳ����ʵ�����͡�
}
detail::~detail(){
	delete ui;
	entityRp->flg = 0;
//	delete entityRp;
//	entityRp->thread->quit();  //δ����
}

void detail::creatNewTopItem(QString name)
{
	topItem = new QTreeWidgetItem(QStringList() << name);
	//��ǰtab�����treewidget_2�������ڵ�
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
	if (item->child(0) == Q_NULLPTR) {	//���һ��ڵ㣬��չʾ
		if (ist == Qt::Checked) { //�����б�ͷ
			ui->tableWidget->setColumnCount(columnCount + 1);
			ui->tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(_s));
			ui->tableWidget->horizontalHeader()->setSectionResizeMode(columnCount, QHeaderView::ResizeToContents);
			ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		}
		else { //ɾ���б�ͷ
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
	if (item->checkState(0) == Qt::PartiallyChecked){ //�ӵ������£���������
		if (item->parent() != Q_NULLPTR && item->parent()->checkState(0) != Qt::PartiallyChecked) {
			item->parent()->setCheckState(0, Qt::PartiallyChecked);
//			qDebug() << QString("\tcheckstate set on %1").arg(item->parent()->text(0));
		}
		return ; 
	}
	if (item->parent() != Q_NULLPTR) { //���¸��ڵ�
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
	// �����ӽڵ�
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
		// ��ȡ����
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
void EntityRetriever::doWork(){  //��ʼ����
	flg = 1;
	qDebug() << QString("This function is in Thread : ") << QThread::currentThreadId() << QString(" for type : ") << entity_info.EnumType;
	QSet<int> rec;
	while (flg) {
		dD.EntitiesId.clear();
		dD.GetEntitiesIDs(entity_info.EnumType);
		qDebug() << entity_info.EnumType;
		if (dD.EntitiesId.size() == 1 && *(dD.EntitiesId.begin()) == -1) {
//			qDebug() << "This Type has no enitiy.";
			thread->sleep(1);  //���������1S
			continue;
		}
		qDebug() << "This Type has " << dD.EntitiesId.size() <<" enities.";
		for (int id : dD.EntitiesId) {  //����Ƿ�������ʵ��
			if (!rec.contains(id)) {  //����id��������tWidget�����
				rec.insert(id);
				QTreeWidgetItem *p = new QTreeWidgetItem(QStringList() << QString::number(id));
				p->setCheckState(0, Qt::Unchecked);
				tWidget->addTopLevelItem(p);
			}
		}
		for (int _id : rec)	{ //����Ƿ������ʵ��
			bool _flg = 0;
			for (int id : dD.EntitiesId) {
				if (id != _id) continue;
				_flg = 1;
				break;
			}
			if (!_flg) { //û�ҵ���ʵ��
				rec.remove(_id);
				for (int i = 0;; i++) {
					QTreeWidgetItem *p = tWidget->topLevelItem(i);
					if (p == Q_NULLPTR) break;
					if (p->text(0) == QString::number(_id)) {
						delete p; //ɾ���ڵ㣬δ������ȷ��
						break;
					}
				}
			}
		}
		thread->wait(1000);  //���������1S
	}
	thread->quit();
}

