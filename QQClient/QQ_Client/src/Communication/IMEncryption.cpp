#include "IMEncryption.h"

QMutex IMEncryption::s_mutex;//实例互斥锁。
QAtomicPointer<IMEncryption> IMEncryption::s_instance = 0; //使用原子指针,默认初始化为0

IMEncryption& IMEncryption::getInstace(void)
{
    #ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
    // 运行时检测
    if (!QAtomicPointer::isTestAndSetNative())
    {
        qDebug() << "Error: TestAndSetNative not supported!";
    }
    #endif

    //使用双重检测。
    //testAndSetOrders操作保证在原子操作前和后的的内存访问不会被重新排序。

    if (s_instance.testAndSetOrdered(0, 0))//第一次检测
    {
        QMutexLocker locker(&s_mutex);//加互斥锁。
        s_instance.testAndSetOrdered(0, new  IMEncryption);//第二次检测。
    }
    return  *s_instance;
}

QString IMEncryption::getXorEncryptDecrypt(const QString &str, const char &key)
{
    QString result;
    QByteArray bs = qstringToByte(str);

    for(int i=0; i<bs.size(); i++)
    {
        bs[i] = bs[i] ^ key;
    }

    result = byteToQString(bs);
    return result;
}


QString IMEncryption::byteToQString(const QByteArray &byte)
{
    QString result;
    if (byte.size() > 0)
    {
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        result = codec->toUnicode(byte);
    }

    return result;
}

QByteArray IMEncryption::qstringToByte(const QString &strInfo)
{
    QByteArray result;
    if (strInfo.length() > 0)
    {
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        result = codec->fromUnicode(strInfo);
    }
    return result;
}
