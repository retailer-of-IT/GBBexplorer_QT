#pragma once

#include <QWidget>
#include "ui_detailMessage.h"

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

public:
	void creatNewTopItem(QString name) ;
	void creatNewItem(QTreeWidgetItem *parentItem, QString name);

	private slots:
	void on_pushButton_7_clicked();//�����ť����ʵ��
	void on_pushButton_8_clicked(); //ʵ������ҳȫѡ����Ŀ��ť��ʵ��
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2ѡ��/��ѡ�д����¼���ģ��GBBexplorer��ѡ����ȡ��

};
