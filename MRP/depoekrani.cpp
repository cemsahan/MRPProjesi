#include "depoekrani.h"
#include "ui_depoekrani.h"

DepoEkrani::DepoEkrani(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DepoEkrani)
{
    ui->setupUi(this);
tabloGuncelle(tabloSorgusu);




}

DepoEkrani::~DepoEkrani()
{
    delete ui;
}

void DepoEkrani::getCalisanDepoId(QString kod)
{

    this->depoCalisanKod=kod;


    tabloSorgusu="SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ' FROM depostok ,stok WHERE depostok.StokId=stok.StokId and depostok.DepoId="+depoCalisanKod;
    tabloGuncelle(tabloSorgusu);

}


void DepoEkrani::dosyaOku(QString path)
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
        if(stokKoduilkkarakter.size()==3) veriTabaniIslem->depostokEkle(stokKodu,stokIsmi,miktarInt,br,fiyat,guncellemeTarihi,depoCalisanKod,"");
      //  else veriTabaniIslem->projeEkle(stokKodu,stokIsmi,miktar,br,fiyat);
    }
}

void DepoEkrani::tabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView->clearFocus();


    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);
    model->setQuery(Sqlquery);

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();




}
void DepoEkrani::on_tf_urunKodAra_textChanged(const QString &arg1)
{

    QString kodAra=ui->tf_urunKodAra->text();

    tabloGuncelle("SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ'"
                  " FROM depostok ,stok WHERE depostok.StokId=stok.StokId and stok.StokId LIKE '%"+kodAra+"%'and depostok.DepoId="+depoCalisanKod);




}


void DepoEkrani::on_tf_urunBrAra_textChanged(const QString &arg1)
{
    QString birimAra=ui->tf_urunBrAra->text();


    tabloGuncelle("SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',depostok.AdetFiyat AS 'ADET FİYATI',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ'"
                  " FROM depostok ,stok WHERE depostok.StokId=stok.StokId and stok.Birim LIKE '%"+birimAra+"%'and depostok.DepoId="+depoCalisanKod);

}

void DepoEkrani::on_pushButton_clicked()
{
    QString urunKodu=ui->tf_urunKodu->text();
    QString urunIsmi=ui->tf_urunIsmi->text();
    QString urunBirim=ui->tf_urunBr->text();
    QString urunFiyat=ui->tf_urunFiyat->text();
    QString rafId=ui->tf_yeniurunRafIf->text();
    int miktar=ui->sp_urunMiktar->value();


    if(ui->tf_urunBr->text()==""||ui->tf_urunFiyat->text()==""||ui->tf_urunIsmi->text()==""||ui->tf_urunKodu->text()=="")
    {
        ui->lbl_message->setText("Lütfen Boş Alanları Doldurunuz !!!");
    }
    else {
    QString dateTimeString=dateTime.toString("dd/MM/yyyy");


    veriTabaniIslem->depostokEkle(urunKodu,urunIsmi,miktar,urunBirim,urunFiyat,dateTimeString,depoCalisanKod,rafId);
    QMessageBox::information(this,"Bilgi","Ürün Eklendi");
    tabloGuncelle(tabloSorgusu);

   ui->tf_urunKodu->setText("");
    ui->tf_urunIsmi->setText("");
   ui->tf_urunBr->setText("");
    ui->tf_urunFiyat->setText("");

    }

}






void DepoEkrani::on_btn_dosya_clicked()
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

void DepoEkrani::on_btn_sil_clicked()
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

        veriTabaniIslem->depostokSil(urunKodString,depoCalisanKod);
        tabloGuncelle(tabloSorgusu);
        QMessageBox::information(this,tr("UYARI"),urunKodString+" Kodlu Ürün Silindi...");



    }






}






}

void DepoEkrani::on_btn_guncelle_clicked()
{



    QModelIndex index=ui->tableView->selectionModel()->currentIndex();

    if(index.row()<0) {

        QMessageBox::information(this,tr("UYARI"),"LÜTFEN GÜNCELLENECEK ÜRÜNÜ SEÇİNİZ...") ;
        ui->tableView->resizeColumnsToContents();

    }
    else{

    QVariant urunKod=index.sibling(index.row(),0).data();
    QString urunKodString=urunKod.toString();

    QVariant urunIsmi=index.sibling(index.row(),1).data();
    QString urunIsmiString=urunIsmi.toString();

    QVariant urunFiyat=index.sibling(index.row(),7).data();
    QString urunFiyatString=urunFiyat.toString();

    QVariant urunBirim=index.sibling(index.row(),2).data();
    QString urunBirimString=urunBirim.toString();

    QVariant rafKodu=index.sibling(index.row(),3).data();
    QString rafKoduString=rafKodu.toString();



    qDebug()<<depoCalisanKod;

    urunStruct=new UrunStruct(urunKodString,urunIsmiString,urunFiyatString,urunBirimString,rafKoduString,depoCalisanKod);

    guncelleForm* frm=new guncelleForm();
    qDebug()<<"asd";
    frm->Bilgiler(urunStruct);

    frm->show();

    connect(frm,SIGNAL(signalTabloGuncelle()),this,SLOT(tabloGuncelle()));

    tabloGuncelle(tabloSorgusu);

    ui->tableView->resizeColumnsToContents();

}
}

void DepoEkrani::tabloGuncelle()
{

    model=new QSqlQueryModel();

    model->clear();

    ui->tableView->clearFocus();

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(tabloSorgusu);

    model->setQuery(Sqlquery);

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();



}





void DepoEkrani::on_tf_urunIsmiAra_textChanged(const QString &arg1)
{
    QString isimAra=ui->tf_urunIsmiAra->text();

    if(ui->tf_urunIsmiAra->text()=="") tabloGuncelle(tabloSorgusu);
    else{
    tabloGuncelle("SELECT stok.StokId AS 'STOK KODU',stok.StokIsmi AS 'STOK İSMİ',stok.Birim AS 'BİRİMİ',depostok.RafId AS 'RAF KODU',depostok.GirisMiktari AS 'GİRİŞ MİKTARI',depostok.CikisMikrari AS 'ÇIKIŞ MİKTARI',(depostok.GirisMiktari-depostok.CikisMikrari) AS '      BAKİYE        ',depostok.AdetFiyat AS 'ADET FİYATI',depostok.guncellemeTarihi AS 'GÜNCELLEME TARİHİ'"
                  " FROM depostok ,stok WHERE depostok.StokId=stok.StokId and stok.StokIsmi LIKE '%"+isimAra+"%'and depostok.DepoId="+depoCalisanKod);
}
}

void DepoEkrani::on_actionBildirim_Ekran_n_A_triggered()
{

    frm=new BildirimEkraniDepo();
    frm->depoIdAl(depoCalisanKod);
    frm->show();
    tabloGuncelle();
}



void DepoEkrani::on_pushButton_2_clicked()
{
    MainWindow* girisEkrani=new MainWindow();
    girisEkrani->show();
    this->close();
}




