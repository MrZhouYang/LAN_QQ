#include "CalendarDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QTextCharFormat>
#include <QComboBox>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <QTextLine>
#include <QValidator>
#include <QDebug>
#include <QHeaderView>
#include <QTableView>
#include <QLabel>
#include <QColor>
#include <QPainter>
#include <QRegExp>


#define HEIGHT_OF_DATE 40      //height of data
#define HEIFHT_OF_WEEKNUMBER 30 //height of weeknumber
#define WIDTH_OF_DATE 40       //width of data

//mark public:
/*************************************************
Function Name： CalendarDialog
Description: constructor
*************************************************/
CalendarDialog::CalendarDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint)
{

    m_headView = NULL;

    m_preMonth = NULL;
    m_monthBox = NULL;
    m_nextMonth = NULL;

    m_preYear = NULL;
    m_yearText = NULL;
    m_nextYear = NULL;

    m_customCalendar = NULL;

    initDialog();
    setAutoFillBackground(true);

    setWindowModality(Qt::ApplicationModal);
    //setWindowOpacity(9.5);
}

/*************************************************
Function Name： ~CalendarDialog
Description: release resource/image
*************************************************/
CalendarDialog:: ~CalendarDialog()
{
    if (m_preMonth)
    {
        delete m_preMonth;
        m_preMonth = NULL;
    }
    if (m_nextMonth)
    {
        delete m_nextMonth;
        m_nextMonth = NULL;
    }

    if (m_preYear)
    {
        delete m_preYear;
        m_preYear = NULL;
    }
    if (m_nextYear)
    {
        delete m_nextYear;
        m_nextYear = NULL;
    }

    if (m_monthBox)
    {
        delete m_monthBox;
        m_monthBox = NULL;
    }

    if (m_yearText)
    {
        delete m_yearText;
        m_yearText = NULL;
    }

    if (m_customCalendar)
    {
        delete m_customCalendar;
        m_customCalendar = NULL;
    }

    if (m_hTopLayout)
    {
        delete m_hTopLayout;
        m_hTopLayout = NULL;
    }

    if (m_headView)
    {
        delete m_headView;
        m_headView = NULL;
    }

    if (m_vLabelLayout)
    {
        delete m_vLabelLayout;
        m_vLabelLayout = NULL;

    }
}

/*************************************************
Function Name： getCalendar
Description: get calendar [m_customCalendar]
*************************************************/
CustomCalendar * CalendarDialog::getCalendar()
{
    return m_customCalendar;
}

/*************************************************
Function Name： getDialogRect
Description: get Dialog's Rect
*************************************************/
QRect CalendarDialog::getDialogRect()
{
    return rect();
}

/*************************************************
Function Name： getMaxDate
Description:
*************************************************/
QDate CalendarDialog::getMaxDate()
{
    return m_maxDate;
}

/*************************************************
Function Name： getMinDate
Description:
*************************************************/
QDate CalendarDialog::getMinDate()
{
    return m_minDate;
}

//mark protected:

/*************************************************
Function Name： keyPressEvent
Description: receive key press events for the widget
*************************************************/
void CalendarDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Left:
        focusPreviousChild();
        break;
    case Qt::Key_Down:
    case Qt::Key_Right:
        focusNextChild();
        break;
    default:
        // If user pressed a key that we are not handling
        QWidget::keyPressEvent(event);
        break;
    }
}

//mark private:

/*************************************************
Function Name： initDialog
Description: initialize dialog
*************************************************/
void CalendarDialog::initDialog()
{
    //head view
    m_headView = new QLabel();
    m_headView->setFixedHeight(40);
    m_headView->setStyleSheet("background-color: #1f2021;");
                              //"opacity: 200");
    m_headView->setWindowOpacity(0.1);
    //end head view

    //month
    m_preMonth = new QPushButton(this);
    m_preMonth->setFlat(true);
    m_preMonth->setStyleSheet("border-width:0;"
                              "border-style:outset");
    m_preMonth->setIcon(QIcon("resource/image/replay_calendar_left_arrow_btn.png"));

    m_monthBox = new CustomComboBox(this);

    m_monthBox->setFixedWidth(105);
    m_monthBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    m_monthBox->setStyleSheet("QComboBox{border: 0;font-size: 16px;}"
                              "QComboBox::drop-down{border-style:none;border:0px;width:40px}");

    m_monthBox->addItem(tr("一月"));//"January");
    m_monthBox->addItem(tr("二月"));//"February");
    m_monthBox->addItem(tr("三月"));//"March");
    m_monthBox->addItem(tr("四月"));//"April");
    m_monthBox->addItem(tr("五月"));//"May");
    m_monthBox->addItem(tr("六月"));//"June");
    m_monthBox->addItem(tr("七月"));//"July");
    m_monthBox->addItem(tr("八月"));//"August");
    m_monthBox->addItem(tr("九月"));//"September");
    m_monthBox->addItem(tr("十月"));//"October");
    m_monthBox->addItem(tr("十一月"));//"November");
    m_monthBox->addItem(tr("十二月"));//"December");

    m_monthBox->setCurrentIndex(QDate::currentDate().month() - 1);

    m_nextMonth = new QPushButton(this);
    m_nextMonth->setFlat(true);
    m_nextMonth->setStyleSheet("border-width:0;"
                              "border-style:outset");
    m_nextMonth->setIcon(QIcon("resource/image/replay_calendar_right_arrow_btn.png"));
    //end month

    //year
    m_preYear = new QPushButton(this);
    m_preYear->setFlat(true);
    m_preYear->setStyleSheet("border-width:0;"
                             "border-style:outset");
    m_preYear->setIcon(QIcon("resource/image/replay_calendar_left_arrow_btn.png"));

    m_yearText = new QLineEdit(this);
    m_yearText->setStyleSheet("color: #ffffff;"
                              "font-size: 16px;"
                              "border-width:0;"
                              "border-style:outset");

    m_yearText->setMaxLength(4);
    m_yearText->setAlignment(Qt::AlignCenter);
    QRegExp regExp("[1-2][0-9][0-9][0-9]");
    m_yearText->setValidator(new QRegExpValidator(regExp, this));
    m_yearText->setText(QString::number(QDate::currentDate().year()));

    m_nextYear = new QPushButton(this);
    m_nextYear->setFlat(true);
    m_nextYear->setStyleSheet("border-width:0;"
                              //"width: 50;"
                              "border-style:outset");
    m_nextYear->setIcon(QIcon("resource/image/replay_calendar_right_arrow_btn.png"));
    //end year

    //calendar
    m_customCalendar = new CustomCalendar(this);
    m_customCalendar->setFixedSize(7 * WIDTH_OF_DATE,
                                   6 * HEIGHT_OF_DATE + HEIFHT_OF_WEEKNUMBER);

    QTableView *table = m_customCalendar->findChild<QTableView *>();
    QHeaderView *verticalHeader = table->verticalHeader();
    QHeaderView *horizontalHeader = table->horizontalHeader();

    horizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);

    verticalHeader->resizeSection(0, HEIFHT_OF_WEEKNUMBER);
    horizontalHeader->resizeSection(0, WIDTH_OF_DATE);

    for (int index =1; index<=7; index++)
    {
        verticalHeader->resizeSection(index,HEIGHT_OF_DATE);
        horizontalHeader->resizeSection(index,WIDTH_OF_DATE);
    }

    //end calendar

    setDialogLayout();
    linkSignalWithSlot();
}

/*************************************************
Function Name： setDialogLayout
Description: set dialog's layout
*************************************************/
void CalendarDialog::setDialogLayout()
{
    //m_hTopLayout
    m_hTopLayout = new QHBoxLayout;
    m_hTopLayout->addWidget(m_preMonth);
    m_hTopLayout->addWidget(m_monthBox);
    m_hTopLayout->addSpacing(2);
    m_hTopLayout->addWidget(m_nextMonth);
    m_hTopLayout->addSpacing(30);
    m_hTopLayout->addWidget(m_preYear);
    m_hTopLayout->addWidget(m_yearText);
    m_hTopLayout->addWidget(m_nextYear);
    m_hTopLayout->setSpacing(0);
    m_headView->setLayout(m_hTopLayout);

    //m_vLabelLayout
    m_vLabelLayout = new QVBoxLayout;
    m_vLabelLayout->addWidget(m_headView);
    m_vLabelLayout->addWidget(m_customCalendar);
    m_vLabelLayout->setSpacing(0);
    m_vLabelLayout->setContentsMargins(0,0,0,0);
    //end m_vLabelLayout

    this->setLayout(m_vLabelLayout);
}

/*************************************************
Function Name： linkSignalWithSlot
Description: link the signals with slots
*************************************************/
void CalendarDialog::linkSignalWithSlot()
{
    connect(m_monthBox, SIGNAL(activated(int)),
            this, SLOT (setCalendarCurrenPageByMonth(int)));

    connect(m_yearText, SIGNAL(textChanged(QString)),
            this, SLOT(setCalendarCurrenPageByYear(QString)));

    connect(m_preMonth, SIGNAL(clicked()),
            this, SLOT(showCalendarPreviousMonthInYear()) );

    connect(m_nextMonth, SIGNAL(clicked()),
            this, SLOT(showCalendarNextMonthInYear()));

    connect(m_preYear, SIGNAL(clicked()),
            this, SLOT(showCalendarPreviousYear()));

    connect(m_nextYear, SIGNAL(clicked()),
            this, SLOT(showCalendarNextYear()));

    connect(m_customCalendar, SIGNAL(currentPageChanged(int,int)),
            this, SLOT(setCalendarCurrenPage(int,int)));

    connect(m_customCalendar, SIGNAL( activated(QDate) ),
            this, SLOT( getSelectedDate() ) );

}

/*************************************************
Function Name： setCalendarPos
Description: set the position of calendar
*************************************************/
void CalendarDialog::setCalendarPos(int posX, int posY, QSize &lineEdit, PosType type)
{
    int calendarX = posX;
    int calendarY = posY;

    switch (type)
    {
    case NONE:
        break;
    case ABOVE_LINEEDIT:
        calendarY -= rect().height();
        break;
    case LEFT_LINEEDIT:
        calendarX -= rect().width();
        break;
    case RIGHT_LINEEDIT:
        calendarX += lineEdit.width();
        break;
    case UNDER_LINEEDIT:
        calendarY += lineEdit.height();
        break;
    default:
        break;
    }

    move(calendarX, calendarY);
}


/*************************************************
Function Name： setCalendarGridVisible
Description:  set grid visible
*************************************************/
void CalendarDialog::setCalendarGridVisible(bool show)
{
    m_customCalendar->setGridVisible(show);
}


/*************************************************
Function Name： setCalendarHorizontalHeaderFormat
Description: set the format of the horizontal header
             The default value is QCalendarWidget::ShortDayNames.
*************************************************/
void CalendarDialog::setCalendarHorizontalHeaderFormat(
        QCalendarWidget::HorizontalHeaderFormat format)
{
    m_customCalendar->setHorizontalHeaderFormat(format);
}

/*************************************************
Function Name： setCalendarVerticalHeaderFormat
Description: set the format of the vertical header
             The default value is QCalendarWidget::NoVerticalHeader
*************************************************/
void CalendarDialog::setCalendarVerticalHeaderFormat(
        QCalendarWidget::VerticalHeaderFormat format)
{
    m_customCalendar->setVerticalHeaderFormat(format);
}

/*************************************************
Function Name： setCalendarFirstDayOfWeek
Description: set the day displayed in the first column
             By default, the day displayed in the first column is Sunday
*************************************************/
void CalendarDialog::setCalendarFirstDayOfWeek (Qt::DayOfWeek dayOfWeek)
{
    m_customCalendar->setFirstDayOfWeek(dayOfWeek);
}

/*************************************************
Function Name： setCalendarCurrentDateRedBorderVisible
Description: set whether the red border of current date is displayed or not
             The default value is true.
*************************************************/
void CalendarDialog::setCalendarCurrentDateRedBorderVisible(bool show)
{
    m_customCalendar->setCurrentDateRedBorderVisible(show);
}

/*************************************************
Function Name： setCalendarColorOfDate
Description: sets the date's foreground and background color
*************************************************/
void CalendarDialog::setCalendarColorOfDate(QDate date,
                                            QColor foregroundColor,
                                            QColor backgroundColor)
{
    QTextCharFormat formatC = m_customCalendar->weekdayTextFormat(Qt::Monday);
    formatC.setBackground(backgroundColor);
    formatC.setForeground(QBrush(foregroundColor, Qt::SolidPattern));
    m_customCalendar->setDateTextFormat(date, formatC);
}


/*************************************************
Function Name： insertHasVideoDate
Description: insert data which has video
*************************************************/
void CalendarDialog::insertHasVideoDate(QDate &date)
{
    m_customCalendar->insertHasVideoDataList(date);
}

/*************************************************
Function Name： setCalendarLocale
Description: set the widget's locale
*************************************************/
void CalendarDialog::setCalendarLocale(const QLocale &locale)
{
    m_customCalendar->setLocale(locale);
}

/*************************************************
Function Name： setCalendarLocale
Description: set the text char format for rendering of day in the week dayOfWeek to format
*************************************************/
void CalendarDialog::setCalendarWeekdayTextFormat(Qt::DayOfWeek dayOfWeek,
                                                  const QTextCharFormat & format)
{
    m_customCalendar->setWeekdayTextFormat(dayOfWeek, format);
}

/*************************************************
Function Name： setCalendarLocale
Description: set the text color for rendering of day in the week dayOfWeek
*************************************************/
void CalendarDialog::setCalendarWeekdayColor(Qt::DayOfWeek dayOfWeek,
                                             QColor foregroundColor,
                                             QColor backgroundColor)
{
    QTextCharFormat format = m_customCalendar->weekdayTextFormat(Qt::Saturday);
    format.setForeground(QBrush(foregroundColor, Qt::SolidPattern));
    format.setBackground(backgroundColor);
    m_customCalendar->setWeekdayTextFormat(dayOfWeek, format);
}


//public slots:

/*************************************************
Function Name： hideCalendar
Description: hide calendar
*************************************************/
void CalendarDialog::hideCalender()
{
    hide();
    m_customCalendar->m_isShowCalendar = false;
}

/*************************************************
Function Name： showCalendar
Description: show calendar
*************************************************/
void CalendarDialog::showCalendar()
{
    if (m_customCalendar->m_isShowCalendar == false)
    {
        show();
        raise();
        m_customCalendar->m_isShowCalendar = true;
    }
    else
    {
        hide();
        m_customCalendar->m_isShowCalendar = false;
    }

    m_customCalendar->setFocusProxy(this);

}



/*************************************************
Function Name： setCalendarState
Description: set state of calendar
*************************************************/
void CalendarDialog::setCalendarState()
{
    if (m_customCalendar->m_isShowCalendar == false)
    {
        show();
        raise();
        m_customCalendar->m_isShowCalendar = true;
    }
    else
    {
        hide();
        m_customCalendar->m_isShowCalendar = false;
    }
}

/*************************************************
Function Name： setCalendarPreMonthBtnIcon
Description: set the icon of button[m_preMonth]
*************************************************/
void CalendarDialog::setCalendarPreMonthBtnIcon(const QIcon & icon)
{
    m_preMonth->setIcon(icon);
}

/*************************************************
Function Name： setCalendarPNextMonthBtnIcon
Description: set the icon of button[m_nextMonth]
*************************************************/
void CalendarDialog::setCalendarNextMonthBtnIcon(const QIcon & icon)
{
    m_nextMonth->setIcon(icon);
}

/*************************************************
Function Name： setCalendarPreYearBtnIcon
Description: set the icon of button[m_preYear]
*************************************************/
void CalendarDialog::setCalendarPreYearBtnIcon(const QIcon & icon)
{
    m_preYear->setIcon(icon);
}

/*************************************************
Function Name： setCalendarPNextYearBtnIcon
Description: set the icon of button[m_nextYear]
*************************************************/
void CalendarDialog::setCalendarNextYearBtnIcon(const QIcon & icon)
{
    m_nextYear->setIcon(icon);
}

/*************************************************
Function Name： getDate
Description: get date
*************************************************/
QDate CalendarDialog::getDate()
{
    return m_customCalendar->selectedDate();
}

/*************************************************
Function Name： setCalendarHeaderTextFormat
Description: set the QTextFormat of header text
*************************************************/
void CalendarDialog::setCalendarHeaderTextFormat(const QTextCharFormat &format)
{
    m_customCalendar->setWeekdayTextFormat(Qt::Saturday, format);
    m_customCalendar->setWeekdayTextFormat(Qt::Sunday, format);
    m_customCalendar->setHeaderTextFormat(format);

}

/*************************************************
Function Name： setCalendarCurrentDateFormat
Description: set the QTextCharFormat of current date
*************************************************/
void CalendarDialog::setCalendarCurrentDateFormat(const QTextCharFormat &format)
{
    m_customCalendar->setCurrentDateFormat(format);
}

/*************************************************
Function Name： setCalendarSelectedDateFormat
Description: set the QTextCharFormat of selected date
*************************************************/
void CalendarDialog::setCalendarSelectedDateFormat(const QTextCharFormat &format)
{
    m_customCalendar->setSelectedDateFormat(format);
}

/*************************************************
Function Name： setCalendarValidDateFormat
Description: set the QTextCharFormat of valid date
*************************************************/
void CalendarDialog::setCalendarValidDateFormat(const QTextCharFormat &format)
{
    m_customCalendar->setValidDateFormat(format);
}

/*************************************************
Function Name： setCalendarInvalidDateFormat
Description: set the QTextCharFormat of invalid date
*************************************************/
void CalendarDialog::setCalendarInvalidDateFormat(const QTextCharFormat &format)
{
    m_customCalendar->setInvalidDateFormat(format);
}

//public slots:
/*************************************************
Function Name： setCalendarCurrenPage
Description: show the given month
*************************************************/
void CalendarDialog::setCalendarCurrenPageByMonth(int month)
{
    m_customCalendar->setCurrentPage(m_customCalendar->yearShown(),
                                    month + 1);
    m_customCalendar->setSelectedMonth(month + 1);
}

/*************************************************
Function Name： setCalendarCurrenPage
Description: show the given year
*************************************************/
void CalendarDialog::setCalendarCurrenPageByYear(QString year)
{
        m_customCalendar->setCurrentPage(year.toInt(),m_customCalendar->monthShown());
}

/*************************************************
Function Name： setCalendarCurrenPage
Description: show the given month of the given year
*************************************************/
void CalendarDialog::setCalendarCurrenPage(int year, int month)
{
     m_monthBox->setCurrentIndex(month - 1);
     m_yearText->setText(QString::number(year));
}

/*************************************************
Function Name： showCalendarPreviousMonthInYear
Description: show the previous month in a year
*************************************************/
void CalendarDialog::showCalendarPreviousMonthInYear()
{
    if (m_customCalendar->monthShown() > 1)
    {
        m_customCalendar->setSelectedMonth(m_customCalendar->monthShown() - 1);
        m_monthBox->setCurrentIndex(m_customCalendar->monthShown() - 2);
        m_customCalendar->showPreviousMonth();

    }
}

/*************************************************
Function Name： showCalendarNextMonthInYear
Description: show the next month in a year
*************************************************/
void CalendarDialog::showCalendarNextMonthInYear()
{
    if (m_customCalendar->monthShown() < 12)
    {
        m_customCalendar->setSelectedMonth(m_customCalendar->monthShown() + 1);
        m_monthBox->setCurrentIndex(m_customCalendar->monthShown());
        m_customCalendar->showNextMonth();

    }
}

/*************************************************
Function Name： showCalendarPreviousYear
Description: show the previous year
*************************************************/
void CalendarDialog::showCalendarPreviousYear()
{
    m_yearText->setText(QString::number(m_customCalendar->yearShown() - 1));
}

/*************************************************
Function Name： showCalendarNextYear
Description: show the next year
*************************************************/
void CalendarDialog::showCalendarNextYear()
{
    m_yearText->setText(QString::number(m_customCalendar->yearShown() + 1));

}

/*************************************************
Function Name： showCalendarPreviousMonth
Description: show the previous month
*************************************************/
void CalendarDialog::showCalendarPreviousMonth()
{
    if (m_customCalendar->monthShown() == 1)
    {
        m_monthBox->setCurrentIndex(11);
    }
    else
    {
        m_monthBox->setCurrentIndex(m_customCalendar->monthShown() - 2);
    }
    m_customCalendar->showPreviousMonth();
}

/*************************************************
Function Name： showCalendarNextMonth
Description: show the next month
*************************************************/
void CalendarDialog::showCalendarNextMonth()
{
    if (m_customCalendar->monthShown() == 12)
    {
        m_monthBox->setCurrentIndex(0);
    }
    else
    {
        m_monthBox->setCurrentIndex(m_customCalendar->monthShown());
    }
    m_customCalendar->showNextMonth();
}

/*************************************************
Function Name： getSlectedDate
Description: get slected date
*************************************************/
void CalendarDialog::getSelectedDate()
{
    QDate date = m_customCalendar->selectedDate();
    emit changeLineEditText(date.toString("yyyy-MM-dd"));
    hide();
    m_customCalendar->m_isShowCalendar = false;
}
