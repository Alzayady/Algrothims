// BY Bakry

int Add(int x , int y)
{
	int z = x + y ;
	if(z >= mod)
		z -= mod ;
	return z ;
}
 
int Sub(int x , int y)
{
	int z = x - y ;
	if(z < 0)
		z += mod ;
	return z ;
}
 
int Mul(int x , int y)
{
	return (x * 1ll * y) % mod ;
}
 
int powlog(int base , int power)
{
	if(power == 0)
		return 1 ;
	int x = powlog(base , power / 2) ;
	x = Mul(x , x) ;
	if(power & 1)
		x = Mul(x , base) ;
	return x ;
}
 
int modinv(int x)
{
	return powlog(x , mod-2) ;
}
 
int Div(int x , int y)
{
	return Mul(x , modinv(y)) ;
}
 
struct combination
{
    vector<int>fact , inv ;
    combination(int sz) : fact(sz + 1) , inv(sz + 1)
    {
        fact[0] = 1 ;
        inv[0] = 1 ;
        for(int i = 1 ; i <= sz ; ++i)
            fact[i] = Mul(fact[i-1] , i) ;
        inv[sz] = modinv(fact[sz]) ;
		for(int i = sz-1 ; i >= 1 ; --i)
		    inv[i] = Mul(inv[i+1] , i+1) ;
    }
    int choose(int n , int k) const
    {
        if(k < 0 || n < k)
            return 0 ;
        return Mul(Mul(fact[n] , inv[k]) , inv[n - k]) ;
    }
};
