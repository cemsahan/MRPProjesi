#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::mainWindow)

{

    ui->setupUi(this);
    con = new Connect();

}

MainWindow::~MainWindow()
{
    delete ui;


}


void MainWindow::on_pushButton_clicked()
{
    ui->lbl_message->setText("");

    QString email="";
    QString sifre="";

    email=ui->tf_email->text();
    sifre=ui->tf_sifre->text();
    if(email==""||sifre=="")
    {
       ui->lbl_message->setText("Lütfen gerekli alanları doldurunuz...");
    }
    else
    {

    int kontrol=con->GirisKontrol(email,sifre);

    if(kontrol==1) {

        qDebug()<<"Depo Giriş Başarılı";
        qDebug()<<con->depoBilgi->GetDepoKod();



        DepoEkrani* depoEkrani=new DepoEkrani();

        depoEkrani->getCalisanDepoId(con->depoBilgi->GetDepoKod());



        //AnaEkran* frm=new AnaEkran();
        depoEkrani->showMaximized();

        this->close();


    }
    else if(kontrol==-1) {

    qDebug()<<"Şirket Giriş Başarılı";
    SirketEkrani* sirketEkrani=new SirketEkrani();
    sirketEkrani->showMaximized();
    this->close();




    }
    else  {
              ui->lbl_message->setText("Email veya parola yanlış...");
}
}
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}
