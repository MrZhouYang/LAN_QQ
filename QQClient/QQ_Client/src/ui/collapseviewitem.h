/*********************************************
File Name： collapseviewitem.h
Author： stormZhou
Date： 2018.06.10
Description： 好友列表选项卡
Changes：
********************************************/
#ifndef COLLAPSEVIEWITEM_H
#define COLLAPSEVIEWITEM_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>

namespace Ui {
class CollapseViewItem;
}


class CollapseViewItem : public QWidget
{
    Q_OBJECT

public:
    explicit CollapseViewItem(QString titleText,QWidget *parent = 0);
    ~CollapseViewItem();

    QList<QWidget *> * getWidgetList()
    {
        return &m_itemList;
    }

    /**
     * @brief 设置标题文字
     * @param titleText
     */
    void setTitleText(QString titleText);

    /**
     * @brief 添加展开抽屉后的内容项目
     * @param widgets 项目列表
     */
    void addSubItems(QList<QWidget *> widgets);

    /**
     * @brief 添加展开抽屉后的内容项目
     * @param widgets 项目
     */
    void addSubItem(QWidget*widget);

    /**
    * @brief 删除好友item
    * @param widgets 项目
    */
    void removeItem(QWidget *item);

    /**
    * @brief 获取成员数量
    * @return 成员数量
    */
    int getSize();


private slots:

    /**
     * @brief 点击按钮进行项目折叠
     */
    void onCollapseButClick();

private:
    Ui::CollapseViewItem *ui;

    QVBoxLayout *item_con_layout;
    QList<QWidget *> m_itemList; //保存着该好友列表选项卡中的好友项目
};

#endif // COLLAPSEVIEWITEM_H
