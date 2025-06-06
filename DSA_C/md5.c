#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "stdint.h"

static uint32_t left_rotate(uint32_t v, int count) {
    return (v << count) | (v >> (32 - count));
}

static uint32_t swap_endian(uint32_t v) {
    return ((v >> 24) & 0x000000FF) | ((v >> 8) & 0x0000FF00) | ((v << 8) & 0x00FF0000) | ((v << 24) & 0xFF000000);
}

static int append(uint8_t* dest, uint32_t prev_dest_len, uint8_t* src, uint32_t src_len)
{
    memcpy(dest + prev_dest_len, src, src_len);
    return src_len;
}

static void md5(uint8_t message[], uint32_t original_message_byte_count)
{
    uint32_t s[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                       5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                       4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                       6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };


    uint32_t K[64];
    for (int i = 0; i < 64; i++) {
        K[i] = (uint32_t)floor(pow(2, 32) * fabs(sin(i + 1)));
    }

    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    int message_length = 0;
    uint8_t* padded_message = calloc(original_message_byte_count + 1000, sizeof(uint8_t));

    message_length += append(padded_message, message_length, message, original_message_byte_count);

    // Append "1" bit
    uint8_t b = 0x80;
    message_length += append(padded_message, message_length, &b, 1);

    // Append "0" bit until message length in bits �� 448 (mod 512), that is in bytes �� 56 (mod 64)
    int remainder = message_length % 64;
    int padded_byte_count = remainder <= 56 ? (56 - remainder) : (64 - remainder + 56);
    message_length += padded_byte_count;

    // Append original length in bits
    uint64_t message_bit_count = original_message_byte_count * 8;
    message_length += append(padded_message, message_length, &message_bit_count, 8);

    for (int i = 0; i < message_length; i += 64)
    {
        uint32_t M[16];
        for (int j = 0; j < 16; j++)
            M[j] = *((uint32_t*)(&padded_message[i + j * 4]));

        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;

        for (int j = 0; j < 64; j++)
        {
            uint32_t F = 0;
            uint32_t g = 0;

            if (j < 16)
            {
                F = (B & C) | ((~B) & D);
                g = j;
            }
            else if (j < 32)
            {
                F = (D & B) | ((~D) & C);
                g = (5 * j + 1) % 16;
            }
            else if (j < 48)
            {
                F = B ^ C ^ D;
                g = (3 * j + 5) % 16;
            }
            else
            {
                F = C ^ (B | (~D));
                g = (7 * j) % 16;
            }

            F = F + A + K[j] + M[g];
            A = D;
            D = C;
            C = B;
            B = B + left_rotate(F, s[j]);
        }

        a0 = a0 + A;
        b0 = b0 + B;
        c0 = c0 + C;
        d0 = d0 + D;
    }

    free(padded_message);

    printf("MD5 of \"%s\":\n", message);
    printf("%08x%08x%08x%08x\n\n", swap_endian(a0), swap_endian(b0), swap_endian(c0), swap_endian(d0));
}

void md5_main()
{
    char* msg = "";
    md5(msg, strlen(msg));
    msg = "The quick brown fox jumps over the lazy dog";
    md5(msg, strlen(msg));
    msg = "The quick brown fox jumps over the lazy dog.";
    md5(msg, strlen(msg));
    msg = "The quick brown fox jumps over the lazy dog once again.";
    md5(msg, strlen(msg));
    msg = "A group of birds flew over the mountain during the sunset.";
    md5(msg, strlen(msg));
    msg = "In the quiet evening, the city lights began to flicker one by one.";
    md5(msg, strlen(msg));
    msg = "She whispered softly into the night, hoping her words would be heard.";
    md5(msg, strlen(msg));
    msg = "Under the bright moonlight, the forest seemed both peaceful and alive.";
    md5(msg, strlen(msg));
    msg = "As the rain gently tapped on the window, she sat by the fire, lost in thought, with a book in hand, letting her mind wander far beyond the room.";
    md5(msg, strlen(msg));
    msg = "On a warm summer evening, the stars twinkled brightly above, while the ocean waves crashed softly against the shore, lulling everyone to sleep.";
    md5(msg, strlen(msg));
    msg = "The concert hall was filled with the sound of violins, and the audience sat in awe as the symphony played a melody that resonated deep within their hearts.";
    md5(msg, strlen(msg));
}