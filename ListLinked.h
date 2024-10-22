#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Fuera de rango");

        Node<T>* aux = first;
        for (int i = 0; i < pos; i++) {
            aux = aux->next;
        }
        return aux->data;
    }

    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "List => [";
        Node<T>* temp = list.first;
        while (temp != nullptr) {
            out << " " << temp->data;
            if (temp->next != nullptr)
                out << ",";
            temp = temp->next;
        }
        out << " ]";
        return out;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw std::out_of_range("Posición inválida!");

        Node<T>* newNode = new Node<T>(e);
        if (pos == 0) {
            newNode->next = first;
            first = newNode;
        } else {
            Node<T>* temp = first;
            for (int i = 0; i < pos - 1; i++)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        n++;
    }

    void append(T e) override { insert(n, e); }

    void prepend(T e) override { insert(0, e); }

    T remove(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida!");

        Node<T>* toDelete;
        T removedData;
        if (pos == 0) {
            toDelete = first;
            removedData = first->data;
            first = first->next;
        } else {
            Node<T>* temp = first;
            for (int i = 0; i < pos - 1; i++)
                temp = temp->next;
            toDelete = temp->next;
            removedData = toDelete->data;
            temp->next = toDelete->next;
        }
        delete toDelete;
        n--;
        return removedData;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida!");

        Node<T>* temp = first;
        for (int i = 0; i < pos; i++)
            temp = temp->next;

        return temp->data;
    }

    int search(T e) override {
        Node<T>* temp = first;
        int index = 0;

        while (temp != nullptr) {
            if (temp->data == e)
                return index;
            temp = temp->next;
            index++;
        }
        return -1; // No encontrado
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }
};

