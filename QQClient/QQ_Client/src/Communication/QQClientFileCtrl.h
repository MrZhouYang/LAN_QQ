/*********************************************
File Name： QQClientFileCtrl.h
Description： xml文件读写
Changes：
********************************************/
#ifndef QQCLIENTFILECTRL_H
#define QQCLIENTFILECTRL_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDataStream>
#include <QDir>
#include <QFile>
#include <qdebug.h>
#include <QRegExp>
#include <QTextDocument>
#include <QTextBrowser>
class QXmlStreamWriter;
class QXmlStreamReader;
class QTextBrowser;

class QQClientFileCtrl : public QObject
{
    Q_OBJECT
public:
    explicit QQClientFileCtrl(QObject *parent = 0);

    // 删除文件
    static bool remove(const QString &filename);

    static QString simplifyRichText(QString richText);

    static void saveTalkHistory(const QString filePath, const QString fileName,
                                const QTextBrowser *messagaShow);
    static void readTalkHistory(const QString filePath, const QString fileName,
                                QTextBrowser *messagaShow);

signals:
    
public slots:

private:


};

#endif // QQCLIENTFILECTRL_H
