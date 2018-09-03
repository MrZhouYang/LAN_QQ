#include "chatform.h"
#include "ui_chatform.h"
#include <QDebug>

ChatForm::ChatForm(QString ChatName, QString senderName, int port, QWidget *parent) :
    MoveableFramelessWindow(parent),m_chatname(ChatName),m_sendername(senderName),m_port_number(port),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);

    //qDebug() << "m_port_number:"<<m_port_number;

    ui->pb_nickName->setText(ChatName);

    //udp相关
//    m_udpSocket = new QUdpSocket(this);
//    qDebug() << "udp套接字绑定端口："<<get_bind_port(senderName);
//    m_udpSocket->bind(get_bind_port(senderName),QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
//    connect(m_udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()) );
//    connect(ui->pb_send,SIGNAL(clicked()),this,SLOT(pb_send_clicked()));


//    connect(ui->pb_minimize,SIGNAL(pressed()),this,SLOT(on_PB_minimize_clicked()));
//    connect(ui->pb_shutdown,SIGNAL(pressed()),this,SLOT(on_PB_shutdown_clicked()));
}

ChatForm::~ChatForm()
{
    delete ui;
}

QWidget *ChatForm::getDragnWidget()
{
    return ui->w_top;
}

//void ChatForm::sendMessage(MessageType type)
//{
//    QByteArray data;
//    QDataStream out(&data, QIODevice::WriteOnly);
//    out << type;

//    switch (type) {
//    case Message:
//        if(ui->textEdit_input->toPlainText() == ""){
//            QMessageBox::information(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
//            return;
//        }
//        QString msg = ui->textEdit_input->toHtml();
//        qDebug() << "UDP发送消息:"<<msg;
//        ui->textEdit_input->clear();
//        ui->textEdit_input->setFocus();
//        out<< m_sendername<<msg;
//        ui->textBrowser_show->verticalScrollBar()->setValue( ui->textBrowser_show->verticalScrollBar()->maximum() );
//        //自己发送的信息也在窗口显示出来
//        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//        ui->textBrowser_show->setTextColor(Qt::green);
//        ui->textBrowser_show->setCurrentFont(QFont("Times New Roman",12));
//        ui->textBrowser_show->append( "["+m_sendername+"]"+time );
//        ui->textBrowser_show->append(msg);
//        break;
//    }
//    m_udpSocket->writeDatagram(data.data(),data.size(),QHostAddress::Broadcast,m_port_number);
//    //m_udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,m_port_number);
//}

//void ChatForm::processPendingDatagrams(){
//    while(m_udpSocket->hasPendingDatagrams()){
//        QByteArray datagram;
//        datagram.resize(m_udpSocket->pendingDatagramSize());
//        m_udpSocket->readDatagram(datagram.data(),datagram.size());
//        QDataStream in(&datagram,QIODevice::ReadOnly);
//        int Type;
//        in >> Type;
//        qDebug() <<"接受到的dup信息类型:"<< Type;
//        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

//        switch (Type) {
//        case Message:
//            QString message,sendername;
//            in>>sendername>>message;
//            qDebug() <<"udp从用户:"<< sendername<<"来";
//            qDebug()<<"该用户发送了:"<<message;
//            ui->textBrowser_show->setTextColor(Qt::blue);
//            ui->textBrowser_show->setCurrentFont(QFont("Times New Roman",12));
//            ui->textBrowser_show->append( "["+sendername+"]"+time );
//            ui->textBrowser_show->append(message);
//            break;
//        }
//    }
//}

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
    //emit destroy_chatname(m_chatname);
    this->deleteLater();
}

//int ChatForm::get_bind_port(QString Name){
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection6");
//    db.setDatabaseName("D:/MyQTCode(Win32)/test/sqlmodel/RegisteredInfo.db");
//    int ip = 0;

//    bool ok = db.open();
//    qDebug() << "数据库打开"<<ok;

//    QSqlQuery query(db);
//    QString sql_str = QString("SELECT * FROM user WHERE nickName='%1'").arg(Name);
//    query.exec(sql_str);
//    while(query.next()){
//        ip = query.value("grade").toInt();
//    }
//    db.close();

//    return ip;
//}
