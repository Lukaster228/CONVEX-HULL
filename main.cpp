#include<bits/stdc++.h>
#include <locale.h>

using namespace std;


#define allDots pair<int, int>


set<allDots> hull;//Хранение результатов


int findSide(allDots p1, allDots p2, allDots p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int lineDist(allDots p1, allDots p2, allDots p)//возвращает значение, пропорциональное расстоянию между точкой p и линией, соединяющей точки p1 и p2
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}


void quickHull(allDots a[], int n, allDots p1, allDots p2, int side)//Конечными точками прямой L являются точки p1 и p2. сторона может иметь значение 1 или -1, определяя каждую из частей, образованных линией L

{
    int ind = -1;
    int max_dist = 0;


    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }


    if (ind == -1)
    {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }

    //Рекурсия для двух частей, разделенных a[ind]
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void printHull(allDots a[], int n)
{

    if (n < 3)
    {
        cout << "Error!";
        return;
    }

    //Нахождение точки минимума и максимума координаты х
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++)
    {
        if (a[i].first < a[min_x].first)
            min_x = i;
        if (a[i].first > a[max_x].first)
            max_x = i;
    }

    //Рекурсивно наодим точки выпуклой оболочки
    quickHull(a, n, a[min_x], a[max_x], 1);

    //Рекурсивно наодим точки выпуклой оболочки
    quickHull(a, n, a[min_x], a[max_x], -1);
    //Вывод точек
    cout << "The points in Convex Hull are:\n";
    while (!hull.empty())
    {
        cout << "(" <<( *hull.begin()).first << ", "
             << (*hull.begin()).second << ") ";
        hull.erase(hull.begin());
    }
}

//Ввод данных
int main()
{
    setlocale(0,"Russian");
    allDots a[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
               {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(a)/sizeof(a[0]);
    printHull(a, n);
    return 0;
}
