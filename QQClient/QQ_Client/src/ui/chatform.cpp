#include "chatform.h"
#include "ui_chatform.h"
#include <QDebug>


ChatForm::ChatForm(const ChatInformation &chatInf, QWidget *parent) :
    MoveableFramelessWindow(parent),m_chatInfor(chatInf),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);


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
    //待完成 2018.09.05
}

QWidget *ChatForm::getDragnWidget()
{
    return ui->w_top;
}


//void ChatForm::pb_send_clicked()
//{
//    sendMessage(Message);
//}

void ChatForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}

void ChatForm::on_PB_shutdown_clicked()
{

    this->deleteLater();
}


