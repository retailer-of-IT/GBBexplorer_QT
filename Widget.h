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
	static int m_map(char c);
	static bool m_cmp(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b);

private:
	Ui::Widget *ui;
	QTimer *timer;
	QStandardItemModel *m_pEntityTableModel, *m_pMessageTableModel, *m_pDescriptorTableModel;
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
