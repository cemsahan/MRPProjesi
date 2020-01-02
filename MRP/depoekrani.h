#ifndef DEPOEKRANI_H
#define DEPOEKRANI_H

#include <QMainWindow>
#include <QMainWindow>
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
#include <MainWindow.h>

namespace Ui {
class DepoEkrani;
}

class DepoEkrani : public QMainWindow
{
    Q_OBJECT


public:
    explicit DepoEkrani(QWidget *parent = 0);
    ~DepoEkrani();
    QString depoCalisanKod;
    void getCalisanDepoId(QString kod);


    void tabloGuncelle(QString sorgu);

     QString tabloSorgusu;
private slots:
    void on_tf_urunKodAra_textChanged(const QString &arg1);

  //  void on_tf_urunIsmiAra_textChanged(const QString &arg1);

    void on_tf_urunBrAra_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_btn_dosya_clicked();

    void on_btn_sil_clicked();

    void on_btn_guncelle_clicked();

    void on_tf_urunIsmiAra_cursorPositionChanged(int arg1, int arg2);

    void on_tf_urunIsmiAra_textChanged(const QString &arg1);

    void on_actionBildirim_Ekran_n_A_triggered();

    void on_pushButton_2_clicked();

public slots:
    void tabloGuncelle();




private:



    Ui::DepoEkrani *ui;

    UrunStruct* urunStruct;



    QFileDialog fileDialog;

    VeriTabaniIslemleri* veriTabaniIslem=new VeriTabaniIslemleri();


    QSqlQueryModel* model;

    void dosyaOku(QString path);

    QDateTime dateTime=dateTime.currentDateTime();

    Connect* conn;
    QString calisanDepoId;
    BildirimEkraniDepo* frm;

};

#endif // DEPOEKRANI_H
