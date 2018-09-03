/*********************************************
File Name： QQTcpSocket.h
Description： 客户端tcpsocket类
Changes：
********************************************/

#ifndef QQTCPSOCKET_H
#define QQTCPSOCKET_H

#include <QTcpSocket>
#include "qqConstant.h"
#include <QMessageBox>
#include <QtNetwork>

/*************************************************
Class Name： QQTcpSocket
Description: 客户端tcpsocket类
*************************************************/
class QQTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    QQTcpSocket(QObject *parent = 0);
    // 请求连接
    void requestConnect();
    // 是否连接
    bool isConnected();

    void setFlag(int);
    int flag();

    // 获取ip
    static QString getIP();
    //获取当前的日期和时间
    static QString getCurrentDateTime();

    static QHostAddress s_hostAddress;
    static int s_hostPort;

signals:
    void showConnectionStatus(const QString &, bool isLogin = false);

private slots:
    // 连接被客户端关闭
    void connectionClosed();
    // 连接创建
    void connectionCreate();
    // 显示错误
    void dispalyError(QAbstractSocket::SocketError);

private:
    // 链接信号与槽
    void linkSignalWithSlot();


    bool m_isConnected;

    int m_flag;//修改密码成功时会将m_flag置1

};

#endif // QQTCPSOCKET_H
