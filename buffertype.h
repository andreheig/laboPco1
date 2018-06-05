#ifndef BUFFERTYPE_H
#define BUFFERTYPE_H
#include "abstractbuffer.h"
#include <iostream>
#include <QList>
#include <QSemaphore>
#include <QMutex>
#include <QWaitCondition>

using namespace std;

template<typename T>
/**
 * @brief The BufferType class
 * Buffer dérivant de notre classe abstraite afin de pouvoir
 * y mettre des éléments de type quelconque.
 */
class BufferType : public AbstractBuffer<T>
// Version Sémaphore tampon simple
/*
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
     * @brief put
     * Fonction permettant de stocker un élément T dans notre QList
     * @param Objet de type Tz que l'on souhaite mettre dans notre collection.
     *//*
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
     *//*
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
};*/

// Version sémaphore tampon multiple non fonctionnelle
/*
{
public:
    BufferType(unsigned int size): mutex(1), waitNotFull(size), waitNotEmpty(0){
        elements = new T[size];
        if(elements != 0){
            writePointer = readPointer = currentSize = 0;
            bufferSize = size;
            return;
        }
        throw new bad_alloc;
    }

    ~BufferType(){}

    void put(T item){

        mutex.acquire();
        waitNotFull.acquire();
        elements[writePointer] = item;
        currentSize++;
        writePointer = (writePointer + 1) % bufferSize;
        waitNotEmpty.release();
        mutex.release();

    }

    T get(){
            T item;
            mutex.acquire();
            waitNotEmpty.acquire();
            item = elements[readPointer];
            currentSize--;
            readPointer = (readPointer + 1) % bufferSize;
            waitNotFull.release();
            mutex.release();
            return item;
    }

    bool tryPut(T item){
        if(currentSize == bufferSize){
            return false;
        }
        else{
            put(item);
            return true;
        }
    }

private:
    T* elements;
    int writePointer;
    int readPointer;
    int bufferSize;
    int currentSize;

    QSemaphore waitNotEmpty;
    QSemaphore waitNotFull;
    QSemaphore mutex;
};*/

{
public:
    BufferType(unsigned int size): bufferSize(size) {
        elements = new T[size];
        nbElements = readPointer = writePointer = 0;
    }

    ~BufferType(){}

    void put(T item) {
       mutex.lock();
        while(nbElements == bufferSize){
            isFree.wait(&mutex);        //si le tampon est plein on attend et libère le mutex
        }
        nbElements = nbElements + 1; //change la condition
        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;
        isFull.wakeOne();

       mutex.unlock();
    }

    T get(void) {
        T item; //element à retourner
        mutex.lock();

        if(nbElements == 0) isFull.wait(&mutex); //si le tampon est vide on attend et on libère le mutex

        item = elements[readPointer];
        nbElements = nbElements - 1; //change la condition
        readPointer = (readPointer + 1) % bufferSize;

        mutex.unlock();   //libère le verrou avant de faire un wakeOne
        isFree.wakeOne(); //on libère une place dans le tampon

        return item;
    }

    bool tryPut(T item){
        if(nbElements == bufferSize){
            return false;
        }
        else{
            put(item);
            return true;
        }
    }

private:
    T* elements;
    unsigned int bufferSize;
    unsigned int readPointer;
    unsigned int writePointer;
    unsigned int nbElements;
    QWaitCondition isFree, isFull;
    QMutex mutex;
};


#endif // BUFFERTYPE_H
