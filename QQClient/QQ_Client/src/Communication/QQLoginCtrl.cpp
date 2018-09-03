/*********************************************
File Name： QQLoginCtrl.cpp
Description： 用于控制登录的类
Changes：
********************************************/

#include "QQLoginCtrl.h"


// public:-----------------------------------------------------------------
QQLoginCtrl::QQLoginCtrl(QObject *parent) :
    QObject(parent)
{
    m_tcpSocket = new QQTcpSocket(this);
    m_tcpSocket->setFlag(1);
    connect(m_tcpSocket, SIGNAL(showConnectionStatus(QString, bool)),
            this, SLOT(changeLoginMessage(QString, bool)));

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

QQLoginCtrl::~QQLoginCtrl()
{
//    if (m_tcpSocket != NULL)
//    {
//        if (m_tcpSocket->isConnected())
//            m_tcpSocket->abort();
//            m_tcpSocket->close();
//        delete m_tcpSocket;
//        m_tcpSocket = NULL;
//    }
}


/*************************************************
Function Name： login()
Description: 发送登录信息
Input： const QString &id： 用户帐号, const QString &pwd：用户密码
*************************************************/
void QQLoginCtrl::login(const QString &id, const QString &pwd, const int status)
{
    m_kind = LOGIN;
    m_loginInfo.m_userID = id;
    m_loginInfo.m_password = pwd;
    m_loginInfo. m_status = status;
    if (m_tcpSocket->isConnected())
    {
        requestLogin();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect(); //如果套接字没有建立连接，则请求连接，connected信号对应的槽函数中会根据m_kind自动进行相应登录操作或其他操作
    }
}

/*************************************************
Function Name： getQuestionAndAnswer()
Description: 获取密保信息
*************************************************/
void QQLoginCtrl::getQuestionAndAnswer(const QString & id)
{
    m_kind = GET_QUESTION_ANSWER;
    m_id = id;
    if (m_tcpSocket->isConnected())
    {
        requestGetQuestionAndAnswer();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}

// mark: public slots:--------------------------------------------------------
/*************************************************
Function Name： changeLoginMessage()
Description: 改变登录信息
Input： const QString &mes： 信息, bool isLogin：状态
Output： NULL
Changes： NULL
*************************************************/
void QQLoginCtrl::changeLoginMessage(const QString &mes, bool isLogin)
{
    emit getLoginMessgae(mes, isLogin);
}

// mark: private slots:--------------------------------------------------

/*************************************************
Function Name： requestLogin()
Description: 请求登录
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void QQLoginCtrl::requestLogin()
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(LOGIN) << m_loginInfo;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}



/*************************************************
Function Name： sendRequest()
Description: 发送请求
*************************************************/
void QQLoginCtrl::sendRequest()
{
    switch (m_kind)
    {
        case LOGIN:
        {
            requestLogin();
            break;
        }
        case GET_QUESTION_ANSWER:
        {
            requestGetQuestionAndAnswer();
            break;
        }
        default:
            break;
    }
}

// private slots:---------------------------------------------

/*************************************************
Function Name： requestGetQuestionAndAnswer()
Description: 发送获取密保问题以及答案的请求
*************************************************/
void QQLoginCtrl::requestGetQuestionAndAnswer()
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(GET_QUESTION_ANSWER) << m_id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： readMessage()
Description: 读取信息
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void QQLoginCtrl::readMessage()
{
    QDataStream in(m_tcpSocket);
    //in.setVersion(QDataStream::Qt_5_9);
    if (m_blockSize == 0)
    {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;
    int type;

    in >> type;
    switch (type)
    {
        case LOGIN_SUCCESS:
            in >> m_myself;
            emit getLoginMessgae(tr("登录成功"), true, &m_myself);
            break;
        case LOGIN_FAIL:
            emit getLoginMessgae(tr("登录失败.帐号或者密码错误."),false);
            break;
        case HAVE_LOGINED:
            emit getLoginMessgae(tr("登录失败.该用户已经登录."),false);
            break;
        case GET_QUESTION_ANSWER_FAIL:
        {
            QMessageBox::critical(NULL, tr("找回密码"), tr("失败，帐号不存在！"));
            break;
        }
        case GET_QUESTION_ANSWER_SUCCESS:
        {
            in >> m_tempStr;
            emit getQuestionAndAnswerSuccess(m_tempStr);

            while (1)
            {
                bool isOkMes = false;
                QString str = QString(tr("密保问题:%1\n请输入问题答案:"))
                        .arg(m_tempStr.m_two);
                QString answer = QInputDialog::getText(NULL, "找回密码",
                                                       str,
                                                       QLineEdit::Normal,
                                                       NULL,
                                                       &isOkMes);
                if (!isOkMes)
                    break;
                if (answer != m_tempStr.m_three)
                {
                    str = QString(tr("回答错误!"));
                    QMessageBox::critical(NULL, tr("找回密码"), str);
                    continue;
                }
                else
                {
                    str = QString(tr("回答正确!\n您的帐号是:%1\n您的密码是:%2"))
                            .arg(m_id)
                            .arg(IMEncryption::getInstace()
                                 .getXorEncryptDecrypt(m_tempStr.m_one, 10));
                    QMessageBox::information(NULL, tr("找回密码"), str);
                }
                break;
            }
            break;

        }
        default:
            break;
    }

    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();
    m_blockSize = 0;
}


