#ifndef QQSERVERWINDOW_H
#define QQSERVERWINDOW_H

#include <QWidget>
#include "Communication/qqservermessagectrl.h"

namespace Ui {
class QQServerwindow;
}

class QQServerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit QQServerwindow(QWidget *parent = 0);
    ~QQServerwindow();

private:
    Ui::QQServerwindow *ui;
    
    QQServerMessageCtrl *m_serverCtrl;
};

#endif // QQSERVERWINDOW_H
