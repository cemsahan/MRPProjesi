#include "guncelleForm.h"
#include "ui_guncelleForm.h"

guncelleForm::guncelleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::guncelleForm)
{
    ui->setupUi(this);


    veriTabaniIslem=new VeriTabaniIslemleri();




}

guncelleForm::~guncelleForm()
{
    delete ui;
}

void guncelleForm::Bilgiler(UrunStruct *urunStruct)
{
    qDebug()<<urunStruct->getDepoId();

    ui->tf_guncelleUrunKodu->setText(urunStruct->getUrunKodu());
    ui->tf_guncelleUrunIsmi->setText(urunStruct->getUrunIsmi());
    ui->tf_guncelleUrunBirim->setText(urunStruct->getUrunBirim());
    ui->tf_guncelleRafKodu->setText(urunStruct->getRafKodu());
    ui->tf_guncelleUrunFiyati->setText(urunStruct->getUrunFiyat());
    ui->tf_guncelleUrunKodu->setEnabled(false);
    depoId=urunStruct->getDepoId();

}




void guncelleForm::on_btn_guncelle_clicked()
{




    QString urunKod=ui->tf_guncelleUrunKodu->text();
    QString urunIsmi=ui->tf_guncelleUrunIsmi->text();
    QString urunBirim=ui->tf_guncelleUrunBirim->text();
    QString urunFiyati=ui->tf_guncelleUrunFiyati->text();
    QString rafIKod=ui->tf_guncelleRafKodu->text();

    veriTabaniIslem->depoStokGuncelle(urunKod,urunIsmi,urunBirim,urunFiyati,rafIKod,depoId);

    QMessageBox::information(this,tr("UYARI"),urunKod+" Kodlu Ürün Güncellendi...");

    emit signalTabloGuncelle();

    this->close();



}











void guncelleForm::on_pushButton_clicked()
{
    this->close();
}
