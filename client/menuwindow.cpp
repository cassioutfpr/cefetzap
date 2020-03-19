#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QDebug>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QNetworkInterface>
#include <QHostInfo>

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

    User *dumb = new User("Cassio", "127.0.0.1", true);
    listOfUsers.append(*dumb);
    //addNewUserToListWidget(*dumb);


    User *dumb2 = new User("Cassio2", "127.0.0.1", false);
    listOfUsers.append(*dumb2);
    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setTextColor("#4cff00");
    item2->setFont(*font);
    item2->setText(dumb2->getName());
    if(!dumb2->getOnline())
    {
        item2->setTextColor("#ff0004");
    }
    ui->listWidget->addItem(item2);
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

    if(ui->listWidget->selectedItems().size() > 0)
    {
        if(checkIfUserOnline(ui->listWidget->currentItem()->text()))
        {
            setNameMessageWindow(ui->listWidget->currentItem()->text());
            ind_message_window.setModal(true);
            ind_message_window.exec();
        }
    }
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
        QListWidgetItem *item = new QListWidgetItem();
        item->setTextColor("#4cff00");
        item->setFont(*font);
        item->setText(ui->listWidget->currentItem()->text());
        ui->listWidget_2->addItem(item);
    }
}

void MenuWindow::on_removeButton_clicked()
{
    if(ui->listWidget->selectedItems().size() > 0)
    {
        QListWidgetItem *it = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
        delete it;
    }
}

void MenuWindow::closeEvent(QCloseEvent *action)
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    // Do something
    action->accept();
}

bool MenuWindow::checkIfUserOnline(QString text)
{
    for(int i = 0; i < this->listOfUsers.length(); i++)
    {
        if(listOfUsers[i].getName() == text)
        {
            if(listOfUsers[i].getOnline())
                return true;
        }
    }
    return false;
}

void MenuWindow::addNewUserToListWidget(User newUser)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setTextColor("#4cff00");
    item->setFont(*font);
    item->setText("oie");
    if(!newUser.getOnline())
    {
        item->setTextColor("#ff0004");
    }
    ui->listWidget->addItem(item);
}

