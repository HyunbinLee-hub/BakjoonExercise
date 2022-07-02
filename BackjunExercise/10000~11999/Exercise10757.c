#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char arr[]) 
{
	int len = strlen(arr);
	for (int i = 0; i < len/2; i++) {
		char temp = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = temp;
	}
}

int main(void)
{
	char num1[10002] = { 0, };
	char num2[10002] = { 0, };
	char res[10003] = { 0, };
	int len, carry = 0;
	int i;

	scanf("%s%s", num1, num2);
	reverse(num1);
	reverse(num2);
	len = (strlen(num1) > strlen(num2)) ? strlen(num1) : strlen(num2);

	for (i = 0; i < len; i++) {
		int sum = num1[i] - '0' + num2[i] - '0' + carry;
		while (sum < 0) sum += '0';
		if (sum > 9) carry = 1;
		else carry = 0;
		res[i] = sum % 10 + '0';
	}

	if (carry == 1) res[len] = '1';
	reverse(res);
	printf("%s", res);

	return 0;
}