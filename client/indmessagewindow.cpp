#include "indmessagewindow.h"
#include "ui_indmessagewindow.h"

IndMessageWindow::IndMessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndMessageWindow)
{
    ui->setupUi(this);
}

IndMessageWindow::~IndMessageWindow()
{
    delete ui;
}

void IndMessageWindow::setNameMessageWindow(QString name)
{
    this->name = name;
    ui->label->setText(name);
}

void IndMessageWindow::receiveMessage(QString message)
{
    conversation += this->name + ": " + message + "\n";
    ui->textEdit->setText(conversation);
}

void IndMessageWindow::on_pushButton_clicked()
{
    conversation += "Você: " + ui->lineEdit->text() + "\n";
    ui->textEdit->setText(conversation);

    //sending message
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    char *c_str = ba.data();
    emit sendMessage(c_str);

    ui->lineEdit->setText("");
}
