#ifndef BEEJAK_HPP
#define BEEJAK_HPP

#include <QObject>
#include <QtCore>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <cstdio>
#include <cstdlib>

class Beejak : public QObject {
    Q_OBJECT
public:
    explicit Beejak(QString query, QObject *parent = nullptr);
signals:
public slots:
protected:
    QString instrumentName;
    QVector<QString> dates;
    QVector<double>  open;
    QVector<double>  high;
    QVector<double>  low;
    QVector<double>  unadjClose;
    QVector<double>  close;
    QVector<double>  volume;
    bool fileFound = true;
};

#endif // BEEJAK_HPP
