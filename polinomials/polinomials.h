#include <iostream>
#include <string.h>
#include "myvector.h"

#pragma once

class Term {
private:
    int coefficient = 0;
    int exponent = 0;

public:
    bool from_poly = false;

    Term() {};
    Term(int coefficient, int exponent) {
        this->coefficient = coefficient;
        this->exponent = exponent;
    }
    
    int get_coefficient() {
        return coefficient;
    }

    int get_exponent() {
        return exponent;
    }

    void set_coefficient(int coefficient) {
        this->coefficient = coefficient;
    }

    void set_exponent(int exponent) {
        this->exponent = exponent;
    }

    Term operator+(Term& term) {
        if(exponent != term.exponent) {
            throw std::runtime_error("Different exponents");
        }
        return Term(coefficient + term.coefficient, exponent);
    }

    Term operator*(Term& term) {
        return Term(coefficient * term.coefficient, exponent + term.exponent);
    }

    friend std::istream& operator>>(std::istream& in, Term& term) {
        term.coefficient = 0;
        term.exponent = 0;
        
        Vector<char> input;
        Vector<char> alph; alph = "0123456789x^";

        bool negative = false;
        bool negative_exponent = false;
        char c = '?'; 
        while(c != '-' && c != '+' && c != '\n') {
            c = in.get();
                
            if(c == '-') {
                negative = true;
            }

            if(alph.find_element(c) != -1) {
                input.add_element(c);
            }
            
            if(c == '^') {
                while(in.peek() == ' ') in.get();
                if(in.peek() == '-') {
                    negative_exponent = true;
                    c = in.get();
                }
            }

            c = in.peek();
        }

        if(c == '\n' && !term.from_poly) {
            in.get();
        }

        bool zero_coefficient = false;
        int* it = &term.coefficient;
        for(int i = 0; i < input.size(); ++i){
            if(input[i] == '^') {
                it = &term.exponent;
            }
            if(input[i] >= '0' && input[i] <= '9') {
                if(input[i] == '0' && it == &term.coefficient) zero_coefficient = true; 
                *it *= 10;
                *it += input[i] - '0';
            }
        }

        if(input.find_element('x') != -1 && it != &term.exponent) {
            term.exponent = 1;
        }
        if(term.coefficient == 0 && (it == &term.exponent || input.size() == 1) 
                                            && !zero_coefficient) {
            term.coefficient = 1;
        }

        if(negative) {
            term.coefficient *= -1; 
        }
        if(negative_exponent) {
            term.exponent *= -1;
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, Term term) {
        if(term.coefficient == 0) {
            out << '0';
            return out;
        }
        if(term.coefficient < 0) {
            out << "- ";
        }
        if(term.exponent == 0) {
            out << std::abs(term.coefficient);
            return out;
        }

        if(std::abs(term.coefficient) != 1) {
            out << std::abs(term.coefficient);
        }
        if(term.exponent != 0) {
            out << 'x';
            if(term.exponent != 1) {
                out << '^' << term.exponent;
            }
        }
        
        return out;
    }

    bool operator>(Term& term) {
        return exponent > term.exponent;
    }

    bool operator<(Term& term) {
        return exponent < term.exponent;
    }
};

class Polynomial {
private:
    Vector<Term> arr; 
    int degree;
    bool order_ = false;

public:
    Polynomial() : degree(0) {}
    Polynomial(int degree) {
        this->degree = degree;
    }
    Polynomial(Term& term) {
        arr.add_element(term);
        degree = term.get_exponent();
    }

    Polynomial(Polynomial& poly) {
        arr = poly.arr;
        degree = poly.degree;
    }

    Polynomial& operator=(Polynomial& poly) {
        if(this != &poly) {
            arr = poly.arr;
            degree = poly.degree;
        }
        return *this;
    }

    Polynomial operator+(Polynomial& poly) {
        Polynomial result(*this); 
        for(int i = 0; i < poly.arr.size(); ++i) {
            result.add_term(poly.arr[i]); 
        }
        return result;
    }

    Polynomial operator*(Polynomial& poly) {
        Polynomial result;
        for(int i = 0; i < arr.size(); ++i) {
            for(int j = 0; j < poly.arr.size(); ++j) {
                Term new_term = arr[i] * poly.arr[j];
                result.add_term(new_term); 
            }
        }

        return result;
    }

    void sum_elements() {
        int i = 1;
        while(i < arr.size()) {
            if(!(arr[i] < arr[i - 1]) && !(arr[i] > arr[i - 1])) {
                arr[i - 1] = arr[i - 1] + arr[i];
                arr.delete_element(i);
            }
            else {
                ++i;
            }
        }

        i = 0; 
        while(i < arr.size()) {
            if(arr[i].get_coefficient() == 0) {
                arr.delete_element(i);
            }
            else i++;
        }
    }

    void add_term(Term& term) {
        if(term.get_coefficient() == 0) {
            return;
        }
        term.from_poly = true;

        arr.add_element(term);
        if (term.get_exponent() > degree) {
            degree = term.get_exponent(); 
        }
        arr.sort(0, arr.size() - 1);
        if(order_ == false) {
            arr.reverse();
        }

        sum_elements();
    }

    friend std::istream& operator>>(std::istream& in, Polynomial& poly) {
        Term term; term.from_poly = true;
        while(in.peek() != '\n') {
            in >> term;
            poly.add_term(term);
        }
        in.get();

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, Polynomial poly) {
        if(poly.arr.size() == 0) {
            out << "0";
        } 
        else {
            for(int i = 0; i < poly.arr.size(); ++i) {
                if(poly.arr[i].get_coefficient() > 0 && i > 0) {
                    out << "+ ";
                }
                out << poly.arr[i] << " ";
            }
        }
        return out;
    }
};