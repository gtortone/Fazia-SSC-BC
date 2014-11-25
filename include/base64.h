#ifndef _BASE64_H_
#define _BASE64_H_

int findchar(unsigned char const *s, unsigned char const ch);
void base64_encode(unsigned char const *src, char *dst, UINT in_len);
void base64_decode(unsigned char const *src, char *dst, UINT *out_len);


#endif

// EOF
