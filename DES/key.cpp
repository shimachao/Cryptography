/*
*生成加密和解密需要的16把钥匙
*/
#include "key.h"
#include <assert.h>
bitset<48> KEY[16];//钥匙

unsigned char left_shift_num[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

//置换选择表1 PC-1
unsigned char PC_1[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4	
						};
//置换选择表2 PC-2
unsigned char PC_2[48] = {
	14,17,11,24,1,5,3,28,
	15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,
	41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,
	34,53,46,42,50,36,29,32
							};

//左移bit数，c为要移动的对象，n为移动的位数（只能为1或2）
void left_shift(bitset<28> &c,unsigned char n)
{
	if (1 == n)
	{
		int c0 = c[0];
		for (int i = 0; i < 27; i++)
		{
			c[i] = c[i+1];
		}
		c[27] = c0;
	}
	else if (2 == n)
	{
		int c0 = c[0];
		int c1 = c[1];
		for (int i = 0; i < 26; i += 2)
		{
			c[i] = c[i+2];
			c[i+1] = c[i+3];
		}
		c[26] = c0;
		c[27] = c1;
	}
}

//利用用户提供的key产生加密和解密用的钥匙
void generate_keys(long long a)
{
	//根据用户输入的long long，得到钥匙
	bitset<64> key;
	get_key(a,key);
	//选择置换PC-1
	bitset<56> key1;
	for (int i = 0; i < 56; i++)
	{
		key1[i] = key[63 - PC_1[i]];//因为bitset对象的下标是逆序的63~0，所以为63 - PC_1[i]
	}
	//cout<<"key1:"<<key1<<endl;
	//将56bit分为两组
	bitset<28> c;//左
	bitset<28> d;//右

	for (int i = 0; i < 28; i++)
	{
		c[i] = key1[i];
		d[i] = key1[i+28];
	}
	
	//cout<<"c:"<<c<<endl<<"d:"<<d<<endl;

	//重复生成加密和解密中使用的Kn
	for (int j = 0; j < 16; j++)
	{
		//左巡回转换
		left_shift(c,left_shift_num[j]);
		left_shift(d,left_shift_num[j]);
		//合并
		bitset<56> key3;
		for (int i = 0; i < 28; i++)
		{
			key3[i] = c[i];
			key[i+28] = d[i];
		}
		//压缩置换PC-2
		
		for (int i = 0; i < 48; i++)
		{
			KEY[j][i] = key3[56 - PC_2[i]];
		}
		cout<<KEY[j]<<endl;
	}
}

//判断本地机器存储数据是否为大端模式
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

//根据用户的输入设置密钥
void get_key(long long a,bitset <64> &key)
{
	union
	{
		long long l;
		unsigned long ul[2];
	}un;
	un.l = a;
	//cout<<"un.ul[0]=="<<un.ul[0]<<endl;
	//cout<<"un.ul[1]=="<<un.ul[1]<<endl;
	bitset<32> bitvec1;
	bitset<32> bitvec2;
	if (is_big_edian())
	{
		bitset<32> b1(un.ul[0]);
		bitset<32> b2(un.ul[1]);

		bitvec1 = b1;
		bitvec2 = b2;
	}
	else
	{
		bitset<32> b1(un.ul[0]);
		bitvec2 = b1;

		bitset<32> b2(un.ul[1]);
		bitvec1 = b2;
	}

	cout<<"bitvec1:"<<bitvec1<<endl;
	cout<<"bitvec2:"<<bitvec2<<endl;
	for (int i = 0; i < 32; i++)
	{
		key[i] = bitvec2[i];
		key[i+32] = bitvec1[i];
	}
	//cout<<"key= :"<<key<<endl;
}

