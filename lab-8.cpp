#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Shape {
protected:
    string name;
    static int objectCount; // 1. Статик хувьсагч
public:
    Shape(string n) : name(n) {
        objectCount++; // Объект тоолно
    }

    virtual void display() const = 0;
    virtual double getArea() const = 0;
    static int getObjectCount() { return objectCount; } // 2. Статик функц
};

int Shape::objectCount = 0; // 2. Гадаа утга оноох

class Shape2D : public Shape {
protected:
    double area, perimeter;
public:
    Shape2D(string n) : Shape(n), area(0), perimeter(0) {}
    virtual double getPerimeter() const = 0;
};

class Circle : public Shape2D {
private:
    double center[2];
    double radius;
public:
    Circle(string n, double cx, double cy, double r) : Shape2D(n), radius(r) {
        this->center[0] = cx;
        this->center[1] = cy;
    }

    double getArea() const override {
        return M_PI * this->radius * this->radius;
    }

    double getPerimeter() const override {
        return 2 * M_PI * this->radius;
    }

    void display() const override {
        cout << "Тойрог: " << this->name << "\n";
        cout << "Төв: (" << this->center[0] << ", " << this->center[1] << ")\n";
        cout << "Радиус: " << this->radius << "\n";
        cout << "Талбай: " << this->getArea() << ", Урт: " << this->getPerimeter() << "\n\n";
    }
};

class Square : public Shape2D {
private:
    vector<pair<double, double>> oroi;
    double side;
public:
    Square(string n, double topX, double topY, double s) : Shape2D(n), side(s) {
        this->oroi.push_back({topX, topY});
        this->oroi.push_back({topX + s, topY});
        this->oroi.push_back({topX, topY - s});
        this->oroi.push_back({topX + s, topY - s});
    }

    double getArea() const override {
        return this->side * this->side;
    }

    double getPerimeter() const override {
        return 4 * this->side;
    }

    void display() const override {
        cout << "Квадрат: " << this->name << "\n";
        cout << "Оройнууд:\n";
        cout << "  (" << this->oroi[0].first << ", " << this->oroi[0].second << ") (Зүүн дээд)\n";
        cout << "  (" << this->oroi[1].first << ", " << this->oroi[1].second << ") (Баруун дээд)\n";
        cout << "  (" << this->oroi[2].first << ", " << this->oroi[2].second << ") (Зүүн доод)\n";
        cout << "  (" << this->oroi[3].first << ", " << this->oroi[3].second << ") (Баруун доод)\n";
        cout << "Талын урт: " << this->side << "\n";
        cout << "Талбай: " << this->getArea() << ", Периметр: " << this->getPerimeter() << "\n\n";
    }
};

class Triangle : public Shape2D {
private:
    vector<pair<double, double>> oroi;
    double side;
public:
    Triangle(string n, double topX, double topY, double s) : Shape2D(n), side(s) {
        this->oroi.push_back({topX, topY});
        this->oroi.push_back({topX - (s/2), topY - (sqrt(3)/2 * s)});
        this->oroi.push_back({topX + (s/2), topY - (sqrt(3)/2 * s)});
    }

    double getArea() const override {
        return (sqrt(3) / 4) * this->side * this->side;
    }

    double getPerimeter() const override {
        return 3 * this->side;
    }

    void display() const override {
        cout << "Зөв гурвалжин: " << this->name << "\n";
        cout << "Оройнууд:\n";
        cout << "  (" << this->oroi[0].first << ", " << this->oroi[0].second << ") (Дээд)\n";
        cout << "  (" << this->oroi[1].first << ", " << this->oroi[1].second << ") (Зүүн доод)\n";
        cout << "  (" << this->oroi[2].first << ", " << this->oroi[2].second << ") (Баруун доод)\n";
        cout << "Талын урт: " << this->side << "\n";
        cout << "Талбай: " << this->getArea() << ", Периметр: " << this->getPerimeter() << "\n\n";
    }
};

// Талбайгаар эрэмбэлэх функц
bool compareByArea(const Shape* a, const Shape* b) {
    return a->getArea() < b->getArea();
}

// Приметерээр эрэмбэлэх функц (хүсвэл хэрэглэж болно)
bool compareByPerimeter(const Shape* a, const Shape* b) {
    return a->getPerimeter() < b->getPerimeter();
}

int main() {
    vector<Shape*> shapes;
    int shapeCount;

    cout << "Хэдэн дүрс үүсгэх вэ? ";
    cin >> shapeCount;

    for (int i = 0; i < shapeCount; i++) {
        string shapeType, name;
        double x, y, size;

        cout << "\nДүрсийн төрөл (circle/square/triangle): ";
        cin >> shapeType;
        cout << "Дүрсийн нэр: ";
        cin >> name;

        if (shapeType == "circle") {
            cout << "Тойргийн төвийн координат (x y): ";
            cin >> x >> y;
            cout << "Радиус: ";
            cin >> size;
            shapes.push_back(new Circle(name, x, y, size));
        }
        else if (shapeType == "square") {
            cout << "Квадратын зүүн дээд оройн координат (x y): ";
            cin >> x >> y;
            cout << "Талын урт: ";
            cin >> size;
            shapes.push_back(new Square(name, x, y, size));
        }
        else if (shapeType == "triangle") {
            cout << "Гурвалжны дээд оройн координат (x y): ";
            cin >> x >> y;
            cout << "Талын урт: ";
            cin >> size;
            shapes.push_back(new Triangle(name, x, y, size));
        }
        else {
            cout << "Буруу төрөл! Дахин оролдоно уу.\n";
            i--;
        }
    }

    // Талбайгаар эрэмбэлэх
    sort(shapes.begin(), shapes.end(), compareByArea);

    // Хэвлэх
    cout << "\nТалбайгаар эрэмбэлэгдсэн дүрсүүд:\n";
    for (const auto& shape : shapes) {
        shape->display();
    }

    cout << "Нийт үүссэн объектын тоо: " << Shape::getObjectCount() << "\n";

    // Санах ой чөлөөлөх
    for (auto shape : shapes) {
        delete shape;
    }

    return 0;
}
