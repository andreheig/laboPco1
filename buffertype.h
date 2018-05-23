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
{
protected:
    // Container permettant de stoquer nos éléments
    T *elements;
    int writePointer, readPointer, nbElements, bufferSize; QSemaphore mutex, waitProd, waitConso;
    unsigned nbWaitingProd, nbWaitingConso;

public:
    BufferType(unsigned int size) {
        mutex.release();
        if ((elements = new T[size]) != 0) {
            writePointer = readPointer = nbElements = 0;
            nbWaitingProd = nbWaitingConso = 0; bufferSize = size;
            return;
        }
        // Exception
        throw new bad_alloc;
    }

    /**
     * @brief Destructor
     */
    virtual ~BufferType() {}

    /**
     * @brief put
     * Fonction permettant de stocker un élément T dans notre QList (store)
     * @param Objet de type T que l'on souhaite ajouter dans notre collection.
     */
    void put(T item){
        mutex.acquire();
        if (nbElements == bufferSize) {
            nbWaitingProd += 1;
            mutex.release();
            waitProd.acquire();
        }

        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;

        nbElements ++;
        if (nbWaitingConso > 0) {
            nbWaitingConso -= 1;
            waitConso.release();
        } else {
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
        if (nbElements == 0) {
            nbWaitingConso += 1; mutex.release(); waitConso.acquire();
        }
        item = elements[readPointer]; readPointer = (readPointer + 1) % bufferSize;
        nbElements --;
        if (nbWaitingProd > 0) {
            nbWaitingProd -= 1;
            waitProd.release(); }
        else {
            mutex.release();
        }
        return item;
    }
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
