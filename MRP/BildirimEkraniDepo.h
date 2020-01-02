#ifndef BILDIRIMEKRANIDEPO_H
#define BILDIRIMEKRANIDEPO_H

#include <QMainWindow>
#include <VeriTabaniIslemleri.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QWidget>
#include <QSqlQueryModel>
#include <QFile>
#include <QDebug>
#include <VeriTabaniIslemleri.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <UrunStruct.h>
#include <guncelleForm.h>
#include <DepoBilgi.h>
#include <connect.h>
#include <BildirimEkraniDepo.h>
namespace Ui {
class BildirimEkraniDepo;
}

class BildirimEkraniDepo : public QMainWindow
{
    Q_OBJECT

public:
    explicit BildirimEkraniDepo(QWidget *parent = 0);
    ~BildirimEkraniDepo();
    void bildirimTabloGuncelle(QString sorgu);
    void depoIdAl(QString depoId);
    QString calisanDepoId;

private slots:
    void on_tableView_bildirimDepo_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BildirimEkraniDepo *ui;
    VeriTabaniIslemleri* veriTabaniIslem;
    QSqlQueryModel* model;

};

#endif // BILDIRIMEKRANIDEPO_H




