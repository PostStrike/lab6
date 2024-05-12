#include <iostream>
#include "polinomials/polinomials.h"

void polynomial_test() {
    Polynomial poly; std::cin >> poly;
    std::cout << poly;
}

void plus() {
    Polynomial poly1, poly2;
    std::cout << "Введите poly1: "; std::cin >> poly1;
    std::cout << "Введите poly2: "; std::cin >> poly2;
    std::cout << "poly1 + poly2 = "; std::cout << poly1 + poly2;
}

void multy() {
    Polynomial poly1, poly2;
    std::cout << "Введите poly1: "; std::cin >> poly1;
    std::cout << "Введите poly2: "; std::cin >> poly2;
    std::cout << "poly1 * poly2 = "; std::cout << poly1 * poly2;
}

void term_test() {
    Term term1, term2;
    std::cout << "Введите term1: "; std::cin >> term1;
    std::cout << "Введите term2: "; std::cin >> term2;
    std::cout << "term1 + term2 = "; std::cout << term1 + term2;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");

    //term_test();
    //multy();
    plus();
    //polynomial_test();
    std::cout << std::endl;

    return 0;
}

//2x - x + 3x^1 -   3 x
