#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool IsSimpleGraph(vector<int> v) {
    if (v.empty()) return true;
    
   
    sort(v.rbegin(), v.rend());
    
    int n = v.size();
    
   
    int sum = 0;
    for (int degree : v) {
        sum += degree;
       
        if (degree >= n) return false;
    }
    if (sum % 2 != 0) return false;
    
    
    for (int k = 1; k <= n; k++) {
        int leftSum = 0;
        for (int i = 0; i < k; i++) {
            leftSum += v[i];
        }
        
        int rightSum = k * (k - 1);
        for (int i = k; i < n; i++) {
            rightSum += min(v[i], k);
        }
        
        if (leftSum > rightSum) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int num;
    cin >> num;
    
    for (int i = 0; i < num; i++) {
        int a;
        cin >> a;
        vector<int> v(a);
        
        for (int j = 0; j < a; j++) {
            cin >> v[j];
        }
        
        if (IsSimpleGraph(v)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}