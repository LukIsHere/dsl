//just an experiment
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Funkcja pomocnicza do sprawdzenia, czy liczba jest pierwsza
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Funkcja pomocnicza do wyznaczania NWD dwóch liczb
int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

// Funkcja pomocnicza do wyznaczania odwrotności modularnej liczby a mod m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

// Funkcja generująca klucze do RSA
void generateKeys(int p, int q, int& n, int& e, int& d) {
    // Obliczanie n i fi(n)
    n = p * q;
    int fi_n = (p - 1) * (q - 1);

    // Wybór liczby e
    e = 2;
    while (e < fi_n && gcd(e, fi_n) != 1) {
        e++;
    }

    // Obliczanie d
    d = modInverse(e, fi_n);
}

// Funkcja szyfrująca wiadomość za pomocą klucza publicznego
string encrypt(string message, int n, int e) {
    string ciphertext = "";
    for (int i = 0; i < message.length(); i++) {
        int m = message[i];
        int c = 1;
        for (int j = 0; j < e; j++) {
            c = (c * m) % n;
        }
        ciphertext += to_string(c);
        ciphertext += " ";
    }
    return ciphertext;
}

// Funkcja odszyfrowująca wiadomość za pomocą klucza prywatnego
string decrypt(string ciphertext, int n, int d) {
    string message = "";
    int i = 0;
    while (i < ciphertext.length()) {
        string num = "";
        while (ciphertext[i] != ' ') {
            num += ciphertext[i];
            i++;
        }
        i++;
        int c = stoi(num);
        int m = 1;
        for (int j = 0; j < d; j++) {
            m = (m * c) % n;
        }
        message += (char) m;
    }
    return message;
}

int main() {
    srand(time(NULL)); // Inicjalizacja generatora liczb pseudolosowych

    // Generowanie dwóch liczb pierwszych
    int p = rand() % 100 + 50;
    while (!isPrime(p)) {
        p++;
    }
    int q = rand() % 100 + 50;
    while (!isPrime(q) || q == p) {
        q++;
    }

    // Generowanie kluczy
    int n, e, d;
    generateKeys(p, q, n, e, d);
    cout << "Klucz publiczny: (" << n << ", " << e << ")" << endl;
    cout << "Klucz prywatny: (" << n << ", " << d << ")" << endl;

    // Szyfrowanie wiadomości
    string message = "Hello, world!";
    string ciphertext = encrypt(message, n, e);
    cout << "Zaszyfrowana wiadomość: " << ciphertext << endl;

    // Odszyfrowywanie wiadomości
    string decrypted = decrypt(ciphertext, n, d);
    cout << "Odszyfrowana wiadomość: " << decrypted << endl;

    return 0;
}
