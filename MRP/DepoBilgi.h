#ifndef DEPOBILGI_H
#define DEPOBILGI_H

#include <QObject>

class DepoBilgi : public QObject
{
    Q_OBJECT
public:
    void SetDepoKod(QString depoKod);
    QString GetDepoKod();
    explicit DepoBilgi(QString depoKod);
private:
    QString depoKod;
signals:

public slots:
};

#endif // DEPOBILGI_H
