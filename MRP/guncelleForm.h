#ifndef GUNCELLEFORM_H
#define GUNCELLEFORM_H

#include <QWidget>
#include <UrunStruct.h>

#include <VeriTabaniIslemleri.h>
#include <QMessageBox>

namespace Ui {
class guncelleForm;
}

class guncelleForm : public QWidget
{
    Q_OBJECT

public:
    explicit guncelleForm(QWidget *parent = 0);
    ~guncelleForm();

   void Bilgiler(UrunStruct* urunStruct);

   QString depoId;
signals:
   void signalTabloGuncelle();

private slots:


   void on_btn_guncelle_clicked();

   void on_pushButton_clicked();

private:

    Ui::guncelleForm *ui;

    VeriTabaniIslemleri* veriTabaniIslem;

};

#endif // GUNCELLEFORM_H
