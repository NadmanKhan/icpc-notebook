pair<int,int>v[4*N];
int arr[N];

void build(int cur,int l,int r)
{
    if(l==r)
    {
        pair<int,int> tmp = {0,0};
        if(arr[l]==0)
        {
            tmp.second++;
        }
        else if(arr[l]<0)
        {
            tmp.first++;
        }
        v[cur] = tmp;
        return;
    }

    int mid = l + (r-l)/2;

    build(cur*2,l,mid);
    build(cur*2 + 1,mid+1,r);

    v[cur].first = v[cur*2].first + v[cur*2 + 1].first;
    v[cur].second = v[cur*2].second + v[cur*2 + 1].second;
    return;
}

pair<int,int>query(int cur,int l,int r,int x,int y)
{
    if(l==x && r==y)
    {
        return v[cur];
    }

    if(x>r || y<l)
    {
        return {-1,-1};
    }
    int mid = l + (r-l)/2;
    pair<int,int> left = query(cur*2,l,mid,x,min(mid,y));
    pair<int,int> right = query(cur*2 + 1,mid+1,r,max(mid+1,x),y);

    pair<int,int> res = {0,0};
    res.first = ((left.first!=-1)?left.first:0) + ((right.first!=-1)?right.first:0);
    res.second = ((left.second!=-1)?left.second:0) + ((right.second!=-1)?right.second:0);

    return res;
}


void update(int cur,int l,int r,int pos,int val)
{
    if(l==r)
    {
        arr[l] = val;
        pair<int,int> tmp = {0,0};
        if(arr[l]==0)
        {
            tmp.second++;
        }
        else if(arr[l]<0)
        {
            tmp.first++;
        }
        v[cur] = tmp;
        return;
    }

    int mid = l + (r-l)/2;

    if(pos<=mid)
    {
        update(cur*2,l,mid,pos,val);
    }
    else
    {
        update(cur*2 + 1,mid+1,r,pos,val);
    }


    v[cur].first = v[cur*2].first + v[cur*2 + 1].first;
    v[cur].second = v[cur*2].second + v[cur*2 + 1].second;
    return;
}

