#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <QString>
#include <QWidget>
class LinkNode
{
  public:
    QString data;
    LinkNode *next;
    LinkNode():next(NULL){}
    LinkNode(const QString &x,LinkNode *p = NULL):data(x),next(p){}
};


class Queue: public QWidget
{
  public:
       Queue(QWidget *parent = 0,LinkNode *fro = NULL,LinkNode *rea = NULL):QWidget(parent),front(fro),rear(rea)
       {

       }
       ~Queue();
       bool isEmpty(); //队列是否为空
       bool makeEmpty(); //队列清空
       void enqueue( const QString &x);//插入一个元素
       void frontEnqueue( const QString &x);//在队列头首部插入数据
       void dequeue(QString &x);   //弹出一个元素
       void getFront(QString &x);  //得到对头元素
   private:
       LinkNode*front; //指向头结点指针 front->next->data是对列头
       LinkNode *rear;  //指向队尾（最后添加的一个元素的指针）
       inline void handleUnderFlow(); //控制队列向下溢出
};
#endif // QUEUE_H
