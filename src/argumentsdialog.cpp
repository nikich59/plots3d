#include "argumentsdialog.h"
#include "ui_argumentsdialog.h"

ArgumentsDialog::ArgumentsDialog(const QVector<QString> &argNames, const QVector<QString> &values,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArgumentsDialog)
{
    ui->setupUi(this);
    setMaximumSize(width(), height());
    setMinimumSize(width(), height());
    setModal(true);

    frameWidth = (float)width() / 20.0;

    for (int i = 0; i < argNames.length(); i++) {
        QLabel *label = new QLabel(argNames[i], this);
        label->setGeometry(0, 0, (ui->verticalScrollBar->x() - 3 * frameWidth) / 2, height() / 8);
        QLineEdit *line = new QLineEdit(values[i], this);
        line->setGeometry(label->geometry());
        QFont font = label->font();
        font.setPointSizeF((float)height() / 20.0);
        label->setFont(font);
        line->setFont(font);
        if (label->fontMetrics().width(argNames[i]) > label->width()) {
            font.setPointSizeF((float)label->width() / label->fontMetrics().width(argNames[i]) *
                               font.pointSizeF());
            label->setFont(font);
        }
        labels.push_back(label);
        lines.push_back(line);
    }

    int totalHeight;
    if (labels.isEmpty())
        totalHeight = 0;
    else
        totalHeight = frameWidth + (frameWidth + labels[0]->height()) * labels.length();
    if (totalHeight <= height()) {
        ui->verticalScrollBar->setEnabled(false);
        ui->verticalScrollBar->setMinimum(0);
        ui->verticalScrollBar->setMaximum(0);
    }else {
        ui->verticalScrollBar->setEnabled(true);
        ui->verticalScrollBar->setMinimum(0);
        ui->verticalScrollBar->setMaximum(20 * (totalHeight - height()) /
                                          (frameWidth + labels[0]->height()));
        ui->verticalScrollBar->setSingleStep(1);
    }

    ui->verticalScrollBar->setValue(0);
    on_verticalScrollBar_valueChanged(0);
}

ArgumentsDialog::~ArgumentsDialog()
{
    delete ui;
    for (int i = 0; i < labels.length(); i++)
        delete labels[i];
    for (int i = 0; i < lines.length(); i++)
        delete lines[i];
}

QVector<QString> ArgumentsDialog::getValues() const
{
    QVector<QString> values;
    for (int i = 0; i < lines.length(); i++)
        values.push_back(lines[i]->text());
    return values;
}

void ArgumentsDialog::on_verticalScrollBar_valueChanged(int value)
{
    if (labels.length() < 1)
        return;
    int totalHeight = frameWidth + (frameWidth + labels[0]->height()) * labels.length();
    if (totalHeight < height())
        totalHeight = height();
    for (int i = 0; i < labels.length(); i++) {
        labels[i]->setGeometry(frameWidth, frameWidth + (frameWidth + labels[0]->height()) * i -
                (totalHeight - height()) * ui->verticalScrollBar->value() /
                (ui->verticalScrollBar->maximum() > 0 ? ui->verticalScrollBar->maximum() : 1),
                labels[0]->width(), labels[0]->height());
        lines[i]->setGeometry(labels[i]->geometry().right() + frameWidth, labels[i]->y(),
                             lines[0]->width(), lines[0]->height());
    }
}

void ArgumentsDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter)
        accept();
}

void ArgumentsDialog::on_pushButton_clicked()
{
    accept();
}
