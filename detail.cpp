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
} //第一个参数是第一次启动的延时，第二个参数是第一次启动后的周期；若只写一个参数就是第一次启动也在相应延迟后才开始执行
#pragma endregion


detail::detail() {}
detail::detail(StaticData::M_EntityInfo ei, QWidget *parent) : QWidget(parent), ui(new Ui::detail) {
	ui->setupUi(this);

	//tablewidget_2勾选列显示
	connect(ui->treeDescriptors, &QTreeWidget::itemChanged, this, &detail::on_treeDescriptors_clicked);
	//tablewidget勾选行显示
	connect(ui->treeEntities, &QTreeWidget::itemChanged, this, &detail::on_treeEntities_clicked);
	//将自定义信号与全选槽函数连接起来，用于在双击tableview1的同时触发触发一次treeWidget_2的全选
	connect(this, &detail::FirstAllSelect, this, &detail::on_btnDSelectAll_clicked);

	//维护实体列表
	qmt_p = new QMutex;
	qmt_p->lock();
	QVector<void *> d_argv; //参数依次:QMutex，QTreeWidget，M_EntityInfo，QSet<int>; 本向量无需维持生命周期
	ei_p = new StaticData::M_EntityInfo(ei);
	qsi_p = new QSet<int>;
	d_argv.push_back((void *)(qmt_p));
	d_argv.push_back((void *)(ui->treeEntities));
	d_argv.push_back((void *)(ei_p));
	d_argv.push_back((void *)(qsi_p));
	qmt_p->unlock();
	qtt_p = new QTimerThread(&detail::keep_Entities, d_argv);
	qtt_p->start(100, 1000);

	//MET_ID
	ui->tableDetail->verticalHeader()->setVisible(false);
	ui->tableDetail->setColumnCount(1);
	ui->tableDetail->setHorizontalHeaderItem(0, new QTableWidgetItem("MET_ID"));
	ui->tableDetail->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui->tableDetail->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableDetail->horizontalHeaderItem(0)->setData(Qt::UserRole, QVariant::fromValue(Q_NULLPTR));
}
detail::~detail() {
	delete ui;
	delete qtt_p;
	delete qmt_p;
	delete ei_p;
	delete qsi_p;
}
//创建描述符树状表的顶级节点。	顶级节点一定来自描述符
void detail::creatNewTopItem(StaticData::M_DescriptorsInfo _item) {
	//描述符应该没有数组类的，目前如此认为
	QString name = QString::fromStdString(_item.DescriptorName);
	topItem = new QTreeWidgetItem(QStringList() << name);
	topItem->setData(0, Qt::UserRole, -1); 
	topItem->setData(0, Qt::UserRole + 1, QVariant::fromValue(_item));//UserRole+1(M_DescriptorsInfo或M_FieldInfo，取决于深度)
	ui->treeDescriptors->addTopLevelItem(topItem);
	topItem->setCheckState(0, Qt::Unchecked);
}
//创建描述符树状表的非顶级节点
void detail::creatNewItem(QTreeWidgetItem *parentItem, StaticData::M_FieldInfo _item) {
	item = new QTreeWidgetItem(parentItem);
	//对Array类型特殊处理（加#）
	if (_item.FieldType == StaticData::FieldType::Array) {
		item->setText(0, QString::fromStdString("(#)" + _item.FieldName));
	}
	else {
		item->setText(0, QString::fromStdString(_item.FieldName));
	}
	item->setData(0, Qt::UserRole + 1, QVariant::fromValue(_item));//UserRole+1(M_DescriptorsInfo或M_FieldInfo，取决于深度)
	item->setCheckState(0, Qt::Unchecked);
}

//描述符列表的勾选
//前提：默认 实体包含的描述符 和 描述符包含的Field 不变（则两者属于staticdata），
//		若要改变则可以考虑将处理写到btnDRefresh里，btnDRefresh的实现方法可以是让widget删掉当前detail然后重新new一个到当前页
//需要修改：在遍历树时将描述符正确展开同时完成列的插入，而本槽函数不再涉及列的插入
void detail::on_treeDescriptors_clicked(QTreeWidgetItem * item) {
	Qt::CheckState ist = item->checkState(0);
	int ColIndex = item->data(0, Qt::UserRole).toInt();
	QString name = item->data(0, Qt::DisplayRole).toString();
	QTreeWidgetItem *cp, *pp;
	//当这个结点不是叶子节点，则他有子节点，它的状态改变将影响祖先节点和子孙节点，且有三种状态
	if (ColIndex <= 0) {
		//树内处理-向上-特例（由子节点导致PartiallyChecked时，会使它的祖先节点全变为PartiallyChecked）
		if (item->checkState(0) == Qt::PartiallyChecked) { //无需进行其他操作了
			if (item->parent() != Q_NULLPTR && item->parent()->checkState(0) != Qt::PartiallyChecked) {
				item->parent()->setCheckState(0, Qt::PartiallyChecked);
			}
			return;
		}
		//树内处理-向下（item为PartiallyChecked时）
		cp = item->child(0);
		bool flg = 0;
		for (int i = 1; cp != Q_NULLPTR; i++) {
			if (cp->checkState(0) != ist)
				cp->setCheckState(0, ist);	//此时的ist不会再是PartiallyChecked
			cp = item->child(i);
		}
		//树内处理-向上
		if (item->parent() != Q_NULLPTR) { //更新父节点
			pp = item->parent();
			cp = pp->child(0);
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
			}
			else {
				if (pp->checkState(0) != ist)
					pp->setCheckState(0, ist);
			}
		}
	}
	//当这个结点是叶子节点，它在tableDetail里有对应的列，它的状态改变仅会影响祖先节点，有两种状态
	//一个叶子节点一定只会对应一个列吗？
	else {
		//树内处理-向上
		if (item->parent() != Q_NULLPTR) { //更新父节点，只更新一层即可
			pp = item->parent();
			cp = pp->child(0);
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
			}
			else {
				if (pp->checkState(0) != ist)
					pp->setCheckState(0, ist);
			}
		}
		//tableDetail处理
		if (ist == Qt::Checked) {
			if (ui->tableDetail->isColumnHidden(ColIndex)) {
				ui->tableDetail->setColumnHidden(ColIndex, false);
			}
		}
		else if(ist == Qt::Unchecked){
			if (!ui->tableDetail->isColumnHidden(ColIndex)) {
				ui->tableDetail->setColumnHidden(ColIndex, true);
			}
		}
		else {
			QMessageBox::warning(this, "Warning from detail", QString("Wrong item checkstate:%1").arg(ist));
		}
	}
}
//描述符的清除所有
void detail::on_btnDClearAll_clicked() {
	for (int i = 0; i < ui->treeDescriptors->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui->treeDescriptors->topLevelItem(i);
		if (item == nullptr) 
			return;
		if (item->checkState(0) != Qt::Unchecked)
			item->setCheckState(0, Qt::Unchecked);
	}
}
//描述符的全选
void detail::on_btnDSelectAll_clicked() {
	for (int i = 0; i < ui->treeDescriptors->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui->treeDescriptors->topLevelItem(i);
		if (item == nullptr) 
			return;
		if(item->checkState(0)!= Qt::Checked)
			item->setCheckState(0, Qt::Checked);
	}
}
//实体列表的勾选
void detail::on_treeEntities_clicked(QTreeWidgetItem * item) {
	QString s = item->text(0);
	QAbstractItemModel *model = ui->tableDetail->model();
	if (item->checkState(0) == Qt::Checked) {
		for (int i = 0; i<model->rowCount(); i++) {
			//取第i行第0个元素
			QModelIndex index = model->index(i, 0);
			if (model->data(index) == s) {
				ui->tableDetail->setRowHidden(i, false);
			}
		}
	}
	else {
		for (int i = 0; i<model->rowCount(); i++) {
			QModelIndex index = model->index(i, 0);
			if (model->data(index) == s) {
				ui->tableDetail->setRowHidden(i, true);
			}
		}
	}
}
//实体的全选
void detail::on_btnESelectAll_clicked() { //全选实体
	qmt_p->lock();
	for (int i = 0;; i++) {
		QTreeWidgetItem *p = ui->treeEntities->topLevelItem(i);
		if (p == Q_NULLPTR) break;
		if (p->checkState(0) != Qt::Checked) p->setCheckState(0, Qt::Checked);
	}
	qmt_p->unlock();
}
//实体的清除所有
void detail::on_btnEClearAll_clicked() { //清除实体
	CArrayDetail *cad = new CArrayDetail();
	cad->show();
}
//维护实体列表的工作函数（QTimerThread需要）
void detail::keep_Entities(QVector<void *> in_date) { //QMutex，QTreeWidget，M_EntityInfo，QSet<int>
	if (in_date.size() != 4) {
		qDebug() << "keep_Entities ERROR: wrong count of in_date!";
		return;
	}
	//从输入的向量中获取所需数据的地址
	QMutex *mtp = (QMutex *)(in_date[0]);
	QTreeWidget *twp = (QTreeWidget *)(in_date[1]);
	StaticData::M_EntityInfo *eip = (StaticData::M_EntityInfo *)(in_date[2]);
	QSet<int> *recp = (QSet<int> *)(in_date[3]);
	//以下为原处理函数
	DynamicData dD;
	mtp->lock();
	dD.GetEntitiesIDs(eip->EnumType);
	if (dD.EntitiesId.size() == 1 && *(dD.EntitiesId.begin()) == -1) {
		qDebug() << "This Type has no enitiy. from " << QThread::currentThreadId();
	}
	else {
		qDebug() << "This Type has " << dD.EntitiesId.size() << " enities. from " << QThread::currentThreadId();
		for (int id : dD.EntitiesId) {  //检查是否增加了实体
			if (!recp->contains(id)) {  //若该id不存在于tWidget则插入
				recp->insert(id);
				QTreeWidgetItem *p = new QTreeWidgetItem(QStringList() << QString::number(id));
				p->setCheckState(0, Qt::Checked);//加入后的初始状态设为checked
				twp->addTopLevelItem(p);
			}
		}
		for (int _id : (*recp)) { //检查是否减少了实体
			bool _flg = 0;
			for (int id : dD.EntitiesId) {
				if (id != _id) continue;
				_flg = 1;
				break;
			}
			if (!_flg) { //没找到该实体
				recp->remove(_id);
				for (int i = 0;; i++) {
					QTreeWidgetItem *p = twp->topLevelItem(i);
					if (p == Q_NULLPTR) break;
					if (p->text(0) == QString::number(_id)) {
						delete p;
						break;
					}
				}
			}
		}
	}
	mtp->unlock();
}
//对该detail的所有ArrayDetail的处理（槽函数连接）
void detail::connectArray(){
	for (int rowIndex = 0; rowIndex < allRowsArrays.size(); rowIndex++) {
		for (auto it = allRowsArrays[rowIndex].begin(); it != allRowsArrays[rowIndex].end(); it++) {
			int colIndex = it.key();
			CArrayDetail *arrayD = it.value();
			if (arrayD == Q_NULLPTR || arrayD->ptb == Q_NULLPTR)
				continue ;
			connect(arrayD->ptb, &QPushButton::clicked, arrayD, &CArrayDetail::hide_show);
		}
	}
}
//根据传入的树节点指针sp，向ui->tableDetail中添加一列，
void detail::addColumn(QString ColName, QTreeWidgetItem * sp)
{
	int columnCount = ui->tableDetail->columnCount();
	ui->tableDetail->setColumnCount(columnCount + 1);
	ui->tableDetail->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(ColName));
	ui->tableDetail->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableDetail->horizontalHeader()->setSectionResizeMode(columnCount, QHeaderView::ResizeToContents);

	//使树节点和表头节点能相互访问
	ui->tableDetail->horizontalHeaderItem(columnCount)->setData(Qt::UserRole, QVariant::fromValue((void *)sp));
	sp->setData(0, Qt::UserRole, columnCount);
}
//作用：向detail页的描述符树中插入新节点，这些节点都不是顶级节点，是parentItem的子节点
void detail::SetTreeItems(StaticData::M_StructuresInfo structInfo, QTreeWidgetItem * parentItem, StaticData &staticdata)
{
	for each(StaticData::M_FieldInfo fieldInfo in structInfo.vecField)
	{
		creatNewItem(parentItem, fieldInfo);
		//如果nestname为空，不是结构体，直接进行展示，否则，寻找名称对应的结构体,分层展示
		//是有效地结构体且非数组，则需要再展开一层，且不占用一行,item设置UserRole=-2表示是非顶级节点也非叶节点
		if (!fieldInfo.NestedName.empty() && fieldInfo.FieldType != StaticData::Array) {
			StaticData::M_StructuresInfo FildStructure = DynamicData::getStructureInfobyName(fieldInfo.NestedName, staticdata);
			//能通过staticdata找到结构体信息，即结构体信息有效
			if (!FildStructure.StructureName.empty()) {
				item->setData(0, Qt::UserRole, -2);
				SetTreeItems(FildStructure, item, staticdata);
				continue;
			}
		}
		//否则不展开，在tableDetail里单独占一列，需要使用creatNewItem(p)中刚申请的item
		//找到祖先节点（描述符）的名字,与Field名结合为列头名
		//应修改为从FieldInfo的DescName获取，要提前在Info里插入（函数调用前）
		QString comName, field = QString::fromStdString(fieldInfo.FieldName);
		//因为此处的节点一定是有parentItem的非顶级节点，所以item->parent()一定有值（后续可做异常处理）
		QTreeWidgetItem *pitem = item->parent();
		while (pitem->parent() != Q_NULLPTR)
			pitem = pitem->parent();
		comName = pitem->text(0) + "\n" + field;
		//特例：Array类型若非有效结构体则存在额外一列，此处处理为前面那一列，名字为#，内容为按钮
		if (fieldInfo.FieldType == StaticData::Array) {
			if (fieldInfo.NestedName.empty() || DynamicData::getStructureInfobyName(fieldInfo.NestedName, staticdata).StructureName.empty()) {
				addColumn("#", item);
				continue;
			}
		}
		//创建新的列
		addColumn(comName, item);
	}
}
