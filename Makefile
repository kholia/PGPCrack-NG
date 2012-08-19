target:
	gcc -O3 *.c -lgcrypt -lgpg-error -lbz2 -lz -I. -o PGPCrack-NG
