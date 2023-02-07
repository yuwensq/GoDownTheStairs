#ifndef START_H
#define START_H

#include <QWidget>

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    ~start();

private slots:

    void on_pushButton_shutdown_clicked();

    void on_pushButton_single_clicked();

    void on_pushButton_double_clicked();


    void on_pushButton_help_clicked();

private:
    Ui::start *ui;
};

#endif // START_H
