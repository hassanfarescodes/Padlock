##############
###  NOTE  ###
##############

# ______________________________________________________________________________
# To change file path, change the "csv_filename" variable, should be on line 51 |
# ==============================================================================

import csv

def read_all_rows(csv_filename):
    """ Read all rows from a CSV file and store each row as an item in a list """
    rows = []
    with open(csv_filename, mode='r') as file:
        reader = csv.reader(file)
        for row in reader:
            if row: 
                rows.append(row)
    return rows

def otp_decrypt(encrypted_hex, otp_key_hex):
    """ Decrypt OTP-encrypted hex message using hex-format OTP key """
    encrypted_bytes = bytes.fromhex(encrypted_hex)
    otp_key_bytes = bytes.fromhex(otp_key_hex)
    decrypted_chars = [chr(e ^ k) for e, k in zip(encrypted_bytes, otp_key_bytes)]
    return ''.join(decrypted_chars)

def remove_index(s, index):
    """ Removes a character for a string at a specified index """
    if index < 0 or index >= len(s):
        raise ValueError("Index out of range")
    s = s.replace(s[index], "") 
    return s

def remove_padding(decrypted, indexes):
    """ Removes the padding after decryption """
    positions = indexes.split(" ")
    #print(positions)
    for i in reversed(positions):
        #print(i)
        decrypted = remove_index(decrypted, int(i))
        return decrypted

def is_hex(s):
    try:
        int(s, 16)  # Attempt to convert the string to an integer in base 16
        return True
    except ValueError:
        return False

csv_filename = "keys.csv"

all_rows = read_all_rows(csv_filename)  
line = 0
for i in all_rows:
    line+=1
    print("[" + str(line) + "]" + " " + str(i[0]) + " - " + str(i[1]))

def main():
    if all_rows:  # Check if its not empty
        encrypted = input("\n[*] Enter encrypted message (hex format): ")
        if(not is_hex(encrypted)):
            print("\n[!] FATAL: ENCRYPTED MESSAGE IS NOT IN HEX FORMAT!")
            return -1
        in_key = int(input("\n[*] Enter which key to use: "))
        if(in_key > line or in_key <= 0):
            print("\n[*] INVALID KEY SELECTION!")
            return -1

        first_key = all_rows[in_key-1][0]
        if(len(first_key) != len(encrypted)):
            print("\n[*] KEY SIZE MUST BE THE SAME AS TEXT LENGTH!")
            return -1

        second_key = all_rows[in_key-1][1]
        #print(second_key)
        decrypted = remove_padding(otp_decrypt(encrypted, first_key), second_key)
        print("\n[!] DECRYPTED: " + decrypted)

    else:
        print("\n[!] FATAL: NO KEYS FOUND!")
       
if __name__ == "__main__":
    main()


