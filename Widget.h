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
    void on_tableViewdoubleClicked(const QModelIndex &index); //双击主页tableview上的名称跳转显示详情
    void on_removetabbtn(int index); //删除标签
    void on_pushButton_8_clicked(); //详情页全选子项目按钮的实现
    void on_pushButton_7_clicked();//清除按钮功能实现
    void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2选中/不选中触发事件，模拟GBBexplorer中选择与取消
    void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidget选中进行全部的行显示

};

#endif // WIDGET_H
