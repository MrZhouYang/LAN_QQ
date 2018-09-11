#include "qqlinkbutton.h"

QQLinkButton::QQLinkButton(QWidget *parent):
    QPushButton(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    m_labelHead = new QLabel;
    m_labelHead->setMinimumSize(HEAD_BIG_SIZE, HEAD_BIG_SIZE);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setContentsMargins(6,6,0,6);
    rightLayout->setSpacing(0);
    m_labelInfo = new QLabel;
    m_labelMes = new QLabel;
    rightLayout->addWidget(m_labelInfo);
    rightLayout->addWidget(m_labelMes);

    mainLayout->addWidget(m_labelHead);
    mainLayout->addLayout(rightLayout);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(12,6,11,6);
    mainLayout->setSpacing(6);
    setLayout(mainLayout);
    //setMinimumSize(100,40);
    setMinimumHeight(60);

    m_menu = NULL;

    setStyleSheet("QPushButton{border: 0;}"
                  "QLable:hover{ background-color: rgb(252, 235, 172); }"
                  "QLabel #m_labelHead:hover{  }");
}

/*************************************************
Function Name： setLatestMessage()
Description:  设置最新消息
*************************************************/
void QQLinkButton::setLatestMessage(const TalkMessage & mes)
{
    m_labelMes->setText(mes.m_text);
}


/*************************************************
Function Name： onClickRightButton()
Description: 右键 单击
*************************************************/
void QQLinkButton::onClickRightButton(/*const QPoint &*/)
{
    if (m_menu == NULL)
    {
        //创建右键菜单
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}


//remark:protected:----------------------------------------

/*************************************************
Function Name： mousePressEvent
Description: 鼠标单击事件
*************************************************/
void QQLinkButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        onClickRightButton();
        return;
    }
    QPushButton::mousePressEvent(event);
}

/*************************************************
Function Name： mouseDoubleClickEvent
Description: 鼠标双击事件
*************************************************/
void QQLinkButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name： getStatusFromInt()
Description: 创建右键菜单
*************************************************/
void QQLinkButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *showMessage = new QAction(tr("查看消息"), m_menu);
    QAction *ignoreMessage = new QAction(tr("忽略消息"), m_menu);
    connect(showMessage, SIGNAL(triggered()),
            this, SLOT(onDoubleClickButton()));
    connect(ignoreMessage, SIGNAL(triggered()),
            this, SLOT(ignoreMessage()));

    m_menu->addAction(showMessage);
    m_menu->addAction(ignoreMessage);
}
