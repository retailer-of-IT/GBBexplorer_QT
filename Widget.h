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
    bool Data;

private:
    Ui::Widget *ui;


private:
    void initForm();


private slots:
    void on_tableViewdoubleClicked(const QModelIndex &index);
    void on_removetabbtn(int index);
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_treeWidget_2_clicked(QTreeWidgetItem *item);
    void on_treeWidget_clicked(QTreeWidgetItem *item);

};

#endif // WIDGET_H
