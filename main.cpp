#include "ordered_cont.h"
#include "bidirectional_list.h"
#include "unidirectional_list.h"


int main(){
    std::cout << "Ordered container\n";
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

    std::cout << "container[3] = " << or_cont[3] << std::endl;
    std::cout << std::endl;


    std::cout << "Bidirectional List\n";
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

    std::cout << "container[3] = " << bi_cont[3] << std::endl;

    BidirectionalList<int> bi_cont2;
    bi_cont = std::move(bi_cont);

    for (auto it = bi_cont.begin(); it != bi_cont.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << std::endl;


    std::cout << "Unidirectional List\n";
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

    std::cout << "container[3] = " << un_cont[3] << std::endl;

    UnidirectionalList<int> un_cont2;
    un_cont2 = std::move(un_cont);

    for (auto it = un_cont2.begin(); it != un_cont2.end(); ++it) {
        std::cout << *it << " ";
    }


    std::cout << "\n\nBidirectional List";
    std::cout << std::endl;
    BidirectionalList<int> list1 = {10, 20, 30, 40, 50};
    std::cout << "list1 (original): " << list1.print() << std::endl;
    BidirectionalList<int> list2;
    std::cout << "list2 (original): " << list2.print() << std::endl;
    list2 = list1;
    std::cout << "list2 (after copy): " << list2.print() << std::endl;
    std::cout << "list1 (after copy): " << list1.print() << std::endl;
    
    BidirectionalList<int> list3;
    std::cout << "list3 (original): " << list3.print() << std::endl;
    list3 = std::move(list1);
    std::cout << "after move:" << std::endl;
    std::cout << "list1: " << list1.print() << std::endl;
    std::cout << "list3: " << list3.print() << std::endl;


    std::cout << "\nUnidirectional List";
    std::cout << std::endl;
    UnidirectionalList<int> list4 = {10, 20, 30, 40, 50};
    std::cout << "list1 (original): " << list4.print() << std::endl;
    UnidirectionalList<int> list5;
    std::cout << "list2 (original): " << list5.print() << std::endl;
    list5 = list4;
    std::cout << "list2 (after copy): " << list5.print() << std::endl;
    std::cout << "list1 (after copy): " << list4.print() << std::endl;
    
    UnidirectionalList<int> list6;
    std::cout << "list3 (original): " << list6.print() << std::endl;
    list6 = std::move(list4);
    std::cout << "after move:" << std::endl;
    std::cout << "list1: " << list4.print() << std::endl;
    std::cout << "list3: " << list6.print() << std::endl;
    return 0;
}