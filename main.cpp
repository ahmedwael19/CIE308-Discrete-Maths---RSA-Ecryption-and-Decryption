#include<iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include<string>
#include <windows.h>
using namespace std;

//////variables/////
unsigned long long int number1,number2; //two prime numbers //private keys
unsigned long long int n; //public key
unsigned long long int m; //private key
unsigned long long int e; //public key
unsigned long long int a; //private key
const int Size = 1000; //The maximum size for the file
static long long TextDecrypted[Size];

//////functions//////

unsigned long long int power(unsigned long long int base, unsigned long long int power,unsigned long long int exp)
{
    unsigned long long int result = 1;      // Initialize result

    base = base % exp;  // Update base if it is more than or
    // equal to p

    while (power > 0)
    {
        // If power is odd, multiply x with result
        if (power & 1)
            result = (result*base) % exp;

        // exp must be even now
        power = power >> 1; // power = power/2
        base = (base*base) % exp;
    }
    return result;
}


void FirstNumber(void)
{
    bool isPrime;
    do
    {
        srand(time(0));
        number1 = abs(2*rand()%3000000+1); //to avoid overflow
        if (number1 > 1)
        {
            isPrime = true;
            for (int i = 2; i <= sqrt(number1); i++)
            {
                if (number1%i == 0)
                {
                    isPrime = false;
                    break;
                }
            }

        }

    }
    while (isPrime == false);
}
void SecondNumber(void)
{
    bool isPrime;
    do
    {
        isPrime = true;
        srand(time(0));
        number2 = abs(2 * rand()%1000000 + 1); //to avoid overflow
        if (number2 > 1)
        {
            for (int i = 2; i <= sqrt(number2); i++)
            {
                if (number2%i == 0)
                {
                    isPrime = false;
                    break;
                }
            }

        }

    }
    while (isPrime == false);

}
int gcd(unsigned long long int m, long long int e)
{
    if (m == 0)
        return e;
    return gcd(e%m, e);

}

bool RelativelyPrime(unsigned long long int m, int e)
{
    for (; ; )
    {
        if (!(m %= e)) return e == 1;
        if (!(e %= m)) return m == 1;
    }
}


void finde(unsigned long long int m)
{
    for (int i = 2; i < m; i++)
    {
        if (RelativelyPrime(m, i))
        {
            e = i;
            break;
        }
    }
}
unsigned long long int ModInverse(unsigned long long int m, int e)
{
    int k = 0;
    for (k = 0; k < m; k++)
    {
        if (((m*k + 1) % e) == 0)
        {
            a = (m*k + 1) / e;
            return a;

        }
    }
}

void generateKeys(void)
{
    FirstNumber();
    Sleep(1000);
    SecondNumber();
    cout << "P is : " << number1 << endl;
    cout << "Q is : " << number2 << endl;
    n = number1 * number2;
    cout << "N is : " << n << endl;
    m = (number1 - 1)*(number2 - 1);
    cout << "M is : " << m << endl;
    finde(m);
    cout << "E is : " << e << endl;
    a = ModInverse(m, e);
    cout << "A is : " << a << endl;
}

long long  int *Encr(unsigned long long int e, unsigned long long int n,string Plain)
{
    static long long TextEncrypted[Size];
    for (int i = 0; i < Size; i++)
    {
        TextEncrypted[i] = power(Plain[i], e, n);
    }
    return TextEncrypted;//pointer to the first number address in the array so I can access it
}

long long int * Decr(long long d, long long n, long long *TextEncrypted)
{
    static long long TextDecrypted[Size];

    for (int i = 0; i < Size; i++)
    {
        TextDecrypted[i] = power(TextEncrypted[i], a, n);
    }
    return TextDecrypted;
}

//main
int main()
{
    ifstream PlainFile;
    ofstream EncryptedFile;
    ofstream DecryptedFile;
    ofstream DecrytpedFile_FinalOutput;

    PlainFile.open("C:/Users/Ahmed Wael/Desktop/Discrete_Project/PlainFile.txt");
    EncryptedFile.open("C:/Users/Ahmed Wael/Desktop/Discrete_Project/EncryptedFile.txt");
    DecryptedFile.open("C:/Users/Ahmed Wael/Desktop/Discrete_Project/DecryptedFile.txt");
    DecrytpedFile_FinalOutput.open("C:/Users/Ahmed Wael/Desktop/Discrete_Project/DecrytpedFile_FinalOutput.txt");

    if (PlainFile.fail() || EncryptedFile.fail())
    {
        cerr << "Error";
        exit(1);
    }
    string message;
    cout<<"Message is : "<<endl;
    if (PlainFile.is_open())
    {
        while (getline(PlainFile, message))
        {
            cout << message;
        }
        cout << endl;
    }
    PlainFile.close();
    generateKeys();

    long long * TextEncrypted = Encr(e, n, message);
    for (int i = 0; i < (int) message.length(); i++)
        EncryptedFile << *(TextEncrypted + i) << " ";

    long long * plain = Decr(a, n, TextEncrypted);
    for (int i = 0; i < (int) message.length(); i++)
        DecryptedFile << *(plain + i) << " ";

    for (int i = 0; i < (int) message.length(); i++)
        DecrytpedFile_FinalOutput << (char) *(plain + i);

    EncryptedFile.close();
    DecryptedFile.close();
    DecrytpedFile_FinalOutput.close();
    return 0;
}
