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
    void initForm(); //初始化主窗口

private slots:
    void on_tableView_1doubleClicked(const QModelIndex &index); //双击主页tableview_1上的名称跳转显示详情
	//void on_tableView_2doubleClicked(const QModelIndex &index); //双击主页tableview_2上的名称跳转显示详情
	//void on_tableView_3doubleClicked(const QModelIndex &index); //双击主页tableview_3上的名称跳转
    void on_removetabbtn(int index); //删除标签

};

#endif // WIDGET_H
