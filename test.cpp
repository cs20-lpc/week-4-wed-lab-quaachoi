#include "DoublyList.hpp"

using namespace std;

int main()
{
    DoublyList<int> dlist;
    dlist.append(4);
    dlist.append(30);
    dlist.append(23);
    dlist.append(24);
    dlist.append(25);
    dlist.append(26);

    cout << dlist.getElement(0) << endl;
    cout << dlist.getElement(1) << endl;
    cout << dlist.getElement(2) << endl;
    cout << dlist.getElement(3) << endl;
    cout << dlist.getElement(4) << endl;
    cout << dlist.getElement(5) << endl;
    cout << dlist;

    return 0;
}