#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <qtreewidget.h>
#include <qstring.h>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include "StaticData.h"
#include "DynamicData.h"

namespace Ui {
	class detail;
}


class EntityRetriever : public QObject { //�����߳���Ϊdetail��������ά���ض����͵�ʵ����б�
	Q_OBJECT
public:
	EntityRetriever(StaticData::M_EntityInfo ei, QTreeWidget *qtw, QThread *tp, QMutex *mp);
	StaticData::M_EntityInfo entity_info;
	QThread  *thread;
	bool flg;
private:
	QTreeWidget *tWidget;
	DynamicData dD;
	QMutex *mutex1_p;
public slots:
	void doWork(); //��1��Ϊ���ڶ�ȡ�ض����͵��б�д��treeWidget
};
class myTest;
class detail : public QWidget
{
	Q_OBJECT
public:
	explicit detail(StaticData::M_EntityInfo ei, QWidget *parent = 0);
	~detail();

private:
	Ui::detail *ui;
	QThread  *thread;
	QMutex mutex1;
	myTest *mT;

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
	void on_pushButton_3_clicked();//ʵ��ȫѡ
	void on_pushButton_2_clicked();//ʵ�����
	void on_pushButton_7_clicked();//�����ť����ʵ��
	void on_pushButton_8_clicked(); //ʵ������ҳȫѡ����Ŀ��ť��ʵ��
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2ѡ��/��ѡ�д����¼���ģ��GBBexplorer��ѡ����ȡ��
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidgetѡ�н���ȫ��������ʾ
};

typedef void* (*comFunc)(void *);
class QTTWorker : public QObject{	Q_OBJECT
private:
	void *in_date;
	comFunc work;
public:
	QTTWorker(comFunc func, void *p);//work��Ҫ�����ݵ�ַp��work��pָ�����Ҫ�Ƕ��еĵ����ݣ�new����������
public slots:
	void do_work();
};

class QTimerThread : public QObject {	Q_OBJECT
public:
	QTimerThread(comFunc func,void * p);  //��������Ҫ�����ݵ�ַ�ʹ������ĵ�ַ
	~QTimerThread();
	void start(int interval);
private:
	QThread *qth_p;
	QTimer *qtm_p;
	QTTWorker *qw_p;
};

class myTest {
public:
	~myTest();
	QTimerThread *qtt;
	static void *test_func(void *p);
	void test();
};

#endif // DETAIL_H
