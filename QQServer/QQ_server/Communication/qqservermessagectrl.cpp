#include "qqservermessagectrl.h"

QQServerMessageCtrl::QQServerMessageCtrl(QObject *parent) : QObject(parent)
{
    m_modelID = new QStringListModel(this);
    m_modelID->setStringList(m_listID);
    m_listViewID = new QListView;
    m_listViewID->setModel(m_modelID);
    // 不可编辑
    m_listViewID->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_modelAddress = new QStringListModel(this);
    m_modelAddress->setStringList(m_listAddress);
    m_listViewAddress = new QListView;
    m_listViewAddress->setModel(m_modelAddress);
    // 不可编辑
    m_listViewAddress->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QQServerMessageCtrl::~QQServerMessageCtrl(){
    if (m_listViewID != NULL)
    {
        delete m_listViewID;
        m_listViewID = NULL;
    }
    if (m_listViewAddress != NULL)
    {
        delete m_listViewAddress;
        m_listViewAddress = NULL;
    }
}

/*************************************************
Function Name： runServer()
Description: 用于启动服务器
Input： NULL
Output：NULL
Changes： NULL
*************************************************/
void QQServerMessageCtrl::runServer()
{
    //创建QQTcpServer 关联TcpServer的相应信号
   m_tcpServer = new QQTcpServer(this);
   connect(m_tcpServer, SIGNAL(haveNewID(QString)),
           this, SLOT(insertIDData(QString)));
   connect(m_tcpServer, SIGNAL(haveNewAddress(QString)),
           this, SLOT(insertAddressData(QString)));

   connect(m_tcpServer, SIGNAL(haveLeftID(QString)),
           this, SLOT(deleteIDData(QString)));
   connect(m_tcpServer, SIGNAL(haveLeftAddress(QString)),
           this, SLOT(deleteAddressData(QString)));

   //监听端口1234
   if (!m_tcpServer->listen(QHostAddress::Any, 1234))
   {
       qDebug("run fail");
       QMessageBox::critical(NULL, tr("IM Server"),
                             tr("Unable to start the server: %1")
                             .arg(m_tcpServer->errorString()));
       exit(EXIT_FAILURE);
   }
   //数据库初始化
   m_databaseCtrl.initDatabase();
}

/*************************************************
Function Name： getIDListView()
Description: 获取ID listiew
*************************************************/
QListView * QQServerMessageCtrl::getIDListView(){
    return m_listViewID;
}

/*************************************************
Function Name： getAddressListView()
Description: 获取Address listiew
*************************************************/
QListView * QQServerMessageCtrl::getAddressListView()
{
    return m_listViewAddress;
}

/*************************************************
Function Name： insertIDData()
Description: 插入ID数据
*************************************************/
void QQServerMessageCtrl::insertIDData(const QString & id)
{
    m_listID.append(id);
    m_modelID->setStringList(m_listID);
}

/*************************************************
Function Name： deleteIDData()
Description: 删除ID数据
*************************************************/
void QQServerMessageCtrl::deleteIDData(const QString &id)
{
    int index = m_listID.indexOf(id);
    m_listID.removeAt(index);
    m_modelID->removeRow(index);
}

/*************************************************
Function Name： insertAddressData()
Description: 插入Address数据
*************************************************/
void QQServerMessageCtrl::insertAddressData(const QString &address)
{
    m_listAddress.append(address);
    m_modelAddress->setStringList(m_listAddress);
}

/*************************************************
Function Name： deleteAddressData()
Description: 删除Address数据
*************************************************/
void QQServerMessageCtrl::deleteAddressData(const QString & address)
{
    int index = m_listAddress.indexOf(address);
    m_listAddress.removeAt(index);
    m_modelAddress->removeRow(index);
}
