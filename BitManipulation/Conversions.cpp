#include<bits/stdc++.h>

using namespace std;

string decimal2Binary(int n){
    string res = "";
    while(n > 0){
        if(n % 2 == 1) res += '1';
        else res += '0';
        n = n / 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

int binary2Decimal(string x){
    int len = x.size();
    int num = 0;
    int p2 = 1;
    for(int i = len - 1; i >= 0; i--){
        if(x[i] == '1')
            num += p2;
        p2 *= 2;
    }
    return num;
}

int main(){
    cout<<"Binary 2 Decimal (1) | Decimal 2 Binary (2)"<<endl;
    int choice;
    cin>>choice;
    if(choice == 1){
        cout<<"Enter binary number: ";
        string x;
        cin>>x;
        cout<<binary2Decimal(x)<<endl;
    } else if(choice == 2){
        cout<<"Enter decimal number: ";
        int n;
        cin>>n;
        cout<<decimal2Binary(n)<<endl;
    } else {
        cout<<"Invalid choice"<<endl;
    }
}