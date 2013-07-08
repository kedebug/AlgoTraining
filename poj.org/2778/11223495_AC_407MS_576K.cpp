
#include <iostream>
#include <deque>
using namespace std;

const int MAX_SIZE = 10 * 10 + 1;
const int CHILD_NUM = 4;
const int MOD = 100000;

class CMatrix
{
public:
    int size;
    long long int elem[MAX_SIZE][MAX_SIZE];

    CMatrix() { memset(elem, 0, sizeof(elem)); }
    void SetSize(int n) 
    { 
        size = n; 
    }

    CMatrix operator = (const CMatrix& other)
    {
        SetSize(other.size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                elem[i][j] = other.elem[i][j];
        return *this;
    }

    CMatrix operator * (const CMatrix& other)
    {
        CMatrix temp;
        temp.SetSize(size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                for (int k = 0; k < size; ++k)
                {
                    temp.elem[i][j] += elem[i][k] * other.elem[k][j];
                    if (temp.elem[i][j] >= MOD)
                        temp.elem[i][j] %= MOD;
                }
        return temp;
    }

    void Power(int exp)
    {
        CMatrix E;
        E.SetSize(size);
        for (int i = 0; i < E.size; ++i)
            E.elem[i][i] = 1;

        while (exp)
        {
            if (exp & 0x01)
                E = E * (*this);
            *this = (*this) * (*this);
            exp >>= 1;
        }
        *this = E;
    }
};

class CAutomaton
{
private:
    int size;
    int trie[MAX_SIZE][CHILD_NUM];
    int fail[MAX_SIZE];
    int value[MAX_SIZE];
    int table[128];

public:
    void Initilize()
    {    
        table['A'] = 0;
        table['C'] = 1;
        table['T'] = 2;
        table['G'] = 3;
    }

    void Reset()
    {
        size = 1;
        memset(trie[0], 0, sizeof(trie[0]));
        memset(fail, 0, sizeof(fail));
        memset(value, 0, sizeof(value));
    }

    void Insert(char* word)
    {
        int p = 0;
        for (int i = 0; word[i]; ++i)
        {
            int m = table[word[i]];
            if (!trie[p][m])
            {
                memset(trie[size], 0, sizeof(trie[0]));
                trie[p][m] = size++;
            }
            p = trie[p][m];
        }
        value[p] = 1;
    }

    void Construct()
    {
        deque<int> deq;
        for (int i = 0; i < CHILD_NUM; ++i)
            if (trie[0][i])
            {
                fail[trie[0][i]] = 0;
                deq.push_back(trie[0][i]);
            }

        while (!deq.empty())
        {
            int u = deq.front();
            deq.pop_front();

            for (int i = 0; i < CHILD_NUM; ++i)
            {
                int& v = trie[u][i];
                if (v)
                {
                    fail[v] = trie[fail[u]][i];
                    deq.push_back(v);
                    value[v] |= value[fail[v]];
                }
                else
                    v = trie[fail[u]][i];
            }
        }
    }

    CMatrix Work()
    {
        CMatrix mat;
        mat.SetSize(size);

        for (int u = 0; u < size; ++u)
        {
            if (value[u])
                continue;
            for (int i = 0; i < CHILD_NUM; ++i)
            {
                int v = trie[u][i];
                if (value[v])
                    continue;
                mat.elem[u][v] += 1;
            }
        }
        return mat;
    }
};

CAutomaton AC;

int main()
{
    int m, n;
    char word[20];
    scanf("%d %d", &m, &n);

    AC.Initilize();
    AC.Reset();
    
    for (int i = 0; i < m; ++i)
    {
        scanf("%s", word);
        AC.Insert(word);
    }
    AC.Construct();

    CMatrix mat = AC.Work();
    mat.Power(n);

    long long int sum = 0;
    for (int i = 0; i < mat.size; ++i)
        sum += mat.elem[0][i];

    printf("%lld\n", sum % MOD);
    return 0;
}