#ifndef PANEL_HPP
#define PANEL_HPP

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCompleter>
#include <QRadioButton>
#include "drishya.hpp"


class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);
signals:
public slots:
private:
    QString instrumentName; QString ohlcString;
    bool fromBeginning; int howManyDays;
    Drishya *delta;
};

#endif // PANEL_HPP
