#include<bits/stdc++.h>
#pragma once 
#include "parts/md5.h"
using namespace std;
uint64_t DJBH2(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        return 0;
    }
    uint64_t hash = 5381;
    char c;
    const int bufferSize = 1024 * 1024;
    vector<char> buffer(bufferSize);
    while (file.read(buffer.data(), bufferSize)) {
        size_t bytesRead = file.gcount();
        for (size_t i = 0; i < bytesRead; i++) {
            hash = ((hash << 5) + hash) + buffer[i];
        }
    }
    size_t bytesRead = file.gcount();
    for (size_t i = 0; i < bytesRead; i++) {
        hash = ((hash << 5) + hash) + buffer[i];
    }
    return hash;
}
uint32_t CRC32(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) return 0;
    uint32_t crc = 0xFFFFFFFF;
    const int bufferSize = 1024 * 1024;
    vector<char> buffer(bufferSize);
    while (file.read(buffer.data(), bufferSize)) {
        size_t bytesRead = file.gcount();
        for (size_t i = 0; i < bytesRead; i++) {
            crc ^= static_cast<uint8_t>(buffer[i]);
            for (int j = 0; j < 8; j++) {
                crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
            }
        }
    }
    size_t bytesRead = file.gcount();
    for (size_t i = 0; i < bytesRead; i++) {
        crc ^= static_cast<uint8_t>(buffer[i]);
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
        }
    }
    return ~crc;
}
uint64_t CRC64(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) return 0;
    uint64_t crc = 0xFFFFFFFFFFFFFFFFULL;
    const int bufferSize = 1024 * 1024;
    vector<char> buffer(bufferSize);
    while (file.read(buffer.data(), bufferSize)) {
        size_t bytesRead = file.gcount();
        for (size_t i = 0; i < bytesRead; i++) {
            crc ^= static_cast<uint8_t>(buffer[i]);
            for (int j = 0; j < 8; j++) {
                crc = (crc >> 1) ^ (0xC96C5795D7870F42ULL & -(crc & 1));
            }
        }
    }
    size_t bytesRead = file.gcount();
    for (size_t i = 0; i < bytesRead; i++) {
        crc ^= static_cast<uint8_t>(buffer[i]);
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xC96C5795D7870F42ULL & -(crc & 1));
        }
    }
    return ~crc;
}
uint32_t XXH32(const string& filePath) {
    ifstream inputFile(filePath, ios::binary);
    if (!inputFile.is_open()) {
        return 0;
    }
    const uint32_t PRIME32_1 = 0x9E3779B1U;
    const uint32_t PRIME32_2 = 0x85EBCA77U;
    const uint32_t PRIME32_3 = 0xC2B2AE3DU;
    const uint32_t PRIME32_4 = 0x27D4EB2FU;
    const uint32_t PRIME32_5 = 0x165667B1U;
    uint32_t h32 = 0;
    vector<char> buffer(1024 * 1024);
    auto rotl32 = [](uint32_t x, int n) {
        return (x << n) | (x >> (32 - n));
    };
    while (inputFile.read(buffer.data(), buffer.size())) {
        const char* p = buffer.data();
        const char* const end = p + inputFile.gcount();
        while (p + 16 <= end) {
            uint32_t k1;
            memcpy(&k1, p, sizeof(k1));
            uint32_t k2;
            memcpy(&k2, p + 4, sizeof(k2));
            uint32_t k3;
            memcpy(&k3, p + 8, sizeof(k3));
            uint32_t k4;
            memcpy(&k4, p + 12, sizeof(k4));
            h32 ^= (k1 * PRIME32_2);
            h32 = rotl32(h32, 13);
            h32 *= PRIME32_1;
            h32 ^= (k2 * PRIME32_2);
            h32 = rotl32(h32, 13);
            h32 *= PRIME32_1;
            h32 ^= (k3 * PRIME32_2);
            h32 = rotl32(h32, 13);
            h32 *= PRIME32_1;
            h32 ^= (k4 * PRIME32_2);
            h32 = rotl32(h32, 13);
            h32 *= PRIME32_1;
            p += 16;
        }
        if (p < end) {
            size_t rem_len = end - p;
            h32 ^= rem_len; 
            while (p + 4 <= end) {
                uint32_t k;
                memcpy(&k, p, sizeof(k));
                h32 ^= (k * PRIME32_3);
                h32 = rotl32(h32, 17);
                h32 *= PRIME32_4;
                p += 4;
            }
            if (p + 2 <= end) {
                uint16_t k;
                memcpy(&k, p, sizeof(k));
                h32 ^= (k * PRIME32_5);
                h32 = rotl32(h32, 11);
                h32 *= PRIME32_1;
                p += 2;
            }
            while (p < end) {
                h32 ^= (*p) * PRIME32_5;
                h32 = rotl32(h32, 11);
                h32 *= PRIME32_1;
                p++;
            }
        }
    }
    size_t last_read_len = inputFile.gcount();
    if (last_read_len > 0) {
        const char* p = buffer.data();
        const char* const end = p + last_read_len;
        h32 ^= last_read_len;
        while (p + 4 <= end) {
            uint32_t k;
            memcpy(&k, p, sizeof(k));
            h32 ^= (k * PRIME32_3);
            h32 = rotl32(h32, 17);
            h32 *= PRIME32_4;
            p += 4;
        }
        if (p + 2 <= end) {
            uint16_t k;
            memcpy(&k, p, sizeof(k));
            h32 ^= (k * PRIME32_5);
            h32 = rotl32(h32, 11);
            h32 *= PRIME32_1;
            p += 2;
        }
        while (p < end) {
            h32 ^= (*p) * PRIME32_5;
            h32 = rotl32(h32, 11);
            h32 *= PRIME32_1;
            p++;
        }
    }
    h32 ^= h32 >> 15;
    h32 *= PRIME32_2;
    h32 ^= h32 >> 13;
    h32 *= PRIME32_3;
    h32 ^= h32 >> 16;
    return h32;
}
uint64_t XXH64(const string& filePath) {
    ifstream inputFile(filePath, ios::binary);
    if (!inputFile.is_open()) {
        return 0;
    }
    const uint64_t PRIME64_1 = 0x9E3779B185EBCA87ULL;
    const uint64_t PRIME64_2 = 0xC2B2AE3D27D4EB4FULL;
    const uint64_t PRIME64_3 = 0x165667B19E3779F9ULL;
    const uint64_t PRIME64_4 = 0x85EBCA77C2B2AE63ULL;
    const uint64_t PRIME64_5 = 0x27D4EB2F165667B1ULL;
    uint64_t h64 = 0;
    vector<char> buffer(1024 * 1024);
    auto rotl64 = [](uint64_t x, int n) {
        return (x << n) | (x >> (64 - n));
    };
    while (inputFile.read(buffer.data(), buffer.size())) {
        const char* p = buffer.data();
        const char* const end = p + inputFile.gcount();
        while (p + 32 <= end) {
            uint64_t k1 = *reinterpret_cast<const uint64_t*>(p);
			uint64_t k2 = *reinterpret_cast<const uint64_t*>(p + 8);
            uint64_t k3 = *reinterpret_cast<const uint64_t*>(p + 16);
            uint64_t k4 = *reinterpret_cast<const uint64_t*>(p + 24);
            h64 ^= (k1 * PRIME64_2);
            h64 = rotl64(h64, 31);
            h64 *= PRIME64_1;
            h64 ^= (k2 * PRIME64_2);
            h64 = rotl64(h64, 31);
            h64 *= PRIME64_1;
            h64 ^= (k3 * PRIME64_2);
            h64 = rotl64(h64, 31);
            h64 *= PRIME64_1;
            h64 ^= (k4 * PRIME64_2);
            h64 = rotl64(h64, 31);
            h64 *= PRIME64_1;
            p += 32;
        }
        if (p < end) {
            size_t rem_len = end - p;
            h64 ^= rem_len; 
            while (p + 8 <= end) {
                uint64_t k = *reinterpret_cast<const uint64_t*>(p);
                h64 ^= (k * PRIME64_2);
                h64 = rotl64(h64, 31);
                h64 *= PRIME64_1;
                p += 8;
            }
            if (p + 4 <= end) {
                uint32_t k = *reinterpret_cast<const uint32_t*>(p);
                h64 ^= (k * PRIME64_1);
                h64 = rotl64(h64, 17);
                h64 *= PRIME64_2;
                p += 4;
            }
            while (p < end) {
                h64 ^= (*p) * PRIME64_5;
                h64 = rotl64(h64, 11);
                h64 *= PRIME64_1;
                p++;
            }
        }
    }
    size_t last_read_len = inputFile.gcount();
    if (last_read_len > 0) {
        const char* p = buffer.data();
        const char* const end = p + last_read_len;
        h64 ^= last_read_len;
        while (p + 8 <= end) {
            uint64_t k = *reinterpret_cast<const uint64_t*>(p);
            h64 ^= (k * PRIME64_2);
            h64 = rotl64(h64, 31);
            h64 *= PRIME64_1;
            p += 8;
        }
        if (p + 4 <= end) {
            uint32_t k = *reinterpret_cast<const uint32_t*>(p);
            h64 ^= (k * PRIME64_1);
            h64 = rotl64(h64, 17);
            h64 *= PRIME64_2;
            p += 4;
        }
        while (p < end) {
            h64 ^= (*p) * PRIME64_5;
            h64 = rotl64(h64, 11);
            h64 *= PRIME64_1;
            p++;
        }
    }
    h64 ^= h64 >> 33;
    h64 *= PRIME64_2;
    h64 ^= h64 >> 29;
    h64 *= PRIME64_3;
    h64 ^= h64 >> 32;
    return h64;
}
