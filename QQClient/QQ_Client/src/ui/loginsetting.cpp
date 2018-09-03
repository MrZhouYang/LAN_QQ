#include "loginsetting.h"
#include "ui_loginsetting.h"
#include "QDebug"
#include <QPushButton>

LoginSetting::LoginSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginSetting)
{
    ui->setupUi(this);

    connect(ui->pb_cancel,SIGNAL(pressed()),this,SLOT(PBcancel()));
    connect(ui->pb_sure,SIGNAL(pressed()),this,SLOT(PBsure()));
}

LoginSetting::~LoginSetting()
{
    delete ui;
}

void LoginSetting::PBcancel(){
    this->deleteLater();
}

void LoginSetting::PBsure(){
    QString IP;
    int port;
    if(ui->LE_IP->text().isEmpty()){
        IP = "127.0.0.1";
    }else{
        IP = ui->LE_IP->text();
    }

    if(ui->LE_Port->text().isEmpty()){
        port = 1234;
    }else{
        port = ui->LE_Port->text().toInt();
    }

    emit server_setting(IP,port);
    QMessageBox::information(this,tr("提示"),tr("修改服务器信息成功!"));

}
