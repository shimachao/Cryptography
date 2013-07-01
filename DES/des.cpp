/*
加密：
输入明文，密钥，输出密文
明文和密钥是二进制数,16进制数
明文和密钥位数不足，需要进行补零操作

解密：
输入密文，密钥，输出明文
其中密文和密钥可以是二进制数，16进制数
密钥位数不足，需进行补零操作
*/
/*
密钥的获取,用一个8字节的long long类型数据保存用户的输入,然后转化为两个4字节的unsigned int数据，（注意大小端模式），a1为高4字节，a2为低4字节
然后用这个两个数初始化两个bitset对象，再申请一个56bit的bitset对象，用之前的两个bitset来初始化它，第7，15，23，31，39，47，55，63位为奇偶验证位，不要。
这个bitset对象即为密钥。
*/

#include <iostream>
#include <bitset>
#include <string>
#include <stdio.h>
#include <assert.h>

#include "key.h"

using namespace std;

int main(void)
{
	long long ll;
	scanf("%llx",&ll);
	generate_keys(ll);
	return 0;
}


