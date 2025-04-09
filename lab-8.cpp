#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Shape {
protected:
    string name;
public:
    Shape(string n) : name(n) {}
    virtual void display() const = 0;
    virtual double getArea() const = 0;
};

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
        center[0] = cx;
        center[1] = cy;
    }

    double getArea() const override {
        return M_PI * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }

    void display() const override {
        cout << "Тойрог: " << name << "\n";
        cout << "Төв: (" << center[0] << ", " << center[1] << ")\n";
        cout << "Радиус: " << radius << "\n";
        cout << "Талбай: " << getArea() << ", Урт: " << getPerimeter() << "\n\n";
    }
};

class Square : public Shape2D {
private:
    vector<pair<double, double>> oroi;
    double side;
public:
    Square(string n, double topX, double topY, double s) : Shape2D(n), side(s) {
        oroi.push_back({topX, topY});
        oroi.push_back({topX + side, topY});
        oroi.push_back({topX, topY - side});
        oroi.push_back({topX + side, topY - side});
    }

    double getArea() const override {
        return side * side;
    }

    double getPerimeter() const override {
        return 4 * side;
    }

    void display() const override {
        cout << "Квадрат: " << name << "\n";
        cout << "Оройнууд:\n";
        cout << "  (" << oroi[0].first << ", " << oroi[0].second << ") (Зүүн дээд)\n";
        cout << "  (" << oroi[1].first << ", " << oroi[1].second << ") (Баруун дээд)\n";
        cout << "  (" << oroi[2].first << ", " << oroi[2].second << ") (Зүүн доод)\n";
        cout << "  (" << oroi[3].first << ", " << oroi[3].second << ") (Баруун доод)\n";
        cout << "Талын урт: " << side << "\n";
        cout << "Талбай: " << getArea() << ", Периметр: " << getPerimeter() << "\n\n";
    }
};

class Triangle : public Shape2D {
private:
    vector<pair<double, double>> oroi;
    double side;
public:
    Triangle(string n, double topX, double topY, double s) : Shape2D(n), side(s) {
        oroi.push_back({topX, topY});
        oroi.push_back({topX - (side/2), topY - (sqrt(3)/2 * side)});
        oroi.push_back({topX + (side/2), topY - (sqrt(3)/2 * side)});
    }

    double getArea() const override {
        return (sqrt(3) / 4) * side * side;
    }

    double getPerimeter() const override {
        return 3 * side;
    }

    void display() const override {
        cout << "Зөв гурвалжин: " << name << "\n";
        cout << "Оройнууд:\n";
        cout << "  (" << oroi[0].first << ", " << oroi[0].second << ") (Дээд)\n";
        cout << "  (" << oroi[1].first << ", " << oroi[1].second << ") (Зүүн доод)\n";
        cout << "  (" << oroi[2].first << ", " << oroi[2].second << ") (Баруун доод)\n";
        cout << "Талын урт: " << side << "\n";
        cout << "Талбай: " << getArea() << ", Периметр: " << getPerimeter() << "\n\n";
    }
};

bool compareByArea(const Shape* a, const Shape* b) {
    return a->getArea() < b->getArea();
}

int main() {
    vector<Shape*> shapes; // shapes нэртэй динамик хүснэгт үүсгэж объектуудыг хадгална
    int shapeCount;

    cout << "Хэдэн дүрс үүсгэх вэ?";
    cin >> shapeCount;

    // Хэрэглэгчээс дүрсүүдийн мэдээлэл авах
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
    cout << "Uussen dursiin too: " << shapeCount;
    // Талбайгаар эрэмбэлэх
    sort(shapes.begin(), shapes.end(), compareByArea);

    // Эрэмбэлэгдсэн дүрсүүдийг хэвлэх
    cout << "\nТалбайгаар эрэмбэлэгдсэн дүрсүүд:\n";
    for (const auto& shape : shapes) {
        shape->display();
    }

    // Санах ойг чөлөөлөх
    for (auto shape : shapes) {
        delete shape;
    }

    return 0;
}
