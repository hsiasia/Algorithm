#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

    vector<int> num;
    vector<char> op;
    int numsize;
    int opsize;
    //儲存上與下括號
    int xparenth[100]={0};
    int yparenth[100]={0};
    int arg[100][100]={0};
    int maxx[100][100]={0};
    int minn[100][100]={0};
    int reversenum=0;
    int maxValue=1;
    int minValue=1;

void parament(int x,int y);
void findrout(int x,int y);

int main()
{
    string s;
    cin>>s;
    stringstream ss;
    ss<<s;

    //分割運算元運算子
    int temp_int;
    char temp_ch;
    while(ss>>temp_int){
        num.push_back(temp_int);
        ss>>temp_ch;
        op.push_back(temp_ch);
    }
    numsize = num.size();
    opsize = numsize-1;

    cout<<"operand: ";
    for(int i=0;i<numsize;i++){
        cout<<num[i]<<" ";
    }
    cout<<"\n";
    cout<<"operator: ";
    for(int i=0;i<opsize;i++){
        cout<<op[i]<<" ";
    }
    cout<<"\n"<<endl;

    for(int i=0;i<numsize;i++){
        maxx[i][i]=num[i];
        minn[i][i]=num[i];
    }
    //max&min dynamic program
    for(int x=1;x<=opsize;x++){
        for(int down=0;down<=opsize-x;down++){//下限
            int upp=down+x;//上限
            maxx[down][upp]=-10000;
            minn[down][upp]=10000;
            for(int middle=down;middle<upp;middle++){
                int maxnum;
                int minnum;
                int a,b,c,d;
                if(op[middle]=='+'){
                    a=maxx[down][middle]+maxx[middle+1][upp];
                    maxnum=a;
                    minnum=a;
                    b=maxx[down][middle]+minn[middle+1][upp];
                    if(maxnum<b){maxnum=b;}
                    if(minnum>b){minnum=b;}
                    c=minn[down][middle]+maxx[middle+1][upp];
                    if(maxnum<c){maxnum=c;}
                    if(minnum>c){minnum=c;}
                    d=minn[down][middle]+minn[middle+1][upp];
                    if(maxnum<d){maxnum=d;}
                    if(minnum>d){minnum=d;}
                }
                else if(op[middle]=='-'){
                    a=maxx[down][middle]-maxx[middle+1][upp];
                    maxnum=a;
                    minnum=a;
                    b=maxx[down][middle]-minn[middle+1][upp];
                    if(maxnum<b){maxnum=b;}
                    if(minnum>b){minnum=b;}
                    c=minn[down][middle]-maxx[middle+1][upp];
                    if(maxnum<c){maxnum=c;}
                    if(minnum>c){minnum=c;}
                    d=minn[down][middle]-minn[middle+1][upp];
                    if(maxnum<d){maxnum=d;}
                    if(minnum>d){minnum=d;}
                }
                else{
                    a=maxx[down][middle]*maxx[middle+1][upp];
                    maxnum=a;
                    minnum=a;
                    b=maxx[down][middle]*minn[middle+1][upp];
                    if(maxnum<b){maxnum=b;}
                    if(minnum>b){minnum=b;}
                    c=minn[down][middle]*maxx[middle+1][upp];
                    if(maxnum<c){maxnum=c;}
                    if(minnum>c){minnum=c;}
                    d=minn[down][middle]*minn[middle+1][upp];
                    if(maxnum<d){maxnum=d;}
                    if(minnum>d){minnum=d;}
                }
                if(maxnum>maxx[down][upp]){
                    maxx[down][upp]=maxnum;
                    arg[down][upp]=middle;
                }
                if(minnum<minn[down][upp]){
                    minn[down][upp]=minnum;
                    arg[upp][down]=middle;
                }
            }
        }
    }
    //初始路徑紀錄
    for(int i=0;i<numsize;i++){
        for(int j=0;j<numsize;j++){
            cout<<setw(4)<<arg[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    findrout(0,opsize);

    //max 紀錄
    for(int i=0;i<numsize;i++){
        for(int j=0;j<numsize;j++){
            cout<<setw(4)<<maxx[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<numsize;i++){
        for(int j=0;j<numsize;j++){
            cout<<setw(4)<<arg[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    //min 紀錄
    for(int i=0;i<numsize;i++){
        for(int j=0;j<numsize;j++){
            cout<<setw(4)<<minn[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    parament(0,numsize-1);

    for(int i=0;i<numsize;i++){

        while(xparenth[i]>0){
            cout<<"(";
            xparenth[i]--;
        }
        cout<<num[i];
        while(yparenth[i]>0){
            cout<<")";
            yparenth[i]--;
        }
        if(i<opsize){
            cout<<op[i];
        }
    }
}

void findrout(int xline,int yline){
    if(xline!=yline){
        int savemiddle=0;
        for(int middle=xline;middle<yline;middle++){
            if(maxValue==1){
                if(op[middle]=='+'){
                    if(maxx[xline][yline]==maxx[xline][middle]+maxx[middle+1][yline]){
                        savemiddle=middle;
                        maxValue=1;}
                    else if(maxx[xline][yline]==maxx[xline][middle]+minn[middle+1][yline]){
                        maxValue=2;
                        savemiddle=middle;}
                    else if(maxx[xline][yline]==minn[xline][middle]+maxx[middle+1][yline]){
                        maxValue=3;
                        savemiddle=middle;}
                    else if(maxx[xline][yline]==minn[xline][middle]+minn[middle+1][yline]){
                        maxValue=4;
                        savemiddle=middle;}
                }
                if(op[middle]=='-'){
                    if(maxx[xline][yline]==maxx[xline][middle]-maxx[middle+1][yline]){
                        savemiddle=middle;
                        maxValue=1;}
                    else if(maxx[xline][yline]==maxx[xline][middle]-minn[middle+1][yline]){
                        maxValue=2;
                        savemiddle=middle;}
                    else if(maxx[xline][yline]==minn[xline][middle]-maxx[middle+1][yline]){
                        maxValue=3;
                        savemiddle=middle;}
                    else if(maxx[xline][yline]==minn[xline][middle]-minn[middle+1][yline]){
                        maxValue=4;
                        savemiddle=middle;}
                }
                if(op[middle]=='*'){
                    if(maxx[xline][yline]==maxx[xline][middle]*maxx[middle+1][yline]){
                        savemiddle=middle;
                        maxValue=1;}
                    else if(maxx[xline][yline]==maxx[xline][middle]*minn[middle+1][yline]){
                        maxValue=2;
                        savemiddle=middle;}
                    else if(maxx[xline][yline]==minn[xline][middle]*maxx[middle+1][yline]){
                        maxValue=3;
                        savemiddle=middle;}
                    else if(maxx[xline][yline]==minn[xline][middle]*minn[middle+1][yline]){
                        maxValue=4;
                        savemiddle=middle;}
                }
            }
            else{
                if(op[middle]=='+'){
                    if(minn[xline][yline]==maxx[xline][middle]+maxx[middle+1][yline]){
                        savemiddle=middle;
                        minValue=1;}
                    else if(minn[xline][yline]==maxx[xline][middle]+minn[middle+1][yline]){
                        minValue=2;
                        savemiddle=middle;}
                    else if(minn[xline][yline]==minn[xline][middle]+maxx[middle+1][yline]){
                        minValue=3;
                        savemiddle=middle;}
                    else if(minn[xline][yline]==minn[xline][middle]+minn[middle+1][yline]){
                        minValue=4;
                        savemiddle=middle;}
                }
                if(op[middle]=='-'){
                    if(minn[xline][yline]==maxx[xline][middle]-maxx[middle+1][yline]){
                        savemiddle=middle;
                        minValue=1;}
                    else if(minn[xline][yline]==maxx[xline][middle]-minn[middle+1][yline]){
                        minValue=2;
                        savemiddle=middle;}
                    else if(minn[xline][yline]==minn[xline][middle]-maxx[middle+1][yline]){
                        minValue=3;
                        savemiddle=middle;}
                    else if(minn[xline][yline]==minn[xline][middle]-minn[middle+1][yline]){
                        minValue=4;
                        savemiddle=middle;}
                }
                if(op[middle]=='*'){
                    if(minn[xline][yline]==maxx[xline][middle]*maxx[middle+1][yline]){
                        savemiddle=middle;
                        minValue=1;}
                    else if(minn[xline][yline]==maxx[xline][middle]*minn[middle+1][yline]){
                        minValue=2;
                        savemiddle=middle;}
                    else if(minn[xline][yline]==minn[xline][middle]*maxx[middle+1][yline]){
                        minValue=3;
                        savemiddle=middle;}
                    else if(minn[xline][yline]==minn[xline][middle]*minn[middle+1][yline]){
                        minValue=4;
                        savemiddle=middle;}
                }
            }
        }
        if(maxValue!=1||reversenum==1||minValue!=1){
            reversenum=1;
            arg[xline][savemiddle]=arg[savemiddle][xline];
            arg[savemiddle+1][yline]=arg[yline][savemiddle+1];
        }
        findrout(xline,savemiddle);
        findrout(savemiddle+1,yline);
    }
    else{
        return;
    }
}

void parament(int a,int b){
    if(a==b){
        return;
    }
    xparenth[a]++;
    yparenth[b]++;

    int number = arg[a][b];
    parament(a,number);
    parament(number+1,b);
}
