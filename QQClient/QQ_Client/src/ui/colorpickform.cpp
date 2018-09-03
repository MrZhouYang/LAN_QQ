#include "colorpickform.h"
#include "ui_colorpickform.h"

#include "src/model/config.h"

#include <QPushButton>
#include <QDebug>
#include <QColorDialog>
#include <QColor>
#include <QHBoxLayout>

//定义颜色标签标签宽度
#define COLOR_LABLE_SIZE 40

ColorPickForm::ColorPickForm(QWidget *parent) :
    MoveableFramelessWindow(parent),
    ui(new Ui::ColorPickForm)
{
    ui->setupUi(this);

    QVector<QString> vec = SYSTEM_CONFIG.skinColors;

    color_item_layout = new QHBoxLayout();
    color_item_layout->setContentsMargins(0,0,0,0);
    color_item_layout->setSpacing(1);
    ui->color_items->setLayout(color_item_layout);
    //初始化颜色
    foreach(QString color,vec){

        QPushButton *l = new QPushButton(this);

        l->setMinimumSize(COLOR_LABLE_SIZE,COLOR_LABLE_SIZE);
        l->setMaximumSize(COLOR_LABLE_SIZE,COLOR_LABLE_SIZE);

        //存入颜色值到属性中，在后来的点击中，可以获取次属性值，用来改变全局主题
        l->setProperty("color",color); //添加动态属性，属性名为name，值为color

        l->installEventFilter(this); //设置QPushButton的事件过滤器为本类的事件过滤器

        QString style=QString("background-color:%1;")
                .arg(color);


        l->setStyleSheet(style);

        color_item_layout->addWidget(l);

    }

    connect(this,SIGNAL(themColorChanged(QString)),this,SLOT(onThemeColorChange(QString)));
    connect(ui->color_panle_pushButton,SIGNAL(clicked()),this,SLOT(onColorPanleClick()));

    connect(ui->pushButton_minimize,SIGNAL(clicked()),this,SLOT(on_PB_minimize_clicked()));
    connect(ui->pushButton_shutdown,SIGNAL(clicked()),this,SLOT(on_PB_shutdown_clicked()));
}

ColorPickForm::~ColorPickForm()
{
    delete ui;
    delete color_item_layout;
}

void ColorPickForm::onColorButClick(QPushButton*pub)
{
    QString colorStr=pub->property("color").toString();

    if(colorStr.isEmpty()==false){

       emit this->themColorChanged(colorStr);

    }
}

bool ColorPickForm::eventFilter(QObject *sender, QEvent *e)
{

    if(e->type()==QEvent::MouseButtonPress){

        QPushButton*pub=(QPushButton*)sender;
        onColorButClick(pub);

    }

    return QWidget::eventFilter(sender,e);;
}

QWidget *ColorPickForm::getDragnWidget()
{
    return ui->color_main_top;
}

void ColorPickForm::onThemeColorChange(QString colorStr)
{
    QString style=QString("#%1{background-color:%2}")
            .arg(ui->centralwidget->objectName(),colorStr);

    ui->centralwidget->setStyleSheet(style);

}

//颜色选择对话框按钮点击槽函数
void ColorPickForm::onColorPanleClick()
{

    QColorDialog colorD;
    int rs=colorD.exec(); //QDialog::Accepted = 1  QDialog::Rejected = 0

    //如果选择了颜色
    if(rs){
        QColor color = colorD.currentColor();
        QString colorStr=QString("rgb(%1,%2,%3)")
                .arg(QString::number(color.red()),QString::number(color.green()),QString::number(color.blue()));

        emit this->themColorChanged(colorStr);
    }

}

void ColorPickForm::on_PB_shutdown_clicked()
{
    this->hide(); //由于该类是单例模式类，故调用this->deletelater()会引起程序崩溃
}

void ColorPickForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}
