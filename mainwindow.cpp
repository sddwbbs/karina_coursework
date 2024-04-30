#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataObjVec(new vector<Data>)
{
    ui->setupUi(this);
    setWindowTitle(" ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputFromFileBtn_clicked()
{
    QFileDialog *fDialog = new QFileDialog(this);
    fDialog->setAttribute(Qt::WA_DeleteOnClose);

    QString fileName = fDialog->getOpenFileName(this, tr("Open Document"), QDir::cleanPath("../karina_coursework/"),
                                                "Text Files (*.txt *.db)", nullptr, QFileDialog::DontUseNativeDialog);

    if (fileName.isEmpty()) return;

    if (loadFromFile(fileName))
        ui->statusbar->showMessage("Данные успешно загружены", 1500);
    else
        ui->statusbar->showMessage("Ошибка при загрузке данных из файла", 1500);
}

void MainWindow::on_inputFromKeyboardBtn_clicked()
{

}

void MainWindow::on_getAnswerBtn_clicked()
{
    int midday = 12 * 3600;
    Data closest(0, 0, 0);
    int counter = 0;

    for (auto &elem : *dataObjVec)
    {
        if (elem.getHours() >= 0
            && elem.getHours() <= 24
            && elem.getMinutes() >= 0
            && elem.getMinutes() <= 60
            && elem.getSeconds() >= 0
            && elem.getSeconds() <= 60)
        {
            ++counter;
            if (std::abs(midday - elem.toSeconds()) < std::abs(midday - closest.toSeconds()))
                closest = elem;
        }
    }

    ui->answerTextEdit->clear();
    ui->answerTextEdit->appendPlainText("Количество элементов удовлетворяющих условию: " + QString::number(counter)
                                        + '\n'
                                        + "Самое близкое к полудню время: "
                                        + QString::number(closest.getHours())
                                        + ':'
                                        + QString::number(closest.getMinutes())
                                        + ':'
                                        + QString::number(closest.getSeconds()));
}

bool MainWindow::loadFromFile(const QString &fileName)
{
    std::ifstream myFileInput(fileName.toStdString());
    char delim = '\n';

    if (!myFileInput.is_open()) {
        return false;
    }

    std::string firstLine;
    std::getline(myFileInput, firstLine);

    if (firstLine.find(';') != std::string::npos)
        delim = ';';

    myFileInput.seekg(0);

    std::string segment;
    while (std::getline(myFileInput, segment, delim)) {
        Data dataObj;
        std::istringstream segStream(segment);
        std::string hh, mm, ss;
        std::getline(segStream, hh, ':');
        std::getline(segStream, mm, ':');
        std::getline(segStream, ss, ':');
        dataObj.setHours(std::stoi(hh));
        dataObj.setMinutes(std::stoi(mm));
        dataObj.setSeconds(std::stoi(ss));
        dataObjVec->push_back(dataObj);
    }

    return true;
}

