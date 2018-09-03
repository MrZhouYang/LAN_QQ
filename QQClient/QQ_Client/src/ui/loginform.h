#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "registerdialog.h"
#include <QString>
#include "loginsetting.h"
#include "QQLoginCtrl.h"
#include "mainform.h"


namespace Ui {
class LoginForm;
}

class LoginForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

protected:
    QWidget* getDragnWidget();

    bool eventFilter(QObject *object, QEvent *e);

private slots:
    void doLoginButClick();//登录按钮点击
    void setServer(QString ip, int port);

public slots:
    //设置状态标签,控制是否弹出主界面
    void setLabelStatus(const QString &mes, bool isLogin,const UserInformation *me);


signals:


private:
    Ui::LoginForm *ui;

    QQLoginCtrl *m_loginCtrl; // 用于控制登录


    int m_status;//登录状态

};

#endif // LOGINFORM_H
