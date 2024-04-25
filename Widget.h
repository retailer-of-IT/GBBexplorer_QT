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
    void on_tableViewdoubleClicked(const QModelIndex &index); //˫����ҳtableview�ϵ�������ת��ʾ����
    void on_removetabbtn(int index); //ɾ����ǩ
    void on_pushButton_8_clicked(); //����ҳȫѡ����Ŀ��ť��ʵ��
    void on_pushButton_7_clicked();//�����ť����ʵ��
    void on_treeWidget_2_clicked(QTreeWidgetItem *item);//treeWidget_2ѡ��/��ѡ�д����¼���ģ��GBBexplorer��ѡ����ȡ��
    void on_treeWidget_clicked(QTreeWidgetItem *item);//treewidgetѡ�н���ȫ��������ʾ

};

#endif // WIDGET_H
