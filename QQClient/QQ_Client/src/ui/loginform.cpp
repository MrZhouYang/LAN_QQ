#include "loginform.h"
#include "ui_loginform.h"
#include "mainform.h"
#include <QMovie>
#include <QDebug>
#include <QMessageBox>



LoginForm::LoginForm(QWidget *parent) :
    MoveableFramelessWindow(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/sys/img/blue70-2.gif");
    ui->label->setMovie(movie);
    ui->label_minimize->installEventFilter(this);
    ui->label_shutdown->installEventFilter(this);
    ui->label_Register->installEventFilter(this);
    ui->label_setting->installEventFilter(this);
    movie->start();

    //关联登录按钮点击
    connect(ui->pushButton_login,SIGNAL(clicked(bool)),this,SLOT(doLoginButClick()) );

}

LoginForm::~LoginForm()
{
    if(m_loginCtrl != NULL){
        delete m_loginCtrl;
        m_loginCtrl = NULL;
    }

    delete ui;
}

QWidget *LoginForm::getDragnWidget()
{
    return ui->login_top_widget;
}

bool LoginForm::eventFilter(QObject *object, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress&&object==ui->label_shutdown)
    {
         close();
         return true;
    }
    else if(e->type()==QEvent::MouseButtonPress&&object==ui->label_minimize){
        showMinimized();
        return true;//停止转发
    }
    else if(e->type()==QEvent::MouseButtonPress&&object==ui->label_Register){
        RegisterDialog *rg_dialog = new RegisterDialog;
        rg_dialog->show();
    }
    else if(e->type()==QEvent::MouseButtonPress&&object==ui->label_setting){
        //弹出IP和端口设置窗口
        LoginSetting *p_setlog = new LoginSetting;
        connect(p_setlog,SIGNAL(server_setting(QString,int)),this,SLOT(setServer(QString,int)));
        p_setlog->show();
    }
    return false; //继续转发
}

//登录按钮按下
void LoginForm::doLoginButClick()
{
    //设置默认连接服务器IP和port
    setServer(QString("127.0.0.1"),1234);

    ui->lineEdit_ID->setReadOnly(true);
    ui->lineEdit_pass->setReadOnly(true);


    //qDebug()<<"建立QQLoginCtrl";
    m_loginCtrl = new QQLoginCtrl(this);
    connect(m_loginCtrl, SIGNAL(getLoginMessgae(QString,bool,const UserInformation*)),
            this, SLOT(setLabelStatus(QString,bool,const UserInformation*)));


    switch (ui->cbx_Status->currentIndex())
    {
        case 0:
            m_status = ONLINE;
            break;
        case 1:
            m_status = INVISIBLE;
            break;
        case 2:
            m_status = BUSY;
            break;
        case 3:
            m_status = LEAVE;
            break;
        case 4:
            m_status = NOTDISTURB;
            break;
        default:
            m_status = ONLINE;
            break;
    }
    QString pwd = IMEncryption::getInstace()
            .getXorEncryptDecrypt(ui->lineEdit_pass->text(), 10); //因为这里对密码进行了加密，所以数据库中存储的是加密后的密码 123456加密后是;89>?<
    m_loginCtrl->login(ui->lineEdit_ID->text(), pwd, m_status);

}


/*************************************************
Function Name： setServer()
Description: 设置服务器信息
Input：  ip地址，端口号
Output： NULL
Changes： NULL
*************************************************/
void LoginForm::setServer(QString ip, int port)
{
    QQTcpSocket::s_hostAddress = ip;
    QQTcpSocket::s_hostPort = port;
}

/*************************************************
Function Name： setLabelStatus()
Description: 设置状态标签,控制是否弹出主界面
*************************************************/
void LoginForm::setLabelStatus(const QString &mes, bool isLogin,
                                   const UserInformation *me)
{
    if (isLogin == true)
    {
        ui->pushButton_login->setEnabled(false);
        ui->pushButton_login->setText(tr("取消"));
        //qDebug() << "验证成功，可以弹出主界面了";
        //弹出主界面
        MainForm *mainWidget = new MainForm(*me);
        mainWidget->getFriendsInformation();
        mainWidget->show();

        close();
    }
    else
    {
        QMessageBox::information(this,tr("警告"),mes);
        ui->pushButton_login->setText(tr("登录"));
        ui->lineEdit_ID->setReadOnly(false);
        ui->lineEdit_pass->setReadOnly(false);
    }
}
