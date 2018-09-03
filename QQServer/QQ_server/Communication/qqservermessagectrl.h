#ifndef QQSERVERMESSAGECTRL_H
#define QQSERVERMESSAGECTRL_H

#include <QObject>
#include <QMessageBox>
#include <QDateTime>
#include <QStringListModel>
#include <QListView>
#include <QStringList>

#include "Database/qqdatabasectrl.h"
#include "qqtcpserver.h"
#include "qqclientsocketctrl.h"

class QQServerMessageCtrl : public QObject
{
    Q_OBJECT
public:
    explicit QQServerMessageCtrl(QObject *parent = 0);
    ~QQServerMessageCtrl();

    void runServer(); // 用于启动服务器
    QListView *getIDListView(); //获取ID listiew
    QListView *getAddressListView(); //获取Address listiew


signals:

public slots:

private slots:
    void insertIDData(const QString &id);//插入ID数据
    void deleteIDData(const QString &id);//删除ID数据

    void insertAddressData(const QString &address);//插入Address数据
    void deleteAddressData(const QString &address);//删除Address数据

private:
    QQTcpServer *m_tcpServer; //继承自QTcpServer
    QQDatabaseCtrl m_databaseCtrl;

    QStringList m_listID; //用于保存登录用户的ID
    QStringListModel *m_modelID;
    QListView *m_listViewID;

    QStringList m_listAddress; //用于保存登录用户的Address
    QStringListModel *m_modelAddress;
    QListView *m_listViewAddress;
};

#endif // QQSERVERMESSAGECTRL_H
