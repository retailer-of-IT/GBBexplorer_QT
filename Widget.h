#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qtreewidget.h>
#include "StaticData.h"
#include "DynamicData.h"
#include "detail.h"
#include "ArrayDetail.h"
#include <qtimer.h>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
	void keepTableView();
	bool insert2Model(QStandardItemModel *tModel, int row, int col, const QVariant &data);
	static int m_map(char c);
	static bool m_cmp(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b);

private:
	Ui::Widget *ui;
	QTimer *timer;	//用于维护主界面的三个表格
	QStandardItemModel *m_pEntityTableModel, *m_pMessageTableModel, *m_pDescriptorTableModel;	//3表格的model
	QSortFilterProxyModel *m_pEntitySFPModel, *m_pMessageSFPModel,*m_pDescriptorSFPModel;	//3张表格的排序model
	StaticData staticdata;
	DynamicData dD;
	QVector<QMap<int, CArrayDetail *> > ArrayDetailMapList;

private slots:
	void initForm(); //初始化主窗口
    void on_tableView_1doubleClicked(const QModelIndex &index); //双击主页tableview_1(实体)上的名称跳转显示详情
	void on_tableView_2doubleClicked(const QModelIndex &index); //双击主页tableview_2（消息）上的名称跳转显示详情
	void on_closealltabbtn();//关闭所有打开的标签页
    void on_removetabbtn(int index); //删除标签

};

#endif // WIDGET_H
