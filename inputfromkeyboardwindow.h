#ifndef INPUTFROMKEYBOARDWINDOW_H
#define INPUTFROMKEYBOARDWINDOW_H

#include <QDialog>

namespace Ui {
class InputFromKeyboardWindow;
}

class InputFromKeyboardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InputFromKeyboardWindow(QWidget *parent = nullptr);
    ~InputFromKeyboardWindow();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

signals:
    void inputEntered(const QString &input);

private:
    Ui::InputFromKeyboardWindow *ui;
};

#endif // INPUTFROMKEYBOARDWINDOW_H
