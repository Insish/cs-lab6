#include <iostream>
#include <set>
using namespace std;

class MySet {
private:
    set<int> data;

public:
    MySet() {}

    MySet(initializer_list<int> init_list) : data(init_list) {}

    MySet(const MySet& other) : data(other.data) {}

    void add(int element) {
        data.insert(element);
    }

    void remove(int element) {
        data.erase(element);
    }

    void print() const {
        cout << "{ ";
        for (const auto& element : data) {
            cout << element << " ";
        }
        cout << "}" << endl;
    }

    bool operator==(const MySet& other) const {
        return data == other.data;
    }

    MySet operator+(const MySet& other) const {
        MySet result = *this;
        for (const auto& element : other.data) {
            result.add(element);
        }
        return result;
    }
};

int main() {
    MySet mySet1 = { 1, 2, 3, 4, 5 };
    MySet mySet2 = { 3, 4, 5, 6, 7 };

    mySet1.print();
    mySet2.print();

    mySet1.add(6);
    mySet1.print();

    mySet1.remove(3);
    mySet1.print();


    if (mySet1 == mySet2) {
        cout << "Sets are equal" << endl;
    }
    else {
        cout << "Sets are not equal" << endl;
    }

    MySet unionSet = mySet1 + mySet2;
    unionSet.print();

    return 0;
}
