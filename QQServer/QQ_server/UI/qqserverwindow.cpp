#include "qqserverwindow.h"
#include "ui_qqserverwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QListView>


QQServerwindow::QQServerwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQServerwindow)
{
    ui->setupUi(this);
    
    m_serverCtrl = new QQServerMessageCtrl(this);
    m_serverCtrl->runServer(); //启动服务器

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(m_serverCtrl->getIDListView());
    viewLayout->addWidget(m_serverCtrl->getAddressListView());

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *labelTitle = new QLabel(tr("连接服务器用户帐号列表:"));
    layout->addWidget(labelTitle);
    layout->addLayout(viewLayout);

    setLayout(layout);
}

QQServerwindow::~QQServerwindow()
{
    delete ui;
}
