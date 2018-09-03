#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>
#include <QCalendarWidget>

class CalendarDialog;

//the type of positon which calendar to move
enum PosType
{
    NONE = 0 ,            // no style
    ABOVE_LINEEDIT = 1,   // on the above of lineEdit
    LEFT_LINEEDIT = 2,    // on the left  of lineEdit
    RIGHT_LINEEDIT = 3,   // on the right of lineEdit
    UNDER_LINEEDIT = 4    // on the under of lineEdit

};


/*************************************************
Class Name： CustomLineEdit
Description: a custom lineEdit
*************************************************/
class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(QWidget *parent = 0);
    ~CustomLineEdit();

    /******************style******************/
    //set calendar's position
    void setCalendarPos(int x = 0, int y = 0, PosType type = NONE);

    //set grid visible
    void setCalendarGridVisible(bool show);

    //set format of date showed on lineEdit
    void setDateFormat(const QString & formatStr);

    //set the format of the horizontal header
    void setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat format);

    //set the format of the vertical header
    void setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat format);

    //set the day displayed in the first column
    void setFirstDayOfWeek (Qt::DayOfWeek dayOfWeek);

    //set whether the table grid is displayed or not
    void setCurrentDateRedBorderVisible(bool show);

    //sets the date's foreground and background color
    void setColorOfDate(QDate date, QColor foregroundColor,
                        QColor backgroundColor);

    //add data which has video
    void addHasVideoDate(QDate &date);

    //set the widget's locale
    void setLocale(const QLocale & locale);

    //set the text char format for rendering of day in the week dayOfWeek to format
    void setWeekdayTextFormat(Qt::DayOfWeek dayOfWeek,
                              const QTextCharFormat & format);

    //set the text color for rendering of day in the week dayOfWeek
    void setWeekdayColor(Qt::DayOfWeek dayOfWeek,
                         QColor foregroundColor,
                         QColor backgroundColor);

    //set the icon of button[m_preMonth]
    void setPreMonthBtnIcon(const QIcon & icon);

    //set the icon of button[m_nextMonth]
    void setNextMonthBtnIcon(const QIcon & icon);

    //set the icon of button[m_preYear]
    void setPreYearBtnIcon(const QIcon & icon);

    //set the icon of button[m_nextYear]
    void setNextYearBtnIcon(const QIcon & icon);

    //set the QTextFormat of header text
    void setHeaderTextFormat(const QTextCharFormat &);

    //set the QTextCharFormat of current date
    void setCurrentDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of selected date
    void setSelectedDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of valid date
    void setValidDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of invalid date
    void setInvalidDateFormat(const QTextCharFormat &);

    //get the date
    QDate getDate();

protected:
    //receive focus events (focus received) for the widget
    void focusInEvent(QFocusEvent *);

    //receive focus events (focus lost) for the widget
    void focusOutEvent(QFocusEvent *);

private:
    PosType m_type;
    int m_posX;
    int m_posY;

    QString  m_dateFormatStr;
    QWidget* m_mainwindow;
    CalendarDialog *m_showDialog;

    void showDateOnLineEdit(); // show date on lineEdit
    void linkSignalWithSlot(); // link the signals with slots
    void setCalendarState();   // set state calendar

signals:

public slots:
    void moveCalendarPos();  // move calendar


};

#endif // CUSTOMLINEEDIT_H
