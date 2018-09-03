/*********************************************
File Name： collapseview.h
Author： stormZhou
Date： 2018.06.10
Description： 好友界面
Changes：
********************************************/
#ifndef COLLAPSEVIEW_H
#define COLLAPSEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "collapseviewitem.h"
#include <QSpacerItem>
#include <QScrollArea>


class MainForm;


class CollapseView : public QWidget
{
    Q_OBJECT

public:
    explicit CollapseView(MainForm *mainWidget,QWidget *parent = 0);
    ~CollapseView();

    //为好友界面添加好友列表选项卡
    void addItem(QWidget *item);


private slots:


private:
    QVBoxLayout *m_layout;
    MainForm *m_mainWidget;
    QScrollArea *m_friendsScrollArea;
    QWidget *m_contentsWidget;

//    QSpacerItem *m_spacer;
//    QList<QWidget *> m_viewitemlist;

};

#endif // COLLAPSEVIEW_H
