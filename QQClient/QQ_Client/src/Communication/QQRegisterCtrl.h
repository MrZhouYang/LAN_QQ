/*********************************************
File Name： QQRegisterCtrl.h
Description： 用于控制注册的类
Changes：
********************************************/

#ifndef QQREGISTERCTRL_H
#define QQREGISTERCTRL_H

#include <QObject>
#include "qqConstant.h"
#include "QQTcpSocket.h"
#include <QMessageBox>

/*************************************************
Class Name： QQRegisterCtrl
Description: 用于控制注册的类
*************************************************/
class QQRegisterCtrl : public QObject
{
    Q_OBJECT
public:
    explicit QQRegisterCtrl(QObject *parent = 0);

    ~QQRegisterCtrl();
    // 注册账号 registerdialog点击确定后会调用该函数
    void registerAccount(const UserInformation &);
    
signals:
    //该信号与registerdialog的槽函数关联，用于设置确定按钮的状态
    void signalResetBtnRegister(bool );
public slots:

private slots:
    // 请求注册 与QQTcpSocket::connected()信号关联
    void requestRegister();
    // 读取信息 与QQTcpSocket::readyRead()信号关联
    void readMessage();
    // 重置按钮 与QQTcpSocket 的出错信号 disconnected()信号关联
    void resetBtnRegister();
private:
    
private:
    UserInformation m_user;
    quint16 m_blockSize;
    QQTcpSocket *m_tcpSocket;

};

#endif // QQREGISTERCTRL_H
