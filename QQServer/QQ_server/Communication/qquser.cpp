#include "qquser.h"

QQUser::QQUser(QObject *parent) : QObject(parent)
{

}

QQUser::QQUser(QString id, const QString &nick, const QString &pwd, const QString &sex,
               const QDate birth, const QString &name, const QString &addr,
               const QString &phone, const QString &ques, const QString &ans,
               const QDateTime regDate, const int status)
{
    m_userID = id;
    m_nickname = nick;
    m_password = pwd;
    m_sex = sex;
    m_birthday = birth;
    m_question = ques;
    m_answer = ans;
    m_name = name;
    m_phone = phone;
    m_address = addr;
    m_regDateTime = regDate;
    m_status = status;
}

/********************* bgein getXX()****************************/
QString QQUser::getUserID() const { return m_userID; }

QString QQUser::getNickname() const { return m_nickname; }

QString QQUser::getPassword() const { return m_password; }

QString QQUser::getSex() const { return m_sex; }

QDate QQUser::getBirthday() const { return m_birthday;}

QString QQUser::getQuestion() const { return m_question; }

QString QQUser::getAnswer() const { return m_answer; }

QString QQUser::getName() const { return m_name; }

QString QQUser::getPhone() const { return m_phone; }

QString QQUser::getAddress() const { return m_address; }

QDateTime QQUser::getRegDateTime() const { return m_regDateTime; }

int QQUser::getStatus() const {return m_status; }

/********************* end getXX()******************************/

/********************* bgein setXX()****************************/
 void QQUser::setUserID(const QString &id) { m_userID = id; }
 void QQUser::setNickname(const QString &nick) { m_nickname = nick; }
 void QQUser::setPassword(const QString &pwd) { m_password = pwd; }
 void QQUser::setSex(const QString &sex) { m_sex = sex; }
 void QQUser::setBirthday(const QDate &birth) { m_birthday = birth; }
 void QQUser::setQusetion(const QString &ques) { m_question = ques; }
 void QQUser::setAnswer(const QString &ans) { m_answer = ans; }
 void QQUser::setName(const QString &name) { m_name = name; }
 void QQUser::setPhone(const QString &phone) { m_phone = phone; }
 void QQUser::setAddress(const QString & add) { m_address = add; }
 void QQUser::setRegDateTime(const QDateTime &date) { m_regDateTime = date; }
 void QQUser::setStatus(const int status) { m_status = status; }
/********************* end setXX()******************************/


 QDataStream &operator<<(QDataStream &out, const QQUser &user)
 {
     out << user.m_userID << user.m_nickname << user.m_password
         << user.m_sex << user.m_birthday << user.m_question
         << user.m_answer << user.m_name << user.m_phone
         << user.m_address << user.m_regDateTime << user.m_status;
     return out;
 }

 QDataStream &operator>>(QDataStream &in, QQUser &user)
 {
     in >> user.m_userID >> user.m_nickname >> user.m_password
        >> user.m_sex >> user.m_birthday >> user.m_question
        >> user.m_answer >> user.m_name >>  user.m_phone
        >> user.m_address >> user.m_regDateTime >> user.m_status;
     return in;
 }
