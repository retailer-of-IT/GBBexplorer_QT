#pragma once

#include <QWidget>
#include "ui_detailMessage.h"
#include "StaticData.h"
#include <qtimer.h>

class detailMessage : public QWidget
{
	Q_OBJECT

public:
	detailMessage(QWidget *parent = Q_NULLPTR) ;
	~detailMessage();

private:
	Ui::detailMessage ui;

public:
	QTreeWidgetItem *topItem;
	QTreeWidgetItem *item;
	int count = 0; //判断是否已经一次性插入所有表头，初始化为0，全选执行一次后+1，之后只做隐藏/显示
	QTimer* m_timer = nullptr;
	StaticData::M_MessageInfo m_curMsgInfo;

public:
	void creatNewTopItem(QString name) ;
	void creatNewItem(QTreeWidgetItem *parentItem, QString name);

signals:
	void FirstAllSelect();

private slots:
	void on_pushButton_7_clicked();//清除按钮功能实现
	void on_pushButton_8_clicked(); //实体详情页全选子项目按钮的实现
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2选中/不选中触发事件，模拟GBBexplorer中选择与取消

};
