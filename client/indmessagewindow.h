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
    QString name;

private:
    Ui::IndMessageWindow *ui;
    QString conversation;

public slots:
    void setNameMessageWindow(QString name);
    void receiveMessage(QString message);
    void teste();
private slots:
    void on_pushButton_clicked();

signals:
    void sendMessage(QString message);
};

#endif // INDMESSAGEWINDOW_H
