#include <iostream>
#include <fstream>
#include <string>

void selection_sort(int student_info[50][5], int max_people, int sort_selection, int mode);

int main() {
    ///////////////////////////////////////////////////////////////////////
    //  input.txt 파일을 읽기 모드로 엽니다.
    ///////////////////////////////////////////////////////////////////////
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "input.txt 파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    int student_infomation[50][5]; // 학생의 정보를 담는 배열

    int person = 0, element = 0;
    int num;
    int sum = 0;

    while (inputFile >> num)
    {
        student_infomation[person][element] = num;

        if (element != 0) // 학번은 제외
            sum += num;
        element += 1;

        if (element == 4) // 총합을 계산해서 저장함.
        {
            student_infomation[person][4] = sum;

            sum = 0;
            element = 0;
            person += 1;
        }
    }

    inputFile.close();

    int max_people = person;
    int sort_selection;
    int mode;

    while (1)
    {
        std::cout << "정렬 기준을 선택하세요 (1: 학번. 2: 국어. 3: 영어. 4: 수학. 5: 총점. 0: 종료): \n";
        std::cin >> sort_selection;

        if (sort_selection == 0) // 0을 입력한 경우에 종료
        {
            return 0;
        }

        sort_selection -= 1; 
        // sort_selection이 student_infomation[]의 index를 나타내는데, 0: 학번, 1: 국어 ... 이런 형태로 정의되어 있음.

        std::cout << "오름차순 정렬은 1. 내림차순 정렬은 -1을 입력하세요: \n";
        std::cin >> mode;

        selection_sort(student_infomation, max_people, sort_selection, mode); // 정렬

        std::cout << "학번 국어 영어 수학 총점" << "\n";
        std::cout << "----------------------" << "\n";
        for (int i = 0; i < person; i++) // 출력
        {
            for (int j = 0 ; j < 5 ; j++)
            {
                std::cout << student_infomation[i][j] << "  ";
            }
            std::cout << '\n';
        }
        
        std::cout << '\n';
        std::cout << '\n';
    }
}

void selection_sort(int student_info[50][5], int max_people, int sort_selection, int mode) // 선택 정렬 알고리즘을 이용해 정렬하는 함수
{
    int temp[5]; // 값 교환을 위한 배열

    if (mode == -1) // 내림차순 정렬
    {
        for (int i = 0; i < max_people; i++) 
    {
        int max_element = student_info[i][sort_selection];
        int index = i;

        for (int j = i; j < max_people; j++) // sub 배열을 쭉 순회해 최댓값을 구함.
        {
            if (student_info[j][sort_selection] == max_element) // 동일할 경우, 학번이 작은 순으로 정렬
            {
                if (student_info[j][0] < student_info[index][0])
                {
                    max_element = student_info[j][sort_selection];
                    index = j;
                }
            }

            if (student_info[j][sort_selection] > max_element)
            {
                max_element = student_info[j][sort_selection];
                index = j;
            }
        }

        for (int k = 0; k < 5; k++) // sub 배열의 맨 앞과 최댓값을 교환해 정렬함.
        {
            temp[k] = student_info[index][k];
            student_info[index][k] = student_info[i][k];
            student_info[i][k] = temp[k]; 
        }
    }

    }

    else if (mode == 1) // 오름차순 정렬
    {
        for (int i = 0; i < max_people; i++)
    {
        int min_element = student_info[i][sort_selection];
        int index = i;

        for (int j = i; j < max_people; j++) // sub 배열을 쭉 순회해 최솟값을 구함.
        {
            if (student_info[j][sort_selection] == min_element) // 동일할 경우, 학번이 작은 순으로 정렬
            {
                if (student_info[j][0] < student_info[index][0])
                {
                    min_element = student_info[j][sort_selection];
                    index = j;
                }
            }

            if (student_info[j][sort_selection] < min_element)
            {
                min_element = student_info[j][sort_selection];
                index = j;
            }
        }
        for (int k = 0; k < 5; k++) // sub 배열의 맨 앞과 최솟값을 교환해 정렬함.
        {
            temp[k] = student_info[index][k];
            student_info[index][k] = student_info[i][k];
            student_info[i][k] = temp[k]; 
        }
    }

    }
    
}