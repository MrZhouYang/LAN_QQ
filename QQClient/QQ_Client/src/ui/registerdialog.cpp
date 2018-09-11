#include "registerdialog.h"
#include "ui_registerdialog.h"


RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),m_regCtrl(nullptr),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->LE_Pwd->setEchoMode(QLineEdit::Password);
    setWindowTitle(tr("注册QQ帐号"));

    //设置默认连接服务器IP和port
    setServer(QString("127.0.0.1"),1234);

    connect(ui->PB_sure,SIGNAL(clicked()),this,SLOT(PB_sure_clicked()));
    connect(ui->PB_cancel,SIGNAL(clicked()),this,SLOT(PB_cancle_clicked()));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::PB_sure_clicked()
{
    // 判断昵称是否为空
    if (ui->LE_Nickname->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("昵称不能为空"));
        return;
    }
    // 判断密码是否为空
    if (ui->LE_Pwd->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("密码不能为空"));
        return;
    }
    // 判断密码是否符合要求
    if (ui->LE_Pwd->text().length()>14 || ui->LE_Pwd->text().length()<6)
    {
        QMessageBox::about(NULL, tr("提示"), tr("密码长度不符合"));
        return;
    }
    // 判断确认密码是否为空
    if (ui->LE_ConfirmPwd->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("请确认密码"));
        return;
    }
    // 判断密码是否一致
    if (ui->LE_Pwd->text().compare(ui->LE_ConfirmPwd->text()) != 0)
    {
        QMessageBox::about(NULL, tr("提示"), tr("密码不一致"));
        return;
    }
    // 判断性别是否为空
    if (ui->cbx_Sex->currentText().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("性别不能为空"));
        return;
    }
    // 判断生日是否为空
    if (ui->LE_Birthday->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("生日不能为空"));
        return;
    }
    // 判断密保问题是否为空
    if (ui->LE_Question->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("密保不能为空"));
        return;
    }
    // 判断问题答案是否为空
    if (ui->LE_Address->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("问题答案不能为空"));
        return;
    }

    m_userInf.m_nickname =  ui->LE_Nickname->text();
    m_userInf.m_password = IMEncryption::getInstace().
            getXorEncryptDecrypt(ui->LE_Pwd->text(), 10);
    m_userInf.m_sex = ui->cbx_Sex->currentText();
    m_userInf.m_birthday = ui->LE_Birthday->getDate();
    m_userInf.m_name = ui->LE_Name->text();
    m_userInf.m_phone = ui->LE_Phone->text();
    m_userInf.m_address= ui->LE_Address->text();
    m_userInf.m_question = ui->LE_Question->text();
    m_userInf.m_answer = ui->LE_Answer->text();

    if ( 0 == m_userInf.m_sex.compare("男"))
    {
        m_userInf.m_headPortrait = 4;
    }
    else
        m_userInf.m_headPortrait = 5;

    if (m_regCtrl == nullptr)
    {
        m_regCtrl = new QQRegisterCtrl;
        connect(m_regCtrl, SIGNAL(signalResetBtnRegister(bool)),
                this, SLOT(resetBtnSure(bool)));
    }
    ui->PB_sure->setEnabled(false);
    m_regCtrl->registerAccount(m_userInf);
}

void RegisterDialog::PB_cancle_clicked()
{
    this->close();
}

/*************************************************
Function Name： resetBtnSure()
Description: 重置确定按钮
*************************************************/
void RegisterDialog::resetBtnSure(bool enable)
{
    ui->PB_sure->setEnabled(enable);
}

/*************************************************
Function Name： setServer()
Description: 设置服务器信息
Input：  ip地址，端口号
Output： NULL
Changes： NULL
*************************************************/
void RegisterDialog::setServer(QString ip, int port)
{
    QQTcpSocket::s_hostAddress = ip;
    QQTcpSocket::s_hostPort = port;
}
