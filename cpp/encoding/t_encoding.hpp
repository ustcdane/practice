#ifndef H_ENCODER
#define H_ENCODER

#include <iconv.h>
#include <stdio.h>
#include <string.h>

// in: "%CA%E4:%C8%EBsogou"
// out: " ‰:»Îsogou" (assume gbk)
static int UrlDecode(const char *pIn, char *pOut, int maxLen)
{
    if( pIn == NULL )
        return 0;

    char *pOutPtr = pOut;
    char ch[12] = {0};
    int curLen = 0;
    while ( *pIn && curLen < maxLen )
    {
        if (*pIn == '%' )
        {
            if(sscanf(pIn, "%%%02X", ch) != 1)
                return -1;
            *pOutPtr = ch[0];
            ++pOutPtr;
            ++curLen;
            pIn += 3;
        }
        else
        {
            *pOutPtr = *pIn;
            ++pOutPtr;
            ++curLen;
            ++pIn;
        }
    }

    pOut[curLen] = 0;
    return curLen;
}

typedef unsigned short ushort;

//return -1 if error, else return the ucs2 characters converted
static int iconv_wrapper_gbk2ucs2(const char* inbuf
                                , ushort* outbuf, size_t maxOutLenByte)
{
    //http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Thread_002dLocal.html#Thread_002dLocal
    static __thread iconv_t *pcd_thread = NULL;
    if( pcd_thread == NULL )
    {
        pcd_thread = new iconv_t;
        *pcd_thread = iconv_open("UCS-2LE", "GBK");
    }
    iconv_t cd = *pcd_thread;
    if( cd == (iconv_t) -1 )
        return -1;
    size_t inLen = strnlen(inbuf, 1024);
    size_t outLenLeft = maxOutLenByte;
    size_t ret = iconv(cd, NULL, NULL, NULL, NULL);
    if( ret == (size_t) -1 )
        return -1;
    ret = iconv(cd, (char**)&inbuf, &inLen, (char**)&outbuf, &outLenLeft);
    //if( iconv_close(cd) == -1 || ret == (size_t) -1 )
    if( ret == (size_t) -1 )
    {
        return -1;
    }
    else
    {
        return (maxOutLenByte-outLenLeft)/sizeof(ushort);
    }

    // no iconv_close.
    // as the handle's life is equal to the server program,
    // regardless of memory leak
}

//return -1 if error, else return the gbk characters converted
static int iconv_wrapper_utf82gbk(const char* inbuf
                                , char* outbuf, size_t maxOutLenByte)
{
    //http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Thread_002dLocal.html#Thread_002dLocal
    static __thread iconv_t *pcd_thread = NULL;
    if( pcd_thread == NULL )
    {
        pcd_thread = new iconv_t;
        *pcd_thread = iconv_open("GBK", "UTF8");
    }
    iconv_t cd = *pcd_thread;
    if( cd == (iconv_t) -1 )
        return -1;
    size_t inLen = strnlen(inbuf, 1024);
    size_t outLenLeft = maxOutLenByte;
    size_t ret = iconv(cd, NULL, NULL, NULL, NULL);
    if( ret == (size_t) -1 )
        return -1;
    ret = iconv(cd, (char**)&inbuf, &inLen, (char**)&outbuf, &outLenLeft);
    //if( iconv_close(cd) == -1 || ret == (size_t) -1 )
    if( ret == (size_t) -1 )
    {
        return -1;
    }
    else
    {
        return maxOutLenByte-outLenLeft;
    }

    // no iconv_close.
    // as the handle's life is equal to the server program,
    // regardless of memory leak
}

//return -1 if error, else return the bytes converted
static int iconv_wrapper_ucs22gbk(const ushort* inbuf, size_t inLen
                                  , char* outbuf, size_t maxOutLenByte)
{
    //http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Thread_002dLocal.html#Thread_002dLocal
    static __thread iconv_t *pcd_thread = NULL;
    if( pcd_thread == NULL )
    {
        pcd_thread = new iconv_t;
        *pcd_thread = iconv_open("GBK", "UCS-2LE");
    }
    iconv_t cd = *pcd_thread;
    if( cd == (iconv_t) -1 )
        return -1;
    //size_t inLen = strnlen(inbuf, 1024);
    size_t outLenLeft = maxOutLenByte;
    size_t ret = iconv(cd, NULL, NULL, NULL, NULL);
    if( ret == (size_t) -1 )
        return -1;
    ret = iconv(cd, (char**)&inbuf, &inLen, (char**)&outbuf, &outLenLeft);
    //if( iconv_close(cd) == -1 || ret == (size_t) -1 )
    if( ret == (size_t) -1 )
    {
        return -1;
    }
    else
    {
        return maxOutLenByte-outLenLeft;
    }

    // no iconv_close.
    // as the handle's life is equal to the server program,
    // regardless of memory leak
}

static int iconv_wrapper_ucs22utf8(const ushort* inbuf, size_t inLen
                                   , char* outbuf, size_t maxOutLenByte)
{
    //http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Thread_002dLocal.html#Thread_002dLocal
    static __thread iconv_t *pcd_thread = NULL;
    if( pcd_thread == NULL )
    {
        pcd_thread = new iconv_t;
        *pcd_thread = iconv_open("UTF8", "UCS-2LE");
    }
    iconv_t cd = *pcd_thread;
    if( cd == (iconv_t) -1 )
        return -1;
    //size_t inLen = strnlen(inbuf, 1024);
    size_t outLenLeft = maxOutLenByte;
    size_t ret = iconv(cd, NULL, NULL, NULL, NULL);
    if( ret == (size_t) -1 )
        return -1;
    ret = iconv(cd, (char**)&inbuf, &inLen, (char**)&outbuf, &outLenLeft);
    //if( iconv_close(cd) == -1 || ret == (size_t) -1 )
    if( ret == (size_t) -1 )
    {
        return -1;
    }
    else
    {
        return maxOutLenByte-outLenLeft;
    }

    // no iconv_close.
    // as the handle's life is equal to the server program,
    // regardless of memory leak
}

#endif
