int getintfc (char** z)
{
    int retwert=0;
    for (; (**z!=' ') && (**z!=0); (*z)++)
    {
        retwert *= 10;
        retwert += ((**z)-'0');
    }
    (*z)++;
    return retwert;
}

int getintfcl (char* z)
{
    int retwert=0;
    for (; (*z!=' ') && (*z!=0); z++)
    {
        retwert *= 10;
        retwert += ((*z)-'0');
    }
    //*z++;
    return retwert;
}
