/*
ID: borisd22
TASK: contact
LANG: C++
*/

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout

ifstream fin("contact.in");
ofstream fout("contact.out");

bool PatternComparator(pair<int, string>& a, pair<int, string>& b)
{
    if (a.first == b.first)
    {
        if (a.second.size() == b.second.size())
        {
            return a.second < b.second;
        }
        return a.second.size() < b.second.size();
    }
    return a.first > b.first;
}

string sequence;

int minPatternLen, maxPatternLen;
int n;

map<string, int> patternMap;

void Input()
{
    Read >> minPatternLen >> maxPatternLen >> n;

    string line;
    while (Read >> line)
    {
        sequence += line;
    }
}

void MapPatterns()
{
    for (int patternLen = minPatternLen; patternLen <= maxPatternLen; patternLen++)
    {
        for (int first = 0; first + patternLen <= sequence.size(); first++)
        {
            string currPattern = sequence.substr(first, patternLen);

            if (patternMap.find(currPattern) != patternMap.end())
            {
                patternMap[currPattern]++;
            }
            else
            {
                patternMap[currPattern] = 1;
            }
        }
    }
}

void Answer()
{
    vector< pair<int, string> > patterns;

    for (map<string, int>::iterator i = patternMap.begin(); i != patternMap.end(); i++)
    {
        patterns.push_back( {(*i).second, (*i).first} );
    }

    sort(patterns.begin(), patterns.end(), PatternComparator);

    int freqCounter = 0;
    for (int i = 0; freqCounter < n && i < patterns.size(); i++, freqCounter++)
    {
        Write << patterns[i].first << endl;
        int j = i;
        while (patterns[j].first == patterns[i].first)
        {
            Write << patterns[j].second;
            if (patterns[j + 1].first == patterns[i].first)
            {
                if ((j - i) % 6 == 5 && j > i)
                {
                    Write << endl;
                }
                else
                {
                    Write << " ";
                }
            }
            j++;
        }
        Write << endl;

        i = j - 1;
    }
}

int main()
{
    Input();
    MapPatterns();
    Answer();

    return 0;
}
