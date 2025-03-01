#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "stdint.h"

static uint32_t right_rotate(uint32_t v, int count) {
    return v >> count | v << (32 - count);
}

static uint32_t right_shift(uint32_t v, int count) {
    return v >> count;
}

static uint64_t swap_endian64(uint64_t v)
{
    return ((v & 0x00000000000000FF) << 56) |
        ((v & 0x000000000000FF00) << 40) |
        ((v & 0x0000000000FF0000) << 24) |
        ((v & 0x00000000FF000000) << 8) |
        ((v & 0x000000FF00000000) >> 8) |
        ((v & 0x0000FF0000000000) >> 24) |
        ((v & 0x00FF000000000000) >> 40) |
        ((v & 0xFF00000000000000) >> 56);
}

static uint32_t swap_endian32(uint32_t v)
{
    return ((v & 0x000000FF) << 24) |
        ((v & 0x0000FF00) << 8) |
        ((v & 0x00FF0000) >> 8) |
        ((v & 0xFF000000) >> 24);
}

static int append(uint8_t* dest, uint32_t prev_dest_len, uint8_t* src, uint32_t src_len)
{
    memcpy(dest + prev_dest_len, src, src_len);
    return src_len;
}

static void sha256(uint8_t message[], uint32_t original_message_byte_count)
{
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    static const uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    int message_length = 0;
    uint8_t* padded_message = calloc(original_message_byte_count + 1000, sizeof(uint8_t));

    message_length += append(padded_message, message_length, message, original_message_byte_count);

    // Append "1" bit
    uint8_t b1 = 0x80;
    message_length += append(padded_message, message_length, &b1, 1);

    // Append "0" bit until message length in  bits ¡Ý 448 (mod 512), that is in bytes ¡Ý 56 (mode 64) 
    int remainder = message_length % 64;
    int padded_byte_count = (remainder <= 56) ? (56 - remainder) : (64 - remainder + 56);
    message_length += padded_byte_count;

    // Append original message length in big endian
    uint64_t message_bit_count = swap_endian64(original_message_byte_count * 8);
    message_length += append(padded_message, message_length, &message_bit_count, 8);

    for (int chunk_i = 0; chunk_i < message_length; chunk_i += 64)
    {
        // create a 64-entry message schedule array w[0..63] of 32-bit words
        uint32_t words[64];
        for (int i = 0; i < 64; i++)
            words[i] = 0;

        for (int words_i = 0; words_i < 16; words_i++)
        {
            words[words_i] = swap_endian32(*(uint32_t*)(padded_message + chunk_i + words_i * 4));
        }
        for (int words_i = 16; words_i < 64; words_i++)
        {
            uint32_t s0 = right_rotate(words[words_i - 15], 7) ^ right_rotate(words[words_i - 15], 18) ^ right_shift(words[words_i - 15], 3);
            uint32_t s1 = right_rotate(words[words_i - 2], 17) ^ right_rotate(words[words_i - 2], 19) ^ right_shift(words[words_i - 2], 10);
            words[words_i] = words[words_i - 16] + s0 + words[words_i - 7] + s1;
        }


        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        for (int i = 0; i < 64; i++)
        {
            uint32_t S1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h + S1 + ch + k[i] + words[i];
            uint32_t S0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;

        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    uint8_t hash[64];
    h0 = swap_endian32(h0);
    memcpy(hash + 0 * 4, &h0, 4);
    h1 = swap_endian32(h1);
    memcpy(hash + 1 * 4, &h1, 4);
    h2 = swap_endian32(h2);
    memcpy(hash + 2 * 4, &h2, 4);
    h3 = swap_endian32(h3);
    memcpy(hash + 3 * 4, &h3, 4);
    h4 = swap_endian32(h4);
    memcpy(hash + 4 * 4, &h4, 4);
    h5 = swap_endian32(h5);
    memcpy(hash + 5 * 4, &h5, 4);
    h6 = swap_endian32(h6);
    memcpy(hash + 6 * 4, &h6, 4);
    h7 = swap_endian32(h7);
    memcpy(hash + 7 * 4, &h7, 4);

    printf("SHA256 of \"%s\":\n", message);
    for (int i = 0; i < 32; i++)
        printf("%02x", hash[i]);
    printf("\n\n");
}

void sha256_main()
{
    char* msg = "";
    sha256(msg, strlen(msg));
    msg = "The quick brown fox jumps over the lazy dog";
    sha256(msg, strlen(msg));
    msg = "The quick brown fox jumps over the lazy dog.";
    sha256(msg, strlen(msg));
    msg = "The quick brown fox jumps over the lazy dog once again.";
    sha256(msg, strlen(msg));
    msg = "A group of birds flew over the mountain during the sunset.";
    sha256(msg, strlen(msg));
    msg = "In the quiet evening, the city lights began to flicker one by one.";
    sha256(msg, strlen(msg));
    msg = "She whispered softly into the night, hoping her words would be heard.";
    sha256(msg, strlen(msg));
    msg = "Under the bright moonlight, the forest seemed both peaceful and alive.";
    sha256(msg, strlen(msg));
    msg = "As the rain gently tapped on the window, she sat by the fire, lost in thought, with a book in hand, letting her mind wander far beyond the room.";
    sha256(msg, strlen(msg));
    msg = "On a warm summer evening, the stars twinkled brightly above, while the ocean waves crashed softly against the shore, lulling everyone to sleep.";
    sha256(msg, strlen(msg));
    msg = "The concert hall was filled with the sound of violins, and the audience sat in awe as the symphony played a melody that resonated deep within their hearts.";
    sha256(msg, strlen(msg));
}