/*
 Course: Design and Analysis of Algorithms CSC 505 ( 001 )
 Instructor: Steffen Heber
 Description: Fall 2015, Homework 3 Solutions.
 Student Name: Himangshu Ranjan Borah
 Student ID: 200105222
 Unity ID: hborah
 
 Matrix Multiplication Code, Dynamic
 */


#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std;


int no_multiplications = 0;
int no_recursions = 0;


int dynamic_matrix_chain(int p[], int n){
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
                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    return m[1][n - 1];
}


void run_test_case(int array[], int size){
    no_multiplications = 0;
    no_recursions = 0;
    int result;
    auto start_time = std::chrono::high_resolution_clock::now();
    

    result = dynamic_matrix_chain(array, size);
    
    auto end_time = std::chrono::high_resolution_clock::now();
    cout<<"No. of multiplications in the Optimal Chain = "<<result<<endl;
    auto running_time = end_time - start_time;
    
    cout << "Dynamic Matrix Chain :: Execution Time = " <<
    chrono::duration_cast<chrono::nanoseconds>(running_time).count() << " nanoseconds"<<endl;
    
    cout<<"Dynamic Matrix Chain :: No of Scalar Multiplications = "<<no_multiplications<<endl;
    cout<<"Dynamic Matrix Chain :: No of Recursive Calls = "<<no_recursions<<endl;
    
    return;
}



int main(int argc, char* argv[]){
    
    int size;
    int test_case1[] = {20, 30, 45, 37, 18};
    size = sizeof(test_case1)/sizeof(test_case1[0]);
    run_test_case(test_case1, size);
    
    cout<<endl<<endl;
    
    int test_case2[] = {20, 30, 45, 37, 18, 25, 35, 45, 87, 28};
    size = sizeof(test_case2)/sizeof(test_case2[0]);
    run_test_case(test_case2, size);
    
    
    cout<<endl<<endl;
    
    
    int test_case3[] = {20, 30, 45, 37, 18, 25, 35, 45, 87, 28, 19, 7, 34, 67, 7};
    size = sizeof(test_case3)/sizeof(test_case3[0]);
    run_test_case(test_case3, size);
    
    cout<<endl<<endl;
    
    
    return 0;
    
    
}