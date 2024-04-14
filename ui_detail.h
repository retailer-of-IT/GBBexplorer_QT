/********************************************************************************
** Form generated from reading UI file 'detail.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAIL_H
#define UI_DETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_detail
{
public:

    void setupUi(QWidget *detail)
    {
        if (detail->objectName().isEmpty())
            detail->setObjectName(QStringLiteral("detail"));
        detail->resize(686, 517);

        retranslateUi(detail);

        QMetaObject::connectSlotsByName(detail);
    } // setupUi

    void retranslateUi(QWidget *detail)
    {
        detail->setWindowTitle(QApplication::translate("detail", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class detail: public Ui_detail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAIL_H
