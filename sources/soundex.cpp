//
// Created by navruz on 12/23/2020.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string Soundex(string input)
{
    char firstLetter;
    vector<char> intermediateResult; //String after each step

    //1. Store first letter and delete 'h' and 'w' letters except first letter
    firstLetter = input[0];

    //Since we need to delete 'h' and 'w' letters execpt first letter we start from index 1
    for (int i = 1; i < input.length(); i++)
        if (input[i] != 'h' && input[i] != 'w')
            intermediateResult.push_back(input[i]);

    //2. Substitute consonants to numbers:
    //b, f, p, v → 1
    //c, g, j, k, q, s, x, z → 2
    //d, t → 3
    //l → 4
    //m, n → 5
    //r → 6
    for (char & i : intermediateResult)
    {
        switch (toupper(i))
        {
            case 'B':
            case 'F':
            case 'P':
            case 'V':
                i = '1';
                break;

            case 'C':
            case 'G':
            case 'J':
            case 'K':
            case 'Q':
            case 'S':
            case 'X':
            case 'Z':
                i = '2';
                break;

            case 'D':
            case 'T':
                i = '3';
                break;

            case 'L':
                i = '4';
                break;

            case 'M':
            case 'N':
                i = '5';
                break;

            case 'R':
                i = '6';
                break;

            default:
                break;
        }
    }

    //3. Sequence of equal numbers replaced to the one number from this sequence
    //e.g. 4444 -> 4
    intermediateResult.erase(std::unique(intermediateResult.begin(), intermediateResult.end()), intermediateResult.end()); //https://stackoverflow.com/a/26706133/10304482

    //4. Delete a, e, i, o, u, y execept first letter
    //Since we need to delete letters execpt first letter we start from index 1

    vector<char> temp; //String without elements a, e, i, o, u, y
    for (char & i : intermediateResult)
    {
        char currentLetter = towlower(i);

        if (currentLetter != 'a' && currentLetter != 'e' && currentLetter != 'i' && currentLetter != 'o' && currentLetter != 'u' && currentLetter != 'y')
            temp.push_back(i);
    }

    //Write result to intermediateResult. But first of all clear intermediateResult since it keeps result from previous step
    intermediateResult.clear();

    for (char character : temp)
        intermediateResult.push_back(character);

    //5. Change first letter to the stored letter and make new letter capitalized
    intermediateResult.insert(intermediateResult.begin(), toupper(firstLetter));

    //6. Leave only first four characters if number of characters much then four
    //If less than four characters add 0's to make final string, 4 characters length
    if (intermediateResult.size() > 4)
    {
        //https://www.geeksforgeeks.org/vector-insert-function-in-c-stl/#:~:text=std%3A%3Avector%3A%3Ainsert,the%20number%20of%20elements%20inserted.
        auto firstElement = intermediateResult.begin();
        auto fourthElement = intermediateResult.begin() + 4;
        vector<char> tempVector(firstElement, fourthElement);

        intermediateResult = tempVector;
    }
    else if(intermediateResult.size()<4)
    {
        while (intermediateResult.size() != 4)
        {
            intermediateResult.push_back('0');
        }
    }

    string soundexString(intermediateResult.begin(), intermediateResult.end());

    return soundexString;
}

