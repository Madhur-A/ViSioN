#ifndef DRISHYA_HPP
#define DRISHYA_HPP

#include <QObject>
#include <QWindow>
#include <QObject>
#include <QtCharts>
#include <QLineSeries>
#include <QDateTime>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QChartView>
#include <QLineSeries>
#include <QChart>

#include "beejak.hpp"

class Drishya : public Beejak {
    Q_OBJECT
public:
    explicit Drishya(QString query, bool fromBegin, QString ohlc, int days, Beejak *parent = nullptr);
    //void display() const noexcept(false);
    QChartView *getChartView() const noexcept(false);
    virtual ~Drishya();
private:
    bool m_fromBegin;
    QString instrumentName;
    QString m_ohlc;
    int  m_days;
    QChartView *m_chartView;
};

#endif // DRISHYA_HPP
