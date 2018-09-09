/*********************************************
File Name： qqlinkfriendbutton.h
Author： StormZhou
Description： 好友新消息提示item
********************************************/
#ifndef QQLINKFRIENDBUTTON_H
#define QQLINKFRIENDBUTTON_H

#include <QPushButton>
#include "qqlinkbutton.h"
#include "qqConstant.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include "litteriem.h"

class QLabel;
class LitterIem;

class QQLinkFriendButton : public QQLinkButton
{
    Q_OBJECT
public:
    explicit QQLinkFriendButton(LitterIem *item,QWidget *parent = 0);
    ~QQLinkFriendButton();


    // 设置button显示信息
    void setButtonStatus();

public slots:
    // 左键 双击
    void onDoubleClickButton();
    // 忽略消息
    void ignoreMessage();


private:
    LitterIem *m_friendBtn; //对应的好友项
    FriendInformation m_info;
};

#endif // QQLINKFRIENDBUTTON_H
