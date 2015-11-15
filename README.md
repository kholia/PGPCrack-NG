Update
======

Please use https://github.com/magnumripper/JohnTheRipper/ instead!

Yes, JtR supports cracking symmetrically encrypted PGP files now :)

PGPCrack-NG
===========

PGPCrack-NG is a program designed to brute-force symmetrically encrypted PGP files.

0. On Fedora 19, do ```sudo yum install libassuan-devel -y```. On Ubuntu, do ```sudo apt-get install libpth-dev libbz2-dev libassuan-dev libgcrypt20-dev libgpg-error-dev```.

1. Compile using ```make```. You might need to edit
   ```-I/usr/include/libassuan2``` part in the Makefile.

2. Run ```cat password.lst  | ./PGPCrack-NG <PGP file>```

3. ```john -i -stdout | ./PGPCrack-NG <PGP file>```

Speed: > 1330 passwords / second on AMD X3 720 CPU @ 2.8GHz (using single core).

TODO
----

* Rebase to GnuPG modern (2.1.3)
