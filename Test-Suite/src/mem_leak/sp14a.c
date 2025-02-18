/*
 * Partial leak
 *
 * Author: Yule Sui
 * Date: 02/04/2014
 */

#include "aliascheck.h"

// TC14: recursion 
int * make(int n) {
	int *y = LEAKFN(10);
	if (n > 0) {
		//    free(y);
		return make(n - 1);
	} else {
		free(y);
		return NFRMALLOC(10);
	}
}

void main() {
	int *x = make(10);
	//free(x);
}

