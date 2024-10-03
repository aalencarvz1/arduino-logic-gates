#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <MemoryUsage.h>  // Inclui a biblioteca MemoryUsage
#include <Arduino.h>
#include "Utils.h"
#include "BaseSingleComponent.h"

template <typename T>
class DoubleLinkedList;

template <typename T>
struct Node {    
    Node<T>* next = nullptr;  // Ponteiro para o próximo nó
    Node<T>* prev = nullptr;  // Ponteiro para o nó anterior
    T* data = nullptr;        // Ponteiro para o objeto do tipo T
    Node() {
      //Serial.println(F("INIT Node<T>::Node"));   
      //Serial.println(F("END Node<T>::Node"));
    };
    ~Node(){
      //Serial.println(F("INIT Node<T>::~Node"));      
      if (next != nullptr) {
        next->prev = prev;
      }
      if (prev != nullptr) {
        prev->next = next;
      }
      if (data != nullptr) {
        delete data;  // Chama o destrutor do objeto armazenado
        data = nullptr;
      }
      next = nullptr;
      prev = nullptr;
      //Serial.println(F("END Node<T>::~Node"));
    }
};

template <typename T>
class DoubleLinkedList {
  protected:
    bool deleteData = true;
    int count = 0;
  public:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    const char* tName;
    DoubleLinkedList(const char* typeName) : 
      tName(typeName)
    {
      //Serial.println(F("INIT DoubleLinkedList<T>::DoubleLinkedList"));
      //Serial.println(F("END DoubleLinkedList<T>::DoubleLinkedList"));
    }

    void setDeleteData(const bool& pDeleteData) {deleteData = pDeleteData;};

    ~DoubleLinkedList() {
      //Serial.println(F("INIT DoubleLinkedList<T>::~DoubleLinkedList"));
      clear();  // Remove todos os nós e libera memória
      //Serial.println(F("END DoubleLinkedList<T>::~DoubleLinkedList"));
    }

    void add(const T* data) {
      //Serial.println(F("INIT DoubleLinkedList<T>::add"));
      //Serial.println(tName);
      //FREERAM_PRINT; 
      //Serial.println(F("antes"));
      Node<T>* newNode = new Node<T>();
      //Serial.println(F("depois"));
      //FREERAM_PRINT;
      newNode->data = data;      
      newNode->next = nullptr;
      newNode->prev = tail;

      if (newNode->prev != nullptr) {
          newNode->prev->next = newNode;
      }
      tail = newNode;
  
      if (head == nullptr) {
          head = newNode;
      }
      count++;
      //Serial.println(F("END DoubleLinkedList<T>::add"));
    }

    void remove(const T* data, const bool& pDeleteData = true) {
      //Serial.print(F("INIT DoubleLinkedList<T>::remove "));
      //Serial.print(tName);
      Node<T>* current = head;
      //Serial.println("ok1");
      while (current != nullptr) {        
          if (current->data == data) {
            //BaseSingleComponent* b = static_cast<BaseSingleComponent>(current->data);
            //ln("dddddddddddddddd encountred, removing...");
            if (current->prev == nullptr) {
                head = current->next;
            }
            if (current->next == nullptr) {
                tail = current->prev;
            }
            if (!pDeleteData || !deleteData) current->data = nullptr; //avoid data delete on node destructor
            delete current;        // Libera o nó
            if (current == tail) {
              tail = nullptr;
            } 
            if (current == head) {
              head = nullptr;
            }
            //Serial.println("removed");
            count--;
            break;
          }
          if (current == current->next) break; //avoid infint loops
          current = current->next;
      }
      //Serial.println(F("END DoubleLinkedList<T>::remove"));
    }

    void clear(const bool& pDeleteData = true) {
      //Serial.print(F("INIT DoubleLinkedList<T>::clear "));
      //Serial.print(tName);
      //Serial.println(":"+String(count));
      Node<T>* current = head;

      while (current != nullptr) {
          //Serial.println("deleting node...");
          Node<T>* nextNode = current->next;
          if (!pDeleteData || !deleteData) {
            //Serial.println("not delete data "+boolToString(pDeleteData) + ","+boolToString(deleteData));
            current->data = nullptr; //avoid data delete on node destructor
          }
          //Serial.println("before");
          delete current;        // Libera o nó
          //Serial.println("after");
          if (current == nextNode) break;
          current = nextNode;          
      }
      head = nullptr;
      tail = nullptr;
      count = 0;
      //Serial.println(F("END DoubleLinkedList<T>::clear"));
    }   

    const int& getCount() const {return count;};
};

#endif
