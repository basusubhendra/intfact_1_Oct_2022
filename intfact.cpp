#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <boost/lexical_cast.hpp>
#include <pthread.h>
#include "zeros.hpp"
using namespace std;
using namespace boost;
#define NZEROS 2001052

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
    std::string factor = "";
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
    unsigned long score = 0;
    unsigned long score_0_5 = 0;
    char nn = 0, cc = 0;
    while (1) {
        int ret = fscanf(f, "%c", &nn);
        ret = fscanf(g, "%c", &cc);
        int ck = cc - '0';
	if (ck == 1 && nn != '0') {
		nchanges += ck;
	}
        if (nn == num[ctr]) {
              bool isRiemann1 = isRiemannZero(nchanges);
              unsigned long long int _reverse_of_nchanges_ = _reverse_of_(nchanges);
              bool isRiemann2 = isRiemannZero(_reverse_of_nchanges_);
              if (isRiemann1 && !isRiemann2) {
                  ++ctr;
              } else if (isRiemann1 && isRiemann2) {
              } else if (!isRiemann1) {
              }
              break;
        }
    }
    while (ctr < l) {
        int ret = fscanf(f, "%c", &nn);
        ret = fscanf(g, "%c", &cc);
        int ck = cc - '0';
	if (ck == 1 && nn != '0') {
		nchanges += ck;
	}
        if (nn == num[ctr]) {
              bool isRiemann1 = isRiemannZero(nchanges);
              unsigned long long int _reverse_of_nchanges_ = _reverse_of_(nchanges);
              bool isRiemann2 = isRiemannZero(_reverse_of_nchanges_);
              if (isRiemann1 && !isRiemann2) {
		  if (score_0_5 % 2 == 0) {
                      score += score_0_5*0.5;
                  }
                  factor += boost::lexical_cast<std::string>(score);
                  score = score_0_5 = 0;
                  ++ctr;
              } else if (isRiemann1 && isRiemann2) {
                  score_0_5++;
              } else if (!isRiemann1) {
                  score++;
              }
        }
    }
    fclose(f);
    fclose(g);
}

int main(int argc, char* argv[]) {
    char* num = strdup(argv[1]);
    struct a* arg1 = new (struct a)();
    arg1->num = strdup(num);
    arg1->param = 1;
    struct a* arg2 = new (struct a)();
    arg2->num = strdup(num);
    arg2->param = 0;
    char* ret1 = 0, *ret2 = 0;
    pthread_t thread_id1, thread_id2;
    pthread_create(&thread_id1, NULL, factorize, arg1);
    pthread_create(&thread_id2, NULL, factorize, arg2);
    pthread_join(thread_id1, (void**) &ret1);
    pthread_join(thread_id2,(void**) &ret2);
    return 0;
}
