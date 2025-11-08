#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H


#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <initializer_list>


template<typename T>
struct Bi_Node{
    std::shared_ptr<Bi_Node<T>> next;   // указатель на следующий элемент Node
    std::shared_ptr<Bi_Node<T>> prev;   // указатель на предыдущий элемент Node
    T data; // пользовательские данные (хранимый объект)
    Bi_Node(const T& value) : next(nullptr), prev(nullptr), data(value) {}
    
};


template<typename T>
class BidirectionalList{
    protected:
        std::shared_ptr<Bi_Node<T>> firstNode; // первый узел списка
        std::shared_ptr<Bi_Node<T>> lastNode;  // последний узел списка
        size_t size;  // текущее количество элементов

    public:
        // конструктор по умолчанию
        BidirectionalList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

        // Конструктор со списком инициализации
        BidirectionalList(std::initializer_list<T> init) : firstNode(nullptr), lastNode(nullptr), size(0) {
            for (const auto& value : init) {
                push_back(value);
            }
        }

        // деструктор
        ~BidirectionalList() = default;

        // добавление нового элемента в конец контейнера
        void push_back(const T& value){
            auto newNode = std::make_shared<Bi_Node<T>>(value);
            
            if (lastNode == nullptr) {
                firstNode = lastNode = newNode;
            } else {
                lastNode->next = newNode;
                newNode->prev = lastNode;
                lastNode = newNode;
            }
            size++;
        }

        // добавление нового элемента в начало контейнера
        void push_begin(const T& value){
            auto newNode = std::make_shared<Bi_Node<T>>(value);
            
            if (firstNode == nullptr) {
                firstNode = lastNode = newNode;
            } else {
                newNode->next = firstNode;
                firstNode->prev = newNode;
                firstNode = newNode;
            }
            size++;
        };

        // добавление нового элемента на конкретное место контейнера
        void insert(const int& index, const T& value) {
            if (index < 0 || index > size) {
                throw std::out_of_range("Index out of range");
            }
            if (index == 0) {
                push_begin(value);
                return;
            }
            if (index == size) {
                push_back(value);
                return;
            }
            auto newNode = std::make_shared<Bi_Node<T>>(value);
            auto current = firstNode;
            
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            
            auto prevNode = current->prev;
            newNode->prev = prevNode;
            newNode->next = current;
            
            if (prevNode) {
                prevNode->next = newNode;
            }
            current->prev = newNode;
            size++;
        }

        // удаление элемента по индексу
        void erase(const int& index){
            if (index < 0 || index >= size) {
                throw std::out_of_range("Index out of range");
            }
            if (size == 1) {
                firstNode.reset();
                lastNode.reset();
                size = 0;
                return;
            }
            if (index == 0) {
                firstNode = firstNode->next;
                firstNode->prev.reset();
                --size;
                return;
            }
            if (index == size-1) {
                lastNode = lastNode->prev;
                lastNode->next.reset();
                --size;
                return;
            }

            auto current = firstNode;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            --size;
        }

        // метод, возвращающий строку для вывода 
        std::string print() {
            std::ostringstream str;
            str << "[";
            
            auto current = firstNode;
            int count {};
            
            while (current != nullptr) {
                str << current->data;
                if (current->next != nullptr) {
                    str << ", ";
                }
                current = current->next;
                count++;
            }
            
            str << "]";
            return str.str();
        }

        // оператор  получения доступа по индексу
        T& operator[](const int& index) {
            auto current = firstNode;
            for (int i{}; i < index; ++i){
                current = current->next;
            }
            return current->data;
        }

        // оператор присваивания
        BidirectionalList& operator= (const BidirectionalList& other) {
            clear();
            auto current = other.firstNode;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
            return *this;
        }

        // удаляем список
        void clear() {
            auto current = firstNode;
            while (current != nullptr) {
                auto nextNode = current->next;
                current->next.reset();
                current->prev.reset();
                current = nextNode;
            }
            firstNode.reset();
            lastNode.reset();
            size = 0;
        }

        // перемещающий оператор
        BidirectionalList& operator=(BidirectionalList&& other) {
            if (this != &other) {
                clear();
                
                firstNode = std::move(other.firstNode);
                lastNode = std::move(other.lastNode);
                size = other.size;
                
                other.size = 0;
                other.firstNode = nullptr;
                other.lastNode = nullptr;
            }
            return *this;
            }

        int container_size(){
            return size;
        }

        class Iterator {
            private:
                std::shared_ptr<Bi_Node<T>> current;
                
            public:
                // конструктор
                Iterator(std::shared_ptr<Bi_Node<T>> node = nullptr) : current(node) {}
                
                // оператор разыменования - получаем данные узла
                T& operator*() {
                    return current->data;
                }
                
                // метод get()
                T& get() {
                    return operator*();
                }
                
                // оператор -> для доступа к членам объекта
                T* operator->() {
                    return &current->data;
                }
                
                // префиксный инкремент (++it)
                Iterator& operator++() {
                    if (current) {
                        current = current->next;
                    }
                    return *this;
                }
                
                // постфиксный инкремент (it++)
                Iterator operator++(int) {
                    Iterator temp = *this;
                    ++(*this);
                    return temp;
                }
                
                // префиксный декремент (--it)
                Iterator& operator--() {
                    if (current) {
                        current = current->prev;
                    }
                    return *this;
                }
                
                // постфиксный декремент (it--)
                Iterator operator--(int) {
                    Iterator temp = *this;
                    --(*this);
                    return temp;
                }
                
                // Операторы сравнения
                bool operator==(const Iterator& other) const {
                    return current == other.current;
                }
                
                bool operator!=(const Iterator& other) const {
                    return !(*this == other);
                }
            };
            
            // итератор на первый элемент
            Iterator begin() {
                return Iterator(firstNode);  
            }
            
            // итератор за последним элементом
            Iterator end() {
                return Iterator(nullptr);    
            }
};

#endif