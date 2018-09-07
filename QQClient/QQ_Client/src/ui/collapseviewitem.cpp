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

    //给litteriem区域widget添加布局
    item_con_layout = new QVBoxLayout(this);
    item_con_layout->setContentsMargins(0,0,0,0);//设置上下左右的边距均为0
    item_con_layout->setSpacing(0);//设置布局内的窗口小部件之间的间距为0
    ui->item_con->setLayout(item_con_layout);

    ui->label->setProperty("slected",!ui->item_con->isVisible());

    this->setTitleText(titleText);

    createMenu();//创建右键弹出菜单

    ui->pushButton->installEventFilter(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onCollapseButClick()));
}

CollapseViewItem::~CollapseViewItem()
{
    delete ui;
}

bool CollapseViewItem::eventFilter(QObject *watched, QEvent *event){
    if(event->type()==QEvent::MouseButtonPress && watched==ui->pushButton){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->button()==Qt::RightButton){
            onClickRightButton();
            return true; //停止转发
        }
    }
    return false;//继续转发
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

/*************************************************
Function Name： createMenu
Description: 创建右键菜单
*************************************************/
void CollapseViewItem::createMenu()
{
    m_menu = new QMenu(this);
    QAction *rename = new QAction(tr("重命名"), m_menu);
    QAction *remove = new QAction(tr("删除"), m_menu);

    connect(rename, SIGNAL(triggered()),
            this, SLOT(renameBox()));
    connect(remove, SIGNAL(triggered()),
            this, SLOT(removeBox()));

    m_menu->addAction(rename);
    m_menu->addAction(remove);
}

/*************************************************
Function Name： mousePressEvent
Description: 鼠标点击事件
*************************************************/
//void CollapseViewItem:: mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::RightButton)
//        onClickRightButton();
//}

/*************************************************
Function Name： onClickRightButton()
Description: 右键点击按键
*************************************************/
void CollapseViewItem::onClickRightButton()
{
    if (m_menu == NULL)
    {
        //创建右键菜单
        createMenu();
    }
    m_menu->exec(QCursor::pos());//在鼠标当前位置同步执行此菜单
}

/*************************************************
Function Name： renameBox()
Description:  重命名
*************************************************/
void CollapseViewItem::renameBox()
{
    //qDebug() << "chose rename";
    emit renameBoxSignal(ui->pushButton->text());
}

/*************************************************
Function Name： removeBox()
Description:  删除整个
*************************************************/
void CollapseViewItem::removeBox()
{
    //qDebug() << "chose remove";
    emit removeBoxSignal(ui->pushButton->text());
}
