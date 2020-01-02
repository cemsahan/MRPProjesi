#ifndef URUNSTRUCT_H
#define URUNSTRUCT_H

#include <QObject>

class UrunStruct : public QObject
{
    Q_OBJECT
public:
    explicit UrunStruct(QObject *parent = nullptr);
    UrunStruct(QString urunKodu,QString urunIsmi,QString urunFiyati,QString urunBirim,QString rafKodu,QString depoId);
    QString getUrunKodu();
    QString getUrunIsmi();
    QString getUrunFiyat();
    QString getUrunBirim();
    QString getRafKodu();
    QString getDepoId();
private:

QString urunKodu;
QString urunIsmi;
QString urunFiyati;
QString urunBirim;
QString rafKodu;
QString depoId;


signals:

public slots:
};

#endif // URUNSTRUCT_H
