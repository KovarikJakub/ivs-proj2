#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtMath>
#include "../lib/math_lib.h"
#include <QtWidgets/QMessageBox>

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

enum OpResultCode
{
    ERR_INV_INPUT,
    ERR_ZERO_DIV,
    ERR_OVERFLOW,
    OK,
};

double calcValue = 0;

bool clearDisplayOnNextDigitPress = false;
bool areButtonsLockedAfterError = false;

Operation activeOperation = NOP;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Displayy->setText(QString::number(calcValue));
    ui->label_preview->clear();


    // digit buttons
    QPushButton* digitButtons[10];
    for(int i = 0; i < 10; ++i)
    {
        QString btnName = "btn_digit" + QString::number(i);
        digitButtons[i] = MainWindow::findChild<QPushButton*>(btnName);
        connect(digitButtons[i], SIGNAL(released()), this, SLOT(DigitPressed()));
    }
    connect(ui->btn_digit000, SIGNAL(released()), this, SLOT(DigitPressed()));

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

    // help
    connect(ui->btn_help, SIGNAL(released()), this, SLOT(HelpButtonPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void SetOperationButtonsStateAfterError(Ui::MainWindow *ui, bool enabled)
{
    ui->btn_abs->setEnabled(enabled);
    ui->btn_fact->setEnabled(enabled);
    ui->btn_pow->setEnabled(enabled);
    ui->btn_comma->setEnabled(enabled);
    ui->btn_equals->setEnabled(enabled);
    ui->btn_div->setEnabled(enabled);
    ui->btn_sub->setEnabled(enabled);
    ui->btn_mul->setEnabled(enabled);
    ui->btn_add->setEnabled(enabled);
    ui->btn_root->setEnabled(enabled);
    ui->btn_digit000->setEnabled(enabled);
}

void MainWindow::DigitPressed()
{
    QPushButton *buttonSender = (QPushButton*)sender();

    // if the first operand is being typed, clear the preview label and display
    if(clearDisplayOnNextDigitPress)
    {
        ui->lineEdit_Displayy->setText("0");
        ui->label_preview->clear();
        clearDisplayOnNextDigitPress = false;
    }

    if(areButtonsLockedAfterError)
    {
        SetOperationButtonsStateAfterError(ui, true);
    }

    QString buttonValue = buttonSender->text();
    QString displayValue = ui->lineEdit_Displayy->text();
    double displayValueDbl = displayValue.toDouble();

    // if theres a zero in the display, override it, othewise, append digits
    if( displayValueDbl == 0 || displayValueDbl == 0.0)
    {
        ui->lineEdit_Displayy->setText(buttonValue);
    }
    else // append
    {
        QString newValue = displayValue + buttonValue;
        double newValueDbl = newValue.toDouble();

        ui->lineEdit_Displayy->setText(QString::number(newValueDbl, 'g', 16));
    }
}

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

    QString displayValue = ui->lineEdit_Displayy->text();
    calcValue  = displayValue.toDouble();

    UpdatePreviewLabel(ui);

    // clear the display
    ui->lineEdit_Displayy->clear();
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

void HandleErrorState(Ui::MainWindow *ui, OpResultCode resCode)
{
    QString errorMsg;
    switch(resCode){
    case ERR_INV_INPUT: errorMsg = "Invalid Input"; break;
    case ERR_OVERFLOW: errorMsg = "Overflow"; break;
    case ERR_ZERO_DIV: errorMsg = "Can't divide by 0"; break;
    default:break;
    }

    ui->lineEdit_Displayy->setText(errorMsg);
    SetOperationButtonsStateAfterError(ui,false);
    areButtonsLockedAfterError = true;
    ui->label_preview->clear();
}

void MainWindow::UnaryOperationPressed()
{
    QPushButton *buttonSender = (QPushButton*)sender();
    Operation selectedOperation = GetOperationType(buttonSender);


    QString oldDisplayValue = ui->lineEdit_Displayy->text();
    double oldDisplayValueDbl = oldDisplayValue.toDouble();

    double ans = 0;
    OpResultCode resCode = OK;

    // perform the operation instantly
    switch(selectedOperation)
    {
    case FACT:
        try{
            ans = Factorial(oldDisplayValueDbl);
        } catch (std::exception ex){
            resCode = ERR_OVERFLOW;
        }
        break;
    case ABS:
        ans = Abs(oldDisplayValueDbl);
        break;
    default: return;
    }


    if(resCode != OK)
    {
        HandleErrorState(ui, resCode);
        return;
    }

    UpdatePreviewAfterUnaryExpression(ui, selectedOperation, oldDisplayValue);
    clearDisplayOnNextDigitPress = true;
    ui->lineEdit_Displayy->setText(QString::number(ans));
}


void MainWindow::EqualButtonPressed()
{
    if(activeOperation == NOP)
    {
        return;
    }

    double ans = 0;
    QString displayValue = ui->lineEdit_Displayy->text();
    double displayValueDbl = displayValue.toDouble();
    OpResultCode resCode = OK;

    switch(activeOperation)
    {
    case ADD:
        try {
            ans = Add(calcValue,displayValueDbl);
        } catch (std::exception ex) {
            resCode = ERR_OVERFLOW;
        }
        break;
    case SUB:
        try {
            ans = Sub(calcValue,displayValueDbl);
        } catch (std::exception ex){
            resCode = ERR_OVERFLOW;
        }
        break;
    case DIV:
        try {
            ans = Div(calcValue,displayValueDbl);
        } catch (std::invalid_argument ex_invarg){
            resCode = ERR_ZERO_DIV;
        } catch (std::out_of_range ex_overflow){
            resCode = ERR_OVERFLOW;
        }
        break;
    case MUL:
        try {
            ans = Mul(calcValue,displayValueDbl);
        } catch (std::exception ex){
            resCode = ERR_OVERFLOW;
        }
        break;
    case POW:
        try {
            ans = Pow(calcValue,displayValueDbl);
        } catch (std::exception ex){
            resCode = ERR_OVERFLOW;
        }
        break;
    case ROOT:
        try {
            ans = Root(displayValueDbl,calcValue);
        } catch (std::exception ex){
            resCode = ERR_INV_INPUT;
        }
        break;
    }

    if(resCode != OK)
    {
        HandleErrorState(ui, resCode);
        return;
    }

    ui->lineEdit_Displayy->setText(QString::number(ans, 'g', 16));
    AppendLastOperandToPreviewLabel(ui, displayValue);

    clearDisplayOnNextDigitPress = true;
    // reset active operation
    activeOperation = NOP;
}

void MainWindow::ClearButtonPressed()
{
    if(areButtonsLockedAfterError)
    {
        SetOperationButtonsStateAfterError(ui, true);
    }

    ui->label_preview->clear();
    ui->lineEdit_Displayy->setText("0");
}

void MainWindow::CommaButtonPressed()
{
    QString displayValue = ui->lineEdit_Displayy->text();
    // the comma is already used
    if(displayValue.contains("."))
    {
        return;
    }

    ui->lineEdit_Displayy->setText(displayValue + ".");
}

void MainWindow::HelpButtonPressed()
{
    QMessageBox::information(this, tr("Help"), R"(
1. Basic Arithmetic Operations:
   - Addition: Simply type the numbers you want to add and press the "+" button.
   - Subtraction: Type the numbers you want to subtract and press the "-" button.
   - Multiplication: Enter the numbers you want to multiply and press the "x" button.
   - Division: Type the dividend, followed by the division sign "/", and then the divisor.

2. Power Function (pow):
   - To calculate the power of a number, type the base followed by the "^" symbol and then the exponent. For example, to calculate 2 raised to the power of 3, type "2 ^ 3" and press "=".

3. Root Function:
   - To calculate the square root or any other root of a number,type the root base, followed by root symbol (√), followed by the number. For example, to find the square root of 25, type "2√25" and press "=".

4. Absolute Value (abs):
   - To find the absolute value of a number, simply type the number and press the "abs" button. For example, to find the absolute value of -5, type "-5" and press "abs".

5. Factorial Function (fact):
   - To calculate the factorial of a number, type the number followed by the "!" symbol. For example, to calculate the factorial of 5, type "5!" and press "=".

6. Result Display:
   - After entering the expression, press the "=" button to see the result displayed on the screen.

7. Clearing the Screen:
   - To clear the current input or result, press the "C" button.

8. Decimal Points:
   - Use the decimal point (.) button to input decimal numbers for calculations.
)");


}

