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

namespace Ui {
class ChatForm;
}

class ChatForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit ChatForm(QString ChatName,QString senderName,int port,QWidget *parent = 0);
    ~ChatForm();

    inline QString Get_chatname(){
        return m_chatname;
    }

protected:
      QWidget*getDragnWidget();

private:
    Ui::ChatForm *ui;

    QString m_chatname;
    QString m_sendername;
    int m_port_number;
//    QUdpSocket *m_udpSocket;

    /**
    * @brief UDP发送函数
    * @param type 发送消息类型
    * @return
    */
    //void sendMessage( MessageType type );

    /**
    * @brief 从数据库中获取需要绑定的IP
    * @param 账号昵称
    * @return ip地址
    */
//    int get_bind_port( QString Name );

private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();

    /**
    * @brief UDP接受函数
    */
//    void processPendingDatagrams();
//    void pb_send_clicked();

signals:
    /**
    * @brief 该窗口关闭时发出该信号
    */
//    void destroy_chatname(QString name);

};

#endif // CHATFORM_H
