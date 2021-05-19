// ������ ������, � ������� ������������ ������������� ���������� ���������
// ����� ������� �������� ����� �������
// ������ ������ ����������� �����  ��������� �������
//


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include<ctime>

using namespace std;

void add(vector<int> arr, int& sum) // ������� ������, ����������� �������� �������.
{                                   // ��������� ������������ � ���������� sum, ������������ �� ������
    int result = 0;
    for (int element : arr) {
        result = result + element;
    }
    sum = result;
}

int main()
{
    int vectorNumber = 12; // ����� ����� �������
    int vectorSize = 1000; // ����� ��������

    // ������ ������� - ������ �� ��������
    vector<vector<int> > matrix(vectorNumber);
    for (vector<int>& element : matrix)
    {
        element = vector<int>(vectorSize);
    }

    // ��������� ������� ����������
    for (int i = 0; i < vectorNumber; i++)
    {
        for (int j = 0; j < vectorSize; j++)
        {
            matrix[i][j] = i + j;
        }
    }


    vector<int> vectorOfSum(vectorNumber); //������ ��� �������� ���� ����� �������
    vector<thread> vectorOfTreads(vectorNumber); //������ �������
    // ������ ������
    for (int i = 0; i < vectorNumber; i++)
    {
        vectorOfTreads[i] = thread(add, matrix[i], ref(vectorOfSum[i]));
    }

    // ��� ���������� ���� �������
    for (int i = 0; i < vectorNumber; i++)
    {
        vectorOfTreads[i].join();
    }

    // ������� ���������
    for (int i = 0; i < vectorNumber; i++)
    {
        cout << vectorOfSum[i] << "\n";
    }

    return 0;
}
