#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <connect.h>
#include <QMessageBox>
#include <connect.h>
#include <depoekrani.h>
#include <ui_MainWindow.h>
#include <Qt>
#include <SirketEkrani.h>
#include <BildirimEkraniDepo.h>
//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mainWindow *ui;
    Connect* con;




};

#endif // MAINWINDOW_H
