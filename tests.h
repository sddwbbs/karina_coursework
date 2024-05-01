#ifndef TESTS_H
#define TESTS_H

#include <QDialog>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <QMessageBox>

#include "data.h"

using std::vector;
using std::string;

namespace Ui {
class Tests;
}

class Tests : public QDialog
{
    Q_OBJECT

public:
    explicit Tests(QWidget *parent = nullptr);
    ~Tests();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::Tests *ui;
    vector<Data> *testObjVec;
    bool allChecksPassed;

    bool loadFromFile();

    void processTest(const string &testName, const vector<Data> &testObjVec, const string &expectedOutput);
};

#endif // TESTS_H
