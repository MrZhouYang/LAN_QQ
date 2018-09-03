#ifndef QQCLIENTSOCKETCTRL_H
#define QQCLIENTSOCKETCTRL_H

#include <QTcpSocket>
#include "Database/qqdatabasectrl.h"
#include "qqConstant.h"
#include <QDateTime>
#include "qquser.h"
#include <QMultiMap>



/*************************************************
Class Name： IMClientSocketCtrl
Description: 与客户端通信建立起来的QTcpSocket套接字
*************************************************/
class QQClientSocketCtrl : public QTcpSocket
{
    Q_OBJECT
public:
    QQClientSocketCtrl(QObject *parent = 0);
    ~QQClientSocketCtrl();

signals:
    // 将接收到的内容通作为参数,通过信号发给qqtcpserver类的槽函数处理
    void sendSignal(const SaveTmpInformation &temp);
    // 用户登录
    void userLoginSignal(const UserInformation &user);
    //用户断开连接了 信号发给qqtcpserver类的槽函数处理
    void deleteSignal(const QString &acc);

public slots:
    // 接收信息
    void receiveMessage();
    // 发送信息 会被qqtcpserver类的槽函数调用向client回送消息
    void sendMessage(const SaveTmpInformation &temp);
    // 删除socket
    void deleteScoket();

private:
    quint16 m_blockSize;
    SaveTmpInformation m_save;
    QQDatabaseCtrl m_database;
};

#endif // QQCLIENTSOCKETCTRL_H
