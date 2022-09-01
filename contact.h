#pragma once
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>
#include<time.h>


int compare(const void*p1,const void* p2);

void menu();

void add();

void del();

void search();

void edit();

void show();

void sort();

void contact();

int** E_mat(int n);

int** randint_mat(int row,int col,int min,int max);

double** rand_mat(int row,int col);

int** int_mat(int row,int col);

void print_mat(int** arr);

double** mat(int row,int col);

void print_mat(double** arr);

int row(double**arr);

int col(double**arr);

int row(int**arr);

int col(int**arr);

double** mat_mul(double**mat1,double**mat2);

double** mat_mul(double**mat1,int**mat2);

double** mat_mul(int**mat1,double**mat2);

int** mat_mul(int**mat1,int**mat2);

double** mat_mul(double d,double**mat2);

double** mat_mul(double**mat2,double d);

double** mat_mul(int x,double**mat2);

double** mat_mul(double**mat2,int x);

double** mat_mul(double d,int**mat2);

double** mat_mul(int**mat2,double d);
int** mat_mul(int x,int**mat2);

int** mat_mul(int**mat2,int x);

double** mat_add(double** mat1,double** mat2);

double** mat_add(double** mat1,int** mat2);

double** mat_add(int** mat1,double** mat2);

int** mat_add(int** mat1,int** mat2);

double** mat_sub(double** mat1,double** mat2);

double** mat_sub(double** mat1,int** mat2);

double** mat_sub(int** mat1,double** mat2);

int** mat_sub(int** mat1,int** mat2);

double** inv(double**arr);

double det(double** arr);

double** inv(int**arr);

double det(int**arr);

double** ind(double**arr,int n);

int** ind(int**arr,unsigned int n);

double fun(double* p,double x,int k);

double** solvep(double*);

