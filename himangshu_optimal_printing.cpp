/*
 Course: Design and Analysis of Algorithms CSC 505 ( 001 )
 Instructor: Steffen Heber
 Description: Fall 2015, Homework 3 Solutions.
 Student Name: Himangshu Ranjan Borah
 Student ID: 200105222
 Unity ID: hborah
 
 Matrix Multiplication Code, Printing the Parenthesiz
 */


#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std;


int no_multiplications = 0;
int no_recursions = 0;


int dynamic_matrix_chain(int**& s, int p[], int n){
    no_recursions++;
    int* m[n];
    for(int i = 0; i < n ; i++){
        m[i] = new int[n];
    }
    
    
    for(int i = 0; i < n ; i++){
        m[i][i] = 0;
    }
    int j;
    int q;
    for(int l = 2 ; l < n; l++){
        for(int i = 1; i < n - l + 1 ; i++){
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for(int k = i; k <= j - 1; k++){
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                no_multiplications += 2;
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n - 1];
}

void print_optimal_parens(int** s, int i, int j){
    if(i == j)
        cout<<"A"<<i;
    else{
        cout<<"(";
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        cout<<")";
    }
    return;
}


int print_optimal(int p[], int n){
    int** s = nullptr;
    s = new int*[n];
    for(int i = 0; i < n ; i++){
        s[i] = new int[n];
    }
    int result = dynamic_matrix_chain(s, p, n);
    print_optimal_parens(s, 1, n - 1);
    
    return result;
}




void run_test_case(int array[], int size){
    no_multiplications = 0;
    no_recursions = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    cout<<"The parenthesization :: ";
    int result = print_optimal(array, size);
    cout<<endl;
    cout<<"Optimal Multiplications :: "<<result<<endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto running_time = end_time - start_time;
    
    cout << "Dynamic Matrix Chain :: Execution Time = " <<
    chrono::duration_cast<chrono::nanoseconds>(running_time).count() << " nanoseconds"<<endl;
    
    cout<<"Dynamic Matrix Chain :: No of Scalar Multiplications = "<<no_multiplications<<endl;
    cout<<"Dynamic Matrix Chain :: No of Recursive Calls = "<<no_recursions<<endl;
    
    return;
}



int main(int argc, char* argv[]){

    int size;
    int test_case1[] = {5, 2, 4, 3, 7, 9, 7, 8, 6, 1, 3, 7, 6, 5};
    size = sizeof(test_case1)/sizeof(test_case1[0]);
    run_test_case(test_case1, size);
    
    cout<<endl<<endl;
    return 0;


}