#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <random>
#include <fstream>
#include <termios.h>
#include <unistd.h>

using namespace std;

// Thank you patorjk for the font!
string menu = R"(
▗▄▄▖ ▗▞▀▜▌▐▌█  ▄▄▄  ▗▞▀▘█  ▄ 
▐▌ ▐▌▝▚▄▟▌▐▌█ █   █ ▝▚▄▖█▄▀  
▐▛▀▘   ▗▞▀▜▌█ ▀▄▄▄▀     █ ▀▄ 
▐▌     ▝▚▄▟▌█           █  █ 

)";


// Padding function with output for padding indexes
string padding(string& message, vector<int>& inserts, double d_padsize) {
    double padding_size = message.length() * d_padsize;
    string pads = "|";
    inserts.resize(padding_size);

    for (int i = 0; i < padding_size; i++) {
        message.insert(inserts[i], pads);
    }
    return message;	
}

// OTP Encryption Function
string OTP_encrypt(const string& message, string& otp_key_hex) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 255); 

    string otp_key;
    stringstream encrypted_hex_stream, key_hex_stream;

    for (char c : message) {
        char random_key_char = static_cast<char>(distribution(generator));
        otp_key += random_key_char;  // Build the OTP key
        char encrypted_char = c ^ random_key_char;  // XOR character with OTP key

        // Convert encrypted character and key character to hex and add to the streams
        encrypted_hex_stream << hex << setw(2) << setfill('0') << (static_cast<int>(encrypted_char) & 0xFF);
        key_hex_stream << hex << setw(2) << setfill('0') << (static_cast<int>(random_key_char) & 0xFF);
    }

    otp_key_hex = key_hex_stream.str(); // Store the OTP key in hex format
    return encrypted_hex_stream.str();   // Return the encrypted message in hex format
}

// Function to save the keys to the CSV file
void saveToCSV(const string& otp_key_hex, const vector<int>& padding_indexes) {
    ofstream file("keys.csv", ios::app);  // Open the key file in append mode
    if (file.is_open()) {
        file << otp_key_hex << ",";
        for (size_t i = 0; i <= padding_indexes.size(); ++i) {
            file << padding_indexes[i];
            if (i < padding_indexes.size()) file << " ";
        }
        file << "\n";
        file.close();
        cout << "[*] Keys appended to 'keys.csv'" << endl;
    } else {
        cerr << "Error: Unable to open file for appending." << endl;
    }
}


// Function to disable echo (used to hide password input)
void disableEcho() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);           // Get the terminal attributes
    tty.c_lflag &= ~ECHO;                    // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);  // Set the attributes
}

// Function to re-enable echo
void enableEcho() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);           // Get the terminal attributes
    tty.c_lflag |= ECHO;                     // Enable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);  // Set the attributes
}

// Encryption function used for inputting the password, encrypting it, and saving it
void encrypt() {
    string message;
    string checker;
    cout << "[-] Enter password: ";
    disableEcho();
    cin >> message;
    enableEcho();
    cout << "\n[-] Re-Enter password: ";
    disableEcho();
    cin >> checker;
    enableEcho();
    cout << "\n";
    if(message.compare(checker) != 0) {
    cout << "\n[!] PASSWORDS DO NOT MATCH, ENCRYPTION WILL NOT PROCEED!\n";
    return;
    }
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> padsize_dist(0.2, 1);

    double d_padsize = padsize_dist(generator);

    uniform_int_distribution<int> padtribution(0, message.length());
    vector<int> padtribe;
    for (int i = 0; i < message.length(); i++) {
        padtribe.push_back(padtribution(generator));
    }

    string padded_message = padding(message, padtribe, d_padsize);

    string otp_key_hex;
    string encrypted_message = OTP_encrypt(padded_message, otp_key_hex);

    saveToCSV(otp_key_hex, padtribe);

    cout << "[*] Encrypted (Hex Format): " << encrypted_message << endl;
    cout << "\n[!] MAKE SURE YOU HAVE SAVED THE ENCRYPTED OUTPUT (Hex Format)!\n";
}

// Proceed through the main function
int main() {
    cout << menu;
    encrypt();
    return 0;
}

