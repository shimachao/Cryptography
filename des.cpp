/*
加密：
输入明文，密钥，输出密文
明文和密钥是二进制数,16进制数
明文和密钥位数不足，需要进行补零操作

解密：
输入密文，密钥，输出明文
其中密文和密钥可以是二进制数，16进制数
密钥位数不足，需进行补零操作
/
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

using namespace std;

bitset <56> key;	//保存用户输入的密钥

bool is_big_edian(void);			//判断本地机器数据的存储是否为大端模式
void set_key(long long a,bitset <56> &key);	//获得用户的输入的密钥，用bitset对象保存,注意bitset二进制成员的顺序从右到左

//设置k1~k16
int main(void)
{
	long long ll;
	scanf("%llx",&ll);
	set_key(ll,key);
	return 0;
}


bool is_big_edian(void)
{
	union
	{
		short s;
		char c[sizeof(short)];
	}un;
	
	un.s = 0x0102;
	
	assert(sizeof(short) == 2);
	
	if(un.c[0] == 0x01 && un.c[1] == 0x02)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void set_key(long long a,bitset <56> &key)//根据用户的输入设置密钥
{
	union
	{
		long long l;
		unsigned long ul[2];
	}un;
	un.l = a;

	bitset<32> bitvec1;
	bitset<32> bitvec2;
	if (is_big_edian())
	{
		cout<<"un.ul[0]=="<<un.ul[0]<<endl;

		bitset<32> b1(un.ul[0]);
		bitset<32> b2(un.ul[1]);

		bitvec1 = b1;
		bitvec2 = b2;
	}
	else
	{
		cout<<"un.ul[0]=="<<un.ul[0]<<endl;
		bitset<32> b1(un.ul[0]);
		bitvec2 = b1;

		cout<<"un.ul[1]=="<<un.ul[1]<<endl;
		bitset<32> b2(un.ul[1]);
		bitvec1 = b2;
	}

	cout<<"bitvec1:"<<bitvec1<<endl;
	cout<<"bitvec2:"<<bitvec2<<endl;
	int i = 0;
	for (int j = 0; i < 28 && j < 32; i++, j++)
	{
		if (j == 0 || j == 8 || j == 15 || j == 24)
		{
			i--;
			continue;
		}
		key[i] = bitvec2[j];
	}
	for (int j = 0; i < 56 && j < 32; i++, j++)
	{
		assert(i > 27);
		
		if (j == 0 || j == 8 || j == 15 || j == 24)
		{
			i--;
			continue;
		}
		key[i] = bitvec1[j];
	}
	cout<<"key== :"<<key<<endl;
}

