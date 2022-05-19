#include "List.h"
#include <iostream>

int main() {
    List<int> list;
    list.insertBack(3);
    list.insertBack(3);
    list.insertBack(3);
    list.insertBack(3);

    List<int> list2;
    list2.insertBack(3);
    list2.insertBack(3);
    list2.insertBack(3);

    list.print();
    std::cout << "\n" << std::endl;
    list2.print();
    std::cout << "\n" << std::endl;

    list.mergeWith(list2);

    list.print();
    std::cout << "\n" << std::endl;
    list2.print();
    std::cout << "\n" << std::endl;
  return 0;
}
