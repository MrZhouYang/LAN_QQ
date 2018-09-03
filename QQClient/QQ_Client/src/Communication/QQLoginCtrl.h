/*********************************************
File Name： QQLoginCtrl.h
Description： 用于控制登录的类
Changes：
********************************************/

#ifndef IMLOGINCTRL_H
#define IMLOGINCTRL_H

#include <QObject>
#include "QQTcpSocket.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QDataStream>
#include <QDateTime>
#include <QtNetwork>
#include <QInputDialog>
#include "qqConstant.h"
#include "IMEncryption.h"


/*************************************************
Class Name： QQLoginCtrl
Description: 用于控制登录的类
*************************************************/
class QQLoginCtrl : public QObject
{
    Q_OBJECT
public:
    explicit QQLoginCtrl(QObject *parent = 0);

    ~QQLoginCtrl();

    // 发送登录信息
    void login(const QString &id ,const QString & pwd = "",
                     const int status = ONLINE);
    // 获取密保信息
    void getQuestionAndAnswer(const QString &id);

signals:
    void getLoginMessgae(const QString &, bool isLogin = false,
                         const UserInformation * me = 0);
    void getQuestionAndAnswerSuccess(const TempStrings & tmpStr);

public slots:
    // 改变登录信息
    void changeLoginMessage(const QString &mes, bool isLogin);


private slots:
    // 发送获取密保问题以及答案的请求
    void requestGetQuestionAndAnswer();
    // 发送登录请求
    void requestLogin();

    // 发送请求
    void sendRequest();

    // 读取信息
    void readMessage();

private:

private:
    int m_kind;
    quint16 m_blockSize;
    QQTcpSocket *m_tcpSocket;
    LoginInformation m_loginInfo;
    UserInformation m_myself;
    TempStrings m_tempStr;
    QString m_id;
};

#endif // IMLOGINCTRL_H
