#ifndef BUFFERTYPE_H
#define BUFFERTYPE_H
#include "abstractbuffer.h"
#include <iostream>
#include <QList>
#include <QSemaphore>

using namespace std;

template<typename T>
/**
 * @brief The BufferType class
 * Buffer dérivant de notre classe abstraite afin de pouvoir
 * y mettre des éléments de type quelconque.
 */
class BufferType : public AbstractBuffer<T>
// Version Sémaphore tampon simple

{

protected:
    T element;
    QSemaphore mutex, waitEmpty, waitFull; enum {Full, Empty} state;
    unsigned nbWaitingProd, nbWaitingCons;

public:
    BufferType(): mutex(1), state(Empty),
    nbWaitingProd(0),
    nbWaitingCons(0) {}

    /**
     * @brief Destructor
     */
    ~BufferType() {}

    /**
     * @brief put
     * Fonction permettant de stocker un élément T dans notre QList
     * @param Objet de type Tz que l'on souhaite mettre dans notre collection.
     */
    void put(T item){
        mutex.acquire();
        if (state == Full) {
            nbWaitingProd += 1;
            mutex.release();
            waitEmpty.acquire();
        }

        store.push_front(item);

        if (nbWaitingCons > 0) {
            nbWaitingCons -= 1;
            waitFull.release();
        } else {
            state = Full;
            mutex.release();
        }
    }

    /**
     * @brief get
     * Fonction permettant de récupérer le premier élément arrivé de type T
     * @return le dernier élément T (celui qui attend depuis longtemps)
     */
    T get(){

        T item;
        mutex.acquire();
        if (state == Empty) {
            nbWaitingCons += 1;
            mutex.release();
            waitFull.acquire();
        }

        item = store.back();
        store.pop_back();

        if (nbWaitingProd > 0) {
            nbWaitingProd -= 1;
            waitEmpty.release(); }
        else {
            state = Empty;
            mutex.release();
        }
        return item;
    }

private:
    // Container permettant de stoquer nos éléments
    QList<T> store;
};

// Version sémaphore tampon multiple non fonctionnelle
/*
{
public:
    BufferType(unsigned int size): mutex(1), waitNotFull(size){
        elements = new T[bufferSize];
        if(elements != 0){
            writePointer = readPointer = 0;
            bufferSize = size;
            return;
        }
        throw new bad_alloc;
    }

    ~BufferType(){}

    void put(T item){

        waitNotFull.acquire();
        mutex.acquire();
        cout << "put: index " << writePointer << endl;
        cout << "elements " << elements << endl;
        elements[writePointer] = item;
        cout << "fin insert" << endl;
        writePointer = (writePointer + 1) % bufferSize;
        waitNotEmpty.release();
        mutex.release();

    }

    T get(){
            T item;
            waitNotEmpty.acquire();
            mutex.acquire();
            item = elements[readPointer];
            readPointer = (readPointer + 1) % bufferSize;
            waitNotFull.release();
            mutex.release();
            return item;
    }

private:
    T* elements;
    int writePointer;
    int readPointer;
    int bufferSize;
    QSemaphore waitNotEmpty;
    QSemaphore waitNotFull;
    QSemaphore mutex;
};*/


#endif // BUFFERTYPE_H
