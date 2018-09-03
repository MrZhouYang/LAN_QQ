#include "CustomCalendar.h"

#include <QKeyEvent>
#include <QPainter>
#include <QHeaderView>
#include <QLabel>
//#include <QTextCharFormat>




/*************************************************
Function Name： CustomCalendar
Description: constructor
*************************************************/
CustomCalendar::CustomCalendar(QWidget *parent) :
    QCalendarWidget(parent)
{
    m_isShowCalendar = false;
    setFocusPolicy(Qt::StrongFocus);

    m_selectedMonth = QDate::currentDate().month();
    m_hasVideoDateList = new QList<QDate>();
    m_videoPixmap = new QPixmap(":/replay_calendar_video_icon.png");
    m_currentDateRedBorderVisible = false;

    setNavigationBarVisible(false);
    setFirstDayOfWeek(Qt::Sunday);

    //set header view
    QTextCharFormat format;
    format.setForeground(QBrush(QColor(0X00, 0X84 ,0Xbb), Qt::SolidPattern));
    format.setBackground(QBrush(QColor(0Xdd, 0Xdd ,0Xdd), Qt::SolidPattern));
    setWeekdayTextFormat(Qt::Saturday, format);
    setWeekdayTextFormat(Qt::Sunday, format);
    setHeaderTextFormat(format);

    //set selected date format
    m_selectedDateFormat.setForeground(QBrush(QColor(0X00,0X00,0X00), Qt::SolidPattern));
    m_selectedDateFormat.setBackground(QBrush(QColor(0Xa5,0Xeb,0Xff), Qt::SolidPattern));

    //set current date format
    m_currentDateFormat.setForeground(QBrush(QColor(0X00,0X00,0X00), Qt::SolidPattern));
    m_currentDateFormat.setBackground(QBrush(QColor(0Xff,0X9c,0X00), Qt::SolidPattern));

    //set valid date format
    m_validDateFormat.setForeground(QBrush(QColor(0X00,0X00,0X00), Qt::SolidPattern));
    m_validDateFormat.setBackground(QBrush(QColor(0Xff,0Xff,0Xff), Qt::SolidPattern));

    //set invalid date format
    m_invalidDateFormat.setForeground(QBrush(QColor(0Xa3, 0Xa3, 0Xa3), Qt::SolidPattern));
    m_invalidDateFormat.setBackground(QBrush(QColor(0Xff, 0Xff, 0Xff), Qt::SolidPattern));


    setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setGridVisible(true);

    linkSignalWithSlot();//link the signals with slots

}

/*************************************************
Function Name： ~CustomCalendar
Description: release resource
*************************************************/
CustomCalendar::~CustomCalendar()
{
    if (m_hasVideoDateList)
    {
        m_hasVideoDateList->clear();
        delete m_hasVideoDateList;
        m_hasVideoDateList = NULL;
    }

    if (m_videoPixmap)
    {
        delete m_videoPixmap;
        m_videoPixmap = NULL;
    }
}

/*************************************************
Function Name： paintCell
Description: paint the cell  by the given date,
             using the given painter and rect
*************************************************/
void CustomCalendar::paintCell (QPainter * painter,
                                const QRect & rect,
                                const QDate & date) const
{
    QRect rectN = rect;
    painter->save();
    if (date == selectedDate())
    {
        painter->fillRect(rectN, m_selectedDateFormat.background());

        painter->setPen(m_selectedDateFormat.foreground().color());
    }
    else if(date.month() == monthShown())
    {
        painter->fillRect(rectN, m_validDateFormat.background());//QColor(0Xff, 0Xff, 0Xff));
        painter->setPen(m_validDateFormat.foreground().color());//QColor(0X00, 0X00, 0X00));
    }
    else
    {
        painter->fillRect(rectN, m_invalidDateFormat.background());//QColor(0Xff, 0Xff, 0Xff));
        painter->setPen(m_invalidDateFormat.foreground().color());//QColor(0Xa3, 0Xa3, 0Xa3));
    }

    if (date == QDate::currentDate())
    {
        painter->fillRect(rectN, m_currentDateFormat.background());//(QColor(0Xff,0X9c,0X00)));
        painter->setPen(m_currentDateFormat.foreground().color());//QColor(0X00, 0X00, 0X00));

        if (m_currentDateRedBorderVisible == true)
        {
            drawRedBorder(painter, rect);
        }

    }


    painter->drawText(rectN, Qt::AlignCenter, QString::number(date.day()));
    painter->restore();

    foreach (QDate tmpdate, *m_hasVideoDateList)
    {
        if (date == tmpdate)
        {
            painter->drawPixmap(rectN.x()+22,rectN.y()+3, *m_videoPixmap);
        }
    }

}

/*************************************************
Function Name： setCurrentDateRedBorderVisible
Description: set whether the table grid is displayed or not
*************************************************/
void CustomCalendar::setCurrentDateRedBorderVisible(bool show)
{
    m_currentDateRedBorderVisible = show;
}


/*************************************************
Function Name： setCurrentDateFormat
Description: set the QTextCharFormat of current date
*************************************************/
void CustomCalendar::setCurrentDateFormat(const QTextCharFormat &format)
{
    m_currentDateFormat = format;
}

/*************************************************
Function Name： setSelectedDateFormat
Description: set the QTextCharFormat of selected date
*************************************************/
void CustomCalendar::setSelectedDateFormat(const QTextCharFormat &format)
{
    m_selectedDateFormat = format;
}

/*************************************************
Function Name： setValidDateFormat
Description: set the QTextCharFormat of valid date
*************************************************/
void CustomCalendar::setValidDateFormat(const QTextCharFormat &format)
{
    m_validDateFormat = format;
}

/*************************************************
Function Name： setInvalidDateFormat
Description: set the QTextCharFormat of invalid date
*************************************************/
void CustomCalendar::setInvalidDateFormat(const QTextCharFormat &format)
{
    m_invalidDateFormat = format;
}


/*************************************************
Function Name： insertHasVideoDataList
Description: insert data to hasVideoDateList
*************************************************/
void CustomCalendar::insertHasVideoDataList(const QDate &date)
{
    m_hasVideoDateList->append(date);
}

/*************************************************
Function Name： setSelectedMonth
Description: set m_selectedMonth
*************************************************/
void CustomCalendar::setSelectedMonth(int month)
{
    m_selectedMonth = month;
}

//mark protected:

/*************************************************
Function Name： focusOutEvent
Description: receive key press events for the widget
*************************************************/
void CustomCalendar::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        if ( monthShown() < m_selectedMonth )
        {
            setSelectedDate(selectedDate().addDays(7));
            focusPreviousChild();
        }
        break;
    case Qt::Key_Down:
        if ( monthShown() > m_selectedMonth )
        {
            setSelectedDate(selectedDate().addDays(-7));
            focusNextChild();
        }
        break;
    case Qt::Key_Right:
        if ( monthShown() > m_selectedMonth )
        {
            setSelectedDate(selectedDate().addDays(-1));
            focusNextChild();
        }
        break;
    case Qt::Key_Left:
        if ( monthShown() < m_selectedMonth )
        {
            setSelectedDate(selectedDate().addDays(1));
            focusPreviousChild();
        }
        break;
    default:
        //If the user pressed a key that we are not handling,
        //we call the base class implementation.
        QWidget::keyPressEvent(event);
        break;
    }
    m_selectedMonth = monthShown();
}

//mark private:

/*************************************************
Function Name： drawRedBorder
Description: draw red border
*************************************************/
void CustomCalendar::drawRedBorder(QPainter * painter,
                                   const QRect & rect) const
{
    QRect rectN = rect;
    QPen m_outlinePen;
    QBrush m_transparentBrush;
    m_outlinePen.setColor(Qt::red);
    m_transparentBrush.setColor(Qt::transparent);// transparent pixel
    painter->setPen(m_outlinePen);
    painter->setBrush(m_transparentBrush);
    painter->drawRect(rectN.adjusted(0, 0, -1, -1));
    painter->drawText(rectN, Qt::AlignCenter | Qt::AlignHCenter,
                      QString::number (QDate::currentDate().day()));

}

/*************************************************
Function Name： linkSignalWithSlot
Description: link the signals with slots
*************************************************/
void CustomCalendar::linkSignalWithSlot()
{
    connect(this, SIGNAL(currentPageChanged(int,int)),
            this, SLOT(setCurrentSelecetdDate(int,int)));
}

//public slots:

/*************************************************
Function Name： setCurrentSelecetdDate
Description: set selected date
*************************************************/
void CustomCalendar::setCurrentSelecetdDate(int year, int month)
{
    QDate date(year, month, 1);
    if (date.daysInMonth() < selectedDate().day())
    {
        date.setDate(year, month, date.daysInMonth());
    }
    else
    {
        date.setDate(year, month, selectedDate().day());
    }
    setSelectedDate(date);
}

