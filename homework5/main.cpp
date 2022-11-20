#include "set.hpp"
#include "rb_tree.hpp"

void test(RBTree<int> s) {
    s.remove(2);

    s.print();
}

int main(void)
{
    // RBTree<int> s;

    // // s.insert(10);
    // // s.insert(1);
    // // s.print();

    // // s.remove(3);
    // // s.remove(10);
    // // s.remove(5);
    // // s.insert(9);
    // // s.insert(9);
    // // s.print();

    // // test(s);    

    // RBTree<int> s1 = s;
    
    // // s1.print();

    // RBTree<int> s2{1, 0, -1, 3, 2, 5};
    // s2.print();
    // // RBTree<int>::iterator be = s.begin(), en = s.end();
    // // ++be;
    // // ++be;
    // // std::cout << *be << " " << *en << std::endl;
    
    // std::cout << "Hello!" << std::endl;

    // for (auto it = s2.begin(); it != s2.end(); ++it) {
    //         std::cout << *it << std::endl;
    // }

    // std::cout << "Hello!" << std::endl;

    // for (auto it = s1.begin(); it != s1.end(); ++it) {
    //         std::cout << *it << std::endl;
    // }

    set<int> se;

    se.insert(1);
    se.insert(1);
    se.erase(1);
    se.erase(1);

    std::cout << se.size() << std::endl;

    return 0;
}
