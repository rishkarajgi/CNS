#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void swap(int* a ,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rc4( char* msg , char* key , int key_len)
{
    int s[256];
    int i;
    for(i = 0 ; i < 256 ; i++)
    {
        s[i] = i;
    }

    int j = 0;
    for(i = 0 ; i < 256 ; i++)
    {
        j = (j + s[i] + key[i % key_len]) % 256;
        swap(&s[i] , &s[j]);
    }

    i = 0 , j = 0;
    int k;
    for(k = 0 ; k < 100 ; k++)
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(&s[i] , &s[j]);
        msg[k] = s[(s[i] + s[j]) % 256] ^ msg[k];
    }
}