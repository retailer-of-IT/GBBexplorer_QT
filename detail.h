#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include<qtreewidget.h>
#include <qstring.h>

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

public:
	QTreeWidgetItem *topItem;
	QTreeWidgetItem *item;

public:
	void creatNewTopItem(QString name); //�������ڵ�
	void creatNewItem(QTreeWidgetItem *parentItem, QString name); //���ݸ��ڵ㴴���ӽڵ�

	private slots:
	void on_pushButton_8_clicked(); //ʵ������ҳȫѡ����Ŀ��ť��ʵ��
	void on_pushButton_7_clicked();//�����ť����ʵ��
	void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2ѡ��/��ѡ�д����¼���ģ��GBBexplorer��ѡ����ȡ��
	void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidgetѡ�н���ȫ��������ʾ

};

#endif // DETAIL_H
