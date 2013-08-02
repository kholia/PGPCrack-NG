target:
	gcc -I/usr/include/libassuan2 -Wall -Wno-pointer-sign -O3 *.c -lgcrypt -lgpg-error -lbz2 -lz -I. -o PGPCrack-NG
