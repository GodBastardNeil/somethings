#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QWidget>

#include "searchprocess.h"

namespace Ui { class algorithm; }

class algorithm : public QWidget
{
    Q_OBJECT

public:
    explicit algorithm(QWidget *parent = nullptr);
    ~algorithm();

signals:
    void return_to_menu();

private slots:
    void on_str_textEdited(const QString &arg1);
    void on_pattern_textChanged(const QString &arg1);
    void show_alg();
    void on_Ok_clicked();
    void on_b_back_clicked();
    void on_l_back_clicked();
    void on_l_forward_clicked();
    void on_b_forward_clicked();

    void on_return_to_clicked();

private:
    Ui::algorithm *ui;
    QVector<QVector<QString>> s; // страница с подпунктами демонстрации
    int i, n; // номер нынешней страницы и количество страниц
    int j, m; // номер нынешнего подпункта и количество подпунктов этой страницы

    searchprocess sp;

    algorithm(const algorithm &)  = delete;
    algorithm(const algorithm &&) = delete;
    algorithm& operator=(const algorithm &)  = delete;
    algorithm& operator=(const algorithm &&) = delete;
};

#endif // ALGORITHM_H
