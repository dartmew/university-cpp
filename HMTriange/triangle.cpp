#include <iostream>
#include <cmath>
#include <iomanip>

int main(){
    float xa, ya, xb, yb, xc, yc;
    std::cout << "Введите xa:" << std::endl;
    std::cin >> xa;
    std::cout << "Введите ya:" << std::endl;
    std::cin >> ya;
    std::cout << "Введите xb:" << std::endl;
    std::cin >> xb;
    std::cout << "Введите yb:" << std::endl;
    std::cin >> yb;
    std::cout << "Введите xc:" << std::endl;
    std::cin >> xc;
    std::cout << "Введите yc:" << std::endl;
    std::cin >> yc;

    float ab = sqrt(pow((xb-xa),2) + pow((yb-ya),2));
    float bc = sqrt(pow((xc-xb),2) + pow((yc-yb),2));;
    float ca = sqrt(pow((xa-xc),2) + pow((ya-yc),2));;

    if (ab + bc <= ca || ab + ca <= bc || bc + ca <= ab){
        std::cout << "Треугольник не существует" << std::endl;
        return 1;
    }

    float p = ab + bc + ca;

    float hp = p / 2;
    float s = sqrt(hp*(hp-ab)*(hp-bc)*(hp-ca));


    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Площадь треугольника: " << s << std::endl;
    std::cout << "Периметр треугольника: " << p << std::endl;

    return 0;
}