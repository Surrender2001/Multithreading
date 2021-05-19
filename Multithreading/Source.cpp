// Пример задачи, в которой используется многопоточное выполнение программы
// Нужно сложить элементы строк матрицы
// Каждая строка суммируется своим  отдельным потоком
//


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include<ctime>

using namespace std;

void add(vector<int> arr, int& sum) // Функция потока, суммирующая элементы массива.
{                                   // Результат записывается в переменную sum, передаваемую по ссылке
    int result = 0;
    for (int element : arr) {
        result = result + element;
    }
    sum = result;
}

int main()
{
    int vectorNumber = 12; // Число строк матрицы
    int vectorSize = 1000; // Число столбцов

    // Создаём матрицу - вектор из весторов
    vector<vector<int> > matrix(vectorNumber);
    for (vector<int>& element : matrix)
    {
        element = vector<int>(vectorSize);
    }

    // Заполняем матрицу значениями
    for (int i = 0; i < vectorNumber; i++)
    {
        for (int j = 0; j < vectorSize; j++)
        {
            matrix[i][j] = i + j;
        }
    }


    vector<int> vectorOfSum(vectorNumber); //вектор для хранения сумм строк матрицы
    vector<thread> vectorOfTreads(vectorNumber); //вектор потоков
    // создаём потоки
    for (int i = 0; i < vectorNumber; i++)
    {
        vectorOfTreads[i] = thread(add, matrix[i], ref(vectorOfSum[i]));
    }

    // ждём завершения всех потоков
    for (int i = 0; i < vectorNumber; i++)
    {
        vectorOfTreads[i].join();
    }

    // выводим результат
    for (int i = 0; i < vectorNumber; i++)
    {
        cout << vectorOfSum[i] << "\n";
    }

    return 0;
}
