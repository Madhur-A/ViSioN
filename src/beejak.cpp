#include "beejak.hpp"

Beejak::Beejak(QString query, QObject *parent):
    QObject(parent),
    instrumentName(query) {

    //QString filePath = "../ViSioN/.data/"+instrumentName+".csv";
    QString filePath = "/home/ank/XOXO/CSVD/"+instrumentName+".csv";
    QFile fileObject(filePath);
    if(!fileObject.open(QIODevice::ReadOnly)) {        
        QMessageBox::information(Q_NULLPTR, "Error!", fileObject.errorString().toUpper()+
                                 "! Try downloading the instrument first!");
        this->fileFound = false;
        //exit(2);
    } else {
        QTextStream inStream(&fileObject);
        QString allString   = inStream.readAll();
        QStringList stList  = allString.split('\n');
        for(int i=1; i<stList.size()-1; ++i) {
            QStringList splitted = stList.at(i).split(',');
            if((splitted.at(2).toDouble() != 0.0) && (splitted.at(5).toDouble() != 0.0)) {
                dates.append(        splitted.at(0));
                open.append(         splitted.at(1).toDouble());
                high.append(         splitted.at(2).toDouble());
                low.append(          splitted.at(3).toDouble());
                unadjClose.append(   splitted.at(4).toDouble());
                close.append(        splitted.at(5).toDouble());
                volume.append(       splitted.at(6).toDouble());
            }
        }
    }
    fileObject.close();
}
