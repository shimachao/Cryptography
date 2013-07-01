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
   密钥的获取,用strng对象保存用户的输入，getline(cin,str,)输入str后，如果str不足64位
   用0补齐。然后用这个str对象初始化一个bitset对象，再申请一个56bit的bitset对象，用之前的bitset来初始化它，第7，15，23，31，39，47，55，63位为奇偶验证位，不要。
*/
#include <iostream>
#include <bitset>
using namespace std;
int main(void)
{
	char str[64];
	cin.getline(str,64);
	string strr(str);
	bitset<64> bitvec(strr);

	cout<<endl<<bitvec<<endl;
	return 0;
}


