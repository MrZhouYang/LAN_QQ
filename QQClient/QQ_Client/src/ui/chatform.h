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
#include <QCloseEvent>
#include "QQClientFileCtrl.h"


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

    // 将好友发来的信息添加到显示窗口
    void appendMessageShow(const TalkMessage &mes);


protected:
      QWidget*getDragnWidget();
      //重载关闭事件
      void closeEvent(QCloseEvent *event);

private:
    Ui::ChatForm *ui;

    ChatInformation m_chatInfor;
    TalkMessage m_mes;

    void initChatForm();
    void linkSignalWithSlot();
    void saveHistoryMessage();//保存历史消息
    void readHistoryMessage();//读取历史消息




private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();
    void pb_send_clicked();
    // 聊天历史记录
    void onClickBtnHistory(bool checked);

signals:
    void sendMessagesFromChat(TalkMessage &); //点击发送按钮后将发送的消息作为参数释放出去
    //退出信号 closerEvent()中会发出该信号
    void roomQuitSignal();


};

#endif // CHATFORM_H
