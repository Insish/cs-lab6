#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;


class Point
{
protected:
    int x;
    int y;

public:
    Point(int x, int y) : x(x), y(y) {}

    //віртуальна функція для відображення точки
    virtual void draw(char symbol) const
    {
        GoToXY(x, y);
    }

    //курсор в точку (x,y)
    static void GoToXY(short x, short y)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hStdOut, { x, y });
    }

    //щоб скрити курсор
    static void ConsoleCursorVisible(bool show, short size)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
        structCursorInfo.bVisible = show;
        structCursorInfo.dwSize = size;
        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
    }

};


class Sphere : public Point
{
private:
    bool mode = false;
    int radius;

public:
    Sphere(int x, int y, int radius) : Point(x, y), radius(radius) {}

    void sphereDrawing()
    {
        system("cls");

        //координати верхнього лівого кута області для виведення сфери
        int leftCornerX = x - radius;
        int leftCornerY = y - radius;

        GoToXY(leftCornerX, leftCornerY);

        for (int i = -radius; i <= radius; i++)
        {
            GoToXY(leftCornerX, leftCornerY++);
            for (int j = -radius; j <= radius; j++)
            {
                float distance = sqrt((i) * (i)+(j) * (j));

                if (distance <= radius)
                {
                    cout << (mode ? "0" : "*") << " ";
                }
                else
                {
                    cout << "  ";
                }
            }
            cout << endl;
        }
        draw(' '); //вивести координати і радіус
    }

    void movement()
    {
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                switch (ch)
                {
                case 72: //стрілка вгору
                    y--;
                    break;
                case 80: //стрілка вниз
                    y++;
                    break;
                case 75: //стрілка вліво
                    x--;
                    break;
                case 77: //стрілка вправо
                    x++;
                    break;
                }
                sphereDrawing();
            }

            if (ch == '\r') //enter
            {
                mode = !mode; //змінити режим "*" на "#"
                sphereDrawing();
            }

            //клавіша для збільшення
            if (ch == '=')
            {
                radius++;
                sphereDrawing();
            }
            else if (ch == '-' && radius > 1) //зменшення радіус
            {
                radius--;
                sphereDrawing();
            }
        }

    }

    void draw(char symbol) const override
    {
        Point::draw(symbol);
        GoToXY(0, 0); //позиція для виведення координат
        cout << "coordinates of the center: " << "(" << x << ", " << y << ")";
        GoToXY(0, 1); //позиція для виведення радіусу
        cout << "radius: " << radius;
    }

};



int main()
{
    SetConsoleTitle(L"Console");

    Sphere a(50, 12, 5);
    a.ConsoleCursorVisible(false, 100);
    a.sphereDrawing();
    a.movement();

}
