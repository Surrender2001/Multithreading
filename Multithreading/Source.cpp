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
#include <iomanip>


using namespace std;
using namespace chrono;
void ToSumEven(vector<int> arr, int& sum) // Функция потока, суммирующая элементы массива.
{   
    // Результат записывается в переменную sum, передаваемую по ссылке
    int result = 0;
    for (auto element : arr)
        if (element % 2 == 0)
            ++result;
    sum = result; 
}

int main()
{
    srand(time(nullptr));
    int vectorRows; // Число строк матрицы
    int vectorColumns; // Число столбцов

    cout << "Count of rows: " << endl;
    cin >> vectorRows;

    cout << "Count of columns" << endl;
    cin >> vectorColumns;

    cout << "MAX of my threads: " <<thread::hardware_concurrency()<<endl;


    vector<vector<int> > matrix(vectorRows);
    for (auto & element : matrix)
        element = vector<int>(vectorColumns);
    


    for (int i = 0; i < vectorRows; ++i)
        for (int j = 0; j < vectorColumns; ++j)
            matrix[i][j] = rand()%100;
        
    for (int i = 0; i < vectorRows; ++i)
    {
        for (int j = 0; j < vectorColumns; ++j)
            cout << matrix[i][j]<<" ";
        cout << endl;
    }




    vector<int> vectorOfSum(vectorRows); 
    vector<thread> vectorOfThreads(vectorRows); 

    for (int i = 0; i < vectorRows; ++i)
    {
        vectorOfThreads[i] = thread(ToSumEven, matrix[i], ref(vectorOfSum[i]));
        cout <<"THREAD ID: "<< vectorOfThreads[i].get_id()<<endl;
    }

    //this_thread::sleep_for(microseconds(2000));


    for (int i = 0; i < vectorRows; ++i)
        vectorOfThreads[i].join();
    


    for (int i = 0; i < vectorRows; ++i)
        cout <<i<<" row: "<<vectorOfSum[i] <<" evens"<< "\n";
    

    return 0;
}
