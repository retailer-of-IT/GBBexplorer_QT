#include "Widget.h"
#include "ui_widget.h"
#include "StaticData.h"
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QTableView>
#include <QAbstractItemView>
#include <qdebug.h>
#include <iostream>
#include <QPushButton>
#include <QMessageBox>
#include <qtreewidget.h>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include "detail.h"
#include "detailMessage.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
	//集中初始化,后面直接取即可
	staticdata.InitDescriptors();
	staticdata.InitEntities();
	staticdata.InitStructures();
	staticdata.InitMessages();

	//链接双击相应事件
	connect(ui->tableView_1, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_tableView_1doubleClicked(const QModelIndex &)));
	connect(ui->tableView_2, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_tableView_2doubleClicked(const QModelIndex &)));

	//关闭全部打开标签tab
	connect(ui->btnclose, &QPushButton::clicked, this, &Widget::on_closealltabbtn);
	//关闭标签
	connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &Widget::on_removetabbtn);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Widget::initForm);
	timer->setInterval(1000); // 每隔1秒刷新一次主界面数据
	//开启主界面线程（）
	timer->start();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::initForm()
{
	qDebug() << u8"GBB主页面线程启动";
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0,new QStandardItem("GBB"));
    model->setHorizontalHeaderItem(1,new QStandardItem("Entities"));
    model->setHorizontalHeaderItem(2,new QStandardItem(u8"数量"));
    model->setHorizontalHeaderItem(3,new QStandardItem(u8"最大"));
    model->setHorizontalHeaderItem(4,new QStandardItem("%"));

	//读取entity数据显示
	for (int i = 0; i < staticdata.vecEntityInfoInGBBEx.size(); i++)
	{
		int EnumType = staticdata.vecEntityInfoInGBBEx[i].EnumType;
		QStandardItem *item = new QStandardItem();
		item->setData(EnumType, Qt::EditRole);
		QString EntityName = QString::fromStdString(staticdata.vecEntityInfoInGBBEx[i].EntityName);
		int MaxEntityNum = staticdata.vecEntityInfoInGBBEx[i].MaxEntityNum;
		QStandardItem *item1 = new QStandardItem();
		item1->setData(MaxEntityNum, Qt::EditRole);
		model->setItem(i, 0, item);
		model->setItem(i, 1, new QStandardItem(EntityName));
		int n = dD.GetEntityCount(EnumType);
		//int n = entityNum[i];
		model->setItem(i, 2, new QStandardItem(QString::number(n)));
		model->setItem(i, 3, item1);
		double rate = static_cast<double>(n)/MaxEntityNum*100;//强转
		QString formattedRate = QString::number(rate, 'f', 2);//保留两位小数
		model->setItem(i, 4, new QStandardItem(formattedRate));
	}

    ui->tableView_1->setModel(model);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_1->setFont(QFont("宋体",15));
	ui->tableView_1->setSortingEnabled(true);
    ui->tableView_1->show();

    QStandardItemModel* model2 = new QStandardItemModel(this);
    model2->setHorizontalHeaderItem(0,new QStandardItem("GBB"));
    model2->setHorizontalHeaderItem(1,new QStandardItem("Message"));
    model2->setHorizontalHeaderItem(2,new QStandardItem(u8"数量"));
    model2->setHorizontalHeaderItem(3,new QStandardItem(u8"最大"));
    model2->setHorizontalHeaderItem(4,new QStandardItem("%"));

	//读取message数据显示
	for (int i = 0; i < staticdata.vecMessageInfoInGBBEx.size(); i++)
	{
		int EnumType = staticdata.vecMessageInfoInGBBEx[i].EnumType;
		QStandardItem *item = new QStandardItem();
		item->setData(EnumType, Qt::EditRole);
		QString MessageName = QString::fromStdString(staticdata.vecMessageInfoInGBBEx[i].MessageName);
		int MaxMessageNum = staticdata.vecMessageInfoInGBBEx[i].MaxMessageNum;
		QStandardItem *item1 = new QStandardItem();
		item1->setData(MaxMessageNum, Qt::EditRole);
		model2->setItem(i, 0, item);
		model2->setItem(i, 1, new QStandardItem(MessageName));
		int n = dD.GetMessageCount(EnumType);
		model2->setItem(i, 2, new QStandardItem(QString::number(n)));
		model2->setItem(i, 3, item1);
		double rate = static_cast<double>(n) / MaxMessageNum * 100;//强转
		QString formattedRate = QString::number(rate, 'f', 2);//保留两位小数
		model2->setItem(i, 4, new QStandardItem(formattedRate));
	}

    ui->tableView_2->setModel(model2);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setFont(QFont("宋体",15));
	ui->tableView_2->setSortingEnabled(true);
    ui->tableView_2->show();

    QStandardItemModel* model3 = new QStandardItemModel(this);
    model3->setHorizontalHeaderItem(0,new QStandardItem("GBB"));
    model3->setHorizontalHeaderItem(1,new QStandardItem("Descriptor"));
    model3->setHorizontalHeaderItem(2,new QStandardItem(u8"数量"));
    model3->setHorizontalHeaderItem(3,new QStandardItem(u8"最大"));
    model3->setHorizontalHeaderItem(4,new QStandardItem("%"));

	//读取descriptors数据显示
	for (int i = 0; i < staticdata.vecDescriptorsInfoInGBBEx.size(); i++)
	{
		int EnumType = staticdata.vecDescriptorsInfoInGBBEx[i].EnumType;
		QStandardItem *item = new QStandardItem();
		item->setData(EnumType, Qt::EditRole);
		QString DescriptorName = QString::fromStdString(staticdata.vecDescriptorsInfoInGBBEx[i].DescriptorName);
		int MaxDescriptorNum = staticdata.vecDescriptorsInfoInGBBEx[i].MaxMessageNum;
		QStandardItem *item1 = new QStandardItem();
		item1->setData(MaxDescriptorNum, Qt::EditRole);
		model3->setItem(i, 0, item);
		model3->setItem(i, 1, new QStandardItem(DescriptorName));
		int n = dD.GetDescriptorCount(EnumType);
		model3->setItem(i, 2, new QStandardItem(QString::number(n)));
		model3->setItem(i, 3, item1);
		double rate = static_cast<double>(n) / MaxDescriptorNum * 100;//强转
		QString formattedRate = QString::number(rate, 'f', 2);//保留两位小数
		model3->setItem(i, 4, new QStandardItem(formattedRate));
	}

    ui->tableView_3->setModel(model3);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->setFont(QFont("宋体",15));
	ui->tableView_3->setSortingEnabled(true);
    ui->tableView_3->show();
    Data = true;

    ui->btnclose->setText(u8"全部关闭");
    ui->btnclose->show();


    //标签页面tabWidget
    ui->tabWidget->setTabText(0,u8"主窗口");
    ui->tabWidget->setTabText(1,u8"详细窗口");
    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, true);
    //ui->tabWidget->removeTab(1);
    //设置页面关闭按钮。
    ui->tabWidget->setTabsClosable(true);
}


//双击实体栏显示详情实现
void Widget::on_tableView_1doubleClicked(const QModelIndex &index)
{
    int curRow = index.row();//选中行
    QAbstractItemModel *modessl = ui->tableView_1->model();
    QModelIndex indextemp;
    QVariant data;
    //获取第二列的实体名称
    indextemp = modessl->index(curRow,1);
    data = modessl->data(indextemp);
    QString s = data.toString();

	//找到所有实体对应的描述符
	//QList<std::string> allValues = staticdata.vecEntityInfo[curRow].mapDescriptores.values();
	StaticData::M_EntityInfo _vecInfo;
	for each(StaticData::M_EntityInfo vecInfo in staticdata.vecEntityInfo){
		if (QString::fromStdString(vecInfo.EntityName) == s){
			_vecInfo = vecInfo;
			break;
		}
	}
    //创建一个新的tab标签页
    detail *newTab = new detail(_vecInfo);
	qDebug() << "new detail is : " << newTab;
    // 将新的tab页面添加到QTabWidget并跳转
	QString tabName = "Entity-" + s;
    ui->tabWidget->addTab(newTab,tabName);
    ui->tabWidget->setCurrentWidget(newTab);
    int openTabsCount = ui->tabWidget->count()+1;
	//设置详情页的描述符和实体个数信息
	QLabel* label = qobject_cast<QLabel*>(newTab->findChild<QLabel*>("label_4"));
	int numOfEntities = dD.GetEntityCount(_vecInfo.EnumType);
	QString labelText = "Entities(" + QString::number(numOfEntities) + ")";
	label->setText(labelText);
	QLabel* label2 = qobject_cast<QLabel*>(newTab->findChild<QLabel*>("label_5"));
	int numOfDes = _vecInfo.mapDescriptores.size();
	QString labelText2 = "Descriptors(" + QString::number(numOfDes) + ")";
	label2->setText(labelText2);

	for each(int var in _vecInfo.mapDescriptores.keys())
	{
		newTab->creatNewTopItem(QString::fromStdString(_vecInfo.mapDescriptores[var]));
		for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfoInGBBEx) 
		{
			if (desInfo.EnumType == var) 
			{
				for each(StaticData::M_StructuresInfo structInfo in staticdata.vecStructuresInfo)
				{
					if (structInfo.StructureName == desInfo.StructureName) 
					{
						for each(StaticData::M_FieldInfo fieldInfo in structInfo.vecField)
						{
							QString field = QString::fromStdString(fieldInfo.FieldName);
							//如果nestname为空，不是结构体，直接进行展示
							if (fieldInfo.NestedName.empty())
							{
								newTab->creatNewItem(newTab->topItem, field);
	//							qDebug() << "hello";
							}
							//否则，寻找名称对应的结构体,分层展示
							else
							{
								newTab->creatNewItem(newTab->topItem, field);
								for each(StaticData::M_StructuresInfo structInfo2 in staticdata.vecStructuresInfo)
								{
									if (structInfo2.StructureName == fieldInfo.NestedName) {
										for each(StaticData::M_FieldInfo fieldInfo2 in structInfo2.vecField)
										{
											QTreeWidgetItem *item1 = new QTreeWidgetItem(newTab->item);
											item1->setText(0, QString::fromStdString(fieldInfo2.FieldName));
											item1->setCheckState(0, Qt::Unchecked);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


void Widget::on_tableView_2doubleClicked(const QModelIndex & index)
{
	int curRow = index.row();//选中行
	QAbstractItemModel *modessl = ui->tableView_2->model();
	QModelIndex indextemp;
	QVariant data;
	indextemp = modessl->index(curRow, 1);
	data = modessl->data(indextemp);
	//获取第二列消息名称
	QString s  = data.toString();
	//创建一个新的tab标签页
	detailMessage *newTab = new detailMessage;
	// 将新的tab页面添加到QTabWidget并跳转
	QString tabName = "Message-" + s;
	ui->tabWidget->addTab(newTab, tabName);
	ui->tabWidget->setCurrentWidget(newTab);
	int openTabsCount = ui->tabWidget->count() + 1;
	//判断是否是描述符消息，用m_bIsDescAsMessage判断
	bool flag = false;
	for each(StaticData::M_MessageInfo msgInfo in staticdata.vecMessageInfo)
	{
		if (QString::fromStdString(msgInfo.MessageName) == s)
		{
			if (msgInfo.m_bIsDescAsMessage)
				flag = true;
		}
	}
	newTab->creatNewTopItem("Creation Time");
	if (flag)
	{
		newTab->creatNewTopItem("MET_ID");
	}
	//匹配消息描述符名称，找到对应结构struct
	for each(StaticData::M_DescriptorsInfo desInfo in staticdata.vecDescriptorsInfo)
	{
		if (QString::fromStdString(desInfo.DescriptorName) == s) 
		{
			for each(StaticData::M_StructuresInfo structInfo in staticdata.vecStructuresInfo) 
			{
				if (structInfo.StructureName == desInfo.StructureName) 
				{
					for each(StaticData::M_FieldInfo fieldInfo in structInfo.vecField)
					{
						QString field = QString::fromStdString(fieldInfo.FieldName);
						//如果nestedname为空，不是结构体，直接进行展示
						if (fieldInfo.NestedName.empty())
						{
							newTab->creatNewTopItem(field);
						}
						//否则，寻找名称对应的结构体,分层展示
						else
						{
							newTab->creatNewTopItem(field); 
							for each(StaticData::M_StructuresInfo structInfo2 in staticdata.vecStructuresInfo)
							{
								if (structInfo2.StructureName == fieldInfo.NestedName) {
									for each(StaticData::M_FieldInfo fieldInfo2 in structInfo2.vecField)
									{
										QTreeWidgetItem *item1 = new QTreeWidgetItem(newTab->topItem);
										item1->setText(0, QString::fromStdString(fieldInfo2.FieldName));
										item1->setCheckState(0, Qt::Checked);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

//关闭全部打开的标签(主页除外)
void Widget::on_closealltabbtn()
{
	for (int i = ui->tabWidget->count() - 1; i > 0; i--) 
	{
		detail *p = (detail*)(ui->tabWidget->widget(i));
		ui->tabWidget->removeTab(i);
		delete p->entityRp;
		delete p;
	}
}


//删除标签
void Widget::on_removetabbtn(int index)
{
	detail *p = (detail*)(ui->tabWidget->widget(index));
    ui->tabWidget->removeTab(index);
	qDebug() << "widget(index) is : " << p;
	delete p->entityRp;
	delete p;
}













