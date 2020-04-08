#include "indmessagewindow.h"
#include "ui_indmessagewindow.h"
#include <QAbstractScrollArea>

IndMessageWindow::IndMessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndMessageWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

IndMessageWindow::~IndMessageWindow()
{
    delete ui;
}

void IndMessageWindow::clearUiAndConversation()
{
    conversation.clear();
    ui->textEdit->clear();
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

void IndMessageWindow::teste()
{
    this->exec();
}

void IndMessageWindow::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        conversation += "Você: " + ui->lineEdit->text() + "\n";
        ui->textEdit->setText(conversation);

        //sending message
        //QByteArray ba = ui->lineEdit->text().toLocal8Bit();
        //char *c_str = ba.data();
        emit sendMessage(ui->lineEdit->text());

        ui->lineEdit->setText("");
    }
}
