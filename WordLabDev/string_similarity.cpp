#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int min(int a, int b, int c) {
	if(a < b) {
		return (a < c) ? a : c;
	} else {
		return (b < c) ? b : c;
	}
}

int compute_distance(char *strA, int len_a, char *strB, int len_b, int **temp) {
	int i, j;

	for(i = 1; i <= len_a; i++) {
		temp[i][0] = i;
	}

	for(j = 1; j <= len_b; j++) {
		temp[0][j] = j;
	}

	temp[0][0] = 0;

	for(i = 1; i <= len_a; i++) {
		for(j = 1; j <= len_b; j++) {
			if(strA[i - 1] == strB[j - 1]) {
				temp[i][j] = temp[i - 1][j - 1];
			} else {
				temp[i][j] = min(temp[i - 1][j], temp[i][j - 1], temp[i - 1][j - 1]) + 1;
			}
		}
	}
	return temp[len_a][len_b];
}

int main() {
	char a[] = "abcdefghijklmnopqrstuvwxyz";
	char b[] = "abcdefghijklmnopqrstvwxyz";
	int len_a = strlen(a);
	int len_b = strlen(b);

	int **temp = (int**)malloc(sizeof(int*) * (len_a + 1));
	for(int i = 0; i < len_a + 1; i++) {
		temp[i] = (int*)malloc(sizeof(int) * (len_b + 1));
		memset(temp[i], 0, sizeof(int) * (len_b + 1));
	}
	int distance = compute_distance(a, len_a, b, len_b, temp);
	printf("%d\n", distance);
}
