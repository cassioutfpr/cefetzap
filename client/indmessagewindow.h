#ifndef INDMESSAGEWINDOW_H
#define INDMESSAGEWINDOW_H

#include <QDialog>

namespace Ui {
class IndMessageWindow;
}

class IndMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IndMessageWindow(QWidget *parent = nullptr);
    ~IndMessageWindow();
    void clearUiAndConversation();

private:
    Ui::IndMessageWindow *ui;
    QString name;
    QString conversation;

public slots:
    void setNameMessageWindow(QString name);
    void receiveMessage(QString message);
private slots:
    void on_pushButton_clicked();

signals:
    void sendMessage(QString message);
};

#endif // INDMESSAGEWINDOW_H
