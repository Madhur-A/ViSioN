#include "drishya.hpp"
#include <QDebug>


Drishya::Drishya(QString query, bool fromBegin, QString ohlc, int days, Beejak *parent):
    Beejak(query, parent), m_fromBegin(fromBegin), instrumentName(query),
    m_ohlc(ohlc), m_days(days) {
    QVector<double> valueVector;
    if(this->m_ohlc == "Open") {
        valueVector = this->open;
    } else if(this->m_ohlc == "High") {
        valueVector = this->high;
    } else if(this->m_ohlc == "Low") {
        valueVector = this->low;
    } else if(this->m_ohlc == "Volume") {
        valueVector = this->volume;
    } else if(this->m_ohlc == "UN Close") {
        valueVector = this->unadjClose;
    } else { valueVector = this->close; }

    const QVector<double> valueVektor = valueVector;
    const QVector<QString> dateVektor = this->dates;
    QLineSeries *lineSeries = new QLineSeries;
    QDateTime dt;
    if(this->fileFound == true) {
        if(this->m_fromBegin == true) {
            for(int i=0; i<this->m_days; ++i) {
                dt.setDate(QDate::fromString(QString(dateVektor.at(i)), Qt::ISODate));
                lineSeries->append(dt.toMSecsSinceEpoch(), valueVektor.at(i));
            }
        } else {
            for(int i=dateVektor.size()-this->m_days; i<dateVektor.size(); ++i) {
                dt.setDate(QDate::fromString(QString(dateVektor.at(i)), Qt::ISODate));
                lineSeries->append(dt.toMSecsSinceEpoch(), valueVektor.at(i));
            }
        }
    }

    QChart *chart = new QChart;
    chart->addSeries(lineSeries);
    chart->legend()->hide();
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(10);
    axisX->setFormat("dd/MM/yyyy");
    chart->addAxis(axisX, Qt::AlignBottom);
    lineSeries->attachAxis(axisX);

    QValueAxis *axisY  = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisY);

    this->m_chartView = new QChartView(chart);
    this->m_chartView->setRenderHint(QPainter::Antialiasing);
    this->m_chartView->setRubberBand(QChartView::RectangleRubberBand);
    this->m_chartView->setMinimumSize(800, 600);
}

QChartView *Drishya::getChartView() const noexcept(false) {
    return this->m_chartView;
}

Drishya::~Drishya() {
    this->m_chartView->deleteLater();
}

