/*********************************************
File Name： qqlatestmessagelistwidget.h
Author： StormZhou
Description： tabwidget中显示最近消息的窗口
********************************************/
#ifndef QQLATESTMESSAGELISTWIDGET_H
#define QQLATESTMESSAGELISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenu>
#include "mainform.h"
#include <QDebug>
#include <QMouseEvent>

class QQLatestMessageListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQLatestMessageListWidget(MainForm *mainWidget, QWidget *parent = 0);
    void addItem(QWidget *item);
    void removeItem(QWidget *item);
    int size();
    //创建右键菜单
    //void creatMenu(); //创建右键菜单

signals:
    void timerStatus(bool isOpen); //该信号控制是否新消息提示闪烁 true表示闪烁

public slots:
    //void showMenu(); //显示右键菜单
protected:
    //void mousePressEvent(QMouseEvent *e);

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_scrollArea;

    //右键菜单
    //QMenu *m_menu;

    MainForm *m_mainWidget;

    int m_mesCounter; //保存消息item的数目
};

#endif // QQLATESTMESSAGELISTWIDGET_H
