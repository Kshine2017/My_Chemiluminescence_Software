#include "queue.h"
#include <QDebug>

/**
 *是否空队列
 */



Queue::~Queue()
{
    makeEmpty();

}



bool Queue ::isEmpty()
{
    return front == NULL;
}


/**********销毁队列**************/

 bool Queue::makeEmpty()
{
    LinkNode  *p;
    while(front != NULL){
        p = front;
        front = front->next;
        delete p;
    }
    return true;
}



/***********尾部压入队列***********************/
void Queue::enqueue(const QString &x)
{
    if(front == NULL){
        front = rear = new LinkNode(x);
        if( !front){
            qDebug() << "内存不足";
        }
    }else {
        rear->next = new LinkNode(x);
        if(!rear){
          qDebug() << "内存不足";
        }
        rear = rear->next;
    }
}

/**在队列首部插入**/
void Queue::frontEnqueue(const QString &x)
{
    LinkNode *p = new LinkNode(x);
    if( !p ) qDebug() << "内存不足";
    if( front == NULL ){
        front = rear = p;
    }else{
        p->next = front;
        front = p;
    }
}


/**************出队列******************************/
void Queue::dequeue( QString &x)
{
    if(!isEmpty()){
        LinkNode *p = front;
        x = front->data;
        front = front->next;
        delete p;
    }else {
        handleUnderFlow();
    }
}

/************得到队头*************************************/
void Queue::getFront(QString &x)
{
    if( !isEmpty()){
        x = front->data;
    }else handleUnderFlow();
}

/**********控制向下溢出**********************************************/
void Queue::handleUnderFlow()
{
    qDebug() << "当前操作的队列是空的";
}
