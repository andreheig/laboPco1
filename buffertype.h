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
public:
    BufferType(): waitEmpty(10), waitFull(0){}

    /**
     * @brief put
     * Fonction permettant de ranger un étément T dans notre QList
     * @param item
     * Objet que l'on souhaite mettre dans notre collection.
     */
    void put(T item){
        //waitEmpty.acquire();
        //store.push_back(item);
        store.push_front(item);
        waitFull.release();
    }

    /**
     * @brief get
     * Fonction permettant de récupérer le premier élément arrivé
     * @return
     * Retourne le dernier élément T (celui qui attend depuis longtemps)
     */
    T get(){
        waitFull.acquire();
            T tmp = store.back();
            store.pop_back();
            //waitEmpty.release();
            return tmp;
    }

private:
    // Container permettant de stoquer nos éléments
    QList<T> store;

    // Sémaphore permettant de savoir que la liste est vide
    QSemaphore waitEmpty;

    // Sémaphore afin de savoir si notre container ontient des objets
    QSemaphore waitFull;
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
