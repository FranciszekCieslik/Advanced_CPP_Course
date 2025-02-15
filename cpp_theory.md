## L-value vs R-value 

### **1. Definicje**

#### **L-value (Left Value)**

- Reprezentuje **obiekt w pamięci**, który posiada **adres**.
- Może stać po lewej stronie operatora `=`.
- Może być modyfikowany (chyba że jest `const`).

**Przykłady:**

```cpp
int x = 10;    // 'x' to L-value, ponieważ ma adres i można go modyfikować.
x = 20;        // OK, przypisanie do L-value.
```

#### **R-value (Right Value)**

- Reprezentuje **wartość tymczasową**, która **nie ma adresu**.
- Może stać tylko po prawej stronie operatora `=`.
- Zwykle jest wynikiem wyrażenia lub stałą liczbową.

**Przykłady:**

```cpp
int y = 5 + 3;  // '5 + 3' to R-value.
int z = 10;     // '10' to R-value.
```

### **2. Przykłady L-value i R-value**

```cpp
int a = 10;   // 'a' to L-value, '10' to R-value.
a = 20;       // OK, L-value może być modyfikowane.

int& ref = a; // OK, referencja do L-value.

int&& rref = 30; // OK, R-value reference może przechwycić R-value.
```

### **3. L-value i R-value Reference**

#### **L-value Reference (`&`)**

- Może przechwycić tylko L-value.
- Może być używana do modyfikowania wartości.

**Przykład:**

```cpp
int x = 10;
int& ref = x;  // OK, 'x' to L-value.
```

#### **R-value Reference (`&&`)**

- Może przechwycić tylko R-value.
- Używane do optymalizacji (np. przenoszenia `std::move`).

**Przykład:**

```cpp
int&& rref = 10;  // OK, '10' to R-value.
```

### **4. std::move i R-value**

- `std::move(x)` zamienia L-value w R-value.
- Używane do **przenoszenia zasobów zamiast kopiowania**.

**Przykład:**

```cpp
#include <iostream>
#include <vector>
#include <utility>  // std::move

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = std::move(v1); // Przenoszenie zasobów.

    std::cout << "Rozmiar v1: " << v1.size() << "\n";  // 0, bo v1 zostało opróżnione.
}
```


## Programowanie Obiektowe

### **Obiekt a klasa**

- **Klasa** – definicja obiektu, określa jego właściwości i zachowanie.
- **Obiekt** – instancja klasy, konkretny egzemplarz posiadający stan i metody.

#### Przykład:

```cpp
class Samochod {
public:
    std::string marka;
    int rok;
    void pokazInformacje() {
        std::cout << "Marka: " << marka << ", Rok: " << rok << std::endl;
    }
};

int main() {
    Samochod auto;
    auto.marka = "Toyota";
    auto.rok = 2020;
    auto.pokazInformacje();
    return 0;
}
```

### **Hermetyzacja**

- Ukrywanie szczegółów implementacji, dostęp do pól tylko przez metody publiczne.
- Chroni dane przed bezpośrednią modyfikacją.

#### Przykład:

```cpp
class KontoBankowe {
private:
    double saldo;
public:
    KontoBankowe(double poczatkowe_saldo) : saldo(poczatkowe_saldo) {}
    void wplac(double kwota) { saldo += kwota; }
    double pobierzSaldo() const { return saldo; }
};
```

### **Dziedziczenie**

- Pozwala na wielokrotne użycie kodu, `public`, `protected`, `private` dziedziczenie.
- Konstruktor klasy bazowej wywoływany jako pierwszy.
#### Przykład:

```cpp
class Pojazd {
public:
    int predkosc;
    void pokazPredkosc() { std::cout << "Predkosc: " << predkosc << " km/h" << std::endl; }
};

class Samochod : public Pojazd {
public:
    std::string marka;
};
```

1. **`public` dziedziczenie** (`class Samochod : public Pojazd`):

|Modyfikator w `Pojazd`|W klasie `Samochod` (przy `public` dziedziczeniu)|
|---|---|
|`public`|`public`|
|`protected`|`protected`|
|`private`|**Niedostępny**|
2. **`protected` dziedziczenie** (`class Samochod : protected Pojazd`):

|Modyfikator w `Pojazd`|W klasie `Samochod` (przy `protected` dziedziczeniu)|
|---|---|
|`public`|`protected`|
|`protected`|`protected`|
|`private`|**Niedostępny**|

3. **`private` dziedziczenie** (`class Samochod : private Pojazd`):

|Modyfikator w `Pojazd`|W klasie `Samochod` (przy `private` dziedziczeniu)|
|---|---|
|`public`|`private`|
|`protected`|`private`|
|`private`|**Niedostępny**|

### **Polimorfizm**

- Możliwość nadpisania metod w klasach pochodnych.
- Pozwala na elastyczne użycie metod w klasach bazowych i pochodnych.

#### Przykład:

```cpp
class Zwierze {
public:
    virtual void dzwiek() { std::cout << "Nieznany dźwięk" << std::endl; }
};

class Pies : public Zwierze {
public:
    void dzwiek() override { std::cout << "Hau Hau" << std::endl; }
};
```

### **Funkcje wirtualne**

- Pozwalają na dynamiczne wiązanie metod, umożliwiają polimorfizm.
- Wywoływane według typu obiektu, a nie wskaźnika.
- słowa klucz  `virtual` i `override` 
- [!] `override` nie jest konieczne

#### Przykład:

```cpp
class Figura {
public:
    virtual void rysuj() { std::cout << "Rysuję figurę" << std::endl; }
};

class Kolo : public Figura {
public:
    void rysuj() override { std::cout << "Rysuję koło" << std::endl; }
};
```

### **Friend**

- `friend` pozwala danej funkcji lub klasie na dostęp do prywatnych i chronionych pól klasy.

#### Przykład:

```cpp
class Konto {
private:
    double saldo;
public:
    Konto(double s) : saldo(s) {}
    friend void pokazSaldo(const Konto& k);
};

void pokazSaldo(const Konto& k) {
    std::cout << "Saldo: " << k.saldo << std::endl;
}
```

### **Dodatkowe elementy programowania obiektowego**

#### **1. Konstruktory i destruktory – zarządzanie cyklem życia obiektów**  
Konstruktory i destruktory odpowiadają za **inicjalizację i zwalnianie zasobów**.  

📌 **Konstruktor** – specjalna metoda wywoływana przy tworzeniu obiektu.  
📌 **Destruktor** – specjalna metoda wywoływana przy niszczeniu obiektu.  

##### **Przykład konstruktora i destruktora:**

```cpp
#include <iostream>

class Samochod {
public:
    std::string marka;

    // Konstruktor
    Samochod(std::string m) : marka(m) {
        std::cout << "Tworzę samochód: " << marka << std::endl;
    }

    // Destruktor
    ~Samochod() {
        std::cout << "Niszczenie samochodu: " << marka << std::endl;
    }
};

int main() {
    Samochod auto1("Toyota");
    return 0;
}
```

**Wyjście:**  
```
Tworzę samochód: Toyota  
Niszczenie samochodu: Toyota  
```
💡 **Zauważ, że destruktor uruchamia się automatycznie przy końcu zakresu obiektu.**  

---

#### **2. Przeciążanie operatorów – redefiniowanie operatorów**  
Przeciążanie operatorów umożliwia **zmianę zachowania operatorów** dla własnych typów.  

📌 **Najczęściej przeciążane operatory**: `+`, `-`, `=`, `[]`, `()`, `<<`, `>>`  
📌 **Nie można przeciążyć**: `::`, `.*`, `sizeof`, `?:`  

##### **Przykład przeciążenia operatora `+`:**
```cpp
#include <iostream>

class Wektor {
public:
    int x, y;

    Wektor(int a, int b) : x(a), y(b) {}

    // Przeciążenie operatora +
    Wektor operator+(const Wektor& v) {
        return Wektor(x + v.x, y + v.y);
    }

    void pokaz() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Wektor v1(2, 3), v2(4, 5);
    Wektor v3 = v1 + v2;
    v3.pokaz();  // (6, 8)
}
```
💡 **Dzięki przeciążeniu `+` możemy sumować wektory tak, jak liczby.**  

---

### **3. Abstrakcja – klasy bazowe z metodami czysto wirtualnymi (`= 0`)**  
Abstrakcja pozwala definiować **szkielet klasy**, który musi zostać zaimplementowany w klasach pochodnych.  

📌 **Metoda czysto wirtualna (`= 0`)** – musi być nadpisana w klasie pochodnej.  
📌 **Nie można utworzyć instancji klasy abstrakcyjnej.**  

##### **Przykład klasy abstrakcyjnej:**
```cpp
#include <iostream>

// Klasa abstrakcyjna
class Zwierze {
public:
    virtual void dzwiek() = 0;  // Metoda czysto wirtualna
};

class Pies : public Zwierze {
public:
    void dzwiek() override {
        std::cout << "Hau Hau!" << std::endl;
    }
};

int main() {
    Pies rex;
    rex.dzwiek();  // Hau Hau!
}
```
💡 **Każda klasa pochodna musi zaimplementować `dzwiek()`, inaczej będzie również abstrakcyjna.**  

---

### **4. Interfejsy – klasy zawierające tylko metody czysto wirtualne**  
Interfejs to **specjalny przypadek klasy abstrakcyjnej**, który **nie zawiera pól ani implementacji metod**.  

📌 **Czysty interfejs to klasa mająca tylko metody czysto wirtualne.**  
📌 **Pozwala na implementację wielokrotnego dziedziczenia bez problemów.**  

#### **Przykład interfejsu:**
```cpp
#include <iostream>

// Interfejs
class Drukowalne {
public:
    virtual void drukuj() const = 0;
};

class Dokument : public Drukowalne {
public:
    void drukuj() const override {
        std::cout << "Drukowanie dokumentu..." << std::endl;
    }
};

int main() {
    Dokument d;
    d.drukuj();  // Drukowanie dokumentu...
}
```
💡 **Interfejsy są powszechne w projektach obiektowych, pozwalając na luźne powiązania między klasami.**  

---

### **5. Zasada pięciu (Rule of Five)**  
Zasada pięciu mówi, że jeśli klasa zarządza **dynamiczną pamięcią**, powinna implementować **pięć specjalnych metod**:

1. **Konstruktor kopiujący (`Class(const Class& other)`)**  
2. **Operator przypisania kopiującego (`Class& operator=(const Class& other)`)**  
3. **Konstruktor przenoszący (`Class(Class&& other) noexcept`)**  
4. **Operator przypisania przenoszącego (`Class& operator=(Class&& other) noexcept`)**  
5. **Destruktor (`~Class()`)**  

📌 **Wprowadzenie tej zasady eliminuje wycieki pamięci i błędy związane z kopiowaniem.**  

#### **Przykład klasy zgodnej z zasadą pięciu:**
```cpp
#include <iostream>
#include <cstring>

class Tekst {
private:
    char* dane;
public:
    // Konstruktor
    Tekst(const char* str) {
        dane = new char[strlen(str) + 1];
        strcpy(dane, str);
    }

    // Konstruktor kopiujący
    Tekst(const Tekst& other) {
        dane = new char[strlen(other.dane) + 1];
        strcpy(dane, other.dane);
    }

    // Operator przypisania kopiującego
    Tekst& operator=(const Tekst& other) {
        if (this == &other) return *this;  // Zabezpieczenie przed samoprzydziałem
        delete[] dane;
        dane = new char[strlen(other.dane) + 1];
        strcpy(dane, other.dane);
        return *this;
    }

    // Konstruktor przenoszący
    Tekst(Tekst&& other) noexcept : dane(other.dane) {
        other.dane = nullptr;
    }

    // Operator przypisania przenoszącego
    Tekst& operator=(Tekst&& other) noexcept {
        if (this == &other) return *this;
        delete[] dane;
        dane = other.dane;
        other.dane = nullptr;
        return *this;
    }

    // Destruktor
    ~Tekst() {
        delete[] dane;
    }

    void pokaz() const {
        std::cout << dane << std::endl;
    }
};

int main() {
    Tekst t1("Hello");
    Tekst t2 = t1;  // Konstruktor kopiujący
    Tekst t3 = std::move(t1);  // Konstruktor przenoszący

    t2.pokaz();  // Hello
    t3.pokaz();  // Hello

    return 0;
}
```

💡 **Dzięki zasadzie pięciu klasa poprawnie zarządza dynamiczną pamięcią!**  


## Obiekty funkcyjne

Obiekty funkcyjne to **klasy lub struktury, które przeciążają operator `operator()`**, dzięki czemu można je wywołać jak funkcję. Są bardziej elastyczne od zwykłych funkcji i pozwalają na przechowywanie stanu.

```cpp
#include <iostream>

class Adder {
    int value;
public:
    Adder(int v) : value(v) {}
    int operator()(int x) const { return x + value; }
};

int main() {
    Adder add5(5);  // Obiekt funkcyjny, który dodaje 5
    std::cout << add5(10);  // Wynik: 15
}
```

Obiekty funkcyjne świetnie sprawdzają się w algorytmach STL jako komparatory.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Descending {
    bool operator()(int a, int b) const { return a > b; }
};

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end(), Descending()); // Sortowanie malejące

    for (int x : v) std::cout << x << " "; // 5 4 3 1 1
}
```

## Lambda

Lambda to **anonimowa funkcja**, którą można przypisać do zmiennej, przekazać jako argument lub używać inline. Wprowadzona w **C++11**, jest krótsza i bardziej elastyczna niż obiekty funkcyjne.

### **📌 Różnice między lambdą, funkcją i obiektem funkcyjnym**

|Cecha|Funkcja|Lambda|Obiekt funkcyjny|
|---|---|---|---|
|**Nazwa**|Ma nazwę|Brak nazwy|Ma nazwę|
|**Złożoność kodu**|Średnia|Najkrótsza|Najdłuższa|
|**Przechowywanie stanu**|Nie|Tak (przez capture)|Tak|
|**Przekazywanie jako argument**|Trudniejsze (wskaźnik do funkcji)|Najłatwiejsze|Możliwe|

### **📌 Jak zdefiniować lambdę?**

#### **1️⃣ Podstawowa składnia**

```cpp
[capture](parametry) -> typ_zwrotu { ciało_funkcji }
```

✔ **`capture`** – lista przechwytywanych zmiennych (np. `[x]`, `[&x]`, `[=]`)  
✔ **`parametry`** – lista argumentów jak w funkcji (opcjonalnie)  
✔ **`-> typ_zwrotu`** – określenie typu zwracanego (opcjonalnie, często dedukowany automatycznie)  
✔ **`{ ciało_funkcji }`** – właściwa implementacja

---

### **📌 Przykłady lambd w C++**

#### **1️⃣ Prosta lambda (bez parametrów)**

```cpp
#include <iostream>
int main() {
    auto hello = []() { std::cout << "Witaj w świecie lambd!\n"; };
    hello(); // Witaj w świecie lambd!
}
```

---

#### **2️⃣ Lambda z parametrami**

```cpp
#include <iostream>
int main() {
    auto add = [](int a, int b) { return a + b; };
    std::cout << add(3, 7); // Wynik: 10
}
```

---

#### **3️⃣ Lambda ze zwracanym typem (`->`)**

```cpp
#include <iostream>
int main() {
    auto divide = [](int a, int b) -> double { return (double)a / b; };
    std::cout << divide(7, 2); // Wynik: 3.5
}
```

📌 **Bez `-> double`, wynik byłby `3`, bo domyślnie zwraca `int`!**

---
### **📌 Przekazywanie zmiennych do lambdy**

#### **1️⃣ Przechwytywanie zmiennych przez wartość (`[=]`, `[x]`)**

```cpp
#include <iostream>
int main() {
    int a = 10;
    auto lambda = [a]() { std::cout << a << "\n"; }; 
    lambda(); // 10
}
```

📌 **Kopia `a` zostaje zapamiętana**, więc nawet jeśli `a` zmieni się po utworzeniu lambdy, to lambda nadal użyje starej wartości.

---

#### **2️⃣ Przechwytywanie przez referencję (`[&]`, `[&x]`)**

```cpp
#include <iostream>
int main() {
    int a = 10;
    auto lambda = [&a]() { a += 5; };
    lambda();
    std::cout << a; // 15
}
```

📌 **Lambda modyfikuje `a` w oryginalnym miejscu pamięci!**

---

#### **3️⃣ Przechwytywanie zmiennych w różnych kombinacjach**

```cpp
int a = 10, b = 20;
auto lambda = [=, &b]() { b += a; };  // `a` przez wartość, `b` przez referencję
```

📌 **`a` nie można zmieniać w lambdzie, ale `b` można!**

---

#### **4️⃣ Mutowalna lambda (`mutable`)**

Domyślnie lambda **nie może zmieniać** przechwyconych wartości przez wartość. Dodanie `mutable` pozwala na modyfikację kopii zmiennych wewnątrz lambdy.

```cpp
#include <iostream>
int main() {
    int x = 10;
    auto lambda = [x]() mutable { x += 5; std::cout << x; };
    lambda(); // 15
    std::cout << x; // 10 (oryginalna wartość się nie zmienia!)
}
```

📌 **Modyfikowana jest tylko KOPIA `x`, a nie oryginał!**

---

#### **5️⃣ Lambda jako parametr funkcji**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void applyFunction(int x, auto func) {
    std::cout << func(x) << "\n";
}

int main() {
    applyFunction(5, [](int n) { return n * 2; }); // 10
}
```

📌 **Lambda może być przekazywana jako argument, co eliminuje potrzebę pisania osobnych funkcji.**

---

#### **6️⃣ Lambda w STL (np. `std::sort`)**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {4, 2, 8, 1};
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });

    for (int x : v) std::cout << x << " "; // 8 4 2 1
}
```

📌 **Lambda jako komparator dla sortowania malejącego.**

---


---
### **📌 Kiedy używać lambd zamiast funkcji lub obiektów funkcyjnych?**

✅ **Lambdy** → Gdy funkcja jest prosta i jednorazowa.  
✅ **Obiekty funkcyjne** → Gdy trzeba przechowywać stan.  
✅ **Funkcje** → Gdy kod powinien być wielokrotnie używany i czytelniejszy.

## Wskaźniki i referencje
### **Smart pointery (unique, shared, weak)**

### **Unique Pointer (`std::unique_ptr`)**

- Posiada wyłączność na zasób.
- Nie można go kopiować, można przenieść (`std::move`).

**Przykład:**

```cpp
#include <memory>
#include <iostream>

class Test {
public:
    void show() { std::cout << "Test show()\n"; }
};

int main() {
    std::unique_ptr<Test> ptr1 = std::make_unique<Test>();
    ptr1->show();
    std::unique_ptr<Test> ptr2 = std::move(ptr1); // Przeniesienie własności.
    if (!ptr1) std::cout << "ptr1 jest nullptr\n";
}
```

### **Shared Pointer (`std::shared_ptr`)**

- Współdzielony wskaźnik, licznik referencji.
- Zasób zwalniany, gdy licznik osiągnie zero.

**Przykład:**

```cpp
#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> sp1 = std::make_shared<int>(10);
    std::shared_ptr<int> sp2 = sp1; // Współdzielenie zasobu.
    std::cout << "Licznik referencji: " << sp1.use_count() << "\n";
}
```

### **Weak Pointer (`std::weak_ptr`)**

- Słaby wskaźnik do `shared_ptr`, nie zwiększa licznika referencji.
- Zapobiega cyklom referencji.

**Przykład:**

```cpp
#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp = sp;
    if (auto sp2 = wp.lock()) {
        std::cout << "Wartość: " << *sp2 << "\n";
    }
}
```

### **Pointer a referencja**

|Cecha|Wskaźnik|Referencja|
|---|---|---|
|Może być `nullptr`|Tak|Nie|
|Może zmieniać obiekt, na który wskazuje|Tak|Nie|
|Wymaga dereferencji `*`|Tak|Nie|

## Struktury danych

### **1. Kontenery sekwencyjne (Sequential Containers)**

Przechowują dane w określonej kolejności.

|Struktura|Opis|
|---|---|
|**`std::vector`**|Dynamiczna tablica, szybki dostęp `O(1)`, operacje na końcu `O(1)`.|
|**`std::array`**|Stała tablica o określonym rozmiarze (nie dynamiczna).|
|**`std::list`**|Lista dwukierunkowa, szybkie wstawianie/usuwanie `O(1)`, ale wolniejszy dostęp `O(n)`.|
|**`std::deque`**|Dwustronna kolejka, szybkie operacje `push_front/push_back` `O(1)`.|

#### **Przykład `vector`**

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};
    v.push_back(4);
    std::cout << "Element: " << v[2] << "\n"; // Wypisze: 3
}
```

---

### **2. Kontenery asocjacyjne (Associative Containers)**

Zoptymalizowane pod kątem szybkiego wyszukiwania `O(log n)`, często oparte na drzewach binarnych.

|Struktura|Opis|
|---|---|
|**`std::set`**|Unikalne wartości, posortowane, brak indeksowania.|
|**`std::unordered_set`**|Unikalne wartości, nieposortowane, szybsze wyszukiwanie `O(1)`.|
|**`std::map`**|Klucz-wartość, unikalne klucze, posortowane, `O(log n)`.|
|**`std::unordered_map`**|Klucz-wartość, nieposortowane, szybsze `O(1)`.|

#### **Przykład `map`**

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> m;
    m["Alice"] = 30;
    m["Bob"] = 25;
    std::cout << "Alice ma " << m["Alice"] << " lat.\n";
}
```

---

### **3. Kontenery adaptacyjne (Adaptors)**

Są zbudowane na bazie innych kontenerów.

|Struktura|Opis|
|---|---|
|**`std::stack`**|Stos (LIFO – Last In, First Out).|
|**`std::queue`**|Kolejka (FIFO – First In, First Out).|
|**`std::priority_queue`**|Kolejka priorytetowa (największy/najmniejszy element na górze).|

#### **Przykład `stack`**

```cpp
#include <stack>
#include <iostream>

int main() {
    std::stack<int> s;
    s.push(10);
    s.push(20);
    std::cout << "Na szczycie: " << s.top() << "\n"; // 20
    s.pop();
    std::cout << "Na szczycie: " << s.top() << "\n"; // 10
}
```

---

##  Struktury zaawansowane

### **1. Drzewa**

##### **BST (Binary Search Tree)**

Drzewo binarne wyszukiwania (BST) to drzewo binarne, w którym dla każdego węzła, wszystkie węzły w jego lewym poddrzewie mają wartość mniejszą, a w jego prawym poddrzewie mają wartość większą niż wartość węzła.

#### **AVL Tree**

AVL to zrównoważone drzewo binarne, w którym różnica wysokości lewego i prawego poddrzewa żadnego węzła nie może być większa niż 1.

### **2. Grafy**

##### **Macierz sąsiedztwa**

Macierz sąsiedztwa to dwuwymiarowa tablica, w której element na pozycji (i, j) oznacza, czy istnieje krawędź między wierzchołkami i i j.

#### **Lista sąsiedztwa**

Lista sąsiedztwa to lista, w której każdy wierzchołek przechowuje listę swoich sąsiadów.

### **3. Kopce**

#### **Min-Heap**

Min-heap to struktura danych, w której dla każdego węzła jego wartość nie jest większa niż wartość jego dzieci.

#### **Max-Heap**

Max-heap to struktura danych, w której dla każdego węzła jego wartość nie jest mniejsza niż wartość jego dzieci.
## Iteratory

- Wskazują na element w kontenerze, `begin()`, `end()`, `rbegin()`, `rend()`.

![[begin_end_rbegin_rend.png]]


## Pamięć
### **Operatory new i delete**

- `new` – alokuje pamięć na stercie.
- `delete` – zwalnia pamięć.
- `new[]` i `delete[]` dla tablic dynamicznych.
### **Sposoby ręcznego zarządzania pamięcią (poza `new` / `delete`)**

| **Technika**                    | **Opis**                                                                              |
| ------------------------------- | ------------------------------------------------------------------------------------- |
| **`malloc()` i `free()`**       | Starsze C-style funkcje do alokacji pamięci, nie wywołują konstruktorów/destruktorów. |
| **`calloc()`**                  | Podobne do `malloc()`, ale zeruje zaalokowaną pamięć.                                 |
| **`realloc()`**                 | Zmienia rozmiar wcześniej zaalokowanej pamięci.                                       |
| **`placement new`**             | Tworzy obiekt w określonym miejscu pamięci (np. w prealokowanym buforze).             |
| **`std::allocator<T>`**         | Standardowy sposób zarządzania pamięcią w STL, np. `std::vector`.                     |
| **`std::unique_ptr`**           | Inteligentny wskaźnik, który automatycznie zwalnia pamięć (`delete`).                 |
| **`std::shared_ptr`**           | Wskaźnik z licznikiem referencji, automatycznie zwalnia pamięć.                       |
| **`std::weak_ptr`**             | Słaby wskaźnik, który nie zwiększa liczby referencji `shared_ptr`.                    |
| **`mmap()` / `VirtualAlloc()`** | Alokacja pamięci na poziomie systemu operacyjnego.                                    |
| **`brk()` / `sbrk()`**          | Niskopoziomowe funkcje zarządzania pamięcią w Linux.                                  |
### **Pamięć (stack vs heap)**

- **Stack** – szybki dostęp, automatyczne zwalnianie pamięci.
- **Heap** – dynamiczna alokacja pamięci, wymaga manualnego zwalniania.

| **Rodzaj zmiennej**                              | **Przechowywanie na**                                   | **Opis**                                                                        |
| ------------------------------------------------ | ------------------------------------------------------- | ------------------------------------------------------------------------------- |
| **Zmienne lokalne**                              | **Stack**                                               | Przechowywane na stosie, automatycznie usuwane po wyjściu z funkcji.            |
| **Argumenty funkcji**                            | **Stack**                                               | Przekazywane przez wartość są kopiowane na stos.                                |
| **Zmienne globalne**                             | **Data Segment (Static Storage)**                       | Istnieją przez cały czas działania programu.                                    |
| **Zmienne `static` (lokalne i globalne)**        | **Data Segment (Static Storage)**                       | Przechowywane w stałym obszarze pamięci, inicjalizowane tylko raz.              |
| **Obiekty alokowane przez `new` / `malloc`**     | **Heap**                                                | Tworzone dynamicznie, muszą być ręcznie zwalniane (`delete` / `free`).          |
| **Tablice dynamiczne (`new[]`)**                 | **Heap**                                                | Alokowane na stercie, wymagają `delete[]`.                                      |
| **Zmienne referencyjne (`&`)**                   | **Stack**                                               | Są aliasami do istniejących obiektów na stosie lub stercie.                     |
| **Obiekty zwracane przez wartość**               | **Stack** _(lub optymalizowane do rejestrów)_           | Kopiowane na stos lub optymalizowane przez NRVO.                                |
| **Obiekty przekazywane przez wskaźnik (`T*`)**   | **Heap** _(lub Stack, jeśli wskaźnik wskazuje na stos)_ | Wskaźnik sam w sobie jest na stosie, ale wskazywany obiekt może być na stercie. |
| **Obiekty przekazywane przez referencję (`T&`)** | **Zależnie od obiektu**                                 | Nie tworzą nowych instancji, działają na istniejących danych.                   |
| **Zmienne `constexpr`**                          | **Compile-time / Data Segment**                         | Wartości znane w czasie kompilacji, często przechowywane w sekcji kodu.         |
| **Zmienne `volatile`**                           | **Zależnie od deklaracji**                              | Wymusza każdorazowe odczytanie z pamięci (np. w przypadku mapowania sprzętu).   |

## Wydajność
### **Testowanie**

- **Jednostkowe (unit testing)** – testowanie małych jednostek kodu.
- **Integracyjne** – testowanie współpracy modułów.
- **Systemowe** – testowanie całego systemu.

### **Złożoność obliczeniowa algorytmów**

|Notacja|Opis|Przykład algorytmu|
|---|---|---|
|**O(1)**|Stała|Odczyt elementu tablicy `arr[i]`|
|**O(log n)**|Logarytmiczna|Wyszukiwanie binarne|
|**O(n)**|Liniowa|Przejście przez tablicę|
|**O(n log n)**|Log-liniowa|Sortowanie szybkie, merge sort|
|**O(n²)**|Kwadratowa|Sortowanie bąbelkowe, insertion sort|
|**O(2ⁿ)**|Eksponencjalna|Rozwiązania rekurencyjne (np. naiwny algorytm Fibonacci)|
|**O(n!)**|Silniowa|Algorytmy brute-force np. permutacje|
🔹 **Im wolniej rośnie funkcja, tym lepsza wydajność programu!**

## Inne koncepty
### **RAII (Resource Acquisition Is Initialization)**

- Technika zarządzania zasobami, w której obiekty przejmują odpowiedzialność za alokację i dealokację zasobów.
- Konstruktor alokuje zasoby, destruktor je zwalnia.
### **SOLID – Zasady dobrego projektowania obiektowego**

1. **Single Responsibility Principle (SRP)** – Klasa powinna mieć tylko jedną odpowiedzialność.
2. **Open/Closed Principle (OCP)** – Kod powinien być otwarty na rozszerzenia, ale zamknięty na modyfikacje.
3. **Liskov Substitution Principle (LSP)** – Podklasy powinny być wymienne z klasami bazowymi.
4. **Interface Segregation Principle (ISP)** – Tworzymy specyficzne interfejsy zamiast jednego dużego.
5. **Dependency Inversion Principle (DIP)** – Moduły wyższego poziomu nie powinny zależeć od modułów niższego poziomu, a obie warstwy powinny zależeć od abstrakcji.
### **AoS (Array of Structures) vs SoA (Structure of Arrays)**

AoS i SoA to **dwa różne sposoby organizacji danych** w pamięci. Wybór między nimi wpływa na **wydajność**, zwłaszcza w kontekście **przetwarzania równoległego (SIMD, cache)**.

-  **📌 1. AoS – Array of Structures (Tablica Struktur)**
	W podejściu **AoS** mamy tablicę, której elementami są **struktury** zawierające różne pola.
	
	✅ **Zalety**  
		✔ Łatwiejsza organizacja i czytelność kodu.  
		✔ Naturalne odwzorowanie obiektów.
		
	❌ **Wady**  
		⏳ Może być **wolniejsze** dla SIMD i cache CPU, bo pola różnych struktur są **rozproszone**.

- **📌 2. SoA – Structure of Arrays (Struktura Tablic)**
	W podejściu **SoA** dane są przechowywane jako **osobne tablice dla każdego pola**.
	
	✅ **Zalety**  
		✔ **Lepsza wydajność w SIMD (SSE, AVX, GPU)** – dane są **ciągłe w pamięci**, co ułatwia wektoryzację.  
		✔ **Lepsza lokalność pamięci cache** – przetwarzając `x[]`, nie tracimy czasu na `y[]` i `z[]`.
		
	❌ **Wady**  
		⏳ Trudniejsza organizacja kodu.  
		⏳ Nie zawsze intuicyjne dla obiektowego myślenia.

### **Programowanie dynamiczne (DP)**

Programowanie dynamiczne to technika algorytmiczna, która optymalizuje rozwiązania problemów poprzez **rozbijanie ich na podproblemy**, a następnie przechowywanie wyników tych podproblemów, aby uniknąć ich wielokrotnego obliczania.

**Główne zasady DP:**

1. **Optymalna podstruktura** – rozwiązanie problemu można skonstruować na podstawie rozwiązań jego podproblemów.
2. **Nakładające się podproblemy** – te same podproblemy są rozwiązywane wielokrotnie.

#### **Kiedy stosować DP?**

Programowanie dynamiczne jest idealne do problemów: ✔️ Gdzie występują **nakładające się podproblemy**  
✔️ Gdzie można podzielić problem na **optymalne podstruktury**  
✔️ Gdzie trzeba **zmaksymalizować lub zminimalizować jakąś wartość**

#### **Jak korzystać z DP w C++?**

W C++ programowanie dynamiczne można implementować na dwa sposoby:

- **Metoda top-down (memoizacja)** – zapisujemy wyniki podproblemów i unikamy ich ponownego obliczania.
- **Metoda bottom-up (tabularyzacja)** – rozwiązujemy podproblemy w kolejności od najmniejszych do większych.
## Słowa kluczowe

### **1️⃣ `static` – zmienna statyczna, funkcja statyczna, zasięg pliku**

**`static`** może mieć różne znaczenia w zależności od kontekstu.

#### **📌 `static` w zmiennej wewnątrz funkcji**

```cpp
void counter() {
    static int count = 0;  // Zmienna zachowuje wartość między wywołaniami
    count++;
    std::cout << "Count: " << count << std::endl;
}
```

📌 **Zachowuje wartość pomiędzy wywołaniami funkcji.**

---

#### **📌 `static` w zmiennej klasy (zmienna statyczna)**

```cpp
class Example {
public:
    static int count;
};

int Example::count = 0;  // Musimy zainicjalizować zmienną statyczną
```

📌 **Zmienne statyczne są współdzielone między wszystkimi obiektami klasy.**

---

#### **📌 `static` w funkcji klasy (funkcja statyczna)**

```cpp
class Example {
public:
    static void sayHello() {
        std::cout << "Hello!\n";
    }
};
```

📌 **Nie ma dostępu do `this`, może być wywoływana bez tworzenia obiektu.**

---

#### **📌 `static` w zmiennej globalnej lub funkcji (ograniczenie zasięgu do pliku)**

```cpp
static int hidden = 42;  // Widoczna tylko w tym pliku
static void helper() {}  // Funkcja tylko dla tego pliku
```

📌 **Zapobiega konfliktom nazw w różnych plikach.**

---

### **2️⃣ `noexcept` – informacja, że funkcja nie rzuca wyjątków**

📌 **`noexcept` jest używane do optymalizacji i zapewnia, że funkcja nie rzuci wyjątku.**

```cpp
void safeFunction() noexcept {
    std::cout << "This function is safe!\n";
}
```

#### **📌 `noexcept` w deklaracji funkcji**

```cpp
int riskyFunction() noexcept(false);  // Może rzucać wyjątki
int safeFunction() noexcept(true);   // Nie rzuca wyjątków
```

📌 **Kompilator może zoptymalizować wywołania `noexcept` – np. nie generować kodu obsługi wyjątków.**

---

#### **📌 `noexcept` w konstruktorze i operatorze przenoszenia**

```cpp
class Example {
public:
    Example(Example&&) noexcept = default; // Optymalizacja dla przenoszenia
};
```

📌 **Gdy konstruktor przenoszenia jest `noexcept`, STL może preferować przenoszenie zamiast kopiowania!**

---

### **3️⃣ `inline` – sugestia dla kompilatora do wstawienia kodu w miejsce wywołania**

📌 **Zmniejsza narzut wywołania funkcji, ale może zwiększyć rozmiar kodu.**

```cpp
inline int square(int x) {
    return x * x;
}
```

📌 **Kompilator może pominąć `inline`, jeśli uzna to za nieopłacalne.**

---

#### **📌 `inline` dla funkcji w plikach nagłówkowych**

📌 Gdy definiujemy funkcję w pliku `.h`, powinna być `inline`, aby uniknąć błędów linkera.

```cpp
// example.h
inline void hello() {
    std::cout << "Hello!\n";
}
```

---

### **4️⃣ `enum` – typ wyliczeniowy**

📌 **Służy do definiowania zestawu stałych.**

```cpp
enum Color { RED, GREEN, BLUE };
Color myColor = RED;
```

📌 **Domyślnie wartości zaczynają się od `0`, ale można je ustawić ręcznie.**

```cpp
enum Status { OK = 200, ERROR = 500 };
```

---

#### **📌 `enum class` – bezpieczniejsza wersja**

```cpp
enum class Status { OK, ERROR };
Status s = Status::OK;  // Trzeba podać `Status::`
```

📌 **Zalecane, bo zapobiega konfliktom nazw.**

---

### **5️⃣ `constexpr` – obliczanie wartości w czasie kompilacji**

📌 **Gdy wartość jest znana w czasie kompilacji, kompilator może wykonać obliczenia wcześniej.**

```cpp
constexpr int square(int x) {
    return x * x;
}

constexpr int result = square(5); // Obliczone w czasie kompilacji!
```

📌 **`constexpr` zapewnia lepszą optymalizację niż `const`.**

---

## Programowanie wielowątkowe

Programowanie wielowątkowe pozwala na **równoczesne wykonywanie kilku wątków** w jednym programie. Dzięki temu możemy zwiększyć wydajność aplikacji, szczególnie w zadaniach wymagających dużych obliczeń lub operacji we/wy.
### **Programowanie Równoległe vs Asynchroniczne (Rozproszone)**

1. **Programowanie Równoległe**:
    
    - **Definicja**: Programowanie równoległe polega na wykonywaniu wielu zadań jednocześnie, wykorzystując wiele rdzeni procesora lub maszyn. Równolegle można wykonywać te same lub różne zadania, np. w przypadku podziału dużego zadania na mniejsze podzadania.

2. **Programowanie Asynchroniczne (Rozproszone)**:
	
	- **Definicja**: Programowanie asynchroniczne koncentruje się na zarządzaniu operacjami, które mogą być wykonywane w tle, ale nie muszą blokować głównego wątku. W programowaniu asynchronicznym operacje są wykonywane równolegle, ale bez potrzeby synchronizacji, ponieważ zakończenie operacji jest sygnalizowane (np. za pomocą `std::future` w C++).

### **Proces vs Wątek**

- **Proces**:
    - **Definicja**: Proces to jednostka wykonawcza w systemie operacyjnym, która ma własną przestrzeń adresową (pamięć, pliki, dane). Każdy proces działa niezależnie od innych procesów.

- **Wątek**:
	- **Definicja**: Wątek to najmniejsza jednostka wykonawcza w ramach procesu. Wątki w tym samym procesie dzielą tę samą przestrzeń adresową, co oznacza, że mogą łatwo współdzielić dane i zasoby, ale również mogą powodować problemy z synchronizacją.

### **1. Wątki w C++**

W C++11 i późniejszych wersjach dostępne jest wsparcie dla wielowątkowości w ramach biblioteki standardowej (STL) w nagłówku **`<thread>`**. Wątki pozwalają na równoległe wykonywanie funkcji w osobnych wątkach.

---

### **2. Tworzenie i uruchamianie wątków**

Do tworzenia wątków używamy klasy `std::thread`, która przyjmuje funkcję lub callable jako argument.

#### **Przykład: Tworzenie wątku**

```cpp
#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(hello); // Tworzenie wątku
    t.join(); // Czekanie na zakończenie wątku
    return 0;
}
```

📌 **`join()`** – czeka na zakończenie wątku.  
📌 **`detach()`** – pozwala na uruchomienie wątku w tle, bez czekania na jego zakończenie.

---

### **3. Przekazywanie argumentów do wątków**

Wątki mogą przyjmować argumenty za pomocą funkcji lub obiektów funkcyjnych (np. lambdy).

#### **Przykład: Przekazywanie argumentów**

```cpp
#include <iostream>
#include <thread>

void printSum(int a, int b) {
    std::cout << "Sum: " << a + b << std::endl;
}

int main() {
    std::thread t(printSum, 5, 10); // Przekazywanie argumentów do wątku
    t.join();
    return 0;
}
```

#### **Przykład: Przekazywanie przez referencję**

```cpp
#include <iostream>
#include <thread>

void increment(int& num) {
    num++;
}

int main() {
    int x = 0;
    std::thread t(increment, std::ref(x)); // Przekazywanie przez referencję
    t.join();
    std::cout << "x: " << x << std::endl; // x powinno wynosić 1
    return 0;
}
```

📌 **`std::ref`** – używamy, aby przekazać argument przez referencję, bo domyślnie wątki kopiują argumenty.

---

### **4. Synchronizacja wątków**

Wielowątkowe programy mogą potrzebować synchronizacji dostępu do wspólnych zasobów, aby uniknąć **wyścigów danych** (data races).

#### **Mutex i Lock**

C++ udostępnia mechanizm **mutex** do blokowania dostępu do zmiennych lub sekcji krytycznych. W standardzie C++11 wprowadzono także `std::lock_guard` i `std::unique_lock` do wygodnej obsługi mutexów.

#### **Przykład: Mutex z `std::lock_guard`**

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex do synchronizacji

void printHello() {
    std::lock_guard<std::mutex> lock(mtx); // Mutex automatycznie zwalniany po zakończeniu
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t1(printHello);
    std::thread t2(printHello);
    
    t1.join();
    t2.join();
    
    return 0;
}
```

#### **Przykład: `std::unique_lock`**

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void printMessage(const std::string& message) {
    std::unique_lock<std::mutex> lock(mtx); // Lock manualny, większa kontrola
    std::cout << message << std::endl;
}

int main() {
    std::thread t1(printMessage, "Message from thread 1");
    std::thread t2(printMessage, "Message from thread 2");
    
    t1.join();
    t2.join();
    
    return 0;
}
```

📌 **`std::lock_guard`** – automatycznie blokuje i odblokowuje mutex.  
📌 **`std::unique_lock`** – daje większą kontrolę nad mutexem (np. możliwość ręcznego odblokowania).

---

### **5. Zmienne warunkowe**

Zmienne warunkowe służą do synchronizacji wątków, np. do czekania na spełnienie określonych warunków.

#### **Przykład: `std::condition_variable`**

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void printHello() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });  // Czeka, aż ready stanie się true
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(printHello);
    
    {
        std::unique_lock<std::mutex> lock(mtx);
        ready = true;  // Zmieniamy stan
    }
    cv.notify_all();  // Powiadamiamy wątki czekające na condition_variable
    
    t.join();
    
    return 0;
}
```

📌 **`std::condition_variable`** pozwala na czekanie na spełnienie warunku, a `notify_all` (lub `notify_one`) powiadamia czekające wątki.

---

### **6. Wątki i wyjątki**

Jeśli wątek zgłosi wyjątek, to jest on przechwytywany przez `std::terminate`, chyba że jest odpowiednio obsłużony. Warto zwrócić uwagę na obsługę wyjątków w kontekście wątków.

#### **Przykład: Obsługa wyjątku w wątku**

```cpp
#include <iostream>
#include <thread>

void throwException() {
    throw std::runtime_error("Something went wrong!");
}

int main() {
    try {
        std::thread t(throwException);
        t.join();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    return 0;
}
```

📌 **Przechwycenie wyjątku w wątku głównym jest konieczne, by uniknąć zakończenia programu.**

---

### **7. Przekazywanie danych między wątkami: promise i future**

#### **std::promise i std::future**

**`std::promise`** i **`std::future`** umożliwiają przekazywanie wyników obliczeń z jednego wątku do drugiego.

```cpp
#include <iostream>
#include <thread>
#include <future>

void calculate(std::promise<int>& p) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Symulacja pracy
    p.set_value(10);  // Ustawienie wartości w obiekcie promise
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();  // Uzyskanie obiektu future
    
    std::thread t(calculate, std::ref(p));  // Przekazywanie promise przez referencję
    t.join();
    
    std::cout << "Result: " << f.get() << std::endl;  // Odczytanie wartości z future
    
    return 0;
}
```

📌 **`std::promise`** pozwala na przekazywanie wartości do wątku głównego lub innego wątku, a **`std::future`** pozwala na pobranie tej wartości.

---

### **8. Asynchroniczne wywołania: std::async**

**`std::async`** pozwala na uruchomienie funkcji asynchronicznie, czyli w tle, i otrzymanie jej wyniku za pomocą obiektu `std::future`.

```cpp
#include <iostream>
#include <future>

int computeSum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> result = std::async(std::launch::async, computeSum, 5, 3);
    
    std::cout << "Result from async: " << result.get() << std::endl;
    
    return 0;
}
```

📌 **`std::async`** uruchamia funkcję asynchronicznie i pozwala na późniejsze uzyskanie wyniku przez **`get()`**.

---

### **9. Execution Policy**

**Execution policy** pozwala na określenie, jak mają być wykonywane algorytmy (np. równolegle lub sekwencyjnie). Jest to przydatne do optymalizacji algorytmów w programach wielowątkowych.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    std::for_each(std::execution::par, vec.begin(), vec.end(), [](int& n) { n *= 2; });
    
    for (int n : vec) {
        std::cout << n << " ";  // Wydrukuje: 2 4 6 8 10
    }
    
    return 0;
}
```

📌 **`std::execution::par`** – mówi kompilatorowi, aby wykonał operację równolegle (wielowątkowo). Można użyć również `std::execution::seq` (sekwencyjnie) lub `std::execution::unseq` (wielowątkowo z SIMD).

---

### **10. Operacje Atomowe**

C++ udostępnia mechanizmy do operacji atomowych, które pozwalają na bezpieczny dostęp do wspólnych zasobów w środowisku wielowątkowym.

```cpp
#include <iostream>
#include <atomic>

std::atomic<int> counter(0);

void increment() {
    counter.fetch_add(1, std::memory_order_relaxed);  // Operacja atomowa
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    std::cout << "Counter: " << counter.load() << std::endl;  // 2
    return 0;
}
```

📌 **`std::atomic`** zapewnia, że operacje na zmiennej będą atomowe, co eliminuje wyścigi danych.

---

### **OpenMP**

**OpenMP** to standard do programowania równoległego na poziomie wielordzeniowych procesorów. Pozwala na łatwe równoleglenie pętli i sekcji kodu za pomocą dyrektyw kompilatora.

```cpp
#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        std::cout << "Thread " << omp_get_thread_num() << " processing " << i << std::endl;
    }
    return 0;
}
```

📌 **`#pragma omp parallel for`** umożliwia równoległe wykonanie pętli.

### **MPI**

**MPI** (Message Passing Interface) to biblioteka do komunikacji między procesami, która jest używana w środowiskach rozproszonych.

---

### **Problemy: Zakleszczenie i Wyścigi Danych**

#### **Zakleszczenie (Deadlock)**

Zakleszczenie występuje, gdy dwa lub więcej wątków blokują się nawzajem, czekając na zasób, który jest zablokowany przez inny wątek.

```cpp
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1, mtx2;

void thread1() {
    mtx1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    mtx2.lock();  // Czeka na mtx2, jeśli mtx2 jest zablokowane przez drugi wątek
    std::cout << "Thread 1 completed!" << std::endl;
    mtx2.unlock();
    mtx1.unlock();
}

void thread2() {
    mtx2.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    mtx1.lock();  // Czeka na mtx1, jeśli mtx1 jest zablokowane przez pierwszy wątek
    std::cout << "Thread 2 completed!" << std::endl;
    mtx1.unlock();
    mtx2.unlock();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();
    
    return 0;
}
```

📌 **Zakleszczenie** – aby go uniknąć, staraj się unikać oczekiwania na zasoby w odwrotnej kolejności.

---

#### **Wyścig Danych (Race Condition)**

Wyścig danych występuje, gdy wątki próbują modyfikować wspólny zasób w tym samym czasie, co prowadzi do nieprzewidywalnych wyników.

```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> count(0);

void increment() {
    for (int i = 0; i < 10000; ++i) {
        count++;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    std::cout << "Count: " << count.load() << std::endl;  // Poprawne, bo atomowe
    return 0;
}
```

📌 **Wyścig danych** – unika się go, używając operacji atomowych, mutexów lub innych mechanizmów synchronizacji.
## Meta-programowanie

Metaprogramowanie w C++ to technika pozwalająca na wykonywanie obliczeń w czasie kompilacji. Główne narzędzia metaprogramowania w C++ to **szablony (templates)**, **decltype**, **concepts**, **typename**, **typedef** i **type traits**.

---
### **1. Templates (Szablony)**

Szablony pozwalają na definiowanie funkcji i klas, które mogą działać na różnych typach danych bez potrzeby ich duplikowania.

#### **1.1 Szablony funkcji**

```cpp
#include <iostream>

// Szablon funkcji
template <typename T>
T max_value(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << max_value(3, 7) << std::endl;     // 7
    std::cout << max_value(4.5, 2.3) << std::endl; // 4.5
    return 0;
}
```

#### **1.2 Szablony klas**

```cpp
#include <iostream>

// Szablon klasy
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() { return value; }
};

int main() {
    Box<int> intBox(10);
    Box<std::string> strBox("Hello");

    std::cout << intBox.get() << std::endl; // 10
    std::cout << strBox.get() << std::endl; // Hello
}
```

#### **1.3 Szablony z wieloma parametrami**

```cpp
template <typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;
public:
    Pair(T1 f, T2 s) : first(f), second(s) {}
    void show() { std::cout << first << ", " << second << std::endl; }
};

int main() {
    Pair<int, double> p(5, 3.14);
    p.show(); // 5, 3.14
}
```

### **Czym jest `value_type` w C++?**

`value_type` to konwencja używana w standardowej bibliotece C++ (STL) do definiowania typu przechowywanego w kolekcjach, iteratorach i szablonach. Jest to szczególnie przydatne w **kontenerach STL**, takich jak `std::vector`, `std::list`, czy `std::map`, oraz w **iteratorach**.

---

### **2. `typename` vs `class` w szablonach**

W kontekście szablonów `typename` i `class` są **równoważne**.

```cpp
template <typename T>
void func(T val) { }

template <class T>
void func2(T val) { }
```

Jednak `typename` jest **wymagane** przy odwoływaniu się do typów zdefiniowanych wewnątrz szablonów:

```cpp
template <typename T>
void func() {
    typename T::value_type x;  // Używamy 'typename', bo kompilator nie wie, czy 'value_type' to typ czy zmienna
}
```

---

### **3. `decltype`**

`decltype` pozwala na określenie typu zmiennej na podstawie wyrażenia.

```cpp
#include <iostream>

int main() {
    int x = 5;
    decltype(x) y = 10; // y jest typu int
    std::cout << y << std::endl; // 10
}
```

Można go również stosować w bardziej skomplikowanych przypadkach:

```cpp
template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    std::cout << add(5, 3.2) << std::endl; // 8.2
}
```

---

### **4. `concepts` (C++20)**

`concepts` pozwalają na bardziej precyzyjne definiowanie szablonów poprzez określanie ograniczeń na typy.

```cpp
#include <iostream>
#include <concepts>

// Definicja konceptu sprawdzającego czy typ wspiera operator <
template <typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

// Funkcja działa tylko dla typów spełniających koncept Comparable
template <Comparable T>
T min_value(T a, T b) {
    return (a < b) ? a : b;
}

int main() {
    std::cout << min_value(3, 7) << std::endl;     // 3
    std::cout << min_value(4.5, 2.3) << std::endl; // 2.3
}
```

Koncepty pozwalają na uniknięcie nieczytelnych błędów kompilatora związanych z szablonami.

---

### **5. `typedef` vs `using`**

W C++98 stosowano `typedef` do definiowania aliasów typów:

```cpp
typedef unsigned int uint;
```

W C++11 wprowadzono `using`, które jest bardziej czytelne i wspiera aliasy dla szablonów:

```cpp
using uint = unsigned int;
```

Aliasowanie szablonów:

```cpp
template <typename T>
using Ptr = T*;

int main() {
    Ptr<int> p; // int*
}
```

### **6. `constexpr` i obliczenia w czasie kompilacji**

Słowo kluczowe `constexpr` pozwala na wykonywanie obliczeń w **czasie kompilacji**, co może poprawić wydajność.

#### **Przykład:**

```cpp
#include <iostream>

// Funkcja obliczana w czasie kompilacji
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

int main() {
    constexpr int result = factorial(5); // 5! = 120, obliczone w czasie kompilacji
    std::cout << result << std::endl;
}
```

Jeśli `constexpr` funkcja otrzyma wartość **nieznaną w czasie kompilacji**, to wykona się w runtime.

---

### **7. `std::enable_if` i SFINAE (Substitution Failure Is Not An Error)**

`std::enable_if` pozwala na wyłączenie pewnych przeciążeń funkcji w zależności od warunków określonych w czasie kompilacji.

#### **Przykład: Wymuszenie, by funkcja działała tylko dla liczb całkowitych**

```cpp
#include <iostream>
#include <type_traits>

// Funkcja działa tylko dla typów całkowitych (int, long, short, itd.)
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type print(T val) {
    std::cout << "Integer: " << val << std::endl;
}

int main() {
    print(10);    // OK
    // print(3.14); // Błąd kompilacji
}
```

📌 **SFINAE (Substitution Failure Is Not An Error)** oznacza, że nieudane dopasowanie szablonu nie powoduje błędu kompilacji.

---

### **8. `type_traits` – introspekcja typów**

Biblioteka `<type_traits>` pozwala na analizowanie i manipulowanie typami w czasie kompilacji.

#### **Najczęściej używane narzędzia:**

|Nazwa|Opis|
|---|---|
|`std::is_integral<T>`|Sprawdza, czy `T` jest typem całkowitym (`int`, `short`, `long` itp.)|
|`std::is_floating_point<T>`|Sprawdza, czy `T` to `float`, `double`, `long double`|
|`std::is_same<T, U>`|Sprawdza, czy `T` i `U` to ten sam typ|
|`std::remove_reference<T>`|Usuwa referencję z typu `T&`|
|`std::remove_pointer<T>`|Usuwa wskaźnik z typu `T*`|

#### **Przykład użycia `type_traits`:**

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
void checkType() {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "T is an integral type" << std::endl;
    } else {
        std::cout << "T is not an integral type" << std::endl;
    }
}

int main() {
    checkType<int>();  // Wyświetli: T is an integral type
    checkType<double>(); // Wyświetli: T is not an integral type
}
```

---

### **9. `std::tuple` i `std::index_sequence` – metaprogramowanie strukturalne**

Szablony umożliwiające operowanie na zestawach typów i indeksach.
#### **Przykład: Odczyt wartości z `std::tuple` w czasie kompilacji**

```cpp
#include <iostream>
#include <tuple>

// Wypisywanie elementów `std::tuple` rekurencyjnie
template <std::size_t Index = 0, typename... Ts>
void print_tuple(const std::tuple<Ts...>& t) {
    if constexpr (Index < sizeof...(Ts)) {
        std::cout << std::get<Index>(t) << " ";
        print_tuple<Index + 1>(t);
    }
}

int main() {
    auto t = std::make_tuple(1, 3.14, "hello");
    print_tuple(t); // 1 3.14 hello
}
```

---

### **10. Variadic Templates (Szablony wariadyczne)**

Pozwalają na przyjmowanie **dowolnej liczby argumentów** w szablonach.
#### **Przykład: Sumowanie wartości**

```cpp
#include <iostream>

// Rekurencyjna funkcja do sumowania dowolnej liczby argumentów
template <typename T, typename... Args>
T sum(T first, Args... rest) {
    return first + sum(rest...);
}

// Przeciążenie dla ostatniego elementu
template <typename T>
T sum(T last) {
    return last;
}

int main() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl; // 15
}
```

---

### **11. CRTP (Curiously Recurring Template Pattern)**

Technika używana do **implementacji polimorfizmu bez kosztów wirtualnych funkcji**.

### **Przykład: Automatyczna konwersja do stringa**

```cpp
#include <iostream>

// Klasa bazowa z CRTP
template <typename Derived>
class Printable {
public:
    void print() const {
        static_cast<const Derived*>(this)->print_impl();
    }
};

// Klasa dziedzicząca
class MyClass : public Printable<MyClass> {
public:
    void print_impl() const {
        std::cout << "Hello from MyClass" << std::endl;
    }
};

int main() {
    MyClass obj;
    obj.print(); // Hello from MyClass
}
```

---


## Programowanie wektorowe

Programowanie wektorowe to technika przetwarzania danych w sposób równoległy przy użyciu instrukcji SIMD (Single Instruction, Multiple Data). Dzięki temu można jednocześnie wykonać tę samą operację na wielu elementach danych, co przyspiesza obliczenia.

### **SIMD (Single Instruction, Multiple Data)**

Instrukcje SIMD pozwalają przetwarzać wiele elementów danych jednocześnie, co jest szczególnie efektywne w operacjach na wektorach liczb.  
Popularne zestawy instrukcji SIMD:

- **SSE** (Streaming SIMD Extensions) – 128-bitowe rejestry
- **AVX** (Advanced Vector Extensions) – 256-bitowe rejestry
- **AVX-512** – 512-bitowe rejestry

### **Przykład: SIMD z użyciem AVX**

```cpp
#include <immintrin.h>
#include <iostream>

void addVectorsAVX(float* a, float* b, float* result, size_t size) {
    for (size_t i = 0; i < size; i += 8) {
        __m256 vecA = _mm256_loadu_ps(&a[i]);   // Załaduj 8 floatów
        __m256 vecB = _mm256_loadu_ps(&b[i]);   // Załaduj 8 floatów
        __m256 vecResult = _mm256_add_ps(vecA, vecB);  // Dodaj wektory
        _mm256_storeu_ps(&result[i], vecResult);  // Zapisz wynik
    }
}

int main() {
    alignas(32) float a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    alignas(32) float b[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    alignas(32) float result[8];

    addVectorsAVX(a, b, result, 8);

    for (float r : result) {
        std::cout << r << " ";
    }
    return 0;
}
```

✅ **Kluczowe operacje:**

- `_mm256_loadu_ps()` – ładuje 8 floatów do rejestru
- `_mm256_add_ps()` – wykonuje dodawanie wektorowe
- `_mm256_storeu_ps()` – zapisuje wynik do pamięci

---

### **Programowanie wektorowe z `std::valarray`**

Standardowa biblioteka C++ oferuje `std::valarray`, który może być używany do wektorowych operacji arytmetycznych.

```cpp
#include <iostream>
#include <valarray>

int main() {
    std::valarray<int> a = {1, 2, 3, 4};
    std::valarray<int> b = {5, 6, 7, 8};

    std::valarray<int> result = a + b;  // Wektorowe dodawanie

    for (int x : result) {
        std::cout << x << " ";
    }
    return 0;
}
```

✅ `std::valarray` automatycznie wektoryzuje operacje, co może poprawić wydajność.

---

### **`std::execution::par_unseq` i równoległe algorytmy STL**

Od C++17 można używać `std::execution::par_unseq` do optymalizacji operacji wektorowych.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> vec(1000000, 1);
    
    // Równoległe zwiększenie wartości
    std::for_each(std::execution::par_unseq, vec.begin(), vec.end(),
                  [](int& x) { x += 1; });

    std::cout << "Gotowe! Przykładowa wartość: " << vec[0] << std::endl;
    return 0;
}
```

✅ `std::execution::par_unseq` pozwala kompilatorowi użyć SIMD i wielowątkowości.

---

### **OpenMP dla programowania wektorowego**

OpenMP wspiera **pragma omp simd**, co wymusza wektoryzację pętli.

```cpp
#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int N = 100000;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), result(N);

    #pragma omp parallel for simd
    for (int i = 0; i < N; ++i) {
        result[i] = a[i] + b[i];
    }

    std::cout << "Przykładowa wartość: " << result[0] << std::endl;
    return 0;
}
```

✅ **`#pragma omp simd`** wymusza wektoryzację.
## Polecenia do prekompilatora

### **1. `#include` – Dołączanie plików nagłówkowych**

📌 **Zastosowanie**: Włącza kod z innego pliku (np. standardowe biblioteki, własne nagłówki).  
📌 **Przykład**:

```cpp
#include <iostream> // Standardowa biblioteka
#include "myheader.h" // Własny plik nagłówkowy
```

✅ **Unikaj** wielokrotnego dołączania tego samego pliku, używając **`#pragma once`** lub **strażników nagłówkowych**.

---

### **2. `#define` – Makra i stałe preprocesora**

📌 **Zastosowanie**: Tworzenie stałych lub prostych makr.  
📌 **Przykład**:

```cpp
#define PI 3.14159
#define SQUARE(x) ((x) * (x))
```

❌ **Niebezpieczeństwo**: Makra nie mają kontroli typów, lepiej używać `constexpr` lub `const`.

---

### **3. `#pragma once` – Strażnik nagłówka**

📌 **Zastosowanie**: Zapobiega wielokrotnemu dołączaniu tego samego pliku nagłówkowego.  
📌 **Przykład** _(zalecane rozwiązanie)_:

```cpp
#pragma once
class MyClass {};
```

🔹 Alternatywa: **Strażniki nagłówkowe**:

```cpp
#ifndef MYHEADER_H
#define MYHEADER_H
// Kod nagłówka
#endif
```

---

### **4. `#ifdef`, `#ifndef`, `#if`, `#else`, `#elif`, `#endif` – Kompilacja warunkowa**

📌 **Zastosowanie**: Włączanie kodu tylko, jeśli spełniony jest określony warunek.

📌 **Przykład – sprawdzenie, czy stała jest zdefiniowana**:

```cpp
#ifdef DEBUG
    std::cout << "Tryb debugowania włączony!\n";
#endif
```

📌 **Przykład – obsługa różnych systemów operacyjnych**:

```cpp
#ifdef _WIN32
    std::cout << "Windows\n";
#elif __linux__
    std::cout << "Linux\n";
#endif
```

✅ **Przydatne do**: Debugowania, konfiguracji dla różnych systemów.

---

### **5. `#undef` – Usunięcie wcześniejszej definicji makra**

📌 **Zastosowanie**: Pozwala usunąć wcześniej zdefiniowane makro i zdefiniować je na nowo.

```cpp
#define DEBUG
#undef DEBUG
```

---

### **6. `#error` – Generowanie błędu podczas kompilacji**

📌 **Zastosowanie**: Wymusza błąd kompilacji, np. jeśli brakuje wymaganej definicji.

```cpp
#ifndef CONFIG_DEFINED
#error "Brak konfiguracji! Zdefiniuj CONFIG_DEFINED."
#endif
```

---

### **7. `#line` – Manipulacja numerami linii**

📌 **Zastosowanie**: Możemy zmienić numer linii i plik, co może pomóc w debugowaniu.

```cpp
#line 100 "fakefile.cpp"
```

✅ **Efekt**: Kompilator uważa, że kolejna linia kodu znajduje się w `fakefile.cpp` w linii 100.

---

### **8. `#pragma` – Specjalne polecenia dla kompilatora**

📌 **Zastosowanie**: Specyficzne dla kompilatora ustawienia, np. optymalizacje.

📌 **Przykład – wyłączanie ostrzeżeń w MSVC**:

```cpp
#pragma warning(disable : 4996) // Wyłącza ostrzeżenie 4996
```

📌 **Przykład – wyrównanie pamięci**:

```cpp
#pragma pack(push, 1) // Wyrównanie struktury do 1 bajta
struct MyStruct { char a; int b; };
#pragma pack(pop)
```

---







