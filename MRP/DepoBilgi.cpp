#include "DepoBilgi.h"




DepoBilgi::DepoBilgi(QString depoKod)
{
    this->depoKod=depoKod;
}
void DepoBilgi::SetDepoKod(QString depoKod)
{
    this->depoKod=depoKod;
}

QString DepoBilgi::GetDepoKod()
{
    return depoKod;
}


