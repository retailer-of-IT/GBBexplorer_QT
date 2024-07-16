#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qtreewidget.h>
#include "StaticData.h"
#include "DynamicData.h"
#include "detail.h"
#include "ArrayDetail.h"
#include <qtimer.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
	Ui::Widget *ui;
	QTimer* timer;
	bool Data = false;
	//���ʵ��������
	StaticData staticdata;
	DynamicData dD;
	QVector<QMap<int, CArrayDetail *> > ArrayDetailMapList;

private slots:
	void initForm(); //��ʼ��������
    void on_tableView_1doubleClicked(const QModelIndex &index); //˫����ҳtableview_1(ʵ��)�ϵ�������ת��ʾ����
	void on_tableView_2doubleClicked(const QModelIndex &index); //˫����ҳtableview_2����Ϣ���ϵ�������ת��ʾ����
	void on_closealltabbtn();//�ر����д򿪵ı�ǩҳ
    void on_removetabbtn(int index); //ɾ����ǩ

};

#endif // WIDGET_H
