#include "BildirimEkraniDepo.h"
#include "ui_BildirimEkraniDepo.h"

BildirimEkraniDepo::BildirimEkraniDepo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BildirimEkraniDepo)
{
    ui->setupUi(this);

    veriTabaniIslem=new VeriTabaniIslemleri();
    ui->btn_onemsiz->setVisible(false);


}


BildirimEkraniDepo::~BildirimEkraniDepo()
{
    delete ui;
}

void BildirimEkraniDepo::bildirimTabloGuncelle(QString sorgu)
{
    model=new QSqlQueryModel();

    model->clear();

    ui->tableView_bildirimDepo->clearFocus();

   // QString sorgu="SELECT * FROM depostok";

    QSqlQuery Sqlquery=veriTabaniIslem->donenSorgu(sorgu);

    model->setQuery(Sqlquery);

    ui->tableView_bildirimDepo->setModel(model);

    ui->tableView_bildirimDepo->resizeColumnsToContents();



}

void BildirimEkraniDepo::depoIdAl(QString depoId)
{
    this->calisanDepoId=depoId;
    bildirimTabloGuncelle("SELECT BildirimId AS 'Bildirim Kodu',StokId AS 'Ürün Kodu',Tarih,Miktar,Mesaj AS 'Kullanici Mesajı' FROM bildirim WHERE Onay=0 and DepoId="+calisanDepoId);
    }



void BildirimEkraniDepo::on_tableView_bildirimDepo_doubleClicked(const QModelIndex &index)
{
    QVariant bildirimKodu=index.sibling(index.row(),0).data();
    QVariant UrunKod=index.sibling(index.row(),1).data();
    QVariant Tarih =index.sibling(index.row(),2).data();
    QVariant miktar=index.sibling(index.row(),3).data();

    QString bildirimKodString =bildirimKodu.toString();
    QString urunKodString=UrunKod.toString();
    QString tarihString=Tarih.toString();
    QString miktarString=miktar.toString();
    QMessageBox msgBox;

    msgBox.setWindowTitle("Sipariş Onayı");

    msgBox.setText(bildirimKodString+" Kodlu bildirimi onaylamak üzeresiniz...");

    msgBox.addButton(QMessageBox::Yes)->setText("Tamam");

    msgBox.addButton(QMessageBox::No)->setText("İptal");

    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {

        veriTabaniIslem->sirketDepoalisverisEkle(urunKodString,calisanDepoId,miktarString,"",tarihString);

        veriTabaniIslem->bildirimGuncelle(bildirimKodString,calisanDepoId,urunKodString,miktarString.toInt(NULL,10));

        veriTabaniIslem->depoSirketEkle(miktarString.toInt(NULL,10),urunKodString);

        bildirimTabloGuncelle("SELECT BildirimId AS 'Bildirim Kodu',StokId AS 'Ürün Kodu',Tarih,Miktar,Mesaj AS 'Kullanici Mesajı' FROM bildirim WHERE Onay=0 and DepoId="+calisanDepoId);


    }
}








