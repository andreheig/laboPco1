#ifndef BUFFERTYPE_H
#define BUFFERTYPE_H
#include "abstractbuffer.h"
#include <iostream>
#include <QList>
#include <QSemaphore>

using namespace std;

template<typename T>
class BufferType : public AbstractBuffer<T>
{
public:

    BufferType(): waitEmpty(1), waitFull(0){
        //QList<T>store = new QList<T>();
    }
    void put(T item){
        waitEmpty.acquire();
        store.push_back(item);
        waitFull.release();
    }

    T get(){

        waitFull.acquire();
            T tmp = store.back();
            store.pop_back();
            waitEmpty.release();
            return tmp;

    }

private:
    QList<T> store;
    QSemaphore waitEmpty;
    QSemaphore waitFull;

};

#endif // BUFFERTYPE_H
