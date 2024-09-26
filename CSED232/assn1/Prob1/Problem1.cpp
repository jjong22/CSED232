#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    const int MAX_SIZE = 10;  // 최대 입력 크기
    int numbers[MAX_SIZE];    // 입력 숫자를 저장할 배열
    int k;                    // 입력된 숫자 개수

    // 입력 받기 (최대 10개의 숫자 입력)
    cout << "숫자 개수를 입력하세요 (1 <= k <= 10): ";
    cin >> k;

    // k개의 숫자 입력
    cout << "각각의 숫자를 입력하세요 (각 숫자는 공백으로 구분): ";
    for (int i = 0; i < k; i++) {
        cin >> numbers[i];
    }

    // 계산 결과를 담는 배열
    int result[MAX_SIZE];

    for (int i = 0; i < k; i++)
    {
        int a1 = 0;
        int a2 = 1;
        int temp = 0;
        
        // 피보나치 수열의 점화식 a_n+2 = a_n+1 + a_n 을 이용해 계산
        for (int j = 0; j < numbers[i]; j++)
        {
            temp = a1 + a2;
            a1 = a2;
            a2 = temp;
        }
        result[i] = a1;
    }

    // 결과를 차례대로 출력함.
    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }

    cout << endl;

    return 0;
}