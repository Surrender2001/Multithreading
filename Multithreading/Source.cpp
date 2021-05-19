// Пример задачи, в которой используется многопоточное выполнение программы
// Нужно сложить элементы строк матрицы
// Каждая строка суммируется своим  отдельным потоком
//


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include<ctime>
#include<chrono>

using namespace std;
using namespace chrono;

void ToSumEven(vector<int> arr, int& sum) // Функция потока, суммирующая элементы массива.
{                                   // Результат записывается в переменную sum, передаваемую по ссылке
    int result = 0;
    for (auto element : arr)
        if (element % 2 == 0)
            ++result;
    sum = result; 
}

int main()
{
    srand(time(nullptr));
    int vectorNumber; // Число строк матрицы
    int vectorSize; // Число столбцов

    cout << "Count of rows: " << endl;
    cin >> vectorNumber;

    cout << "Count of columns" << endl;
    cin >> vectorSize;

    cout << "MAX of my threads: " <<thread::hardware_concurrency()<<endl;

    // Создаём матрицу - вектор из весторов
    vector<vector<int> > matrix(vectorNumber);
    for (auto & element : matrix)
    {
        element = vector<int>(vectorSize);
    }

    // Заполняем матрицу значениями
    for (int i = 0; i < vectorNumber; i++)
    {
        for (int j = 0; j < vectorSize; j++)
        {
            matrix[i][j] = rand()%100;
        }
    }


    vector<int> vectorOfSum(vectorNumber); //вектор для хранения сумм строк матрицы
    vector<thread> vectorOfThreads(vectorNumber); //вектор потоков
    // создаём потоки
    for (int i = 0; i < vectorNumber; i++)
    {
        vectorOfThreads[i] = thread(ToSumEven, matrix[i], ref(vectorOfSum[i]));
        cout <<"THREAD ID: "<< vectorOfThreads[i].get_id()<<endl;
    }

    // ждём завершения всех потоков
    for (int i = 0; i < vectorNumber; ++i)
        vectorOfThreads[i].join();
    

    // выводим результат
    for (int i = 0; i < vectorNumber; ++i)
        cout <<i<<" row: "<< vectorOfSum[i] << "\n";
    

    return 0;
}
