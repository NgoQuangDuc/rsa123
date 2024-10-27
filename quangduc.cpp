#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i, eve[100];
char msg[100];
int fin_msg[100];
ll r;

ll c1[100], c2[100], c3[100];
ll m1, m2, m3;
ll M, M1, M2, M3;
ll i_M1, i_M2, i_M3;

ll inv(ll a, ll m) { 
    ll m0 = m, t, q; 
    ll x0 = 0, x1 = 1; 
    if (m == 1) return 0; 
    while (a > 1) { 
        q = a / m; t = m; 
        m = a % m, a = t; 
        t = x0; 
        x0 = x1 - q * x0; 
        x1 = t; 
    } 
    if (x1 < 0) x1 += m0; 
    return x1; 
}

ll gcd(ll a, ll b) { 
    if (b == 0) return a; 
    return gcd(b, a % b);  
}

ll check_gcd(ll a, ll b, ll c) {
    ll g1 = gcd(a, b);
    ll g2 = gcd(b, c);
    ll g3 = gcd(a, c);
    return (g1 == 1 && g2 == 1 && g3 == 1) ? 1 : 0;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y) { 
    if (a == 0) { 
        *x = 0, *y = 1; 
        return b; 
    } 
    ll x1, y1; 
    ll gcd = gcdExtended(b % a, a, &x1, &y1); 
    *x = y1 - (b / a) * x1; 
    *y = x1; 
    return gcd; 
} 

ll modInverse(ll a, ll m) { 
    ll x, y; 
    ll g = gcdExtended(a, m, &x, &y); 
    if (g != 1) return 0;
    ll res = (x % m + m) % m; 
    return res;
} 

ll power(ll x, ll y, ll p) {  
    ll res = 1; x = x % p; 
    if (x == 0) return 0; 
    while (y > 0) {  
        if (y & 1) res = (res * x) % p;  
        y = y >> 1; x = (x * x) % p;  
    }  
    return res;  
}  

ll prime(ll pr) {
    ll i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++) {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

void encrypt(ll e_val,string filename) {
    ll i = 0;
    ll len = strlen(msg); 
    while (i < len) {
        c1[i] = power(msg[i], e_val, m1);
        c2[i] = power(msg[i], e_val, m2);
        c3[i] = power(msg[i], e_val, m3);
        i++;
    }

    ofstream outfile(filename);  // Ghi đè lên tệp message.txt
    for (i = 0; i < len; i++) {
        outfile << c1[i] << " ";
    }
    outfile << endl;
    for (i = 0; i < len; i++) {
        outfile << c2[i] << " ";
    }
    outfile << endl;
    for (i = 0; i < len; i++) {
        outfile << c3[i] << " ";
    }
    outfile << endl;
    outfile.close();
}

ll compute(ll c1, ll c2, ll c3) {
    i_M1 = 2225; i_M2 = 389301; i_M3 = 2099309;
    ll x = (((c1 * M1) % M * i_M1) % M + ((c2 * M2) % M * i_M2) % M + ((c3 * M3) % M * i_M3)) % M;
    return cbrt(x);
}

void decrypt() {
    ll i = 0;
    ll len = strlen(msg);
    ofstream outfile("decrypted.txt");
    outfile << "\nTHE DECRYPTED MESSAGE IS\n";
    while (i < len) {
        m[i] = compute(c1[i], c2[i], c3[i]);
        char val = m[i];
        outfile << m[i] << " " << val << endl;
        i++;
    }
    outfile.close();
}

ll findMinX(ll num[], ll rem[], ll k) { 
    ll prod = 1; 
    for (ll i = 0; i < k; i++) 
        prod *= num[i]; 

    ll result = 0; 
    ll pp[3];
    pp[0] = num[1] * num[2];
    pp[1] = num[0] * num[2];
    pp[2] = num[1] * num[0];

    for (ll i = 0; i < k; i++) { 
        result += (rem[i] * modInverse(pp[i], num[i]) * pp[i]) % prod; 
    } 
    return result % prod; 
} 

void decrypt_new() {
    ll num[] = {m1, m2, m3};
    ll k = sizeof(num) / sizeof(num[0]);
    ll len = strlen(msg);
    ofstream outfile("final_decrypted.txt");
    for (ll i = 0; i < len; i++) {
        ll rem[] = {c1[i], c2[i], c3[i]}; 
        m[i] = findMinX(num, rem, k);
        double tt = cbrt(m[i]); 
        fin_msg[i] = int(0.5 + tt);
    }
    for (ll i = 0; i < len; i++) {
        outfile << char(fin_msg[i]);
    }
    outfile << endl;
    outfile.close();
}

int main() {
	string filename;
    cout << "Say Alice choses 3 public keys for 3 diff persons with low exponent" << endl;
    cout << "Give Low exponent" << endl;
    ll exp;
    cin >> exp;
    ll p1, q1, p2, q2, p3, q3;

    cout << "Enter p.qs for each of N1,N2,N3 values" << endl;
    cin >> p1 >> q1 >> p2 >> q2 >> p3 >> q3;

    m1 = p1 * q1; m2 = p2 * q2; m3 = p3 * q3;

    if (check_gcd(m1, m2, m3) == 0) {
        cout << "Invalid N1,N2,N3 since they are coprime with each other" << endl;
        exit(1);
    }

	cin>>filename;
    ifstream infile(filename);
    infile.getline(msg, sizeof(msg));
    infile.close();

    encrypt(exp,filename);
    decrypt_new();  
    return 0;
}

