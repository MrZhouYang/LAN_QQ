/*********************************************
File Name： QQMainCtrl.h
Description： 用于控制主界面的类
********************************************/

#ifndef QQMAINCTRL_H
#define QQMAINCTRL_H

#include <QObject>
#include <QMultiMap>
#include <QVector>
#include "qqConstant.h"
#include "QQTcpSocket.h"
#include <QMessageBox>
#include "loginform.h"

class QQMainCtrl : public QObject
{
    Q_OBJECT
public:
    explicit QQMainCtrl(const QString myID, QObject *parent = 0);
    ~QQMainCtrl();

    // 关闭链接
    void closeConnect();

    // 获取所有好友列表信息
    void getFriendsInformation(const QString &, const int);

    // 获取好友详细信息
    void getFriendInformation(const QString &id);
    // 修改自己的信息
    void changeMyInformation(const UserInformation &me);
    // 修改好友备注
    void changeFriendRemark(const QString & myID,
                            const QString & friendID,
                            const QString &remark);
    // 删除好友
    void deleteFriend(const QString & myID, const QString & friendID);
    // 重命名分组
    void renameBox(const QString &, const QString &);

signals:
    void getFriendsSuccess(const QVector<FriendInformation> &);//case GET_ALL_FRIENDS_SUCCESS
    void getFriendInformationSuccess(const UserInformation &);//case GET_FRIEND_SUCCESS
    void getMyInformationSuccess(const UserInformation &);//case GET_MYSELF_SUCCESS
    void changeMyInformationSuccess(const UserInformation &);//case CHANGE_INFORMATION_SUCCESS
    void getFriendChangedStatus(const QString &, const int);//case CHANGE_STATUE
    void getFriendChangedInformation(const FriendInformation &);//case CHANGE_INFORMATION
    void changeFriendRemarkSuccess(const TempStrings &);//case CHANGE_REMARK_SUCCESS
    void deleteFriendSuccess(const QString &, const QString &, const QString &);//case DELETE_FRIEND_SUCCESS 和BE_DELETED
    void renameBoxSuccess(const QString &, const QString &);//case RENAME_BOX_SUCCESS
    void moveFriendToBoxSuccess(const QString &, const QString &, const QString);//case MOVE_FRIEND_BOX_SUCCESS
    void closeWindowSignal();//case CHANGE_PWD_SUCCESS m_tcpSocket::disconnected()时均会释放该信号


public slots:
    // 发送获取所有好友信息的请求
    void requestGetFriendsInformation();
    // 读取信息
    void readMessage();
    // 关闭程序
    void closeWindow();

    // 发送获取好友详细信息的请求
    void requestGetFriendInformation(const QString &);
    // 发送修改自己信息的请求
    void requestChangeMyInformation(const UserInformation &);
    // 发送修改好友备注的请求
    void requestChangeFriendRemark(const QString & myID,
                                   const QString & friendID,
                                   const QString &remark);
    // 发送删除好友的请求
    void requestDeleteFriend(const QString & myID, const QString & friendID);
    // 发送重命名分组的请求
    void requestRenameBox(const QString &, const QString &);

private:
    QString m_myID;

    QQTcpSocket *m_tcpSocket;
    quint16 m_blockSize;
    QString m_id;
    int m_status;

    QVector<FriendInformation> m_friendsVec; //用于保存每个好友的用户信息
    UserInformation m_friInf;//保存最近查询的单个好友的用户信息
    UserInformation m_myInf;//保存自己的用户信息

    QString m_peerID;
    int m_peerStatus;
    FriendInformation m_friSimInf;
    TempStrings m_tempStr;// 储存在各种小窗口中填写的信息
    QString m_groupName;

    QString m_title;
    QString m_newTitle;

};

#endif // QQMAINCTRL_H
