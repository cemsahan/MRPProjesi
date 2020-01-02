#ifndef ANAEKRAN_H
#define ANAEKRAN_H

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
namespace Ui {
class AnaEkran;
}

class AnaEkran : public QWidget
{
    Q_OBJECT

public:
    explicit AnaEkran(QWidget *parent = 0);
    ~AnaEkran();



private slots:
    void on_tf_urunKodAra_textChanged(const QString &arg1);

    void on_tf_urunIsmiAra_textChanged(const QString &arg1);

    void on_tf_urunBrAra_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_btn_dosya_clicked();

    void on_btn_sil_clicked();

    void on_btn_guncelle_clicked();



public slots:
    void tabloGuncelle();


private:


    UrunStruct* urunStruct;

    QString tabloSorgusu="SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' FROM depostok ,stok WHERE depostok.StokId=stok.StokId";

    QFileDialog fileDialog;

VeriTabaniIslemleri* veriTabaniIslem=new VeriTabaniIslemleri();

    Ui::AnaEkran *ui;

    QSqlQueryModel* model;

    void dosyaOku(QString path);
    void tabloGuncelle(QString sorgu);
    QDateTime dateTime=dateTime.currentDateTime();

};

#endif // ANAEKRAN_H
