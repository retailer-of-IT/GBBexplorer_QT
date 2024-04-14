#include "Widget.h"
#include "ui_widget.h"
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QTableView>
#include<QAbstractItemView>
#include<detail.h>
#include<qdebug.h>
#include<iostream>
#include<QPushButton>
#include<QMessageBox>
#include<qtreewidget.h>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Data = false;
    this->initForm();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::initForm()
{
    if(Data)
    {
        //shu
    }
    else
    {
        QStandardItemModel* model = new QStandardItemModel(this);
        model->setHorizontalHeaderItem(0,new QStandardItem("GBB"));
        model->setHorizontalHeaderItem(1,new QStandardItem("Entities"));
        model->setHorizontalHeaderItem(2,new QStandardItem(u8"数量"));
        model->setHorizontalHeaderItem(3,new QStandardItem(u8"最大"));
        model->setHorizontalHeaderItem(4,new QStandardItem("%"));

        //预设一些值
        model->setItem(0, 0, new QStandardItem(u8"张三"));
        model->setItem(0, 1, new QStandardItem("3"));
        model->setItem(0, 2, new QStandardItem(u8"男"));

        ui->tableView_1->setModel(model);
        ui->tableView_1->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_1->setFont(QFont("宋体",15));
        ui->tableView_1->show();

        QStandardItemModel* model2 = new QStandardItemModel(this);
        model2->setHorizontalHeaderItem(0,new QStandardItem("GBB"));
        model2->setHorizontalHeaderItem(1,new QStandardItem("Message"));
        model2->setHorizontalHeaderItem(2,new QStandardItem(u8"数量"));
        model2->setHorizontalHeaderItem(3,new QStandardItem(u8"最大"));
        model2->setHorizontalHeaderItem(4,new QStandardItem("%"));

        model2->setItem(0, 0, new QStandardItem(u8"张三"));
        model2->setItem(0, 1, new QStandardItem("4"));
        model2->setItem(0, 2, new QStandardItem(u8"男"));

        ui->tableView_2->setModel(model2);
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_2->setFont(QFont("宋体",15));
        ui->tableView_2->show();

        QStandardItemModel* model3 = new QStandardItemModel(this);
        model3->setHorizontalHeaderItem(0,new QStandardItem("GBB"));
        model3->setHorizontalHeaderItem(1,new QStandardItem("Descriptor"));
        model3->setHorizontalHeaderItem(2,new QStandardItem(u8"数量"));
        model3->setHorizontalHeaderItem(3,new QStandardItem(u8"最大"));
        model3->setHorizontalHeaderItem(4,new QStandardItem("%"));

        model3->setItem(0, 0, new QStandardItem(u8"张三"));
        model3->setItem(0, 1, new QStandardItem("5"));
        model3->setItem(0, 2, new QStandardItem(u8"男"));

        ui->tableView_3->setModel(model3);
        ui->tableView_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_3->setFont(QFont("宋体",15));
        ui->tableView_3->show();
        Data = true;

        //QPushButton *btnclose = new QPushButton;
        ui->btnclose->setText(u8"关闭所有窗口");
        ui->btnclose->show();


        //标签页面tabWidget
        ui->tabWidget->setTabText(0,u8"主窗口");
        ui->tabWidget->setTabText(1,u8"详细窗口");
        ui->tabWidget->setTabEnabled(0, true);
        ui->tabWidget->setTabEnabled(1, true);
        //ui->tabWidget->removeTab(1);
        //设置页面关闭按钮。
        ui->tabWidget->setTabsClosable(true);

        //链接双击相应事件
        connect(ui->tableView_1,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(on_tableViewdoubleClicked(const QModelIndex &)));
        connect(ui->tableView_2,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(on_tableViewdoubleClicked(const QModelIndex &)));
        connect(ui->tableView_3,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(on_tableViewdoubleClicked(const QModelIndex &)));
        connect(ui->btnclose, &QPushButton::clicked, this, &QWidget::close);
        //关闭窗口
        connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this,&Widget::on_removetabbtn);
        //全选
        //connect(ui->pushButton_8,&QPushButton::clicked,this,&Widget::on_allselectbtn);
        //tablewidget_2勾选列显示
        connect(ui->treeWidget_2,&QTreeWidget::itemChanged,this,&Widget::on_treeWidget_2_clicked);
        //tablewidget勾选行显示
        connect(ui->treeWidget,&QTreeWidget::itemChanged,this,&Widget::on_treeWidget_clicked);

    }
}

//双击显示详情实现
void Widget::on_tableViewdoubleClicked(const QModelIndex &index)
{
    int curRow=index.row();//选中行
    QAbstractItemModel *modessl = ui->tableView_1->model();
    QModelIndex indextemp;
    QVariant data;
    QString infor[1];//用于临时存放行的数据
    //获取第二列的实体名称
    indextemp=modessl->index(curRow,1);
    data=modessl->data(indextemp);
    infor[0]=data.toString();
    QString show=QString(u8"序号："+infor[0]);

    //创建一个新的tab标签页
    QWidget *newTab = new QWidget;
    // 在新的tab页面上添加内容，例如一个标签显示被双击的单元格的文本

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel(this);
    label->setText(show);
    layout->addWidget(label);
    newTab->setLayout(layout);
    // 将新的tab页面添加到QTabWidget并跳转
    ui->tabWidget->addTab(newTab, u8"详情页");
    ui->tabWidget->setCurrentWidget(newTab);
    int openTabsCount = ui->tabWidget->count()+1;
    qDebug(u8"整数：%d", openTabsCount);
    ui->tabWidget->setCurrentIndex(openTabsCount);

    //TODO 详情页展示

    //创建页面样式todo，在界面样式.md文档里


    //数据显示树状tablewidget_2
    //添加顶层节点，这里仅是自己伪造的数据，还没右从系统中读入
    QTreeWidgetItem *topItem1 = new QTreeWidgetItem(QStringList()<<infor[0]);
    QTreeWidgetItem *topItem2 = new QTreeWidgetItem(QStringList()<<infor[0]);
    ui->treeWidget_2->addTopLevelItem(topItem1);
    topItem1->setCheckState(0,Qt::Unchecked);
    ui->treeWidget_2->addTopLevelItem(topItem2);
    topItem2->setCheckState(0,Qt::Unchecked);
    //隐藏表头
    ui->treeWidget_2->setHeaderHidden(true);
    //设置展开
    //ui->treeWidget_2->expandAll();
    QTreeWidgetItem *item11 = new QTreeWidgetItem(topItem1);
    item11->setText(0,u8"研发部");
    item11->setCheckState(0,Qt::Unchecked);
    QTreeWidgetItem *item21 = new QTreeWidgetItem(topItem2);
    item21->setText(0,u8"研究大部");
    item21->setCheckState(0,Qt::Unchecked);
    QTreeWidgetItem *item12 = new QTreeWidgetItem(topItem1);
    item12->setText(0,u8"销售部");
    item12->setCheckState(0,Qt::Unchecked);
    QTreeWidgetItem *item13 = new QTreeWidgetItem(topItem1);
    item13->setText(0,u8"人事部");
    item13->setCheckState(0,Qt::Unchecked);

    //tablewidget中加入
    QTreeWidgetItem *topItem3 = new QTreeWidgetItem(ui->treeWidget);
    QTreeWidgetItem *topItem4 = new QTreeWidgetItem(ui->treeWidget);
    //添加顶层节点
    topItem3->setText(0,"555");
    ui->treeWidget->addTopLevelItem(topItem3);
    topItem4->setText(0,"666");
    ui->treeWidget->addTopLevelItem(topItem4);
    topItem3->setCheckState(0,Qt::Unchecked);
    topItem4->setCheckState(0,Qt::Unchecked);
}

//删除标签
void Widget::on_removetabbtn(int index)
{
    ui->tabWidget->removeTab(index);
}


//全选树子项目的实现
void Widget::on_pushButton_8_clicked()
{
    for (int i = 0; i < ui->treeWidget_2->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(i);
        if (item == nullptr) {
            return;
        }
        item->setCheckState(0,Qt::Checked);
        int count = item->childCount();
        for (int i = 0; i < count; ++i) {
            QTreeWidgetItem *child = item->child(i);
            child->setCheckState(0,Qt::Checked);
        }
    }
}


//清除按钮功能实现
void Widget::on_pushButton_7_clicked()
{
    for (int i = 0; i < ui->treeWidget_2->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(i);
        if (item == nullptr) {
            return;
        }
        item->setCheckState(0,Qt::Unchecked);
        int count = item->childCount();
        for (int i = 0; i < count; ++i) {
            QTreeWidgetItem *child = item->child(i);
            child->setCheckState(0,Qt::Unchecked);
        }
    }
}

//treeWidget_2选中/不选中触发事件
void Widget::on_treeWidget_2_clicked(QTreeWidgetItem *item)
{
    QStandardItemModel* model = new QStandardItemModel(this);
    //QAbstractItemModel *model2 = ui->tableView->model();
    //不是根节点，才展示
    if(item->parent() != nullptr){
        //计算当前列数
        int columnCount = ui->tableView->horizontalHeader()->count();
        //int columnnum = model->columnCount();
        qDebug()<<columnCount;
        QString s = item->text(0);
        if (item->checkState(0) == Qt::Checked){
            //设置列表头名
            model->setHorizontalHeaderItem(ui->tableView->horizontalHeader()->count(),new QStandardItem(s));
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
        else{
            for(int i=0; i<ui->tableView->horizontalHeader()->count(); i++){
                if(ui->tableView->model()->headerData(i,Qt::Horizontal).toString() == s){
                    //ui->tableView->horizontalHeader()->setSectionHidden(i,true);
                    QAbstractItemModel *model = ui->tableView->model();
                    model->removeColumn(i);
                }
            }
            ui->tableView->setModel(model);
        }
    }
}


//treeWidget_2选中/不选中触发事件
//void Widget::on_treeWidget_2_clicked(QTreeWidgetItem *item)
//{
//    //获取tableview，获取列数
//    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
//    int columnCount = model->columnCount();
//    //不是根节点，才展示
//    qDebug()<<"hello";
//    if(item->parent() != nullptr){
//        QString s = item->text(0);
//        if (item->checkState(0) == Qt::Checked){
//            //设置列表头名
//            QStandardItem *newHeaderItem = new QStandardItem(s);
//            model->setHorizontalHeaderItem(columnCount, newHeaderItem);
//            ui->tableView->setModel(model);
//            ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
//            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//        }
//        else{
//            for(int i=0; i<columnCount; i++){
//                QStandardItem *headerItem = model->horizontalHeaderItem(i);
//                if (headerItem && headerItem->text() == s) {
//                     model->removeColumn(columnCount);
//                     break; // 如果只想删除第一个匹配的表头，可以注释掉这行
//                }
//            }
//            ui->tableView->setModel(model);
//        }
//    }
//}

//treewidget选中进行行显示
void Widget::on_treeWidget_clicked(QTreeWidgetItem *item)
{
    QString s = item->text(0);
    QAbstractItemModel *model = ui->tableView->model();
    if (item->checkState(0) == Qt::Checked){
        // 获取行数
        int rowCount = model->rowCount();
        model->insertRow(rowCount);
        model->setData(model->index(rowCount, 0), s);
    }
    else{
        for(int i=0; i<model->rowCount(); i++){
            QModelIndex index = model->index(i, 0);
            if(model->data(index) == s){
                //ui->tableView->horizontalHeader()->setSectionHidden(i,true);
                model->removeRow(i);
            }
        }
    }
    ui->tableView->setModel(model);
    //qDebug()<<"hello";
}










