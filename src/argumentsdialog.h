#ifndef ARGUMENTSDIALOG_H
#define ARGUMENTSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>

namespace Ui {
class ArgumentsDialog;
}

class ArgumentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArgumentsDialog(const QVector<QString> &argNames, const QVector<QString> &values,
                             QWidget *parent);
    ~ArgumentsDialog();
    QVector<QString> getValues() const;

private slots:
    void on_verticalScrollBar_valueChanged(int value);
    void keyPressEvent(QKeyEvent *);

    void on_pushButton_clicked();

private:
    Ui::ArgumentsDialog *ui;
    QVector<QString> argNames;
    QVector<QLabel *> labels;
    QVector<QLineEdit *> lines;
    float frameWidth;
};

#endif // ARGUMENTSDIALOG_H
