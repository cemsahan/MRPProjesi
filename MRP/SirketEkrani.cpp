#include "SirketEkrani.h"
#include "ui_SirketEkrani.h"
#include <QtGui>
#include <QLabel>

SirketEkrani::SirketEkrani(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SirketEkrani)
{

    ui->setupUi(this);

    DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo");

    projeIhtiyacTabloGuncelle("SELECT stok.stokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId=''");

    stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok");

    projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");

}




void SirketEkrani::UrunTabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_urun->clearFocus();

   // QString sorgu="SELECT * FROM depostok";

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_urun->setModel(model);

    ui->tableView_urun->resizeColumnsToContents();




}



SirketEkrani::~SirketEkrani()
{
    delete ui;
}

void SirketEkrani::on_pushButton_clicked()
{


    UrunTabloGuncelle("SELECT depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' FROM depostok ,stok,depo WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId");

    depoKodPublic="";
    ui->pushButton_2->setEnabled(true);

}

void SirketEkrani::DepoTabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_depolar->clearFocus();

   // QString sorgu="SELECT * FROM depostok";

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_depolar->setModel(model);

    ui->tableView_depolar->resizeColumnsToContents();




}


void SirketEkrani::on_tableView_depolar_clicked(const QModelIndex &index)
{

     QModelIndex index1=ui->tableView_depolar->selectionModel()->currentIndex();


     QVariant depoKod=index1.sibling(index1.row(),0).data();
     QString depoKodString=depoKod.toString();

     depoKodPublic=depoKodString;

     UrunTabloGuncelle("SELECT depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' FROM depostok ,stok,depo WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId and depostok.DepoId="+depoKodPublic);









}



void SirketEkrani::on_tf_depoIsimAra_textChanged(const QString &arg1)
{
    QString depoIsmi=ui->tf_depoIsimAra->text();

    DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo WHERE depoIsmi LIKE '%"+depoIsmi+"%'");

}

void SirketEkrani::on_tf_depoIdAra_textChanged(const QString &arg1)
{
    QString depoKod=ui->tf_depoIdAra->text();
    DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo WHERE DepoId LIKE '%"+depoKod+"%'");
}

void SirketEkrani::on_tf_urunKodAra_textChanged(const QString &arg1)
{
    QString urunKod=ui->tf_urunKodAra->text();







    if(depoKodPublic=="") {
        UrunTabloGuncelle("SELECT "
        "depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' "
        "FROM depostok ,stok,depo "
        "WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId  and depostok.StokId LIKE '%"+urunKod+"%'");
ui->pushButton_2->setEnabled(true);
    }

   else
    {

    UrunTabloGuncelle("SELECT "
    "depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' "
    "FROM depostok ,stok,depo "
    "WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId and depostok.DepoId="+depoKodPublic+" and depostok.StokId LIKE '%"+urunKod+"%'");
    ui->pushButton_2->setEnabled(true);
    }
}









void SirketEkrani::on_tf_urunIsimAra_textChanged(const QString &arg1)
{
    QString urunIsim=ui->tf_urunIsimAra->text();

    if(depoKodPublic=="") {

        UrunTabloGuncelle("SELECT depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS ' BAKİYE ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' FROM stok,depostok,depo WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId and stok.StokIsmi LIKE '%"+urunIsim+"%'");
ui->pushButton_2->setEnabled(true);
    }

   else
    {

    UrunTabloGuncelle("SELECT "
    "depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' "
    "FROM depostok ,stok,depo "
    "WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId and depostok.DepoId="+depoKodPublic+" and stok.StokIsmi LIKE '%"+urunIsim+"%'");
    qDebug()<<depoKodPublic;
    }
}



void SirketEkrani::on_tf_urunBirimAra_textChanged(const QString &arg1)
{
    QString urunBirim=ui->tf_urunBirimAra->text();
ui->pushButton_2->setEnabled(true);






    if(depoKodPublic=="") {
        UrunTabloGuncelle("SELECT "
        "depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' "
        "FROM depostok ,stok,depo "
        "WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId  and stok.Birim LIKE '%"+urunBirim+"%'");
ui->pushButton_2->setEnabled(true);
    }

   else
    {

    UrunTabloGuncelle("SELECT "
    "depo.depoIsmi AS 'DEPO ADI',depo.DepoId AS 'DEPO KODU',stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' "
    "FROM depostok ,stok,depo "
    "WHERE depostok.StokId=stok.StokId and depostok.DepoId=depo.DepoId and depostok.DepoId="+depoKodPublic+" and stok.Birim LIKE '%"+urunBirim+"%'");
   ui->pushButton_2->setEnabled(true);
    }



}

void SirketEkrani::stokTabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_malzemeListesi->clearFocus();

   // QString sorgu="SELECT * FROM depostok";

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_malzemeListesi->setModel(model);

    ui->tableView_malzemeListesi->resizeColumnsToContents();




}

void SirketEkrani::projeIhtiyacTabloGuncelle(QString sorgu)
{

    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_projeMalzemeListesi->clearFocus();

   // QString sorgu="SELECT * FROM depostok";

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);



    model->setQuery(Sqlquery);


    ui->tableView_projeMalzemeListesi->setModel(model);

    ui->tableView_projeMalzemeListesi->resizeColumnsToContents();




}

void SirketEkrani::on_btn_projeTanimla_clicked()
{
    if(ui->btn_projeTanimla->text()=="Güncelle")
    {




        if(ui->tf_yeniProjeIsim->text()==""|| ui->tf_yeniProjeId->text()==""||ui->tf_yeniProjeBirim->text()==""|| ui->tf_yeniProjeFiyat->text()=="")
        {
            QMessageBox::information(this,"UYARI","BOŞLUKLARI DOLDURUNUZ");

        }
        else
        {

            QString projeIsmi=ui->tf_yeniProjeIsim->text();
            QString projeId=ui->tf_yeniProjeId->text();
            QString projeMiktar=ui->spinBox->text();
            QString projeBirim=ui->tf_yeniProjeBirim->text();
            QString projeAdetFiyat=ui->tf_yeniProjeFiyat->text();

            int projeMiktarInt=projeMiktar.toInt(NULL,10);


            veriTabaniIslem->projeGuncelle(projeId,projeIsmi,projeMiktar,projeBirim,projeAdetFiyat);



            QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktar+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeId+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

            ui->tf_yeniProjeId->setEnabled(false);

            ui->btn_projeTanimla->setEnabled(false);

            ui->btn_malzemeEkle->setEnabled(true);

            projeIhtiyacTabloGuncelle(sorgu);

            DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo");



            stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok");

            projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");



    }
    }

    else
    {
    if(ui->tf_yeniProjeIsim->text()==""|| ui->tf_yeniProjeId->text()==""||ui->tf_yeniProjeBirim->text()==""|| ui->tf_yeniProjeFiyat->text()=="")
    {
        QMessageBox::information(this,"UYARI","BOŞLUKLARI DOLDURUNUZ");

    }
    else
    {


        QString projeIsmi=ui->tf_yeniProjeIsim->text();
        QString projeId=ui->tf_yeniProjeId->text();
        QString projeMiktar=ui->spinBox->text();
        QString projeBirim=ui->tf_yeniProjeBirim->text();
        QString projeAdetFiyat=ui->tf_yeniProjeFiyat->text();

        int projeMiktarInt=projeMiktar.toInt(NULL,10);

    veriTabaniIslem->projeEkle(projeId,projeIsmi,projeMiktar,projeBirim,projeAdetFiyat);

    QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktar+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeId+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

    ui->tf_yeniProjeId->setEnabled(false);

    ui->btn_projeTanimla->setEnabled(false);

    ui->btn_malzemeEkle->setEnabled(true);

    projeIhtiyacTabloGuncelle(sorgu);
    DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo");


    stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok");

    projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");




    }
}

}






void SirketEkrani::on_btn_yeniProje_clicked()
{
    ui->btn_projeTanimla->setText("Proje Ekle");
    ui->btn_projeTanimla->setEnabled(true);
    ui->tf_yeniProjeId->setEnabled(true);
    ui->tf_yeniProjeId->setText("");
    ui->tf_yeniProjeIsim->setText("");
    ui->tf_yeniProjeBirim->setText("");
    ui->tf_yeniProjeFiyat->setText("");
    ui->spinBox->setValue(0);

    ui->btn_malzemeEkle->setEnabled(false);

}

void SirketEkrani::on_btn_malzemeEkle_clicked()
{

    QString projeId=ui->tf_yeniProjeId->text();

    QModelIndex index1=ui->tableView_malzemeListesi->selectionModel()->currentIndex();
    QString projeMiktari=ui->spinBox->text();
    int projeMiktariInt=projeMiktari.toInt(NULL,10);
if(index1.row()<0)
{
QMessageBox::information(this,"UYARI","Lütfen eklenecek malzemeyi seçiniz...");

}

    else
{
    bool isOkPressed=false;
    QVariant malzemeKod=index1.sibling(index1.row(),0).data();


    QString malzemekodString=malzemeKod.toString();

    int miktar=QInputDialog::getInt(NULL,"Miktar",malzemekodString+" Miktarı:",1,0,50,1,&isOkPressed,windowFlags());

    if(isOkPressed)
    {

    veriTabaniIslem->projeIhtiyacEkle(projeId,malzemekodString,miktar);


    QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktari+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeId+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";


    projeIhtiyacTabloGuncelle(sorgu);

    QString sorgu1="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktari+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeId+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

    seciliProjeMalzemeTablo(sorgu1);
    sirketteOlmayanMalzemeTabloGuncelle("SELECT pi.StokId AS 'MALZEME KOD',s.StokIsmi AS 'MALZEME İSMİ',COUNT(*)* "+projeMiktari+" AS 'MİKTAR' FROM projeihtiyaclari pi LEFT JOIN deposirket ds ON pi.StokId=ds.StokId INNER JOIN stok s ON s.StokId=pi.StokId WHERE ds.StokId IS NULL and pi.projeId='"+projeId+"' GROUP BY pi.ProjeId,pi.StokId");
}
    else QMessageBox::information(NULL,"Bilgi","İşlem İptal Edildi");

}
}
void SirketEkrani::on_tf_malzemeAra_textChanged(const QString &arg1)
{

    QString malzemeIsim=ui->tf_malzemeAra->text();

    stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok WHERE StokIsmi LIKE '%"+malzemeIsim+"%'");

}

void SirketEkrani::projeTabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_sirketProjeleri->clearFocus();

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_sirketProjeleri->setModel(model);

    ui->tableView_sirketProjeleri->resizeColumnsToContents();
}

void SirketEkrani::seciliProjeMalzemeTablo(QString sorgu)
{

    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_seciliProjeMalzeme->clearFocus();

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_seciliProjeMalzeme->setModel(model);

    ui->tableView_seciliProjeMalzeme->resizeColumnsToContents();

}


void SirketEkrani::on_tableView_sirketProjeleri_clicked(const QModelIndex &index)
{

    QModelIndex index1=ui->tableView_sirketProjeleri->selectionModel()->currentIndex();

    QVariant projeMiktar=index1.sibling(index1.row(),2).data();
    QVariant projeKod=index1.sibling(index1.row(),0).data();
    QString projeKodString=projeKod.toString();
    QString projeMiktarString=projeMiktar.toString();





    QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktarString+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeKodString+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

    seciliProjeMalzemeTablo(sorgu);
    sirketteOlmayanMalzemeTabloGuncelle("SELECT pi.StokId AS 'MALZEME KOD',s.StokIsmi AS 'MALZEME İSMİ',COUNT(*) * "+projeMiktarString+" AS 'MİKTAR' FROM projeihtiyaclari pi LEFT JOIN deposirket ds ON pi.StokId=ds.StokId INNER JOIN stok s ON s.StokId=pi.StokId WHERE ds.StokId IS NULL and pi.projeId='"+projeKodString+"' GROUP BY pi.ProjeId,pi.StokId");
}





void SirketEkrani::on_btn_sirketDepoGoruntule_clicked()
{
    UrunTabloGuncelle("SELECT deposirket.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',COUNT(*) AS 'MİKTAR',stok.Birim AS 'BİRİM' FROM deposirket,stok WHERE deposirket.StokId=stok.StokId GROUP BY deposirket.StokId");
    ui->pushButton_2->setEnabled(false);
}

void SirketEkrani::sirketteOlmayanMalzemeTabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_sirketteOlmayanMalzeme->clearFocus();


    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_sirketteOlmayanMalzeme->setModel(model);

    ui->tableView_sirketteOlmayanMalzeme->resizeColumnsToContents();
}



void SirketEkrani::on_pushButton_5_clicked()
{


    QModelIndex index1=ui->tableView_sirketProjeleri->selectionModel()->currentIndex();
    QVariant projeKod=index1.sibling(index1.row(),0).data();
    QString projeKodString=projeKod.toString();
    QVariant projeMiktar=index1.sibling(index1.row(),2).data();
    QString projeMiktarString=projeMiktar.toString();

    if(index1.row()<0)
    {
        QMessageBox::information(this,"UYARI","Lütfen Silinecek Projeyi Seçiniz...");

    }
    else
    {


    QMessageBox msgBox;
    msgBox.setWindowTitle("UYARI");
    msgBox.setText(projeKodString+" Kodlu projeyi silmek üzeresiniz...");
    msgBox.addButton(QMessageBox::Yes)->setText("SİL");
    msgBox.addButton(QMessageBox::No)->setText("SİLME");
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){


        veriTabaniIslem->projeSil(projeKodString);
        projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");


        DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo");


        stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok");

        projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");

        QString sorgu1="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktarString+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeKodString+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

        projeIhtiyacTabloGuncelle(sorgu1);

        QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktarString+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeKodString+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

        seciliProjeMalzemeTablo(sorgu);
        sirketteOlmayanMalzemeTabloGuncelle("SELECT pi.StokId AS 'MALZEME KOD',s.StokIsmi AS 'MALZEME İSMİ',COUNT(*) * "+projeMiktarString+" AS 'MİKTAR' FROM projeihtiyaclari pi LEFT JOIN deposirket ds ON pi.StokId=ds.StokId INNER JOIN stok s ON s.StokId=pi.StokId WHERE ds.StokId IS NULL and pi.projeId='"+projeKodString+"' GROUP BY pi.ProjeId,pi.StokId");


    }

}


}


void SirketEkrani::on_pushButton_6_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_5);

    ui->tf_yeniProjeId->setEnabled(false);


    QModelIndex index1=ui->tableView_sirketProjeleri->selectionModel()->currentIndex();
    QVariant projeKod=index1.sibling(index1.row(),0).data();
    QVariant projeIsmi=index1.sibling(index1.row(),1).data();
    QVariant projeMiktar=index1.sibling(index1.row(),2).data();
    QVariant projeBirim=index1.sibling(index1.row(),3).data();
    QVariant projeFiyat=index1.sibling(index1.row(),4).data();



    QString projeKodString=projeKod.toString();
    QString projeIsmiString=projeIsmi.toString();
    QString projeMiktarString=projeMiktar.toString();
    QString projeBirimString=projeBirim.toString();
    QString projeFiyatString=projeFiyat.toString();

    ui->tf_yeniProjeId->setText(projeKodString);
    ui->tf_yeniProjeIsim->setText(projeIsmiString);
    ui->tf_yeniProjeBirim->setText(projeBirimString);
    ui->tf_yeniProjeFiyat->setText(projeFiyatString);
    ui->spinBox->setValue(projeMiktarString.toInt());


    ui->btn_projeTanimla->setText("Güncelle");

    DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo");


    stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok");

    projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");

    QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktarString+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeKodString+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

    projeIhtiyacTabloGuncelle(sorgu);

    ui->btn_malzemeEkle->setEnabled(true);




}




void SirketEkrani::on_btn_projeMalzemeSil_clicked()
{
    QModelIndex index1=ui->tableView_projeMalzemeListesi->selectionModel()->currentIndex();

    QString projeMiktarString=ui->spinBox->text();

    if(index1.row()<0) {

        QMessageBox::information(this,tr("UYARI"),"LÜTFEN SİLİNECEK ÜRÜNÜ SEÇİNİZ...") ;

    }
    else{

        QVariant malzemeKod=index1.sibling(index1.row(),0).data();
        QString malzemeKodString=malzemeKod.toString();
        QString projeKod=ui->tf_yeniProjeId->text();




        QMessageBox msgBox;
        msgBox.setWindowTitle("UYARI");
        msgBox.setText(malzemeKodString+" Kodlu ürününüzü silmek üzeresiniz...");
       // msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::Yes)->setText("SİL");
        msgBox.addButton(QMessageBox::No)->setText("SİLME");
        msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){
        veriTabaniIslem->projeIhtiyacSil(projeKod,malzemeKodString);



        DepoTabloGuncelle("SELECT DepoId AS 'DEPO KODU',DepoIsmi AS 'DEPO ADI' FROM depo");


        stokTabloGuncelle("SELECT stok.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME İSMİ',stok.Birim AS 'BİRİM' FROM stok");

        projeTabloGuncelle("SELECT ProjeId AS 'PROJE KODU',ProjeAdi AS 'PROJE ADI',Miktar AS 'MİKTAR',Birim AS 'BİRİM',AdetFiyat AS 'FİYAT' FROM proje");

        QString sorgu1="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktarString+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeKod+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

        projeIhtiyacTabloGuncelle(sorgu1);



        QString sorgu="SELECT  projeihtiyaclari.StokId AS 'MALZEME KODU',stok.StokIsmi AS 'MALZEME ADI',stok.Birim AS 'BİRİM',COUNT(*) * "+projeMiktarString+" AS 'Miktar' FROM projeihtiyaclari,stok WHERE projeihtiyaclari.StokId=stok.StokId and projeihtiyaclari.projeId='"+projeKod+"' GROUP BY projeihtiyaclari.projeId,projeihtiyaclari.StokId";

        seciliProjeMalzemeTablo(sorgu);
        sirketteOlmayanMalzemeTabloGuncelle("SELECT pi.StokId AS 'MALZEME KOD',s.StokIsmi AS 'MALZEME İSMİ',COUNT(*) * "+projeMiktarString+" AS 'MİKTAR' FROM projeihtiyaclari pi LEFT JOIN deposirket ds ON pi.StokId=ds.StokId INNER JOIN stok s ON s.StokId=pi.StokId WHERE ds.StokId IS NULL and pi.projeId='"+projeKod+"' GROUP BY pi.ProjeId,pi.StokId");


    }
}
}

void SirketEkrani::on_tableView_sirketteOlmayanMalzeme_doubleClicked(const QModelIndex &index)
{

    QVariant malzemeKod=index.sibling(index.row(),0).data();
    QString malzemeKodString=malzemeKod.toString();

    QVariant malzemeAdi=index.sibling(index.row(),1).data();
    QString malzemeAdiString=malzemeAdi.toString();

    ui->tf_urunKodAra->setText(malzemeKodString);
    ui->tf_urunIsimAra->setText(malzemeAdiString);

    ui->tabWidget->setCurrentWidget(ui->tab);






}



void SirketEkrani::on_pushButton_2_clicked()
{


    QModelIndex index=ui->tableView_urun->selectionModel()->currentIndex();

    if(index.row()<0)
    {
        QMessageBox::information(this,"UYARI","Lütfen sipariş verilecek ürünü seçiniz...");
    }
    else
    {
        bool isOkPressed1=false;
        QString mesaj="";

        QVariant bakiye=index.sibling(index.row(),5).data();
        QString bakiyeString=bakiye.toString();

        int miktar=QInputDialog::getInt(NULL,"Miktar Kutusu","Sipariş Miktarı:",1,0,bakiyeString.toInt(NULL,10),1,&isOkPressed1,windowFlags());
        bool isOkPressed = false;

        if(isOkPressed1)
        {
         mesaj=QInputDialog::getMultiLineText(NULL,"Mesaj Kutusu",tr("Depoya mesajınızı(varsa) yazı alanına yazınız..."),"",&isOkPressed);


        if(isOkPressed)
        {
        QString dateTimeString=dateTime.toString("dd/MM/yyyy");
        QVariant depoKod=index.sibling(index.row(),1).data();
        QVariant urunKod=index.sibling(index.row(),2).data();
        QString depoKodString=depoKod.toString();
        QString urunKodString=urunKod.toString();
        veriTabaniIslem->bildirimEkle(urunKodString,depoKodString,dateTimeString,mesaj,miktar);

        }
        else QMessageBox::information(NULL,"Bilgi","İşlem İptal Edildi");


    }
        else QMessageBox::information(NULL,"Bilgi","İşlem İptal Edildi");

}
}

void SirketEkrani::on_btn_cikis_clicked()
{
    MainWindow* girisEkrani=new MainWindow();
    girisEkrani->show();
    this->close();
}
