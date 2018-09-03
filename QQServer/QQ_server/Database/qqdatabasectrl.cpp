#include "qqdatabasectrl.h"
#include "Encryption/IMEncryption.h"

static const QString UPDATE_STATUS_IN_USERINFORMATION_SQL =
        "update UserInformation set status = 5";
static const QString UPDATE_PASSWORD_IN_USERINFORMATION_SQL =
        "update UserInformation set password = ? "
        "where userID = ? and password = ?";
static const QString SEARCH_QUESTION_ANSWER_IN_USERINFORMATION_SQL =
        "select password, question, answer from UserInformation where userID = ?;";
static const QString SEARCH_USER_IN_USERINFORMATION_SQL =
        "select * from UserInformation where (userID = ? and password = ?)";
static const QString SEARCH_USER_IN_USERINFORMATION_ID_SQL =
        "select * from UserInformation where userID = ?";
static const QString UPDATE_USERINFORMATION_SQL =
        "update UserInformation set "
        "head = ?, nickname = ?, sex = ?, birthday = ?, "
        "name = ?, phone = ?, address = ?  where userID = ?;";

//update UserInformation set head =33, nickname = "33nick", sex = "女",
//birthday= 1991,name= 333,phone= 334,address= "33a"  where userID=201404081;

static const QString  UPDATE_STATUS_IN_USERINFORMATION_BY_ID_SQL=
        "update UserInformation set status = ? where userID = ?;";

static const QString  UPDATE_REMARKNAME_IN_USERFRIENDS_SQL=
        "update UserFriends set remarkName = ? where userID = ? and friendID = ?;";

static const QString ADD_USER_IN_USERINFORMATION_SQL =
        "insert into UserInformation (userID,head,nickname,password,sex,birthday,question,answer,name,phone,address,regDate,status) values(?,?,?,?,?,?,?,?,?,?,?,?,?)";

static const QString COUNT_REGISTERED_USERS_IN_USERINFORMATION_SQL =
        "select count(*) from UserInformation where regDate >= ? and regDate < ?";

static const QString COUNT_FLOCKS_IN_FLOCKINFORMATION_SQL =
        "select count(*) from FlockInformation where createDate >= ? and createDate < ?";

static const QString SEARCH_FRIENDS_IN_USERFRIENDS_USERINFORMATION_SQL =
        "select UserFriends.groupName, UserFriends.friendID, "
        "UserInformation.nickName, UserFriends.remarkName,"
        "UserInformation.status, UserInformation.head "
        "from UserFriends,UserInformation "
        "where UserFriends.userID = ? "
        "and UserInformation.userID = UserFriends.friendID;";

static const QString SEARCH_ID_IN_USERFRIENDS_SQL =
        "select friendID from UserFriends where userID = ?";
static const QString SEARCH_GROUPNAME_IN_USERFRIENDS_SQL =
        "select groupName from UserFriends where userID = ? and friendID = ?";
static const QString DELETE_FRIEND_IN_USERFRIENDS_SQL =
        "delete from UserFriends where "
        "(userID = ? and friendID = ?) or "
        "(userID = ? and friendID = ?)";
static const QString ADD_FRIEND_IN_USERFRIENDS_SQL =
        "insert into UserFriends(userID, friendID, groupName) values (?, ?, ?);";

static const QString SEARCH_FLOCKS_IN_FLOCKINFORMAIONT_USERFLOCKS_SQL =
        "select * from FlockInformation "
        "where FlockInformation.flockID IN ("
        "select UserFlocks.flockID from UserFlocks "
        "where UserFlocks.userID = ?);";
static const QString SEARCH_FLOCK_IN_FLOCKINFORMAIONT_SQL =
        "select * from FlockInformation where flockID = ?";

static const QString SEARCH_FLOCKMEMBERS_IN_USERINFORMATION_USERFLOCKS_SQL =
        "select UserFlocks.flockID, UserFlocks.userID, UserInformation.head, "
        "UserInformation.nickname, UserInformation.status, UserFlocks.remark, "
        "UserFlocks.status, UserFlocks.joinDate "
        "from UserInformation, UserFlocks "
        "where UserFlocks.flockID = ? and "
        "UserInformation.userID = UserFlocks.userID;";

static const QString SEARCH_FLOCKMEMBER_IN_USERINFORMATION_USERFLOCKS_SQL =
        "select UserFlocks.flockID, UserFlocks.userID, UserInformation.head, "
        "UserInformation.nickname, UserInformation.status, UserFlocks.remark, "
        "UserFlocks.status, UserFlocks.joinDate "
        "from UserInformation, UserFlocks "
        "where UserFlocks.flockID = ? and UserFlocks.userID= ? and "
        "UserInformation.userID = UserFlocks.userID;";

static const QString SEARCH_DISCUSSIONS_IN_DISCUSSIONINFORMAIONT_USERDISCUSSIONS_SQL =
        "select * from DiscussionInformation "
        "where DiscussionInformation.discussionID IN ("
        "select UserDiscussions.discussionID from UserDiscussions "
        "where UserDiscussions.userID = ?);";

static const QString SEARCH_DISCUSSION_IN_DISCUSSIONINFORMAIONT_SQL =
        "select * from DiscussionInformation where discussionID = ?";

static const QString SEARCH_DISCUSSIONMEMBERS_IN_USERINFORMATION_USERDISCUSSIONS_SQL =
        "select UserDiscussions.discussionID, UserDiscussions.userID, "
        "UserInformation.head, UserInformation.nickname, "
        "UserInformation.status,UserDiscussions.status, "
        "UserDiscussions.joinDate "
        "from UserInformation, UserDiscussions "
        "where UserDiscussions.discussionID = ? and "
        "UserInformation.userID = UserDiscussions.userID;";

static const QString SEARCH_DISCUSSIONMEMBER_IN_USERINFORMATION_USERDISCUSSIONS_SQL =
        "select UserDiscussions.discussionID, UserDiscussions.userID, "
        "UserInformation.head, UserInformation.nickname, "
        "UserInformation.status,UserDiscussions.status, "
        "UserDiscussions.joinDate "
        "from UserInformation, UserDiscussions "
        "where UserDiscussions.discussionID = ? and UserDiscussions.userID= ? and "
        "UserInformation.userID = UserDiscussions.userID;";

////////////////////////////////////////////////////////////////////////////////////

static const QString SEARCH_FLOCK_CREATORID_IN_FLOCKINFORMATION_SQL =
        "select creatorID from FlockInformation where flockID = ?";

static const QString ADD_MEMBER_IN_USERFLOCKS_SQL =
        "insert into UserFlocks(flockID, userID, status, joinDate) values (?, ?, ?, ?);";

static const QString DELETE_FLOCK_IN_FLOCKINFORMATION_SQL =
        "delete from FlockInformation where flockID = ? and creatorID = ?";

static const QString DELETE_FLOCKMEMEBER_IN_USERFLOCKS_SQL =
        "delete from UserFlocks where flockID= ? and userID = ?";

static const QString UPDATE_FLOCKINFORMATION_SQL =
        "update FlockInformation set flockName = ?, theme = ? where flockID = ?;";

static const QString UPDATE_FLOCKMEMBER_REMAKR_IN_USERFLOCKS_SQL =
        "update UserFlocks set remark = ? where flockID = ? and userID = ?";

static const QString ADD_FLOCK_IN_FLOCKINFORMATOIN_SQL =
        "insert into FlockInformation (flockID,creatorID,createDate,flockName,theme) values( ?, ?, ?, ?, ?);";
////////////////////////////////////////////////////////////////////////////////////

static const QString SEARCH_DISCUSSION_CREATORID_IN_DISCUSSIONINFORMATION_SQL =
        "select creatorID from DiscussionInformation where discussionID = ?";

static const QString ADD_MEMBER_IN_USERDISCUSSIONS_SQL =
        "insert into UserDiscussions(discussionID, userID, status, joinDate) values (?, ?, ?, ?);";

static const QString DELETE_DISCUSSION_IN_DISCUSSIONINFORMATION_SQL =
        "delete from DiscussionInformation where discussionID = ? and creatorID = ?";

static const QString DELETE_DISCUSSIONMEMEBER_IN_USERDISCUSSIONS_SQL =
        "delete from UserDiscussions where discussionID= ? and userID = ?";

static const QString UPDATE_DISCUSSIONINFORMATION_SQL =
        "update DiscussionInformation set discussionName = ?, theme = ? where discussionID = ?;";

static const QString UPDATE_DISCUSSIONMEMBER_REMAKR_IN_USERDISCUSSIONS_SQL =
        "update UserDiscussions set remark = ? where discussionID = ? and userID = ?";

static const QString ADD_DISCUSSION_IN_DISCUSSIONINFORMATOIN_SQL =
        "insert into DiscussionInformation (discussionID,creatorID,createDate,discussionName,theme) values( ?, ?, ?, ?, ?);";


////////////////////////////////////////////////////////////////////////////////////

static const QString COUNT_DATARECORD_IN_DATECOUNTER_SQL =
        "select count(*) from DateCounter where date = ?;";
static const QString INSERT_VALUES_IN_DATECOUNTER_SQL =
        "insert into DateCounter (date,userTimes,flockTimes,discussionTimes) values(?, 0, 0, 0);";

static const QString SELECT_USERTIMES_IN_DATECOUNTER_SQL =
        "select userTimes from DateCounter where date = ?;";
static const QString SELECT_FLOCKTIMES_IN_DATECOUNTER_SQL =
        "select flockTimes from DateCounter where date = ?;";
static const QString SELECT_DISCUSSIONTIMES_IN_DATECOUNTER_SQL =
        "select discussionTimes from DateCounter where date = ?;";

static const QString INCREASE_USERTIMES_IN_DATECOUNTER_SQL =
        "update DateCounter set userTimes = userTimes + 1 where date = ?;";
static const QString INCREASE_FLOCKTIMES_IN_DATECOUNTER_SQL =
        "update DateCounter set flockTimes = flockTimes + 1 where date = ?;";
static const QString INCREASE_DISCUSSIONTIMES_IN_DATECOUNTER_SQL =
        "update DateCounter set discussionTimes = discussionTimes + 1 where date = ?;";

static const QString COUNT_FLOCKMEMBER_IN_USERFLOCKS_SQL =
        "select count(*) from UserFlocks where flockID = ? and userID = ?;";

static const QString COUNT_DISCUSSIONMEMBER_IN_USERDISCUSSIONS_SQL =
        "select count(*) from UserDiscussions where discussionID = ? and userID = ?;";

/************************mail*********************/

static const QString SEARCH_IN_MAILS_IN_MAIL =
        "select * from Mail where receiverStatus = 0 and "
        "receiverID = ? and receiverAddress = ? order by time desc;";

static const QString SEARCH_OUT_MAILS_IN_MAIL =
        "select * from Mail where senderStatus = 0 and "
        "senderID = ? and senderAddress = ? order by time desc;";

static const QString INSERT_MAIL_IN_MAIL =
        "insert into Mail (senderID, senderAddress, receiverID, receiverAddress,"
        "theme, content, time) values (?, ?, ?, ?, ?, ?, ?);";
static const QString DELETE_MAIL_IN_MAIL =
        "delete from Mail where receiverID = ? and mailID = ?";
static const QString UPDATE_MAIL_IN_MAIL =
        "update Mail set receiverStatus = 1 where receiverID = ? and mailID = ?";
static const QString UPDATE_MAIL_OUT_MAIL =
        "update Mail set senderStatus = 1 where senderID = ? and mailID = ?";
static const QString SET_MAIL_READ_IN_MAIL =
        "update Mail set status = 1 where receiverID = ? and mailID = ?";

/************************group***************************/
static const QString RENAME_GROUPNAME_IN_USERFREINS =
        "update UserFriends set groupName = ? where userID = ? and groupName = ?;";
static const QString MOVE_FRIEND_IN_USERFREINS =
        "update UserFriends set groupName = ? where userID = ? "
        "and friendID = ?;";   // and groupName = ?;";

/************************message************************/
static const QString INSERT_MESSAGE_IN_HISTORYMESSAGE =
        "insert into HistoryMessage (senderID, receiverID, content, dateTime) "
        "values(?, ?, ?, ?); ";
static const QString INSERT_MESSAGE_IN_OFFLINEMESSAGE =
        "insert into OfflineMessage (kind, senderID, receiverID, content) "
        "values(?, ?, ?, ?);";
static const QString SEARCH_FRIEND_DATE_MESSAGE_IN_HISTORYMESSAGE =
        "select senderID, receiverID, content, dateTime from HistoryMessage "
        "where ( (senderID = ? and receiverID = ?) "
        "or (senderID = ? and receiverID = ?) ) "
        "and dateTime >= ? and dateTime < ?;";

/********************create tables********************/
static const QString CREATE_TABLE_USERINFORMATION_SQL = "";
static const QString CREATE_TABLE_USERFRIENDS_SQL = "";
static const QString CREATE_TABLE_TMPMESSAGE_SQL = "";

//将html格式的qstring转换为纯文本
QString simplifyRichText( QString richText )
{
    QTextDocument doc;
    doc.setHtml(richText);
    qDebug() << "say:"<< doc.toPlainText();
    return doc.toPlainText();
}

QQDatabaseCtrl::QQDatabaseCtrl(QObject *parent) : QObject(parent)
{
    m_db = new QSqlDatabase;
}

QQDatabaseCtrl::~QQDatabaseCtrl()
{
    if (m_db != NULL)
    {
        if (m_db->isOpen())
            m_db->close();
        delete m_db;
        m_db = NULL;
    }
}

/*************************************************
Function Name： createConnection()
Description: 创建连接
Input： NULL
Output：bool 表示创建结果
Changes： NULL
*************************************************/
bool QQDatabaseCtrl::createConnection()
{
    if (m_db == NULL)
        m_db = new QSqlDatabase;
    if (m_db->isOpen())
    {
        return true;
    }
    // 如果已经打开
    if (QSqlDatabase::contains("serverIMDB"))
    {
        *m_db = QSqlDatabase::database("serverIMDB");
    }
    else
    {// 如果没有，就添加
        *m_db = QSqlDatabase::addDatabase("QSQLITE", "serverIMDB");
        m_db->setDatabaseName("D:/MyQTCode(Win32)/test/sqlmodel/serverIMDB.db");
    }

//    m_db->setUserName("root");
//    m_db->setPassword("123456");
//    m_db->setHostName(QLatin1String("localhost"));
    if (!m_db->open())
    {
        qDebug()<<"serverIMDB数据库打开失败";
        return false;
    }
    else{
        qDebug()<<"serverIMDB数据库打开成功";
    }
    return true;
}

/*************************************************
Function Name： initDatabase()
Description: 初始化数据库 将所有用户的状态status设置为OFFLINE
*************************************************/
bool QQDatabaseCtrl::initDatabase()
{
    if (!createConnection())
    {
        return false;
    }

    QSqlQuery query(*m_db);
    query.exec(UPDATE_STATUS_IN_USERINFORMATION_SQL);
    errorSQLOrder(query, "initiDatabase");
    if (!query.isActive())
    {
        m_db->close();
        return false;
    }
    m_db->close();
    return true;
}

/*************************************************
Function Name： close()
Description: 关闭数据库
Input： NULL
Output：NULL
Changes： NULL
*************************************************/
void QQDatabaseCtrl::close()
{
    if (m_db != NULL && m_db->isOpen())
        m_db->close();
}


/*************************************************
Function Name： isOpen()
Description: 是否连接着
Input： NULL
Output： bool: 是否连接着
Changes： NULLUserFriends.userID
*************************************************/
bool QQDatabaseCtrl::isOpen()
{
    return (m_db->isOpen());

}


/*************************************************
Function Name： updatePassword()
Description: 修改密码
*************************************************/
int QQDatabaseCtrl::updatePassword(TempStrings & tmp)
{
    if (!createConnection())
    {
        return CHANGE_PWD_FAIL;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(UPDATE_PASSWORD_IN_USERINFORMATION_SQL);

    query.addBindValue(tmp.m_three);
    query.addBindValue(tmp.m_one);
    query.addBindValue(tmp.m_two);

    query.exec();
    errorSQLOrder(query, "update-pwd");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return CHANGE_PWD_FAIL;
    }
    qDebug() << "size:" << query.numRowsAffected();
    if (query.numRowsAffected() <= 0)
    {
        m_db->close();
        return CHANGE_PWD_FAIL;
    }

    qDebug() << "size:" << query.numRowsAffected();
//    m_db->close();
    return CHANGE_PWD_SUCCESS;
}

/*************************************************
Function Name： searchQuestionAndAnswer()
Description: 查询密保问题以及答案
*************************************************/
int QQDatabaseCtrl::searchQuestionAndAnswer(const QString &id, TempStrings &tmp)
{
    if (!createConnection())
    {
        return GET_QUESTION_ANSWER_FAIL;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_QUESTION_ANSWER_IN_USERINFORMATION_SQL);
    query.addBindValue(id);
//    query.addBindValue(IMEncryption::getInstace().
//                       getXorEncryptDecrypt(logInf.m_password, 10));
    query.exec();
    errorSQLOrder(query, "forget-pwd");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_QUESTION_ANSWER_FAIL;
    }
    if (query.size() <= 0)
    {
        m_db->close();
        return GET_QUESTION_ANSWER_FAIL;
    }
    if (query.next())
    {
        tmp.m_one = query.value(0).toString();
        tmp.m_two = query.value(1).toString();
        tmp.m_three = query.value(2).toString();


        return GET_QUESTION_ANSWER_SUCCESS;
    }
//    m_db->close();
    return GET_QUESTION_ANSWER_FAIL;
}

/*************************************************
Function Name： searchUserInUserInformation()
Description: 查询用户
*************************************************/
int QQDatabaseCtrl::searchUserInUserInformation(const LoginInformation &logInf,
                                                  UserInformation &userInf)
{
    qDebug()<<"QQDatabaseCtrl::searchUserInUserInformation 480行 根据用户名和密码查询用户信息";
    if (!createConnection())
    {
        return LOGIN_FAIL;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    //"select * from UserInformation where (userID = ? and password = ?)"
    //如果UserInformation中没有这个用户名和密码对应项，则这条语句会执行失败，那么就后面会返回LOGIN_FAIL
    query.prepare(SEARCH_USER_IN_USERINFORMATION_SQL);
    query.addBindValue(logInf.m_userID);
    query.addBindValue(logInf.m_password);
    query.exec();
    errorSQLOrder(query, "login-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        qDebug()<<"QQDatabaseCtrl::searchUserInUserInformation 501行 !query.isActive()";
        qDebug()<<query.lastError();
        m_db->close();
        return LOGIN_FAIL;
    }

    //注意对于QSqlite数据库，不支持QSqlQuery::size()，它始终返回-1
    if (query.size() <= 0)
//    {
//        qDebug()<<"QQDatabaseCtrl::searchUserInUserInformation 507行 query.size() <= 0";
//        m_db->close();
//        return LOGIN_FAIL;
//    }
    if (query.next())
    {
        userInf.m_userID = query.value(0).toString();
        userInf.m_headPortrait = query.value(1).toInt();
        userInf.m_nickname = query.value(2).toString();
        userInf.m_sex = query.value(4).toString();
        userInf.m_birthday = query.value(5).toDate();
        userInf.m_name = query.value(8).toString();
        userInf.m_phone = query.value(9).toString();
        userInf.m_address = query.value(10).toString();
        userInf.m_regDateTime = query.value(11).toDateTime();
        userInf.m_status = logInf.m_status;

        qDebug() << "searchUserInUserInformation:" << userInf.m_status;
        if (updateStatus(logInf.m_status, logInf.m_userID)){
            qDebug()<< "QQDatabaseCtrl::searchUserInUserInformation 523行 LOGIN_SUCCESS";
            return LOGIN_SUCCESS;
        }

    }
//    m_db->close();
    return LOGIN_FAIL;
}

/*************************************************
Function Name： searchFriendSimpleInformationByID()
Description: 通过id查询好友简易信息
*************************************************/
int QQDatabaseCtrl::searchFriendSimpleInformationByID(const QString &id,
                                                        FriendInformation &friInf)
{
}

/*************************************************
Function Name： searchFriendInformationByID()
Description: 通过id查询好友信息
*************************************************/
int QQDatabaseCtrl::searchFriendInformationByID(const QString &id,
                                            UserInformation &userInf)
{
    if (!createConnection())
    {
        return GET_FRIEND_FAIL;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_USER_IN_USERINFORMATION_ID_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "friend-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_FRIEND_FAIL;
    }
    if (query.size() <= 0)
    {
        m_db->close();
        return GET_FRIEND_FAIL;
    }
    if (query.next())
    {
        userInf.m_userID = query.value(0).toString();
        userInf.m_headPortrait = query.value(1).toInt();
        userInf.m_nickname = query.value(2).toString();
        userInf.m_sex = query.value(4).toString();
        userInf.m_birthday = query.value(5).toDate();
        userInf.m_name = query.value(8).toString();
        userInf.m_phone = query.value(9).toString();
        userInf.m_address = query.value(10).toString();
        userInf.m_regDateTime = query.value(11).toDateTime();
        userInf.m_status = query.value(12).toInt();
    }
//    m_db->close();
    return GET_FRIEND_SUCCESS;
}

/*************************************************
Function Name： searchMyselfInformationByID()
Description: 通过id查询自己信息
*************************************************/
int QQDatabaseCtrl::searchMyselfInformationByID(const QString &id,
                                            UserInformation &userInf)
{
    if (!createConnection())
    {
        return GET_MYSELF_FAIL;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_USER_IN_USERINFORMATION_ID_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "myself-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_MYSELF_FAIL;
    }
    if (query.size() <= 0)
    {
        m_db->close();
        return GET_MYSELF_FAIL;
    }
    if (query.next())
    {
        userInf.m_userID = query.value(0).toString();
        userInf.m_headPortrait = query.value(1).toInt();
        userInf.m_nickname = query.value(2).toString();
        userInf.m_sex = query.value(4).toString();
        userInf.m_birthday = query.value(5).toDate();
        userInf.m_name = query.value(8).toString();
        userInf.m_phone = query.value(9).toString();
        userInf.m_address = query.value(10).toString();
        userInf.m_regDateTime = query.value(11).toDateTime();
        userInf.m_status = query.value(12).toInt();
    }
//    m_db->close();
    return GET_MYSELF_SUCCESS;
}

/*************************************************
Function Name： updateMyselfInformation()
Description: 修改用户信息
*************************************************/
int QQDatabaseCtrl::updateMyselfInformation(const UserInformation &user)
{
    if (!createConnection())
    {
        return CHANGE_INFORMATION_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();
    QSqlQuery query(*m_db);
    query.prepare(UPDATE_USERINFORMATION_SQL);
    query.addBindValue(user.m_headPortrait);
    query.addBindValue(user.m_nickname);
    query.addBindValue(user.m_sex);
    query.addBindValue(user.m_birthday);
    query.addBindValue(user.m_name);
    query.addBindValue(user.m_phone);
    query.addBindValue(user.m_address);
    query.addBindValue(user.m_userID);

    query.exec();
    errorSQLOrder(query, "change-update");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CHANGE_INFORMATION_FAIL;
    }
    return CHANGE_INFORMATION_SUCCESS;
}

/*************************************************
Function Name： addUserInUserInformation()
Description: 添加用户
*************************************************/
int QQDatabaseCtrl::addUserInUserInformation(const UserInformation &userInf)
{
    if (!createConnection())
    {
        return REGISTER_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(ADD_USER_IN_USERINFORMATION_SQL);
    query.addBindValue(userInf.m_userID);
    query.addBindValue(userInf.m_headPortrait);
    query.addBindValue(userInf.m_nickname);
    query.addBindValue(userInf.m_password);
    query.addBindValue(userInf.m_sex);
    query.addBindValue(userInf.m_birthday.toString("yyyy-MM-dd"));
    query.addBindValue(userInf.m_question);
    query.addBindValue(userInf.m_answer);
    query.addBindValue(userInf.m_name);
    query.addBindValue(userInf.m_phone);
    query.addBindValue(userInf.m_address);
    query.addBindValue(userInf.m_regDateTime);//.toString("yyyy-MM-dd hh:mm:ss"));
    query.addBindValue(5);
    query.exec();
    errorSQLOrder(query, "register-add");
    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return REGISTER_FAIL;
    }

    if (!increaseUserTimes(QDate::currentDate()))
            return REGISTER_FAIL;

//    m_db->close();
    return REGISTER_SUCCESS;
}


/*************************************************
Function Name： countRegisteredInPeriod()
Description: 获取一段时间注册数量
Input： IMUser
Output： int
Changes： NULL
*************************************************/
int QQDatabaseCtrl::countRegisteredInPeriod(const QDateTime &datePre,
                                            const QDateTime &dateLater)
{
    qDebug() << "among of date:" << datePre.toString("yyyy-MM-dd hh:mm:ss")
                << dateLater.toString("yyyy-MM-dd hh:mm:ss");

    if (!createConnection())
    {
        return 0;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(COUNT_REGISTERED_USERS_IN_USERINFORMATION_SQL);
    query.addBindValue(datePre);
    query.addBindValue(dateLater);
    query.exec();
    errorSQLOrder(query, "register-count");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return 0;
    }
    int sum = 0;
    if (query.next())
        sum = query.value(0).toInt() + 1;

    //m_db->close();
    return sum;

}


/*************************************************
Function Name： countFlockInPeriod()
Description: 获取一段时间群添加数量
*************************************************/
int QQDatabaseCtrl::countFlockInPeriod(const QDateTime &datePre,
                                 const QDateTime &dateLater)
{
    qDebug() << "among of date:" << datePre.toString("yyyy-MM-dd hh:mm:ss")
                << dateLater.toString("yyyy-MM-dd hh:mm:ss");

    if (!createConnection())
    {
        return 0;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(COUNT_FLOCKS_IN_FLOCKINFORMATION_SQL);
    query.addBindValue(datePre);
    query.addBindValue(dateLater);
    query.exec();
    errorSQLOrder(query, "register-count");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return 0;
    }
    int sum = 0;
    if (query.next())
        sum = query.value(0).toInt() + 1;

    //m_db->close();
    return sum;
}


/*************************************************
Function Name： searchFriendsInformation()
Description: 获取所有好友信息
*************************************************/
int QQDatabaseCtrl::searchFriendsInformation(const QString &id,
                                              QVector<FriendInformation> &friendsVec)
{
    if (!createConnection())
    {
        return GET_ALL_FRIENDS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FRIENDS_IN_USERFRIENDS_USERINFORMATION_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "get-friends-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_ALL_FRIENDS_FAIL;
    }
    friendsVec.clear();
    while (query.next())
    {
        FriendInformation fri;

        fri.m_groupName = query.value(0).toString();
        fri.m_userID = query.value(1).toString();
        fri.m_nickname = query.value(2).toString();
        fri.m_remarkName = query.value(3).toString();
        fri.m_status = query.value(4).toInt();
        fri.m_headPortrait = query.value(5).toInt();
        friendsVec.push_back(fri);
    }
//    m_db->close();
    if (friendsVec.isEmpty())
    {
        return NO_FRIEND;
    }
    return GET_ALL_FRIENDS_SUCCESS;
}


/*************************************************
Function Name： searchFriendsID()
Description: 获取所有好友ID
*************************************************/
bool QQDatabaseCtrl::searchFriendsID(const QString &id,
                     QVector<QString> &friVec)
{
    friVec.clear();
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_ID_IN_USERFRIENDS_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "get-friends-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }

    while (query.next())
    {
        friVec.push_back(query.value(0).toString());
    }

    return true;
}

// mark: private----------------------------------------------------

/*************************************************
Function Name： errorSQLOrder()
Description: 检查SQL语句的正确性
*************************************************/
void QQDatabaseCtrl::errorSQLOrder(QSqlQuery query, QString mark)
{
    //如果SQL语句错误，就弹出警告信息
    if(!query.isActive())
    {
        QString str = query.lastError().text() + "\n " + mark;
        //QMessageBox::warning(NULL, "ERROR", str);
        qDebug() << "Mysql qurey error: " << str;
        qDebug() << "query text:" << query.lastQuery();
    }
}

/*************************************************
Function Name： updateStatus()
Description: 更新好友状态
*************************************************/
bool QQDatabaseCtrl::updateStatus(int status, const QString &id)
{
    qDebug() << "status is what :" << status;
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();
    QSqlQuery query(*m_db);
    //"update UserInformation set status = ? where userID = ?;"
    query.prepare(UPDATE_STATUS_IN_USERINFORMATION_BY_ID_SQL);
    query.addBindValue(status);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "quit-update");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

//    m_db->close();
    return true;
}

/*************************************************
Function Name： updateRemark()
Description: 更新好友备注
*************************************************/
int QQDatabaseCtrl::updateRemark(const TempStrings & tempStr)
{
    if (!createConnection())
    {
        return CHANGE_REMARK_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();
    QSqlQuery query(*m_db);
    query.prepare(UPDATE_REMARKNAME_IN_USERFRIENDS_SQL);
    query.addBindValue(tempStr.m_three);
    query.addBindValue(tempStr.m_one);
    query.addBindValue(tempStr.m_two);
    query.exec();
    errorSQLOrder(query, "update-remark");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CHANGE_REMARK_FAIL;
    }

//    m_db->close();
    return CHANGE_REMARK_SUCCESS;
}


/*************************************************
Function Name： deleteFriend()
Description: 删除好友
*************************************************/
int QQDatabaseCtrl::deleteFriend(const QString &myID, const QString &friendID,
                                   QString &groupName, QString &groupNameF)
{
    if (!createConnection())
    {
        return DELETE_FRIEND_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();
    QSqlQuery query(*m_db);

    /***********start 查询groupName***************/
    query.prepare(SEARCH_GROUPNAME_IN_USERFRIENDS_SQL);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.exec();
    errorSQLOrder(query, "search-friend-groupName");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DELETE_FRIEND_FAIL;
    }
    if (query.next())
    {
        groupName = query.value(0).toString();
    }
    query.clear();

    /***********start 查询groupNameF***************/
    query.prepare(SEARCH_GROUPNAME_IN_USERFRIENDS_SQL);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.exec();
    errorSQLOrder(query, "search-friend-groupNameF");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DELETE_FRIEND_FAIL;
    }
    if (query.next())
    {
        groupNameF = query.value(0).toString();
    }
    query.clear();

    /***********start 删除好友***************/
    query.prepare(DELETE_FRIEND_IN_USERFRIENDS_SQL);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.exec();
    errorSQLOrder(query, "delete-friend");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DELETE_FRIEND_FAIL;
    }

//    m_db->close();
    return DELETE_FRIEND_SUCCESS;
}


/*************************************************
Function Name： addFriend()
Description: 添加好友
*************************************************/
bool QQDatabaseCtrl::addFriend(const TalkMessage & mes)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(ADD_FRIEND_IN_USERFRIENDS_SQL);
    query.addBindValue(mes.m_senderID);
    query.addBindValue(mes.m_receiverID);
    query.addBindValue(GROUP_NAME_DEFAULT);
    query.exec();
    errorSQLOrder(query, "add-friend1");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }
    query.clear();
    query.prepare(ADD_FRIEND_IN_USERFRIENDS_SQL);
    query.addBindValue(mes.m_receiverID);
    query.addBindValue(mes.m_senderID);
    query.addBindValue(GROUP_NAME_DEFAULT);
    query.exec();
    errorSQLOrder(query, "add-friend2");

    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}


/*************************************************
Function Name： searchFlocksInformation()
Description: 获取某用户加入的所有群
*************************************************/
int QQDatabaseCtrl::searchFlocksInformation(
        const QString & id, QVector<FlockInformation> & flocksVec)
{
    if (!createConnection())
    {
        return GET_ALL_FLOCKS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FLOCKS_IN_FLOCKINFORMAIONT_USERFLOCKS_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "get-flocks-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_ALL_FLOCKS_FAIL;
    }

    flocksVec.clear();
    while (query.next())
    {
        FlockInformation flock;

        flock.m_flockID = query.value(0).toString();
        flock.m_creatorID = query.value(1).toString();
        flock.m_createDate = query.value(2).toDate();
        flock.m_flockName = query.value(3).toString();
        flock.m_theme = query.value(4).toString();
        flocksVec.push_back(flock);
    }
//    m_db->close();
    if (flocksVec.isEmpty())
    {
        return NO_FLOCK;
    }
    return GET_ALL_FLOCKS_SUCCESS;
}

/*************************************************
Function Name： searchFlockInformation()
Description: 获取某个群信息
*************************************************/
bool QQDatabaseCtrl::searchFlockInformation(const QString & flockID,
                                            FlockInformation & flock)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FLOCK_IN_FLOCKINFORMAIONT_SQL);
    query.addBindValue(flockID);
    query.exec();
    errorSQLOrder(query, "get-flock-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }

    if (query.next())
    {
        flock.m_flockID = query.value(0).toString();
        flock.m_creatorID = query.value(1).toString();
        flock.m_createDate = query.value(2).toDate();
        flock.m_flockName = query.value(3).toString();
        flock.m_theme = query.value(4).toString();
        return true;
    }
//    m_db->close();

    return false;
}

/*************************************************
Function Name： searchFlockMembers()
Description: 获取某群中所有的成员
*************************************************/
int QQDatabaseCtrl::searchFlockMembers(
        const QString & id, QVector<FlockMember> &flockMembersVec)
{
    if (!createConnection())
    {
        return GET_FLOCK_MEMBERS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FLOCKMEMBERS_IN_USERINFORMATION_USERFLOCKS_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "get-flock-members-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_FLOCK_MEMBERS_FAIL;
    }

    flockMembersVec.clear();
    while (query.next())
    {
        FlockMember flockMember;

        flockMember.m_flockID = query.value(0).toString();
        flockMember.m_userID = query.value(1).toString();
        flockMember.m_headPortrait = query.value(2).toInt();
        flockMember.m_nickname = query.value(3).toString();
        flockMember.m_loginStatus = query.value(4).toInt();
        flockMember.m_remark = query.value(5).toString();
        flockMember.m_flockStatus = query.value(6).toInt();
        flockMember.m_joinDate = query.value(7).toDateTime();
        flockMembersVec.push_back(flockMember);
    }
//    m_db->close();
    if (flockMembersVec.isEmpty())
    {
        return NO_FLOCK_MEMBER;
    }
    return GET_FLOCK_MEMBERS_SUCCESS;
}

/*************************************************
Function Name： searchFlockMember()
Description: 获取某群的某个成员
*************************************************/
bool QQDatabaseCtrl::searchFlockMember(const QString & flockID,
                                       const QString & userID,
                                       FlockMember & flockMember)
{

    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FLOCKMEMBER_IN_USERINFORMATION_USERFLOCKS_SQL);
    query.addBindValue(flockID);
    query.addBindValue(userID);
    query.exec();
    errorSQLOrder(query, "get-flock-member-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }

    if (query.next())
    {
        flockMember.m_flockID = query.value(0).toString();
        flockMember.m_userID = query.value(1).toString();
        flockMember.m_headPortrait = query.value(2).toInt();
        flockMember.m_nickname = query.value(3).toString();
        flockMember.m_loginStatus = query.value(4).toInt();
        flockMember.m_remark = query.value(5).toString();
        flockMember.m_flockStatus = query.value(6).toInt();
        flockMember.m_joinDate = query.value(7).toDateTime();
        return true;
    }
//    m_db->close();
    return false;
}


/*************************************************
Function Name： searchDiscussionsInformation()
Description: 获取所有用户加入的讨论组
*************************************************/
int QQDatabaseCtrl::searchDiscussionsInformation(
        const QString & id, QVector<DiscussionInformation> & discussionsVec)
{
    if (!createConnection())
    {
        return GET_ALL_DISCUSSIONS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_DISCUSSIONS_IN_DISCUSSIONINFORMAIONT_USERDISCUSSIONS_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "get-discussions-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_ALL_DISCUSSIONS_FAIL;
    }

    discussionsVec.clear();
    while (query.next())
    {
        DiscussionInformation discussion;

        discussion.m_discussionID = query.value(0).toString();
        discussion.m_creatorID = query.value(1).toString();
        discussion.m_createDate = query.value(2).toDate();
        discussion.m_discussionName = query.value(3).toString();
        discussion.m_theme = query.value(4).toString();
        discussionsVec.push_back(discussion);
    }
//    m_db->close();
    if (discussionsVec.isEmpty())
    {
        return NO_DISCUSSION;
    }
    return GET_ALL_DISCUSSIONS_SUCCESS;
}

/*************************************************
Function Name： searchDiscussionInformation()
Description: 获取某个讨论组信息
*************************************************/
bool QQDatabaseCtrl::searchDiscussionInformation(const QString & discussionID,
                                                 DiscussionInformation & discussion)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_DISCUSSION_IN_DISCUSSIONINFORMAIONT_SQL);
    query.addBindValue(discussionID);
    query.exec();
    errorSQLOrder(query, "get-discussion-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }

    if (query.next())
    {
        discussion.m_discussionID = query.value(0).toString();
        discussion.m_creatorID = query.value(1).toString();
        discussion.m_createDate = query.value(2).toDate();
        discussion.m_discussionName = query.value(3).toString();
        discussion.m_theme = query.value(4).toString();
        return true;
    }
//    m_db->close();

    return false;
}

/*************************************************
Function Name： searchDiscussionMembers()
Description: 获取某讨论组中所有的成员
*************************************************/
int QQDatabaseCtrl::searchDiscussionMembers(
        const QString & id, QVector<DiscussionMember> & discussionMembersVec)
{
    if (!createConnection())
    {
        return GET_DISCUSSION_MEMBERS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_DISCUSSIONMEMBERS_IN_USERINFORMATION_USERDISCUSSIONS_SQL);
    query.addBindValue(id);
    query.exec();
    errorSQLOrder(query, "get-discussion-members-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_DISCUSSION_MEMBERS_FAIL;
    }

    discussionMembersVec.clear();
    while (query.next())
    {
        DiscussionMember flockMember;

        flockMember.m_discussionID = query.value(0).toString();
        flockMember.m_userID = query.value(1).toString();
        flockMember.m_headPortrait = query.value(2).toInt();
        flockMember.m_nickname = query.value(3).toString();
        flockMember.m_loginStatus = query.value(4).toInt();
        flockMember.m_discussionStatus = query.value(5).toInt();
        flockMember.m_joinDate = query.value(6).toDateTime();
        discussionMembersVec.push_back(flockMember);
    }
//    m_db->close();
    if (discussionMembersVec.isEmpty())
    {
        return NO_DISCUSSION_MEMBER;
    }
    return GET_DISCUSSION_MEMBERS_SUCCESS;
}


/*************************************************
Function Name： searchDiscussionMember()
Description: 获取某讨论组中的某个成员
*************************************************/
bool QQDatabaseCtrl::searchDiscussionMember(const QString & discussionID,
                                           const QString & userID,
                                           DiscussionMember & discussionMember)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_DISCUSSIONMEMBER_IN_USERINFORMATION_USERDISCUSSIONS_SQL);
    query.addBindValue(discussionID);
    query.addBindValue(userID);
    query.exec();
    errorSQLOrder(query, "get-discussion-member-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }

    if (query.next())
    {
        discussionMember.m_discussionID = query.value(0).toString();
        discussionMember.m_userID = query.value(1).toString();
        discussionMember.m_headPortrait = query.value(2).toInt();
        discussionMember.m_nickname = query.value(3).toString();
        discussionMember.m_loginStatus = query.value(4).toInt();
//        discussionMember.m_remark = query.value(5).toString();
        discussionMember.m_discussionStatus = query.value(5).toInt();
        discussionMember.m_joinDate = query.value(6).toDateTime();
        return true;
    }
//    m_db->close();
    return false;
}

/*************************************************
Function Name： searchFlockHost()
Description: 获取群主帐号
*************************************************/
bool QQDatabaseCtrl::searchFlockHost(const QString & flockID, QString & hostID)
{
    if (!createConnection())
    {
        return false;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FLOCK_CREATORID_IN_FLOCKINFORMATION_SQL);
    query.addBindValue(flockID);
    query.exec();
    errorSQLOrder(query, "flock-creatorID-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }
    if (query.size() <= 0)
    {
        m_db->close();
        return false;
    }
    if (query.next())
    {
        hostID = query.value(0).toString();
        return true;
    }
//    m_db->close();
    return false;
}


/*************************************************
Function Name： searchDiscussionHost()
Description: 获取组长帐号
*************************************************/
bool QQDatabaseCtrl::searchDiscussionHost(const QString & discussionID,
                                          QString & hostID)
{
    if (!createConnection())
    {
        return false;
    }

    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_DISCUSSION_CREATORID_IN_DISCUSSIONINFORMATION_SQL);
    query.addBindValue(discussionID);
    query.exec();
    errorSQLOrder(query, "discussion-creatorID-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return false;
    }
    if (query.size() <= 0)
    {
        m_db->close();
        return false;
    }
    if (query.next())
    {
        hostID = query.value(0).toString();
        return true;
    }
//    m_db->close();
    return false;
}

/*************************************************
Function Name： addFlockMember()
Description: 添加群成员
*************************************************/
bool QQDatabaseCtrl::addFlockMember(const QString & flockID,
                                    const QString & memberID,
                                    const int status)
{
    qDebug()<<"QQDatabaseCtrl::addFlockMember 1588行 添加群成员";

    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);


    query.prepare(COUNT_FLOCKMEMBER_IN_USERFLOCKS_SQL);
    query.addBindValue(flockID);
    query.addBindValue(memberID);
    query.exec();

    errorSQLOrder(query, "count-flock member by id");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    int num = 0;
    if (query.next())
    {
        num = query.value(0).toInt();
    }
    if (0 != num)
        return false;

    query.prepare(ADD_MEMBER_IN_USERFLOCKS_SQL);
    query.addBindValue(flockID);
    query.addBindValue(memberID);
    query.addBindValue(status);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.exec();
    errorSQLOrder(query, "add-flock-member");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}

/*************************************************
Function Name： addDiscussionMember()
Description: 添加讨论组成员
*************************************************/
bool QQDatabaseCtrl::addDiscussionMember(const QString & discussionID,
                                        const QString & memberID,
                                        const int status)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();
    QSqlQuery query(*m_db);

    query.prepare(COUNT_DISCUSSIONMEMBER_IN_USERDISCUSSIONS_SQL);
    query.addBindValue(discussionID);
    query.addBindValue(memberID);
    query.exec();

    errorSQLOrder(query, "count-discussion member by id");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    int num = 0;
    if (query.next())
    {
        num = query.value(0).toInt();
    }
    if (0 != num)
        return false;

    query.prepare(ADD_MEMBER_IN_USERDISCUSSIONS_SQL);
    query.addBindValue(discussionID);
    query.addBindValue(memberID);
    query.addBindValue(status);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.exec();
    errorSQLOrder(query, "add-discussion-member");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}

/*************************************************
Function Name： addFlock()
Description: 添加群
*************************************************/
int QQDatabaseCtrl::addFlock(const TempStrings & tmpStr, QString & flockID)
{
    qDebug()<<"QQDatabaseCtrl::addFlock 1702行 添加群";
    int sum = getFlockTimes(QDate::currentDate());

    if (0 == sum)
    {
        return CREATE_FLOCK_FAIL;
    }

    QString id = QDate::currentDate().toString("yyyyMMdd");
    id.append(QString::number(1));
    id.append(QString::number(sum));
    flockID = id;

    if (!createConnection())
    {
        return CREATE_FLOCK_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(ADD_FLOCK_IN_FLOCKINFORMATOIN_SQL);
    query.addBindValue(id);
    query.addBindValue(tmpStr.m_one);
    query.addBindValue(QDate::currentDate().toString("yyyy-MM-dd"));
    query.addBindValue(tmpStr.m_two);
    query.addBindValue(tmpStr.m_three);
    query.exec();

    errorSQLOrder(query, "create-flock");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CREATE_FLOCK_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return CREATE_FLOCK_FAIL;
    }

    QSqlDatabase::database().commit();

    if (!addFlockMember(flockID, tmpStr.m_one, FLOCK_HOST))
        return CREATE_FLOCK_FAIL;

//    m_db->close();
    if (!increaseFlockTimes(QDate::currentDate()))
            return CREATE_FLOCK_FAIL;
    return CREATE_FLOCK_SUCCESS;
}

/*************************************************
Function Name： addDiscussion()
Description: 添加讨论组
*************************************************/
int QQDatabaseCtrl::addDiscussion(const TempStrings & tmpStr, QString & discussionID)
{
    int sum = getDiscussionTimes(QDate::currentDate());

    if (0 == sum)
    {
        return CREATE_DISCUSSION_FAIL;
    }

    QString id = QDate::currentDate().toString("yyyyMMdd");
    id.append(QString::number(2));
    id.append(QString::number(sum));
    discussionID = id;

    if (!createConnection())
    {
        return CREATE_DISCUSSION_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(ADD_DISCUSSION_IN_DISCUSSIONINFORMATOIN_SQL);
    query.addBindValue(id);
    query.addBindValue(tmpStr.m_one);
    query.addBindValue(QDate::currentDate().toString("yyyy-MM-dd"));
    query.addBindValue(tmpStr.m_two);
    query.addBindValue(tmpStr.m_three);
    query.exec();

    errorSQLOrder(query, "create-discussion");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CREATE_DISCUSSION_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return CREATE_DISCUSSION_FAIL;
    }

    QSqlDatabase::database().commit();

    if (!addDiscussionMember(discussionID, tmpStr.m_one, DISCUSSION_HOST))
        return CREATE_DISCUSSION_FAIL;

//    m_db->close();
    if (!increaseDiscussionTimes(QDate::currentDate()))
            return CREATE_DISCUSSION_FAIL;
    return CREATE_DISCUSSION_SUCCESS;

}

/*************************************************
Function Name： deleteFlock()
Description: 删除群
*************************************************/
int QQDatabaseCtrl::deleteFlock(const QString userID, const QString & flockID)
{
    if (!createConnection())
    {
        return DROP_FLOCK_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(DELETE_FLOCK_IN_FLOCKINFORMATION_SQL);
    query.addBindValue(flockID);
    query.addBindValue(userID);
    query.exec();

    errorSQLOrder(query, "delete-flock");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DROP_FLOCK_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return DROP_FLOCK_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return DROP_FLOCK_SUCCESS;
}

/*************************************************
Function Name： deleteDiscussion()
Description: 删除讨论组
*************************************************/
int QQDatabaseCtrl::deleteDiscussion(const QString userID, const QString & discussionID)
{
    if (!createConnection())
    {
        return DROP_DISCUSSION_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(DELETE_DISCUSSION_IN_DISCUSSIONINFORMATION_SQL);
    query.addBindValue(discussionID);
    query.addBindValue(userID);
    query.exec();

    errorSQLOrder(query, "delete-discussion");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DROP_DISCUSSION_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return DROP_DISCUSSION_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return DROP_DISCUSSION_SUCCESS;
}

/*************************************************
Function Name： deleteFlockMember()
Description: 删除群成员
*************************************************/
int QQDatabaseCtrl::deleteFlockMember(const QString & flockID,
                                       const QString & memberID)
{
    if (!createConnection())
    {
        return LEAVE_FLCCK_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(DELETE_FLOCKMEMEBER_IN_USERFLOCKS_SQL);
    query.addBindValue(flockID);
    query.addBindValue(memberID);
    query.exec();

    errorSQLOrder(query, "delete-flock-member");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return LEAVE_FLCCK_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return LEAVE_FLCCK_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return LEAVE_FLOCK_SUCCESS;
}

/*************************************************
Function Name： deleteDiscussionMember()
Description: 删除讨论组成员
*************************************************/
int QQDatabaseCtrl::deleteDiscussionMember(const QString & discussionID, const QString & memberID)
{
    if (!createConnection())
    {
        return LEAVE_DISCUSSION_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(DELETE_DISCUSSIONMEMEBER_IN_USERDISCUSSIONS_SQL);
    query.addBindValue(discussionID);
    query.addBindValue(memberID);
    query.exec();

    errorSQLOrder(query, "delete-discussion-member");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return LEAVE_DISCUSSION_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return LEAVE_DISCUSSION_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return LEAVE_DISCUSSION_SUCCESS;
}


/*************************************************
Function Name： updateFlockInformation()
Description: 更新群信息
*************************************************/
int QQDatabaseCtrl::updateFlockInformation(const FlockInformation & flock)
{
    if (!createConnection())
    {
        return CHANGE_FLOCK_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(UPDATE_FLOCKINFORMATION_SQL);

    query.addBindValue(flock.m_flockName);
    query.addBindValue(flock.m_theme);
    query.addBindValue(flock.m_flockID);

    query.exec();

    errorSQLOrder(query, "update-flock-inf");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CHANGE_FLOCK_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return CHANGE_FLOCK_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return CHANGE_FLOCK_SUCCESS;
}


/*************************************************
Function Name： updateDiscussionInformation()
Description: 更新讨论组信息
*************************************************/
int QQDatabaseCtrl::updateDiscussionInformation(const DiscussionInformation & discussion)
{
    if (!createConnection())
    {
        return CHANGE_DISCUSSION_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(UPDATE_DISCUSSIONINFORMATION_SQL);

    query.addBindValue(discussion.m_discussionName);
    query.addBindValue(discussion.m_theme);
    query.addBindValue(discussion.m_discussionID);

    query.exec();

    errorSQLOrder(query, "update-discussion-inf");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CHANGE_DISCUSSION_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return CHANGE_DISCUSSION_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return CHANGE_DISCUSSION_SUCCESS;
}


/*************************************************
Function Name： updateFlockMemberRemark()
Description: 更新群成员名片
*************************************************/
int QQDatabaseCtrl::updateFlockMemberRemark(const TempStrings & tmpStr)
{
    if (!createConnection())
    {
        return  CHANGE_FLOCK_REMARK_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(UPDATE_FLOCKMEMBER_REMAKR_IN_USERFLOCKS_SQL);

    query.addBindValue(tmpStr.m_three); // remark
    query.addBindValue(tmpStr.m_one);   // flockID
    query.addBindValue(tmpStr.m_two);   // userID

    query.exec();

    errorSQLOrder(query, "update-flock-member-remark");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return CHANGE_FLOCK_REMARK_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return CHANGE_FLOCK_REMARK_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return CHANGE_FLOCK_REMARK_SUCCESS;
}


/*************************************************
Function Name： insertValuesInDateCounter()
Description: 插入DateCounterb表某日的数据项
*************************************************/
bool QQDatabaseCtrl::insertValuesInDateCounter(const QDate & date)
{
    if (!createConnection())
    {
        return  false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(COUNT_DATARECORD_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "count-datecounter");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

//    if (0 >= query.numRowsAffected())
//    {
//        return false;
//    }

    int num = 0;
    if (query.next())
    {
        num = query.value(0).toInt();
    }
    if (num == 0)
    {
        query.prepare(INSERT_VALUES_IN_DATECOUNTER_SQL);
        query.addBindValue(date.toString("yyyy-MM-dd"));
        query.exec();

        errorSQLOrder(query, "insert datecounter");
        if (!query.isActive())
        {
            qDebug() << "QUERY_FAIL::" << query.lastError().text();
            m_db->close();
            return false;
        }

        if (0 >= query.numRowsAffected())
        {
            return false;
        }
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}

/*************************************************
Function Name： updateFlockMemberRemark()
Description: 获取某日用户注册数量+1
*************************************************/
int QQDatabaseCtrl::getUserTimes(const QDate & date)
{
    if (!insertValuesInDateCounter(QDate::currentDate()))
        return 0;

    if (!createConnection())
    {
        return  0;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SELECT_USERTIMES_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "select-usertimes");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

//    if (0 >= query.numRowsAffected())
//    {
//        return 0;
//    }

    int num = 0;
    if (query.next())
    {
        num = query.value(0).toInt();
    }
    QSqlDatabase::database().commit();

    return 1 + num;
}

/*************************************************
Function Name： getFlockTimes()
Description: 获取某日新建群数量+1
*************************************************/
int QQDatabaseCtrl::getFlockTimes(const QDate & date)
{
    if (!insertValuesInDateCounter(QDate::currentDate()))
        return 0;

    if (!createConnection())
    {
        return  0;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SELECT_FLOCKTIMES_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "select-flocktimes");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

//    if (0 >= query.numRowsAffected())
//    {
//        return 0;
//    }

    int num = 0;
    if (query.next())
    {
        num = query.value(0).toInt();
    }
    QSqlDatabase::database().commit();

    return 1 + num;
}

/*************************************************
Function Name： getDiscussionTimes()
Description: 获取某日新建讨论组数量+1
*************************************************/
int QQDatabaseCtrl::getDiscussionTimes(const QDate & date)
{
    if (!insertValuesInDateCounter(QDate::currentDate()))
        return 0;

    if (!createConnection())
    {
        return  0;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SELECT_DISCUSSIONTIMES_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "select-discussiontimes");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

//    if (0 >= query.numRowsAffected())
//    {
//        return 0;
//    }

    int num = 0;
    if (query.next())
    {
        num = query.value(0).toInt();
    }
    QSqlDatabase::database().commit();

    return 1 + num;
}


/*************************************************
Function Name： increaseUserTimes()
Description: 增加某日用户注册数量
*************************************************/
bool QQDatabaseCtrl::increaseUserTimes(const QDate & date)
{
    if (!createConnection())
    {
        return  0;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(INCREASE_USERTIMES_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "increase-usertimes");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }
    QSqlDatabase::database().commit();
    return true;
}

/*************************************************
Function Name： increaseFlockTimes()
Description: 增加某日新建群数量
*************************************************/
bool QQDatabaseCtrl::increaseFlockTimes(const QDate & date)
{
    if (!createConnection())
    {
        return  0;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(INCREASE_FLOCKTIMES_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "increase-flocktimes");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }
    QSqlDatabase::database().commit();
    return true;
}

/*************************************************
Function Name： increaseDiscussionTimes()
Description: 增加某日新建讨论组数量
*************************************************/
bool QQDatabaseCtrl::increaseDiscussionTimes(const QDate & date)
{
    if (!createConnection())
    {
        return  0;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(INCREASE_DISCUSSIONTIMES_IN_DATECOUNTER_SQL);
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.exec();

    errorSQLOrder(query, "increase-discussiontimes");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }
    QSqlDatabase::database().commit();
    return true;
}


/*************************************************
Function Name： searchInMails()
Description: 获取收件箱
*************************************************/
int QQDatabaseCtrl::searchInMails(const QString & id,
                                  QVector<MailInformation> & mailsVec)
{
    if (!createConnection())
    {
        return GET_IN_MAILS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_IN_MAILS_IN_MAIL);
    query.addBindValue(id);
    query.addBindValue(MAIL_ADDRESS_FORMAT);
    query.exec();
    errorSQLOrder(query, "get-mails-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_IN_MAILS_FAIL;
    }

    mailsVec.clear();
    MailInformation mail;
    while (query.next())
    {
        mail.m_mailID = query.value(0).toInt();
        mail.m_senderAddress = query.value(1).toString();
//        mail. = query.value(2).toString();
        mail.m_receiverAddress = query.value(3).toString();
//        mail. = query.value(4).toString();
        mail.m_theme = query.value(5).toString();
        mail.m_content = query.value(6).toString();
        mail.m_dateTime = query.value(7).toDateTime();
        mail.m_status = query.value(8).toInt();

        mailsVec.push_back(mail);
    }

    return GET_IN_MAILS_SUCCESS;
}


/*************************************************
Function Name： searchOutMails()
Description: 获取发件箱
*************************************************/
int QQDatabaseCtrl::searchOutMails(const QString & id,
                                   QVector<MailInformation> & mailsVec)
{
    if (!createConnection())
    {
        return GET_OUT_MAILS_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_OUT_MAILS_IN_MAIL);
    query.addBindValue(id);
    query.addBindValue(MAIL_ADDRESS_FORMAT);
    query.exec();
    errorSQLOrder(query, "get-mails-search");

    QSqlDatabase::database().commit();

    if (!query.isActive())
    {
        m_db->close();
        return GET_OUT_MAILS_FAIL;
    }

    mailsVec.clear();
    while (query.next())
    {
        MailInformation mail;

        mail.m_mailID = query.value(0).toInt();
        mail.m_senderAddress = query.value(1).toString();
//        mail. = query.value(2).toString();
        mail.m_receiverAddress = query.value(3).toString();
//        mail. = query.value(4).toString();
        mail.m_theme = query.value(5).toString();
        mail.m_content = query.value(6).toString();
        mail.m_dateTime = query.value(7).toDateTime();
//        mail.m_status = query.value(8).toInt();

        mailsVec.push_back(mail);
    }

    return GET_OUT_MAILS_SUCCESS;
}


/*************************************************
Function Name： deleteMail()
Description: 删除邮件
*************************************************/
bool QQDatabaseCtrl::deleteMail(const QString & receiverID, const int mailID)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(DELETE_MAIL_IN_MAIL);
    query.addBindValue(receiverID);
    query.addBindValue(mailID);
    query.exec();

    errorSQLOrder(query, "delete-mail");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}

/*************************************************
Function Name： deleteInMail()
Description: 删除收件箱邮件
*************************************************/
int QQDatabaseCtrl::deleteInMail(const QString & receiverID, const int mailID)
{
    if (!createConnection())
    {
        return DELETE_IN_MAIL_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(UPDATE_MAIL_IN_MAIL);
    query.addBindValue(receiverID);
    query.addBindValue(mailID);
    query.exec();

    errorSQLOrder(query, "delete-in-mail");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DELETE_IN_MAIL_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return DELETE_IN_MAIL_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return DELETE_IN_MAIL_SUCCESS;
}

/*************************************************
Function Name： deleteOutMail()
Description: 删除发件箱邮件
*************************************************/
int QQDatabaseCtrl::deleteOutMail(const QString & senderID, const int mailID)
{
    if (!createConnection())
    {
        return DELETE_OUT_MAIL_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(UPDATE_MAIL_OUT_MAIL);
    query.addBindValue(senderID);
    query.addBindValue(mailID);
    query.exec();

    errorSQLOrder(query, "delete-out-mail");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return DELETE_OUT_MAIL_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return DELETE_OUT_MAIL_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return DELETE_OUT_MAIL_SUCCESS;
}


/*************************************************
Function Name： insertMail()
Description: 插入新邮件
*************************************************/
int QQDatabaseCtrl::insertMail(MailInformation & mail)
{
    if (!createConnection())
    {
        return SEND_MAIL_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(INSERT_MAIL_IN_MAIL);
    query.addBindValue(mail.m_senderAddress);
    query.addBindValue(MAIL_ADDRESS_FORMAT);
    query.addBindValue(mail.m_receiverAddress);
    query.addBindValue(MAIL_ADDRESS_FORMAT);
    query.addBindValue(mail.m_theme);
    query.addBindValue(mail.m_content);
    query.addBindValue(mail.m_dateTime);
    query.exec();

    errorSQLOrder(query, "insert-mail");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return SEND_MAIL_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return SEND_MAIL_FAIL;
    }
    QSqlDatabase::database().commit();

    query.exec("select LAST_INSERT_ID() from Mail");
    if (query.next())
    {
        mail.m_mailID = query.value(0).toInt();
    }

//    m_db->close();
    return SEND_MAIL_SUCCESS;
}


/*************************************************
Function Name： setMailRead()
Description: 更新邮件，设置为已读
*************************************************/
bool QQDatabaseCtrl:: setMailRead(const QString & receiverID, const int mailID)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SET_MAIL_READ_IN_MAIL);
    query.addBindValue(receiverID);
    query.addBindValue(mailID);
    query.exec();

    errorSQLOrder(query, "set-mail-read");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}


/*************好友分组********************/


/*************************************************
Function Name： moveFriendToGroup()
Description: 移动好友至其他分组
*************************************************/
int QQDatabaseCtrl::moveFriendToGroup(const QString & myID, const QString & friendID,
                      const QString & title, const QString & newTitle)
{
    if (!createConnection())
    {
        return MOVE_FRIEND_BOX_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(MOVE_FRIEND_IN_USERFREINS);
    query.addBindValue(newTitle);
    query.addBindValue(myID);
    query.addBindValue(friendID);
//    query.addBindValue(title);
    query.exec();

    errorSQLOrder(query, "move-friend-to-group");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return MOVE_FRIEND_BOX_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return MOVE_FRIEND_BOX_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return MOVE_FRIEND_BOX_SUCCESS;
}


/*************************************************
Function Name： renameGroup()
Description: 重命名分组
*************************************************/
int QQDatabaseCtrl::renameGroup(const QString & id, const QString & title,
                const QString & newTitle)
{
    if (!createConnection())
    {
        return RENAME_BOX_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(RENAME_GROUPNAME_IN_USERFREINS);
    query.addBindValue(newTitle);
    query.addBindValue(id);
    query.addBindValue(title);
    query.exec();

    errorSQLOrder(query, "rename-group");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return RENAME_BOX_FAIL;
    }

    if (0 >= query.numRowsAffected())
    {
        return RENAME_BOX_FAIL;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return RENAME_BOX_SUCCESS;
}

/*************************************************
Function Name： addHistoryMessage()
Description: 存储历史记录
*************************************************/
bool QQDatabaseCtrl::addHistoryMessage(const TalkMessage & mes)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(INSERT_MESSAGE_IN_HISTORYMESSAGE);
    query.addBindValue(mes.m_senderID);
    query.addBindValue(mes.m_receiverID);
    query.addBindValue(simplifyRichText(mes.m_text));
    query.addBindValue(mes.m_dateTime);


    query.exec();

    errorSQLOrder(query, "inser-mes-to-HistoryMmesage");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}

/*************************************************
Function Name： addOfflineMessage()
Description: 存储离线记录
*************************************************/
bool QQDatabaseCtrl::addOfflineMessage(const TalkMessage & mes)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(INSERT_MESSAGE_IN_OFFLINEMESSAGE);
    query.addBindValue(mes.m_type);
    query.addBindValue(mes.m_senderID);
    query.addBindValue(mes.m_receiverID);
    query.addBindValue(mes.m_text);
    query.exec();

    errorSQLOrder(query, "inser-mes-to-Offline-Mmesage");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}


/*************************************************
Function Name： searchHistoryMessageOneFriendOneDate()
Description: 获取用户的某日与某位好友的聊天记录
*************************************************/
int QQDatabaseCtrl::searchHistoryMessageOneFriendOneDate(
        const QString & myID, const QString &friendID,
        const QDate & date, QVector<TalkMessage> & mesVec)
{
    if (!createConnection())
    {
        return GET_HISTORY_MESSAGE_FAIL;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QSqlQuery query(*m_db);
    query.prepare(SEARCH_FRIEND_DATE_MESSAGE_IN_HISTORYMESSAGE);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.addBindValue(date);
    query.addBindValue(date.addDays(1));
    query.exec();

    errorSQLOrder(query, "search-history-Mmesage-friend-date");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return GET_HISTORY_MESSAGE_FAIL;
    }

    mesVec.clear();
//    if (0 >= query.numRowsAffected())
//    {
//        return NO_HISTORY_MESSAGE;
//    }
    TalkMessage mes;
    while (query.next())
    {
        mes.m_senderID = query.value(0).toString();
        mes.m_receiverID = query.value(1).toString();
        mes.m_text = query.value(2).toString();
        mes.m_dateTime = query.value(3).toDateTime();
        mesVec.push_back(mes);
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return GET_HISTORY_MESSAGE_SUCCESS;
}

