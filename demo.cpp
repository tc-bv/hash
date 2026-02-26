#include<bits/stdc++.h>
#include"hashfunc+.h" 
using namespace std; 
int main(){
	cout<<"测试1：计算"<<__FILE__<<"的CRC32：";
	cout<<CRC32(__FILE__)<<endl;
	cout<<"测试2：计算"<<__FILE__<<"的CRC64：";
	cout<<CRC64(__FILE__)<<endl;
	cout<<"测试3：计算"<<__FILE__<<"的XXH32：";
	cout<<XXH32(__FILE__)<<endl;
	cout<<"测试4：计算"<<__FILE__<<"的XXH64：";
	cout<<XXH64(__FILE__)<<endl;
	cout<<"测试5：计算"<<__FILE__<<"的MD5(十六进制)：";
	cout<<FileMD5(__FILE__)<<endl;
	cout<<"测试6：计算字符串'tc-bv/hash'的SHA-256值：";
	cout<<hashstr256("tc-bv/hash")<<endl;
	cout<<"测试7：计算字符串'tc-bv/hash'的SHA3-384值：";
	cout<<hashstr3("tc-bv/hash",384)<<endl;
	cout<<"测试8：计算"<<__FILE__<<"的SHA1值：";
	cout<<hashfile1(__FILE__)<<endl;
}
