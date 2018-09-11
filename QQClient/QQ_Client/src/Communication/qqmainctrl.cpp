#include "qqmainctrl.h"

QQMainCtrl::QQMainCtrl(const QString myID, QObject *parent) :
    m_myID(myID),QObject(parent)
{
    m_tcpSocket = new QQTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(requestGetFriendsInformation()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(closeWindow()));
}

QQMainCtrl::~QQMainCtrl()
{
    m_tcpSocket->close();
}

void QQMainCtrl::closeConnect(){
    m_tcpSocket->close();
}

/*************************************************
Function Name： getFriendsInformation
Description: 获取所有好友信息
*************************************************/
void QQMainCtrl::getFriendsInformation(const QString &id, const int status)
{
    m_myID = id;
    m_status = status;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetFriendsInformation();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect(); //这里建立连接后connected()信号会同样出发requestGetFriendsInformation()来获取好友列表
    }
}

/*************************************************
Function Name： getFriendInformation
Description: 获取好友详细信息
*************************************************/
void QQMainCtrl::getFriendInformation(const QString &id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetFriendInformation(id);
    }
}

/*************************************************
Function Name： requestGetFriendInformation()
Description: 发送获取好友详细信息的请求
*************************************************/
void QQMainCtrl::requestGetFriendInformation(const QString &id)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(GET_FRIEND_INFORMATION) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： changeMyInformation
Description: 修改自己的信息
*************************************************/
void QQMainCtrl::changeMyInformation(const UserInformation &me)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestChangeMyInformation(me);
    }
}

/*************************************************
Function Name： requestChangeMyInformation()
Description: 发送修改自己信息的请求
*************************************************/
void QQMainCtrl::requestChangeMyInformation(const UserInformation &me)
{
    if (NULL == m_tcpSocket)
        return;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(CHANGE_INFORMATION) << me;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： changeFriendRemark
Description: 修改好友备注
*************************************************/
void QQMainCtrl::changeFriendRemark(const QString & myID,
                                    const QString & friendID,
                                    const QString & remark)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFriendRemark(myID, friendID, remark);
}

/*************************************************
Function Name： requestChangeFriendRemark()
Description: 发送修改好友备注的请求
*************************************************/
void QQMainCtrl::requestChangeFriendRemark(const QString & myID,
                                           const QString & friendID,
                                           const QString &remark)
{
    if (NULL == m_tcpSocket)
        return;

    TempStrings tempStr;
    tempStr.m_one = myID;
    tempStr.m_two = friendID;
    tempStr.m_three = remark;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(CHANGE_REMARK) << tempStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： deleteFriend
Description: 删除好友
*************************************************/
void QQMainCtrl::deleteFriend(const QString & myID, const QString & friendID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDeleteFriend(myID, friendID);
}

/*************************************************
Function Name： requestDeleteFriend()
Description: 发送删除好友的请求
*************************************************/
void QQMainCtrl::requestDeleteFriend(const QString & myID,
                                     const QString & friendID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(DELETE_FRIEND) << myID << friendID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestGetFriendsInformation()
Description: 发送获取所有好友信息的请求 QTcpSocket::connected()的槽函数
*************************************************/
void QQMainCtrl::requestGetFriendsInformation()
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(GET_ALL_FRIENDS) << m_myID << m_status;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： readMessage
Description: 读取信息 QTcpSocket::readyRead()的槽函数
*************************************************/
void QQMainCtrl::readMessage()
{
    qDebug()<<"QQMainCtrl::readMessage() 204行";
    if (NULL == m_tcpSocket)
        return;

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
    int len;
    switch(type)
    {
        case NO_FRIEND: // 没有好友
        {
            //发送获取所有群消息的请求

            break;
        }
        case GET_ALL_FRIENDS_FAIL: // 获取所有好友信息失败
            break;
        case GET_ALL_FRIENDS_SUCCESS: // 获取所有好友信息成功
        {
            in >> len;
            m_friendsVec.clear();
            m_friendsVec.resize(len);
            for(int i=0; i<len; i++)
            {
                in >> m_friendsVec[i];
            }
            qDebug() << "friends len: " << len;
            emit getFriendsSuccess(m_friendsVec);
            break;
        }
        case GET_FRIEND_FAIL: // 获得好友资料失败
            break;
        case GET_FRIEND_SUCCESS: //获得好友资料成功
        {
            in >> m_friInf;//获取单个好友的个人信息
            emit getFriendInformationSuccess(m_friInf);
            break;
        }
        case GET_MYSELF_FAIL: //获得自己详细资料失败
        {
            break;
        }
        case GET_MYSELF_SUCCESS: //获得自己详细资料成功
        {
            in >> m_myInf;
            emit getMyInformationSuccess(m_myInf);
            break;
        }
        case CHANGE_INFORMATION_FAIL: //改变自身资料失败
        {
            QMessageBox::critical(NULL, tr("修改个人信息"), tr("修改个人信息失败"));
            break;
        }
        case CHANGE_INFORMATION_SUCCESS: //改变自身资料成功
        {
            in >> m_myInf;
            emit changeMyInformationSuccess(m_myInf);
            QMessageBox::information(NULL, tr("修改个人信息"), tr("修改个人信息成功"));
            break;
        }
        case TALK: //收到对话
        {
            //qDebug()<<"QQMainCtrl::readMessage() case TALK emit getFriendTalkMessage(m_message)";
            in >> m_message;
            emit getFriendTalkMessage(m_message);
            break;
        }
        case CHANGE_STATUE: //改变自身状态
        {
            in >> m_peerID >> m_peerStatus;
            emit getFriendChangedStatus(m_peerID, m_peerStatus);
            break;
        }
        case CHANGE_INFORMATION: //改变自己的信息
        {
            in >> m_friSimInf;
            emit getFriendChangedInformation(m_friSimInf);
            break;
        }
        case CHANGE_REMARK_SUCCESS: //修改备注成功
        {
            in >> m_tempStr;
            emit changeFriendRemarkSuccess(m_tempStr);
            break;
        }
        case DELETE_FRIEND_SUCCESS: //删除好友成功
        {
            in >> m_id >> m_peerID >> m_groupName;
            emit deleteFriendSuccess(m_id, m_peerID, m_groupName);
            break;
        }
        case DELETE_FRIEND_FAIL: //删除好友失败
        {
            break;
        }
        case BE_DELETED: //自己被好友删除了
        {
            in >> m_id >> m_peerID >> m_groupName;

            QString temp = QString(tr("你被好友(%1)删除了")).arg(m_peerID);
            QMessageBox::information(NULL, tr("消息"), temp);
            emit deleteFriendSuccess(m_id, m_peerID, m_groupName);
            break;
        }
    //    case ADD_FRIEND:
    //    {
    //        in >> m_message >> m_friInf;
    //        emit getFriendRequest(m_message, m_friInf);
    //        break;
    //    }
        case RENAME_BOX_SUCCESS: // 重命名分组成功
        {
            in >> m_id >> m_title >> m_newTitle;
            if (m_id == m_myID)
            {
                emit renameBoxSuccess(m_title, m_newTitle);
            }
            break;
        }
        case MOVE_FRIEND_BOX_SUCCESS://移动好友至其他分组成功
        {
            in >> m_id >> m_peerID >> m_title >> m_newTitle;
            if (m_id == m_myID)
            {
                emit moveFriendToBoxSuccess(m_peerID, m_title, m_newTitle);
            }
            break;
        }
        case CHANGE_PWD_FAIL: //修改密码失败
        {
            QMessageBox::information(NULL, tr("修改密码"), tr("修改密码失败！"));
            break;
        }
        case CHANGE_PWD_SUCCESS:  //修改密码成功
        {
            m_tcpSocket->setFlag(1);
            QMessageBox::information(NULL, tr("修改密码"), tr("修改成功！请重新登录"));
            emit closeWindowSignal();
            LoginForm *loginWidget = new LoginForm;
            loginWidget->show();
            break;
        }
        default:
            break;
    }
    m_blockSize = 0;
    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();
}

/*************************************************
Function Name： closeWindow
Description: 关闭主程序
*************************************************/
void QQMainCtrl::closeWindow()
{
    qDebug()<<"QQMainCtrl::closeWindow() 372行";
    if (m_tcpSocket->flag() == 0)
    {
        QMessageBox::information(NULL, tr("系统提示"),
                              tr("您的客户端已经与服务器断开连接，请重新登录。"));
        emit closeWindowSignal();
        LoginForm *loginWidget = new LoginForm;
        loginWidget->show();
    }
}

/*************************************************
Function Name： renameBox
Description: 重命名分组
*************************************************/
void QQMainCtrl::renameBox(const QString & oldTitle, const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestRenameBox(oldTitle, newTitle);
}

/*************************************************
Function Name： requestRenameBox
Description: 发送重命名分组的请求
*************************************************/
void QQMainCtrl::requestRenameBox(const QString & oldTitle, const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(RENAME_BOX) << m_myID << oldTitle << newTitle;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： sendTalkMessage
Description: 发送聊天信息
*************************************************/
void QQMainCtrl::sendTalkMessage(TalkMessage &mes)
{
    mes.m_senderID = m_myID;
    mes.m_senderIP = QQTcpSocket::getIP();
    m_messageVector.push_back(mes);
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestSendTalkMessage();
    }
}

/*************************************************
Function Name： requestSendTalkMessage
Description: 发送对话信息请求
*************************************************/
void QQMainCtrl::requestSendTalkMessage()
{
    if (NULL == m_tcpSocket)
        return;

    while (m_messageVector.size() > 0)
    {
        m_blockSize = 0;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        //out.setVersion(QDataStream::Qt_5_9);
        out << quint16(0) << int(TALK)
            << m_messageVector.front();
        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));
        m_tcpSocket->write(block);

        m_messageVector.pop_front();
    }
}

/*************************************************
Function Name： moveFriendToBox
Description:  移动好友至其他分组
*************************************************/
void QQMainCtrl::moveFriendToBox(const QString &friendID, const QString &oldTitle,
                                 const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestMoveFriendToBox(friendID, oldTitle, newTitle);
}

/*************************************************
Function Name： requestMoveFriendToBox
Description:  请求移动好友至其他分组
*************************************************/
void QQMainCtrl::requestMoveFriendToBox(const QString & friendID,
                                        const QString & oldTitle,
                                        const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << int(MOVE_FRIEND_BOX) << m_myID << friendID << oldTitle << newTitle;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}
