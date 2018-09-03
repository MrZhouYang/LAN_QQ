#include "qqdatabasectrl.h"


/************************message************************/
static const QString INSERT_MESSAGE_IN_HISTORYMESSAGE =
        "insert into ##HISTORY##MESSAGE## (senderID, receiverID, content, dateTime) "
        "values(?, ?, ?, ?);";
static const QString SEARCH_MESSAGE_IN_HISTORYMESSAGE =
        "select * from ##HISTORY##MESSAGE## where ( (senderID = ? and receiverID = ?) "
        "or (senderID = ? and receiverID = ?) )and dateTime >=? and dateTime < ?;";
static const QString EXPORT_ONE_MESSAGE_IN_HISTORY =
        "select * from ##HISTORY##MESSAGE## where (senderID = ? and receiverID = ?) or "
        "(senderID = ? and receiverID = ?) into outfile ? "
        "fields terminated by ',' optionally enclosed by '\"' escaped by '\"'"
        "lines terminated by '\\r\\n';";

static const QString EXPORT_ALL_MESSAGE_IN_HISTORY =
        "select * from ##HISTORY##MESSAGE## where senderID = ? or receiverID = ? "
        "into outfile ? "
        "fields terminated by ',' optionally enclosed by '\"' escaped by '\"'"
        "lines terminated by '\\r\\n';";

static const QString DELETE_ONE_MESSAGE_IN_HISTORY =
        "delete from ##HISTORY##MESSAGE## where (senderID = ? and receiverID = ?) "
        "or (senderID = ? and receiverID = ?)";
static const QString DELETE_ALL_MESSAGE_IN_HISTORY =
        "delete from ##HISTORY##MESSAGE## where senderID = ? or receiverID = ? ";

/********************create tables********************/
static const QString CREATE_TABLE_HISTORYMESSAGE_SQL =
"create table if not exists ##HISTORY##MESSAGE## "
"("
"messageID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
"senderID varchar(15) NOT NULL, "
"receiverID varchar(15) NOT NULL, "
"content varchar(1000) NOT NULL DEFAULT '', "
"dateTime datetime NOT NULL "
");";

QQDatabaseCtrl::QQDatabaseCtrl(const QString myID, QObject *parent) :
    QObject(parent), m_myID(myID)
{
    m_localHistoryTableName = "HistoryMessage";
    m_localHistoryTableName.append(m_myID);

    m_db = new QSqlDatabase;
    createConnection();
    createTable();
    close();
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
    if (QSqlDatabase::contains("clientIMDB"))
    {
        *m_db = QSqlDatabase::database("clientIMDB");
    }
    else
    {// 如果没有，就添加
        *m_db = QSqlDatabase::addDatabase("QSQLITE", "clientIMDB");
        m_db->setDatabaseName("clientIMDB");
    }

    if (!m_db->open())
    {
        return false;
    }
    return true;
}


/*************************************************
Function Name： close()
Description: 关闭数据库
*************************************************/
void QQDatabaseCtrl::close()
{
    if (m_db != NULL && m_db->isOpen())
        m_db->close();
}


/*************************************************
Function Name： isOpen()
Description: 是否连接着
*************************************************/
bool QQDatabaseCtrl::isOpen()
{
    return (m_db->isOpen());

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

    QString queryStr = INSERT_MESSAGE_IN_HISTORYMESSAGE;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
//    QString str =
//            "insert into HistoryMessage2014050701 (senderID, receiverID, content, dateTime) "
//            "values(?, ?, ?, ?);";

    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    qDebug() << "my sql:" << str;
//    query.prepare(INSERT_MESSAGE_IN_HISTORYMESSAGE);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(mes.m_senderID);
    query.addBindValue(mes.m_receiverID);
    query.addBindValue(QQClientFileCtrl::simplifyRichText(mes.m_text));
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
Function Name： searchHistoryMessage()
Description: 获取某日的消息记录
*************************************************/
bool QQDatabaseCtrl::searchHistoryMessage(const QString & myID, const QString & friendID,
                                          const QDate & date, QVector<TalkMessage> & mesVec)
{
    if (!createConnection())
    {
        return false;
    }
    //sql 事务
    QSqlDatabase::database().transaction();

    QString queryStr = SEARCH_MESSAGE_IN_HISTORYMESSAGE;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.prepare(SEARCH_MESSAGE_IN_HISTORYMESSAGE);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.addBindValue(date);//.toString("yyyy-MM-dd"));
    query.addBindValue(date.addDays(1));//.addDays(1).toString("yyyy-MM-dd"));

    query.exec();

    errorSQLOrder(query, "search-mes-in-HistoryMmesage");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    TalkMessage mes;
    while (query.next())
    {
        mes.m_senderID = query.value(1).toString();
        mes.m_receiverID = query.value(2).toString();
        mes.m_text = query.value(3).toString();
        mes.m_dateTime = query.value(4).toDateTime();
        mesVec.push_back(mes);
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}


/*************************************************
Function Name： searchHistoryMessage()
Description: 导出好友消息记录
*************************************************/
int QQDatabaseCtrl::exportHistoryMessageOneFriend(const QString &myID ,
                                                  const QString &friendID,
                                                  const QString &name)
{
    if (!createConnection())
    {
        return -1;
    }
    //sql 事务
//    QSqlDatabase::database().transaction();

    QString queryStr = EXPORT_ONE_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);

//    QString exportMessage = "select * from HistoryMessage into outfile ";
//    exportMessage.append("'/tmp/local_history_message").append(name).append(".xls';");
//    QString na = "/tmp/local_history_message5.xls";
//    static int i =100;
//    exportMessage.append("'/tmp/local_history_message").
//            append(QString::number(i++)).append(".xls';");
//    query.exec(exportMessage);
//    query.prepare();

//    query.prepare(EXPORT_ONE_MESSAGE_IN_HISTORY);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.addBindValue(name);

    query.exec();

    errorSQLOrder(query, "exportl-one-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}

/*************************************************
Function Name： exportHistoryMessageAll()
Description: 导出所有消息记录
*************************************************/
int QQDatabaseCtrl::exportHistoryMessageAll(const QString &myID,
                                            const QString &fileName)
{
    if (!createConnection())
    {
        return -1;
    }

    QString queryStr = EXPORT_ALL_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.prepare(EXPORT_ALL_MESSAGE_IN_HISTORY);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(myID);
    query.addBindValue(fileName);

    query.exec();

    errorSQLOrder(query, "exportl-all-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}

/*************************************************
Function Name： deleteHistoryMessageOneFriend()
Description: 删除单个好友消息记录
*************************************************/
int QQDatabaseCtrl::deleteHistoryMessageOneFriend(const QString myID,
                                                  const QString friendID)
{
    if (!createConnection())
    {
        return -1;
    }
    //sql 事务
//    QSqlDatabase::database().transaction();

    QString queryStr = DELETE_ONE_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.prepare(DELETE_ONE_MESSAGE_IN_HISTORY);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);


    query.exec();

    errorSQLOrder(query, "delete-one-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}

/*************************************************
Function Name： deleteHistoryMessageAll()
Description: 删除所有好友消息记录
*************************************************/
int QQDatabaseCtrl::deleteHistoryMessageAll(const QString myID)
{
    if (!createConnection())
    {
        return -1;
    }
    //sql 事务
//    QSqlDatabase::database().transaction();

    QString queryStr = DELETE_ALL_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(myID);
    query.exec();

    errorSQLOrder(query, "delete-all-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
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
        QString str = query.lastError().text() + "\n" + mark;
        //QMessageBox::warning(NULL, "ERROR", str);
        qDebug() << "Mysql qurey error: " << str;
        qDebug() << "query text:" << query.lastQuery();
    }
}

/*************************************************
Function Name： createTable()
Description: 创建数据库表格
*************************************************/
void QQDatabaseCtrl::createTable()
{
//    QString createHis =
//    "create table if not exists ";
//    createHis.append(m_localHistoryTableName).append(
//    " ("
//    "messageID int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY, "
//    "senderID varchar(15) NOT NULL, "
//    "receiverID varchar(15) NOT NULL, "
//    "content varchar(1000) NOT NULL DEFAULT '', "
//    "dateTime datetime NOT NULL "
//    ")ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    QString queryStr = CREATE_TABLE_HISTORYMESSAGE_SQL;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
//    query.prepare(CREATE_TABLE_HISTORYMESSAGE_SQL);
//    query.addBindValue(queryStr);
    query.exec(queryStr);
    errorSQLOrder(query, "createTable-historymessage");
}
