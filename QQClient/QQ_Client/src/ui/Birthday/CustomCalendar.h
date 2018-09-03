#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QCalendarWidget>
#include <QTextCharFormat>

/*************************************************
Class Name： CustomCalendar
Description: a custom calendar
*************************************************/
class CustomCalendar : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CustomCalendar(QWidget *parent = 0);

    ~CustomCalendar();

    //paint the cell  by the given date, using the given painter and rect
    void paintCell (QPainter * painter,
                    const QRect & rect,
                    const QDate & date) const;

    //set whether the table grid is displayed or not
    void setCurrentDateRedBorderVisible(bool show);  

    //set the selected date's foreground and background color
    void setSelectedColor(QColor foregroundColor, QColor backgroundColor);

    //set the QTextCharFormat of current date
    void setCurrentDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of selected date
    void setSelectedDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of valid date
    void setValidDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of invalid date
    void setInvalidDateFormat(const QTextCharFormat &);

    //insert data to hasVideoDateList
    void insertHasVideoDataList(const QDate &date);

    //set m_selectedMonth
    void setSelectedMonth(int month);

    bool m_isShowCalendar; //whether the calendar is show or not

protected:
    void keyPressEvent(QKeyEvent *); //receive key press events for the widget

private:
    bool m_currentDateRedBorderVisible;   // whether the table grid is displayed or not

    QTextCharFormat m_currentDateFormat;  // QTextCharFormat of current date
    QTextCharFormat m_selectedDateFormat; // QTextCharFormat of selected date
    QTextCharFormat m_validDateFormat;    // QTextCharFormat of valid date
    QTextCharFormat m_invalidDateFormat;  // QTextCharFormat of invalid date

    int m_selectedMonth;                  // month of previous selected date
    int m_selectedDay;                    // day of previous selected date

    QList<QDate> *m_hasVideoDateList;     // list contains dates which have video
    QPixmap *m_videoPixmap;               // pixmap of vidoe,be used to mark date

    //draw red border
    void drawRedBorder(QPainter *painter, const QRect & rect) const;

    void linkSignalWithSlot(); //link the signals with slots

signals:

public slots:

    void setCurrentSelecetdDate(int year, int month); // set selected date
};

#endif // CUSTOMCALENDAR_H
