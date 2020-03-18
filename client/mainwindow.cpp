#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(newLogin(QString)), &menu_window, SLOT(newLogin(QString)));
    //QPixmap pix("\images\utfpr.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit newLogin(ui->lineEdit->text());
    menu_window.setModal(true);
    menu_window.exec();
}
