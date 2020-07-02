#include "panel.hpp"
#include <QStringList>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

inline std::vector<std::string> fetch_list() noexcept(false) {
    const std::string file_path = "/home/ank/Factory/Kurtakan/ViSioN/nyse.csv";
    std::vector<std::string> file_list;
    std::ifstream iof(file_path);
    if(!iof) {
        puts("No file found!"); exit(2);
    } else {
        while(iof.good()) {
            std::string feeder;
            std::getline(iof, feeder, '\n');
            file_list.emplace_back(feeder);
            feeder.clear();
        }
    }
    file_list.erase(file_list.begin());
    file_list.erase(file_list.end());
    file_list.shrink_to_fit();
    std::sort(file_list.begin(), file_list.end(), [](std::string const &a, std::string const &b){
        return a>b;
    }); // this lambda is pointless, nevertheless provided here to suppress
    // the anonying compiler warnings on some architectures
    return file_list;
}

inline void layoutCleaner(QLayout *layout) noexcept(false) {
   if(!layout) return;
   while (QLayoutItem *loItem = layout->takeAt(0)) {
      delete loItem->widget();
      layoutCleaner(loItem->layout());
   }
}

inline QString displayAboutText() noexcept(false) {
    QString aboutPointless = "ViSioN\nA Lightweight Display for Equities.\n\nCopyright © 2020 Varush Varsha\nvarush.varsha777@gmail.com\n\n\n"
                             "The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY"
                             " AND FITNESS FOR A PARTICULAR PURPOSE.";
    return aboutPointless;
}

Panel::Panel(QWidget *parent) : QWidget(parent) {
    QPushButton *buttonInfo = new QPushButton("About");
    QPushButton *buttonExit = new QPushButton("Exit");
    QPushButton *buttonLoad = new QPushButton("Load");
    QObject::connect(buttonExit, &QAbstractButton::clicked, [this](){ this->close(); });    
    QLabel *daysLabel   = new QLabel("Days: ");
    QLineEdit *daysOf   = new QLineEdit;
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setText("DWARKESH");
    const std::vector<std::string> wordListVector = fetch_list();
    QStringList wordList;
    for(const std::string &e: wordListVector) { wordList << QString::fromStdString(e); }
    QCompleter *completer   = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit->setCompleter(completer);

    lineEdit->setMaximumSize(250, 40);
    daysOf->setMaximumSize(150, 40);
    daysOf->setText("55");
    QLabel    *labelInstrument = new QLabel("Instrument ID: ");
    QRadioButton *rButtonBegin = new QRadioButton("From Beginning");
    QRadioButton *rButtonEnd   = new QRadioButton("From End");
    rButtonEnd->setChecked(true);

    QLineEdit  *selection      = new QLineEdit;
    QStringList selectionWordsList;
    selectionWordsList << "Open" << "High" << "Low" << "Close" << "Volume" << "UN Close";
    QCompleter *ohlcCompleter = new QCompleter(selectionWordsList, this);
    ohlcCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    selection->setCompleter(ohlcCompleter);
    selection->setFixedSize(250, 40);
    selection->setText("Close");

    QHBoxLayout *chartLayout = new QHBoxLayout;    

    ///// connection for buttons
    QObject::connect(buttonLoad, &QAbstractButton::clicked, [this, lineEdit, rButtonBegin, selection, daysOf, chartLayout](){
        layoutCleaner(chartLayout);
        this->instrumentName =  lineEdit->text().toUpper();
        this->fromBeginning  =  rButtonBegin->isChecked();
        this->ohlcString     =  selection->text();
        this->howManyDays    =  daysOf->text().toInt();
        this->delta          =  new Drishya(this->instrumentName, this->fromBeginning,
                                            this->ohlcString, this->howManyDays);
        QChartView *mainCharter = this->delta->getChartView();
        chartLayout->addWidget(mainCharter);
    });

    QObject::connect(buttonInfo, &QAbstractButton::clicked, [this](){
        QMessageBox::about(this, "ViSioN", displayAboutText());
    });

    ///// the final layout
    QVBoxLayout *finalLayout = new QVBoxLayout;

    ///// adding goodies to panel
    QHBoxLayout *panelLayout = new QHBoxLayout;
    panelLayout->addWidget(labelInstrument);
    panelLayout->addWidget(lineEdit);
    panelLayout->addWidget(rButtonBegin);
    panelLayout->addWidget(rButtonEnd);
    panelLayout->addWidget(selection);
    panelLayout->addWidget(daysLabel);
    panelLayout->addWidget(daysOf);
    panelLayout->addWidget(buttonLoad);
    panelLayout->addWidget(buttonInfo);
    panelLayout->addWidget(buttonExit);

    finalLayout->addLayout(panelLayout);
    finalLayout->addLayout(chartLayout);


    this->setLayout(finalLayout);
    this->setMinimumWidth(1200);
    if(this->findChildren<QWidget*>("chartLayout").size() == 0) {
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    } else {
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    }

}
