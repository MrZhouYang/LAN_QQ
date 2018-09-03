#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H


#include <QDialog>
#include "CustomLineEdit.h"
#include "CustomCalendar.h"
#include "CustomComboBox.h"

class QComboBox;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QLineEdit;
class QValidator;
class QLabel;


/*************************************************
Class Name： CalendarDialog
Description: a custom Dialog contains a calendar
*************************************************/
class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = 0);
    ~CalendarDialog();

    CustomCalendar * getCalendar(); // get calendar [m_customCalendar]
    QRect getDialogRect();          // get dialog's rect
    QDate getMaxDate();             // get m_maxDate
    QDate getMinDate();             // get m_minDate

    //set the QTextFormat of header text
    void setCalendarHeaderTextFormat(const QTextCharFormat &);

    //set the QTextCharFormat of current date
    void setCalendarCurrentDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of selected date
    void setCalendarSelectedDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of valid date
    void setCalendarValidDateFormat(const QTextCharFormat &);

    //set the QTextCharFormat of invalid date
    void setCalendarInvalidDateFormat(const QTextCharFormat &);

    //set the position of calendar
    void setCalendarPos(int posX, int posY, QSize &lineEdit, PosType type);

    //set whether the table grid is displayed or not
    void setCalendarGridVisible(bool);

    //set the format of the horizontal header
    void setCalendarHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat format);

    //set the format of the vertical header
    void setCalendarVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat format);

    //set the day displayed in the first column
    void setCalendarFirstDayOfWeek (Qt::DayOfWeek dayOfWeek);

    //set whether the red border of current date is displayed or not
    void setCalendarCurrentDateRedBorderVisible(bool show);

    //set a date's foreground and background color
    void setCalendarColorOfDate(QDate date,
                                QColor foregroundColor,
                                QColor backgroundColor);
    //insert data which has video
    void insertHasVideoDate(QDate &date);

    //set the widget's locale
    void setCalendarLocale(const QLocale &locale);

    //set the text char format for rendering of day in the week dayOfWeek to format
    void setCalendarWeekdayTextFormat(Qt::DayOfWeek dayOfWeek,
                                      const QTextCharFormat & format);

    //set the text color for rendering of day in the week dayOfWeek
    void setCalendarWeekdayColor(Qt::DayOfWeek dayOfWeek,
                                 QColor foregroundColor,
                                 QColor backgroundColor);

    //hide calendar
    void hideCalender();

    //show calendar
    void showCalendar();



    //set state of calendar
    void setCalendarState();

    //set the icon of button[m_preMonth]
    void setCalendarPreMonthBtnIcon(const QIcon & icon);

    //set the icon of button[m_nextMonth]
    void setCalendarNextMonthBtnIcon(const QIcon & icon);

    //set the icon of button[m_preYear]
    void setCalendarPreYearBtnIcon(const QIcon & icon);

    //set the icon of button[m_nextYear]
    void setCalendarNextYearBtnIcon(const QIcon & icon);

    //get date
    QDate getDate();


protected:
    //receive key press events for the widget
    void keyPressEvent(QKeyEvent *);


private:

    QLabel *m_headView;

    QPushButton *m_preMonth;    // turn to previous month in calendar
    CustomComboBox *m_monthBox; // show the month of selected date
    QPushButton *m_nextMonth;   // turn to next month in calendar

    QPushButton *m_preYear;     // turn to previous year in calendar
    QLineEdit *m_yearText;      // show the year of selected date
    QPushButton *m_nextYear;    // turn to next year in calendar

    CustomCalendar *m_customCalendar; // custom calendar

    QHBoxLayout *m_hTopLayout;
    QVBoxLayout *m_vLabelLayout;

    int m_width;  // width of dialog
    int m_height; // height of dialog

    QDate m_maxDate; // max date of calendar
    QDate m_minDate; // min date of calendar

    void initDialog();         // initialize dialog
    void setDialogLayout();    // set dialog's layout
    void linkSignalWithSlot(); // link the signals with slots

signals:
    void focusOutDialog(); // this signal is emitted when the widget lose focus
    void changeLineEditText(const QString & text); 
    void addHasVideoDataList(QDate &date);//add data to hasVideoDateList

public slots:

    //show the given month
    void setCalendarCurrenPageByMonth(int month);

    //show the given year
    void setCalendarCurrenPageByYear(QString year);

    //show the given month of the given year
    void setCalendarCurrenPage(int year, int month);

    //show the previous month in a year
    void showCalendarPreviousMonthInYear();

    //show the next month in a year
    void showCalendarNextMonthInYear();

    //show the previous year
    void showCalendarPreviousYear();

    //show the next year
    void showCalendarNextYear();

    //show the previous month
    void showCalendarPreviousMonth();

    //show the next month
    void showCalendarNextMonth();

    //get selected date
    void getSelectedDate();

};

#endif // CALENDARDIALOG_H
