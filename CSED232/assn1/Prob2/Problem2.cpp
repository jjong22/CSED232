#include <iostream>
#include <fstream>
#include <string>
#define MAX_SIZE 10
int submat[MAX_SIZE][MAX_SIZE];

void submatrix(int matrix[MAX_SIZE][MAX_SIZE], int submat[MAX_SIZE][MAX_SIZE], int p, int q, int n);
int det(int mat[MAX_SIZE][MAX_SIZE], int n);
void clear_matrix(int submat[MAX_SIZE][MAX_SIZE]);

int main() {
    ///////////////////////////////////////////////////////////////////////
    //  input.txt 파일을 읽기 모드로 엽니다.
    ///////////////////////////////////////////////////////////////////////
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "input.txt 파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    int matrix1[MAX_SIZE][MAX_SIZE]; // 첫번째 행렬 입력
    int matrix2[MAX_SIZE][MAX_SIZE]; // 두번째 행렬 입력
    clear_matrix(matrix1); // 행렬 초기화
    clear_matrix(matrix2); // 행렬 초기화
    int operation; // 연산
    int num_element; // 행,열의 개수

    std::string line;

    std::getline(inputFile, line); // 연산
    operation = stoi(line);

    std::getline(inputFile, line); // 행 개수
    num_element = stoi(line);

    int number; // istream을 받는 변수
    for (int i = 0; i < num_element; i++) // 각 원소를 행렬 배열에 입력.
    {
        for (int j = 0; j < num_element; j++)
        {
            inputFile >> number;
            matrix1[i][j] = number;
        }
    }
    if (operation < 4) // 2개의 matrix를 입력 받음.
    {
        for (int i = 0; i < num_element; i++)
        {
            for (int j = 0; j < num_element; j++)
            {
                inputFile >> number;
                matrix2[i][j] = number;
            }
        }
    }

    inputFile.close();

    std::ofstream outputFile("output.txt");

    if (!outputFile) {
        std::cerr << "output.txt 파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    if (operation == 1) // 덧셈
    {
        for (int i = 0; i < num_element; i++)
        {
            for (int j = 0; j < num_element; j++)
            {
                matrix1[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }

        for (int i = 0; i < num_element; i++) // 파일로 출력
        {
            for (int j = 0; j < num_element; j++)
            {
                outputFile << matrix1[i][j] << " ";
            }
            outputFile << '\n';
        }
    }
    else if (operation == 2) // 뺄셈
    {
        for (int i = 0; i < num_element; i++)
        {
            for (int j = 0; j < num_element; j++)
            {
                matrix1[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        }

        for (int i = 0; i < num_element; i++) // 파일로 출력
        {
            for (int j = 0; j < num_element; j++)
            {
                outputFile << matrix1[i][j] << " ";
            }
            outputFile << '\n';
        }
    }
    else if (operation == 3) // 곱셈
    {
        int result[MAX_SIZE][MAX_SIZE];

        for (int i = 0; i < num_element; i++) 
        {
            for (int j = 0; j < num_element; j++)
            {
                result[i][j] = 0;
                for (int inner = 0; inner < num_element; inner++)
                    result[i][j] += matrix1[i][inner] * matrix2[inner][j]; // 행렬곱 연산 https://learn.microsoft.com/ko-kr/cpp/parallel/amp/walkthrough-matrix-multiplication?view=msvc-170
            }
        }

        for (int i = 0; i < num_element; i++) // 파일로 출력
        {
            for (int j = 0; j < num_element; j++)
            {
                outputFile << result[i][j] << " ";
            }
            outputFile << '\n';
        }
    }
    else if (operation == 4) // transpose
    {
        int result[MAX_SIZE][MAX_SIZE];

        for (int i = 0; i < num_element; i++) // row와 column을 바꿔서 저장함.
        {
            for (int j = 0; j < num_element; j++)
            {
                result[i][j] = matrix1[j][i];
            }
        }

        for (int i = 0; i < num_element; i++) // 파일로 출력
        {
            for (int j = 0; j < num_element; j++)
            {
                outputFile << result[i][j] << " ";
            }
            outputFile << '\n';
        }
    }
    else if (operation == 5) // determinent
    {
        int determinent;

        determinent = det(matrix1, num_element); // 행렬식을 det 함수를 이용해 계산함.

        outputFile << determinent; // 파일로 출력
    }
    outputFile.close();

    return 0;
}

void submatrix(int matrix[MAX_SIZE][MAX_SIZE], int submat[MAX_SIZE][MAX_SIZE], int p, int q, int n) // submatrix를 구해서 submat[][]을 수정함.
{
    int row = 0, col = 0;

    for (int i = 0; i < n; i++) {
        if (i == p) // 현재 해당하는 row를 제외함.
        {   
            continue;
        }
        else
        {
            col = 0;
            for (int j = 0; j < n; j++) {
                if (j == q) // 현재 해당하는 column을 제외함.
                {
                    continue;
                }
                else
                {
                    submat[row][col] = matrix[i][j]; // submat[][]에 row p, column q 를 제외한 submatrix가 기록됨.
                    col++;
                }
            }
        row++;
        }
    }
}

int det(int mat[MAX_SIZE][MAX_SIZE], int n) // 행렬식(determinent)을 계산함.
{
    int determinent = 0;
    int submat[MAX_SIZE][MAX_SIZE];
    clear_matrix(submat);

    if (n == 1) return mat[0][0];

    if (n == 2) return (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]); // 2차원에서의 공식을 이용함.

    int sign = 1;

    for (int j = 0; j < n; j++) // 재귀적으로 submatrix에 대해서 행렬식을 계산함.
    {
        clear_matrix(submat);
        submatrix(mat, submat, 0, j, n);
        determinent += sign * mat[0][j] * det(submat, n-1);

        sign = - sign;
    }
    return determinent;
}

// chatgpt.

void clear_matrix(int submat[MAX_SIZE][MAX_SIZE]) // 행렬을 0으로 초기화
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            submat[i][j] = 0;
        }
    }
}