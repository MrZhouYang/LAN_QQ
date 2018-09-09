/*********************************************
File Name： qqlinkbutton.h
Author： StormZhou
Description： 新消息提示item的基类
********************************************/
#ifndef QQLINKBUTTON_H
#define QQLINKBUTTON_H

#include <QPushButton>
#include "qqConstant.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class QLabel;

class QQLinkButton : public QPushButton
{
    Q_OBJECT
public:
    QQLinkButton(QWidget *parent = 0);
    virtual ~QQLinkButton(){} //纯虚函数，子类需要实现自己的析构函数

    void setLatestMessage(const TalkMessage & mes);

    // 设置button显示信息
    virtual void setButtonStatus() = 0; //纯虚函数，子类需要自己实现

signals:
    void deleteLinkButton(const QString & id);


public slots:
    // 左键 双击
    virtual void onDoubleClickButton() = 0; //纯虚函数，子类需要自己实现
    // 右键点击按键
    virtual void onClickRightButton(/*const QPoint &*/);
    // 忽略消息
    virtual void ignoreMessage() = 0; //纯虚函数，子类需要自己实现

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);

protected:
    QLabel *m_labelHead; //显示头像
    QLabel *m_labelInfo; //显示消息来源信息
    QLabel *m_labelMes;  //显示新消息内容

    // 右键菜单
    QMenu *m_menu;

private:
    // 创建右键菜单
    void creatMenu(/*const QList<QString> *groutList*/);
};

#endif // QQLINKBUTTON_H
