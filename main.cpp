#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>

using std::string;
using std::fstream;
using std::cout;
using std::cin;
using std::endl;

static bool GAMEOVER = false;
static string GAMEOVERINFO = "";

//struct Words {
//    string word;
//    string meaning;
//};

static string * words;
static int quantity;


void Speak(string str);
void Shuffle();
void Swap(int a, int b);
void Print(string fileName);


void Speak(string str)
{
    if (str == "")
        return;

    char ch[99];

    ch[0] = 's';
    ch[1] = 'a';
    ch[2] = 'y';
    ch[3] = ' ';

    for (unsigned int i = 0; i <= str.length(); i++)
        ch[i + 4] = i!=str.length()?str[i]:'\0';

    system(ch);
}

void Shuffle()
{
    for (int i = 0; i < quantity; i++)
    {
        srand((unsigned)time(0)+rand());
        int a, b;
        a = rand() % quantity;
        b = rand() % quantity;
        Swap(a, b);
    }
}

void Swap(int a, int b)
{
    if (a < 0 || a >= quantity || b < 0 || b >= quantity)
        return;
    else
    {
        string tmp;
        tmp = words[a];
        words[a] = words[b];
        words[b] = tmp;
    }
}

void Print(string fileName)
{
    cout << "––––" << fileName << "––––\n"
         << "Quantity: " << quantity << endl;

    if(quantity > 0)
    {
        cout << "List of words:" << endl;
        for (int i = 0; i < quantity; i++)
            cout << (i+1<10?cout<<"0",i+1:i+1) << " | " << words[i] << endl;
    }
    cout << "––––End of file––––" << endl;

}

void StartPractice()
{
    system("clear");
    while (true)
    {
        for (int i = 0; i < quantity; i++)
        {
            cout << endl;
            cout << "[ " << i + 1 << " / " << quantity << " ]: ";
            cout << endl;
            cout << "  ";

            for (unsigned long j = 0; j < words[i].length(); j++)
            {
                if (j == 0 || j == words[i].length() - 1)
                    cout << words[i][j];
                else if (words[i][j] == ' ')
                    cout << " ";
                else
                    cout << "_";
            }
            cout << endl;
            cout << "> " << std::flush;

            Speak(words[i]);

            string input;

            getline(cin, input);

            system("clear");

            if (input == "q")
                return;

            if (input == words[i])
                cout << "✅  Correct!" << endl;
            else
            {
                cout << "Incorrect." << endl;
                cout << "✅  Should be: " << words[i] << endl;
                cout << "🚫  Yours is : " << input << endl << endl;
                i--; continue;
            }
        }
        system("clear");
        cout << "You completed the list! \n Want to start over? y/n \n> ";
        string tmp;
        cin >> tmp;
        if (tmp == "n" || tmp == "N")
            break;
    }
}

int main()
{
    cout << endl;

    fstream file;

    cout << "File name:\n> ";

    string fileName;
    cin >> fileName; cout << endl;

    // Make sure the file is open, or, create a new one and open it.
    file.open(fileName, fstream::in | fstream::out);
    if (file.is_open() == false)
    {
        cout << "File not found. Creating a new one.\n";
        file.close();
        file.open(fileName, fstream::out);
        file << "0";
        file.close();
        file.open(fileName, fstream::in | fstream::out);
    }


    // Read the first line and set "quantity" ( text->int conversion)
    quantity = 0;
    {
        string strtmp;
        int inttmp = 0;
        getline(file, strtmp);
        for (unsigned int i = 0; i < strtmp.length(); i++)
            switch (strtmp[i])
            {
            case '0': inttmp += 0 * pow(10, strtmp.length() - i - 1); break;
            case '1': inttmp += 1 * pow(10, strtmp.length() - i - 1); break;
            case '2': inttmp += 2 * pow(10, strtmp.length() - i - 1); break;
            case '3': inttmp += 3 * pow(10, strtmp.length() - i - 1); break;
            case '4': inttmp += 4 * pow(10, strtmp.length() - i - 1); break;
            case '5': inttmp += 5 * pow(10, strtmp.length() - i - 1); break;
            case '6': inttmp += 6 * pow(10, strtmp.length() - i - 1); break;
            case '7': inttmp += 7 * pow(10, strtmp.length() - i - 1); break;
            case '8': inttmp += 8 * pow(10, strtmp.length() - i - 1); break;
            case '9': inttmp += 9 * pow(10, strtmp.length() - i - 1); break;
            default: GAMEOVER = true; GAMEOVERINFO = "Unexcepted characters when processing quantity number.";
            }
        quantity = inttmp;
    }

    words = new string [quantity];

    for (int i = 0; i < quantity; i++)
        getline(file, words[i]);

    file.close();

    Print(fileName);

    cin.get();
    StartPractice();

    delete [] words;

    return 0;
}
