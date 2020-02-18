#include <stdlib.h>
#include <iostream>
using namespace std;                                                                                    //разрешить доступ к стандартному пространству имен

class Heap {
    private:
        int size;                                                                                       // размер кучи
    public:
        Heap(int s) : size(s) {};                                                                       // инициализация кучи
                                                                                                        // запрос размера и выбор предметов из кучи
        int get(int n = 0) { size -= n; return(size); };
};                                                                                                      // Heap
                                                                                                        // базовый класс игрока
class Gambler {
    protected:
        Heap* heap;                                                                                     // адрес кучи
        const int limit;                                                                                // предел выборки за 1 ход
        const char* name;                                                                               // имя игрока
    public:
        Gambler(Heap& h, int l) : limit(l) { heap = &h; };                                              // инициализация данных
        virtual int move() = 0;                                                                         // чистая виртуальная функция хода
        int query();                                                                                    // запрос хода
};                                                                                                      // Gambler
                                                                                                        // класс человека
class Man : public Gambler {
    public:
        Man(Heap& h, int l, const char* n) : Gambler(h, l) { name = n; };
        int move();                                                                                      // ход человека
};                                                                                                       // Man
                                                                                                         // класс копьютера
class Pen : public Gambler {
    public:
        Pen(Heap& h, int l, const char* n) : Gambler(h, l) { name = n; };
        int move();                                                                                      // ход копьютера
};                                                                                                       // Pen
                                                                                                         // метод запроса хода
int Gambler::query() {
    cout << "Heap = " << heap->get() << " " << name << " > ";
    return(heap->get());                                                                                 // возврат размера кучи
}                                                                                                        // query()
                                                                                                         // метод хода человека
int Man::move() {
    int g;                                                                                               // число выбранных предметов из кучи
    cin >> g;                                                                                            // ввод числа выбранных предметов
                                                                                                         // анализ числа выбранных предметов
    if((g < 1) || (g > (heap->get())) || (g > limit))
        g = 1;
                                                                                                         // выбор предметов из кучи с возвратом ее размера
    return(heap->get(g));
}                                                                                                        // Man::move()
                                                                                                         // метод хода компьютера
int Pen::move() {
    int rest = 0;                                                                                        // остаток кучи
    int x = 0;                                                                                           // параметр выбора
    int h;                                                                                               // текущий размер кучи
    if((h = heap->get()) == 1)
    {
        h = heap->get(1);
        cout << 1 << "\n";
    }                                                                                                    // подбор выигрышного остатка кучи
    else{
        while((rest = (x *limit + x + 1)) < h)
             x ++;
        if((rest > h) || (rest == h))
            rest = (x - 1)*limit + x;
        if((h-rest)>limit)
            rest=h-limit;
        heap->get(h - rest);                                                                             // выбор предметов из кучи;                                                                                                    
        cout << h - rest << "\n";   
    }                                                                                                    // вывод хода компьютера
    return(heap->get());                                                                                 // возврат текущего размера кучи
}                                                                                                        // Pen::move()
                                                                                                         // основная функция
int main(int argc, char* argv[]) {
    int i = 0;                                                                                           // индекс игрока
    Heap h(atoi(argv[1]));                                                                               // инициализация кучи
                                                                                                         // инициализация и адресация игроков
    Gambler* g[] = { new Pen(h, atoi(argv[2]), "Pen"),
                     new Man(h, atoi(argv[2]), "Man")
                   };
                   
    if((atoi(argv[2])<1)||(atoi(argv[1])<(atoi(argv[2]))))
       exit(1);
                                                                                                         // реализация партии игры
    while(g[i]->query() != 0) {
        g[i]->move();
        if(++i > 1)
            i = 0;
    }
                                                                                                         // идентификация победителя
    cout << "Winner\n";
                                                                                                         // освобождение памяти игроков
    //delete g[0];
    //delete g[1];
    return(0);                                                                                           // корректное завершение программы
}


