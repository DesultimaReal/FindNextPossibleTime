#include <iostream>
#include <string>
#include <stdlib.h>
#include <set>
#include<stdio.h>
#include<string.h>
#include <sstream>
using namespace std;

/* Following function is used by the library qsort() function
  to sort an array of chars */
int compare (const void * a, const void * b);

/* The main function that recursively prints all repeated
   permutations of  the given string. It uses data[] to store all
   permutations one by one */
void allLexicographicRecur (char *str, char* data, int last, int index, set<string> & Permutations)
{
    int i, len = strlen(str);

    // One by one fix all characters at the given index and recur for
    // the/ subsequent indexes
    for ( i=0; i<len; i++ )
    {
        // Fix the ith character at index and if this is not the last
        // index then recursively call for higher indexes
        data[index] = str[i] ;

        // If this is the last index then print the string stored in
        // data[]
        if (index == last){
            Permutations.insert(data);
        }
        else // Recur for higher indexes
            allLexicographicRecur (str, data, last, index+1, Permutations);
    }
}

/* This function sorts input string, allocate memory for data (needed
   for allLexicographicRecur()) and calls allLexicographicRecur() for
   printing all  permutations */
void allLexicographic(char *str, set<string> &Permutations)
{
    int len = strlen (str) ;

    // Create a temp array that will be used by allLexicographicRecur()
    char *data = (char *) malloc (sizeof(char) * (len + 1)) ;
    data[len] = '\0';

    // Sort the input string so that we get all output strings in
    // lexicographically sorted order
    qsort(str, len, sizeof(char), compare);

    // Now print all permutaions
    allLexicographicRecur (str, data, len-1, 0, Permutations);

    // Free data to avoid memory leak
    free(data);
}

// Needed for library function qsort()
int compare (const void * a, const void * b)
{
    return ( *(char *)a - *(char *)b );
}

class Clock{
private:
    int MinsSmall;
    int MinsBig;
    int HoursSmall;
    int HoursBig;
    string OriginalTime;
public:
    Clock(string CurrentTime){
        MinsBig = CurrentTime[3]-'0';
        MinsSmall = CurrentTime[4]-'0';
        HoursBig = CurrentTime[0]-'0';
        HoursSmall = CurrentTime[1]-'0';

        CurrentTime.erase(CurrentTime.begin()+2);
        OriginalTime = CurrentTime;
    }
    string returnOriginalTime(){
        return OriginalTime;
    }
    void PrintCurrentTime(){
        cout << HoursBig << HoursSmall << ":" <<MinsBig << MinsSmall << endl;
    }
    void AddAMinute(){
        MinsSmall ++;
        if(MinsSmall == 10){
            MinsSmall = 0;
            MinsBig ++;
        }
        if(MinsBig == 6){
            MinsBig = 0;
            HoursSmall++;
        }
        if(HoursSmall == 10){
            HoursSmall = 0;
            HoursBig ++;
        }
        if(HoursBig == 2 && HoursSmall == 4){
            HoursBig = 0;
            HoursSmall =0;
        }
    }
    string CurrentAsString(){
        string s;
        stringstream out;
        out << HoursBig << HoursSmall << MinsBig << MinsSmall;
        return out.str();
    }
};

string NextPermutationTime(string input2){
    set<string> Permutations;
    Clock * Tracker = new Clock(input2);
    string s = Tracker->returnOriginalTime();
    //std::string s
    char *a=new char[s.size()+1];
    a[s.size()]=0;
    memcpy(a,s.c_str(),s.size());
    allLexicographic(a, Permutations);
    Tracker->AddAMinute();
    string CurrentTime = Tracker->CurrentAsString();
    while(CurrentTime != Tracker->returnOriginalTime()){
        string CurrentTime = Tracker->CurrentAsString();
        auto search = Permutations.find(CurrentTime);
        if(search != Permutations.end()) {
            CurrentTime.insert(CurrentTime.begin()+2, ':');
            return CurrentTime;
        }
        Tracker->AddAMinute();
    }
    return "Same Time next day is the only available permutation.";
}
bool isValid(string input){
    if(input.length()!= 5){
        return false;
    }
    if (isdigit(input[0]) && isdigit(input[1]) && isdigit(input[3]) && isdigit(input[4]) && input[2] == ':'){
        if(input[0]-'0' < 3 && input[1]-'0' < 4 && input[3]-'0' < 6 && input[4]-'0' <= 9)
            return true;
    }return false;
}
int main()
{
    cout << "Input Format-> 'Hour:Minute' in the 24 hour time frame.\nI.E. '00:00' to '23:59'.\n\n";
    cout << "This program will tell you the next available time\nusing any combination of the original times numbers.\nI.E. 11:00 -> 11:01, 23:59-> 22:22\n";
    cout << "INPUT: ";
    string input1 = "DEFAULT";
    while(input1 != "Quit"){
        string input1;
        cin >> input1;
        if(isValid(input1)){
            cout <<"Final Time: " <<NextPermutationTime(input1) << endl;
        }
        else{
            cout << "Invalid Input.\n";
        }
        cout << endl;
    }cout << "Quitting\n";
    return 0;
}
