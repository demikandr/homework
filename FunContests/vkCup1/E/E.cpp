#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

typedef long long li;
typedef unsigned long long uli;
typedef long double ld;

const int INF = 1e9;
const li lINF = 1e18;
const int P = 1e9 + 7, Q = 1e9 + 9;
const int base = 41;
const double PI = 3.141592653589793238;
const double eps = 1e-7;

#ifdef DEBUG
#define dout(x) cerr << x
#else
#define dout(x)
#endif // DEBUG

map< string, string > ids;
map< string, string > inv;
string prog1, prog2;
enum type {symb, wspace, str, comment, comment_end, ident};

inline bool is_letter (char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

inline bool is_digit (char c)
{
    return '0' <= c && c <= '9';
}

int main()
{
#ifdef DEBUG
    freopen ("test.in", "r", stdin);
#endif // DEBUG

    string s;
    cin >> s;
    while (s != "#")
    {
//        cout << s << endl;
        ids[s] = s;
        inv[s] = s;
        cin >> s;
    }

    type cur = wspace;
    prog1.pb (' ');
    char c = getchar ();
    while (c != '#')
    {
//        cout << c;
        if (cur == comment)
        {
            if (c == '*')
            {
                cur = comment_end;
            }
        }
        else if (cur == comment_end)
        {
            if (c == '/')
            {
                cur = wspace;
                if (prog1.back () != ' ')
                    prog1.pb (' ');
            }
            else
            {
                cur = comment;
            }
        }
        else if (cur == str)
        {
            if (c == '"')
            {
                if (prog1.back () == '\\')
                    prog1.pop_back ();
                else
                {
                    prog1.pb ('"');
                    cur = symb;
                }
            }
            else
            {
                if (prog1.back () == '\\')
                    prog1.pop_back ();
                if (c == '\\')
                    prog1.pb ('\\');
            }
        }
        else if (cur == wspace)
        {
            if (c <= 32);
            else
            {
                if (c == '"')
                {
                    prog1.pop_back ();
                    prog1.pb ('"');
                    cur = str;
                    cur = str;
                }
                else if (is_letter (c))
                {
                    prog1.pb (c);
                    cur = ident;
                }
                else
                {
                    prog1.pop_back ();
                    prog1.pb (c);
                    cur = symb;
                }
            }
        }
        else if (cur == symb)
        {
            if (c == '*' && prog1.back () == '/')
            {
                prog1.pop_back ();
                cur = comment;
            }
            else
            {
                if (is_letter (c))
                    prog1.pb (' ');
                prog1.pb (max (c, ' '));
                if (is_letter (c))
                {
                    cur = ident;
                }
                else if (c == '"')
                {
                    cur = str;
                }
                else if (c <= 32)
                {
                    cur = wspace;
                }
            }
        }
        else if (cur == ident)
        {
            prog1.pb (max (c, ' '));
            if (is_letter (c) || is_digit (c));
            else if (c <= 32)
            {
                cur = wspace;
            }
            else if (c == '"')
            {
                cur = str;
            }
            else
            {
                cur = symb;
            }
        }
        c = getchar ();
    }
    prog1.pb (' ');
    dout (prog1 << endl << endl);

    cur = wspace;
    prog2.pb (' ');
    c = getchar ();
    while (c != EOF)
    {
//        cout << c;
        if (cur == comment)
        {
            if (c == '*')
            {
                cur = comment_end;
            }
        }
        else if (cur == comment_end)
        {
            if (c == '/')
            {
                cur = wspace;
                if (prog2.back () != ' ')
                    prog2.pb (' ');
            }
            else
            {
                cur = comment;
            }
        }
        else if (cur == str)
        {
            if (c == '"')
            {
                if (prog2.back () == '\\')
                    prog2.pop_back ();
                else
                {
                    prog2.pb ('"');
                    cur = symb;
                }
            }
            else
            {
                if (prog2.back () == '\\')
                    prog2.pop_back ();
                if (c == '\\')
                    prog2.pb ('\\');
            }
        }
        else if (cur == wspace)
        {
            if (c <= 32);
            else
            {
                if (c == '"')
                {
                    prog2.pop_back ();
                    prog2.pb ('"');
                    cur = str;
                    cur = str;
                }
                else if (is_letter (c))
                {
                    prog2.pb (c);
                    cur = ident;
                }
                else
                {
                    prog2.pop_back ();
                    prog2.pb (c);
                    cur = symb;
                }
            }
        }
        else if (cur == symb)
        {
            if (c == '*' && prog2.back () == '/')
            {
                prog2.pop_back ();
                cur = comment;
            }
            else
            {
                if (is_letter (c))
                    prog2.pb (' ');
                prog2.pb (max (c, ' '));
                if (is_letter (c))
                {
                    cur = ident;
                }
                else if (c == '"')
                {
                    cur = str;
                }
                else if (c <= 32)
                {
                    cur = wspace;
                }
            }
        }
        else if (cur == ident)
        {
            prog2.pb (max (c, ' '));
            if (is_letter (c) || is_digit (c));
            else if (c <= 32)
            {
                cur = wspace;
            }
            else if (c == '"')
            {
                cur = str;
            }
            else
            {
                cur = symb;
            }
        }
        c = getchar ();
    }
    prog2.pb (' ');
    dout (prog2 << endl << endl);

    int i = 0, j = 0;
    string id1 = "", id2 = "";
    while (i < prog1.size () && j < prog2.size ())
    {
        if (is_letter (prog1[i]) != is_letter (prog2[j]))
        {
            cout << "NO\n";
            return 0;
        }
        if (!is_letter (prog1[i]) && prog1[i] != prog2[j])
        {
            cout << "NO\n";
            return 0;
        }
        if (is_letter (prog1[i]))
        {
            while (is_letter (prog1[i]) || is_digit (prog1[i]))
            {
                id1.pb (prog1[i]);
                ++i;
            }
            while (is_letter (prog2[j]) || is_digit (prog2[j]))
            {
                id2.pb (prog2[j]);
                ++j;
            }
            if ((ids.find (id2) != ids.end () && ids[id2] != id1) || (inv.find (id1) != inv.end () && inv[id1] != id2))
            {
                cout << "NO\n";
                return 0;
            }
            else
            {
                if (ids.find (id2) == ids.end ())
                {
                    ids[id2] = id1;
                    inv[id1] = id2;
                }
                dout ("OK " << id1 << ' ' << id2 << endl);
            }
            id1.clear ();
            id2.clear ();
        }
        else
        {
            dout ("OK " << prog1[i] << ' ' << prog2[j] << endl);
            ++i;
            ++j;
        }
    }
    cout << "YES\n";
    return 0;
}
