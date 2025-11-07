#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <initializer_list>


template<typename T>
class OrderedContainer{
    protected:
        std::unique_ptr <T[]> data; // указатель на динамический массив
        size_t size;      // текущее количество элементов
        size_t capacity;  // текущая вместимость

        // увеличение вместимости контейнера
        void resize(size_t new_capacity){
            std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
        
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            
            data = std::move(new_data);
            capacity = new_capacity;
        }

    public:
        // Конструктор со списком инициализации
         OrderedContainer(std::initializer_list<T> init_list) : size(init_list.size()), capacity(init_list.size()) {
            if (size > 0) {
                data = std::make_unique<T[]>(capacity*2);
                size_t i = 0;
                for (const auto& item : init_list) {
                    data[i++] = item;
                }
            }
        }

        OrderedContainer() : data(nullptr), size(0), capacity(2) {} // конструктор по умолчанию

        // деструктор
        ~OrderedContainer() = default;

        // добавление нового элемента в конец контейнера
        void push_back(const T& value){
            if(size+1 > capacity){
                size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
                resize(new_capacity);
            }
            data[size] = value;
            size++;
        }

        // добавление нового элемента в начало контейнера
        void push_begin(const T& value){
            std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity+1);
            new_data[0] = value;

            for (int i = 1; i < size+1; ++i){
                new_data[i] = data[i-1];
            }

            data = std::move(new_data);
            size++;
            capacity++;
        }

        // добавление нового элемента на конкретное место контейнера
        void insert(const int& index, const int& value){
            std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity+1);
            for (int i{}; i < index; ++i){
                new_data[i] = data[i];
            }

            new_data[index] = value;

            for (int i = index; i < size; ++i){
                new_data[i+1] = data[i];
            }

            data = std::move(new_data);
            size++;
            capacity++;
        }

        // метод, возвращающий строку для вывода 
        std::string print(){
            std::ostringstream str;

            str << "[";
            for (int i{}; i < size; ++i){
                str << data[i];
                if (i < size - 1) {
                    str << ", ";
                }
            }
            str << "]";
            return str.str();
        }

        int container_size(){
            return size;
        }

        // оператор присваивания
        OrderedContainer& operator=(const OrderedContainer& other) {
            std::unique_ptr<T[]> new_data = std::make_unique<T[]>(other.capacity);
        
            for (size_t i = 0; i < other.size; ++i) {
                new_data[i] = other.data[i];
            }
            
            data = std::move(new_data);
            size = other.size;
            capacity = other.capacity;

            return *this;
        }

        // оператор  получения доступа по индексу
        T& operator[](const int& index) {
            return data[index];
        }

        // удаление элемента по индексу
        void erase(const int& index){
            std::unique_ptr<T[]> new_data(new T[capacity]);

            for (int i{}; i <= index; ++i){
                new_data[i] = data[i];
            }
            for (int i = index+1; i < size; ++i){
                new_data[i-1] = data[i];
            }

            data = std::move(new_data);
            --size;
        }
};

int main(){

    OrderedContainer<int> cont = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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

    return 0;
}