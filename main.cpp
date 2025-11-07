#include "ordered_cont.h"
#include "bidirectional_list.h"
#include "unidirectional_list.h"


int main(){
    OrderedContainer<int> or_cont = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << or_cont.print() << std::endl << or_cont.container_size() << std::endl;

    or_cont.erase(2);
    or_cont.erase(3);
    or_cont.erase(4);
    std::cout << or_cont.print() << std::endl;
    
    or_cont.push_begin(10);
    std::cout << or_cont.print() << std::endl;

    or_cont.insert(4, 20);
    std::cout << or_cont.print() << std::endl;

    or_cont.push_back(30);
    std::cout << or_cont.print() << std::endl;

    std::cout << or_cont[3] << std::endl;
    std::cout << std::endl;


    BidirectionalList<int> bi_cont = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << bi_cont.print() << std::endl << bi_cont.container_size() << std::endl;

    bi_cont.erase(2);
    bi_cont.erase(3);
    bi_cont.erase(4);
    std::cout << bi_cont.print() << std::endl;

    bi_cont.push_begin(10);
    std::cout << bi_cont.print() << std::endl;

    bi_cont.insert(4, 20);
    std::cout << bi_cont.print() << std::endl;

    bi_cont.push_back(30);
    std::cout << bi_cont.print() << std::endl;

    std::cout << bi_cont[3] << std::endl;

    BidirectionalList<int> bi_cont2;
    bi_cont = std::move(bi_cont);

    for (auto it = bi_cont.begin(); it != bi_cont.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << std::endl;


    UnidirectionalList<int> un_cont = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << un_cont.print() << std::endl << un_cont.container_size() << std::endl;

    un_cont.erase(2);
    un_cont.erase(3);
    un_cont.erase(4);
    std::cout << un_cont.print() << std::endl;

    un_cont.push_begin(10);
    std::cout << un_cont.print() << std::endl;

    un_cont.insert(4, 20);
    std::cout << un_cont.print() << std::endl;

    un_cont.push_back(30);
    std::cout << un_cont.print() << std::endl;

    std::cout << un_cont[3] << std::endl;

    UnidirectionalList<int> un_cont2;
    un_cont2 = std::move(un_cont);

    for (auto it = un_cont2.begin(); it != un_cont2.end(); ++it) {
        std::cout << *it << " ";
    }


    return 0;
}