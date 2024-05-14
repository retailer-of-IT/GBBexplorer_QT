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
	//��ǰtab�����treewidget_2�������ڵ�
	ui.treeWidget_2->addTopLevelItem(topItem);
	topItem->setCheckState(0, Qt::Unchecked);
}

void detailMessage::creatNewItem(QTreeWidgetItem *parentItem, QString name)
{
	item = new QTreeWidgetItem(parentItem);
	item->setText(0, name);
	item->setCheckState(0, Qt::Unchecked);
}


