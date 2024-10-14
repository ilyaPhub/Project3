#include <iostream>

using namespace std;

class MyString {
private:
    char* str;
    size_t length;

public:
    MyString() {
        str = new char[1];
        str[0] = '\0';
        length = 0;
    }

    ~MyString() {
        delete[] str;
    }

    char& operator[](size_t index) {
        if (index >= length) {
            throw out_of_range("Index out of bounds");
        }
        return str[index];
    }

    void init() {
        char input[100];
        cout << "Enter a string: ";
        cin.getline(input, 100);
        length = strlen(input);
        str = new char[length + 1];
        strcpy(str, input);
    }

    MyString operator+(char c) {
        MyString newStr;
        newStr.length = length + 1;
        newStr.str = new char[newStr.length + 1];
        strcpy(newStr.str, str);
        newStr.str[length] = c;
        newStr.str[newStr.length] = '\0';
        return newStr;
    }

    friend MyString operator+(char c, MyString& obj) {
        MyString newStr;
        newStr.length = obj.length + 1;
        newStr.str = new char[newStr.length + 1];
        newStr.str[0] = c;
        strcpy(newStr.str + 1, obj.str);
        return newStr;
    }

    MyString operator+(int n) {
        if (n != 10) {
            throw invalid_argument("Only 10 is supported");
        }
        MyString newStr;
        newStr.length = length + 10;
        newStr.str = new char[newStr.length + 1];
        strcpy(newStr.str, str);
        for (int i = 0; i < 10; ++i) {
            newStr.str[length + i] = '*';
        }
        newStr.str[newStr.length] = '\0';
        return newStr;
    }

    void addCharToEnd(char c) {
        MyString newStr = *this + c;
        *this = newStr; 
    }

    void addCharToStart(char c) {
        MyString newStr = c + *this;
        *this = newStr;
    }

    MyString& operator++() {
        addCharToEnd('!'); 
        return *this;
    }

    void print() const {
        cout << str << endl;
    }
};

int main() {
    MyString myStr;
    myStr.init();

    myStr.print();

    myStr = myStr + 'A'; 
    myStr.print();

    myStr = 'B' + myStr;
    myStr.print();

    myStr = myStr + 10; 
    myStr.print();

    myStr.addCharToEnd('C');
    myStr.print();

    myStr.addCharToStart('D'); 

    ++myStr;
    myStr.print();

    return 0;
}
