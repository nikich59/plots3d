#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scene3dxyz.h>
#include <scene3dpolar.h>
#include <scene3dcomplex.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <argumentsdialog.h>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QFunction<Complex> function;
    QOperationCompiler<Complex> compiler;
};

#endif // MAINWINDOW_H
