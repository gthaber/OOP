
#ifndef PROCEDURAL_FIGURE_H
#define PROCEDURAL_FIGURE_H
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

namespace figure_space {

    bool read_int(int &buffer, std::ifstream &ifstr);

    const double pi = 3.1415;

    // Параметры, общие для всех альтернатив:
    // Цвет фигуры (перечислимый тип)
    // {красный, оранжевый, желтый, зеленый, голубой, синий, фиолетовый}
    enum color {
        RED = 0,
        ORANGE = 1,
        YELLOW = 2,
        GREEN = 3,
        BLUE = 4,
        SAPPHIRE = 5,
        PURPLE = 6
    };


    // Перечисляемый тип, определяющий тип фигуры
    enum e_figure {
        CIRCLE = 1,
        RECTANGLE = 2,
        TRIANGLE = 3
    };

    // Структура, объединяющая все виды фигур
    class figure {
    public:
        // Статический метод (static) - можно вызвать без создания объекта (как функцию)
        // Считывает один объект figure и возвращает указатель на него
        static figure *read_one(std::ifstream &ifstr);
        // Компаратор для сортировки
        static bool comparator(figure*first, figure*second);
        // Виртуальный метод "virtual" - требует от потомков переопределения этого метода
        // Чисто виртуальный "pure virtual" (= 0) - помимо необходимости переопределения не может быть определен в предке
        // Считывает уникальные свойства в объект
        virtual bool read(std::ifstream &ifstr) = 0;
        // Выводит уникальные свойства объекта
        virtual void write(std::ofstream &ofstr) = 0;
        // Вычисление периметра для каждой из фигур (действительное число)
        virtual double calculate() = 0;


        virtual void multi_method(figure *other, std::ofstream &ofst) = 0;
        virtual void multi_cycle(std::ofstream &ofst) = 0;
        virtual void multi_rect(std::ofstream &ofst) = 0;
        virtual void multi_triangle(std::ofstream &ofst) = 0;

        // gets
        color get_color();
        double get_density();

        // sets
        void set_color(color _color);
        e_figure type;
        void set_density(double _density);
    private:
        double density; // Плотность материала, из которого вырезаются эти геометрические фигуры (действительное число)
        color figure_color; // Цвет
    };

    // Структура, описывающая круг
    class figure_circle : public figure {
    public:
        // Переопределяем методы предка
        bool read(std::ifstream &ifstr) override;
        void write(std::ofstream &ofstr) override;
        double calculate() override;

        void multi_method(figure *other, std::ofstream &ofst);
        void multi_cycle(std::ofstream &ofst);
        void multi_rect(std::ofstream &ofst);
        void multi_triangle(std::ofstream &ofst);
        // Координаты центра (целочисленные)
        int center_x;
        int center_y;
        // Радиус
        double radius;
    };

    // Структура, описывающая прямоугольник
    class figure_rectangle : public figure {
    public:
        // Переопределяем методы предка
        bool read(std::ifstream &ifstr) override;
        void write(std::ofstream &ofstr) override;
        double calculate() override;

        void multi_method(figure *other, std::ofstream &ofst);
        void multi_cycle(std::ofstream &ofst);
        void multi_rect(std::ofstream &ofst);
        void multi_triangle(std::ofstream &ofst);
        // Координаты левого верхнего угла (целочисленные)
        int upper_x;
        int upper_y;
        // Координаты нижнего правого угла (целочисленные)
        int bottom_x;
        int bottom_y;
    };

    // Элемент контейнера
    class container_node {
    public:
        figure *_f;
        container_node *next = nullptr; // Следующий элемент в списке
    };

    // Структура, описывающая треугольник
    class figure_triangle : public figure {
    public:
        // Переопределяем методы предка
        bool read(std::ifstream &ifstr) override;
        void write(std::ofstream &ofstr) override;
        double calculate() override;

        void multi_method(figure *other, std::ofstream &ofst);
        void multi_cycle(std::ofstream &ofst);
        void multi_rect(std::ofstream &ofst);
        void multi_triangle(std::ofstream &ofst);
        // Три точки, задающие целочисленные координаты вершин
        int x1, y1;
        int x2, y2;
        int x3, y3;
    };

    // Контейнер на основе однонаправленного линейного списка.
    // В списке находятся элементы, каждый из них (кроме последнего) имеет ссылку на следующего.
    class figure_container {
    public:
        // Конструктор контейнера
        figure_container();
        // Сортировка
        void sort();
        // Очистка контейнер
        void clear();
        // Добавление элемента в контейнер
        void append(container_node *new_element);
        // Чтение из файла
        void read(std::ifstream &ifstr);
        // Вывод в файл
        void write(std::ofstream &ofstr);
        void write_ignore(std::ofstream &ofstr, e_figure type);
        container_node *get_begin();
        int get_size();

        void multi_m(std::ofstream &ofst);
    private:
        // Начальный элемент
        container_node *begin;
        // Последний элемент
        container_node *end;
    };

}

#endif //PROCEDURAL_FIGURE_H
