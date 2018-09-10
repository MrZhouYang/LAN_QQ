#include "qqlatestmessagelistwidget.h"

QQLatestMessageListWidget::QQLatestMessageListWidget(MainForm *mainWidget, QWidget *parent) :
    QWidget(parent), m_layout(new QVBoxLayout), m_mainWidget(mainWidget)
{
    m_mesCounter = 0;
    if(NULL == m_mainWidget)
        return;
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    m_contentsWidget = new QWidget;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_contentsWidget->setLayout(m_layout);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setAlignment(Qt::AlignLeft);
    m_scrollArea->setWidget(m_contentsWidget);

    mainLayout->addWidget(m_scrollArea);
    setLayout(mainLayout);
    setStyleSheet("QWidget{border: 0;}");

    //创建右键菜单
    //creatMenu();
}

/*************************************************
Function Name： addItem()
Description:  添加
*************************************************/
void QQLatestMessageListWidget::addItem(QWidget *item){
    // Remove last spacer item if present.
    int count = m_layout->count();
    if(count>1){
        m_layout->removeItem(m_layout->itemAt(count-1));
    }

    // Add item and make sure it stretches the remaining space.
    m_layout->addWidget(item);
    m_layout->addStretch(1);

    emit timerStatus(true);
}

/*************************************************
Function Name： removeItem()
Description:  删除
*************************************************/
void QQLatestMessageListWidget::removeItem(QWidget *item){
    m_layout->removeWidget(item);

    if(m_layout->count() ==1){
        m_layout->removeItem(m_layout->itemAt(0));
        emit timerStatus(false);
    }
}

/*************************************************
Function Name： size()
Description:  返回消息item的数目
*************************************************/
int QQLatestMessageListWidget::size(){
    m_mesCounter = m_layout->count();
    if(m_mesCounter>1)
            --m_mesCounter;
    return m_mesCounter;
}




