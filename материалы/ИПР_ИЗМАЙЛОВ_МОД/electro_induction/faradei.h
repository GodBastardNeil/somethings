#ifndef FARADEI_H
#define FARADEI_H

#include <QWidget>

#include "picturebox.h"

namespace Ui { class faradei; }

class faradei : public QWidget
{
    Q_OBJECT

public:
    explicit faradei(QWidget *parent = nullptr);
    ~faradei();

signals:
    void return_to_menu();

private slots:
    void on_return_to_clicked(); // вернуться в меню

    void on_B_change_activated(int index);
    void on_B_change_2_activated(int index);

    void on_R_change_activated(int index);

    void on_picture_activated(int index);

private:
    Ui::faradei *ui;
};

#endif // FARADEI_H
