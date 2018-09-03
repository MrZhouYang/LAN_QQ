#include "CustomLineEdit.h"
#include "CalendarDialog.h"
#include <QDate>
#include <QCalendarWidget>
#include <QDebug>

//mark public:
/*************************************************
Function Name： CustomLineEdit
Description: constructor
*************************************************/
CustomLineEdit::CustomLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setReadOnly(true);
    m_type = UNDER_LINEEDIT;
    m_posX= 0;
    m_posY = 1;

    m_showDialog =new CalendarDialog(parent);
    m_mainwindow = parent;
    setAlignment(Qt::AlignCenter);
    setFocusPolicy(Qt::StrongFocus);
    m_dateFormatStr = "yyyy-MM-dd";
    showDateOnLineEdit();
    linkSignalWithSlot();
}


/*************************************************
Function Name： ~CustomLineEdit
Description: release resource
*************************************************/
CustomLineEdit::~CustomLineEdit()
{
    if (m_showDialog)
    {
        delete m_showDialog;
        m_showDialog = NULL;
    }
}


/*************************************************
Function Name： setGridVisible
Description: set grid visible
*************************************************/
void CustomLineEdit::setCalendarPos(int x , int y , PosType type)
{
    m_type = type;
    m_posX = x;
    m_posY = y;
}


/*************************************************
Function Name： setGridVisible
Description: set grid visible
*************************************************/
void CustomLineEdit::setCalendarGridVisible(bool show)
{
    m_showDialog->setCalendarGridVisible(show);
}


/*************************************************
Function Name： setDateFormat
Description: set format of date showed on lineEdit
*************************************************/
void CustomLineEdit::setDateFormat(const QString & formatStr)
{
    m_dateFormatStr = formatStr;
    showDateOnLineEdit();
}

/*************************************************
Function Name： setHorizontalHeaderFormat
Description: set the format of the horizontal header
             The default value is QCalendarWidget::ShortDayNames.
*************************************************/
void CustomLineEdit::setHorizontalHeaderFormat(
        QCalendarWidget::HorizontalHeaderFormat format)
{
    m_showDialog->setCalendarHorizontalHeaderFormat(format);
}

/*************************************************
Function Name： setVerticalHeaderFormat
Description: set the format of the vertical header
             The default value is QCalendarWidget::NoVerticalHeader
*************************************************/
void CustomLineEdit::setVerticalHeaderFormat(
        QCalendarWidget::VerticalHeaderFormat format)
{
    m_showDialog->setCalendarVerticalHeaderFormat(format);
}

/*************************************************
Function Name： onClickedDataEdit
Description: set the day displayed in the first column
             By default, the day displayed in the first column is Sunday
*************************************************/
void CustomLineEdit::setFirstDayOfWeek (Qt::DayOfWeek dayOfWeek)
{
    m_showDialog->setCalendarFirstDayOfWeek(dayOfWeek);
}

/*************************************************
Function Name： setCurrentDateRedBorderVisible
Description: set whether the table grid is displayed or not
             The default value is true.
*************************************************/
void CustomLineEdit::setCurrentDateRedBorderVisible(bool show)
{
    m_showDialog->setCalendarCurrentDateRedBorderVisible(show);
}

/*************************************************
Function Name： setColorOfDate
Description: sets the date's foreground and background color
*************************************************/
void CustomLineEdit::setColorOfDate(QDate date, QColor foregroundColor,
                                  QColor backgroundColor)
{
    m_showDialog->setCalendarColorOfDate(date, foregroundColor,backgroundColor);
}

/*************************************************
Function Name： markHasVideoDate
Description: mark data which has video
*************************************************/
void CustomLineEdit::addHasVideoDate(QDate &date)
{
    m_showDialog->insertHasVideoDate(date);
}


/*************************************************
Function Name： setLocale
Description: set the widget's locale
*************************************************/
void CustomLineEdit::setLocale(const QLocale &locale)
{
    m_showDialog->setCalendarLocale(locale);
}

/*************************************************
Function Name： setWeekdayTextFormat
Description: set the text char format for rendering of day in the week dayOfWeek to format
*************************************************/
void CustomLineEdit::setWeekdayTextFormat(Qt::DayOfWeek dayOfWeek,
                                          const QTextCharFormat & format)
{
    m_showDialog->setCalendarWeekdayTextFormat(dayOfWeek, format);
}

/*************************************************
Function Name： setWeekdayColor
Description: set the text color for rendering of day in the week dayOfWeek
*************************************************/
void CustomLineEdit::setWeekdayColor(Qt::DayOfWeek dayOfWeek,
                     QColor foregroundColor,
                     QColor backgroundColor)
{
    m_showDialog->setCalendarWeekdayColor(dayOfWeek, foregroundColor, backgroundColor);
}

/*************************************************
Function Name： setPreMonthBtnIcon
Description: set the icon of button[m_preMonth]
*************************************************/
void CustomLineEdit::setPreMonthBtnIcon(const QIcon & icon)
{
    m_showDialog->setCalendarPreMonthBtnIcon(icon);
}

/*************************************************
Function Name： setNextMonthBtnIcon
Description: set the icon of button[m_nextMonth]
*************************************************/
void CustomLineEdit::setNextMonthBtnIcon(const QIcon & icon)
{
    m_showDialog->setCalendarNextMonthBtnIcon(icon);
}

/*************************************************
Function Name： setPreYearBtnIcon
Description: set the icon of button[m_preYear]
*************************************************/
void CustomLineEdit::setPreYearBtnIcon(const QIcon & icon)
{
    m_showDialog->setCalendarPreYearBtnIcon(icon);
}

/*************************************************
Function Name： setNextYearBtnIcon
Description: set the icon of button[m_nextYear]
*************************************************/
void CustomLineEdit::setNextYearBtnIcon(const QIcon & icon)
{
    m_showDialog->setCalendarNextYearBtnIcon(icon);
}

/*************************************************
Function Name： setHeaderTextFormat
Description: set the QTextFormat of header text
*************************************************/
void CustomLineEdit::setHeaderTextFormat(const QTextCharFormat &format)
{
    m_showDialog->setCalendarHeaderTextFormat(format);
}

/*************************************************
Function Name： setCurrentDateFormat
Description: set the QTextCharFormat of current date
*************************************************/
void CustomLineEdit::setCurrentDateFormat(const QTextCharFormat &format)
{
    m_showDialog->setCalendarCurrentDateFormat(format);
}

/*************************************************
Function Name： setSelectedDateFormat
Description: set the QTextCharFormat of selected date
*************************************************/
void CustomLineEdit::setSelectedDateFormat(const QTextCharFormat &format)
{
    m_showDialog->setCalendarSelectedDateFormat(format);
}

/*************************************************
Function Name： setValidDateFormat
Description: set the QTextCharFormat of valid date
*************************************************/
void CustomLineEdit::setValidDateFormat(const QTextCharFormat &format)
{
    m_showDialog->setCalendarValidDateFormat(format);
}

/*************************************************
Function Name： setInvalidDateFormat
Description: set the QTextCharFormat of invalid date
*************************************************/
void CustomLineEdit::setInvalidDateFormat(const QTextCharFormat &format)
{
    m_showDialog->setCalendarInvalidDateFormat(format);
}

/*************************************************
Function Name： getDate
Description: get the date
*************************************************/
QDate CustomLineEdit::getDate()
{
    return m_showDialog->getDate();
}

//mark protected:
/*************************************************
Function Name： focusInEvent
Description: receive focus events (focus received) for the widget
*************************************************/
void CustomLineEdit::focusInEvent(QFocusEvent *event)
{
    //emit focusInLineEdit();
    setCalendarState();
    QLineEdit::focusInEvent(event);
    focusNextChild();
}

/*************************************************
Function Name： focusOutEvent
Description: receive focus events (focus lost) for the widget
*************************************************/
void CustomLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
}

/*************************************************
Function Name： showDateOnLineEdit
Description: show date on lineEdit
*************************************************/
void CustomLineEdit::showDateOnLineEdit()
{
    QDate date = QDate::currentDate();
    setText(date.toString(m_dateFormatStr));
}


/*************************************************
Function Name： linkSignalWithSlot
Description: link the signals with slots
*************************************************/
void CustomLineEdit::linkSignalWithSlot()
{
    connect(m_showDialog, SIGNAL( changeLineEditText(QString) ),
            this, SLOT( setText(QString) ) );
}

/*************************************************
Function Name： setCalendarState
Description: set state calendar
*************************************************/
void CustomLineEdit::setCalendarState()
{
    m_showDialog->setCalendarState();
    moveCalendarPos();
}


//public slots:

/*************************************************
Function Name： moveCalendarPos
Description: move calendar
*************************************************/
void CustomLineEdit::moveCalendarPos()
{
    QPoint lineEditPos = mapToGlobal(QPoint(0,0));

    int calendarX = m_posX + lineEditPos.x();
    int calendarY = m_posY + lineEditPos.y();

    QSize size(rect().width(), rect().height());

    m_showDialog->setCalendarPos(calendarX, calendarY, size, m_type);
}


