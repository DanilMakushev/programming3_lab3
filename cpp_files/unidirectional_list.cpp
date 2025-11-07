#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <initializer_list>


template<typename T>
struct Un_Node{
    std::shared_ptr<Un_Node<T>> next;   // указатель на следующий элемент Node
    T data; // пользовательские данные (хранимый объект)
    Un_Node(const T& value) : next(nullptr), data(value) {}
    
};


template<typename T>
class UnidirectionalList{
    protected:
        std::shared_ptr<Un_Node<T>> firstNode; // первый узел списка
        std::shared_ptr<Un_Node<T>> lastNode;  // последний узел списка
        size_t size;  // текущее количество элементов

    public:
        // конструктор по умолчанию
        UnidirectionalList() : firstNode(nullptr), lastNode(nullptr), size(0) {}

        // Конструктор со списком инициализации
        UnidirectionalList(std::initializer_list<T> init) : firstNode(nullptr), lastNode(nullptr), size(0) {
            for (const auto& value : init) {
                push_back(value);
            }
        }

        // деструктор
        ~UnidirectionalList() = default;

        // добавление нового элемента в конец контейнера
        void push_back(const T& value){
            auto newNode = std::make_shared<Un_Node<T>>(value);      
            if (firstNode == nullptr) {
                firstNode = newNode;
                lastNode = newNode;
            } else {
                lastNode->next = newNode;
                lastNode = newNode;
            }
            size++;
        }

        // добавление нового элемента в начало контейнера
        void push_begin(const T& value){
            auto newNode = std::make_shared<Un_Node<T>>(value);
            
            if (firstNode == nullptr) {
                firstNode = newNode;
                lastNode = newNode;
            } else {
                newNode->next = firstNode;
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
            auto newNode = std::make_shared<Un_Node<T>>(value);
            auto current = firstNode;
            
            for (int i = 0; i < index-1; ++i) {
                current = current->next;
            }
            
            newNode->next = current->next;
            current->next = newNode; 

            size++;
        }

        // удаление элемента по индексу
        void erase(const int& index){
            if (index < 0 || index >= size) {
                throw std::out_of_range("Index out of range");
            }
            if (index == 0) {
                auto node = firstNode;
                firstNode = firstNode->next;
                node.reset();
                if (size == 1) {
                    lastNode = nullptr;
                }
                --size;
                return;
            }
            auto current = firstNode;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            auto node_to_delete = current->next;
            current->next = node_to_delete->next;

            if (index == size - 1) {
                lastNode = current;
            }
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
        UnidirectionalList& operator= (const UnidirectionalList& other) {
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
            firstNode.reset();
            lastNode.reset();
        size = 0;
        }

        // перемещающий оператор
        UnidirectionalList& operator=(UnidirectionalList&& other) {
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
                std::shared_ptr<Un_Node<T>> current;
                
            public:
                // конструктор
                Iterator(std::shared_ptr<Un_Node<T>> node = nullptr) : current(node) {}
                
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


int main(){

    UnidirectionalList<int> cont = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << cont.print() << std::endl << cont.container_size() << std::endl;

    cont.erase(2);
    cont.erase(3);
    cont.erase(4);
    std::cout << cont.print() << std::endl;

    cont.push_begin(10);
    std::cout << cont.print() << std::endl;

    cont.insert(4, 20);
    std::cout << cont.print() << std::endl;

    cont.push_back(30);
    std::cout << cont.print() << std::endl;

    std::cout << cont[3] << std::endl;

    UnidirectionalList<int> cont2;
    cont2 = std::move(cont);

    for (auto it = cont2.begin(); it != cont2.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}