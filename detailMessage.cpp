#include "detailMessage.h"
#include <qdebug.h>

detailMessage::detailMessage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//tablewidget_2勾选列显示
	connect(ui.treeWidget_2, &QTreeWidget::itemChanged, this, &detailMessage::on_treeWidget_2_clicked);
}
detailMessage::~detailMessage(){}

void detailMessage::creatNewTopItem(QString name)
{
	topItem = new QTreeWidgetItem(QStringList() << name);
	//当前tab界面的treewidget_2建立根节点
	ui.treeWidget_2->addTopLevelItem(topItem);
	topItem->setCheckState(0, Qt::Unchecked);
}
void detailMessage::creatNewItem(QTreeWidgetItem *parentItem, QString name)
{
	item = new QTreeWidgetItem(parentItem);
	item->setText(0, name);
	item->setCheckState(0, Qt::Unchecked);
}

void detailMessage::on_treeWidget_2_clicked(QTreeWidgetItem * item)
{
	QString s = item->text(0), _s = s;
	if (item->parent() != Q_NULLPTR)
		_s = ((item->parent()->parent() != Q_NULLPTR) ? (item->parent()->parent()->text(0)) : (item->parent()->text(0))) + "\n" + _s;
	Qt::CheckState ist = item->checkState(0);
	int columnCount = ui.tableWidget->columnCount();
	qDebug() << QString("reach %1 when %2 columns").arg(s, QString(columnCount));
	if (item->child(0) == Q_NULLPTR) {	//最后一层节点，才展示
		if (ist == Qt::Checked) { //增加列表头
			ui.tableWidget->setColumnCount(columnCount + 1);
			ui.tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(_s));
			ui.tableWidget->horizontalHeader()->setSectionResizeMode(columnCount, QHeaderView::ResizeToContents);
			ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		}
		else { //删除列表头
			for (int i = 0; i< columnCount; i++) {
				QString name = ui.tableWidget->model()->headerData(i, Qt::Horizontal).toString();
				name.remove(0, name.lastIndexOf("\n") + 1);
				if (name == s) {
					QAbstractItemModel *model = ui.tableWidget->model();
					model->removeColumn(i);
					break;
				}
			}
		}
	}
	if (item->checkState(0) == Qt::PartiallyChecked) { //子到父导致，继续向上
		if (item->parent() != Q_NULLPTR && item->parent()->checkState(0) != Qt::PartiallyChecked) {
			item->parent()->setCheckState(0, Qt::PartiallyChecked);
			//			qDebug() << QString("\tcheckstate set on %1").arg(item->parent()->text(0));
		}
		return;
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
			pp->setCheckState(0, ist);
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
void detailMessage::on_pushButton_7_clicked()
{
	for (int i = 0; i < ui.treeWidget_2->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui.treeWidget_2->topLevelItem(i);
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
void detailMessage::on_pushButton_8_clicked()
{
	for (int i = 0; i < ui.treeWidget_2->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui.treeWidget_2->topLevelItem(i);
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
