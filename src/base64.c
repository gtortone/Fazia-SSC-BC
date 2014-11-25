#include <string.h>

#include <Generic.h>
#include "base64.h"

static const char *base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

static BOOL is_base64(unsigned char c) {
   return (c >= 32 && c <= 126);
}

int findchar(unsigned char const *s, unsigned char const ch) {

   UINT i;
   for(i=0;i<strlen((const char *)s);i++)
      if(s[i] == ch) return(i);

   return(-1);
}

void base64_encode(unsigned char const *src, char *dst, UINT in_len) {

   int i = 0;
   int j = 0;
   unsigned char char_array_3[3];
   unsigned char char_array_4[4];
   UINT sp = 0;

   while (in_len--) {
      char_array_3[i++] = *(src++);
      if (i == 3) {
         char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
         char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
         char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
         char_array_4[3] = char_array_3[2] & 0x3f;

         for (i = 0; (i < 4); i++)
            dst[sp++] = base64_chars[char_array_4[i]];
         i = 0;
      }
   }

   if (i) {
      for (j = i; j < 3; j++)
         char_array_3[j] = '\0';

      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (j = 0; (j < i + 1); j++)
         dst[sp++] = base64_chars[char_array_4[j]];

      while ((i++ < 3))
         dst[sp++] = '=';

   }

   dst[sp] = '\0';
}

void base64_decode(unsigned char const *src, char *dst, UINT *out_len) {

   UINT in_len = strlen((const char *) src);
   int i = 0;
   int j = 0;
   int in_ = 0;
   unsigned char char_array_4[4], char_array_3[3];
   UINT sp = 0;

   while (in_len-- && (src[in_] != '=') && is_base64(src[in_])) {
      char_array_4[i++] = src[in_];
      in_++;
      if (i == 4) {
         for (i = 0; i < 4; i++)
            char_array_4[i] = findchar((unsigned char const *)base64_chars,char_array_4[i]);

         char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
         char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
         char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

         for (i = 0; (i < 3); i++)
            dst[sp++] = char_array_3[i];
         i = 0;
      }
   }

   if (i) {
      for (j = i; j < 4; j++)
         char_array_4[j] = 0;

      for (j = 0; j < 4; j++)
         char_array_4[j] = findchar((unsigned char const *)base64_chars,char_array_4[j]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (j = 0; (j < i - 1); j++) dst[sp++] = char_array_3[j];
   }

   *out_len = sp;
}
