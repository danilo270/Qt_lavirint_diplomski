#ifndef SEPARATEWINDOW_H
#define SEPARATEWINDOW_H

#include <QDialog>
#include <QListWidget>
namespace Ui {
class SeparateWindow;
}

class SeparateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SeparateWindow(QWidget *parent = nullptr);
    ~SeparateWindow();
    void set_QlistWidget(QListWidget* widget);
private:
    Ui::SeparateWindow *ui;
    QListWidget* widget;
};

#endif // SEPARATEWINDOW_H
