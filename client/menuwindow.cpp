#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QDebug>
#include <QListWidgetItem>


MenuWindow::MenuWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    font = new QFont( "Sans Serif" );
    font->setPointSize(10);
    font->setWeight( QFont::Bold );
    connect(this, SIGNAL(setNameMessageWindow(QString)), &ind_message_window, SLOT(setNameMessageWindow(QString)));
    connect(&ind_message_window, SIGNAL(sendMessage(char*)), this, SLOT(sendMessage(char*)));
    connect(this, SIGNAL(receiveMessage(QString)), &ind_message_window, SLOT(receiveMessage(QString)));
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::newLogin(QString login)
{
    this->login = login;

    ui->label_4->setText("Olá, " + login + ".");

    //Adding items to qlistWidget.
    QListWidgetItem *item = new QListWidgetItem();
    item->setTextColor("#4cff00");
    item->setFont(*font);
    item->setText("Maark");
    ui->listWidget->addItem(item);

    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setTextColor("#4cff00");
    item2->setFont(*font);
    item2->setText("Olavo");
    ui->listWidget->addItem(item2);

    QListWidgetItem *item3 = new QListWidgetItem();
    item3->setTextColor("#4cff00");
    item3->setFont(*font);
    item3->setText("Show");
    item3->setTextColor("#ff0004");
    ui->listWidget->addItem(item3);
}

void MenuWindow::sendMessage(char* message)
{
    socket->write(message);
}

void MenuWindow::connect_network()
{
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    qDebug() << "Connecting...";
    socket->connectToHost("127.0.0.1", 80);

    if(!socket->waitForConnected(1000))
        qDebug() << "Error: " << socket->errorString();
}

void MenuWindow::connected()
{
    qDebug() << "Connected";

    socket->write("OLA, MUNDAO");
}

void MenuWindow::disconnected()
{
    qDebug() << "Disconnected";
}

void MenuWindow::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " was written";
}

void MenuWindow::readyRead()
{
    qDebug() << "Reading...";
    QString message_received = socket->readAll();

    emit receiveMessage(message_received);
}

void MenuWindow::on_talkButton_clicked()
{
    connect_network();

    setNameMessageWindow(ui->listWidget->currentItem()->text());
    ind_message_window.setModal(true);
    ind_message_window.exec();
}

void MenuWindow::on_addButton_clicked()
{
    if(ui->listWidget->currentItem()->text() != "")
    {
        for(int i = 0; i < ui->listWidget_2->count(); i++)
        {
            if(ui->listWidget_2->item(i)->text() == ui->listWidget->currentItem()->text())
            return;
        }
        ui->listWidget_2->addItem(ui->listWidget->currentItem()->text());

    }
}

void MenuWindow::on_removeButton_clicked()
{
    if(ui->listWidget_2->currentItem()->text() != "")
    {
        QListWidgetItem *it = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
        delete it;
    }
}
