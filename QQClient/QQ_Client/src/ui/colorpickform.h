#ifndef COLORPICKFORM_H
#define COLORPICKFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include "src/model/singleton.h"

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

namespace Ui {
class ColorPickForm;
}

class ColorPickForm : public MoveableFramelessWindow,public Singleton<ColorPickForm>
{
    Q_OBJECT

    friend class Singleton<ColorPickForm>;//必须为友元类，否则父类无法访问子类的构造函数

public:
    ~ColorPickForm();

protected:
    ColorPickForm(QWidget *parent = 0);

    QWidget* getDragnWidget();

private:
    Ui::ColorPickForm *ui;

    QHBoxLayout *color_item_layout;

signals:
    /**
     * @brief 主题颜色改变事件
     * @param colorStr
     */
    void themColorChanged(QString colorStr);

private slots:
    void onColorButClick(QPushButton *pub);
    //定义事件过滤，用来扑捉主题颜色点击事件
    bool eventFilter(QObject *sender, QEvent *e);

    void onThemeColorChange(QString colorStr);

    //调色盘按钮点击
    void onColorPanleClick();

    void on_PB_shutdown_clicked();
    void on_PB_minimize_clicked();
};

#define MY_COLOR_PICK_FORM ColorPickForm::getInstance()

#endif // COLORPICKFORM_H
