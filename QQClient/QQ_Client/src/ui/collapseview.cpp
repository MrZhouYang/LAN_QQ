#include "collapseview.h"


#include <QDebug>


CollapseView::CollapseView(MainForm *mainWidget, QWidget *parent) :
    QWidget(parent),m_mainWidget(mainWidget),m_layout(new QVBoxLayout)
{
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    m_contentsWidget = new QWidget;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_contentsWidget->setLayout(m_layout);

    m_friendsScrollArea = new QScrollArea(this);
    m_friendsScrollArea->setWidgetResizable(true);
    m_friendsScrollArea->setAlignment(Qt::AlignLeft);
    m_friendsScrollArea->setWidget(m_contentsWidget);

    mainLayout->addWidget(m_friendsScrollArea);
    setLayout(mainLayout);

    setStyleSheet("QWidget{border: 0;}");

    //creatMenu(); //创建右键菜单
}

CollapseView::~CollapseView()
{

}

//为好友界面添加好友列表选项卡
void CollapseView::addItem(QWidget *item)
{
    // Remove last spacer item if present.
    int count = m_layout->count();
    //qDebug()<<"CollapseView::addItem count="<<count;
    if (count > 1)
    {
        m_layout->removeItem(m_layout->itemAt(count - 1));
    }

    // Add item and make sure it stretches the remaining space.
    m_layout->addWidget(item);
    m_layout->addStretch(1);//如果不添加这个，CollapseViewItem的高度会太大
}

