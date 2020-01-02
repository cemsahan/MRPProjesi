#ifndef VERITABANIISLEMLERI_H
#define VERITABANIISLEMLERI_H
#include <QString>
#include<connect.h>
#include <QDebug>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <iostream>
#include <sql.h>
#include <QDateTime>
#include <QMessageBox>
//#include <SirketEkrani.h>



class VeriTabaniIslemleri:public Connect
{

public:

    void depoSirketEkle(int miktar,QString StokId);

    void sirketDepoalisverisEkle(QString StokId,QString DepoId,QString Miktar,QString Fiyat,QString Tarih);

    void bildirimGuncelle(QString bildirimId,QString depoId,QString StokId,int miktar);

    void projeGuncelle(QString projeKodu,QString projeIsmi,QString miktar,QString birim,QString adetFiyat);

    void projeSil(QString projeKod);

    VeriTabaniIslemleri();

    void depostokSil(QString urunKod,QString depoKod);

    void depostokEkle(QString stokKodu,QString stokIsmi,int miktar,QString br,QString fiyat,QString trh,QString depoKod,QString rafId);

    QSqlQuery donenSorgu(QString sorgu);

    void depoStokGuncelle(QString stokKodu,QString stokIsmi,QString br,QString fiyat,QString rafKod,QString depoId);

    void projeEkle(QString projeKodu,QString projeIsmi,QString miktar,QString birim,QString adetFiyat);

    void projeIhtiyacEkle(QString projeId,QString stokId,int miktar);

    void projeIhtiyacSil(QString projeId,QString malzemeKod);

    void bildirimEkle(QString StokId,QString DepoId,QString Tarih,QString mesaj,int miktar);


private:

    QDateTime dateTime=dateTime.currentDateTime();

};



#endif // VERITABANIISLEMLERI_H
