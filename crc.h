
//returns -1 if data is out of range (greater than 255)
int crc_6_enc(int data, int divisor);

//returns 0 if no error is detected.
//the data argument will be bit shifted to delete the redundant bits
int crc_6_dec(int* data, int divisor);