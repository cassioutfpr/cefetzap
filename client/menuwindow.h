#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>

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
    QString login;
    QTcpSocket *socket;

public slots:
    void newLogin(QString login);
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


};

#endif // MENUWINDOW_H
