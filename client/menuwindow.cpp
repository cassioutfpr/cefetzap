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
    socket = new QTcpSocket(this);
    ui->setupUi(this);
    font = new QFont( "Sans Serif" );
    font->setPointSize(10);
    font->setWeight( QFont::Bold );

    // create a timer
    //timerId = startTimer(1000);
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
          this, SLOT(MyTimerSlot()));

    // msec


    //ind message window
    connect(this, SIGNAL(setNameMessageWindow(QString)), &indMessageWindow, SLOT(setNameMessageWindow(QString)));
    connect(&indMessageWindow, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    connect(this, SIGNAL(receiveMessage(QString)), &indMessageWindow, SLOT(receiveMessage(QString)));

    //group message window
    connect(this, SIGNAL(setNameGroupMessageWindow(QString)), &groupMessageWindow, SLOT(setNameMessageWindow(QString)));
    connect(&groupMessageWindow, SIGNAL(sendMessage(QString, bool)), this, SLOT(sendGroupMessage(QString, bool)));
    connect(this, SIGNAL(receiveGroupMessage(QString,QString)), &groupMessageWindow, SLOT(receiveMessage(QString,QString)));

    connect(this, SIGNAL(teste()), &indMessageWindow, SLOT(teste()));

    receiveListOfUsersOnline = true;
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::newLogin(QString login)
{
    this->login = login;

    ui->label_4->setText("Olá, " + login + ".");

    connect_network();
}

void MenuWindow::sendMessage(QString message)
{
    std::string s;
    if(message.length()/10 == 0)
        s = "00" + std::to_string(message.length());
    else if(message.length()/100 == 0)
        s = "0" + std::to_string(message.length());
    else
        s = std::to_string(message.length());
    char const *pchar = s.c_str();  //use char const* as target type
    socket->write(pchar);

    QByteArray ba = message.toLocal8Bit();
    char *c_str = ba.data();
    socket->write(c_str);
}

void MenuWindow::sendGroupMessage(QString message,  bool sendListOfGroupUsersToServer)
{
    std::string s;
    if(message.length()/10 == 0)
        s = "00" + std::to_string(message.length());
    else if(message.length()/100 == 0)
        s = "0" + std::to_string(message.length());
    else
        s = std::to_string(message.length());
    if(sendListOfGroupUsersToServer)
        s = "0" + s;
    else
        s = "1" + s;
    char const *pchar = s.c_str();  //use char const* as target type
    socket->write(pchar);
    QByteArray ba = message.toLocal8Bit();
    char *c_str = ba.data();
    socket->write(c_str);
}

void MenuWindow::MyTimerSlot()
{
    receiveListOfUsersOnline = false;
    qWarning() << "ENTROU";
    timer->stop();
}

void MenuWindow::connect_network()
{
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    qDebug() << "Connecting...";
    socket->connectToHost("127.0.0.1", 1234);


    if(!socket->waitForConnected(1000))
        qDebug() << "Error: " << socket->errorString();
    qWarning() << "aqui2";

    // create a timer
    //timerId = startTimer(5000);
    timer->start(5000);
}

void MenuWindow::connected()
{
    qDebug() << "Connected";
    std::string s;
    if(this->login.length()/10 == 0)
        s = "00" + std::to_string(this->login.length());
    else if(this->login.length()/100 == 0)
        s = "0" + std::to_string(this->login.length());
    else
        s = std::to_string(this->login.length());
    s = "1" + s;
    char const *pchar = s.c_str();  //use char const* as target type
    socket->write(pchar);
    QByteArray ba = this->login.toLocal8Bit();
    char *c_str = ba.data();
    socket->write(c_str);
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
    qWarning() << "Reading...";
    QString message_received = socket->readAll();
    if(receiveListOfUsersOnline){
        receiveListOfUsers(message_received);
        return;
    }
    sendMessageToDialogs(message_received);
    //emit receiveMessage(message_received);
}

void MenuWindow::on_talkButton_clicked()
{
    if(ui->listWidget->selectedItems().size() > 0)
    {
        if(checkIfUserOnline(ui->listWidget->currentItem()->text()))
        {
            setNameMessageWindow(ui->listWidget->currentItem()->text());
            receiveListOfUsersOnline = false;
            indMessageWindow.setModal(true);
            indMessageWindow.exec();
            indMessageWindow.clearUiAndConversation();
            receiveListOfUsersOnline = true;
            timer->start(1000);
        }
    }
}

void MenuWindow::on_addButton_clicked()
{
    if(!ui->listWidget->currentItem()->text().isEmpty() && listOfUsers[userIndexFromString(ui->listWidget->currentItem()->text())].getOnline())
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
    socket->disconnectFromHost();
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

int MenuWindow::userIndexFromString(QString name)
{
    for(int i = 0; i < listOfUsers.length();i++)
    {
        if(listOfUsers[i].getName() == name)
            return i;
    }
    return -1;
}

void MenuWindow::receiveListOfUsers(QString messageReceived)
{
    QStringList pieces = messageReceived.split( "|" );
    QString ind_user;
    for(int i = 0; i < pieces.length(); i++)
    {
        ind_user = pieces.value( pieces.length() -1 -i);
        if(!ind_user.isEmpty())
        {
            ind_user.remove(0,5);
            QString name = ind_user.left(ind_user.indexOf("IP:"));
            QString ip = ind_user.right(ind_user.length() - ind_user.indexOf(":") -1).remove(QChar(')'), Qt::CaseInsensitive);
            ip = ip.remove(QChar('('), Qt::CaseInsensitive);
            ip = ip.remove(QChar('\''), Qt::CaseInsensitive);
            qDebug() << "name: " << name;
            qDebug() << "IP: " << ip.left(ip.indexOf(","));
            qDebug() << "Ports: " << ip.right(ip.length() - ip.indexOf(",")-2);
            if(QString::compare(name, this->login, Qt::CaseInsensitive) == 0)
                return;
            bool success = true;
            for(int i = 0; i < listOfUsers.length();i++)
            {
                if(listOfUsers[i].getName() == name)
                    success = false;
            }
            if(!success)
                continue;

            User *dumb = new User();
            dumb->setName(name);
            dumb->setIp(ip.left(ip.indexOf(",")));
            dumb->setPort(ip.right(ip.length() - ip.indexOf(",")-2).toUInt());
            dumb->setOnline(true);
            listOfUsers.append(*dumb);

            QListWidgetItem *item2 = new QListWidgetItem();
            item2->setTextColor("#4cff00");
            item2->setFont(*font);
            item2->setText(dumb->getName());
            if(!dumb->getOnline())
            {
                item2->setTextColor("#ff0004");
            }
            ui->listWidget->addItem(item2);
        }
    }
}

void MenuWindow::sendMessageToDialogs(QString messageReceived)
{
    QStringList pieces = messageReceived.split( "|" );
    QString ind_user;
    qWarning() << "Message Received: " << messageReceived;
    if(pieces.isEmpty())
        return;
    QString who_sent = pieces.value(0);
    qWarning() << "who sent:" << who_sent;
    QString payload_message = pieces.value(pieces.length()-1);
    qWarning() << "Payload: " << payload_message;
    QString users_to_group_message;

    if(pieces.length() == 3)
    {
        qWarning() << "IF";
        ind_user = pieces.value(1);
        if(indMessageWindow.isVisible())
        {
            qWarning() << "isVisible";
            if(indMessageWindow.name == ind_user)
            {
                emit sendMessage(payload_message);
            }else{
                return;
            }
        }else{
            qWarning() << "notVisible";
            indMessageWindow.open();
            emit setNameMessageWindow(ind_user);
            emit receiveMessage(payload_message);
        }
    }else{
        qWarning() << "ELSE";
        for(int i = 1; i < pieces.length() -1; i++)
        {
            if(pieces.value(pieces.length()-1-i) != this->login)
                users_to_group_message += pieces.value(pieces.length()-1-i) + "|";
            qWarning() << "users: " << users_to_group_message;
        }
        if(pieces.value(0) != this->login)
            users_to_group_message += pieces.value(0);
        if(groupMessageWindow.isVisible())
        {
            qWarning() << "isVisible";
            //sendListOfGroupUsersToServer = false;
             emit receiveGroupMessage(payload_message,who_sent);
        }else{
            qWarning() << "notVisible";
            groupMessageWindow.clearUiAndConversation();
            emit setNameGroupMessageWindow(users_to_group_message);
            emit receiveGroupMessage(payload_message,who_sent);
            groupMessageWindow.open();
            //sendListOfGroupUsersToServer = false;
        }
    }
}

void MenuWindow::on_groupButton_clicked()
{
    QString users_to_group_message;
    if(ui->listWidget_2->count() > 1)
    {
        groupMessageWindow.clearUiAndConversation();
        for(int i = 0; i < ui->listWidget_2->count() - 1; i++)
        {
            emit setNameGroupMessageWindow(ui->listWidget_2->item(i)->text() + "|");
            users_to_group_message = ui->listWidget_2->item(i)->text() + "|";
        }
        emit setNameGroupMessageWindow(ui->listWidget_2->item(ui->listWidget_2->count() - 1)->text());
        users_to_group_message += ui->listWidget_2->item(ui->listWidget_2->count() - 1)->text();
        sendGroupMessage(users_to_group_message, true);
        receiveListOfUsersOnline = false;
        groupMessageWindow.setModal(true);
        groupMessageWindow.exec();
        groupMessageWindow.clearUiAndConversation();
        receiveListOfUsersOnline = true;
        timer->start(1000);
    }
}

void MenuWindow::on_pushButton_clicked()
{
    socket->disconnectFromHost();
    qDebug() << "Connecting...";
    socket->connectToHost("127.0.0.1", 1234);

    if(!socket->waitForConnected(5000))
        qDebug() << "Error: " << socket->errorString();
    receiveListOfUsersOnline = true;
    timer->start(1000);
}

void MenuWindow::timerEvent(QTimerEvent *event)
{
    receiveListOfUsersOnline = false;
    qWarning() << "ENTROOOOO";
}
