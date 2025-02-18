/*
 * Safe malloc and partial leak
 *
 * Author: Yule Sui
 * Date: 02/04/2014
 */

//TC08: if dependent 
#include "aliascheck.h"

int G;
void clear_conditioned() {
	char *buf1, *buf2;

	if (G) {
		buf1 = SAFEMALLOC(10); // psafix PLKLEAKFP
	} else {
		buf2 = SAFEMALLOC(10); // psafix PLKLEAKFP
	}

	if (G) {
		free(buf1);
	} else {
		free(buf2);
	}
}
// no alarms 

void unclear_conditioned(int arg1) {
	char *buf1, *buf2;
	int i;

	if (arg1) {
		buf1 = PLKMALLOC(10);      // true alarm
	} else {
		buf2 = NFRMALLOC(10);     // false alarm psafix PLKLEAKFP
	}

	arg1 = arg1 - 1;

	arg1 = arg1 + 10;

	if (arg1) {
		free(buf1);
	} else {
		free(buf2);
	}
}

int main() {
	clear_conditioned();
	unclear_conditioned(G);
}
