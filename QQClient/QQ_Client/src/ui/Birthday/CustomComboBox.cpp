#include "CustomComboBox.h"
#include <QKeyEvent>


/*************************************************
Function Name： CustomComboBox
Description: constructor
*************************************************/
MonthLineEdit::MonthLineEdit(QWidget *parent):
    QLineEdit(parent)
{
}

/*************************************************
Function Name： mousePressEvent
Description: receive mouse press events for the widget
*************************************************/
void MonthLineEdit::mousePressEvent(QMouseEvent* event)
{
    emit mousePress(true);
    QLineEdit::mousePressEvent(event);
}

//mark public:
/*************************************************
Function Name： CustomComboBox
Description: constructor
*************************************************/
CustomComboBox::CustomComboBox(QWidget *parent):
    QComboBox(parent),
    m_isMousePress(false)
{
    MonthLineEdit *lineEdit = new MonthLineEdit();
    lineEdit->setStyleSheet("Color:#ffffff;");
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setFixedWidth(100);
    setLineEdit(lineEdit);
    connect(lineEdit, SIGNAL(mousePress(bool)),
            this, SLOT(setIsMousePress(bool)));
}


/*************************************************
Function Name： ~CustomComboBox
Description: release resource
*************************************************/
CustomComboBox::~CustomComboBox()
{
}

//mark protected:
/*************************************************
Function Name： keyPressEvent
Description: receive key press events for the widget
*************************************************/
void CustomComboBox::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Enter:
        m_isMousePress = true;
        break;
    default:
        // If user pressed a key that we are not handling
        QWidget::keyPressEvent(event);
        break;
    }
}

/*************************************************
Function Name： focusInEvent
Description: receive focus events (focus received) for the widget
*************************************************/
void CustomComboBox::focusInEvent(QFocusEvent *event)
{
    showPopup();
    QComboBox::focusInEvent(event);
    focusNextChild();
}


/*************************************************
Function Name： hidePopup
Description: hide the list of items in the combobox
*************************************************/
void CustomComboBox::hidePopup()
{

   if(m_isMousePress)
   {
       m_isMousePress = false;
   }
   else
   {
       QComboBox::hidePopup();
   }
}


/*************************************************
Function Name： focusOutEvent
Description: receive focus events (focus lost) for the widget
*************************************************/
void CustomComboBox::focusOutEvent(QFocusEvent * event)
{
    QComboBox::focusOutEvent(event);
}


/*************************************************
Function Name： mousePressEvent
Description: receive mouse press events for the widget
*************************************************/
void CustomComboBox::mousePressEvent(QMouseEvent* event)
{
    m_isMousePress = true;
    QComboBox::mousePressEvent(event);
}

/*************************************************
Function Name： mouseReleaseEvent
Description: receive mouse release events for the widget
*************************************************/
void CustomComboBox::mouseReleaseEvent(QMouseEvent* event)
{
    QComboBox::mouseReleaseEvent(event);
}

//mark public slots:
void CustomComboBox::setIsMousePress(bool press)
{
    m_isMousePress = press;
}
