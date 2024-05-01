#include "tests.h"
#include "ui_tests.h"

Tests::Tests(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Tests)
    , testObjVec(new vector<Data>)
    , allChecksPassed(true)
{
    ui->setupUi(this);
    setWindowTitle("Тесты");

    this->resize(400, 700);
    loadFromFile();
}

Tests::~Tests()
{
    delete ui;
}

void Tests::on_closeBtn_clicked()
{
    close();
}

bool Tests::loadFromFile()
{
    std::ifstream myFileInput("../tests/tests.txt");
    if (!myFileInput.is_open()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка открытия файла");
        return false;
    }

    string line;
    string testName;
    vector<Data> testObjVec;
    string expectedOutput;

    while (std::getline(myFileInput, line)) {
        if (line.empty()) continue;

        if (line.find("expected_output") != string::npos) {
            expectedOutput = line.substr(line.find("=") + 2);
        } else if (line.find("test_") != string::npos) {
            testName = line;
        } else {
            std::istringstream lineStream(line);
            string hh, mm, ss;
            try {
                std::getline(lineStream, hh, ':');
                std::getline(lineStream, mm, ':');
                std::getline(lineStream, ss, ':');

                Data testObj;
                testObj.setHours(std::stoi(hh));
                testObj.setMinutes(std::stoi(mm));
                testObj.setSeconds(std::stoi(ss));
                testObjVec.push_back(testObj);
            } catch (const std::invalid_argument& e) {
                QMessageBox::critical(this, "Ошибка", "Ошибка при обработке входных данных: недопустимые данные в строке.");
                return false;
            }
        }

        if (!expectedOutput.empty()) {
            processTest(testName, testObjVec, expectedOutput);
            testName = "";
            testObjVec.clear();
            expectedOutput = "";
        }
    }

    myFileInput.close();

    if (allChecksPassed) ui->testsTextEdit->appendPlainText("All checks have been passed!");
    else ui->testsTextEdit->appendPlainText("Not all checks have been passed :(");

    return true;
}

void Tests::processTest(const string &testName, const vector<Data> &testObjVec, const string &expectedOutput)
{
    int midday = 12 * 3600;
    Data closest(-1, -1, -1);
    int counter = 0;

    for (auto &elem : testObjVec)
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

    QString result = QString("Test Name: %1\nTest Input:\n").arg(QString::fromStdString(testName));
    for (const auto &input : testObjVec) {
        result += QString::number(input.getHours())
                  + ':'
                  + QString::number(input.getMinutes())
                  + ':'
                  + QString::number(input.getSeconds())
                  + '\n';
    }
    result += QString("Expected Output: %1\n").arg(QString::fromStdString(expectedOutput));
    result += QString("Test passed with %1 valid elements\n").arg(QString::number(counter));

    string actualOutput;
    actualOutput = std::to_string(counter) + ';'
                   + std::to_string(closest.getHours())
                   + ':'
                   + std::to_string(closest.getMinutes())
                   + ':'
                   + std::to_string(closest.getSeconds());
    result += QString("Actual output: %1\n").arg(QString::fromStdString(actualOutput));

    bool passed = (expectedOutput == actualOutput);
    if (!passed) allChecksPassed = false;

    if (passed) {
        result += "Result: PASSED\n\n";
    } else {
        result += "Result: FAILED\n\n";
    }

    ui->testsTextEdit->appendPlainText(result);
}
