// ������ ������, � ������� ������������ ������������� ���������� ���������
// ����� ������� �������� ����� �������
// ������ ������ ����������� �����  ��������� �������
//


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include<ctime>
#include<chrono>

using namespace std;
using namespace chrono;

void ToSumEven(vector<int> arr, int& sum) // ������� ������, ����������� �������� �������.
{                                   // ��������� ������������ � ���������� sum, ������������ �� ������
    int result = 0;
    for (auto element : arr)
        if (element % 2 == 0)
            ++result;
    sum = result; 
}

int main()
{
    srand(time(nullptr));
    int vectorNumber; // ����� ����� �������
    int vectorSize; // ����� ��������

    cout << "Count of rows: " << endl;
    cin >> vectorNumber;

    cout << "Count of columns" << endl;
    cin >> vectorSize;

    cout << "MAX of my threads: " <<thread::hardware_concurrency()<<endl;

    // ������ ������� - ������ �� ��������
    vector<vector<int> > matrix(vectorNumber);
    for (auto & element : matrix)
    {
        element = vector<int>(vectorSize);
    }

    // ��������� ������� ����������
    for (int i = 0; i < vectorNumber; i++)
    {
        for (int j = 0; j < vectorSize; j++)
        {
            matrix[i][j] = rand()%100;
        }
    }


    vector<int> vectorOfSum(vectorNumber); //������ ��� �������� ���� ����� �������
    vector<thread> vectorOfThreads(vectorNumber); //������ �������
    // ������ ������
    for (int i = 0; i < vectorNumber; i++)
    {
        vectorOfThreads[i] = thread(ToSumEven, matrix[i], ref(vectorOfSum[i]));
        cout <<"THREAD ID: "<< vectorOfThreads[i].get_id()<<endl;
    }

    // ��� ���������� ���� �������
    for (int i = 0; i < vectorNumber; ++i)
        vectorOfThreads[i].join();
    

    // ������� ���������
    for (int i = 0; i < vectorNumber; ++i)
        cout <<i<<" row: "<< vectorOfSum[i] << "\n";
    

    return 0;
}
