/*********************************************
File Name： IMConstant.h
Description： 定义了一个常用的结构体与常量
Changes：
********************************************/

#ifndef QQCONSTANT_H
#define QQCONSTANT_H

#include <QFont>
#include <QColor>
#include <QDataStream>
#include <QDateTime>
#include <QVector>
#include <QString>
#include <QObject>
class QQClientSocketCtrl;

static const QString GROUP_NAME_DEFAULT = QString(QObject::tr("New Friends"));

struct ServerNode
{
    QString ipAddress;			//服务器地址
    int port;					//服务器窗口
    ServerNode()
    {	port = 0;	}
};

// 登录状态
enum LoginStatus
{
    ONLINE = 0,    // 在线
    INVISIBLE = 1, // 隐身
    BUSY = 2,      // 忙碌
    LEAVE = 3,     // 离开
    NOTDISTURB = 4,// 请勿打扰
    OFFLINE = 5
};

//群成员身份
enum FlockStatus
{
    FLOCK_HOST = 0,    // 群主
    FLOCK_ADMAIN = 1,  // 群管理员
    FLOCK_MEMBER = 2   // 群成员
};

//讨论组成员身份
enum DiscussionStatus
{
    DISCUSSION_HOST = 0,    // 组长
    DISCUSSION_MEMBER = 1   // 组员
};

enum MailStatus
{
    MAIL_UNREAD = 0,
    MAIL_READ = 1
};


// 信息类型
enum MessageType
{
    /***********************client to server************************/
    CHECK_CONNECTION,           // 检查是否能与服务器连接
    LOGIN,                      // 登录
    REGISTER,                   // 注册
    GET_QUESTION_ANSWER,    // 获取密保问题以及答案
    GET_QUESTION_ANSWER_SUCCESS,
    GET_QUESTION_ANSWER_FAIL,

    CHECK_MESSAGE,              // 检查有无给自己的信息（登录时检查）

    GET_ALL_FRIENDS,            // 获取所有好友信息
    GET_ALL_FLOCKS,             // 获取所有群信息
    GET_ALL_DISCUSSIONS,        // 获取所有讨论组信息
    GET_FLOCK_MEMBERS,          // 获取群成员
    GET_DISCUSSIONS_MEMBERS,    // 获取讨论组成员

    TALK,				// 发送对话
    ADD_FRIEND,                 // 添加好友



    ADD_FLOCK,                   // 用户加群
    ADD_DISCUSSION,

    FLOCK_ADD_MEMBER,            // 群加用户

    GET_FRIEND_INFORMATION,		// 获取好友信息
    DELETE_FRIEND,				// 删除好友
    GET_MYSELF_INFORMATION,		// 获取自己信息
    CHANGE_INFORMATION,			// 改变自己的信息
    CHANGE_REMARK,				// 改变（好友）备注
    CHANGE_PASSWORD,			    // 修改密码
    CHANGE_STATUE,				// 改变自身状态
    // 还有分组好友管理
    QUIT,						// 退出

    /***********************server to client************************/

    LOGIN_SUCCESS ,				// 登录成功
    LOGIN_FAIL,			        // 登录失败
    HAVE_LOGINED,				// 已经登录
    REGISTER_SUCCESS,	        // 注册成功
    REGISTER_FAIL,			    // 注册失败

    REMOVE_BOX,               // 删除分组
    REMOVE_BOX_SUCCESS,
    REMOVE_BOX_FAIL,
    RENAME_BOX,               // 重命名分组
    RENAME_BOX_SUCCESS,
    RENAME_BOX_FAIL,
    CREATE_BOX,               // 创建分组
    CREATE_BOX_SUCEESS,
    CREATE_BOX_FAIL,
    MOVE_FRIEND_BOX,          // 移动好友至其他分组  36
    MOVE_FRIEND_BOX_SUCCESS,
    MOVE_FRIEND_BOX_FAIL,


    GET_ALL_FRIENDS_SUCCESS,    // 获取所有好友信息成功
    GET_ALL_FRIENDS_FAIL,       // 获取所有好友信息失败
    NO_FRIEND,                  // 没有好友
    GET_ALL_FLOCKS_SUCCESS,     // 获取所有群信息成功
    GET_ALL_FLOCKS_FAIL,        // 获取所有群信息失败
    NO_FLOCK,
    GET_ALL_DISCUSSIONS_SUCCESS,// 获取所有讨论组信息成功
    GET_ALL_DISCUSSIONS_FAIL,   // 获取所有讨论组信息失败
    NO_DISCUSSION,

    GET_FLOCK_MEMBERS_FAIL,           // 获取群成员失败
    GET_FLOCK_MEMBERS_SUCCESS,        // 获取群成员成功
    NO_FLOCK_MEMBER,                // 没有群成员
    GET_DISCUSSION_MEMBERS_FAIL,     // 获取讨论组成员失败
    GET_DISCUSSION_MEMBERS_SUCCESS,  // 获取讨论组成员成功
    NO_DISCUSSION_MEMBER,          // 没有讨论组成员

    NO_MESSAGE,				    // 没有信息
    HAVE_MESSAGE,				// 有信息
    HAVE_TALK_MESSAGE,          // 有聊天信息
    //？？？？？？？？？？？？？？？？
    FRIEND_REQUESTED,			// 好友请求
    FRIEDN_NO_ACCOUNT,			// 没有这个用户名
    ALREAD_FRIENDS,			    // 回应好友请求

    GET_FRIEND_FAIL,
    GET_FRIEND_SUCCESS,			// 获得好友资料成功
    DELETE_FRIEND_FAIL,
    DELETE_FRIEND_SUCCESS,		// 删除好友成功
    GET_MYSELF_FAIL,
    GET_MYSELF_SUCCESS,		    // 获得自己详细资料成功
    CHANGE_INFORMATION_FAIL,
    CHANGE_INFORMATION_SUCCESS,	// 改变自身资料成功

    CHANGE_REMARK_FAIL,             // 修改备注失败
    CHANGE_REMARK_SUCCESS,		// 修改备注成功

    OLD_PWD_IS_WRONG,			// 旧密码是错的
    CHANGE_PWD_FAIL,              // 修改密码失败
    CHANGE_PWD_SUCCESS,			// 修改密码成功

    /***********************client to client************************/

    REQUEST_FRIEND,	     // 请求添加好友
    AGREE_FRIEND,	     // 同意好友请求
    REFUSE_FRIEND,		 // 不同意好友请求
    ADD_FRIEND_FAIL,      // 添加好友失败
    ADD_FRIEND_SUCCESS,   // 添加好友成功
    END_ADD_FRIEND,	     // 好友添加结束
    BE_DELETED,		     // 自己被好友删除了

    MESSAGE,				 // 普通信息
    TALK_MESSAGE,         // 聊天信息

    REQUEST_FLOCK,   // 用户请求加入群
    FLOCK_AGREE,    // 群主同意用户加入
    FLOCK_REFUSE,   // 群主拒绝用户加入
    ADD_FLOCK_FAIL,             // 加入群失败
    ADD_FLOCK_SUCCESS,          // 加入群成功
    NEW_FLOCK_MEMBER,           // 新成员入群
    LEAVE_FLOCK_MEMBER,


    FLOCK_REQUEST,  // 群主请求用户加入群
    AGREE_FLOCK,    // 用户同意加入群
    REFUSE_FLOCK,   // 用户拒绝加入群


    CREATE_FLOCK,               // 创建群
    CREATE_FLOCK_FAIL,
    CREATE_FLOCK_SUCCESS,

    CREATE_DISCUSSION,               // 创建讨论组
    CREATE_DISCUSSION_FAIL,
    CREATE_DISCUSSION_SUCCESS,

    DROP_FLOCK,                 // 解散群
    DROP_FLOCK_FAIL,            // 解散群失败
    DROP_FLOCK_SUCCESS,         // 解散群成功

    DROP_DISCUSSION,                 // 解散讨论组
    DROP_DISCUSSION_FAIL,            // 解散讨论组失败
    DROP_DISCUSSION_SUCCESS,         // 解散讨论组成功

    LEAVE_FLOCK,              // 退出群
    LEAVE_FLOCK_SUCCESS,      // 退出群成功
    LEAVE_FLCCK_FAIL,         // 退出群失败
    LEAVE_DISCUSSION,           // 退出讨论组
    LEAVE_DISCUSSION_FAIL,       // 退出讨论组失败
    LEAVE_DISCUSSION_SUCCESS,   // 退出讨论组成功


    ADD_DISCUSSION_FAIL,
    ADD_DISCUSSION_SUCCESS,
    NEW_DISCUSSION_MEMBER,      // 新成员入讨论组
    LEAVE_DISCUSSION_MEMBER,

    CHANGE_FLOCK,               // 修改群信息
    CHANGE_FLOCK_SUCCESS,
    CHANGE_FLOCK_FAIL,

    CHANGE_FLOCK_REMARK,             // 修改群成员备注
    CHANGE_FLOCK_REMARK_FAIL,
    CHANGE_FLOCK_REMARK_SUCCESS,

    CHANGE_DISCUSSION,               // 修改讨论组信息
    CHANGE_DISCUSSION_SUCCESS,
    CHANGE_DISCUSSION_FAIL,

    TALK_FLOCK,               // 群对话
    TALK_DISCUSSION,          // 讨论组对话

    REQUEST_VIDEO,
    REFUSE_VIDEO,
    END_VIDEO,
    REQUEST_VOICE,
    AGREE_VOICE,
    REFUSE_VOICE,
    END_VOICE,
    REQUEST_FILE,
    AGREE_FILE,
    REFUSE_FILE,
    END_FILE,

    /****** 邮件模块 ******/
    GET_IN_MAILS,
    GET_IN_MAILS_SUCCESS,
    GET_IN_MAILS_FAIL,

    GET_OUT_MAILS,
    GET_OUT_MAILS_SUCCESS,
    GET_OUT_MAILS_FAIL,

    SEND_MAIL,
    SEND_MAIL_SUCCESS,
    SEND_MAIL_FAIL,

    RECEIVE_MAIL,
    RECEIVE_MAIL_SUCCESS,
    RECEIVE_MAIL_FAIL,

    DELETE_IN_MAIL,
    DELETE_IN_MAIL_SUCCESS,
    DELETE_IN_MAIL_FAIL,
    DELETE_OUT_MAIL,
    DELETE_OUT_MAIL_SUCCESS,
    DELETE_OUT_MAIL_FAIL,

    SET_MAIL_READ,

    GET_HISTORY_MESSAGE,
    GET_HISTORY_MESSAGE_SUCCESS,
    GET_HISTORY_MESSAGE_FAIL
};


// 存储聊天的字体和颜色
struct SaveFile
{
    QFont m_font;
    QColor m_color;
    friend QDataStream & operator<< (QDataStream &out, const SaveFile &sf)
    {
       out << sf.m_font << sf.m_color;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, SaveFile &sf)
    {
       in >> sf.m_font >> sf.m_color;
       return in;
    }
};

struct MailInformation
{
    int m_mailID;
    QString m_senderAddress;
    QString m_receiverAddress;
    QString m_theme;
    QString m_content;
    QDateTime m_dateTime;
    int m_status;

    MailInformation()
    {
        m_status = MAIL_UNREAD;
    }

    // 重载输入输出操作符
    friend QDataStream &operator<<(QDataStream &out, const MailInformation &mail)
    {
        out << mail.m_mailID << mail.m_senderAddress << mail.m_receiverAddress
            << mail.m_theme << mail.m_content << mail.m_dateTime << mail.m_status;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, MailInformation &mail)
    {
        in >> mail.m_mailID >> mail.m_senderAddress >> mail.m_receiverAddress
           >> mail.m_theme >> mail.m_content >> mail.m_dateTime >> mail.m_status;
        return in;
    }
};

// 用户详细信息
struct UserInformation
{
    //    QString m_picture;
    int m_headPortrait;
    QString m_userID;
    QString m_nickname;
    QString m_password;
    QString m_sex;
    QDate m_birthday;
    QString m_question;
    QString m_answer;
    QString m_name;
    QString m_phone;
    QString m_address;
    QDateTime m_regDateTime;
    //    QString m_mark;
    int m_status;

    UserInformation()
    {
       m_status = OFFLINE;
       m_headPortrait = 1;
    }
    // 重载输入输出操作符
    friend QDataStream &operator<<(QDataStream &out, const UserInformation &user)
    {
       out << user.m_headPortrait << user.m_userID << user.m_nickname
           << user.m_password << user.m_sex << user.m_birthday
           << user.m_question << user.m_answer << user.m_name
           << user.m_phone << user.m_address << user.m_regDateTime
           << user.m_status;
       return out;
    }

    friend QDataStream &operator>>(QDataStream &in, UserInformation &user)
    {
       in >> user.m_headPortrait >> user.m_userID >> user.m_nickname
          >> user.m_password >> user.m_sex >> user.m_birthday
          >> user.m_question >> user.m_answer >> user.m_name
          >>  user.m_phone >> user.m_address >> user.m_regDateTime
          >> user.m_status;
       return in;
    }
};

// 好友信息
struct FriendInformation
{
//    QString m_picture;
    int m_headPortrait;
    QString m_userID;
    QString m_nickname;
    QString m_groupName;
    QString m_remarkName;
    int m_status;

    FriendInformation()
    {
       m_status = OFFLINE;
       m_headPortrait = 1;
       m_groupName = GROUP_NAME_DEFAULT;
    }

    //重载输入输出操作符
    friend QDataStream & operator<< (QDataStream &out,
                                    const FriendInformation &fri)
    {
       out << fri.m_headPortrait << fri.m_userID << fri.m_nickname
           << fri.m_groupName << fri.m_remarkName << fri.m_status;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, FriendInformation &fri)
    {
       in >> fri.m_headPortrait >> fri.m_userID >> fri.m_nickname
          >> fri.m_groupName >> fri.m_remarkName >> fri.m_status;
       return in;
    }
};

// 储存在各种小窗口中填写的信息
struct TempStrings
{
    QString m_one;
    QString m_two;
    QString m_three;
    friend QDataStream & operator<< (QDataStream &out, const TempStrings &str)
    {
       out << str.m_one << str.m_two << str.m_three;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, TempStrings &str)
    {
       in >> str.m_one >> str.m_two >> str.m_three;
       return in;
    }
};

// 聊天框信息
struct ChatInformation
{
     QString m_myID;
//     QString m_myNickname;
    int m_headPortrait;
    QString m_friendID;          // 好友id
    QString m_friendNickname;    // 好友昵称
    QString m_friendRemark;      // 好友备注
    QString m_friendMark;        // 好友签名
    QString m_friendIP;          // 好友ip地址
    int m_friendStatus;

    ChatInformation()
    {
       m_friendStatus = OFFLINE;
       m_headPortrait= 1;
       m_friendMark = QString(QObject::tr("好友签名"));
    }

//    //重载输入输出操作符
//    friend QDataStream & operator<< (QDataStream &out, const ChatInformation &chat)
//    {
//       out << chat.m_headPortrait << chat.m_friendID << chat.m_friendNickname
//           << chat.m_friendRemark << chat.m_friendMark << chat.m_friendIP;
//       return out;
//    }
//    friend QDataStream & operator>> (QDataStream &in, ChatInformation &chat)
//    {
//       in >> chat.m_headPortrait >> chat.m_friendID >> chat.m_friendNickname
//          >> chat.m_friendRemark >> chat.m_friendMark >> chat.m_friendIP;
//       return in;
//    }
};

// 对话信息
struct TalkMessage
{
    int m_type;               // 消息类型
    QString m_senderID;       // 发送者ID
    QString m_senderIP;       // 发送者IP
    QString m_receiverID;     // 接收者ID
    QString m_receiverIP;     // 接收者IP
    QString m_text;           // 消息内容
    QDateTime m_dateTime;

    TalkMessage() {	m_type = 0; }

    friend QDataStream & operator<< (QDataStream &out, const TalkMessage &mes)
    {
       out << mes.m_type << mes.m_senderID << mes.m_senderIP << mes.m_receiverID
           << mes.m_receiverIP << mes.m_text << mes.m_dateTime;
       return out;
    }

    friend QDataStream & operator>> (QDataStream &in, TalkMessage &mes)
    {
       in >> mes.m_type >> mes.m_senderID >> mes.m_senderIP >> mes.m_receiverID
          >> mes.m_receiverIP >> mes.m_text >>  mes.m_dateTime;
       return in;
    }
};

// 用户登录信息
struct LoginInformation
{
    QString m_userID;
    QString m_password;
    int m_status;

    LoginInformation()
    {	m_status = OFFLINE;	}
    friend QDataStream & operator<< (QDataStream &out, const LoginInformation &li)
    {
       out << li.m_userID << li.m_password << li.m_status;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, LoginInformation &li)
    {
       in >> li.m_userID >> li.m_password >> li.m_status;
       return in;
    }
};

// 群成员信息
struct FlockMember
{
    QString m_flockID;     // 群ID
    QString m_userID;      // 用户ID
    int m_headPortrait;    // 用户头像编号
    QString m_nickname;    // 用户昵称
    int m_loginStatus;     // 用户登录状态
    QString m_remark;      // 用户群名片
    int m_flockStatus;     // 用户身份
    QDateTime m_joinDate;  // 加入时间

    friend QDataStream & operator<< (QDataStream &out, const FlockMember &flockMember)
    {
       out << flockMember.m_flockID << flockMember.m_userID
           << flockMember.m_headPortrait << flockMember.m_nickname
           << flockMember.m_loginStatus << flockMember.m_remark
           << flockMember.m_flockStatus << flockMember.m_joinDate;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, FlockMember &flockMember)
    {
       in >> flockMember.m_flockID >> flockMember.m_userID
          >> flockMember.m_headPortrait >> flockMember.m_nickname
          >> flockMember.m_loginStatus >> flockMember.m_remark
          >> flockMember.m_flockStatus >> flockMember.m_joinDate;
       return in;
    }
};

// 讨论组成员信息
struct DiscussionMember
{
    QString m_discussionID;// 讨论组ID
    QString m_userID;      // 用户ID
    int m_headPortrait;    // 用户头像编号
    QString m_nickname;    // 用户昵称
    int m_loginStatus;     // 用户登录状态
    int m_discussionStatus;// 用户身份
    QDateTime m_joinDate;  // 加入时间

    friend QDataStream & operator<< (QDataStream &out, const DiscussionMember &disMember)
    {
       out << disMember.m_discussionID << disMember.m_userID
           << disMember.m_headPortrait << disMember.m_nickname
           << disMember.m_loginStatus << disMember.m_discussionStatus
           << disMember.m_joinDate;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, DiscussionMember &disMember)
    {
       in >> disMember.m_discussionID >> disMember.m_userID
          >> disMember.m_headPortrait >> disMember.m_nickname
          >> disMember.m_loginStatus  >> disMember.m_discussionStatus
          >> disMember.m_joinDate;
       return in;
    }
};

// 群信息
struct FlockInformation
{
    QString m_flockID;
    QString m_creatorID;
    QDate m_createDate;
    QString m_flockName;
    QString m_theme;

    friend QDataStream & operator<< (QDataStream &out, const FlockInformation &flock)
    {
       out << flock.m_flockID << flock.m_creatorID << flock.m_createDate
           << flock.m_flockName << flock.m_theme;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, FlockInformation &flock)
    {
       in >> flock.m_flockID >> flock.m_creatorID >> flock.m_createDate
          >> flock.m_flockName >> flock.m_theme;
       return in;
   }
};

// 讨论组信息
struct DiscussionInformation
{
    QString m_discussionID;
    QString m_creatorID;
    QDate m_createDate;
    QString m_discussionName;
    QString m_theme;

    friend QDataStream & operator<< (QDataStream &out, const DiscussionInformation &dis)
    {
       out << dis.m_discussionID << dis.m_creatorID << dis.m_createDate
           << dis.m_discussionName << dis.m_theme;
       return out;
    }
    friend QDataStream & operator>> (QDataStream &in, DiscussionInformation &dis)
    {
       in >> dis.m_discussionID >> dis.m_creatorID >> dis.m_createDate
          >> dis.m_discussionName >> dis.m_theme;
       return in;
    }
};

// 存储临时信息的结构体，用于信号/糟
struct SaveTmpInformation
{
    int m_requestKind;
    int m_replyKind;
    QQClientSocketCtrl *m_clientSocket;

    QString m_myID;
    QString m_peerID;
    QDate m_date;
    QString m_groupName;
    QString m_groupNameF;
    UserInformation m_userInf;
    LoginInformation m_loginInf;
    FriendInformation m_friendInf;
    TalkMessage m_message;
    int m_status;
    TempStrings m_tempStr;
    QVector<TalkMessage> m_messageVec;
    QVector<FriendInformation> m_friendsVec;
    QVector<QString> m_IDVec;

    QString m_flockID;
    FlockMember m_flockMember;
    FlockInformation m_flockInf;
    QVector<FlockInformation> m_flocksVec;
    QVector<FlockMember> m_flockMembersVec;
    QString m_discussionID;
    DiscussionMember m_discussionMember;
    DiscussionInformation m_discussionInf;
    QVector<DiscussionInformation> m_discussionsVec;
    QVector<DiscussionMember> m_discussionMembersVec;

    int m_mailID;
    MailInformation m_mail;
    QVector<MailInformation>  m_inMailsVec;
    QVector<MailInformation>  m_outMailsVec;

    QString m_title;
    QString m_newTitle;

    QString m_socketID;

    QVector<TalkMessage> m_historyMessageVec;
};


//头像尺寸.
const int HEAD_BIG_SIZE = 40;
const int HEAD_SMALL_SIZE = 35;
const int HEAD_MINI_SIZE = 20;

//聊天室 工具栏尺寸
const int CHAT_WIDGET_TOOL_SIZE = 20;
const int CHAT_WIDGET_TOOL_SMALL_SIZE = 15;

const int FONT_SIZE = 2;

static const QString MAIL_ADDRESS_FORMAT = "@qq.com";

static const QString LOCAL_HISTORY_MESSAGE_PATH = "resource/history/local/";
static const QString NETWORK_HISTORY_MESSAGE_PATH = "resource/history/network/";

#endif // QQCONSTANT_H
