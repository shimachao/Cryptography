/*
凯撒密码
	它是一种替换加密的技术，明文中的所有字母都在字母表上向后（或向前）按照一个固定数目进行偏移后被替换成密文
实验要求
加密：输入明文，密钥，输出密文
解密：输入密文，密钥，输出明文
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char*plain,size_t len,int k,char *cipher);//加密
void decrypt(char*cipher,size_t len,int k,char *plain);//解密
void fflush_stdin(void);

int main(void)
{
	char plain[1024] = {'\0'};//明文
	char cipher[1024] = {'\0'};//密文
	int k;//密钥
	puts("输入明文：");
	gets(plain);
//	fflush_stdin();
	puts("输入密钥：");
	scanf("%d",&k);
	printf("你输入的明文为：%s,密钥为：%d\n",plain,k);

	encrypt(plain,strlen(plain),k,cipher);

	printf("凯撒加密后的密文为：%s\n",cipher);

	char plain2[1024] = {'\0'};
	decrypt(cipher,strlen(cipher),k,plain2);
	printf("再次解密后为：%s\n",plain2);

	return 0;
}


void encrypt(char*plain,size_t len,int k,char *cipher)
{
	for (int i = 0; i < len; i++)
	{
		if (plain[i] >= 'a' && plain[i] <= 'z')
		{
			cipher[i] = (plain[i] + k - 'a')%26 + 'a';
		}
		else if (plain[i] >= 'A' && plain[i] <= 'Z')
		{
			cipher[i] = (plain[i] + k - 'A')%26 + 'A';
		}
		else
		{
			cipher[i] = plain[i];
		}
	}
}
void decrypt(char*cipher,size_t len,int k,char *plain)
{
	for (int i = 0; i < len; i++)
	{
		if (cipher[i] >= 'a' && cipher[i] <= 'z')
		{
			plain[i] = (cipher[i] - 'a' - k + 26) % 26 + 'a';
		}
		else if (cipher[i] >= 'A' && cipher[i] <= 'Z')
		{
			plain[i] = (cipher[i] - k - 'A'+ 26) % 26 + 'A';
		}
		else
		{
			plain[i] = cipher[i];
		}
	}
}

void fflush_stdin(void)
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}
