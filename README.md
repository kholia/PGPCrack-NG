PGPCrack-NG
===========

PGPCrack-NG is a program designed to brute-force symmetrically encrypted PGP files

1. Compile using ```make```

2. Run ```cat ~/magnum-jumbo/run/password.lst  | ./PGPCrack-NG <PGP file>```

3. ```john -i -stdout | ./PGPCrack-NG <PGP file>```

Speed: > 1330 passwords / second on AMD X3 720 CPU @ 2.8GHz (using single core).