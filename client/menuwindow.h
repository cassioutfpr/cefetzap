#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QListWidgetItem>
#include "indmessagewindow.h"
#include "user.h"

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
    IndMessageWindow ind_message_window;
    void closeEvent(QCloseEvent *action);
    User mySelf;
    QList<User> listOfUsers;

    bool checkIfUserOnline(QString text);
public slots:
    void newLogin(QString login);
    void addNewUserToListWidget(User newUser);
    void sendMessage(char* message);
private slots:
    void connect_network();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

    void on_talkButton_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

signals:
    void setNameMessageWindow(QString name);
    void receiveMessage(QString message);


};

#endif // MENUWINDOW_H
