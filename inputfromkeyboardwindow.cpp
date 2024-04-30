#include "inputfromkeyboardwindow.h"
#include "ui_inputfromkeyboardwindow.h"

InputFromKeyboardWindow::InputFromKeyboardWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InputFromKeyboardWindow)
{
    ui->setupUi(this);
    setWindowTitle("Ввод");
}

InputFromKeyboardWindow::~InputFromKeyboardWindow()
{
    delete ui;
}

void InputFromKeyboardWindow::on_okBtn_clicked()
{
    QString input = ui->inputFromKeyboadrdTextEdit->toPlainText();
    emit inputEntered(input);
    close();
}

void InputFromKeyboardWindow::on_cancelBtn_clicked()
{
    close();
}

