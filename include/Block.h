#ifndef __C_BLOCK_INCLUDED__
#define __C_BLOCK_INCLUDED__
#include <openssl/sha.h>
#include <string>
#include <ctime>

namespace Blockchain
{
    class block
    {         
    private:
        uint8_t Hash[SHA256_DIGEST_LENGTH];
        uint8_t previousHash[SHA256_DIGEST_LENGTH];
        block *previous_block;
        block *next_update;
        std::string details_hash;
        time_t timestamp_currBlock;
        uint32_t nonce;

    public:
        block(block *prevBlock);
        void calculateHash();
        std::string readDataHashFromFile();
        uint8_t *gethash();
        std::string getHashstr();
        block *getpreviousblock();
        void appendData(std::string details_hash);
        block* setnextupdate(block* next);
        bool isdifficulty(int difficulty);
        void mine(int difficulty);
        uint32_t getnonce();
    };
}

#endif
