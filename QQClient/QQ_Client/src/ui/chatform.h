/*********************************************
File Name： IMChatWidget.h
Author： StormZhou
Description： 用于控制聊天界面的类
********************************************/
#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include "data_pools.h"
#include <QtNetwork>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include <QScrollBar>
#include <QSqlDatabase>
#include <QSqlQuery>


#include "qqConstant.h"

namespace Ui {
class ChatForm;
}

class ChatForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit ChatForm(const ChatInformation &chatInf, QWidget *parent = 0);
    ~ChatForm();


protected:
      QWidget*getDragnWidget();

private:
    Ui::ChatForm *ui;

    ChatInformation m_chatInfor;

    void initChatForm();
    void linkSignalWithSlot();



private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();
//    void pb_send_clicked();

signals:


};

#endif // CHATFORM_H
