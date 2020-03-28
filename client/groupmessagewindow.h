#ifndef GROUPMESSAGEWINDOW_H
#define GROUPMESSAGEWINDOW_H

#include <QDialog>

namespace Ui {
class GroupMessageWindow;
}

class GroupMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GroupMessageWindow(QWidget *parent = nullptr);
    ~GroupMessageWindow();
    void clearUiAndConversation();

public slots:
    void setNameMessageWindow(QString name);
    void receiveMessage(QString message);
private slots:
    void on_pushButton_clicked();
private:
    Ui::GroupMessageWindow *ui;
    QString name;
    QString conversation;
signals:
    void sendMessage(QString message);
};

#endif // GROUPMESSAGEWINDOW_H
