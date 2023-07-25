#include <iostream>
using namespace std;
// char arr[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
string arr={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
string encrypt(string plaintext,int key){
    string ciphertext ="";
    int i=0;
    while(i<plaintext.length()){
       ciphertext+= arr[(key+arr.find(plaintext[i]))%26];
       i++;
    }
    return ciphertext;
}
int main(int argc, char** argv){
    int key = atoi(argv[1]);
    string plaintext=argv[2];
    string ciphertext= encrypt(plaintext,key);
    cout<< ciphertext<<endl;

}

