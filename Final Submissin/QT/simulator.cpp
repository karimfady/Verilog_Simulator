#include "simulator.h"
#include "./ui_simulator.h"
#include "Module.h"
#include "Stimuli.h"
#include "File.h"

Simulator::Simulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Simulator)
{
    ui->setupUi(this);

}

Simulator::Simulator(int max,string stimName,vector<pair<char, bool>> ins){
    maxTime=max;
    inputs=ins;
    stimName=this->stimName;
    this->setFocusPolicy(Qt::StrongFocus);
    scene = new QGraphicsScene(0,0,1520,950);
    backgroundPic=QPixmap("/Users/karimfady/Downloads/SimulatorBackground.jpg");
    backgroundPic=backgroundPic.scaledToHeight(950);
    backgroundItem=new QGraphicsPixmapItem;
    backgroundItem->setPixmap(backgroundPic);
    scene->addItem(backgroundItem);

    view = new QGraphicsView(scene, this);
    view->setGeometry(0,0,1520,950);

    QGraphicsTextItem *s;

     QFont font;
    font.setBold(true);
    font.setPointSize(30);
    for(int i=0;i<ins.size();i++){
        in.push_back(s);
        char c=ins[i].first;
        QString inName=QChar(c);
        in[i]=new QGraphicsTextItem;
        in[i]->setFont(font);
        in[i]->setPos(50,(i+1)*130);
        in[i]->setDefaultTextColor(Qt::green);
        in[i]->setPlainText(inName);
        scene->addItem(in[i]);
    }
    out=new QGraphicsTextItem;
    out->setFont(font);
    out->setPos(50,600);
    out->setDefaultTextColor(Qt::green);
    out->setPlainText("O");
    scene->addItem(out);

    font.setPointSize(9);
    for(int i=0;i<50;i++){
     scale.push_back(s);
    int no=(maxTime/45)*i;
    QString noString=QString::number(no);
    scale[i]=new QGraphicsTextItem;
    scale[i]->setFont(font);
    scale[i]->setPos(80+(i*30),800);
    scale[i]->setDefaultTextColor(Qt::white);
    scale[i]->setPlainText(noString);
    scene->addItem(scale[i]);
    }


    QPen pen(Qt::green);
    pen.setWidth(2);



    //Drawing the lines
    for(int i=0;i<ins.size();i++){
            int last=80,current=80;
            int c=0;
            string line;
            ifstream inputFile("/Users/karimfady/Downloads/Simulation.sim"); // Open the input file
            if (!inputFile) {
                cout << "Unable to open file data.txt";
                    // Exit if the file cannot be opened
            }

            while (getline(inputFile, line))    {
                int Time;
                char inputName;
                bool logicVal;


                istringstream iss(line);
                string temp;


                iss >> Time >> inputName >> temp;
                int logicInt;
                iss >> logicInt;
                logicVal = logicInt;


                cout << "Time: " << Time << ", Input Name: " << inputName << ", Logic Value: " << logicVal << std::endl;
                if(ins[i].first==inputName){
                current=(Time/40)*30;
                scene->addItem(new QGraphicsLineItem(80+last,(i+1)*130+(logicVal*50) , 80+current,(i+1)*130+(logicVal*50)));
                last=current;
                }

            }
            for (auto item : scene->items()) {
                if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(item)) {
                    lineItem->setPen(pen);
                }
            }
        inputFile.close();
        }
    int last=80,current=80;
    int c=0;
    string line;
    ifstream inputFile("/Users/karimfady/Downloads/Simulation.sim"); // Open the input file
    if (!inputFile) {
        cout << "Unable to open file data.txt";
            // Exit if the file cannot be opened
    }

    while (getline(inputFile, line))    {
        int Time;
        char inputName;
        bool logicVal;


        istringstream iss(line);
        string temp;


        iss >> Time >> inputName >> temp;
        int logicInt;
        iss >> logicInt;
        logicVal = logicInt;


        cout << "Time: " << Time << ", Input Name: " << inputName << ", Logic Value: " << logicVal << std::endl;
        if('o'==inputName){
            current=(Time/40)*30;
            scene->addItem(new QGraphicsLineItem(80+last,(3.5+1)*130+(logicVal*50) , 80+current,(3.5+1)*130+(logicVal*50)));
            last=current;
        }

    }
    for (auto item : scene->items()) {
        if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(item)) {
            lineItem->setPen(pen);
        }
    }
    }






int Simulator::checkInputName(char c){
    for(int i=0;i<inputs.size();i++){
        if(c==inputs[i].first)
            return i;
    }
    return -1;
}

Simulator::~Simulator()
{
    delete ui;
}
