#include<bits/stdc++.h>
#include"hash.h"
#pragma once
constexpr int HASHFILE_BUFFER_SIZE=256*1024;
namespace _sha3{
	#include"parts/hash/sha3.h"
} 
namespace _sha256{
	#include"parts/hash/sha256.h"
}
namespace _sha1{
	#include"parts/hash/sha1.h"
}
string hashstr(const string& data,int bits=256){
	return _sha3::SHA3((_sha3::SHA3::Bits)bits)(data);
}
string hashfile(const string& file,int bits=256){
	_sha3::SHA3 sha3((_sha3::SHA3::Bits)bits);
	ifstream fin(file,ios::binary);
	char buffer[HASHFILE_BUFFER_SIZE];
	while(fin.read(buffer,sizeof(buffer))){
		sha3.add(buffer,sizeof(buffer));
	}
	sha3.add(buffer,fin.gcount());
	return sha3.getHash();
}
string hashstr3(const string& data,int bits=256){
	return hashstr(data,bits);
}
string hashfile3(const string& file,int bits=256){
	return hashfile(file,bits);
}
string hashstr256(const string& data){
	return _sha256::SHA256()(data);
}
string hashfile256(const string& file){
	_sha256::SHA256 sha256;
	ifstream fin(file,ios::binary);
	char buffer[HASHFILE_BUFFER_SIZE];
	while(fin.read(buffer,sizeof(buffer))){
		sha256.add(buffer,sizeof(buffer));
	}
	sha256.add(buffer,fin.gcount());
	return sha256.getHash();
}
string hashstr1(const string& data){
	return _sha1::SHA1()(data);
}
string hashfile1(const string& file){
	_sha1::SHA1 sha1;
	ifstream fin(file,ios::binary);
	char buffer[HASHFILE_BUFFER_SIZE];
	while(fin.read(buffer,sizeof(buffer))){
		sha1.add(buffer,sizeof(buffer));
	}
	sha1.add(buffer,fin.gcount());
	return sha1.getHash();
}
