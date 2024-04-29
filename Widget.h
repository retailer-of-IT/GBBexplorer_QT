#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<qtreewidget.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
	bool Data = false;

private:
    Ui::Widget *ui;


private:
    void initForm(); //��ʼ��������

private slots:
    void on_tableView_1doubleClicked(const QModelIndex &index); //˫����ҳtableview_1�ϵ�������ת��ʾ����
	//void on_tableView_2doubleClicked(const QModelIndex &index); //˫����ҳtableview_2�ϵ�������ת��ʾ����
	//void on_tableView_3doubleClicked(const QModelIndex &index); //˫����ҳtableview_3�ϵ�������ת
    void on_removetabbtn(int index); //ɾ����ǩ

};

#endif // WIDGET_H
