#include "chatform.h"
#include "ui_chatform.h"
#include <QDebug>


ChatForm::ChatForm(const ChatInformation &chatInf, QWidget *parent) :
    MoveableFramelessWindow(parent),m_chatInfor(chatInf),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);

    initChatForm();
    linkSignalWithSlot();

}

ChatForm::~ChatForm()
{
    delete ui;
}

/*************************************************
Function Name： initChatForm()
Description:  初始化主界面
*************************************************/
void ChatForm::initChatForm()
{
    //设置头像及昵称
    QString str = QString(":/media/person/media/person/%1.jpg").
        arg(QString::number(m_chatInfor.m_headPortrait));
    QString name;
    if(m_chatInfor.m_friendRemark.isEmpty()) //备注为空
        name = m_chatInfor.m_friendNickname;
    else
        name = m_chatInfor.m_friendRemark;

    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_BIG_SIZE,HEAD_BIG_SIZE)); //设置图片大小为42*42
    ui->label_head->setPixmap(pixmap);
    ui->pb_nickName->setText(name);
}

/*************************************************
Function Name： linkSignalWithSlot()
Description:  连接信号与槽
*************************************************/
void ChatForm::linkSignalWithSlot(){
    connect(ui->pb_minimize,SIGNAL(pressed()),this,SLOT(on_PB_minimize_clicked()));
    connect(ui->pb_shutdown,SIGNAL(pressed()),this,SLOT(on_PB_shutdown_clicked()));
    connect(ui->pb_send,SIGNAL(pressed()),this,SLOT(pb_send_clicked()));
}

QWidget *ChatForm::getDragnWidget()
{
    return ui->w_top;
}


/*************************************************
Function Name： closeEvent()
Description:  重载关闭事件
*************************************************/
void ChatForm::closeEvent(QCloseEvent *event)
{
//    if (m_fileSender != 0)
//    {
//        if (!m_fileSender->isStopped())
//        {
//            QString temp = tr("文件还在发送中，您确定想要关闭聊天窗口？");
//            QMessageBox::StandardButton rb;
//            rb = QMessageBox::question(this, tr("关闭聊天"), temp,
//                QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
//            if(rb == QMessageBox::No)
//            {
//                event->ignore();
//                return;
//            }
//        }
//    }

    //向主界面发送退出信号
    emit roomQuitSignal();
    saveHistoryMessage();

    event->accept();
}

/*************************************************
Function Name： saveHistoryMessage()
Description:  保存历史记录
*************************************************/
void ChatForm::saveHistoryMessage()
{
    //待完成 2018.09.06
//    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
//    filePath.append(m_chatInfor.m_myID);
//    QString fileName = QString("%1_%2_friend.imres")
//            .arg(m_chatInfor.m_myID, m_chatInfor.m_friendID);

    //IMClientFileCtrl::saveTalkHistory(filePath, fileName, m_tbMessageShow);
}

void ChatForm::pb_send_clicked()
{
    if(ui->textEdit_input->toPlainText().isEmpty())
        return;
    // 获取信息输入框的信息，并且更新信息输入框
    QString sendString = ui->textEdit_input->toHtml();
    ui->textEdit_input->clear();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=green>%1    %2: </font>%3")
            .arg("我").arg(dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(sendString);
    ui->textBrowser_show->append(temp);

    m_mes.m_text = sendString;
    m_mes.m_type = TALK_MESSAGE;
    m_mes.m_receiverID = m_chatInfor.m_friendID;
    m_mes.m_dateTime = dateTime;

    emit sendMessagesFromChat(m_mes);
}

void ChatForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}

void ChatForm::on_PB_shutdown_clicked()
{
    this->close();
    //this->deleteLater(); //在mainform会通过容器保存的该指针来deleteLater()
}


/*************************************************
Function Name： appendMessageShow()
Description:  将好友发来的信息添加到显示窗口
*************************************************/
void ChatForm::appendMessageShow(const TalkMessage &mes)
{
    QString  name;
    if(m_chatInfor.m_friendRemark.isEmpty())
        name = m_chatInfor.m_friendNickname;
    else
        name = m_chatInfor.m_friendRemark;

    //将（收到的）信息显示在输出栏
    QString temp = QString("<font size=\"FONT_SIEZE\" color=blue>%1    %2: </font>%3")
        .arg(name).arg(mes.m_dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(mes.m_text);
    ui->textBrowser_show->append(temp);
}
