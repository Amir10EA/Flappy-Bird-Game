//Amir Eihab El Abidou, amel6385

// Labb2, IntVector.cpp – definitioner av icke-triviala medlemsfunktioner

#include <cstring>
#include <iostream>

#include <stdexcept>
#include "IntVector.h"

using namespace std;


    IntVector::IntVector(const std::initializer_list<int>& intlist):_size(static_cast<int>(intlist.size()) )
    {
        data = new int[_size];
        int i = 0;
        for (int x : intlist){
            data[i++] = x;
        }
    }

    
    IntVector::IntVector() : _size(0), data(nullptr){}

   
    IntVector::IntVector(const int *intlist) {
        int count = 0;
        while(intlist[count] != -1)
        {
            count++;
        }
        _size = count;

        data = new int[_size];
        for (int i = 0; i < _size; i++){
            data[i] = intlist[i];
        }
    }

   
    IntVector::IntVector(const IntVector &other){
        _size = other._size;
        data = new int[_size];
        for (int i = 0; i < _size; i++){
        data[i] = other.data[i];
        }
    }

   
     IntVector::IntVector(IntVector &&other){
        _size = other._size;
        data = other.data;
        other.data = nullptr;
        other._size = 0;
     } 
    
    IntVector::~IntVector(){
        delete[] data;
    }

     const IntVector& IntVector::operator=(const IntVector &other) {
    if (this != &other) { 
        delete[] data; 
        _size = other._size;
        data = new int[_size]; 
        for (int i = 0; i < _size; i++) { 
            data[i] = other.data[i];
        }
    }
    return *this; 
}
    
    

   
    int & IntVector::operator[](int pos) const{
    if (pos >= _size || pos < 0){
        throw out_of_range("Index out of bounds");    
    }
    return data[pos];
    }

    int IntVector::size() const{
    return _size;
}

    void IntVector::push_back(const int &value) {
        int *temp = new int[_size + 1];
        for (int i = 0; i < _size; i++){
            temp[i] = data[i];
        }
        temp[_size] = value;
        delete[] data;
        data = temp;
        _size++;
    }

    

    std::ostream& operator<<(std::ostream& os, const IntVector& vector){
        for (int i = 0; i < vector._size; i++){
            os << vector.data[i] << " ";
        }
        return os;
    }

