#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <string.h>

template<class T> 
class Vector{
protected:
    T* array = nullptr;
    int max_size = 1;
    int real_size = 0;
    const int k = 2;

    void copy(T* lhs, T* rhs, int cnt){
        for(int i = 0; i < cnt; ++i){
            lhs[i] = rhs[i];
        }
    }

    void resize(int new_size){
        T* copy_array = new T[max_size];
        copy(copy_array, array, real_size);

        array = new T[new_size];
        copy(array, copy_array, real_size);

        delete []copy_array;
        max_size = new_size;
    }
public:
    Vector(){
        array = new T[max_size];
    }

    ~Vector(){
        if(array != nullptr){
            delete []array;
        }
    }

    Vector(T el) {
        array = new T[max_size];
        add_element(el);
    };
    
    Vector(Vector &v){ //конструктор копирования
        while(v.real_size >= max_size){
            resize(max_size * k);
        }
        real_size = v.real_size;
        copy(array, v.array, real_size);
    }

    void add_element(T new_el){    
        if(real_size + 1 >= max_size){
            resize(max_size * k);
        }
        real_size++;

        array[real_size - 1] = new_el;
    }

    void delete_element(int ind){
        for(int i = ind; i < real_size - 1; ++i){
            array[i] = array[i + 1];
        }
        real_size--;
    }

    void reverse() {
        Vector<T> copy = *this;
        for(int i = 0; i < real_size; ++i) {
            array[i] = copy[real_size - i - 1];
        }
    }

    int find_element(T el){
        for(int i = 0; i < real_size; ++i) {
            if(array[i] == el) return i;
        }
        return -1;
    }

    void clear(){
        real_size = 0;
    }
    
    int size(){
      return real_size;
    }

    T& operator[](int ind){
        return array[ind];
    }
    
    void sort(int l, int r) {
        if(l >= r) return;
        
        int mid = (l + r) / 2;
        T partition = array[mid];

        int partition_pos = l;
        for(int i = l; i <= r; ++i) {
            if(array[i] < partition) {
                partition_pos++;
            }
        }

        std::swap(array[mid], array[partition_pos]);

        int right = r;
        for(int left = l; left < partition_pos; ++left) {
            if(array[left] < partition) continue;

            while(true) {
                if(array[right] < partition) break;
                right--;
            }

            std::swap(array[left], array[right]);
        }

        sort(partition_pos + 1, r);
        sort(l, partition_pos - 1);
    }
    
    Vector& operator=(const Vector& v){ //оператор присваивания
        delete []array;
        real_size = v.real_size;
        max_size = v.max_size;

        array = new T[max_size];

        for(int i = 0; i < real_size; ++i){
            array[i] = v.array[i];
        }

        return *this;
    }

    Vector<char>& operator=(const char* s){ 
        for(int i = 0; i < strlen(s); ++i) {
            add_element(s[i]);
        }

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, Vector &v) {
        for(int i = 0; i < v.real_size; ++i) {
            out << v.array[i] << " ";
        }

        return out;
    }
};


#endif //MYVECTOR_H