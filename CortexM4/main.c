#include <stdio.h>
#include <stdlib.h>

#include "stm32wrapper.h"

#include <time.h>
#include "common/random.h"
#include "api.h"
#include "poly.h"
#include "pack.h"
#include "sample.h"
#include "params.h"
#include "gauss.h"
#include "utils.h"

#define MLEN 59
//#define NRUNS 10
#define NTESTS 1000

unsigned char mi[MLEN];
unsigned char mo[MLEN+CRYPTO_BYTES];
unsigned char sm[MLEN+CRYPTO_BYTES];

unsigned char pk[CRYPTO_PUBLICKEYBYTES];
unsigned char sk[CRYPTO_SECRETKEYBYTES];


unsigned long long smlen, mlen;

masked_poly msk, me;
poly t;



unsigned char seed[CRYPTO_RANDOMBYTES];


int f(int);
static unsigned long long overflowcnt = 0;

void sys_tick_handler(void)
{
  ++overflowcnt;
}

static void printcycles(const char *s, unsigned long long c)
{
  char outs[32];
  send_USART_str(s);
  snprintf(outs,sizeof(outs),"%llu\n",c);
  send_USART_str(outs);
}




int main (void)
{
    clock_setup(CLOCK_BENCHMARK);
    gpio_setup();
    usart_setup(115200);
    systick_setup();
    rng_enable();
	
    unsigned int t0, t1;

    //send_USART_str("\n===================================");
    
    /*int b;

    t0 = systick_get_value();
    overflowcnt = 0;
    b = f(1);
    t1 = systick_get_value();
    printcycles("cycles function:", (t0+overflowcnt*2400000llu)-t1);
    printcycles("b:",b);
    
    ++b;


    //int a;
    //char buf[10];*/
    unsigned int i, j;
    unsigned char r;
    int valid, response;
    srand48(time(NULL));

    send_USART_str("Hello there, I'm gonna sign\n"); 

    randombytes(mi, MLEN);

    //crypto_masked_keypair(msk, me, pk, seed);



    crypto_sign_keypair(pk, sk);

    

    



    /*
    t0 = systick_get_value();
    overflowcnt = 0;

    crypto_masked_sign(sm, &smlen, mi, MLEN, msk, me, seed);

    t1 = systick_get_value();
    printcycles("cycles function:", (t0+overflowcnt*2400000llu)-t1);
  
    send_USART_str("\n \n \n");

    valid = crypto_sign_open(mo, &mlen, sm, smlen, pk);

    if (valid != 0) {
      send_USART_str("Signature verification FAILED. \n");
      //send_USART_str("Error %i", valid);
      return -1;
    } else if (mlen != MLEN) {
      send_USART_str("crypto_sign_open returned BAD message length. \n");
      return -1;
    }

    for (j = 0; j < mlen; j++) {
      if (mi[j] != mo[j]) {
        send_USART_str ("crypto_sign_open returned BAD message value. \n");
        return -1;
      }
    }

    // Change something in the signature somewhere    
    randombytes(&r, 1);
    sm[r % (MLEN+CRYPTO_BYTES)] ^= 1;
    response = crypto_sign_open(mo, &mlen, sm, smlen, pk);
    if (response == 0) {
      send_USART_str("Corrupted signature VERIFIED. \n");
      return -1;
    }
  
    send_USART_str("Signature tests PASSED... \n\n");*/


    //printf("Reject z: %llu\nReject w: %llu\n", rejyzctr, rejwctr);




	while(1) {
    send_USART_str("S\n");
    for(int i=0; i < NRUNS; ++i){
      t0 = systick_get_value();
      overflowcnt = 0;

      //crypto_masked_sign(sm, &smlen, mi, MLEN, msk, me, seed);
      crypto_sign(sm, &smlen, mi, MLEN, sk);
      t1 = systick_get_value();
      printcycles("", (t0+overflowcnt*2400000llu)-t1);

    }
    send_USART_str("D\n");
  }

    return 0;
}
