#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QListWidgetItem>
#include "indmessagewindow.h"
#include "groupmessagewindow.h"
#include "user.h"
#include <QTimer>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    Ui::MenuWindow *ui;
    QFont *font;
    QString login;
    QTcpSocket *socket;
    IndMessageWindow indMessageWindow;
    GroupMessageWindow groupMessageWindow;
    virtual void closeEvent(QCloseEvent *action);
    User mySelf;
    QList<User> listOfUsers;
    QTimer *timer;
    int timerId;

    bool checkIfUserOnline(QString text);
    int userIndexFromString(QString name);
    bool receiveListOfUsersOnline;
    //bool sendListOfGroupUsersToServer;

    void receiveListOfUsers(QString messageReceived);

    void sendMessageToDialogs(QString messageReceived);
public slots:
    void newLogin(QString login);
    void sendMessage(QString message);
    void sendGroupMessage(QString message, bool sendListOfGroupUsersToServer);
    void MyTimerSlot();
private slots:
    void connect_network();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

    void on_talkButton_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_groupButton_clicked();

    void on_pushButton_clicked();

signals:
    //ind
    void setNameMessageWindow(QString name);
    void receiveMessage(QString message);
    //group
    void setNameGroupMessageWindow(QString listofUsers);
    void receiveGroupMessage(QString message, QString whoSaid);

    void teste();

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MENUWINDOW_H
