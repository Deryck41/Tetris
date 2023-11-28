#include <iostream>
#include <vector>

class MyClass {
private:
    int data;

public:
    MyClass(int val) : data(val) {}

    // Метод-сеттер для изменения параметра data
    void setData(int val) {
        data = val;
    }

    // Метод-геттер для получения значения параметра data
    int getData() const {
        return data;
    }
};

int main() {
    std::vector<MyClass> myVector;
    
    // Добавляем объекты в вектор
    myVector.push_back(MyClass(10));
    myVector.push_back(MyClass(20));
    myVector.push_back(MyClass(30));
    
    // Изменяем параметр объекта с использованием метода-сеттера
    int index_to_modify = 1; // Индекс объекта, который нужно изменить
    int new_value = 25; // Новое значение для параметра data
    
    if (index_to_modify >= 0 && index_to_modify < myVector.size()) {
        myVector[index_to_modify].setData(new_value);
        std::cout << "Значение параметра объекта с индексом " << index_to_modify << " изменено на " << new_value << std::endl;
    } else {
        std::cout << "Недопустимый индекс." << std::endl;
    }
    
    // Выводим значения параметров объектов в векторе
    for (const MyClass& obj : myVector) {
        std::cout << "Значение параметра data: " << obj.getData() << std::endl;
    }
    
    return 0;
}
