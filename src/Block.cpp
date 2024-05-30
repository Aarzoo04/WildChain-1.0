#include "Block.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
std::string get_config_value(const std::string& filename, const std::string& key);

using namespace Blockchain;

block::block(block *prevBlock)
{
    previous_block = prevBlock;
    if (prevBlock)
    {
        memcpy(previousHash, prevBlock->gethash(), SHA256_DIGEST_LENGTH);
    }
    else
    {
        memset(previousHash, 0, SHA256_DIGEST_LENGTH);
    }

    timestamp_currBlock = time(0);

    details_hash= readDataHashFromFile();
    nonce = 0;

    calculateHash();
}

std::string block::readDataHashFromFile() {
    std::string data_hash_path = get_config_value("config.ini", "data_hash_path");
    std::ifstream file(data_hash_path);
    std::string content;
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line;
            content += '\n'; // Adding newline character to maintain line breaks
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file " << std::endl;
    }
    
    return content;

}

void block::calculateHash()
{
    uint32_t size_payload = SHA256_DIGEST_LENGTH + sizeof(time_t) + details_hash.size() + sizeof(uint32_t);
    uint8_t *buf = new uint8_t[size_payload];
    uint8_t *ptr = buf;

    memcpy(ptr, previousHash, SHA256_DIGEST_LENGTH);
    ptr += SHA256_DIGEST_LENGTH;
    memcpy(ptr, &timestamp_currBlock, sizeof(time_t));
    ptr += sizeof(time_t);
    memcpy(ptr, details_hash.c_str(), details_hash.size());
    ptr += details_hash.size();
    memcpy(ptr, &nonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buf, size_payload);
    SHA256_Final(Hash, &sha256);
}

uint8_t *block::gethash()
{
    return Hash;
}

std::string block::getHashstr()
{
    char buf[SHA256_DIGEST_LENGTH * 2 + 1];
    for (uint32_t n = 0; n < SHA256_DIGEST_LENGTH; n++)
    {
        sprintf(buf + (n * 2), "%02x", Hash[n]);
    }
    buf[SHA256_DIGEST_LENGTH * 2] = 0;
    return std::string(buf);
}

block *block::getpreviousblock()
{
    return previous_block;
}

void block::appendData(std::string details_hash)
{
    this->details_hash = details_hash;
}

bool block::isdifficulty(int difficulty)
{
    for (uint32_t n = 0; n < difficulty; n++)
    {
        if (Hash[n] != 0)
        {
            return false;
        }
    }
    return true;
}

void block::mine(int difficulty)
{
    while (!isdifficulty(difficulty))
    {
        nonce++;
        calculateHash();
    }
}

uint32_t block::getnonce()
{
    return nonce;
}
