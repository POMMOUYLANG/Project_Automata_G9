#include <algorithm>
#include<iostream>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h>
//#include <queue>
#include <bits/stdc++.h>
using namespace std;

    int num,i,j,k,State;
    string name,state,finalstate,startstate,symbol,Symbol;
    char m;
    int numSymbol,numState;
    fstream Myfile;
#define max 100
#define STATES 99
#define SYMBOLS 20

int N_symbols;
int N_DFA_states;
char* DFA_finals;
int DFAtab[STATES][SYMBOLS];
char StateName[STATES][STATES+1];
int N_optDFA_states;
int OptDFA[STATES][SYMBOLS];
char NEW_finals[STATES+1];
//test STRING
#define STATES 99
#define SYMBOLS 20
char states[20];
//*******************
void FullOption();
void CreateNewFAfile();
void DFA();
void NFA();
void convertNFAToDFA();
void inputDFA1();
void MinimizeDFA();
int  TestFAstring();
void DeleteCurrentFA();
void updateFA();
void exit();
int main();

struct file{
    string name;
    string ID;
};
file f;
file get_data(ifstream &read)
{
    file obj;
    read>>obj.ID;
    read.get();
    getline(read,obj.name);
};
struct Element{
  char symbol;
  string state, final_state;
  Element *next;
};
struct Queue{
  int n;
  Element *myrear, *myfront;
};
Queue *createEmptyqueue(){
  Queue *q;
  q = new Queue;

  q->myrear = NULL;
  q->myfront = NULL;
  q->n = 0;
  return q;
}
void enqueueSymbol(Queue *q, char mySymbol){

    Element *e;
    e = new Element;
    e->symbol =mySymbol;
    e->next = NULL;

  if(q->n == 0){//when q is empty
    q->myfront = e;
    q->myrear = e;
  }
  else{//when q is not empty
     q->myrear->next = e;
     q->myrear = e;
  }
  q->n = q->n + 1;
}
void enqueueState(Queue *q, string myState){

     Element *e;
  e = new Element;
  e->state = myState;
  e->next = NULL;

  if(q->n == 0){//when q is empty
    q->myfront = e;
    q->myrear = e;

  }
  else{//when q is not empty
     q->myrear->next = e;
     q->myrear = e;
  }
  q->n = q->n + 1;
}
void enqueueFinalState(Queue *q, string myFinalState){

     Element *e;
  e = new Element;
  e->final_state = myFinalState;
  e->next = NULL;

  if(q->n == 0){//when q is empty
    q->myfront = e;
    q->myrear = e;

  }
  else{//when q is not empty
     q->myrear->next = e;
     q->myrear = e;
  }
  q->n = q->n + 1;
}
void enqueueTransition(Queue *q, string myState, char mySymbol){

    Element *e;
    e = new Element;
    e->state = myState;
    e->symbol = mySymbol;
    e->next = NULL;
    if (q->n == 0){
        q->myrear = e;
        q->myfront = e;
    }
    else{
        q->myrear->next = e;
        q->myrear = e;
    }
    q->n = q->n + 1;
}
void displayMySymbol(Queue *q){
  Element *tmp;
   tmp = q->myfront;
   while (tmp != NULL){
     cout<<tmp->symbol;
     tmp = tmp->next;
   }
}
void displayMyTransition(Queue *q){
  Element *tmp;
   tmp = q->myfront;

   while (tmp != NULL){
     cout<<tmp->symbol<<" "<<tmp->state;
     tmp = tmp->next;
   }
}
void displayMyFinalstate(Queue *q){
  Element *tmp;
   tmp = q->myfront;
   cout<<"***Final State : ";
   while (tmp != NULL){
     cout<<tmp->final_state<<" ";
     tmp = tmp->next;
   }
}
void LoadFA_File() //we create this void function for pull out file from text file
{
    system("cls");
    Myfile.open("auto.txt",ios::in);
    short loop =0;
    cin.ignore(1, '\n');
    cout<<"\t\t=============Table File============="<<endl;
    if (Myfile.is_open()){ //checking whether the file is open
      string tp;
      while(getline(Myfile, tp)){ //read data from file object and put it into string.
         cout << tp<< "\n"; //print the data of the string
      }
      Myfile.close(); //close the file object.
   }
   exit();
}
void FullOption()
{
    system("color 3");
    //Myfile.open("auto.txt",ios::app);
    int n;
    cout<<"\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<"<<endl;
    cout<<"\t\t\t\tWelcome to FA Program"<<endl;
    cout<<"\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<"<<endl;
    //cout<<"\t\t\t **********Menu**********"<<endl;
    cout<<"\t\t1.Load FA from file"<<endl;
    cout<<"\t\t2.Create New FA"<<endl;
    cout<<"\t\t3.Convert NFA to DFA"<<endl;
    cout<<"\t\t4.Minimize a DFA"<<endl;
    cout<<"\t\t5.Test if string except by FA"<<endl;
    cout<<"\t\t6.Delete FA file"<<endl;
    cout<<"\t\t7.update FA file"<<endl;
    cout<<"\t\t8.exit program"<<endl;
    cout<<"Choose your option: ";cin>>n; cout << endl;

    if (n==1)
    {
        LoadFA_File();
        exit();
    }
   else if (n==2)
    {
        CreateNewFAfile();
        exit();
    }
    else if (n==3)
    {
        convertNFAToDFA();
        exit();
    }
    else if(n==4)
    {
        MinimizeDFA();
        exit();
    }
    else if(n==5)
    {
        TestFAstring();
        exit();
    }
    else if(n==6)
    {
        DeleteCurrentFA();
        exit();
    }
    else if(n==7)
    {
        updateFA();
        exit();
    }
     else if(n==8)

    return;

    //Myfile.close();
}
void CreateNewFAfile()
{
    int num;
    cout << "1.DFA\n";
    cout << "2.NFA\n";
    cout<<"\t\tEnter your FA: ";cin>>num;
    if(num == 1)
    {
        DFA();
    }
    else if (num == 2)
    {
        NFA();
    }
}
void DFA()
{
    system("cls");
    Myfile.open("auto.txt",ios::app);
    cout<<"\n\t\t************** DFA **************"<<endl;
    string type="DFA";
    int ID;
    string Name;
    cout<<"\n=>ID:";cin>>f.ID;
    Myfile << "\n=>ID: " <<f.ID;
    //Myfile<<"=>ID:";Myfile>>ID;
    cout<<"\n=>File Name: ";cin>>f.name;
    Myfile<<"\n=>File Name: "<< f.name;
    Myfile<<endl;

    Queue *qsymbol;
    Queue *qstate;
    Queue *qtransition;
    Queue *qfinalstate;
    qsymbol=createEmptyqueue();
    qstate = createEmptyqueue();
    qtransition=createEmptyqueue();
    qfinalstate=createEmptyqueue();
    char symbol;
    int Nofstate,Nofsymbol,NofFinState;
    string state,StartState,FinalState;
    cout<<"\n\t=>Enter number of state:";cin>>Nofstate;

    for( int a=0;a<Nofstate;a=a+1)
    {
        cout<<"\t\tState "<<a+1<<" : ";cin>>state;
        //Myfile<<"\t\tState "<<a+1<<" : " << state;
        enqueueState(qstate,state);
    }
    cout<<"\t=>Enter the number of symbol:";cin>>Nofsymbol;

    for(int a=0;a<Nofsymbol;a=a+1)
    {
        cout<<"\t\tSymbol "<<a+1<<" : ";cin>>symbol;
       // Myfile<<"\t\tSymbol"<<a+1<<" :" << symbol;
        enqueueSymbol(qsymbol,symbol);
    }
    cout<<"\t=>Enter start state:";cin>>StartState;
    cout<<"\n\t***Enter the number of final state:";cin>>NofFinState;
    for( int a=0;a<NofFinState;a=a+1)
    {
        cout<<"\t\tFinal state "<<a+1<<" : ";cin>>FinalState;
        //Myfile<<"\t\tFinal state "<<a+1<<" : " << FinalState;
        enqueueFinalState(qfinalstate,FinalState);
    }
    Element *tmpsymbol;
    tmpsymbol =qsymbol->myfront;
    char ep='E';
    string Storestate;
    Element *tmpstate;
    tmpstate=qstate->myfront;
    cout<<"\n\t\t**********Transition**********" <<endl;
    for( int a=0;a<Nofstate;a=a+1)
    {
        cout<<"\t State:"<<tmpstate->state<<" \t";
        //Myfile<<"\t State:"<<tmpstate->state<<" \t";
        enqueueSymbol(qsymbol,symbol);
        tmpstate=tmpstate->next;
//        cout<<"\n\t\t=>Transition by " << ep <<":";
//        cin>>Storestate;
//        enqueueTransition(qtransition,Storestate,ep);
        tmpsymbol=qsymbol->myfront;
        cout <<endl;
        for (int j=0; j<Nofsymbol; j=j+1){
            cout<<"\t\t=>Transition by "<<tmpsymbol->symbol<<" : ";  cin>>Storestate;
            enqueueTransition(qtransition,Storestate,tmpsymbol->symbol);
            tmpsymbol=tmpsymbol->next;
            cout <<endl;
        }
    }
    cout<<"\n\t=>Start State: "<<StartState; cout<<endl;
    cout << "\t";displayMyFinalstate(qfinalstate);
    tmpsymbol=qsymbol->myfront;
    cout << "\n\n\t--------------------------------"<< endl;
    cout<<endl<<"\t\tTABLE DFA"<<endl;
    cout << "\t--------------------------------"<< endl;
    cout<<"\t";
     Myfile<<"\t";


    for (int a=0; a<Nofsymbol; a=a+1){
        cout<< "\t"<<tmpsymbol->symbol;
        Myfile<<"\t"<<tmpsymbol->symbol;
        tmpsymbol=tmpsymbol->next;
    }
    Element *tmp; // state
    tmpstate  = qstate->myfront;
    Element *tmptransition;
    tmptransition=qtransition->myfront;

    for (int a = 0; a< Nofstate; a++) {
        cout<<endl<<"\t"<<tmpstate->state<<"\t";
        Myfile<<endl<<"\t"<<tmpstate->state<<"\t";
        tmpstate=tmpstate->next;

        for (int a = 0; a < Nofsymbol; a++) {
        cout<<tmptransition->state<<"\t";
        Myfile<<tmptransition->state<<"\t";
        tmptransition=tmptransition->next;
        }
    }

    Myfile<<endl;
    exit();
    Myfile.close();
}
void NFA()
{
    system("cls");
    Myfile.open("auto.txt",ios::app);
    cout<<"\n\t\t************** NFA **************"<<endl;
    string type="NFA";
    int ID;
    string Name;
    cout<<"\n=>ID:";cin>>f.ID;
    Myfile << "\n=>ID: " <<f.ID;
    //Myfile<<"=>ID:";Myfile>>ID;
    cout<<"=>File Name: ";cin>> f.name;
    Myfile<<"\n=>File Name: "<< f.name;
    Myfile<<endl;

    Queue *qsymbol;
    Queue *qstate;
    Queue *qtransition;
    Queue *qfinalstate;
    qsymbol=createEmptyqueue();
    qstate = createEmptyqueue();
    qtransition=createEmptyqueue();
    qfinalstate=createEmptyqueue();
    char symbol;
    int Nofstate,Nofsymbol,NofFinState;
    string state,StartState,FinalState;
    cout<<"\n\t=>Enter number of state:";cin>>Nofstate;

    for( int a=0;a<Nofstate;a=a+1)
    {
        cout<<"\t\tState "<<a+1<<" : ";cin>>state;
        //Myfile<<"\t\tState "<<a+1<<" : " << state;
        enqueueState(qstate,state);
    }
    cout<<"\t=>Enter the number of symbol:";cin>>Nofsymbol;

    for(int a=0;a<Nofsymbol;a=a+1)
    {
        cout<<"\t\tSymbol "<<a+1<<" : ";cin>>symbol;
       // Myfile<<"\t\tSymbol"<<a+1<<" :" << symbol;
        enqueueSymbol(qsymbol,symbol);
    }
    cout<<"\t=>Enter start state:";cin>>StartState;
    cout<<"\n\t***Enter the number of final state:";cin>>NofFinState;
    for( int a=0;a<NofFinState;a=a+1)
    {
        cout<<"\t\tFinal state "<<a+1<<" : ";cin>>FinalState;
        //Myfile<<"\t\tFinal state "<<a+1<<" : " << FinalState;
        enqueueFinalState(qfinalstate,FinalState);
    }
    Element *tmpsymbol;
    tmpsymbol =qsymbol->myfront;
    char ep='E';
    string Storestate;
    Element *tmpstate;
    tmpstate=qstate->myfront;
    cout<<"\n\t\t**********Transition**********" <<endl;
    for( int a=0;a<Nofstate;a=a+1)
    {
        cout<<"\t State:"<<tmpstate->state<<" \t";
        //Myfile<<"\t State:"<<tmpstate->state<<" \t";
        enqueueSymbol(qsymbol,symbol);
        tmpstate=tmpstate->next;
        cout<<"\n\t\t=>Transition by " << ep <<":";
        cin>>Storestate;
        enqueueTransition(qtransition,Storestate,ep);
        tmpsymbol=qsymbol->myfront;
        cout <<endl;
        for (int j=0; j<Nofsymbol; j=j+1){
            cout<<"\t\t=>Transition by "<<tmpsymbol->symbol<<" : ";  cin>>Storestate;
            enqueueTransition(qtransition,Storestate,tmpsymbol->symbol);
            tmpsymbol=tmpsymbol->next;
            cout <<endl;
        }
    }
    cout<<"\n\t=>Start State: "<<StartState; cout<<endl;
    cout << " \t";displayMyFinalstate(qfinalstate);
    tmpsymbol=qsymbol->myfront;
    cout<<endl<<"\n\t\tTABLE NFA"<<endl;
    cout << "\t--------------------------------"<< endl;
    cout<<"\t\tep";
     Myfile<<"\t\tep";

    for (int a=0; a<Nofsymbol; a=a+1){
        cout<<"\t"<<tmpsymbol->symbol;
        Myfile<<"\t"<<tmpsymbol->symbol;
        tmpsymbol=tmpsymbol->next;
    }
    //Element *tmp; // state
    tmpstate  = qstate->myfront;
    Element *tmptransition;
    tmptransition=qtransition->myfront;

    for (int a = 0; a<Nofstate; a++) {
        cout<<endl<<"\t"<<tmpstate->state<<"\t";
        Myfile<<endl<<"\t"<<tmpstate->state<<"\t";
        tmpstate=tmpstate->next;

        for (int a = 0; a <= Nofsymbol; a++) {
        cout<<tmptransition->state<<"\t";
        Myfile<<tmptransition->state<<"\t";
        tmptransition=tmptransition->next;
        }
    }
    Myfile<<endl;
    exit();
    Myfile.close();
}
void print(vector<vector<vector<int> > > table)
{
    cout<<"\tSTATE  |";
	char a='a';
	for(int i=0;i<table[0].size()-1;i++){
		cout<<" "<<a++<<"\t"<<"|";
	}
	cout<<"Ep"<<endl<<endl;
	for(int i=0;i<table.size();i++){
		cout<<"\t"<<i<<"\t";
		for(int j=0;j<table[i].size();j++){
			cout<<"{";
			for(int k=0;k<table[i][j].size();k++){
				cout<<table[i][j][k]<<" ";

			}
			cout<<"}\t";
		}
		cout<<endl;
	}
}
void printDfa(vector<vector<int> > states, vector<vector<vector<int> > > dfa){
	cout<<"\tSTATE  |";
	char a='a';
	for(int i=0;i<dfa[0].size();i++){
		cout<<" "<<a++<<"\t"<<"|";
	}
	cout<<"Ep"<<endl<<endl;
	for(int i=0;i<states.size();i++){
		cout<<"\t{";
		for(int h=0;h<states[i].size();h++)
			cout<<states[i][h]<<" ";
		if(states[i].empty()){
			cout<<"Ep";
		}
		cout<<"}\t";
		for(int j=0;j<dfa[i].size();j++){
			cout<<"{";
			for(int k=0;k<dfa[i][j].size();k++){
				cout<<dfa[i][j][k]<<" ";

			}
			if(dfa[i][j].empty()){
				cout<<"Ep";
			}
			cout<<"}\t";
		}
		cout<<endl;
	}
}
vector<int> closure(int s, vector<vector<vector<int> > > v){
    vector<int> t;
    queue<int>q ;
    t.push_back(s);

    int a =v[s][v[s].size()-1].size();
    for(int i=0;i<a;i++){
        t.push_back(v[s][v[s].size()-1][i]);
        q.push(t[i]);
    }
    while(!q.empty()){
        int f = q.front();
        q.pop();
        if(!v[f][v[f].size()-1].empty()){
            int u =v[f][v[f].size()-1].size();
            for(int i=0;i<u;i++){
                int y =v[f][v[f].size()-1][i];
                if(find (t.begin(),t.end(),y)==t.end()){
                    t.push_back(y);
                    q.push(y);
                }
            }
        }
    }
    return t;
}
// Convert NFA to DFA
void convertNFAToDFA(){
    system("cls");
    Myfile.open("auto.txt",ios::app);
    int n,alpha;
    int ID;
    int y,yn;
    int num;
    cout<< "\n\t\t===================================="<<endl;
    cout<< "\t\t\t NFA TO DFA"<<endl;
    cout<< "\t\t===================================="<<endl;
    cout<<"\n\t**Note : All the state input in Number {0,1,...}**"<<endl;
    cout<<"\t**All the transition input in Number {0,1,...}**"<<endl;
    cout<< "\n\t\t===================================="<<endl;
    cout<<"\n\t*The number of states in NFA : ";cin>>n;
    cout<<"\t*The number of alphabet : ";cin>>alpha;
    vector<vector<vector<int> > > table;
    for(int i=0;i<n;i++){
        cout<< "\tState "<<i<<endl;
        vector< vector< int > > v;
        char a = 'a';
        int y,yn;

        for(int j=0;j<alpha;j++){
            vector<int> t;
            cout<< "\t\tNumber of Transition "<< a++<<":";
            cin>>yn;
            cout<< "\t\tTransition: "<< endl;
            for(int k=0;k<yn;k++){
                cout<< "\t\t\t=>";
                cin>>y;
                t.push_back(y);
            }
            v.push_back(t);
        }
        vector<int> t;
        cout<< "\t\t Number of Ep:";
        cin>>yn;
        cout<< "\t\tTransition: "<<endl;
        for(int k=0; k<yn;k++){
            cout<< "\t\t\t=>";
            cin>>y;
            t.push_back(y);
        }
        v.push_back(t);
        table.push_back(v);
    }
    cout<<"\n\t******** TRANSITION TABLE OF NFA ************"<<endl;
    print(table);
    cout<<endl<<"\t******** TRANSITION TABLE OF DFA ************"<<endl;
    vector<vector<vector<int> > > dfa;
    vector<vector<int> > states;
    states.push_back(closure(0,table));
    queue<vector<int> > q;
    q.push(states[0]);
    while(!q.empty()){
            vector<int> f= q .front();
    q.pop();
    vector<vector<int> > v;
    for(int i=0; i<alpha; i++){
        vector<int> t;
        set<int>s;
        for(int j=0;j<f.size();j++){
            for(int k=0;k<table[f[j]][i].size();k++){
                vector<int> cl = closure(table[f[j]][i][k],table);
                for(int h=0;h<cl.size();h++){
                    if(s.find(cl[h]) == s.end() ) // position
                    {
                         s.insert(cl[h]);
                    }
                }
            }
        }
        for(set<int> ::iterator u =s.begin();u!=s.end();u++)
            t.push_back(*u);
        v.push_back(t);
        if(find(states.begin(),states.end(),t)==states.end())
        {
            states.push_back(t);
            q.push(t);
        }
    }
    dfa.push_back(v);
    }
    printDfa(states,dfa);
//    cout<<"\t******** TRANSITION TABLE OF DFA ************"<<endl;
//    printTable(table);
    Myfile.close();
}
void input_DFA(){

    char a ='A'; char in;char st;
    //char* DFA_finals;
    DFA_finals = new char[25];
    cout<<"\t\t==========================================="<<endl;
    cout<<"\t\t\t\tMinimize DFA"<<endl;
    cout<<"\t\t============================================"<<endl;
    cout<<"\t****Input symbols: '0', '1',...";
    cout<<"\n\t****Input Transition: 'A', 'B', 'C',...";
    cout<< "\n\t****If there are two or more final states input like =>ex AB)"<<endl;
    cout<<"\t=============================================================="<<endl;
    cout<<"\n\t\t*Enter Number of Symbol: ";cin>> N_symbols;
    cout<<"\n\t\t*Enter Number of State:";cin>>N_DFA_states;
    cout<<"\t\t *Enter start State: A"<<endl;
    cout<<"\t\t *Enter final State: "; cin>>DFA_finals;
    for(int i=0; i< N_DFA_states; i++){
        cout<<"\n\tState "<< a++<< ":";
        for(int j=0;j<N_symbols;j++){
            cout<<"\n\t\t\tTransition "<<j<< ":";
            cin>>in;
            DFAtab[i][j] = in;
        }
    }
}
void get_next_state(char *nextstates, char *cur_states, int dfa[STATES][SYMBOLS], int symbols)
{

    int i,h;
    for(i =0;i<strlen(cur_states);i++){
        *nextstates++ = dfa[cur_states[i]-'A'][symbols];
        *nextstates = '\0';
    }
}
char equiv_class_ndx(char ch, char stnt[][STATES+1],int n){
    int i;
    for(i =0;i<n;i++)
        if(strchr(stnt[i],ch))return i+'0';
    return -1;
}

char is_one_nextstate(char *s){
    char equiv_class;

    while(*s == '@')s++;
    equiv_class = *s++;
    while(*s){
        if(*s != '@' && *s != equiv_class)return 0;
        s++;
    }
    return equiv_class;

}
int state_index(char *state,char stnt[][STATES+1],int n,int *pn,int cur){
    int i;
    char state_flags[STATES+1];
    if(!*state)return -1;
    for(i=0; i<strlen(state);i++)
        state_flags[i] = equiv_class_ndx(state[i],stnt,n);state_flags[i] = '\0';
    if(i = is_one_nextstate(state_flags))
        return i-'0';
    else{
        strcpy(stnt[*pn],state_flags);
        return (*pn)++;
    }

}
int init_quiv_clas(char statename[][STATES+1],int n, char *finals)
{
    int i,j;
    if(strlen(finals)==n){
        strcpy(statename[0],finals);return 1;
    }
    strcpy(statename[1],finals);
    for(int i=j=0; i<n;i++){
        if(i == *finals - 'A'){
            finals++;
        }else statename[0][j++] = i+ 'A';
    }
    statename[0][j] = '\0';return 2;
}

int get_optimized_DFA (char stnt[][STATES+1], int n,int dfa [][SYMBOLS],int n_sym, int newdfa[][SYMBOLS])
{
    int n2 = n;
    int i,j;
    char nextstate[STATES +1];

    for(i =0; i<n ;i++){
        for(j=0 ; j< n_sym;  j++){
            get_next_state(nextstate, stnt [i],dfa ,j);
            newdfa[i][j] = state_index(nextstate, stnt , n ,&n2,i)+ 'A';
        }
    }
    return n2;
}

void chr_append(char *s, char ch){
    int n =strlen(s);
    *(s+n) = ch;
    *(s+n+1) = '\0';
}

void sort(char stnt[][STATES +1], int n){
    int i,j;
    char temp[STATES+1];

    for(i=0; i<n-1 ;i++)
        for(j =i+1 ;j<n; j++)
    if(stnt[i][0] > stnt [j][0]){
        strcpy(temp, stnt[i]);
        strcpy(stnt[i],stnt[j]);
        strcpy(stnt[j],temp);
    }
}
int SplitEquivClass(char stnt[][STATES+1], int i1, int i2, int n, int n_dfa)    //stnt=state name table
{
    char *old = stnt[i1], *vec = stnt[i2];
    char newStates[STATES][STATES+1];
    int i, n2, status=0;

    for(i=0; i<STATES; i++)
    {
        newStates[i][0] = '\0';
    }

    for(i=0; vec[i]; i++)
    {
        chr_append(newStates[vec[i]-'0'], old[i]);
    }

    for(i=0, n2=n; i<n_dfa; i++)
    {
        if(newStates[i][0])
        {
            if(!status)
            {
                strcpy(stnt[i], newStates[i]);
                status=1;
            }
            else
            {
                strcpy(stnt[n2++], newStates[i]);
            }
        }
    }
    sort(stnt, n2);

    return n2;
}

int setNewEquivClass(char stnt[][STATES+1], int n, int new_dfa[][SYMBOLS], int n_sym, int n_dfa)
{
    int i, j, k;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n_sym; j++)
        {
            k = new_dfa[i][j]-'A';
            if(k >= n)
            {
                return SplitEquivClass(stnt, i, k, n, n_dfa);
            }
        }
    }
    return n;
}
int optimizeDFA(int dfa[][SYMBOLS], int n_dfa, int n_sym, char *finals, char stnt[][STATES+1], int new_dfa[][SYMBOLS])
{
    char nextState[STATES+1];
    int n, n2;

    n = init_quiv_clas(stnt, n_dfa, finals);

    while(1)
    {
//        printEquivClass(stnt, n);

        n2 = get_optimized_DFA(stnt,n,dfa,n_sym,new_dfa);

        if(n != n2)
        {
            n = setNewEquivClass(stnt,n,new_dfa,n_sym,n_dfa);
        }
        else
        {
            break;
        }
    }
    return n;
}
int isSubset(char *s, char *t)
{
    for(int i=0; *t; i++)

        if(!strchr(s, *t++))
            return 0;
    return 1;
}
void getNewFinals(char *newFinals, char *oldFinals, char stnt[][STATES+1], int n)
{
    for(int i=0; i<n; i++)
        if(isSubset(oldFinals, stnt[i]))


            *newFinals++ = i+'A'; // FINAL

    *newFinals++ = '\0'; // \0 = null
}
void printTable(int tab[][SYMBOLS],int nstates,int nsymbols,char *finals)
{
	int i, j;
	char a='a';
	puts("\n\n\t\tDFA: STATE TRANSITION TABLE");
	printf("\t\tState| ");
	for (i = 0; i < nsymbols; i++) printf(" %c\t", '0'+i);
	printf("\n\t\t\t--------");
	for (i = 0; i < nsymbols; i++) printf("-----");
	printf("\n");
	for (i = 0; i < nstates; i++) {
		printf("\t\t % c   |\t", 'A'+i);
		for (j = 0; j < nsymbols; j++)
			printf("%c\t", tab[i][j]);
		printf("\n");
	}
	printf("\n\t\t\tFinal states = %s\n", finals);
}
void print_dfa_table(int tab[][SYMBOLS],int nstates, int nsymbols, char *finals){
    char st;
    //printf("\tStart States = %s \n",st);
    int i,j;
    char a = 'A';
    puts("\n\n\t\tDFA: STATE TRANSITION TABLE");
    printf("\t\tState |\t");
    for(i=0; i<nsymbols; i++)printf("%c\t", '0'+i);
    printf("\n\t\t\t---------");
    for(i=0; i<nsymbols;i++) printf("-----");
    printf("\n");
    for(i=0; i < nstates ;i++){
        printf("\t\t%c |\t",'A'+i);//a++;
        for(j=0; j < nsymbols;j++)
            printf("%c \t", tab[i][j]);
            printf("\n");
        }
        cout<<endl;
        printf("\n\tFinal States = %s \n",finals);
}
void MinimizeDFA()
{
    system("cls");
    Myfile.open("auto.txt",ios::app);
    system("cls");
    input_DFA();
    printTable(DFAtab, N_DFA_states, N_symbols, DFA_finals);

    N_optDFA_states = optimizeDFA(DFAtab, N_DFA_states,N_symbols, DFA_finals, StateName, OptDFA);
    getNewFinals(NEW_finals, DFA_finals, StateName, N_optDFA_states);
    print_dfa_table(OptDFA, N_optDFA_states, N_symbols, NEW_finals);

    Myfile.close();
}
void inputDFA1()
{
    char a='A',iN;
    //char* DFA_finals;
    //int DFAtab[STATES][SYMBOLS];
    DFA_finals = new char[25];
    cout << "\t\t-----------------------------------\n";
    cout << "\t\t\tWELCOME TO Testing DFA\n";
    cout << "\t\t-----------------------------------\n";
    cout<<"\t>>>Enter symbols:{ '0', '1', ...}"<<endl;
    cout<<"\t>>>State names:{ 'A', 'B', 'C', ...}"<<endl;
    cout<<"\t>>>If there are two or more final states input.*E.g:AB)"<<endl;
    cout<<"\t======================================================"<<endl;
    cout << "\n\t\t Enter number of Symbol: "; cin>>N_symbols;
    cout << "\t\t Enter number of State: "; cin >> N_DFA_states;
    cout << "\t\t Enter final state: "; cin>> DFA_finals;
    for(int i=0;i<N_DFA_states;i++)
    {
        state[i] = a;
        cout << "\n\t\tState" << a++ << " : " <<endl;
        for(int j=0;j<N_symbols;j++)
        {
            cout<< "\t\t\t\tTransition " <<j<< " : "; cin>>iN;
            DFAtab[i][j]= iN;
        }
    }
}
int TestFAstring()
{
    system("cls");
    //ifstream Myfile;
    Myfile.open("auto.txt",ios::app);

    inputDFA1();
	printTable(DFAtab,N_DFA_states,N_symbols,DFA_finals);

while(1)
{
       char str[max],f='a'; // end 011
       int i;
       printf("\n\t Enter the string to be checked: ");
       scanf("%s",str);
       for(i=0;str[i]!='\0';i++) {
          switch(f) {
             case 'a': if(str[i]=='0') f='b';
                else if(str[i]=='1') f='a';
             break;
             case 'b': if(str[i]=='0') f='b';
                else if(str[i]=='1') f='c';
             break;
             case 'c': if(str[i]=='0') f='b';
                else if(str[i]=='1') f='d';
             break;
             case 'd': if(str[i]=='0') f='d';
                else if(str[i]=='1') f='d';
             break;
          }
       }
           if(f =='d') // == final state
          printf("\n\t\tString is accepted.\n", f);
        else printf("\n\t\tString is not accepted.\n", f);
    }
    Myfile.close();
    exit();
}
//Delete
void DeleteCurrentFA() // delete all data
{
    system("cls");
    ifstream Myfile;
    Myfile.open("auto.txt");
    ofstream writefile;
    writefile.open("new.txt");
    Element *tmp;
    cout << "\n\t\t\t********************************\n";
    cout << "\t\t\t****Welcome to delete FA********\n";
    cout << "\t\t\t********************************\n";
    cout << "\t\t Delete function"<<endl;
    if(!Myfile)
    {
        cout<< "File is not found.\n";
    }
    else{
            cout << "Delete successful \n";
        Myfile.read((char*)&tmp,sizeof(tmp));
        while (!Myfile.eof())
        {
            Myfile.read((char*)&tmp,sizeof(tmp));
        }
    }
    Myfile.close();
    writefile.close();
    remove("auto.txt");
    rename("new.txt","auto.txt");
    exit();
}
void insert_data(ofstream &write) {

   file f1;

    cout << "\n\tEnter id : ";

    cin >> f1.ID;

    cout << "\n\tEnter name : ";

    cin.get();

    getline(cin, f1.name);

    write << f1.ID << endl;

    write << f1.name <<endl;
}
void updateFA(string id,ifstream &read)
{
   system("cls");
   string name;
   //string id;
   //ifstream read("auto.txt");
   ofstream writefile("auto.txt");

   //writefile.open("auto.txt",ios::app);
//    fstream read;
//    read.open("auto.txt",ios::in);

   file f;

   f = get_data(read);

   while(!read.eof())
   {
       if(f.ID ==id)
       {
           cout << "\n\tEnter new ID: "<<id;
           insert_data(writefile);
       }
       else
       {
           writefile<<f.ID<<endl;
           writefile<<f.name<<endl;
       }
       f = get_data(read);
   }

   read.close();
   writefile.close();
   remove("auto.txt");
   rename("new.txt","auto.txt");
}
void searchdata()
{
    string idsearch, id, name;
    ifstream Myfile("auto.txt");
    bool found = false;
    string line;
    cout << "Enter ID to search: "; cin>> idsearch;
    if(Myfile.is_open())
    {
        while (getline(Myfile,line))
        {
            f.ID = line.substr(0,8);
            if(f.ID != idsearch)
            {
                found = true;
                break;
            }
            else{
                found = false;
            }
        }
        if(found == true)
        {
            name= line.substr(9,line.length()-1);
            cout << "\n*****************************\n";
            cout << "ID number: "; cin>> id;
            cout << "Name: "; cin>> name;
            cout << "\n*****************************\n";
            cin.get();
        }
        else
        {
            cout << "ID is not exist! \n";
            cin.get();
        }
    }
    else {
        cout << "enable to open file! Press any key to continue.\n";
    }
    Myfile.close();
}


void updateFA()
{
    ifstream Myfile("auto.txt");
    string idsearch , newname;
    int newid;
    int recon;
    bool found;
    int counter = 0;
    string line;
    string linearr[100];

    try {
    cout << endl;
    cout << "\t\tEnter ID: "; cin >> idsearch;
    cout <<endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid number."<<endl;
    }
            if(Myfile.is_open())
    {
        found = false;
         while (getline(Myfile,line))
        {
            f.ID = line.substr(0,5);
            if(f.ID == idsearch)
            {
                found = true;
                break;
            }
            else{
                found = false;
            }
        }


    if (found == false )
    {
        //system("cls");
            cout<< "New ID : ";cin>> newid;cout<<endl;
            cout << "update name: "; cin>> newname;
            //getline(cin.newname);
            //getline(cin.newname);

            //linearr[recon] = idsearch+"," + newname + "," ;

            fstream write("auto.txt");
            //write.open("auto.txt",ios::out);
            for(int i=0;i<counter;i++)
            {
                write << idsearch <<endl;
                write << newname << endl;
            }
            cout << "update successfully!\n";
            cin.get();
    write.close();
    }
    Myfile.close();
    }

}
void exit()
{
        cout<<endl;
        cout <<"\nPress 'b' back:";cin>>m;
        if (m=='b'||m=='B')
        {
            system("cls");
            FullOption();
        }
}
void loadbar()
{

    Myfile.open("auto.txt",ios::in);
    //system("COLOR 4");
    system("cls");
    //printf("\e[?251");
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1=178,bar2=221;
    cout << "\n\n\n\n\n\n\n\n\n\n "<<setw(62.5) << "\tWELCOME TO MENU";
    cout<< "\n\n"<<setw(40);
    for (int i=0;i<33;i++)
    {
        cout<<(char)bar2;
        Sleep(50);
    }
    cout<< "\n\n"<<setw(40)<<(char)1<<"!";
   system("Pause");
    Myfile.close();
    }

int main()
{
    system("cls");
   // system("COLOR 2e");
    //system("color 4");
    loadbar();
    system("cls");
    //system("color 3");
    FullOption();
    cout<< endl;

}