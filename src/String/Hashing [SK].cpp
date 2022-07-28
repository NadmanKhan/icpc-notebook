int powhash1[ 1000000+ 10]= {};
int powhash2[ 1000000+ 10]= {};
int f_prefhash1[1000000 + 10];
int f_prefhash2[1000000 + 10];
int r_prefhash1[1000000 + 10];
int r_prefhash2[1000000 + 10];

int add(ll x,ll y,ll mod)
{
    return (x+y>=mod)?(x+y-mod):(x+y);
}
int subtract(ll x,ll y,ll mod)
{
    return (x-y<0)?(x-y+mod):(x-y);
}

int multp(ll x,ll y,ll mod)
{
    return (x*y)%mod;
}


const int BASE1 = 125;
const int MOD1 = 1e9 + 9;

const int BASE2 = 250;
const int MOD2 = 1e9 + 7;

void f_prefhashcalc(string& s,int base,int mod,int*prefhash)
{
    ll sum = 0;
    int ns = s.size();

    for(int i=0; i<ns; i++)
    {

        sum = add(((ll)sum*base)%mod,s[i],mod);
        prefhash[i]=sum;
    }
}
void r_prefhashcalc(string& s,ll base,ll mod,int*prefhash)
{
    ll sum = 0;
    int ns = s.size();
    prefhash[ns]=0;

    for(int i=ns-1; i>=0; i--)
    {

        sum = add((sum*base)%mod,s[i],mod);
        prefhash[i]=sum;
    }
}



int f_strhash(string& s,int base,int mod)
{
    ll sum = 0;
    int ns = s.size();

    for(int i=0; i<ns; i++)
    {
        sum = add(((ll)sum*base)%mod,s[i],mod);
    }
    return sum;

}
int r_strhash(string& s,ll base,ll mod)
{
    ll sum = 0;
    int ns = s.size();

    for(int i=ns-1; i>=0; i--)
    {
        sum = add((sum*base)%mod,s[i],mod);
    }
    return sum;

}


void powhashfill(int base,int mod,int*powhash)
{
    for(int i=0; i<1000000 + 10; i++)
    {
        if(i==0)
        {
            powhash[0]=1;
            continue;
        }

        powhash[i] = multp(powhash[i-1],base,mod);
    }

}

int f_substrhash(int l,int r,ll mod,int*prefhash,int*powhash)
{

    ll x = subtract(  prefhash[r],  multp(prefhash[l-1],powhash[r-l+1],mod),  mod  );

    return x;
}
int r_substrhash(int l,int r,ll mod,int*prefhash,int*powhash)
{

    ll x = subtract(  prefhash[l],  multp(prefhash[r+1],powhash[r-l+1],mod),  mod  );

    return x;
}
