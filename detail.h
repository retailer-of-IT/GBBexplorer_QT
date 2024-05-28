#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <qtreewidget.h>
#include <qstring.h>
#include <QThread>
#include "StaticData.h"
#include "DynamicData.h"

namespace Ui {
	class detail;
}

class EntityRetriever : public QObject { //�����߳���Ϊdetail��������ά���ض����͵�ʵ����б�
	Q_OBJECT
public:
	EntityRetriever(StaticData::M_EntityInfo ei, QTreeWidget *qtw, QThread *tp);
	StaticData::M_EntityInfo entity_info;
	QThread  *thread;
	bool flg;
private:
	QTreeWidget *tWidget;
	DynamicData dD;
public slots:
	void doWork(); //��1��Ϊ���ڶ�ȡ�ض����͵��б�д��treeWidget
};

class detail : public QWidget
{
	Q_OBJECT
public:
	explicit detail(StaticData::M_EntityInfo ei, QWidget *parent = 0);
	~detail();

private:
	Ui::detail *ui;
	QThread  *thread;

public:
	QTreeWidgetItem *topItem;
	QTreeWidgetItem *item;
	EntityRetriever *entityRp;

public:
	void creatNewTopItem(QString name); //�������ڵ�
	void creatNewItem(QTreeWidgetItem *parentItem, QString name); //���ݸ��ڵ㴴���ӽڵ�

signals:
	void EntityRetrieve();
private slots:
	void on_pushButton_7_clicked();//�����ť����ʵ��
	void on_pushButton_8_clicked(); //ʵ������ҳȫѡ����Ŀ��ť��ʵ��
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2ѡ��/��ѡ�д����¼���ģ��GBBexplorer��ѡ����ȡ��
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidgetѡ�н���ȫ��������ʾ
};



#endif // DETAIL_H
