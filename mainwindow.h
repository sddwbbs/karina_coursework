#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "data.h"

using std::string;
using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputFromFileBtn_clicked();

    void on_inputFromKeyboardBtn_clicked();

    void on_getAnswerBtn_clicked();

private:
    Ui::MainWindow *ui;
    vector<Data> *dataObjVec;

    bool loadFromFile(const QString &fileName);
};
#endif // MAINWINDOW_H
