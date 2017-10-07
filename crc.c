#include "crc.h"
#include <stdio.h>

int crc_6_div(int data, int divisor) {
  //shift the divisor so the significant bits of data and divisor line up
  divisor <<= 5;

  //high_order_bit tracks the left end of the divisor and indicates
  //when the next XOR operation needs to happen
  int high_order_bit = 1; high_order_bit <<= 8;
  //low order bit tracks the right end of the divisor.
  //this prevents the divisor from being right-shifted to lose data.
  int low_order_bit = 1; low_order_bit <<= 5;
  int remain = data;
  
  while (low_order_bit > 1) {
    remain = remain ^ divisor;
    //keep shifting the divisor right until it reaches the end
    //or it reaches the next appropriate XOR position
    while (high_order_bit > remain && low_order_bit > 1) {
      high_order_bit >>= 1;
      low_order_bit >>= 1;
      divisor >>= 1;
    }
  }
  
  //occurs only during decoding and indicates no errors.
  if (remain == divisor) {
    return 0;
  }

  //shift 1 bit to get the remainder to length 3
  remain >>= 1;
  return remain;
}

int crc_6_enc(int data, int divisor) {
  //ensures data contains at most 6 bits of data
  if (data > 63 || data < 0) {
    return -1;
  }
  //ensures divisor is at most 4 bits of data
  if (divisor > 15 || data <= 0) {
    return -1;
  }

  //insert r = 3 bits to the right
  data = data << 3;


  int r = crc_6_div(data, divisor);
  data += r;
  return data;
}

int crc_6_dec(int* data, int divisor) {
  int r = crc_6_div((*data), divisor);
  (*data) >>= 3;
  if (r != 0) {
    return -1;
  } else {
    return 0;
  }
}