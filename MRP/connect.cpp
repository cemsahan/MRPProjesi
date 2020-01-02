#include "connect.h"


Connect::Connect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName("boom");
    db.setUserName(kullaniciAdi);   //jdbc:mysql://"+host+":"+port+"/"+db_ismi+"?useUniCode=true&characterEncoding=utf8
    db.setPassword(parola);
    db.setDatabaseName(db_ismi);

    bool ok =db.open();
    if(ok)
    {
        qDebug()<<"baglandı";


    }
    else qDebug()<<"baglanmadı...";



}
int Connect::GirisKontrol(QString email, QString sifre)
{
    QSqlQuery sorgu;
    QSqlQuery sorgu1;

    sorgu.exec("SELECT * FROM users WHERE email=? and password=? and fonksiyon='DepoCalisani'");
    sorgu.addBindValue(email);
    sorgu.addBindValue(sifre);




    if(!sorgu.exec()) qDebug()<<"sorgu hatalı...";

    if(sorgu.next())
    {
        //QVariant depoIdvariant=sorgu.value(i);



        QString depo=sorgu.value("DepoId").toString();

        depoBilgi=new DepoBilgi(depo);

        this->calisanDepoKod=depo;

        SetCalisanDepoKod(depoBilgi->GetDepoKod());


        return 1;
    }

    sorgu1.exec("SELECT * FROM users WHERE email=? and password=? and fonksiyon='SirketCalisani'");
    sorgu1.addBindValue(email);
    sorgu1.addBindValue(sifre);

    if(!sorgu1.exec()) qDebug()<<"sorgu1 hatalı...";
    if(sorgu1.next())
    {
        return -1;
    }
    return 0;


}

void Connect::SetCalisanDepoKod(QString depoKod)
{
 this->calisanDepoKod=depoKod;
}

QString Connect::getCalisanDepoKod()
{
    return this->calisanDepoKod;

}





