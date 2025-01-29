/*
#include <iostream>
using namespace std;
int main(){
    int arr[5] = {0, 5, 10, 15, 20};
    int *ptr = arr;

    cout << *ptr << endl; //0
    cout << *ptr++ << endl;//0 ++ -> 5
    cout << *++ptr << endl;//++ 5  * -> 10
    cout << ++*ptr << endl;//*10  ++ -> 11
    cout << (*ptr)++ << endl;//*11 ++ -> 11
    cout << *ptr << endl;//12
}
*/

#include <iostream>
#include <stack>
using namespace std;

int evaluar_expresion(string s) {
    stack<int> pila;
    int num = 0;
    char operador = '+';  // Se inicializa en '+' por defecto
    int n = s.size();

    for (int i = 0; i < n; i++) {
        char c = s[i];

        if (isdigit(c)) {
            num = num * 10 + (c - '0');  // Convertir caracteres a número
        }

        if (!isdigit(c) && c != ' ' || i == n - 1) {  // Procesar cuando hay un operador o llegamos al final
            if (operador == '+') {
                pila.push(num);
            } else if (operador == '-') {
                pila.push(-num);
            } else if (operador == '*') {
                int top = pila.top();
                pila.pop();
                pila.push(top * num);
            } else if (operador == '/') {
                int top = pila.top();
                pila.pop();
                pila.push(top / num);  // División truncada
            }

            operador = c;
            num = 0;
        }
    }

    // Sumar todos los valores en la pila
    int resultado = 0;
    while (!pila.empty()) {
        resultado += pila.top();
        pila.pop();
    }

    return resultado;
}

int main() {
    string s = "3+2*2";
    cout << "Resultado: " << evaluar_expresion(s) << endl;
    return 0;
}
