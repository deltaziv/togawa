#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int num;
int dp[1<<18][18];
int parent[1<<18][18];
string dpStr[1<<18][18]; 
//dp[mask][i]:mask means the set of visited nodes(by 2^i), i means the last one
//parent[mask][i]: the previous node before i in mask
//dpStr[mask][i]: the corresponding string for dp[mask][i]
//keep trying to add a new node j to mask, and update to the new mask

int check(string a,string b){
    int maxOverlap=0;
    int minLen=min(a.size(),b.size());
    for(int overlap=minLen;overlap>=1;overlap--){
        bool match=true;
        for(int i=0;i<overlap;i++){
            if(a[a.size()-overlap+i]!=b[i]){
                match=false;
                break;
            }
        }
        if(match){
            maxOverlap=overlap;
            break;
        }
    }
    return b.size()-maxOverlap;
}

void BuildAdj(vector<vector<int>> &adj,vector<string> &cha){
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(i!=j){
                int dif=check(cha[i],cha[j]);
                adj[i][j]=dif;
            }else{
                adj[i][j]=1000;
            }
        }
    }
}

void SolveMyGO(vector<vector<int>> &adj,vector<bool> &visit,vector<string> &cha,string &ans){
    memset(dp,0x3f,sizeof(dp));
    memset(parent,-1,sizeof(parent));

    for(int i=0;i<num;i++){
        dp[1<<i][i]=cha[i].size();
        dpStr[1<<i][i]=cha[i];
    }

    int fullMask=(1<<num)-1;

    for(int mask=0;mask<=fullMask;mask++){
        for(int i=0;i<num;i++){
            if(!(mask&(1<<i))) continue;
            if(dp[mask][i]>=1e8) continue;

            for(int j=0;j<num;j++){
                if(mask&(1<<j)) continue;
                int newMask=mask|(1<<j);
                int newLen=dp[mask][i]+adj[i][j];
                string newStr=dpStr[mask][i]+cha[j].substr(cha[j].size()-adj[i][j]);

                if(newLen < dp[newMask][j] || 
                   (newLen == dp[newMask][j] && newStr < dpStr[newMask][j])){
                    dp[newMask][j]=newLen;
                    parent[newMask][j]=i;
                    dpStr[newMask][j]=newStr;
                }
            }
        }
    }

    int minLen=1e9 + 7;
    string minStr="";

    for(int i=0;i<num;i++){
        if(dp[fullMask][i]>=1e9) continue;
        string tempAns=dpStr[fullMask][i];
        if(dp[fullMask][i] < minLen || 
           (dp[fullMask][i] == minLen && tempAns < minStr) || minStr == ""){
            minLen=dp[fullMask][i];
            minStr=tempAns;
        }
    }

    ans=minStr;
    return;
}

int main(){
    vector<string> cha;
    cin>>num;
    for(int i=0;i<num;i++){
        string k;
        cin>>k;
        cha.push_back(k);
    }

    vector<string> filtered;
    vector<bool> isSubstring(num,false);
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(i!=j && cha[j].find(cha[i])!=string::npos){
                isSubstring[i]=true;
                break;
            }
        }
        if(!isSubstring[i]){
            filtered.push_back(cha[i]);
        }
    }

    num=filtered.size();
    cha=filtered;

    string ans="";
    vector<vector<int>> adj(num,vector<int>(num,0));
    vector<bool> visit;
    BuildAdj(adj,cha);
    SolveMyGO(adj,visit,cha,ans);
    cout<<ans<<endl;

    return 0;
}