#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include<qtreewidget.h>

namespace Ui {
	class detail;
}

class detail : public QWidget
{
	Q_OBJECT

public:
	explicit detail(QWidget *parent = 0);
	~detail();

private:
	Ui::detail *ui;
	QTreeWidgetItem *topItem;
	void *_model;

public:
	void creatNewTopItem(QString name);
	void creatNewItem(QString name);

	private slots:
	void on_pushButton_8_clicked(); //实体详情页全选子项目按钮的实现
	void on_pushButton_7_clicked();//清除按钮功能实现
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2选中/不选中触发事件，模拟GBBexplorer中选择与取消
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidget选中进行全部的行显示

};

#endif // DETAIL_H
