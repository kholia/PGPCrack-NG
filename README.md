PGPCrack-NG
===========

PGPCrack-NG is a program designed to brute-force symmetrically encrypted PGP files.

0. On Fedora 19, do ```sudo yum install libassuan-devel -y```. On Ubuntu, do ```sudo apt-get libpth-dev libbz2-dev libassuan-dev```.

1. Compile using ```make```. You might need to edit
   ```-I/usr/include/libassuan2``` part in the Makefile.

2. Run ```cat ~/magnum-jumbo/run/password.lst  | ./PGPCrack-NG <PGP file>```

3. ```john -i -stdout | ./PGPCrack-NG <PGP file>```

Speed: > 1330 passwords / second on AMD X3 720 CPU @ 2.8GHz (using single core).
