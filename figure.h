
#ifndef PROCEDURAL_FIGURE_H
#define PROCEDURAL_FIGURE_H
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

namespace figure_space {

    const double PI = 3.1516;

    // Параметры, общие для всех альтернатив:
    // Цвет фигуры (перечислимый тип)
    // {красный, оранжевый, желтый, зеленый, голубой, синий, фиолетовый}
    enum Color {
        RED = 0,
        ORANGE = 1,
        YELLOW = 2,
        GREEN = 3,
        BLUE = 4,
        SAPPHIRE = 5,
        PURPLE = 6
    };


    // Перечисляемый тип, определяющий тип фигуры
    enum eFigure {
        CIRCLE = 1,
        RECTANGLE = 2
    };

    // Структура, объединяющая все виды фигур
    class figure {
    public:
        // Статический метод (static) - можно вызвать без создания объекта (как функцию)
        // Считывает один объект figure и возвращает указатель на него
        static figure *read_one(std::ifstream &ifstr);
        // Виртуальный метод "virtual" - требует от потомков переопределения этого метода
        // Чисто виртуальный "pure virtual" (= 0) - помимо необходимости переопределения не может быть определен в предке
        // Считывает уникальные свойства в объект
        virtual void read(std::ifstream &ifstr) = 0;
        // Выводит уникальные свойства объекта
        virtual void write(std::ofstream &ofstr) = 0;
        // Вычисление периметра для каждой из фигур (действительное число)
        virtual double calculate() = 0;

        // gets
        Color get_color();

        // sets
        void set_color(Color _color);
        eFigure type;
    private:
        Color figure_color; // Цвет
    };

    // Структура, описывающая круг
    class figure_circle : public figure {
    public:
        // Переопределяем методы предка
        void read(std::ifstream &ifstr) override;
        void write(std::ofstream &ofstr) override;
        double calculate() override;
    private:
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
        void read(std::ifstream &ifstr) override;
        void write(std::ofstream &ofstr) override;
        double calculate() override;
    private:
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
        figure* _f;
        container_node *next = nullptr; // Следующий элемент в списке
    };

    // Контейнер на основе однонаправленного линейного списка.
    // В списке находятся элементы, каждый из них (кроме последнего) имеет ссылку на следующего.
    class figure_container {
    public:
        // Конструктор контейнера
        figure_container();
        // Очистка контейнер
        void clear();
        // Добавление элемента в контейнер
        void append(container_node *new_element);
        // Чтение из файла
        void read(std::ifstream &ifstr);
        // Вывод в файл
        void write(std::ofstream &ofstr);
        void writeIgnore(std::ofstream &ofstr, eFigure type);
    private:
        // Начальный элемент
        container_node *begin;
        // Последний элемент
        container_node *end;
    };

    /// Объявление функций:
}

#endif //PROCEDURAL_FIGURE_H
