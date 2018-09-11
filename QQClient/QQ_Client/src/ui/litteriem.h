/*********************************************
File Name： litteriem.h
Author： stormZhou
Date： 2018.06.11
Description： 单个好友项目
Changes：
********************************************/
#ifndef LITTERIEM_H
#define LITTERIEM_H

#include <QWidget>
#include "chatform.h"
#include "qqConstant.h"
#include <QMessageBox>
#include <QMouseEvent>
#include "mainform.h"


class MainForm;
class ChatForm;

namespace Ui {
class LitterIem;
}

class LitterIem : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief LitterIem
     * @param info 用户信息结构体
     * @param groupList 目前的分组名列表，保存了所有的分组选项卡名
     * @param mainWidget 拥有这个好友的主界面指针
     */
    explicit LitterIem(const FriendInformation &info, QList<QString> *groupList, MainForm *mainWidget, QWidget *parent = 0);
    ~LitterIem(); 


    FriendInformation &getInformation()
    {	return m_info;	}
    FriendInformation getInformation() const
    {	return m_info;	}

    ChatForm *getRoomPoint() const
    {
        return m_chatForm;
    }
    bool isRoomOpen() const
    {
        return m_isOpen;
    }
    bool isRoomShow() const
    {
        return m_isShow;
    }
    void setChangedInformation(const FriendInformation & fri)
    {
        if (m_info.m_userID != fri.m_userID)
            return;
        m_info.m_headPortrait = fri.m_headPortrait;
        m_info.m_nickname = fri.m_nickname;
//        m_info.m_status = fri.m_status;
    }

    // 创建聊天窗口
    void openChatRoom();
    // 显示聊天窗口
    void showChatRoom();
    // 关闭聊天窗口
    void closeChatRoom();
    // 刷新菜单中分组信息
    void refreshMoveMenu();
    // 设置item显示信息
    void setItemStatus();


protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::LitterIem *ui;

    FriendInformation m_info;
    MainForm *m_mainWidget;
    QList<QString> *m_groupList;
    //以字符串形式储存用户状态信息
    QString m_strStatus;
    ChatForm *m_chatForm;

    // 聊天窗口是否打开了
    bool m_isOpen;
    // 聊天窗口是否显示
    bool m_isShow;

    //右键菜单
    QMenu *m_menu;
    QMenu *m_moveFriendMenu;

//    ChatForm *chatform_p;
    // 将用户状态从数字形式转换为字符串形式
    QString getStatusFromInt(const int n) const;

private slots:
    //聊天窗口关闭了
    void chatRoomQuit();

public slots:
    // 移动好友至其他分组
    void onClickMove();

signals:
    void wake_message_to(int port, QString showname);
};

#endif // LITTERIEM_H
