#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>

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
};

#endif // DETAIL_H
