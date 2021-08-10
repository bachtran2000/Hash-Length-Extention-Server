/* length_ext.c */
#include <stdio.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

int main(int argc, const char *argv[])
{
int i;
unsigned char buffer[SHA256_DIGEST_LENGTH];
SHA256_CTX c;
SHA256_Init(&c);
for(i=0; i<64; i++)
SHA256_Update(&c, "*", 1);

// MAC of the original message M (padded) c0616b825c8235aabf20c1865c12d4bb268f826f815b07862876fc7387e3a6ad
c.h[0] = htole32(0xf8890d3d);
c.h[1] = htole32(0x75937cbb);
c.h[2] = htole32(0xe1cd3f11);
c.h[3] = htole32(0xc9cbd9ca);
c.h[4] = htole32(0x843abe50);
c.h[5] = htole32(0x4be60aa5);
c.h[6] = htole32(0xa5e9f241);
c.h[7] = htole32(0x3b88a872);

// Append additional message
SHA256_Update(&c, "&download=secret.txt", 20);
SHA256_Final(buffer, &c);

for(i = 0; i < 32; i++) {
printf("%02x", buffer[i]);
}
printf("\n");
return 0;
}