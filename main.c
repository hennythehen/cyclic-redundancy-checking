#include <stdio.h>

#include "crc.h"

void errorTest(int error, int enc_data, int divisor) {
  //fake transit error
  int pseudo_recv_data = enc_data ^ error;
  int crc_result = crc_6_dec(&pseudo_recv_data, divisor);
  if (crc_result == 0) {
    printf("Success -- Data received: %d\n", pseudo_recv_data);
  } else {
    printf("Error   -- Data received: %d\n", pseudo_recv_data);
  }
}

int main() {
  int data = 46;
  int divisor = 10;

  printf("Using CRC on 46 to check if errors are detected\n");

  int enc_data = crc_6_enc(data, divisor);

  printf("\nForcing 1 bit corruption. Should detect error.\n");
  errorTest(16, enc_data, divisor);

  printf("\nForcing 2 bit corruption. Should detect error.\n");
  errorTest(33, enc_data, divisor);

  printf("\nForcing 3 bit corruption. Should NOT detect error.\n");
  errorTest(35, enc_data, divisor);
}