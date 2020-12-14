void InsertSearch(int r[],int n,int key)
{
    low =1;
    high=n;

    while(low<=high)
    {
        mid=(high-low)*key/a[high]-a[low];

        if(k>r[mid])
            low=mid+1;
        else if(k<r[mid])
            high=mid-1;
        else
            return mid;
    }
    return 0;
}
