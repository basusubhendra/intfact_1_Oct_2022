#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <pthread.h>
#include <vector>
#include "zeros.hpp"
using namespace std;
#define NZEROS 2001053

struct a {
    char* num;
    short int param;
};

unsigned long long int _reverse_of_(unsigned long long int x) {
    unsigned long long int _reverse_ = 0;
    while (x > 0) {
         _reverse_ = _reverse_*10 + (x % 10);
         x /= 10;
    }
    return _reverse_;
}

int binary_search(unsigned int arr[], int l, int r, unsigned long long int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid; 
        if (arr[mid] > x) 
            return binary_search(arr, l, mid - 1, x); 
        return binary_search(arr, mid + 1, r, x); 
    } 
    return -1; 
}  

bool isRiemannZero(unsigned long long int x) {
    if (binary_search(zeros, 0, NZEROS - 1, x) > 0) {
        return true;
    } else {
        return false;
    }
    return false;
}

void* factorize(void* arg) {
    char* num = ((struct a*) arg)->num;
    short int param = ((struct a*) arg)->param;
    FILE* f = 0, *g = 0;
    vector<unsigned long long int>* result = new vector<unsigned long long int>();
    if (param == 1) {
          f = fopen64("./positive_values.txt","r");
          g = fopen64("./positive_changes.txt","r");
    } else if (param == 0) {
          f = fopen64("./negative_values.txt","r");
          g = fopen64("./negative_changes.txt","r");
    }
    unsigned long long int l = strlen(num);
    unsigned long long int ctr = 0;
    unsigned long long int nchanges = 0;
    unsigned long score_0_5 = 0;
    char nn = 0, cc = 0;
    while (ctr < l) {
        int ret = fscanf(f, "%c", &nn);
        ret = fscanf(g, "%c", &cc);
        if (nn == num[ctr]) {
              bool isRiemann1 = isRiemannZero(nchanges);
              unsigned long long int _reverse_of_nchanges_ = _reverse_of_(nchanges);
              bool isRiemann2 = isRiemannZero(_reverse_of_nchanges_);
              if (isRiemann1 && !isRiemann2) {
                  result->push_back(score_0_5);
                  score_0_5 = 0;
                  ++ctr;
              } else if (isRiemann1 && isRiemann2) {
                  score_0_5++;
              }
        }
    }
    fclose(f);
    fclose(g);
    return result;
}

int main(int argc, char* argv[]) {
    char* num = strdup(argv[1]);
    struct a* arg1 = new (struct a)();
    arg1->num = strdup(num);
    arg1->param = 1;
    struct a* arg2 = new (struct a)();
    arg2->num = strdup(num);
    arg2->param = 0;
    vector<unsigned long long int>* ret1 = 0, *ret2 = 0;
    pthread_t thread_id1, thread_id2;
    pthread_create(&thread_id1, NULL, factorize, arg1);
    pthread_create(&thread_id2, NULL, factorize, arg2);
    pthread_join(thread_id1, (void**) &ret1);
    pthread_join(thread_id2, (void**) &ret2);
    int partition_index = 0;
    for ( ; partition_index < ret1->size(); ++partition_index) {
       unsigned long long int res1 = ret1->at(partition_index);
       unsigned long long int res2 = ret2->at(partition_index);
       unsigned long long int sum = res1 + res2;
       sum = (sum % 2 == 0)? (sum / 2):sum;
       printf("\nParititon : \t %d\t%llu\n", partition_index+1, res1);
       printf("\nParititon : \t %d\t%llu\n", partition_index+1, res2);
       printf("\nSum : \t %d\t%llu\n", partition_index+1, sum);
    }
    return 0;
}
