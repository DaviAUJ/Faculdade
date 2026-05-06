#include <array>
#include <iostream>

using namespace std;

int main() {
    const int A = 10;
    array<int, A> real;
    array<int, A> fake = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };

    real.swap(fake);

    cout << "Tamanho:\n" << real.size() << "\n\n";
    cout << "Tamanho máximo:\n" << real.max_size() << "\n\n";
    cout << "Vazia?\n" << real.empty() << "\n\n";
    cout << "Posição com .at(" << A - 2 << "):\n" << real.at(A - 2) << "\n\n";
    cout << "Frente:\n" << real.front() << "\n\n";
    cout << "Atrás:\n" << real.back() << "\n\n";
    cout << "Posição com .data() + " << 2 << ":\n" << *(real.data() + 2) << "\n\n";

    cout << "Elementos:\n";
    for(int const& e : real) {
        cout << e << '\n';
    }

    cout << '\n';

    cout << "Elementos reversos:\n";
    for(auto it = real.crbegin(); it != real.crend(); ++it) {
        cout << *it << '\n';
    }

    return 0;
}
