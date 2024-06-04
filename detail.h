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


class EntityRetriever : public QObject { //在子线程中为detail类周期性维护特定类型的实体的列表
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
	void doWork(); //以1秒为周期读取特定类型的列表并写入treeWidget
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
	void creatNewTopItem(QString name); //创建根节点
	void creatNewItem(QTreeWidgetItem *parentItem, QString name); //根据父节点创建子节点

signals:
	void EntityRetrieve();
private slots:
	void on_pushButton_3_clicked();//实体全选
	void on_pushButton_2_clicked();//实体清除
	void on_pushButton_7_clicked();//清除按钮功能实现
	void on_pushButton_8_clicked(); //实体详情页全选子项目按钮的实现
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2选中/不选中触发事件，模拟GBBexplorer中选择与取消
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidget选中进行全部的行显示
};

typedef void* (*comFunc)(void *);
class QTTWorker : public QObject{	Q_OBJECT
private:
	void *in_date;
	comFunc work;
public:
	QTTWorker(comFunc func, void *p);//work需要的数据地址p和work，p指向的需要是堆中的的数据（new方法创建）
public slots:
	void do_work();
};

class QTimerThread : public QObject {	Q_OBJECT
public:
	QTimerThread(comFunc func,void * p);  //处理函数需要的数据地址和处理函数的地址
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
