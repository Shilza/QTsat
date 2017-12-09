#include "floodtimer.h"

FloodTimer::FloodTimer(QWidget *parent) : QObject(parent){
    timerErrorHide = new QTimer(this);
    timerErrorHide->setSingleShot(true);
    timerShow = new QTimer(this);
    timerShow->setInterval(10);
    counter=0;
    connect(timerErrorHide, SIGNAL(timeout()), this, SLOT(emitErrorTimeout()));
    connect(timerShow, SIGNAL(timeout()), this, SLOT(emitShowTimeout()));
}

int FloodTimer::remainingTime(){
    return timerErrorHide->remainingTime();
}

void FloodTimer::start(){
    counter++;
    if(counter<4){
        timerErrorHide->start(3000*counter);
        timerShow->start();
    }
}

void FloodTimer::emitErrorTimeout(){
    timerShow->stop();
    emit errorTimeout();
}

void FloodTimer::emitShowTimeout(){
    emit showTimeout();
}