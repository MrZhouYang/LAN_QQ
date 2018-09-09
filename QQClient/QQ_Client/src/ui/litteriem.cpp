#include "litteriem.h"
#include "ui_litteriem.h"
#include <QDebug>

#include <QPixmap>

LitterIem::LitterIem(const FriendInformation &info, QList<QString> *groupList, MainForm *mainWidget, QWidget *parent):
    QWidget(parent),m_info(info),m_mainWidget(mainWidget),m_groupList(groupList),m_isOpen(false),m_isShow(false),
    ui(new Ui::LitterIem)
{
    ui->setupUi(this);
    setItemStatus();
}

LitterIem::~LitterIem()
{

    delete ui;
}

/*************************************************
Function Name： mouseDoubleClickEvent
Description: 鼠标双击事件
*************************************************/
void LitterIem::mouseDoubleClickEvent(QMouseEvent *event){   
    if(event->button()==Qt::LeftButton){
        qDebug() << "鼠标左键双击";
        openChatRoom();
        showChatRoom();
        //待完成 2018.09.07
        m_mainWidget->removeLinkButton(m_info.m_userID);
        return;
    }
    QWidget::mouseDoubleClickEvent(event);
}

/*************************************************
Function Name： setItemStatus()
Description:  设置显示信息
*************************************************/
void LitterIem::setItemStatus()
{
    //获取头像地址
    QString picPath = QString(":/media/person/media/person/%1.jpg")
                   .arg(QString::number(m_info.m_headPortrait));
    //获取用户当前在线状态
    m_strStatus = getStatusFromInt(m_info.m_status);
    QString text,mark;
    if(m_info.m_remarkName.isEmpty())
        mark = m_info.m_nickname; //如果没有备注名，则保存昵称
    else
        mark = m_info.m_remarkName; //有备注名，则保存备注名
    if(OFFLINE == m_info.m_status || INVISIBLE == m_info.m_status)
    {
        QPixmap pixmap;
        QIcon icon(picPath);
        //获取用户离线时的灰色头像图片
        pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE),
                             QIcon::Disabled, QIcon::On);
        ui->label_pic->setPixmap(pixmap);

        //设置用户离线时候显示的字符串 html
        text = QString("<font color=gray>%1(%2)<br>[%3]</font>").
                arg(m_info.m_userID).arg(mark).arg(m_strStatus);
    }
    else
    {
        //用户在线时的图片和字符串
        ui->label_pic->setPixmap(QPixmap(picPath));
        text = QString("<font color=green>%1(%2)<br>[%3]</font>").
                arg(m_info.m_userID).arg(mark).arg(m_strStatus);
    }
    ui->label_name->setText(text);
}

QString LitterIem::getStatusFromInt(const int n) const{
    //    ONLINE = 0,    // 在线
    //    INVISIBLE = 1, // 隐身
    //    BUSY = 2,      // 忙碌
    //    LEAVE = 3,     // 离开
    //    NOTDISTURB = 4 // 请勿打扰
        switch (n)
        {
        case ONLINE:
            return tr("在线");
            break;
        case OFFLINE:
        case INVISIBLE:
            return tr("离线");
            break;
        case BUSY:
            return tr("忙碌");
            break;
        case LEAVE:
            return tr("离开");
            break;
        case NOTDISTURB:
            return tr("请勿打扰");
            break;
        default:
            break;
        }
        return NULL;
}

/*************************************************
Function Name： openChatRoom()
Description: 打开聊天窗口
*************************************************/
void LitterIem::openChatRoom(){
    if(m_isOpen)
        return;
    ChatInformation chatInf;
    chatInf.m_myID = m_mainWidget->getLocalMyInformation().m_userID;
    chatInf.m_headPortrait = m_info.m_headPortrait;
    chatInf.m_friendID = m_info.m_userID;
    chatInf.m_friendNickname = m_info.m_nickname;
    chatInf.m_friendRemark = m_info.m_remarkName;
    chatInf.m_friendStatus = m_info.m_status;

    m_isOpen = true;
    m_chatForm = new ChatForm(chatInf);
    m_mainWidget->insertChatRoomMap(chatInf.m_friendID,m_chatForm);
    connect(m_chatForm,SIGNAL(sendMessagesFromChat(TalkMessage&)),m_mainWidget,SLOT(ChatFormSendMessage(TalkMessage&)));
    connect(m_chatForm,SIGNAL(roomQuitSignal()),this,SLOT(chatRoomQuit()));
}

/*************************************************
Function Name： showChatRoom()
Description: 显示聊天窗口
*************************************************/
void LitterIem::showChatRoom()
{
    m_chatForm->raise();
    m_chatForm->activateWindow();
    m_chatForm->show();
    m_isShow = true;
}

/*************************************************
Function Name： chatRoomQuit()
Description: 聊天室被关闭
*************************************************/
void LitterIem::chatRoomQuit()
{
    m_isOpen = false;
    m_isShow = false;
    if (NULL != m_mainWidget)
        m_mainWidget->removeChatWidget(m_info.m_userID);
}
