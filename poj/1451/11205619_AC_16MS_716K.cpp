#include <iostream>
#include <vector>
using namespace std;

struct node {
    bool isword;
    int prob, index;
    int child[10];
    node(bool _isword, int _prob, int _index) 
        :   isword(_isword), prob(_prob), index(_index)
    { memset(child, 0, sizeof(child)); }
};

vector<node> trie;

int tab[256];
char dict[1010][102];
int prob[1010][102];

void Insert(const char* word, int i, int index, int rt)
{
    if (word[i] == '\0')
    {
        trie[rt].isword = true;
        return ;
    }

    int m = tab[word[i]];
    if (trie[rt].child[m])
    {
        if (trie[trie[rt].child[m]].prob < prob[index][i])
        {
            trie[trie[rt].child[m]].prob = prob[index][i];
            trie[trie[rt].child[m]].index = index;
        }
        else if (trie[trie[rt].child[m]].prob == prob[index][i])
        {
            if (strncmp(dict[index], dict[trie[trie[rt].child[m]].index], i + 1) < 0)
                trie[trie[rt].child[m]].index = index;
        }

        Insert(word, i + 1, index, trie[rt].child[m]);
    }
    else
    {
        trie.push_back(node(false, 0, 0));
        trie[rt].child[m] = trie.size() - 1;
        trie[trie[rt].child[m]].index = index;
        trie[trie[rt].child[m]].prob = prob[index][i];
        Insert(word, i + 1, index, trie[rt].child[m]);
    }
}

int Query(const char* word, int rt)
{
    if (*word == '\0')
        return trie[rt].index;

    int m = *word - '0';
    if (!trie[rt].child[m])
        return -1;
    else
        return Query(word + 1, trie[rt].child[m]);
}

void Init()
{
    tab['a'] = tab['b'] = tab['c'] = 2;
    tab['d'] = tab['e'] = tab['f'] = 3;
    tab['g'] = tab['h'] = tab['i'] = 4;
    tab['j'] = tab['k'] = tab['l'] = 5;
    tab['m'] = tab['n'] = tab['o'] = 6;
    tab['p'] = tab['q'] = tab['r'] = tab['s'] = 7;
    tab['t'] = tab['u'] = tab['v'] = 8;
    tab['w'] = tab['x'] = tab['y'] = tab['z'] = 9;
}

int main()
{
    int cases;
    Init();
    scanf("%d", &cases);
    for (int c = 1; c <= cases; ++c)
    {
        int n, p;
        scanf("%d", &n);
        printf("Scenario #%d:\n", c);

        trie.clear();
        trie.push_back(node(false, 0, 0));

        memset(prob, 0, sizeof(prob));
        for (int i = 1; i <= n; ++i)
        {
            scanf("%s %d", dict[i], &p);
            int len = strlen(dict[i-1]);
            for (int j = 0; dict[i][j] != '\0'; ++j)
            {
                prob[i][j] = p;
                if (j < len && !strncmp(dict[i], dict[i-1], j + 1))
                    prob[i][j] += prob[i-1][j];
            }
            Insert(dict[i], 0, i, 0);
        }

        char word[110], is[110], os[110];
        scanf("%d", &n);
        while (n--)
        {
            scanf("%s", is);
            //if (is[0] == '1')
            //{
            //    printf("\n\n");
            //    continue;
            //}
            for (int i = 0; is[i] != '1'; ++i)
            {
                word[i] = is[i];
                word[i+1] = '\0';
                int id = Query(word, 0);
                if (id != -1)
                {
                    int j = 0;
                    for (j = 0; j <= i; ++j)
                        os[j] = dict[id][j];
                    os[j] = '\0';
                    printf("%s\n", os);
                }
                else 
                    printf("MANUALLY\n");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}