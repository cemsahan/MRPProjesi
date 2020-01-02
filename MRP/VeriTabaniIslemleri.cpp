#include "VeriTabaniIslemleri.h"

#include <MainWindow.h>




VeriTabaniIslemleri::VeriTabaniIslemleri()
{


}

void VeriTabaniIslemleri::depostokEkle(QString stokKodu, QString stokIsmi, int miktar, QString br, QString fiyat, QString trh,QString depoKod,QString rafId)
{

    QSqlQuery query2;
    query2.exec("SELECT * FROM depostok WHERE StokId=?");
    query2.addBindValue(stokKodu);

    if(!query2.exec()) qDebug()<<"sorgu hatalı...";
    if(query2.next())
    {
      qDebug()<<"Kayıt var...";
    }
    else
    {
            QSqlQuery query;
            query.exec("insert into stok (StokId,StokIsmi,Birim,DepoId) values (?,?,?,?)");

            query.addBindValue(stokKodu);
            query.addBindValue(stokIsmi);
            query.addBindValue(br);
            query.addBindValue(depoKod);

            if(!query.exec()) qDebug()<<"Stokda var..."+stokKodu;




            QSqlQuery query1;

            query1.exec("INSERT INTO depostok (StokId,AdetFiyat,guncellemeTarihi,GirisMiktari,DepoId,RafId) VALUES (?,?,?,?,?,?)");
            query1.addBindValue(stokKodu);
            query1.addBindValue(fiyat);
            query1.addBindValue(trh);
            query1.addBindValue(miktar);
            query1.addBindValue(depoKod);
            query1.addBindValue(rafId);
            if(!query1.exec()) qDebug()<<"(depostok ekle)sorgu1 hatalı...";

        }



}

QSqlQuery VeriTabaniIslemleri::donenSorgu(QString cameQuery)
{

    QSqlQuery query;
	query.exec(cameQuery);
    return sorgu;

}

void VeriTabaniIslemleri::depoStokGuncelle(QString stokKodu, QString stokIsmi, QString br, QString fiyat, QString rafKod,QString depoId)
{

qDebug()<<depoId;

    QSqlQuery query;
    QSqlQuery query1;
    QString dateTimeString=dateTime.toString("dd/MM/yyyy");

    query.exec("UPDATE stok SET StokIsmi=?,Birim=? WHERE StokId=? and DepoId=?");
    query.addBindValue(stokIsmi);
    query.addBindValue(br);
    query.addBindValue(stokKodu);
    query.addBindValue(depoId);

  if(!query.exec()) {
      qDebug()<<"Stok sorgusu hatalı...";
  }
  else {
      qDebug()<<"depoStokGeldi";
      query1.exec("UPDATE depostok SET AdetFiyat=?,guncellemeTarihi=?,RafId=? WHERE StokId=? and DepoId=?");

      query1.addBindValue(fiyat);
      query1.addBindValue(dateTimeString);
      query1.addBindValue(rafKod);
      query1.addBindValue(stokKodu);
      query1.addBindValue(depoId);
        qDebug()<<"başarılı";
       if(!query1.exec()) qDebug()<<"depoStokGuncelle sorgusu hatalı";


  }








}

void VeriTabaniIslemleri::projeEkle(QString projeKodu, QString projeIsmi, QString miktar, QString birim, QString adetFiyat)
{

    QSqlQuery query;
    query.exec("SELECT * FROM proje WHERE ProjeId=?");
    query.addBindValue(projeKodu);

    if(!query.exec()) qDebug()<<"(projeKontrol)sorgu hatalı...";
    if(query.next())
    {

        //sirketEkrani=new SirketEkrani();


      //  QMessageBox::information(sirketEkrani,"UYARI","PROJE DAHA ÖNCE EKLENMİŞ...");

        QMessageBox msgBox;
        msgBox.setText("PROJE DAHA ÖNCE EKLENMİŞ....");
        msgBox.exec();


     qDebug()<<"Kayıt var...";

    }
    else
    {
        QSqlQuery query1;

        query1.exec("INSERT INTO proje (ProjeId,ProjeAdi,Miktar,Birim,AdetFiyat) VALUES (?,?,?,?,?)");
        query1.addBindValue(projeKodu);
        query1.addBindValue(projeIsmi);
        query1.addBindValue(miktar);
        query1.addBindValue(birim);
        query1.addBindValue(adetFiyat);
        QMessageBox msgBox1;
        msgBox1.setText("PROJE EKLENDİ....");
        msgBox1.exec();
        if(!query1.exec()) qDebug()<<"(proje ekle)sorgu1 hatalı...";


    }



}

void VeriTabaniIslemleri::projeIhtiyacEkle(QString projeId, QString stokId,int miktar)
{
    QSqlQuery query;
    for(int i=1;i<miktar;i++)
    {

    query.exec("INSERT INTO projeihtiyaclari (projeId,StokId) VALUES (?,?)");
    query.addBindValue(projeId);
    query.addBindValue(stokId);
    if(!query.exec()) qDebug()<<"(proje ihticayac ekle) sorgu hatalı...";

    }
    if(query.exec())
    {
        QMessageBox msgBox1;
        msgBox1.setText(stokId+" Kodlu malzeme projeye eklendi...");
        msgBox1.exec();

    }
}

void VeriTabaniIslemleri::projeIhtiyacSil(QString projeId, QString malzemeKod)
{
    QSqlQuery query;
    query.exec("DELETE FROM projeihtiyaclari WHERE projeId=? and StokId=?");
    query.addBindValue(projeId);
    query.addBindValue(malzemeKod);
    if(!query.exec()) {

        QMessageBox msgBox1;
        msgBox1.setText("(Proje İhtiyac sil ) sorgu hatalı...");
        msgBox1.exec();



    }
        else
    {
        QMessageBox msgBox1;
        msgBox1.setText("Proje Malzemesi Silindi...");
        msgBox1.exec();
    }
}

void VeriTabaniIslemleri::bildirimEkle(QString StokId, QString DepoId, QString Tarih, QString mesaj,int miktar)
{

    QSqlQuery query;
    query.exec("INSERT INTO bildirim (StokId,DepoId,Tarih,Mesaj,Miktar) VALUES (?,?,?,?,?) ");
    query.addBindValue(StokId);
    query.addBindValue(DepoId);
    query.addBindValue(Tarih);
    query.addBindValue(mesaj);
    query.addBindValue(miktar);
    if(!query.exec()) {

        QMessageBox msgBox1;
        msgBox1.setText("(Bildirim Ekle ) sorgu hatalı...");
        msgBox1.exec();



    }
        else
    {
        QMessageBox msgBox1;
        msgBox1.setText(StokId+" Kodlu Malzeme Sipariş Onayına Gönderildi...");
        msgBox1.exec();
    }




}

void VeriTabaniIslemleri::depostokSil(QString urunKod, QString depoKod)
{
    QSqlQuery query;
    query.exec("DELETE FROM depostok WHERE StokId=? and DepoId=?");

    query.addBindValue(urunKod);
    query.addBindValue(depoKod);

    if(!query.exec()) qDebug()<<"(depostok Sil)sorgu hatalı...";

}




void VeriTabaniIslemleri::depoSirketEkle(int miktar, QString StokId)
{
    for(int i=0;i<miktar;i++)
    {
        QSqlQuery query;
        query.exec("INSERT INTO deposirket (StokId) VALUES (?)");
        query.addBindValue(StokId);
        if(!query.exec()) qDebug()<<"deposirket sorgu hatalı";

    }
}

void VeriTabaniIslemleri::sirketDepoalisverisEkle(QString StokId,QString DepoId,QString Miktar,QString Fiyat,QString Tarih)
{
    QSqlQuery query;
    query.exec("INSERT INTO sirketdepodepo (StokId,DepoId,Miktar,Fiyat,AlisverisTarihi) VALUES (?,?,?,?,?) ");
    query.addBindValue(StokId);
    query.addBindValue(DepoId);
    query.addBindValue(Miktar);
    query.addBindValue(Fiyat);
    query.addBindValue(Tarih);

    if(!query.exec()) {
        QMessageBox msgBox1;
        msgBox1.setText("sirketdepodepo Sorgu hatası....");
        msgBox1.exec();

    }

}

void VeriTabaniIslemleri::bildirimGuncelle(QString bildirimId,QString depoId,QString StokId,int miktar)
{
    QSqlQuery query;
    query.exec("UPDATE bildirim SET Onay=true WHERE BildirimId=?");
    query.addBindValue(bildirimId);

    if(!query.exec()) {
        QMessageBox msgBox1;
        msgBox1.setText("Bildirim Güncelleme Sorgusu Hatalı....");
        msgBox1.exec();

    }
    else{


        QSqlQuery query1;
        query1.exec("UPDATE depostok SET CikisMikrari=CikisMikrari+? WHERE DepoId=? and StokId=?");

        query1.addBindValue(miktar);

        query1.addBindValue(depoId);
        query1.addBindValue(StokId);
       if(!query1.exec()) qDebug()<<"depostok guncellenemedi..";

       else
        {
            QMessageBox msgBox1;
            msgBox1.setText("Sipariş Onaylandi...");
            msgBox1.exec();
         }
        }
       }

void VeriTabaniIslemleri::projeGuncelle(QString projeKodu, QString projeIsmi, QString miktar, QString birim, QString adetFiyat)
{

    QSqlQuery query;
    query.exec("UPDATE proje SET ProjeAdi=?,Miktar=?,Birim=?,AdetFiyat=? WHERE ProjeId=?");
    query.addBindValue(projeIsmi);
    query.addBindValue(miktar);
    query.addBindValue(birim);
    query.addBindValue(adetFiyat);
    query.addBindValue(projeKodu);
    if(!query.exec()) {
        QMessageBox msgBox1;
        msgBox1.setText("Güncelleme Sorgusu Hatalı....");
        msgBox1.exec();

    }
    else{
        QMessageBox msgBox1;
        msgBox1.setText("Proje Güncellendi....");
        msgBox1.exec();


    }

}

void VeriTabaniIslemleri::projeSil(QString projeKod)
{

    QSqlQuery query;
    query.exec("DELETE FROM proje WHERE projeId=?");
    query.addBindValue(projeKod);
    if(!query.exec()){
        QMessageBox msgBox1;
        msgBox1.setText("PROJE SİLME SORGUSU HATALI....");
        msgBox1.exec();


    }    else
    {
        QMessageBox msgBox1;
        msgBox1.setText(projeKod+" KODLU PROJE SİLİNDİ....");
        msgBox1.exec();
    }

}



