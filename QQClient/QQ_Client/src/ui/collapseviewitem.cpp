#include "collapseviewitem.h"
#include "ui_collapseviewitem.h"

#include "litteriem.h"

#include <QDebug>
#include <QTime>


CollapseViewItem::CollapseViewItem(QString titleText, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollapseViewItem)
{
    ui->setupUi(this);

    if(ui->item_con->layout()!=0 )
    {
        qDebug()<<"ui->item_con->layout已经存在";
    }

    //给litteriem区域widget添加布局
    item_con_layout = new QVBoxLayout(this);
    item_con_layout->setContentsMargins(0,0,0,0);//设置上下左右的边距均为0
    item_con_layout->setSpacing(0);//设置布局内的窗口小部件之间的间距为0
    ui->item_con->setLayout(item_con_layout);


    ui->label->setProperty("slected",!ui->item_con->isVisible());

    this->setTitleText(titleText);

//    //根据时间制作随机种子
//    QTime time;
//    time = QTime::currentTime();
//    qsrand(time.msec()+time.second()*1000);

//    //随机产生好友数目
//    int personNumber = qrand()%(MAX_PERSON_PIC_NUM)+1;
//    qDebug()<<"personNumber:"<<personNumber;

//    for(int i=0;i<personNumber;++i)
//    {
//        //随机选择好友头像
//        QString picPath = QString(":/media/person/media/person/%1.jpg")
//                .arg(QString::number(qrand()%(MAX_PERSON_PIC_NUM)+1));
//        addSubItem(new LitterIem(picPath,this));
//    }

//    //随机产生上线好友数目
//    int onlinePerson=qrand()%personNumber;

//    titleText = QString("%1 (%2/%3)")
//            .arg(titleText).arg(QString::number(onlinePerson)).arg(QString::number(personNumber));



    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onCollapseButClick()));
}

CollapseViewItem::~CollapseViewItem()
{
    delete ui;
}

/*************************************************
Function Name： setTitleText()
Description:  设置分组组名
*************************************************/
void CollapseViewItem::setTitleText(QString titleText)
{
    ui->pushButton->setText(titleText);
}

void CollapseViewItem::addSubItems(QList<QWidget *> widgets)
{
    foreach (QWidget *var, widgets) {
        m_itemList.append(var);
        addSubItem(var);
    }
}

/*************************************************
Function Name： addSubItem()
Description:  添加好友项目
*************************************************/
void CollapseViewItem::addSubItem(QWidget *widget)
{
    m_itemList.append(widget);
    item_con_layout->addWidget(widget);
}

/*************************************************
Function Name： removeItem()
Description:  删除好友项目
*************************************************/
void CollapseViewItem::removeItem(QWidget *item){
    item_con_layout->removeWidget(item);
    m_itemList.removeAt(m_itemList.indexOf(item));
}

/*************************************************
Function Name： getSize()
Description:  获取成员数量
*************************************************/
int CollapseViewItem::getSize(){
    return m_itemList.size();
}

void CollapseViewItem::onCollapseButClick()
{
    //设置为相反的显示状态
    ui->item_con->setVisible(!ui->item_con->isVisible());

    ui->label->setProperty("slected",ui->item_con->isVisible());

    ui->label->update();

}

