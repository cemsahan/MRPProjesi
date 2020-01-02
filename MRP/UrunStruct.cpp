#include "UrunStruct.h"



UrunStruct::UrunStruct(QString urunKodu, QString urunIsmi, QString urunFiyati, QString urunBirim, QString rafKodu,QString depoId)
{

    this->urunKodu=urunKodu;
    this->urunIsmi=urunIsmi;
    this->urunFiyati=urunFiyati;
    this->urunBirim=urunBirim;
    this->rafKodu=rafKodu;
    this->depoId=depoId;
}

QString UrunStruct::getUrunKodu()
{
    return urunKodu;

}

QString UrunStruct::getUrunIsmi()
{
    return urunIsmi;
}

QString UrunStruct::getUrunFiyat()
{
    return urunFiyati;
}

QString UrunStruct::getUrunBirim()
{
    return urunBirim;
}

QString UrunStruct::getRafKodu()
{
    return rafKodu;
}

QString UrunStruct::getDepoId()
{
    return depoId;
}
