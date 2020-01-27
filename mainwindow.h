#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QThread>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QPushButton>
#include <map>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSlider* slider;

private slots:
    void on_pushButton_clicked();
    void on_textEdit_textChanged();
    void on_pushButton_2_clicked();

    void on_horizontalSlider_rangeChanged(int min, int max);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    static int counter;
};
class Individual
{
public:
    std::vector<int> chromosome;
    std::map<int,int>kordinate_2;
    float fitness;
    std::vector<std::pair<int,int>>kordinate;
    Individual(std::vector<int> chromosome);
    Individual():fitness(0){}
    Individual mate(Individual parent2);
    void cal_fitness();
    void draw();
    void update();
    void erase();
};


#endif // MAINWINDOW_H
