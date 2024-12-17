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
#include <QStandardItem>
#include "detail.h"
#include "detailMessage.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{	
	ui->setupUi(this);

	//链接双击相应事件-实体页和消息页的双击跳转
	connect(ui->tableView_Entity, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_tableView_1doubleClicked(const QModelIndex &)));
	connect(ui->tableView_Message, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_tableView_2doubleClicked(const QModelIndex &)));

	//关闭全部打开标签tab
	connect(ui->btnclose, &QPushButton::clicked, this, &Widget::on_closealltabbtn);
	//关闭标签
	connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &Widget::on_removetabbtn);
	//思路：在initForm中构造QStandardItemModel，在维护函数中获取model并修改
	initForm();
	//开启QTimer的计时，触发三个表的维护函数
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Widget::keepTableView);
	timer->setInterval(200); 
	timer->start();
}

Widget::~Widget()
{
	delete ui;
}
//返回0表示修改，返回1表示新增
bool Widget::insert2Model(QStandardItemModel *tModel, int row, int col, const QVariant &data) {
	QStandardItem *item = tModel->item(row, col);
	if (item != Q_NULLPTR) {
		item->setData(data, Qt::DisplayRole);
		return 0;
	}
	else {
		tModel->setItem(row, col, new QStandardItem(data.toString()));
		return 1;
	}
}

void Widget::keepTableView() {
	int i, j;	//行、列序号
	QStandardItem *_item;
	//实体表的维护
	for (i = 0; i < staticdata.vecEntityInfoInGBBEx.size(); i++)//以DisplayRole存储
	{
		//第0列：实体类型枚举，其实就是一个int用以区分不同实体类型
		int EnumType = staticdata.vecEntityInfoInGBBEx[i].EnumType;
		insert2Model(m_pEntityTableModel, i, 0, EnumType);
		//第1列：类型名
		QString EntityName = QString::fromStdString(staticdata.vecEntityInfoInGBBEx[i].EntityName);
		insert2Model(m_pEntityTableModel, i, 1, EntityName);
		//第2列：该类型的实体数量
		int n = dD.GetEntityCount(EnumType);
		insert2Model(m_pEntityTableModel, i, 2, n);
		//第3列：最大数量
		int MaxEntityNum = staticdata.vecEntityInfoInGBBEx[i].MaxEntityNum;
		insert2Model(m_pEntityTableModel, i, 3, MaxEntityNum);
		//第4列：当前数量占最大数量的百分比
		double rate = static_cast<double>(n) / MaxEntityNum * 100;	//强转
		insert2Model(m_pEntityTableModel, i, 4, QString::number(rate, 'f', 2));//保留两位小数
	}
	//删除表格里多余的记录行
	_item = m_pEntityTableModel->item(i, 0);
	while (_item!=Q_NULLPTR) {
		m_pEntityTableModel->removeRow(i);
		i++;
		_item = m_pEntityTableModel->item(i, 0);
	}

	//消息表的维护-待完成
	for (i = 0; i < staticdata.vecMessageInfoInGBBEx.size(); i++)
	{
		//第0列：消息类型枚举，其实就是一个int用以区分不同实体类型
		int EnumType = staticdata.vecMessageInfoInGBBEx[i].EnumType;
		insert2Model(m_pMessageTableModel, i, 0, EnumType);
		//第1列：类型名
		QString MessageName = QString::fromStdString(staticdata.vecMessageInfoInGBBEx[i].MessageName);
		insert2Model(m_pMessageTableModel, i, 1, MessageName);
		//第2列：该类型的消息数量
		int n = dD.GetMessageCount(EnumType);
		insert2Model(m_pMessageTableModel, i, 2, n);
		//第3列：最大数量
		int MaxMessageNum = staticdata.vecMessageInfoInGBBEx[i].MaxMessageNum;
		insert2Model(m_pMessageTableModel, i, 3, MaxMessageNum);
		//第4列：当前数量占最大数量的百分比
		double rate = static_cast<double>(n) / MaxMessageNum * 100;//强转
		insert2Model(m_pMessageTableModel, i, 4, QString::number(rate, 'f', 2));//保留两位小数
	}
	//删除表格里多余的记录行
	_item = m_pMessageTableModel->item(i, 0);
	while (_item != Q_NULLPTR) {
		m_pMessageTableModel->removeRow(i);
		i++;
		_item = m_pMessageTableModel->item(i, 0);
	}

	//描述符表的维护-待完成
	for (int i = 0; i < staticdata.vecDescriptorsInfoInGBBEx.size(); i++)
	{
		//第0列：描述符类型枚举，其实就是一个int用以区分不同实体类型
		int EnumType = staticdata.vecDescriptorsInfoInGBBEx[i].EnumType;
		insert2Model(m_pDescriptorTableModel, i, 0, EnumType);
		//第1列：类型名
		QString DescriptorName = QString::fromStdString(staticdata.vecDescriptorsInfoInGBBEx[i].DescriptorName);
		insert2Model(m_pDescriptorTableModel, i, 1, DescriptorName);
		//第2列：该类型的描述符数量
		int n = dD.GetDescriptorCount(EnumType);
		insert2Model(m_pDescriptorTableModel, i, 2, n);
		//第3列：最大数量
		int MaxDescriptorNum = staticdata.vecDescriptorsInfoInGBBEx[i].MaxMessageNum;
		insert2Model(m_pDescriptorTableModel, i, 3, MaxDescriptorNum);
		//第4列：当前数量占最大数量的百分比
		double rate = static_cast<double>(n) / MaxDescriptorNum * 100;//强转
		insert2Model(m_pDescriptorTableModel, i, 4, QString::number(rate, 'f', 2));//保留两位小数
	}
	//删除表格里多余的记录行
	_item = m_pDescriptorTableModel->item(i, 0);
	while (_item != Q_NULLPTR) {
		m_pDescriptorTableModel->removeRow(i);
		i++;
		_item = m_pDescriptorTableModel->item(i, 0);
	}
}
void Widget::initForm()
{
	//实体表初始化
	m_pEntityTableModel = new QStandardItemModel();
	m_pEntitySFPModel = new QSortFilterProxyModel();
	m_pEntitySFPModel->setSourceModel(m_pEntityTableModel);
	m_pEntityTableModel->setHorizontalHeaderItem(0, new QStandardItem("GBB"));
	m_pEntityTableModel->setHorizontalHeaderItem(1, new QStandardItem("Entities"));
	m_pEntityTableModel->setHorizontalHeaderItem(2, new QStandardItem(u8"数量"));
	m_pEntityTableModel->setHorizontalHeaderItem(3, new QStandardItem(u8"最大"));
	m_pEntityTableModel->setHorizontalHeaderItem(4, new QStandardItem("%"));
	//设置实体表排序
	ui->tableView_Entity->setSortingEnabled(true);
	ui->tableView_Entity->horizontalHeader()->setSortIndicatorShown(true);
	ui->tableView_Entity->setModel(m_pEntitySFPModel);	//展示排序后的数据
	ui->tableView_Entity->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui->tableView_Entity->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView_Entity->setFont(QFont("宋体", 15));
	ui->tableView_Entity->show();
	//消息表初始化-待完成
	m_pMessageTableModel = new QStandardItemModel(this);
	m_pMessageSFPModel = new QSortFilterProxyModel();
	m_pMessageSFPModel->setSourceModel(m_pMessageTableModel);
	m_pMessageTableModel->setHorizontalHeaderItem(0, new QStandardItem("GBB"));
	m_pMessageTableModel->setHorizontalHeaderItem(1, new QStandardItem("Message"));
	m_pMessageTableModel->setHorizontalHeaderItem(2, new QStandardItem(u8"数量"));
	m_pMessageTableModel->setHorizontalHeaderItem(3, new QStandardItem(u8"最大"));
	m_pMessageTableModel->setHorizontalHeaderItem(4, new QStandardItem("%"));
	//设置消息表排序
	ui->tableView_Message->setSortingEnabled(true);
	ui->tableView_Message->horizontalHeader()->setSortIndicatorShown(true);
	ui->tableView_Message->setModel(m_pMessageSFPModel);
	ui->tableView_Message->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui->tableView_Message->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView_Message->setFont(QFont("宋体", 15));
	ui->tableView_Message->show();
	//描述符表初始化-待完成
	m_pDescriptorTableModel = new QStandardItemModel(this);
	m_pDescriptorSFPModel = new QSortFilterProxyModel();
	m_pDescriptorSFPModel->setSourceModel(m_pDescriptorTableModel);
	m_pDescriptorTableModel->setHorizontalHeaderItem(0, new QStandardItem("GBB"));
	m_pDescriptorTableModel->setHorizontalHeaderItem(1, new QStandardItem("Descriptor"));
	m_pDescriptorTableModel->setHorizontalHeaderItem(2, new QStandardItem(u8"数量"));
	m_pDescriptorTableModel->setHorizontalHeaderItem(3, new QStandardItem(u8"最大"));
	m_pDescriptorTableModel->setHorizontalHeaderItem(4, new QStandardItem("%"));
	//设置描述符表排序
	ui->tableView_Descriptor->setSortingEnabled(true);
	ui->tableView_Descriptor->horizontalHeader()->setSortIndicatorShown(true);
	ui->tableView_Descriptor->setModel(m_pDescriptorSFPModel);
	ui->tableView_Descriptor->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui->tableView_Descriptor->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView_Descriptor->setFont(QFont("宋体", 15));
	ui->tableView_Descriptor->show();

	ui->btnclose->setText(u8"全部关闭");
	ui->btnclose->show();
	//直接先进行一次更新
	//keepTableView();

	//标签主页面tabWidget
	ui->tabWidget->setTabText(0, u8"主窗口");
	ui->tabWidget->setTabEnabled(0, true); 
	//设置页面关闭按钮。
	ui->tabWidget->setTabsClosable(true);
}
//下面两个函数用于修正对字符串的排序结果与原版C#结果不同的问题
int Widget::m_map(char c) {
	if (c >= 'a'&&c <= 'z')
		return (c - 'a') * 2 + 256;
	if (c >= 'A'&&c <= 'Z')
		return (c - 'A') * 2 + 257;
	if (c >= '0'&&c <= '9')
		return c + 128;
	return c;
}
bool Widget::m_cmp(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b){
	int va, vb;		//判断是否小于
	std::string sa = a.second, sb = b.second;
	for (int i = 0; ; i++) {
		va = m_map(sa[i]);
		vb = m_map(sb[i]);
//		cout<<va<<","<<vb<<"; ";
		if (va == vb) {
			if (sa[i] == 0) return 0;
			continue;
		}
		return va<vb;
	}
	return 0;
}

//双击实体栏显示详情实现
void Widget::on_tableView_1doubleClicked(const QModelIndex &index)
{
	int curRow = index.row();//选中行
	QAbstractItemModel *modessl = ui->tableView_Entity->model();
	QModelIndex indextemp;
	QVariant data;
	//获取第二列的实体名称
	indextemp = modessl->index(curRow, 1);
	data = modessl->data(indextemp);
	QString s = data.toString();

	//找到所有实体对应的描述符
	//QList<std::string> allValues = staticdata.vecEntityInfo[curRow].mapDescriptores.values();
	StaticData::M_EntityInfo _vecInfo;
	for each(StaticData::M_EntityInfo vecInfo in staticdata.vecEntityInfo) {
		if (QString::fromStdString(vecInfo.EntityName) == s) {
			_vecInfo = vecInfo;
			break;
		}
	}

	//排序_vecInfo中的map的values，按照字典序比较，保持与GBBExplorer相同，以便后续动态数据的视图读取顺序
	QVector<std::pair<int, std::string> > items;
	for (auto it = _vecInfo.mapDescriptores.constBegin(); it != _vecInfo.mapDescriptores.constEnd(); ++it) {
		items.append(std::pair<int, std::string>(it.key(), it.value()));
	}
	std::sort(items.begin(), items.end(), Widget::m_cmp);

	//创建一个新的tab标签页
	detail *newTab = new detail(_vecInfo);
	//qDebug() << "new detail is : " << newTab << " | " << QThread::currentThreadId();
	// 将新的tab页面添加到QTabWidget并跳转
	QString tabName = "Entity-" + s;
	ui->tabWidget->addTab(newTab, tabName);
	ui->tabWidget->setCurrentWidget(newTab);
	int openTabsCount = ui->tabWidget->count() + 1;
	//设置详情页的实体个数信息
	QLabel* label = qobject_cast<QLabel*>(newTab->findChild<QLabel*>("lbEntities"));
	int numOfEntities = dD.GetEntityCount(_vecInfo.EnumType);
	QString labelText = "Entities(" + QString::number(numOfEntities) + ")";
	label->setText(labelText);
	//设置详情页的描述符个数信息
	QLabel* label2 = qobject_cast<QLabel*>(newTab->findChild<QLabel*>("lbDescriptors"));
	int numOfDes = _vecInfo.mapDescriptores.size();
	QString labelText2 = "Descriptors(" + QString::number(numOfDes) + ")";
	label2->setText(labelText2);
	//为了让树和表的节点能够相互访问：
	//树节点的value为：
	//UserRole(对叶子节点来说为对应的列Index，对顶级节点为-1，若都不是则为-2)
	//UserRole+1(M_DescriptorsInfo或M_FieldInfo，取决于深度)
	//列表头的value为:
	//UserRole(对应的树节点指针转为void*，使用时记得将void*转回QTreeWidgetItem*)
	//处理树节点
	for each(auto var in items)
	{
		//处理items里记录的描述符，这是第一层
		StaticData::M_DescriptorsInfo desInfo = DynamicData::getDescInfobyType(var.first, staticdata);
		newTab->creatNewTopItem(desInfo);
		//设置UserRole的列号需要在后面进行
		StaticData::M_StructuresInfo structInfo = DynamicData::getStructureInfobyName(desInfo.StructureName, staticdata);
		//根据描述符的结构体信息找到对应的Field数组，根据其设置树的非顶级节点
		newTab->SetTreeItems(structInfo, newTab->topItem, staticdata);
	}
	//emit newTab->FirstAllSelect();//发射信号，触发一次全选操作，执行插入列表头操作，count+1
	dD.GetEntityDynamicData(_vecInfo.EnumType, items, newTab);  
}

//双击消息栏显示详情
void Widget::on_tableView_2doubleClicked(const QModelIndex & index)
{
	int curRow = index.row();//选中行
	QAbstractItemModel *modessl = ui->tableView_Message->model();
	QModelIndex indextemp;
	QVariant data;
	indextemp = modessl->index(curRow, 1);
	data = modessl->data(indextemp);
	//获取第二列消息名称
	QString s = data.toString();
	//创建一个新的tab标签页
	detailMessage *newTab = new detailMessage;
	// 将新的tab页面添加到QTabWidget并跳转
	QString tabName = "Message-" + s;
	ui->tabWidget->addTab(newTab, tabName);
	ui->tabWidget->setCurrentWidget(newTab);
	int openTabsCount = ui->tabWidget->count() + 1;
	//判断是否是描述符消息，用m_bIsDescAsMessage判断
	bool flag = false;
	StaticData::M_MessageInfo cur_MsgInfo;
	for each(StaticData::M_MessageInfo msgInfo in staticdata.vecMessageInfo)
	{
		if (QString::fromStdString(msgInfo.MessageName) == s)
		{
			cur_MsgInfo = msgInfo;
			if (msgInfo.m_bIsDescAsMessage)
				flag = true;
		}
	}
	StaticData::M_FieldInfo CT_field;
	CT_field.FieldName = "Creation Time";
	newTab->creatNewTopItem(CT_field);
	if (flag)
	{
		StaticData::M_FieldInfo met_field;
		met_field.FieldName = "MET_ID";
		newTab->creatNewTopItem(met_field);
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
						//如果nestedname为空，不是结构体，直接进行展示
						if (fieldInfo.NestedName.empty())
						{
							newTab->creatNewTopItem(fieldInfo);
						}
						//否则，寻找名称对应的结构体,分层展示
						else
						{
							newTab->creatNewTopItem(fieldInfo);
							for each(StaticData::M_StructuresInfo structInfo2 in staticdata.vecStructuresInfo)
							{
								if (structInfo2.StructureName == fieldInfo.NestedName) {
									for each(StaticData::M_FieldInfo fieldInfo2 in structInfo2.vecField)
									{
										QTreeWidgetItem *item1 = new QTreeWidgetItem(newTab->topItem);
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
	emit newTab->FirstAllSelect();//发射信号，触发一次全选操作，执行插入列表头操作，count+1
	// 创建 QTimer 对象并启动
	newTab->m_timer = new QTimer(newTab);
	connect(newTab->m_timer, &QTimer::timeout, [=]() {
		long long tmp = 1000;
		dD.GetMessageWithAckTableData(cur_MsgInfo.EnumType, newTab, tmp);
	});
	newTab->m_timer->start(1000); // 每 1 秒钟触发一次
}

//关闭全部打开的标签(主页除外)
void Widget::on_closealltabbtn()
{
	for (int i = ui->tabWidget->count() - 1; i > 0; i--)
	{
		Widget *p = (Widget*)(ui->tabWidget->widget(i));
		ui->tabWidget->removeTab(i);
		delete p;
	}
}


//删除标签
void Widget::on_removetabbtn(int index)
{
	detail *p = (detail*)(ui->tabWidget->widget(index));
	ui->tabWidget->removeTab(index);
	qDebug() << "widget(index) is : " << p;
	delete p;
}