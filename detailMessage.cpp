#include "detailMessage.h"

detailMessage::detailMessage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}


detailMessage::~detailMessage()
{
}

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


