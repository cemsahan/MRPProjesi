#include "AnaEkran.h"
#include "ui_AnaEkran.h"


AnaEkran::AnaEkran(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnaEkran)
{
    ui->setupUi(this);

    tabloGuncelle(tabloSorgusu);
}



void AnaEkran::dosyaOku(QString path)
{

    QFile file(path);
    file.open(QIODevice::Truncate|QFile::ReadOnly);
    file.readLine();
    QString guncellemeTarihi=file.readLine();


    while(!file.atEnd())
    {

        QByteArray firstLine=file.readLine();
        QString lineString=QString::fromLocal8Bit(firstLine.data());

        QStringList sline=lineString.split(';');

        QString fiyat=sline.at(sline.size()-2);
        QString br=sline.at(sline.size()-4);

        QString miktar=sline.at(sline.size()-5);
        int miktarInt=miktar.toInt(NULL,10);

        QString stokIsmi=sline.at(sline.size()-6);
        QString stokKodu=sline.at(sline.size()-7);

        QStringList stokKoduKontrol=stokKodu.split('-');
        QString stokKoduilkkarakter=stokKoduKontrol.at(0);
     //   if(stokKoduilkkarakter.size()==3) veriTabaniIslem->depostokEkle(stokKodu,stokIsmi,miktarInt,br,fiyat,guncellemeTarihi);

    }
}

void AnaEkran::tabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView->clearFocus();

   // QString sorgu="SELECT * FROM depostok";
    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);
    model->setQuery(Sqlquery);
    ui->tableView->setModel(model);

}




AnaEkran::~AnaEkran()
{
    delete ui;
}



void AnaEkran::on_tf_urunKodAra_textChanged(const QString &arg1)
{

    QString kodAra=ui->tf_urunKodAra->text();

    tabloGuncelle("SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ'"
                  " FROM depostok ,stok WHERE depostok.StokId=stok.StokId and stok.StokId LIKE '%"+kodAra+"%' ");




}

void AnaEkran::on_tf_urunIsmiAra_textChanged(const QString &arg1)
{
    QString isimAra=ui->tf_urunIsmiAra->text();

    tabloGuncelle("SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ'"
                  " FROM depostok ,stok WHERE depostok.StokId=stok.StokId and stok.StokIsmi LIKE '%"+isimAra+"%' ");

}

void AnaEkran::on_tf_urunBrAra_textChanged(const QString &arg1)
{
    QString birimAra=ui->tf_urunBrAra->text();


    tabloGuncelle("SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ'"
                  " FROM depostok ,stok WHERE depostok.StokId=stok.StokId and stok.Birim LIKE '%"+birimAra+"%' ");

}

void AnaEkran::on_pushButton_clicked()
{
    QString urunKodu=ui->tf_urunKodu->text();
    QString urunIsmi=ui->tf_urunIsmi->text();
    QString urunBirim=ui->tf_urunBr->text();
    QString urunFiyat=ui->tf_urunFiyat->text();
    int miktar=ui->sp_urunMiktar->value();


    if(ui->tf_urunBr->text()==""||ui->tf_urunFiyat->text()==""||ui->tf_urunIsmi->text()==""||ui->tf_urunKodu->text()=="")
    {
        ui->lbl_message->setText("Lütfen Boş Alanları Doldurunuz !!!");
    }
    else {
    QString dateTimeString=dateTime.toString("dd/MM/yyyy");


    //veriTabaniIslem->depostokEkle(urunKodu,urunIsmi,miktar,urunBirim,urunFiyat,dateTimeString);

    tabloGuncelle(tabloSorgusu);
    }

}






void AnaEkran::on_btn_dosya_clicked()
{



    QString path=QFileDialog::getOpenFileName(this,tr("Open File"),"C://","All Files (*.csv)" );

    if(path=="")
    {
        QMessageBox::information(this,tr("UYARI!"),"Lütfen .csv Uzantılı Dosyanızı Seçiniz...");

    }
        else
    {
        dosyaOku(path);

        QMessageBox::information(this,tr("UYARI"),"Eklendi...");

        tabloGuncelle(tabloSorgusu);

         }

}

void AnaEkran::on_btn_sil_clicked()
{
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();



    if(index.row()<0) {

        QMessageBox::information(this,tr("UYARI"),"LÜTFEN SİLİNECEK ÜRÜNÜ SEÇİNİZ...") ;

    }
    else{


        QVariant urunKod=index.sibling(index.row(),0).data();
        QString urunKodString=urunKod.toString();


    QMessageBox msgBox;
    msgBox.setWindowTitle("UYARI");
    msgBox.setText(urunKodString+" Kodlu ürününüzü silmek üzeresiniz...");
   // msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::Yes)->setText("SİL");
    msgBox.addButton(QMessageBox::No)->setText("SİLME");
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){

        veriTabaniIslem->depostokSil(urunKodString,NULL);
        tabloGuncelle(tabloSorgusu);
        QMessageBox::information(this,tr("UYARI"),urunKodString+" Kodlu Ürün Silindi...");



    }






}






}

void AnaEkran::on_btn_guncelle_clicked()
{



    QModelIndex index=ui->tableView->selectionModel()->currentIndex();

    if(index.row()<0) {

        QMessageBox::information(this,tr("UYARI"),"LÜTFEN GÜNCELLENECEK ÜRÜNÜ SEÇİNİZ...") ;

    }
    else{

    QVariant urunKod=index.sibling(index.row(),0).data();
    QString urunKodString=urunKod.toString();

    QVariant urunIsmi=index.sibling(index.row(),1).data();
    QString urunIsmiString=urunIsmi.toString();

    QVariant urunFiyat=index.sibling(index.row(),6).data();
    QString urunFiyatString=urunFiyat.toString();

    QVariant urunBirim=index.sibling(index.row(),2).data();
    QString urunBirimString=urunBirim.toString();

    QVariant rafKodu=index.sibling(index.row(),3).data();
    QString rafKoduString=rafKodu.toString();





  /*  urunStruct=new UrunStruct(urunKodString,urunIsmiString,urunFiyatString,urunBirimString,rafKoduString,d);

    guncelleForm* frm=new guncelleForm();
    qDebug()<<"asd";
    frm->Bilgiler(urunStruct);

    frm->show();

    connect(frm,SIGNAL(signalTabloGuncelle()),this,SLOT(tabloGuncelle()));

    tabloGuncelle(tabloSorgusu);*/

}
}

void AnaEkran::tabloGuncelle()
{

    model=new QSqlQueryModel();

    model->clear();

    ui->tableView->clearFocus();

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(tabloSorgusu);

    model->setQuery(Sqlquery);

    ui->tableView->setModel(model);


}







