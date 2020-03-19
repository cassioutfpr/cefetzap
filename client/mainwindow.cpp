#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(newLogin(QString)), &menu_window, SLOT(newLogin(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        emit newLogin(ui->lineEdit->text());
        menu_window.setModal(true);
        menu_window.exec();
    }
}
