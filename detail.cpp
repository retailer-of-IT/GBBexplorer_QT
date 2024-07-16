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


#pragma region QTimerThread
QTTWorker::QTTWorker(comFunc func, QVector<void *> p) {
	work = func;
	in_date = p;
	interval = -1;
}
void QTTWorker::do_work() {
	work(in_date);
	if (interval != -1) {
		qt_p->setInterval(interval);
		interval = -1;
	}
}
QTimerThread::QTimerThread(comFunc func, QVector<void *> p) {
	qtm_p = new QTimer();
	qth_p = new QThread();
	qw_p = new QTTWorker(func, p);
	qw_p->qt_p = qtm_p;
}
QTimerThread::~QTimerThread() {
	qth_p->quit();
	qth_p->wait();
	qtm_p->deleteLater();
	qw_p->deleteLater();
	qth_p->deleteLater();
}
void QTimerThread::start(int interval1, int interval2 = -1) {
	qtm_p->start(interval1);
	qw_p->interval = interval2;
	qtm_p->moveToThread(qth_p);
	qw_p->moveToThread(qth_p);
	QObject::connect(qtm_p, SIGNAL(timeout()), qw_p, SLOT(do_work()));
	qth_p->start();
} //��һ�������ǵ�һ����������ʱ���ڶ��������ǵ�һ������������ڣ���ֻдһ���������ǵ�һ������Ҳ����Ӧ�ӳٺ�ſ�ʼִ��
#pragma endregion


detail::detail() {}
detail::detail(StaticData::M_EntityInfo ei, QWidget *parent) : QWidget(parent), ui(new Ui::detail) {
	ui->setupUi(this);

	//tablewidget_2��ѡ����ʾ
	connect(ui->treeWidget_2, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_2_clicked);
	//tablewidget��ѡ����ʾ
	connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &detail::on_treeWidget_clicked);
	//���Զ����ź���ȫѡ�ۺ�������������������˫��tableview1��ͬʱ��������һ��treewidget_2��ȫѡ
	connect(this, &detail::FirstAllSelect, this, &detail::on_pushButton_8_clicked);

	//ά��ʵ���б�
	qmt_p = new QMutex;
	qmt_p->lock();
	QVector<void *> d_argv; //��������:QMutex��QTreeWidget��M_EntityInfo��QSet<int>; ����������ά����������
	ei_p = new StaticData::M_EntityInfo(ei);
	qsi_p = new QSet<int>;
	d_argv.push_back((void *)(qmt_p));
	d_argv.push_back((void *)(ui->treeWidget));
	d_argv.push_back((void *)(ei_p));
	d_argv.push_back((void *)(qsi_p));
	qmt_p->unlock();
	qtt_p = new QTimerThread(&detail::keep_Entities, d_argv);
	qtt_p->start(100, 1000);

	//MET_ID
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setColumnCount(1);
	ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("MET_ID"));
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
detail::~detail() {
	delete ui;
	delete qtt_p;
	delete qmt_p;
	delete ei_p;
	delete qsi_p;
}

void detail::creatNewTopItem(QString name) {
	topItem = new QTreeWidgetItem(QStringList() << name); //��ǰtab�����treewidget_2�������ڵ�
	ui->treeWidget_2->addTopLevelItem(topItem); //topItem->setCheckState(0, Qt::Unchecked);
}
void detail::creatNewItem(QTreeWidgetItem *parentItem, QString name) {
	item = new QTreeWidgetItem(parentItem);
	item->setText(0, name);
	item->setCheckState(0, Qt::Unchecked);
}

void detail::on_treeWidget_2_clicked(QTreeWidgetItem * item) {
	QString s = item->text(0), _s = s;
	if (item->parent() != Q_NULLPTR)
		_s = ((item->parent()->parent() != Q_NULLPTR) ? (item->parent()->parent()->text(0)) : (item->parent()->text(0))) + "\n" + _s;
	Qt::CheckState ist = item->checkState(0);
	int columnCount = ui->tableWidget->columnCount();
	//	qDebug() << QString("reach %1 when %2 columns").arg(s,QString(columnCount));
	if (item->child(0) == Q_NULLPTR) {	//���һ��ڵ㣬��չʾ
		if (count == 0) {//��δ����һ����ȫѡ����ʱ�ǽ��в������
			if (ist == Qt::Checked) { //�����б�ͷ
				ui->tableWidget->setColumnCount(columnCount + 1);
				ui->tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(_s));
				ui->tableWidget->horizontalHeader()->setSectionResizeMode(columnCount, QHeaderView::ResizeToContents);
				ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
			}
			else { //�����б�ͷ
				for (int i = 1; i < columnCount; i++) {
					QString name = ui->tableWidget->model()->headerData(i, Qt::Horizontal).toString();
					name.remove(0, name.lastIndexOf("\n") + 1);
					if (name == s) {
						ui->tableWidget->setColumnHidden(i, true);
						break;
					}
				}
			}
		}
		else {//count�Ѿ�>=1��ִ����ʾ/���ز���
			if (ist == Qt::Checked) {
				for (int i = 1; i < columnCount; i++) {
					QString name = ui->tableWidget->model()->headerData(i, Qt::Horizontal).toString();
					name.remove(0, name.lastIndexOf("\n") + 1);
					if (name == s) {
						//QAbstractItemModel *model = ui->tableWidget->model();
						//model->removeColumn(i);
						ui->tableWidget->setColumnHidden(i, false);
						break;
					}
				}
			}
			else { //�����б�ͷ
				for (int i = 1; i < columnCount; i++) {
					QString name = ui->tableWidget->model()->headerData(i, Qt::Horizontal).toString();
					name.remove(0, name.lastIndexOf("\n") + 1);
					if (name == s) {
						ui->tableWidget->setColumnHidden(i, true);
						break;
					}
				}
			}
		}
	}
	if (item->checkState(0) == Qt::PartiallyChecked) { //�ӵ������£���������
		if (item->parent() != Q_NULLPTR && item->parent()->checkState(0) != Qt::PartiallyChecked) {
			item->parent()->setCheckState(0, Qt::PartiallyChecked);
			//			qDebug() << QString("\tcheckstate set on %1").arg(item->parent()->text(0));
		}
		return;
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
			pp->setCheckState(0, ist);
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
void detail::on_treeWidget_clicked(QTreeWidgetItem * item) {
	QString s = item->text(0);
	QAbstractItemModel *model = ui->tableWidget->model();
	if (item->checkState(0) == Qt::Checked) {
		for (int i = 0; i<model->rowCount(); i++) {
			QModelIndex index = model->index(i, 0);
			if (model->data(index) == s) {
				ui->tableWidget->setRowHidden(i, false);
			}
		}
	}
	else {
		for (int i = 0; i<model->rowCount(); i++) {
			QModelIndex index = model->index(i, 0);
			if (model->data(index) == s) {
				ui->tableWidget->setRowHidden(i, true);
			}
		}
	}
}

void detail::on_pushButton_7_clicked() {
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
void detail::on_pushButton_8_clicked() {
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
	count += 1;
}
void detail::on_pushButton_3_clicked() { //ȫѡʵ��
	qmt_p->lock();
	for (int i = 0;; i++) {
		QTreeWidgetItem *p = ui->treeWidget->topLevelItem(i);
		if (p == Q_NULLPTR) break;
		if (p->checkState(0) != Qt::Checked) p->setCheckState(0, Qt::Checked);
	}
	qmt_p->unlock();
}
/*void detail::on_pushButton_2_clicked() { //���ʵ��
	for (int i = 0;; i++) {
		QTreeWidgetItem *p = ui->treeWidget->topLevelItem(i);
		if (p == Q_NULLPTR) break;
		if (p->checkState(0) != Qt::Unchecked) p->setCheckState(0, Qt::Unchecked);
	}
}*/
void detail::on_pushButton_2_clicked() { //���ʵ��
	CArrayDetail *cad = new CArrayDetail();
	cad->show();
}
void detail::keep_Entities(QVector<void *> in_date) { //QMutex��QTreeWidget��M_EntityInfo��QSet<int>
	if (in_date.size() != 4) {
		qDebug() << "keep_Entities ERROR: wrong count of in_date!";
		return;
	}
	//������������л�ȡ�������ݵĵ�ַ
	QMutex *mtp = (QMutex *)(in_date[0]);
	QTreeWidget *twp = (QTreeWidget *)(in_date[1]);
	StaticData::M_EntityInfo *eip = (StaticData::M_EntityInfo *)(in_date[2]);
	QSet<int> *recp = (QSet<int> *)(in_date[3]);
	//����Ϊԭ������
	DynamicData dD;
	mtp->lock();
	dD.GetEntitiesIDs(eip->EnumType);
	if (dD.EntitiesId.size() == 1 && *(dD.EntitiesId.begin()) == -1) {
		qDebug() << "This Type has no enitiy. from " << QThread::currentThreadId();
	}
	else {
		qDebug() << "This Type has " << dD.EntitiesId.size() << " enities. from " << QThread::currentThreadId();
		for (int id : dD.EntitiesId) {  //����Ƿ�������ʵ��
			if (!recp->contains(id)) {  //����id��������tWidget�����
				recp->insert(id);
				QTreeWidgetItem *p = new QTreeWidgetItem(QStringList() << QString::number(id));
				p->setCheckState(0, Qt::Checked);//�����ĳ�ʼ״̬��Ϊchecked
				twp->addTopLevelItem(p);
			}
		}
		for (int _id : (*recp)) { //����Ƿ������ʵ��
			bool _flg = 0;
			for (int id : dD.EntitiesId) {
				if (id != _id) continue;
				_flg = 1;
				break;
			}
			if (!_flg) { //û�ҵ���ʵ��
				recp->remove(_id);
				for (int i = 0;; i++) {
					QTreeWidgetItem *p = twp->topLevelItem(i);
					if (p == Q_NULLPTR) break;
					if (p->text(0) == QString::number(_id)) {
						delete p; //ɾ���ڵ㣬δ������ȷ��
						break;
					}
				}
			}
		}
	}
	mtp->unlock();
}