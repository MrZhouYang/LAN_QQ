#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>
#include <QLineEdit>


/*************************************************
Class Name： MonthLineEdit
Description: a custom QLineEdit
*************************************************/
class MonthLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MonthLineEdit(QWidget *parent = 0);

protected:
    //receive mouse press events for the widget
    void mousePressEvent(QMouseEvent* event);

signals:
    void mousePress(bool press);

};

/*************************************************
Class Name： CustomComboBox
Description: a custom QComboBox
*************************************************/
class CustomComboBox : public QComboBox
{
    Q_OBJECT
public:
    CustomComboBox(QWidget *parent = 0);
    ~CustomComboBox();

protected:

    //receive key press events for the widget
    void keyPressEvent(QKeyEvent * event);

    //receive focus events (focus received) for the widget
    void focusInEvent(QFocusEvent * event);

    //receive focus events (focus lost) for the widget
    void focusOutEvent(QFocusEvent * event);

    //receive mouse press events for the widget
    void mousePressEvent(QMouseEvent* event);

    //receive widget move events
    void mouseReleaseEvent(QMouseEvent* event);

    //hide the list of items in the combobox
    void hidePopup();

private:
    bool m_isMousePress;

public slots:
    void setIsMousePress(bool press);
};

#endif // CUSTOMCOMBOBOX_H
