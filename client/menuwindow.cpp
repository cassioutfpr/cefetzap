#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QDebug>
#include <QListWidgetItem>


MenuWindow::MenuWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    //ui->listWidget->setSpacing(10);
   // ui->listWidget.set
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::newLogin(QString login)
{
    this->login = login;

    ui->listWidget->addItem("Marcos1");
    ui->listWidget->addItem("Marcos2");
    ui->listWidget->addItem("Marcos3");

    //QListWidgetItem *item = new QListWidgetItem;
    //item->setText("Item");
    //item->
    //item->setIcon(QIcon("image.png"));
    //ui->listWidget->insertItem(4,item);
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
    qDebug() << socket->readAll();
}

void MenuWindow::on_talkButton_clicked()
{
    connect_network();
    ui->talkButton->setText(ui->listWidget->currentItem()->text());
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
