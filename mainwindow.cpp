#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_getAnswer_clicked()
{
    int midday = 12 * 3600;
    Data closest(0, 0, 0);
    int counter = 0;

    for (auto &elem : dataObjVec)
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
}
