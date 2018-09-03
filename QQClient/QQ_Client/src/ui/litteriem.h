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


class MainForm;

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

    // 设置显示信息
    void setItemStatus();

    FriendInformation getInformation() const
    {	return m_info;	}

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::LitterIem *ui;

    FriendInformation m_info;
    MainForm *m_mainWidget;
    QList<QString> *m_groupList;
    //以字符串形式储存用户状态信息
    QString m_strStatus;

//    ChatForm *chatform_p;
    // 将用户状态从数字形式转换为字符串形式
    QString getStatusFromInt(const int n) const;


signals:
    void wake_message_to(int port, QString showname);
};

#endif // LITTERIEM_H
