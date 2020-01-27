#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "separatewindow.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QObject>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include <QVector>
#include <QRandomGenerator>
#include <QThread>
#include <QTime>
#include <QVector>
#include <vector>
#include <QtMath>
#include <utility>
#include <QSlider>
QPushButton* lavirint[40][40];
std::vector<std::pair<int,int>>zid;
std::vector<std::vector<std::pair<int,int>>>zid2;
int generation =0;
double penali=0;
 bool found=false;
int start1,start2,igrac_x,igrac_y;
int igractmp_x,igractmp_y;
int finis_x,finis_y;
int MainWindow::counter=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)    
{
    srand(time(NULL));
    int broj=0,k=0,broj2=0,n=0;
    ui->setupUi(this);
    QWidget parent2;
    slider=this->ui->horizontalSlider;
    slider->setRange(10,40);
    parent2.resize(500,500);
    for(int i=0;i!=40;++i){
        std::vector<std::pair<int,int>>v;
        for(int j=0;j!=40;++j){
            v.push_back(std::pair<int,int>{0,0});
        }
       zid2.push_back(v);
    }
    for (int i=0;i!=40;++i) {
        for (int j=0;j!=40;j++) {
            lavirint[i][j]=new QPushButton();
            if(i==0 || j==0 || i==39 || j==39){
                lavirint[i][j]->setStyleSheet("background-color:black");
                lavirint[i][j]->setText("w");
                zid.push_back(std::pair<int,int>{i,j});
                zid2[i][j].first=i;
                zid2[i][j].second=j;
            }
            ui->gridLayout->addWidget(lavirint[i][j],i,j);
        }
    }
}
Individual Individual::mate(Individual parent2){
    std::vector<int>child_chromosome;
    QMessageBox mb;
    for(int i=0;i!=chromosome.size()/2;++i){
        child_chromosome.push_back(chromosome[i]);
    }
    for (int j=parent2.chromosome.size()/2;j!=parent2.chromosome.size();++j) {
           child_chromosome.push_back(parent2.chromosome[j]);
    }
    return Individual(child_chromosome);
}
Individual::Individual(std::vector<int>chromosome1){
    this->chromosome=chromosome1;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(30);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::on_pushButton_clicked()
{
    QMessageBox mb;
    counter++;
    for (int i=0;i!=40;++i) {
        for (int j=0;j!=40;j++) {
            lavirint[i][j]->setText("");
            if(i!=0 && j!=0 && i!=39 && j!=39){
                lavirint[i][j]->setStyleSheet("background-color:white");
            }
        }
    }
    int k=0,brojx,brojy=0,broj_start=0,broj_start2=0,broj_finis=0,broj_finis2=0;
    while (k!=300) {
        brojx=rand()%40+0;
        brojy=rand()%40+0;
        zid.push_back(std::pair<int,int>{brojy,brojx});
        zid2[brojy][brojx].first=brojy;
        zid2[brojy][brojx].second=brojx;
        lavirint[brojy][brojx]->setStyleSheet("background-color:black");
        lavirint[brojy][brojx]->setText("w");
        k++;
    }
    while (true) {
        broj_start=rand()%40+0;
        broj_start2=rand()%40+0;
        broj_finis=rand()%40+0;
        broj_finis2=rand()%40+0;
        if(broj_start==0||broj_start==39||broj_start2==0||broj_start2==39||broj_finis==0||broj_finis==39||broj_finis2==0||broj_finis2==39||lavirint[broj_start][broj_start2]->text()=='w'
                ||lavirint[broj_finis][broj_finis2]->text()=='w')continue;
        if(broj_start-broj_finis>=20&&broj_start2-broj_finis2>=20)break;
    }
    start1=broj_start;
    start2=broj_start2;
    igrac_x=broj_start2;
    igrac_y=broj_start;
    finis_y=broj_finis;
    finis_x=broj_finis2;
    lavirint[broj_start][broj_start2]->setStyleSheet("background-color:green");
    lavirint[broj_finis][broj_finis2]->setStyleSheet("background-color:red");
}
void Individual::update(){
    QMessageBox mb;
    int move=0;
    int broj=0,broj2=0;
    int tmp=0,j=0;
    std::vector<std::pair<int,int>>tmp_kord;
    bool flag=false,flag2=false,flag3=false;
    while (1) {
        flag2=false;
        if(j==chromosome.size())break;
        if(chromosome[j]==0){
            flag=false;
            if(zid2[igrac_y][igrac_x-1].first==igrac_y&&zid2[igrac_y][igrac_x-1].second==igrac_x-1)
                {
                flag=true;
                chromosome[j]=rand()%4;
                }
                if(!flag&&!flag2){
                    igrac_x--;
                    kordinate.push_back(std::pair<int,int>(igrac_y,igrac_x));
                    j++;
                    continue;
                }
            }
        if(chromosome[j]==1){
            flag=false;
            if(zid2[igrac_y-1][igrac_x].first==igrac_y-1&&zid2[igrac_y-1][igrac_x].second==igrac_x)
                {
                flag=true;
                chromosome[j]=rand()%4;
                }
            if(!flag&&!flag2){
                igrac_y--;
                kordinate.push_back(std::pair<int,int>(igrac_y,igrac_x));
                j++;
                continue;
            }
        }
        if(chromosome[j]==2){
            flag=false;
            if(zid2[igrac_y][igrac_x+1].first==igrac_y&&zid2[igrac_y][igrac_x+1].second==igrac_x+1)
                {
                flag=true;
                chromosome[j]=rand()%4;
                }
                if(!flag&&!flag2){
                    igrac_x++;
                    kordinate.push_back(std::pair<int,int>(igrac_y,igrac_x));
                    j++;
                    continue;
                }
        }
        if(chromosome[j]==3){
            flag=false;
            if(zid2[igrac_y+1][igrac_x].first==igrac_y+1&&zid2[igrac_y+1][igrac_x].second==igrac_x)
                {
                flag=true;
                chromosome[j]=rand()%4;
                }
                if(!flag&&!flag2){
                    igrac_y++;
                    kordinate.push_back(std::pair<int,int>(igrac_y,igrac_x));
                    j++;
                    continue;
                }
            }
    }
}
void Individual::draw(){
    QMessageBox mb;
    mb.setText("Velicina kordinata:"+QString::number(kordinate.size()));
    //mb.exec();
    for (int i=0;i!=kordinate.size();++i) {
        lavirint[kordinate[i].first][kordinate[i].second]->setStyleSheet("background-color:blue");
        QMessageBox mb;
        if(kordinate[i].first==finis_y&&kordinate[i].second==finis_x){
            mb.setText("Cilj je dostignut generacija:"+QString::number(generation));
            mb.exec();
            found=true;
            return;
        }
        delay();
    }
}
void Individual::erase(){
    for (int i=0;i!=kordinate.size();++i) {
        lavirint[kordinate[i].first][kordinate[i].second]->setStyleSheet("background-color:white");
    }
    //kordinate.clear();
}
bool sort_kord(std::pair<int,int>a,std::pair<int,int>b){
    return abs(a.first-finis_y)+abs(a.second-finis_x)<abs(b.first-finis_y)+abs(b.second-finis_x);
}
void Individual::cal_fitness(){
   std::vector<std::pair<int,int>>vi;
    //Mutacija
    chromosome[rand()%100]=rand()%4;
    chromosome[rand()%200+100]=rand()%4;
    penali=0;
    this->update();
    vi=kordinate;
    this->fitness=0;
    //std::sort(vi.begin(),vi.end(),sort_kord);
    fitness=sqrt(pow((abs(vi[vi.size()-1].first-finis_y)),2)+pow((vi[vi.size()-1].second-finis_x),2))+penali;
    igrac_x=igractmp_x;
    igrac_y=igractmp_y;
}
void MainWindow::on_pushButton_2_clicked()
{
       srand((unsigned)(time(0)));
       QMessageBox mb;
       QString s1;
       std::vector<Individual>population(10);
       std::vector<Individual>new_generation;
       int counter2=0;
       igractmp_x=igrac_x;
       igractmp_y=igrac_y;
       Individual parent1,parent2,child,child2;
       for(int i=0;i!=population.size();++i){
           for(int j=0;j!=200;++j){
               population[i].chromosome.push_back(rand()%4);
           }
       }
       for(int i=0;i!=population.size();++i){
           population[i].cal_fitness();
       }
       mb.setText("Krece generacija!");
       mb.exec();
       while (!found) {
           s1="";
           if(igrac_x==finis_x&&igrac_y==finis_y){
               mb.setText("Cilj je dostignut generacija:"+QString::number(generation));
               mb.exec();
               found=true;
               return;
           }
           counter2=2;
           new_generation.clear();
           new_generation.push_back(population[0]);
           new_generation.push_back(population[1]);
           for(int i=0;i!=population.size()/2-1;++i){
               parent1=population[i];
               parent2=population[i+1];
               child=parent1.mate(parent2);
               child2=parent2.mate(parent1);
               new_generation.push_back(child);
               new_generation.push_back(child2);
               counter2+=2;
           }
           mb.setText("Generacija:"+QString::number(generation));
           mb.exec();
           population=new_generation;
           for(int i=2;i!=population.size();++i){
               population[i].cal_fitness();
           }
           std::sort(population.begin(),population.end(),[](Individual a,Individual b)->bool{return a.fitness<b.fitness;});
           for(int i=0;i!=population.size();++i){
               //population[i].draw();
               s1+=QString::number(population[i].fitness)+", ";
               if(found)return;
               //population[i].erase();
           }
           mb.setText("Fitnes:"+s1);
           mb.exec();
           generation++;
       }
}

void MainWindow::on_horizontalSlider_rangeChanged(int min, int max)
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QLabel* labela=this->ui->label;
    QMessageBox mb;
    mb.setText("saasa"+QString::number(value));
    //mb.exec();
    //labela->addAction(QAction::)
    labela->setText("Procenat za elitizam"+QString::number(value)+"%");
}
