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
#include "ArrayDetail.h"

namespace Ui {
	class detail;
}

typedef void(*comFunc)(QVector<void *>);
class QTTWorker : public QObject {
	Q_OBJECT
private:
	QVector<void *>in_date;
	comFunc work;
public:
	QTTWorker(comFunc func, QVector<void *> p);//work需要的数据地址p和work，p指向的需要是堆中的的数据（new方法创建）
	int interval;
	QTimer *qt_p;
	public slots:
	void do_work();
};
class QTimerThread : public QObject {
	Q_OBJECT
public:
	QTimerThread(comFunc func, QVector<void *> p);  //处理函数需要的数据地址和处理函数的地址
	~QTimerThread();
	void start(int interval1, int interval2);
private:
	QThread *qth_p;
	QTimer *qtm_p;
	QTTWorker *qw_p;
};
/*使用说明：（具体细节参考detail内的代码）
step1 准备需要的数据：在类中声明对应类型的指针，并在构造函数中通过new方法为指针申请空间并赋值。
step2 书写处理函数： 函数类型参考comFunc的定义，建议按照类的静态成员函数书写。
step3 运行：在需要开始线程的地方准备好需要的输入数据并创建QTimerThread，执行start()即可。
P.S. 需要自行上锁来保证不出现访问冲突，锁的地址可以作为一个参数保存在in_date向量里，用于处理函数内上锁。
*/

class detail : public QWidget {
	Q_OBJECT
public:
	explicit detail(StaticData::M_EntityInfo ei, QWidget *parent = 0);
	detail();
	~detail();

private:
	Ui::detail *ui;

public:
	QTreeWidgetItem *topItem;
	QTreeWidgetItem *item;
	QTimerThread *qtt_p;
	//以下是一些QTimerThread需要的参数，于构造函数中申请，于堆中存储，于析构函数中销毁。
	QMutex *qmt_p;
	StaticData::M_EntityInfo *ei_p;
	QSet<int> *qsi_p;
	int count = 0; //判断是否已经一次性插入所有表头，初始化为0，全选执行一次后+1，之后只做隐藏/显示
	QVector<QMap<int, CArrayDetail*> > allRowsArrays;

public:
	static void keep_Entities(QVector<void *> in_date);
	void creatNewTopItem(QString name); //创建根节点
	void creatNewItem(QTreeWidgetItem *parentItem, QString name); //根据父节点创建子节点
	void connectArray();

signals:
	void EntityRetrieve();
	void FirstAllSelect();

private slots:
	void on_pushButton_3_clicked();//实体全选
	void on_pushButton_2_clicked();//实体清除
	void on_pushButton_7_clicked();//清除按钮功能实现
	void on_pushButton_8_clicked(); //实体详情页全选子项目按钮的实现
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2选中/不选中触发事件，模拟GBBexplorer中选择与取消
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidget选中进行全部的行显示
};


#endif // DETAIL_H