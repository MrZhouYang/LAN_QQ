/*********************************************
File Name： IMEncryption.h
Description： 加密解密
Changes：
********************************************/

#ifndef IMENCRYPTION_H
#define IMENCRYPTION_H

#include <QAtomicPointer>
#include <QMutexLocker>
#include <QReadWriteLock>
#include <QString>
#include <QDebug>
#include <QTextCodec>

class IMEncryption
{
public:
    // 用户获取实例，返回实例的引用
    static IMEncryption& getInstace(void);

    // 使用异或运算加密
    QString getXorEncryptDecrypt(const QString &, const char &);
    // QByteArray 转 QString
    QString byteToQString(const QByteArray &byte);
    // QString 转 QByteArray
    QByteArray qstringToByte(const QString &strInfo);

private:
    IMEncryption(){}//禁止构造函数。
    IMEncryption(const  IMEncryption &);//禁止拷贝构造函数。
    IMEncryption & operator =(const  IMEncryption &);//禁止赋值拷贝函数。

    QReadWriteLock m_internalMutex;//函数使用的读写锁。
    static  QMutex s_mutex;//实例互斥锁。
    static  QAtomicPointer<IMEncryption> s_instance; //使用原子指针,默认初始化为0
};

#endif // IMENCRYPTION_H
