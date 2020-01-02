#ifndef SIRKETEKRANI_H
#define SIRKETEKRANI_H

#include <QMainWindow>
#include <VeriTabaniIslemleri.h>
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
#include <QInputDialog>
#include <MainWindow.h>

namespace Ui {
class SirketEkrani;
}

class SirketEkrani : public QMainWindow
{
    Q_OBJECT

public:
    explicit SirketEkrani(QWidget *parent = 0);
    ~SirketEkrani();

private slots:
    void on_pushButton_clicked();

    void on_tableView_depolar_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tf_depoIsimAra_selectionChanged();

    void on_tf_depoIsimAra_textChanged(const QString &arg1);

    void on_tf_depoIdAra_textChanged(const QString &arg1);

    void on_tf_urunKodAra_textChanged(const QString &arg1);

    void on_tf_urunIsimAra_textChanged(const QString &arg1);

    void on_tf_urunBirimAra_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_btn_projeTanimla_clicked();

    void on_btn_yeniProje_clicked();

    void on_btn_malzemeEkle_clicked();

    void on_tf_malzemeAra_textChanged(const QString &arg1);

    void on_tableView_sirketProjeleri_clicked(const QModelIndex &index);

    void on_btn_sirketDepoGoruntule_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_btn_projeMalzemeSil_clicked();

    void on_tableView_sirketteOlmayanMalzeme_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_btn_cikis_clicked();

private:
    QDateTime dateTime=dateTime.currentDateTime();

    void sirketteOlmayanMalzemeTabloGuncelle(QString sorgu);

    void projeTabloGuncelle(QString sorgu);
    void seciliProjeMalzemeTablo(QString sorgu);
    void stokTabloGuncelle(QString sorgu);
    void projeIhtiyacTabloGuncelle(QString sorgu);
    Ui::SirketEkrani *ui;

    QString depoKodPublic="";

    void DepoTabloGuncelle(QString sorgu);

    QSqlQueryModel* model;
    void UrunTabloGuncelle(QString sorgu);
    VeriTabaniIslemleri* veriTabaniIslem;
};

#endif // SIRKETEKRANI_H
