#include <stdio.h>
 
const int maxn = 20003, maxq = 700003, prime0 = 20101, prime1 = 97;
int n, n2, answer, head, last, q[maxq][3];
bool hash[prime0][prime1];
 
int input() {
	scanf("%d", &n);
	return 0;
}
 
bool in_hash(int wv0, int wv1) {
	return hash[wv0][wv1];
}
 
void add_hash(int wv0, int wv1) {
	hash[wv0][wv1] = true;
}
 
bool add_node(int wv0, int wv1, int step) {
	if (wv0 == n || wv1 == n)
		return true;
	if (wv0 < wv1) {
		int temp = wv0;
		wv0 = wv1;
		wv1 = temp;
	}
	if (wv0 == wv1 || wv0 >= n2 || wv1 >= prime1)
		return false;
	if (!in_hash(wv0, wv1)) {
		add_hash(wv0, wv1);
		++last;
		q[last][0] = wv0;
		q[last][1] = wv1;
		q[last][2] = step;
	}
	return false;
}
 
int work() {
	n2 = n + prime1;
	head = last = -1;
	add_node(1, 0, 0);
	while (head < last) {
		++head;
		int wv0 = q[head][0], wv1 = q[head][1], step1 = q[head][2] + 1;
		if (	add_node(wv0+wv0, wv1, step1) ||
				add_node(wv0+wv1, wv1, step1) ||
				add_node(wv1+wv1, wv1, step1) ||
				add_node(wv0, wv0+wv0, step1) ||
				add_node(wv0, wv0+wv1, step1) ||
				add_node(wv0, wv1+wv1, step1) ||
				add_node(wv0, wv0-wv1, step1) ||
				add_node(wv0-wv1, wv0, step1)) {
			answer = step1;
			break;
		}
	}
	return 0;
}
 
int output() {
	printf("%d\n", answer);
	return 0;
}
 
int main() {
	input();
	work();
	output();
	return 0;
}