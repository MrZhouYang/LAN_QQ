#include "moveableframelesswindow.h"


#include <QKeyEvent>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QGridLayout>


MoveableFramelessWindow::MoveableFramelessWindow(QWidget *parent) :
    QWidget(parent),
    isMove(false)
{
    //设置窗体为无边框
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置底层背景透明
    setAttribute(Qt::WA_TranslucentBackground);

}

/**
 * @brief 鼠标按下，准备拖动窗体
 * @param event
 */
void MoveableFramelessWindow::mousePressEvent(QMouseEvent *event)
{
    //判断鼠标按下的位置是否在窗体内部
    bool shouldMove=isPointInDragnWidget(getDragnWidget(),event->pos());

    if(shouldMove){
          pressedPoint=event->pos();
          isMove=true;
    }

    event->ignore();

}

/**
* @brief 鼠标移动，处理窗体拖动
* @param event
*/
//event->x()返回鼠标光标相对于接收事件的窗口小部件的x位置
void MoveableFramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons()==Qt::LeftButton) && isMove==true){

            QPoint currPoint=this->pos(); //返回子窗口相对于父窗口的位置，如果是顶层窗口，则返回相对于桌面的位置
            currPoint.setX(currPoint.x()+event->x()-pressedPoint.x());
            currPoint.setY(currPoint.y()+event->y()-pressedPoint.y());
            this->move(currPoint); //窗口移动到绝对坐标
     }
}

void MoveableFramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isMove=false;

}

/**
 * @brief 判断鼠标点击的位置是否进入可拖动区域
 * @param widget 可拖动控件位置
 * @param point  鼠标点击位置
 * @return
 */
bool MoveableFramelessWindow::isPointInDragnWidget(const QWidget *widget, const QPoint &point)
{
    //判断位置
    QRect rect=widget->rect();

    bool isIn=point.x()>=rect.left()&&point.x()<=rect.right()&&point.y()>=rect.top()&&point.y()<=rect.bottom();

    return isIn;
}
