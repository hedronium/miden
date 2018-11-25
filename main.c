int main() {
	int y;
	y = multiplyNumbers(2, 3); /*Returns product of 2 and 3*/
}

int multiplyNumbers(int a, int b) {
	int i;
	int product = 0;
	for (i = 0; i != b; i = i + 1) {
		product = product + a;
	}
	return product;
}