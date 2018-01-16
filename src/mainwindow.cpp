#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(size());
    setMaximumSize(size());

    compiler.initContextFromFile(QString(":/new/prefix1/opsynonyms.txt"));
    compiler.setCompilationFlags(compiler.getCompilationFlags() |
                                 CompilationFlags::ALLOW_SQARE_BRACKETS |
                                 CompilationFlags::ALLOW_UNSIGNED_MULTIPLICATION);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Scene3DXYZ *scene = new Scene3DXYZ();
    scene->setGeometry(geometry());
    scene->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Scene3DComplex *scene = new Scene3DComplex();
    scene->setGeometry(geometry());
    scene->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    Scene3DPolar *scene = new Scene3DPolar();
    scene->setGeometry(geometry());
    scene->show();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    function.setString(ui->lineEdit->text(), compiler);
    ui->label->setText(function.result().toQString());
}
