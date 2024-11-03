#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <vector>
#include <QDebug>
#include <QTimer>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <QPointF>
#include <QThread>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLineF>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class Simulator;
}
QT_END_NAMESPACE

class Simulator : public QMainWindow
{
    Q_OBJECT

public:
    Simulator(QWidget *parent = nullptr);
    int maxTime;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *backgroundItem;
    QPixmap backgroundPic;
    QGraphicsView *view;
    vector <QGraphicsTextItem*> in;
    QGraphicsTextItem *out;
    vector <QGraphicsTextItem*> scale;
    Simulator(int,string,vector<pair<char, bool>>);
    int checkInputName(char);
    vector<pair<char, bool>> inputs;
    string stimName;

    ~Simulator();

private:
    Ui::Simulator *ui;
};
#endif // SIMULATOR_H
