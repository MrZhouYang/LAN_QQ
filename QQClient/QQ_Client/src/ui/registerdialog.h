#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "qqConstant.h"
#include "QQRegisterCtrl.h"
#include "IMEncryption.h"


namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

    void setServer(QString ip, int port);

private:
    Ui::RegisterDialog *ui;

    QQRegisterCtrl * m_regCtrl;
    UserInformation m_userInf;

public slots:
    void resetBtnSure(bool );    // 重置确定按钮

private slots:
    void PB_sure_clicked();
    void PB_cancle_clicked();
};

#endif // REGISTERDIALOG_H
