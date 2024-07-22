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
	QTTWorker(comFunc func, QVector<void *> p);//work��Ҫ�����ݵ�ַp��work��pָ�����Ҫ�Ƕ��еĵ����ݣ�new����������
	int interval;
	QTimer *qt_p;
	public slots:
	void do_work();
};
class QTimerThread : public QObject {
	Q_OBJECT
public:
	QTimerThread(comFunc func, QVector<void *> p);  //��������Ҫ�����ݵ�ַ�ʹ������ĵ�ַ
	~QTimerThread();
	void start(int interval1, int interval2);
private:
	QThread *qth_p;
	QTimer *qtm_p;
	QTTWorker *qw_p;
};
/*ʹ��˵����������ϸ�ڲο�detail�ڵĴ��룩
step1 ׼����Ҫ�����ݣ�������������Ӧ���͵�ָ�룬���ڹ��캯����ͨ��new����Ϊָ������ռ䲢��ֵ��
step2 ��д�������� �������Ͳο�comFunc�Ķ��壬���鰴����ľ�̬��Ա������д��
step3 ���У�����Ҫ��ʼ�̵߳ĵط�׼������Ҫ���������ݲ�����QTimerThread��ִ��start()���ɡ�
P.S. ��Ҫ������������֤�����ַ��ʳ�ͻ�����ĵ�ַ������Ϊһ������������in_date��������ڴ�������������
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
	//������һЩQTimerThread��Ҫ�Ĳ������ڹ��캯�������룬�ڶ��д洢�����������������١�
	QMutex *qmt_p;
	StaticData::M_EntityInfo *ei_p;
	QSet<int> *qsi_p;
	int count = 0; //�ж��Ƿ��Ѿ�һ���Բ������б�ͷ����ʼ��Ϊ0��ȫѡִ��һ�κ�+1��֮��ֻ������/��ʾ
	QVector<QMap<int, CArrayDetail*> > allRowsArrays;

public:
	static void keep_Entities(QVector<void *> in_date);
	void creatNewTopItem(QString name); //�������ڵ�
	void creatNewItem(QTreeWidgetItem *parentItem, QString name); //���ݸ��ڵ㴴���ӽڵ�
	void connectArray();

signals:
	void EntityRetrieve();
	void FirstAllSelect();

private slots:
	void on_pushButton_3_clicked();//ʵ��ȫѡ
	void on_pushButton_2_clicked();//ʵ�����
	void on_pushButton_7_clicked();//�����ť����ʵ��
	void on_pushButton_8_clicked(); //ʵ������ҳȫѡ����Ŀ��ť��ʵ��
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2ѡ��/��ѡ�д����¼���ģ��GBBexplorer��ѡ����ȡ��
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidgetѡ�н���ȫ��������ʾ
};


#endif // DETAIL_H