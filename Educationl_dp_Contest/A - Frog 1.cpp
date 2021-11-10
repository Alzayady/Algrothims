#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <time.h>
#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long int ll;
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
    int n ;
    cin>>n ;
    int arr[n+2];
    for(int i =0 ;i < n ; i++)cin>>arr[i];
    int best_in_last= abs(arr[1]-arr[0]);
    int best_in_last_last=0;
    for(int i = 2 ;i < n ; i++){
        int best_in_last_temp=best_in_last;
        best_in_last=min(best_in_last+(abs(arr[i]-arr[i-1])),best_in_last_last+abs(arr[i]-arr[i-2]));
        best_in_last_last=best_in_last_temp;
    }
    cout<<best_in_last<<endl;

    return 0;
}
