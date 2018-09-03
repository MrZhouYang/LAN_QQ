#ifndef LOGINSETTING_H
#define LOGINSETTING_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class LoginSetting;
}

class LoginSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LoginSetting(QWidget *parent = 0);
    ~LoginSetting();

signals:
    void server_setting(QString ip,int port);

private:
    Ui::LoginSetting *ui;

private slots:
    void PBsure();
    void PBcancel();
};

#endif // LOGINSETTING_H
