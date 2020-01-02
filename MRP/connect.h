#ifndef CONNECT_H
#define CONNECT_H
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>
#include <iostream>
#include <sql.h>
#include <DepoBilgi.h>


 class Connect
{
public:

     Connect();

    int GirisKontrol(QString email,QString sifre);

    void SetCalisanDepoKod(QString depoKod);

    QString getCalisanDepoKod();

    DepoBilgi* depoBilgi;



 private:


   QString kullaniciAdi="root";

   QString parola="";

   QString db_ismi="boom";

   QString host="localhost";

   int port=3306;

   QSqlDatabase db;

   QString calisanDepoKod;




 };






#endif // CONNECT_H






















