#include "groupmessagewindow.h"
#include "ui_groupmessagewindow.h"

GroupMessageWindow::GroupMessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupMessageWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

GroupMessageWindow::~GroupMessageWindow()
{
    delete ui;
}

void GroupMessageWindow::clearUiAndConversation()
{
    conversation.clear();
    ui->textEdit->clear();
    this->name = "";
}

void GroupMessageWindow::setNameMessageWindow(QString name)
{
    this->name += name;

    ui->label->setText(this->name);
}

void GroupMessageWindow::receiveMessage(QString message, QString whoSaid)
{
    conversation += whoSaid + ": " + message + "\n";
    ui->textEdit->setText(conversation);
}

void GroupMessageWindow::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        conversation += "Você: " + ui->lineEdit->text() + "\n";
        ui->textEdit->setText(conversation);

        //sending message
        //QByteArray ba = ui->lineEdit->text().toLocal8Bit();
        //char *c_str = ba.data();
        emit sendMessage(this->name, true);
        emit sendMessage(ui->lineEdit->text(), false);

        ui->lineEdit->setText("");
    }
}
