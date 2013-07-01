/*
*生成DES加密和解密的16个钥匙
*/
#ifndef _KEY_H_
#define _KEY_H_

#include <iostream>
#include <bitset>

using namespace std;

//判断本地机器数据的存储是否为大端模式
bool is_big_edian(void);

//获得用户的输入的密钥，用bitset对象保存,注意bitset二进制成员的顺序从右到左
void get_key(long long a,bitset <64> &key);

//生成加密和解密的16个把钥匙
void generate_keys(long long a);

#endif

