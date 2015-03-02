#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

vector<string> one_d;
vector< vector<string> > two_d;
vector<string> aug_grammar;
vector< vector<string> > minItemSet;
vector< vector<string> > ItemSet;
vector<string> terminals, non_terminals;
vector< vector<string> > First;
vector< vector<string> > Follow;
map<string,int> firstMake;
vector< vector<string> > followMake;
map<string, int> nullProd;
vector< vector<string> > prodFirst;
vector< vector<string> > grammarTable;
vector< vector<string> > firstCheck;
vector< vector<string> > SLRTable;
vector<string> conflictsTable;
string startSymbol;
string FirstCheck = "";
int sizeTerm;
int isLL1Grammar=1;
char input[] = "SLRCPPgrammar.txt";
string newStart;
string inputText = "yxxy$"; //i,i,i;f //(a+a) //i=i //i+i*i //aaba
string closureCheck;


void printVecTwoD(vector< vector<string> > v)
{
    int h=v.size();
    for(int i=0;i<h;i++)
    {
        int l=v[i].size();
        /*cout << " ";
        for(int r=0;r<l;r++)
        {
            cout << r << " ";
        }
        cout << endl;
        cout << i;*/
        for(int j=0;j<l;j++)
        {
            cout << v[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void printVecOneD(vector<string> v)
{
    int l=v.size();
    for(int j=0;j<l;j++)
    {
        cout << v[j] << " " ;
    }
    cout << endl;
}

int compareItem(vector<string> dumItemSet, vector< vector<string> > ItemSet1)
{
    int len = ItemSet1.size();
    int stat;
    //printVecOneD(dumItemSet);
    //cout << endl;
    for (int i = 0; i < len; ++i)
    {
        //printVecOneD(ItemSet[i]);
        int len1 = ItemSet1[i].size();
        int len2 = dumItemSet.size();
        stat=0;
        if(len1!=len2)
        {
            stat = -1;
        }
        else
        {
            int count=0;
            stat=0;
            for (int j = 0; j < len1; ++j)
            {
                if(dumItemSet[j].compare(ItemSet1[i][j])!=0)
                {
                    //cout << "Item " << i << endl;
                    stat = -2;
                }
                else
                {
                    count++;
                    //cout << "equal" << endl;
                }
            }
            if(stat!=-2) return i;
        }
    }
    return stat;
}

int findInVector(vector<string> v, string s)
{
    int i=v.size();
    for(int j=0;j<i;j++)
    {
        if(v[j]==s)
        {
            return j;
        }
    }
    return -1;
}

void readGrammar()
{
  fstream ingrammar;
  string buffer;
  ingrammar.open(input, ios::in);
  if (!ingrammar.is_open()) { // File Check
    cerr << "Can't open input file " << input << endl;
    return;
  }
  one_d.push_back(" ");
  grammarTable.push_back(one_d);
  one_d.clear();
  while(getline(ingrammar, buffer))
  {
    size_t prev = 0, pos;
        while ((pos = buffer.find_first_of(":| ", prev)) != string::npos)
        {
            if (pos > prev)
            {
                  one_d.push_back(buffer.substr(prev, pos-prev));
              }
            prev = pos+1;
        }
        if (prev < buffer.length())
          {
            one_d.push_back(buffer.substr(prev, string::npos));
          }
          non_terminals.push_back(one_d.front());
            two_d.push_back(one_d);
            one_d.clear();
          one_d.push_back(non_terminals.at(non_terminals.size()-1));
          First.push_back(one_d);
          Follow.push_back(one_d);
            minItemSet.push_back(one_d);
          followMake.push_back(one_d);
          grammarTable.push_back(one_d);
        one_d.clear();
    }
    startSymbol = non_terminals[0];
  ingrammar.close();  // Close file after use
}

int checkNonTerminals(string s)
{
    int l = non_terminals.size();
    for(int j=0;j<l;j++)
    {
        if(s.compare(non_terminals[j]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void checkForTerminals(string s)
{
    int l = s.length();
    string r;
    for(int i=0;i<l;i++)
    {
        r = s.at(i);
        if(checkNonTerminals(r) == 0 && findInVector(terminals, r) == -1)
        {
            terminals.push_back(r);
        }
    }

}

void makeTerminalsList()
{
    int h=two_d.size();
    for(int i=0;i<h;i++)
    {
        int l=two_d[i].size();
        for(int j=1;j<l;j++)
        {
            checkForTerminals(two_d[i][j]);
        }
    }
    int d=terminals.size();
    for(int i=0;i<d;i++)
    {
        if(terminals[i]!="^")
        {
            grammarTable[0].push_back(terminals[i]);
        }
    }
    grammarTable[0].push_back("$");
}

int isTerminal(string s)
{
    int i=terminals.size();
    for(int j=0;j<i;j++)
    {
        if(terminals[j].compare(s)==0)
        {
            return 1;
        }
    }
    return 0;
}

vector<string> findFirstString(string s, int l, int start)
{
    int m=two_d[l].size();
    //cout << "Size of " << two_d[l][0] << " " << m << " " << start << endl;
    vector<string> dummyVec;
    vector<string> dummyVec1;
    if (FirstCheck.find(s) == string::npos) {
        //cout << "Could not find " << s << endl;
        FirstCheck+=s;
        //cout << "First has not been found for " << s << endl;
    }
    else
    {
        //cout << "First has been found for " << s << endl;
        int r = findInVector(non_terminals, s);
        //cout << "First of " << First[r][0] << ": ";
        for(int z = 1;z < First[r].size();z++)
        {
            cout << First[r][z] << " ";
            dummyVec.push_back(First[r][z]);
        }
        cout << endl;
        return dummyVec;
    }
    //cout << "FirstCheck: " << FirstCheck << endl;
    for(int j=start;j<m;j++)
    {
        string h=two_d.at(l).at(j);
        int k = h.length();
        //cout << "Production: " << j << " " << h << " has length " << k << endl;
        for(int i=0;i<k;i++)
        {
            string t = h.substr(i,i+1);
            //cout << t << endl;
            if(isTerminal(t) == 1)
            {
                //cout << t << " is a terminal" << endl;
                //cout << t << " is the First of " << s << endl;
                dummyVec.push_back(t);
                break ;
            }
            /*for(int j=start;j<m;j++)
            {
                string h=two_d.at(l).at(j);
                int k = h.length();
                //cout << "Production: " << j << " " << h << " has length " << k << endl;
                for(int i=0;i<k;i++)
                {
                    string t = h.substr(i,i+1);
                    if(isTerminal(t) == 1)
                    {
                        dummyVec.push_back(t);
                        break ;
                    }*/
                    if(isTerminal(t) == 0)
                    {
                        int r = findInVector(non_terminals, t);
                        if (FirstCheck.find(t) == string::npos) {
                            //cout << t << " is " << r << " in non-terminals" << endl;
                            //cout << "Starting with " << t << " from Production: " << 1 << endl;
                           //cout << "First of " << s << " contains " << " First of " << t << endl;
                            //cout << "Finding First of " << t << endl;
                            dummyVec1 = findFirstString(t, r, 1);
                            for (int z = 0; z < dummyVec1.size(); ++z)
                            {
                                dummyVec.push_back(dummyVec1[z]);
                            }
                        }
                        else {
                            //cout << "Starting1 with " << t << " from Production: " << j+1 << endl;
                            //cout << "First of " << s << " contains " << " First of " << t << endl;
                            //cout << "Finding First of " << t << endl;
                            dummyVec1 = findFirstString(t, r, j+1);
                            for (int z = 0; z < dummyVec1.size(); ++z)
                            {
                                dummyVec.push_back(dummyVec1[z]);
                            }
                        }
                    }
                    if(findInVector(dummyVec, "^") == -1)
                    {
                        break;
                    }
              /*  }
            }*/
        }
    }
    sort( dummyVec.begin(), dummyVec.end() );
    dummyVec.erase( unique( dummyVec.begin(), dummyVec.end() ), dummyVec.end() );
    firstMake[s] = 1;
    for (int z = 0; z < dummyVec.size(); ++z)
    {
        First[l].push_back(dummyVec[z]);
        if(dummyVec[z] == "^")
        {
            nullProd[s] = 1;
        }
    }
    int FirstL = First[l].size();
    /*cout << "First of " << First[l][0] << ": ";
    for(int z = 1;z < FirstL;z++)
    {
        cout << First[l][z] << " " ;
    }
    cout << endl;*/
    return dummyVec;
}

void findFollowString()
{
    int noProd,l,o,r,noOption,len;
    noProd = two_d.size();
    for(int i=0;i<noProd;i++)
    {
        noOption = two_d[i].size();
        for(int j=1;j<noOption;j++)
        {
            string s = two_d[i][j];
            len = s.length();
            for(int k=0;k<len-1;k++)
            {
                char dummy = s.at(k);
                char dummy1 = s.at(k+1);
                if(!(isTerminal(string(1,dummy))))
                {
                    int l=findInVector(non_terminals, string(1,dummy));
                    int o=findInVector(non_terminals, string(1,dummy1));
                    int r=First[l-1].size();
                    if(isTerminal(string(1,dummy1)))
                    {
                        Follow[l].push_back(string(1,dummy1));
                    }
                    else
                    {
                        if(nullProd[First[o][0]] == 1)
                        {
                            followMake[l].push_back(two_d[i][0]);
                        }
                        int y = First[o].size();
                        for (int z = 1; z < y; ++z)
                        {
                            if(First[o][z] != "^")
                            {
                                Follow[l].push_back(First[o][z]);
                            }
                        }
                    }
                }
            }
            char dummy = s.at(len-1);
            l=findInVector(non_terminals, string(1,dummy));
            if(dummy!='^' && l!=-1)
            {
                followMake[l].push_back(two_d[i][0]);
            }
        }
    }
}

vector<string> findFirst(string s)
{
    int k=s.length();
    vector<string> dum;
    for(int i=0;i<k;i++)
    {
        string d = string(1,s.at(i));
        if(isTerminal(d))
        {
            dum.push_back(d);
            break;
        }
        if(nullProd[d] == 1)
        {
            int y=findInVector(non_terminals, d);
            for (int z = 1; z < y; ++z)
            {
                dum.push_back(First[y][z]);
            }
        }
        if(nullProd[d] != 1)
        {
            int y=findInVector(non_terminals, d);
            int d=First[y].size();
            for (int z = 1; z < d; ++z)
            {
                dum.push_back(First[y][z]);
            }
            break;
        }
    }
    return dum;
}

void makeFirst()
{
    int k=First.size();
    string first;
    vector<string> firstPush;
    for(int i=0;i<k;i++)
    {
        first = First[i][0];
        //cout << "Finding first for " << first << endl;
        if(firstMake[first] != 1)
        {
            //cout << "Finding first " << first << endl;
            firstPush = findFirstString(first, i, 1);
            //cout << "Found first for " << first << endl;
        }
    }
    for(int i=0;i<k;i++)
    {
        sort( First[i].begin()+1, First[i].end() );
        First[i].erase( unique( First[i].begin()+1, First[i].end() ), First[i].end() );
    }
}

void makeFollow()
{
    int k=Follow.size();
    string follow;
    vector<string> followPush;
    Follow[0].push_back("$");
    findFollowString();
    for(int i=0;i<k;i++)
    {
        int e = followMake[i].size();
        for(int j=1;j<e;j++)
        {
            int l=findInVector(non_terminals, followMake[i][j]);
            int y = Follow[l].size();
            for (int z = 1; z < y; ++z)
            {
                 Follow[i].push_back(Follow[l][z]);
            }
        }
        sort( Follow[i].begin()+1, Follow[i].end() );
        Follow[i].erase( unique( Follow[i].begin()+1, Follow[i].end() ), Follow[i].end() );
    }
}

void makeFirstProd()
{
    int r=two_d.size();
    vector<string> dum;
    vector<string> dum1;
    for(int i=0;i<r;i++)
    {
        int s=two_d[i].size();
        for(int j=1;j<s;j++)
        {
            string p = two_d[i][j];
            dum.push_back(p);
            dum1 = findFirst(p);
            int u=dum1.size();
            for (int z = 0; z < u; ++z)
            {
                if(dum1[z]=="^")
                {
                        nullProd[p]=1;
                }
                dum.push_back(dum1[z]);
            }
            prodFirst.push_back(dum);
            dum.clear();
        }
    }
}

void makeSLRParsingTable()
{
    int termLen = terminals.size();
    int nonTermLen = non_terminals.size();
    vector<string> dummy;
    dummy.push_back(" ");
    dummy.push_back("$");
    for (int i = 0; i < termLen; ++i)
    {
        dummy.push_back(terminals[i]);
    }
    for (int i = 0; i < nonTermLen; ++i)
    {
        dummy.push_back(non_terminals[i]);
    }
    SLRTable.push_back(dummy);
    dummy.clear();
}

void makeMinItemSet()
{
    int len = non_terminals.size();
    string item;
    for (int i = 0; i < len; ++i)
    {
        int len1 = two_d[i].size();
        for (int j = 1; j < len1; ++j)
        {
            item=two_d[i][0]+":."+two_d[i][j];
            minItemSet[i].push_back(item);
        }
    }
}

vector<string> findItem(vector<string> input, string S)
{
    cout << "Starting to find for Item " << closureCheck << endl;
    int len=input.size();
    vector<string> ItemSet2;
    printVecOneD(input);
    for (int i = 0; i < len; ++i)
    {
        string inputString = input[i];
        int strLen = inputString.length();
        int first = input[i].find_first_of(".",0);
        int stat=0;
        string symbol;
        if(first+1!=strLen)
        {
            symbol = string(1,inputString[first+1]);
            stat=1;
        }
        if(symbol.compare(S)==0 && first!=-1 && stat==1)
        {
            cout << "Closure on " << inputString << endl;
            swap(inputString[first],inputString[first+1]);
            string outputString = inputString;
            ItemSet2.push_back(outputString);
        }
        printVecOneD(ItemSet2);
        for (int j = 0; j < ItemSet2.size(); ++j)
        {
            string closureToFind = ItemSet2[j];
            first = closureToFind.find_first_of(".",0);
            string closureFind = string(1,closureToFind[first+1]);
            int closure = findInVector(non_terminals, closureFind);
            if (closureCheck.find(closureFind) == string::npos) {
                if(closure!=-1)
                {
                    closureCheck+=closureFind;
                    cout << "Has the closure been found for " << closureToFind << " No!!!" << endl;
                    cout << "Taking closure for " << ItemSet2[j] << endl;
                    int closureLen = minItemSet[closure].size();
                    for (int j = 1; j < closureLen; ++j)
                    {
                        //cout << "Pushing " << minItemSet[closure][j] << endl;
                        ItemSet2.push_back(minItemSet[closure][j]);
                    }
                    printVecOneD(ItemSet2);
                }
            }
            else
            {
                cout << "Has the closure been found for " << closureToFind << " Yes!!!" << endl;
            }
            cout << "Closure found for " << closureCheck << endl;
        }
    }
    return ItemSet2;
}

void makeItemSet()
{
    string begin = startSymbol+"'.:"+startSymbol;
    vector<string> input,itemFind;
    string conflict;
    input.push_back(begin);
    cout << "Making Item Set 0" << endl;
    closureCheck="";
    vector<string> dumItemSet = findItem(input, ":");
    vector<string> dummy;
    ItemSet.push_back(dumItemSet);
    dumItemSet.clear();
    int item = 0,term,find;
    int lengthTable = SLRTable[0].size();
    for (int i = 0; i < ItemSet.size(); ++i)
    {
        //cout << "Present Item Set has " << ItemSet.size() << " items" << endl;
        //dummy.push_back(string(1,i+'0'));
        dummy.push_back(to_string(i));
        for (int z = 1; z < lengthTable; ++z)
        {
            dummy.push_back("");
        }
        SLRTable.push_back(dummy);
        dummy.clear();
        int len = ItemSet[i].size();
        int visitLen[len+1];
        for (int l = 0; l < len; ++l)
        {
            visitLen[l]=0;
        }
        for (int j = 0; j < len; ++j)
        {
            if(visitLen[j]==0)
            {
                string closureToFind = ItemSet[i][j];
                int first = closureToFind.find_first_of(".",0);
                if(first!=closureToFind.length()-1)
                {
                    visitLen[j]=1;
                    //cout << "Calculating Item " << item+1 << endl;
                    string closureFind = string(1,closureToFind[first+1]);
                    itemFind.push_back(closureToFind);
                    //cout << "Visited ItemString1 " << j << " in Item " << i << endl;
                    for (int k = j+1; k < len; ++k)
                    {
                        closureToFind = ItemSet[i][k];
                        first = closureToFind.find_first_of(".",0);
                        string closureFind1 = string(1,closureToFind[first+1]);
                        if(closureFind.compare(closureFind1)==0)
                        {
                            itemFind.push_back(closureToFind);
                            //cout << "Visited ItemString2 " << k << " in Item " << i << endl;
                            visitLen[k]=1;
                        }
                    }
                    /*cout << "Taking closure of ";
                    printVecOneD(itemFind);
                    cout << " wrt " << closureFind << endl;*/
                    //cout << "Making Item " << item+1 << " from Item " << i << " using " << closureFind << endl;
                    cout << endl;
                    closureCheck="";
                    dumItemSet = findItem(itemFind, closureFind);
                    int compare = compareItem(dumItemSet, ItemSet);
                    if(compare==-1 || compare==-2)
                    {
                        cout << "Item " << i << " -> " << closureFind << " Item " << item+1 << endl;
                        printVecOneD(itemFind);
                        cout << "Item " << item+1 << ": ";
                        printVecOneD(dumItemSet);
                        ItemSet.push_back(dumItemSet);
                        item++;
                        term = findInVector(terminals,closureFind);
                        if(term==-1)
                        {
                            term = findInVector(non_terminals,closureFind);
                            cout << "Contains a GOTO Step" << endl;
                            //printVecOneD(SLRTable[0]);
                            //cout << closureFind << endl;
                            find = findInVector(SLRTable[0],closureFind);
                            //cout << find << i << closureFind << item << endl;
                            SLRTable[i+1][find] = to_string(item);
                        }
                        else
                        {
                            cout << "Contains a Shift Step" << endl;
                            find = findInVector(SLRTable[0],closureFind);
                            if(SLRTable[i+1][find]=="")
                            {
                                SLRTable[i+1][find] = "S"+to_string(item);
                            }
                            else
                            {
                                conflict = "Conflict in Table Entry at State "+to_string(i)+" Action "+closureFind+" over "+SLRTable[i+1][find]+" & "+"S"+to_string(item);
                                conflictsTable.push_back(conflict);
                                SLRTable[i+1][find] = "C";
                            }
                        }
                    }
                    else
                    {
                        cout << "Item " << i << " -> " << closureFind << " Item " << compare << endl;
                        term = findInVector(terminals,closureFind);
                        if(term==-1)
                        {
                            term = findInVector(non_terminals,closureFind);
                            cout << "Contains a GOTO Step" << endl;
                            find = findInVector(SLRTable[0],closureFind);
                            SLRTable[i+1][find] = to_string(compare);
                        }
                        else
                        {
                            cout << "Contains a Shift Step" << endl;
                            find = findInVector(SLRTable[0],closureFind);
                            if(SLRTable[i+1][find]=="")
                            {
                                SLRTable[i+1][find] = "S"+to_string(compare);
                            }
                            else
                            {
                                conflict = "Conflict in Table Entry at State "+to_string(i)+" Action "+closureFind+" over "+SLRTable[i+1][find]+" & "+"S"+to_string(compare);
                                conflictsTable.push_back(conflict);
                                SLRTable[i+1][find] = "C";
                            }
                        }
                    }
                    dumItemSet.clear();
                    itemFind.clear();
                    cout << "Present State of Items" << endl;
                    printVecTwoD(ItemSet);
                    cout << endl;
                }
                else
                {
                    string reduce = closureToFind.substr(0,closureToFind.length()-1);
                    cout << "Item " << i << endl;
                    cout << "Contains a Reduce Step  " << reduce << endl;
                    int prodNo = findInVector(aug_grammar,reduce);
                    if(prodNo==0)
                    {
                        cout << "Accept State" << endl << endl;
                        find = findInVector(SLRTable[0],"$");
                        SLRTable[i+1][find] = "A";
                    }
                    else
                    {
                        cout << "Reduce to Prod " << prodNo << endl;
                        string followFind = string(1,reduce[0]);
                        int find1;
                        find = findInVector(non_terminals,followFind);
                        int followLen = Follow[find].size();
                        for (int z = 1; z < followLen; ++z)
                        {
                            find1 = findInVector(SLRTable[0],Follow[find][z]);
                            if(SLRTable[i+1][find1]=="")
                            {
                                SLRTable[i+1][find1] = "R"+to_string(prodNo);
                            }
                            else
                            {
                                string problem = SLRTable[i+1][find1];
                                conflict = "Conflict in Table Entry at State "+to_string(i)+" Action "+Follow[find][z]+" over "+SLRTable[i+1][find]+" & "+"R"+to_string(prodNo);
                                conflictsTable.push_back(conflict);
                                SLRTable[i+1][find] = "C";
                            }
                        }
                    }
                    cout << endl;
                }
            }
        }
        /*cout << "Visit Array begin" << endl;
        for (int l = 0; l < len; ++l)
        {
            cout << visitLen[l] << " ";
        }
        cout << "Visit Array end" << endl;
        cout << endl;*/
        /*cout << "ItemSet" << endl;
        printVecTwoD(ItemSet);*/
        closureCheck="";
    }
}

void runString(string s)
{
    cout << "SLR Parsing on " << s << endl;
    int len=s.length();
    stack<string> grammar;
    string grammars="0";
    grammar.push("0");
    int slen=0,step=1,pstate=0;
    cout << "Step\t\tStack\t\t\tString\t\tAction" << endl;
    string action = "";
    int prodno,intLen;
    const char* c;
    while(1)
    {
        cout << step << "\t\t\t";
        //cout << "Present State " << pstate << endl;
        step++;
        string top=string(1,s[slen]);
        int find=findInVector(SLRTable[0],top);
        if(find==-1)
        {
            cout << "Symbol " << top << " doesn't belong to this grammar" << endl;
            return ;
        }
        action = SLRTable[pstate+1][find];
        //cout << action << endl;
        if(action.compare("")==0)
        {
            cout << "Error has occured. Please check your string." << endl;
            return ;
        }
        if(action.compare("A")==0)
        {
            cout << grammars << "\t\t" << s.substr(slen,len) << "\t\t" << "Accept" << endl;
            return ;
        }
        if(action[0]=='S')
        {
            cout << grammars << "\t\t\t\t" << s.substr(slen,len) << "\t\t" << "Shift " << action.substr(1,action.length()) << endl;
            //grammars.push_back(s[slen]);
            //grammars.push_back(action.substr(1,action.length()));
            grammars+=s[slen]+action.substr(1,action.length());
            grammar.push(string(1,s[slen]));
            grammar.push(action.substr(1,action.length()));
            c = action.substr(1,action.length()).c_str();
            pstate=atoi(c);
            slen++;
        }
        if(action[0]=='R')
        {
            cout << grammars << "\t\t\t\t" << s.substr(slen,len) << "\t\t" << "Reduce " << action.substr(1,action.length()) << endl;
            c = string(1,action[1]).c_str();
            prodno=atoi(c);
            string production = aug_grammar[prodno];
            int colon = production.find_first_of(":",0);
            int prodlen = production.substr(colon+1,len).length();
            prodlen = 2*prodlen;
            while(prodlen>0)
            {
                if(prodlen%2!=0)
                {
                    //cout << "Removing " << grammar.top() << endl;
                    grammars.pop_back();
                    c = grammar.top().c_str();
                    pstate = atoi(c);
                }
                else
                {
                    string num = to_string(pstate);
                    intLen = num.length();
                    //cout << "Removing1 " << pstate << " " << intLen << endl;
                    while(intLen--)
                    {
                        grammars.pop_back();
                    }
                }
                grammar.pop();
                //cout << grammars << endl;
                prodlen--;
            }
            c = grammar.top().c_str();
            pstate = atoi(c);
            //cout << pstate << endl;
            grammar.push(string(1,production[0]));
            grammars.push_back(production[0]);
            find = findInVector(SLRTable[0],string(1,production[0]));
            if(find==-1)
            {
                cout << "Symbol " << production[0] << " doesn't belong to this grammar" << endl;
                return ;
            }
            c = SLRTable[pstate+1][find].c_str();
            int gotoNo = atoi(c);
            grammar.push(to_string(gotoNo));
            grammars+=to_string(gotoNo);
            pstate=gotoNo;
        }
    }
}

vector<string> intersection(vector<string> &v1, vector<string> &v2)
{
    vector<string> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    return v3;
}

void makeAugmentedGrammar()
{
    int l = two_d.size();
    newStart = startSymbol+"':"+startSymbol;
    aug_grammar.push_back(newStart);
    for(int i=0;i<l;i++)
    {
        int k = two_d[i].size();
        for(int j=1;j<k;j++)
        {
            newStart=two_d[i][0]+":"+two_d[i][j];
            aug_grammar.push_back(newStart);
        }
    }
}

void module1()
{
    cout << "Reading Grammar" << endl;

    readGrammar();
    cout << "Grammar" << endl;
    printVecTwoD(two_d);
    cout << "Non-Terminals List" << endl;
    printVecOneD(non_terminals);

    cout << endl;
    cout << "Making Terminals List" << endl;
    makeTerminalsList();
    cout << "Terminals List" << endl;
    printVecOneD(terminals);
    makeSLRParsingTable();

    cout << endl;
    cout << "Making First List" << endl;
    makeFirst();
    cout << "First" << endl;
    printVecTwoD(First);

    cout << endl;
    cout << "Making Follow List" << endl;
    makeFollow();
    cout << "Follow" << endl;
    printVecTwoD(Follow);

    makeAugmentedGrammar();
    printVecOneD(aug_grammar);

    makeMinItemSet();
    cout << "Min Item Set" << endl;
    printVecTwoD(minItemSet);

    makeItemSet();
    cout << endl;
    cout << "Item Set" << endl;
    int ItemSetSize = ItemSet.size();
    for (int i = 0; i < ItemSetSize; ++i)
    {
        cout << "Item " << i << " -> ";
        printVecOneD(ItemSet[i]);
    }

    cout << endl;
    printVecTwoD(SLRTable);

    int noConflicts = conflictsTable.size();
    int conflictsStat=0;
    if (noConflicts>0)
    {
        conflictsStat=1;
        cout << "Conflicts are there in table " << endl;
        for (int i = 0; i < noConflicts; ++i)
        {
            cout << conflictsTable[i] << endl;
        }
    }

    if(conflictsStat!=1)
    {
        runString(inputText);
    }
}

void module2()
{
    readGrammar();
    makeTerminalsList();
    makeFirst();
    makeFollow();
    makeAugmentedGrammar();
    makeMinItemSet();

    vector<string> inputItem;
    //inputItem.push_back("E:E+.T");
    //inputItem.push_back("T:.T*F");
    inputItem.push_back("R':.R");
    inputItem.push_back("R:.R+R");
    inputItem.push_back("R:.RR");
    inputItem.push_back("R:.R*");
    closureCheck = "";
    vector<string> items = findItem(inputItem, "R");
    cout << "Items: " << endl;
    for (int i = 0; i < items.size(); ++i)
    {
        cout << items[i] << endl;
    }
}

void module3()
{
    vector< vector<string> > dummyItemSet;
    string compareItemSetString[] = {"R:L."};

    string ItemSetString1[] = {"S':.S","S:.L=R","S:.R","L:.*R","L:.i","R:.L"};
    string ItemSetString2[] = {"S':S."};
    string ItemSetString3[] = {"S:L.=R","R:L."};
    string ItemSetString4[] = {"S:R."};
    string ItemSetString5[] = {"L:*.R","R:.L","L:.*R","L:.i"};
    string ItemSetString6[] = {"L:i."};
    string ItemSetString7[] = {"S:L=.R","R:.L","L:.*R","L:.i"};
    string ItemSetString8[] = {"L:*R."};
    string ItemSetString9[] = {"R:L."};
    string ItemSetString10[] = {"S:L=R."};
    vector<string> dummySet;
    vector<string> dummySet1(ItemSetString1, ItemSetString1 + 6);
    dummyItemSet.push_back(dummySet1);
    vector<string> dummySet2(ItemSetString2, ItemSetString2 + 1);
    dummyItemSet.push_back(dummySet2);
    vector<string> dummySet3(ItemSetString3, ItemSetString3 + 2);
    dummyItemSet.push_back(dummySet3);
    vector<string> dummySet4(ItemSetString4, ItemSetString4 + 1);
    dummyItemSet.push_back(dummySet4);
    vector<string> dummySet5(ItemSetString5, ItemSetString5 + 4);
    dummyItemSet.push_back(dummySet5);
    vector<string> dummySet6(ItemSetString6, ItemSetString6 + 1);
    dummyItemSet.push_back(dummySet6);
    vector<string> dummySet7(ItemSetString7, ItemSetString7 + 4);
    dummyItemSet.push_back(dummySet7);
    vector<string> dummySet8(ItemSetString8, ItemSetString8 + 1);
    dummyItemSet.push_back(dummySet8);
    vector<string> dummySet9(ItemSetString9, ItemSetString9 + 1);
    dummyItemSet.push_back(dummySet9);
    vector<string> dummySet10(ItemSetString10, ItemSetString10 + 1);
    dummyItemSet.push_back(dummySet10);
    vector<string> compareItemSet(compareItemSetString, compareItemSetString + 1);
    printVecOneD(compareItemSet);
    int compareTest = compareItem(compareItemSet, dummyItemSet);
    cout << compareTest << endl;
}

void module4()
{
    vector<string> itemFind;
    vector< vector<string> > ItemSetTest;
    //string ItemTestSet[] = {"S:L=.R","R:.L","L:.*R","L:.i"};
    string ItemTestSet[] = {"E:E+.T","T:.T*F","T:.F","F:.(E)","F:.i"};
    vector<string> dummySet(ItemTestSet, ItemTestSet + 5);
    ItemSetTest.push_back(dummySet);
    for (int i = 0; i < ItemSetTest.size(); ++i)
    {
        int len = ItemSetTest[i].size();
        int visitLen[len+1];
        for (int l = 0; l < len; ++l)
        {
            visitLen[l]=0;
        }
        string closureFind;
        for (int j = 0; j < len; ++j)
        {
            if(visitLen[j]==0)
            {
                string closureToFind = ItemSetTest[i][j];
                int first = closureToFind.find_first_of(".",0);
                if(first!=closureToFind.length()-1)
                {
                    visitLen[j]=1;
                    closureFind = string(1,closureToFind[first+1]);
                    itemFind.push_back(closureToFind);
                    for (int k = j+1; k < len; ++k)
                    {
                        closureToFind = ItemSetTest[i][k];
                        first = closureToFind.find_first_of(".",0);
                        string closureFind1 = string(1,closureToFind[first+1]);
                        if(closureFind.compare(closureFind1)==0)
                        {
                            itemFind.push_back(closureToFind);
                            visitLen[k]=1;
                        }
                    }
                }
                printVecOneD(itemFind);
                cout << closureFind << endl;
                itemFind.clear();
            }
        }
    }
}

int main()
{
    /*cout << "Module 2" << endl;
    cout << "Min Item Set1" << endl;
    printVecTwoD(minItemSet);
    module2();
    cout << "Min Item Set2" << endl;
    printVecTwoD(minItemSet);
    module2();
    cout << "Min Item Set3" << endl;
    printVecTwoD(minItemSet);*/
    cout << "Module 1" << endl;
    module1();
    freopen("output.txt","w",stdout);
    /*readGrammar();
    makeAugmentedGrammar();
    printVecOneD(aug_grammar);*/
    return 0;
}