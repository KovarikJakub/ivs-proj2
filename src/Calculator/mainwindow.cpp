#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtMath>
#include "../lib/math_lib.h"

enum Operation
{
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    ROOT,
    FACT,
    ABS,
    NOP
};

double calcValue = 0;

bool clearDisplayOnNextDigitPress = false;

Operation activeOperation = NOP;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Display->setText(QString::number(calcValue));
    ui->label_preview->clear();

    QPushButton* digitButtons[10];
    for(int i = 0; i < 10; ++i)
    {
        QString btnName = "btn_digit" + QString::number(i);
        digitButtons[i] = MainWindow::findChild<QPushButton*>(btnName);
        connect(digitButtons[i], SIGNAL(released()), this, SLOT(DigitPressed()));
    }

    // binary ops
    connect(ui->btn_add, SIGNAL(released()),  this, SLOT(BinaryOperationPressed()));
    connect(ui->btn_sub, SIGNAL(released()),  this, SLOT(BinaryOperationPressed()));
    connect(ui->btn_div, SIGNAL(released()),  this, SLOT(BinaryOperationPressed()));
    connect(ui->btn_mul, SIGNAL(released()),  this, SLOT(BinaryOperationPressed()));
    connect(ui->btn_pow, SIGNAL(released()),  this, SLOT(BinaryOperationPressed()));
    connect(ui->btn_root, SIGNAL(released()), this, SLOT(BinaryOperationPressed()));

    // u,nary ops
    connect(ui->btn_abs, SIGNAL(released()), this, SLOT(UnaryOperationPressed()));
    connect(ui->btn_fact, SIGNAL(released()), this, SLOT(UnaryOperationPressed()));

    // comma
    connect(ui->btn_comma, SIGNAL(released()), this, SLOT(CommaButtonPressed()));

    // equals
    connect(ui->btn_equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    // clear
    connect(ui->btn_clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DigitPressed()
{
    QPushButton *buttonSender = (QPushButton*)sender();

    // if the first operand is being typed, clear the preview label and display
    if(clearDisplayOnNextDigitPress)
    {
        ui->lineEdit_Display->setText("0");
        ui->label_preview->clear();
        clearDisplayOnNextDigitPress = false;
    }

    QString buttonValue = buttonSender->text();
    QString displayValue = ui->lineEdit_Display->text();
    double displayValueDbl = displayValue.toDouble();

    // if theres a zero in the display, override it, othewise, append digits
    if( displayValueDbl == 0 || displayValueDbl == 0.0)
    {
        ui->lineEdit_Display->setText(buttonValue);
    }
    else // append
    {
        QString newValue = displayValue + buttonValue;
        double newValueDbl = newValue.toDouble();

        ui->lineEdit_Display->setText(QString::number(newValueDbl, 'g', 16));
    }
}

//void MainWindow::CommaButtonPressed()
//{
//
//}

Operation GetOperationType(QPushButton* button)
{
    QString btnName = button->objectName();

    if(QString::compare(btnName, "btn_div",  Qt::CaseInsensitive) == 0)
        return DIV;
    if(QString::compare(btnName, "btn_mul",  Qt::CaseInsensitive) == 0)
        return MUL;
    if(QString::compare(btnName, "btn_sub",  Qt::CaseInsensitive) == 0)
        return SUB;
    if(QString::compare(btnName, "btn_add",  Qt::CaseInsensitive) == 0)
        return ADD;
    if(QString::compare(btnName, "btn_pow",  Qt::CaseInsensitive) == 0)
        return POW;
    if(QString::compare(btnName, "btn_root", Qt::CaseInsensitive) == 0)
        return ROOT;
    if(QString::compare(btnName, "btn_fact", Qt::CaseInsensitive) == 0)
        return FACT;
    if(QString::compare(btnName, "btn_abs",  Qt::CaseInsensitive) == 0)
        return ABS;

    return NOP;
}

QString GetOperationSymbol(Operation operation)
{
    switch(operation)
    {
    case ADD : return "+";
    case SUB : return "-";
    case MUL : return "×";
    case DIV : return "÷";
    case POW : return "^";
    case ROOT: return "√";
    default:break;
    }

    return "?";
}

bool IsBinaryOperation(Operation op)
{
    return (op == MUL  ||
            op == DIV  ||
            op == SUB  ||
            op == ADD  ||
            op == ROOT ||
            op == POW
            );
}

bool IsUnaryOperation(Operation op)
{
    return (op == FACT  ||
            op == ABS
            );
}

void UpdatePreviewLabel(Ui::MainWindow *ui)
{
    QString symbol = GetOperationSymbol(activeOperation);
    QString newPreview = QString::number(calcValue) + " " + symbol + " ";
    ui->label_preview->setText(newPreview);
}

void AppendLastOperandToPreviewLabel(Ui::MainWindow *ui, const QString& valueToAppend)
{
    QString oldPreview = ui->label_preview->text();
    QString newPreview = oldPreview + valueToAppend + " = ";
    ui->label_preview->setText(newPreview);
}


void MainWindow::BinaryOperationPressed()
{
    QPushButton *buttonSender = (QPushButton*)sender();

    Operation selectedOperation = GetOperationType(buttonSender);

    bool selectedOperationChanged = (activeOperation != NOP);

    activeOperation = selectedOperation;

    // we do not want to clear the preview
    clearDisplayOnNextDigitPress = false;

    // if multiple operations are pressed, do not rewrite calcValue with an empty display value
    if(selectedOperationChanged)
    {
        UpdatePreviewLabel(ui);
        return;
    }

    QString displayValue = ui->lineEdit_Display->text();
    calcValue  = displayValue.toDouble();

    UpdatePreviewLabel(ui);

    // clear the display
    ui->lineEdit_Display->clear();
}

void UpdatePreviewAfterUnaryExpression(Ui::MainWindow *ui, Operation operation, const QString& newValue)
{
    QString newPreview;
    switch(operation)
    {
    case FACT: newPreview = newValue + "! = " ; break;
    case ABS:  newPreview = "|" + newValue + "| = "; break;
    default: return;
    }

    ui->label_preview->setText(newPreview);
}

void MainWindow::UnaryOperationPressed()
{
    QPushButton *buttonSender = (QPushButton*)sender();
    Operation selectedOperation = GetOperationType(buttonSender);


    QString oldDisplayValue = ui->lineEdit_Display->text();
    double oldDisplayValueDbl = oldDisplayValue.toDouble();

    double ans = 0;
    // perform the operation instantly
    switch(selectedOperation)
    {
    case FACT: ans = Factorial(oldDisplayValueDbl);  break;
    case ABS:  ans = Abs(oldDisplayValueDbl); break;
    default: return;
    }

    UpdatePreviewAfterUnaryExpression(ui, selectedOperation, oldDisplayValue);
    clearDisplayOnNextDigitPress = true;
    ui->lineEdit_Display->setText(QString::number(ans));
}


void MainWindow::EqualButtonPressed()
{
    if(activeOperation == NOP)
    {
        return;
    }

    double ans = 0;
    QString displayValue = ui->lineEdit_Display->text();
    double displayValueDbl = displayValue.toDouble();

    switch(activeOperation)
    {
    case ADD: ans = Add(calcValue,displayValueDbl); break;
    case SUB: ans = Sub(calcValue,displayValueDbl); break;
    case DIV: ans = Div(calcValue,displayValueDbl); break;
    case MUL: ans = Mul(calcValue,displayValueDbl); break;
    case POW: ans = Pow(calcValue,displayValueDbl); break;
    case ROOT: ans = Root(calcValue,displayValueDbl); return ; break;
    }

    ui->lineEdit_Display->setText(QString::number(ans, 'g', 16));
    AppendLastOperandToPreviewLabel(ui, displayValue);

    clearDisplayOnNextDigitPress = true;
    // reset active operation
    activeOperation = NOP;
}

void MainWindow::ClearButtonPressed()
{
    ui->label_preview->clear();
    ui->lineEdit_Display->setText("0");
}

void MainWindow::on_btn_digit1_clicked()
{

}

