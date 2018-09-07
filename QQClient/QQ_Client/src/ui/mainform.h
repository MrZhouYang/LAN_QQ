#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QVBoxLayout>
#include "collapseview.h"
#include "colorpickform.h"
#include <QtNetwork>
#include <QByteArray>
#include <QDataStream>
#include "chatform.h"
#include "litteriem.h"
#include "qqConstant.h"
#include "qqdatabasectrl.h"
#include "qqmainctrl.h"
#include "collapseviewitem.h"

class QQMainCtrl;
class LitterIem;
class ChatForm;

namespace Ui {
class MainForm;
}

class MainForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit MainForm( const UserInformation me, QWidget *parent = 0);
    ~MainForm();

//    QQMainCtrl * getMainCtrl() const
//    {
//        return m_mainCtrl;
//    }

    UserInformation getLocalMyInformation() const;

    bool isMyFriend(const QString &id) const;

    // 获取好友信息（发送至服务器）
    void getFriendInformation(const QString &id);
    // 改变自己信息（发送至服务器）
    void changeMyInformation(const UserInformation &);
    // 改变好友备注（发送至服务器）
    void changeFriendRemark(const QString &, const QString &);
    // 删除好友（发送至服务器）
    void deleteFriend(const QString &);
    // 删除存储于m_informationMap中的信息窗口
    void removeInformationWidget(const QString &);
    // 添加好友（发送至服务器）
    void addFriend(const QString friendID);
    // 移动好友至其他分组
    void moveFriendToBox(const QString & friendID, const QString & groupName, const QString &title);
    // 获取某个分组里所有好友的备注名列表
    QStringList getGroupFriendList(const QString & groupName);
    // 设置在线人数
    void setOnlineCounter(int num);
    // 插入好友聊天界面
    void insertChatRoomMap(const QString &, ChatForm *);
    // 删除存储于m_chatRoomMap中的聊天窗口
    void removeChatWidget(const QString &);

public slots:
    // 设置好友列表
    void setFriendListWidget(const QVector<FriendInformation> &);
    // 添加好友按钮
    bool addFriendButton(const FriendInformation &);
    // 获取好友列表
    void getFriendsInformation();
    // 重命名分组成功
    void renameBoxSuccess(const QString & title, const QString & newTitle);
    // 获取好友发来的消息 //待完成 2018.09.06
    //void receiveFriendTalkMessage(const TalkMessage &);
    // 删除新消息连接按钮
    void removeLinkButton(const QString & id);

protected:
      QWidget*getDragnWidget();

private:
    Ui::MainForm *ui;


    QQMainCtrl *m_mainCtrl;
    UserInformation m_myself;
    int m_onlineCounter;//当前在线人数

    CollapseView *m_friendListWidget;//好友界面  用于保存好友列表选项卡
    QVBoxLayout *page4_layout;

    //数据库
    QQDatabaseCtrl m_datebase;

    QMap<QString,ChatForm *> m_chatRoomMap; // 好友ID 与 聊天室 映射表

    QMap<QString, LitterIem *> m_friendMap; // 好友帐号 与 好友按钮 映射表

    QStringList m_friendsGroupList;  // 分组名列表
    QStringList m_friendsMarkList; // 某分组中好友 备注名 列表
    QStringList m_friendsIDList; // 某分组中好友 ID  列表
    QMap<QString, int> m_indexFriendsGroupMap; // 组名 与 下标 映射表
    QVector<CollapseViewItem *> m_listItemsFriendsVec;  // 存储每个分组选项卡的向量

    int m_flag;

    void InitQQMainWidget();
    void linkSignalWithSlot();
    void InitMainWidget();

    //清空容器
    void clearContainers();
    void refreshFriendButtonMenu();



private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();
    void on_PB_p_pressed();
    void on_PB_q_pressed();
    void on_PB_t_pressed();

    void doChangeColor();
    void onThemeColorChange(QString colorStr);

    // 关闭主窗口
    void closeWindow();
    // 关闭所有别的窗口
    void closeAllWindows();
    // 删除该好友分组
    void removeBox(const QString &);
    // 重命名该好友组
    void renameBox(const QString &);
    // 好友聊天窗口发送消息
    void ChatFormSendMessage(TalkMessage &);


};

#endif // MAINFORM_H
