##############################
###        FEATURES        ###
##############################

A secure password encrypter that uses One-Time Pad (OTP) encryption for maximum security.

OTP encryption is a highly secure method which is nearly impossible to break if used correctly.

The encryption software automatically saves your keys to a file called "keys.csv"

This software comes with a decrypter that reads the "keys.csv" file and decrypts the encrypted message inputted


##############################
######      USAGE       ######
##############################

bash: g++ OTP.cpp -o encrypt

bash: ./encrypt

NOTE: Make sure to save the encrypted output or else your encrypted password will be lost!

NOTE: For the decryption program, simply run the following:

bash: python3 decrypt.py


##############################
##       REQUIREMENTS       ##
##############################

C++ Compiler

Python3


##############################
##     RECOMMENDATIONS      ## 
##############################

Save the "keys.csv" file to an external usb drive (If you do this, simply change the file path to "keys.csv" in decrypt.py)


Disclaimer:

OTP encryption is very secure when used correctly. However, the responsibility for securely managing OTP keys lies with the user. Ensure that keys are not accidentally shared, copied, or stored insecurely.

THANK YOU!

~ Stay Secure!


