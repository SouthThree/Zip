#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huffmanzip.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Methods::Finalize();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_compress_clicked()
{
    if(global::FileName!="")
    {
        Methods::CountFreq(global::PATH,global::FileName);
        Methods::BuildTree(global::PATH,global::FileName);
        Methods::EncodeFile(global::PATH,global::FileName,threadCount);
        Methods::WriteLog(global::PATH,global::FileName,threadCount);
        string s;
        s="compress complete\nfile:";
        s+=global::PATH+global::FileName;

        QMessageBox::information(this,"compress complete",QString::fromStdString(s));
    }
    else
        QMessageBox::information(this,"error","no file selected");
    Methods::Finalize();
    ui->lineEdit->setText("");

}

void MainWindow::on_extract_clicked()
{
    if(global::FileName!="")
    {
        string logfilename=global::FileName.substr(0,global::FileName.length()-4);
        Methods::DecodeFile(global::PATH,logfilename,threadCount);
        QMessageBox::information(this,"Decode File:","Decode File Succeeded!");
    }
    else
        QMessageBox::information(this,"error","no file selected");
}



void MainWindow::on_pushButton_clicked()
{
    QString file_full = QFileDialog::getOpenFileName(this, tr("open file"),".");

    ui->lineEdit->setText(file_full);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QFileInfo fileinfo;
    QString PATH;
    QString fileName;
    fileinfo=QFileInfo(arg1);
    fileName=fileinfo.fileName();
    PATH=fileinfo.path();
    PATH+='/';
    global::FileName=fileName.toStdString();
    global::PATH=PATH.toStdString();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    threadCount=1+index;
}
