#include "tests.h"
#include "ui_tests.h"

Tests::Tests(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Tests)
    , testObjVec(new vector<Data>)
{
    ui->setupUi(this);
    setWindowTitle("Тесты");

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
    std::ifstream myFileInput("../karina_coursework/tests/tests.txt");
    if (!myFileInput.is_open()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка открытия файла");
        return false;
    }

    std::string line;
    std::string testName;
    std::vector<std::string> testInput;
    std::string expectedOutput;

    while (std::getline(myFileInput, line)) {
        if (line.empty()) continue; // Пропускаем пустые строки

        if (line.find("expected_output") != std::string::npos) {
            // Нашли строку с ожидаемым выводом, сохраняем его
            expectedOutput = line.substr(line.find("=") + 1);
        } else if (line.find("test_") != std::string::npos) {
            // Нашли строку с названием теста, добавляем предыдущий тест (если есть) и начинаем новый
            if (!testName.empty() && !testInput.empty()) {
                processTest(testName, testInput, expectedOutput);
                testInput.clear();
            }
            testName = line;
        } else {
            // Строка с временем, добавляем ее в текущий тест
            testInput.push_back(line);
        }
    }

    // Обрабатываем последний тест (если есть)
    if (!testName.empty() && !testInput.empty()) {
        processTest(testName, testInput, expectedOutput);
    }

    myFileInput.close();
    return true;
}

void Tests::processTest(const string &testName, const vector<string> &testInput, const string &expectedOutput)
{
    int midday = 12 * 3600;
    Data closest(0, 0, 0);
    int counter = 0;

    for (auto &elem : *testObjVec)
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
    for (const auto &input : testInput) {
        result += QString::fromStdString(input) + "\n";
    }
    result += QString("Expected Output: %1\n").arg(QString::fromStdString(expectedOutput));

    // Здесь формируется actualOutput на основе результатов вашей проверки
    string actualOutput;
    if (counter > 0) {
        actualOutput = "Test passed with " + std::to_string(counter) + " valid elements.";
    } else {
        actualOutput = "Test failed: no valid elements found.";
    }

    // Проверяем, прошел ли тест
    bool passed = (expectedOutput == actualOutput);

    if (passed) {
        result += "Result: Passed\n\n";
    } else {
        result += "Result: Failed\n\n";
    }

    ui->testsTextEdit->appendPlainText(result);
}
