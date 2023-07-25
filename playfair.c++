#include <iostream>
#include <cctype>
using namespace std;

void add_bogus(string &plaintext) {
    plaintext += "X";
}

int* find_index(char a, char** matrix) {
    if (a == 'J') {
        a = 'I';
    }
    int* indices = new int[2];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == a) {
                indices[0] = i;
                indices[1] = j;
                return indices; // Return here to prevent memory leak
            }
        }
    }
    return nullptr; // Return nullptr if character not found
}

string encryption(string plaintext, char** matrix) {
    if (plaintext.length() % 2 != 0) {
        add_bogus(plaintext);
    }

    string encrypted;
    for (int i = 0; i < plaintext.length(); i += 2) {
        int* indices1 = find_index(plaintext[i], matrix);
        int* indices2 = find_index(plaintext[i + 1], matrix);
        if (indices1 == nullptr || indices2 == nullptr) {
            // Handle characters not found in the matrix
            delete[] indices1;
            delete[] indices2;
            return "Error: Characters not found in the matrix.";
        }
    

        if (indices1[0] == indices2[0]) {
            indices1[1]=(indices1[1]+1)%5;
            indices2[1]=(indices2[1]+1)%5;
        }
        else if(indices1[1]==indices2[1]){
            indices1[0]=(indices1[0]+1)%5;
            indices2[0]=(indices2[0]+1)%5;
        }
        else{
            swap(indices1[1],indices2[1]);

        }

        encrypted += matrix[indices1[0]][indices1[1]];
        encrypted += matrix[indices2[0]][indices2[1]];

        delete[] indices1;
        delete[] indices2;
    }

    return encrypted;
}

char** make_table(string key) {
    int i = 0, j, k;
    int flag = 0;
    char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char** matrix = new char* [5];

    for (i = 0; i < 5; i++) {
        matrix[i] = new char[5];
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            matrix[i][j] = '+';
        }
    }

    // Populate the matrix with the key
    i = 0;
    for (j = 0; j < 5; j++) {
        for (k = 0; k < 5; k++) {
            if (i < key.length()) {
                matrix[j][k] = key[i];
                i++;
            } else {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }

    int alpha_index = 0;
    for (j = 0; j < 5; j++) {
        for (k = 0; k < 5; k++) {
            if (matrix[j][k] == '+') {
                while (key.find(alpha[alpha_index]) != string::npos) {
                    alpha_index++;
                }
                matrix[j][k] = alpha[alpha_index];
                alpha_index++;
            }
        }
    }

    return matrix;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <key> <plaintext>" << endl;
        return 1;
    }

    string key = argv[1];
    for(int i =0;i<key.length();i++){
        key[i]=toupper(key[i]);
    }
    string plaintext = argv[2];
    for(int i =0;i<plaintext.length();i++){
        plaintext[i]=toupper(plaintext[i]);
    }
    char** matrix = make_table(key);

    cout << "Key Matrix:" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    string encryptedText = encryption(plaintext, matrix);
    cout << "Encrypted Text: " << encryptedText << endl;

    // Deallocate memory
    for (int i = 0; i < 5; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
