#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
    private:
        T* array;
        int max;
        int n;
        static const int MINSIZE = 2;
        void resize(int new_size) {
            if (new_size < MINSIZE) {
                new_size = MINSIZE;
            }
            
            T* newArray = new T[new_size];
            for (int i = 0; i < n; i++) {
                newArray[i] = array[i];
            }

            delete[] array;
            array = newArray;
            max = new_size;
        }
    public: 
        ListArray() : array(new T[MINSIZE]), max(MINSIZE), n(0){}
    
        ~ListArray() {
            delete[] array;
        }

        T operator[](int pos) {
            if ((n-1) < pos || pos < 0)
                throw std::out_of_range("Fuera de rango");
            return array[pos];
        }

        friend std::ostream& operator<<(std::ostream& out, const ListArray<T>& list) {
            out << "[";

            for (int i = 0; i < list.n; i++) {
                out << list.array[i];
                if (i+1 < list.n) 
                    out << ", ";
            }    
            out << "]";
            return out;
        }

        void insert(int pos, T e) override{
            if (pos < 0 || pos > n)
                throw std::out_of_range("Fuera de rango");

            if (n == max)
                resize(max + 1);

            for (int i = n; i > pos; i--)
                array[i] = array[i - 1];

            array[pos] = e;
            n++;
        }

        void append(T e) override {
            insert(n, e);
        }

        void prepend(T e) override {
            insert(0, e);
        }

        T remove(int pos) override { //PREGUNTAR resize
            if (pos < 0 || pos >= n)
                throw std::out_of_range("Fuera de rango");

            T borrado = array[pos];

            for (int i = pos; i < (n - 1); i++) {
                array[i] = array[i + 1];
            }

            n--;
            return borrado;
        }

        T get(int pos) override {
            if (pos < 0 || pos >= n)
                throw std::out_of_range("Fuera de rango");

            return array[pos];
        }

        int search(T e) override {
            for (int i = 0; i < n; i++) {
                if (array[i] == e) return i;
            }
            
            return -1; //Fuera de rango
        }

        bool empty() {
            return n == 0;
        }

        int size() {
            return n;
        }
};
