#include "qqclientsocketctrl.h"

QQClientSocketCtrl::QQClientSocketCtrl(QObject *parent):
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteScoket()));
    m_blockSize = 0;
    m_save.m_clientSocket = this;
}


QQClientSocketCtrl::~QQClientSocketCtrl()
{
    if (m_database.isOpen())
        m_database.close();
}

/*************************************************
Function Name： receiveMessage()
Description: 接收用户发送的信息 与readyRead()信号关联 最后会emit sendSignal(m_save);
*************************************************/
void QQClientSocketCtrl::receiveMessage()

{
    QDataStream in(this);
    //in.setVersion(QDataStream::Qt_5_9);
    if (m_blockSize == 0)
    {
        if (bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (bytesAvailable() < m_blockSize)
        return;

    in >> m_save.m_requestKind;

    switch (m_save.m_requestKind)
    {
        case CHECK_CONNECTION:
        {
            m_save.m_replyKind = CHECK_CONNECTION;
            sendMessage(m_save);
            m_blockSize = 0;
            break;
        }
        case LOGIN:
        {
            in >> m_save.m_loginInf;
            m_save.m_myID = m_save.m_loginInf.m_userID;
            m_save.m_socketID = m_save.m_myID;
            break;
        }
        case CHECK_MESSAGE:
        {
            in >> m_save.m_myID;
            break;
        }
        case REGISTER:
        {
            in >> m_save.m_userInf;
            break;
        }
        case GET_QUESTION_ANSWER:
        {
            in >> m_save.m_myID;
            break;
        }
        case TALK:
        {
            qDebug()<<"QQClientSocketCtrl::receiveMessage()  case TALK";
            in >> m_save.m_message;
            break;
        }
        case GET_ALL_FRIENDS:
        {
            in >> m_save.m_myID >> m_save.m_status;
            m_save.m_socketID = m_save.m_myID;
            break;
        }
        case GET_ALL_FLOCKS:
        {
            in >> m_save.m_myID;
            break;
        }
        case GET_ALL_DISCUSSIONS:
        {
            in >> m_save.m_myID;
            break;
        }
        case GET_FLOCK_MEMBERS:
        {
            in >> m_save.m_flockID;
            break;
        }
        case GET_DISCUSSIONS_MEMBERS:
        {
            in >> m_save.m_discussionID;
            break;
        }

        case GET_FRIEND_INFORMATION:
        {
            in >> m_save.m_peerID;
            break;
        }
        case GET_MYSELF_INFORMATION:
        {
            in >> m_save.m_myID;
            break;
        }
        case CHANGE_INFORMATION:
        {
            in >> m_save.m_userInf;
            break;
        }
        case CHANGE_REMARK:
        {
            in >> m_save.m_tempStr;
            break;
        }
        case CHANGE_STATUE:
        {
            in >> m_save.m_myID >> m_save.m_status;
            break;
        }
        case ADD_FRIEND:
        {
            in >> m_save.m_message;
            break;
        }
        case REFUSE_FRIEND:
        {
            //in >> m_save.m_peerID;
            break;
        }
        case DELETE_FRIEND:
        {
            in >> m_save.m_myID >> m_save.m_peerID;
            break;
        }

        case ADD_FLOCK:
        {
            in >> m_save.m_message;
            break;
        }
        case DROP_FLOCK:
        {
            in >> m_save.m_myID >> m_save.m_flockID;
            break;
        }
        case LEAVE_FLOCK:
        {
            in >> m_save.m_myID >> m_save.m_flockID;
            break;
        }
        case CHANGE_FLOCK:
        {
            in >> m_save.m_flockInf;
            break;
        }
        case CHANGE_FLOCK_REMARK:
        {
            in >> m_save.m_tempStr;
            break;
        }
        case CREATE_FLOCK:
        {
            in >> m_save.m_tempStr;
            break;
        }

        case ADD_DISCUSSION:
        {
            in >> m_save.m_message;
            break;
        }
        case DROP_DISCUSSION:
        {
            in >> m_save.m_myID >> m_save.m_discussionID;
            break;
        }
        case LEAVE_DISCUSSION:
        {
            in >> m_save.m_myID >> m_save.m_discussionID;
            break;
        }
        case CHANGE_DISCUSSION:
        {
            in >> m_save.m_discussionInf;
            break;
        }
        case CREATE_DISCUSSION:
        {
            in >> m_save.m_tempStr;
            break;
        }
        case GET_IN_MAILS:
        case GET_OUT_MAILS:
        {
            in >> m_save.m_myID;
            m_save.m_socketID = m_save.m_myID;
            m_save.m_socketID.append(MAIL_ADDRESS_FORMAT);
            break;
        }
        case DELETE_IN_MAIL:
        case DELETE_OUT_MAIL:
        case SET_MAIL_READ:
        {
            in >> m_save.m_myID >> m_save.m_mailID;
            break;
        }
        case SEND_MAIL:
        {
            in >> m_save.m_mail;
            break;
        }

        case REMOVE_BOX:
        case CREATE_BOX:
        {
            in >> m_save.m_myID >> m_save.m_title;
            break;
        }
        case MOVE_FRIEND_BOX:
        {
            in >> m_save.m_myID >> m_save.m_peerID
               >> m_save.m_title >> m_save.m_newTitle;
            break;
        }
        case RENAME_BOX:
        {
            in >> m_save.m_myID >> m_save.m_title >> m_save.m_newTitle;
            break;
        }
        case GET_HISTORY_MESSAGE:
        {
            in >> m_save.m_myID >> m_save.m_peerID >> m_save.m_date;
            break;
        }
        case CHANGE_PASSWORD:
        {
            in >> m_save.m_tempStr;
            break;
        }

        default:
            break;
    }
    QByteArray data = this->readAll();
    qDebug() << "IMClientSocketCtrl::receiveMessage _剩余读取数据大小leaved in socket: " << data.size();

    m_blockSize =0;
    emit sendSignal(m_save);
}

/*************************************************
Function Name： deleteScoket()
Description: 删除socket 与disconnected()信号关联
*************************************************/
void QQClientSocketCtrl::deleteScoket()
{
    if (!m_save.m_socketID.isEmpty())
    {
        if ( LOGIN != m_save.m_requestKind)
            emit deleteSignal(m_save.m_socketID);
    }
    deleteLater();
}

/*************************************************
Function Name： sendMessage()
Description: 发送信息
*************************************************/
void QQClientSocketCtrl::sendMessage(const SaveTmpInformation &temp)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << (int)temp.m_replyKind;

    switch (temp.m_replyKind)
    {
        case LOGIN_SUCCESS:
        {
            qDebug()<<"IMClientSocketCtrl::sendMessage  回送LOGIN_SUCCESS";
            out << temp.m_userInf;
            break;
        }
        case REGISTER_SUCCESS:
        {
            out << temp.m_userInf.m_userID << temp.m_userInf.m_regDateTime;
            break;
        }
        case GET_QUESTION_ANSWER_SUCCESS:
        {
            out << temp.m_tempStr;
            break;
        }
        case GET_ALL_FRIENDS_SUCCESS:
        {
            int len = temp.m_friendsVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_friendsVec[i];
            break;
        }
        case GET_ALL_FLOCKS_SUCCESS:
        {
            int len = temp.m_flocksVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_flocksVec[i];
            break;
        }
        case GET_ALL_DISCUSSIONS_SUCCESS:
        {
            int len = temp.m_discussionsVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_discussionsVec[i];
            break;
        }
        case GET_FLOCK_MEMBERS_SUCCESS:
        {
            int len = temp.m_flockMembersVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_flockMembersVec[i];
            break;
        }
        case GET_DISCUSSION_MEMBERS_SUCCESS:
        {
            int len = temp.m_discussionMembersVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_discussionMembersVec[i];
            break;
        }


        case HAVE_MESSAGE:
            break;
        case CHANGE_STATUE:
            out << temp.m_peerID << temp.m_status;
            break;
        case GET_MYSELF_SUCCESS:
        {
            out << temp.m_userInf;
            break;
        }
        case DELETE_FRIEND_SUCCESS:
        {
            out << temp.m_myID << temp.m_peerID << temp.m_groupName;
            break;
        }
        case CHANGE_INFORMATION_SUCCESS:
        {
            out << temp.m_userInf;
            break;
        }
        case CHANGE_INFORMATION:
        {
            out << temp.m_friendInf;
            break;
        }
        case ADD_FRIEND:
        {
            out << temp.m_message << temp.m_userInf;
            break;
        }
        case GET_FRIEND_SUCCESS:
        {
            out << temp.m_userInf;
            break;
        }
        case TALK:
            qDebug()<<"QQClientSocketCtrl::sendMessage case TALK ";
            out << temp.m_message;
            break;
        case CHANGE_REMARK_SUCCESS:
        {
            out << temp.m_tempStr;
            break;
        }
        case BE_DELETED:
        {
            out << temp.m_myID << temp.m_peerID << temp.m_groupNameF;
            break;
        }
        case REQUEST_FLOCK:
        {
            out << temp.m_message;
            break;
        }
        case ADD_FLOCK:
        {
            out << temp.m_message << temp.m_flockMember << temp.m_flockInf;
            break;
        }

        case DROP_FLOCK_SUCCESS:
        {
            out << temp.m_flockID;
            break;
        }
         case LEAVE_FLOCK_SUCCESS:
        {
            out << temp.m_myID << temp.m_flockID << temp.m_peerID;
            break;
        }
        case LEAVE_FLOCK_MEMBER:
        {
            out << temp.m_myID << temp.m_flockID << temp.m_peerID;
            break;
        }
        case CHANGE_FLOCK_SUCCESS:
        {
            out << temp.m_flockInf;
            break;
        }
        case CHANGE_FLOCK_REMARK_SUCCESS:
        {
            out << temp.m_tempStr;
            break;
        }
        case CREATE_FLOCK_SUCCESS:
        {
            out << temp.m_flockInf;
            break;
        }



        case ADD_DISCUSSION:
        {
            out << temp.m_message;
            if (ADD_DISCUSSION_SUCCESS == temp.m_message.m_type)
                out << temp.m_discussionInf;
            else if (NEW_DISCUSSION_MEMBER == temp.m_message.m_type)
                out << temp.m_discussionMember;
            break;
        }

        case DROP_DISCUSSION_SUCCESS:
        {
            out << temp.m_discussionID;
            break;
        }
         case LEAVE_DISCUSSION_MEMBER:
        {
            out << temp.m_myID << temp.m_discussionID;// << temp.m_peerID;
            break;
        }
        case CHANGE_DISCUSSION_SUCCESS:
        {
            out << temp.m_discussionInf;
            break;
        }

        case CREATE_DISCUSSION_SUCCESS:
        {
            out << temp.m_discussionInf;
            break;
        }
        /*****************mail*****************/
        case GET_IN_MAILS_SUCCESS:
        {
            int len = temp.m_inMailsVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_inMailsVec[i];
            break;
        }
        case GET_OUT_MAILS_SUCCESS:
        {
            int len = temp.m_outMailsVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_outMailsVec[i];
            break;
        }

        case DELETE_IN_MAIL_SUCCESS:
        case DELETE_OUT_MAIL_SUCCESS:
        {
            out << temp.m_myID << temp.m_mailID;
            break;
        }

        case SEND_MAIL_SUCCESS:
        case RECEIVE_MAIL:
        {
            out << temp.m_mail;
            break;
        }

        case RENAME_BOX_SUCCESS:
        {
            out << temp.m_myID << temp.m_title << temp.m_newTitle;
            break;
        }
        case MOVE_FRIEND_BOX_SUCCESS:
        {
            out << temp.m_myID << temp.m_peerID << temp.m_title << temp.m_newTitle;
            break;
        }
        case GET_HISTORY_MESSAGE_SUCCESS:
        {
            out << temp.m_myID << temp.m_peerID << temp.m_date;
            int len = temp.m_historyMessageVec.size();
            out << len;
            for (int i=0; i<len; ++i)
                out << temp.m_historyMessageVec[i];
            break;
        }
        default:
            break;
    }

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
}
