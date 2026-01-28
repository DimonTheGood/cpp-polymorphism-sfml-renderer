#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

class Shape{
public:
    virtual double calculate_area() const = 0;
    virtual double calculate_perimetr() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape{
private:
    double W;
    double H;
public:
    Rectangle(const double w, const double h) : 
        W(w), H(h)  {}
    double calculate_area() const override {
        return W * H;
    }
    double calculate_perimetr() const override {
        return W + W + H + H;
    }
    void draw() const override{
        std::cout << "rect done" << "\n";
    }
    ~Rectangle() override = default; 
};

class Triangle : public Shape{
private:
    std::pair<double, double> p1;
    std::pair<double, double> p2;
    std::pair<double, double> p3;

    double a1;
    double a2;
    double a3;
public:
    Triangle(const std::pair<double, double> p1, const std::pair<double, double> p2, const std::pair<double, double> p3) : 
        p1(p1), p2(p2), p3(p3) {
            a1 = sqrt(pow((p2.second - p1.second), 2) + pow((p2.first - p1.first), 2));
            a2 = sqrt(pow((p3.second - p1.second), 2) + pow((p3.first - p1.first), 2));
            a3 = sqrt(pow((p2.second - p3.second), 2) + pow((p2.first - p3.first), 2));
        }
    double calculate_area() const override{
        double pp = (a1 + a2 + a3) / 2;
        return sqrt(pp * (pp - a1) * (pp - a2) * (pp - a3));
    }
    double calculate_perimetr() const override{
        return a1 + a2 + a3;
    }
    void draw() const override{
        std::cout << "done triangle" << "\n";
    }
    ~Triangle() override = default;
};

class Circle : public Shape {
private:
    double r;
public:
    Circle(const double R) 
        : r(R){}
    double calculate_area() const override{
        return 3.14 * r * r;
    }
    double calculate_perimetr() const override{
        return 2 * 3.14 * r;
    }
    void draw() const override{
        std::cout << "done circle" << "\n";
    }
    ~Circle() override = default;
};

sf::VertexArray create_line(const sf::Vector2f& p1, const sf::Vector2f& p2, sf::Color color = sf::Color::White){
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = p1;
    line[0].color = color;
    line[1].position = p2;
    line[1].color = color;
    return line;
}

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simle Figure Render!");
    std::vector<Shape*> shapes;
    bool is_rectangle = 0;
    bool is_triangle = 0;
    double x_p = -1;
    double y_p = -1;
    double x_r = -1;
    double y_r = -1;
    double center_x = -1;
    double center_y = -1;
    sf::VertexArray line1;
    sf::VertexArray line2;
    sf::VertexArray line3;
    sf::VertexArray line4;
    sf::VertexArray line1t;
    sf::VertexArray line2t;
    sf::VertexArray line3t;
    double r = -1; 
    bool f = 0;
    bool f2 = 0;
    bool is_circle = 0;
    bool is_drawing = 0;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }   
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space){
                    is_drawing = 0;
                    window.clear(sf::Color::Black);
                }
            }
            if(event.type == sf::Event::MouseButtonPressed){
                std::cout << "Pressed" << std::endl;
                if(event.mouseButton.button == sf::Mouse::Left){
                    is_rectangle = 1;
                    std::cout << "left" << std::endl;
                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    is_triangle = 1;
                    std::cout << "right" << std::endl;
                }
                if(event.mouseButton.button == sf::Mouse::Middle){
                    is_circle = 1;
                    std::cout << "circle" << std::endl;
                }
                x_p = event.mouseButton.x;
                y_p = event.mouseButton.y;
            }
            if(event.type == sf::Event::MouseButtonReleased){
                std::cout << "released" << " " << is_rectangle << std::endl;
                x_r = event.mouseButton.x;
                y_r = event.mouseButton.y;
                is_drawing = 1;
                if(is_rectangle){
                    std::cout << "rectangle" << std::endl;
                    double h = abs(y_r - y_p);
                    double w = abs(x_r - x_p);
                    shapes.push_back(new Rectangle(w, h));
                    sf::Vector2f p1(static_cast<float>(x_p), static_cast<float>(y_p));
                    sf::Vector2f p2(static_cast<float>(x_p), static_cast<float>(y_r));
                    sf::Vector2f p3(static_cast<float>(x_r), static_cast<float>(y_r));
                    sf::Vector2f p4(static_cast<float>(x_r), static_cast<float>(y_p));
                    line1 = create_line(p1, p2);
                    line2 = create_line(p1, p4);
                    line3 = create_line(p2, p3);
                    line4 = create_line(p4, p3);
                }
                if(is_triangle){
                    std::cout << "Triangle" << std::endl;
                    std::pair<double, double> p11 = {x_p, y_p};
                    std::pair<double, double> p22 = {x_r, y_p};
                    std::pair<double, double> p33 = {x_r / 2, y_r};
                    shapes.push_back(new Triangle(p11, p22, p33));
                    sf::Vector2f p1(static_cast<float>(x_p), static_cast<float>(y_p));
                    sf::Vector2f p2(static_cast<float>(x_r), static_cast<float>(y_p));
                    sf::Vector2f p3(static_cast<float>(x_r / 2), static_cast<float>(y_r));
                    line1t = create_line(p1, p3);
                    line2t = create_line(p1, p2);
                    line3t = create_line(p2, p3);
                }
                if(is_circle){
                    std::cout << "Circle" << std::endl;
                    r = sqrt(pow(y_p - y_r,2) + pow(x_p - x_r, 2));
                    shapes.push_back(new Circle(r));
                    center_x = x_p;
                    center_y = y_p;
                }
                is_circle = 0;
                is_rectangle = 0;
                is_triangle = 0;
            }
        }
        if(!f){
            window.clear(sf::Color::Black);
            f = 1;
        }
        if(is_drawing){
            window.draw(line1);
            window.draw(line2);
            window.draw(line3);
            window.draw(line4);
            window.draw(line1t);
            window.draw(line2t);
            window.draw(line3t);
            int segments = 30; 
            float angleStep = 2 * 3.14159f / segments;
            for(int i = 0; i < segments; i++) {
                float angle1 = i * angleStep;
                float angle2 = (i + 1) * angleStep;
                sf::VertexArray segment(sf::Lines, 2);
                segment[0].position = sf::Vector2f(
                    center_x + r * cos(angle1),
                    center_y + r * sin(angle1)
                );
                segment[1].position = sf::Vector2f(
                    center_x + r * cos(angle2),
                    center_y + r * sin(angle2)
                );
                window.draw(segment);
            }
        }
        window.display();
    }
    return 0;
}