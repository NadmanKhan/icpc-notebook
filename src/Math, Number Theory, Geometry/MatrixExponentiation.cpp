struct Matrix : vector<vector<ll>>
{
	Matrix(size_t n) : std::vector<std::vector<ll>>(n, std::vector<ll>(n, 0)) {}
	Matrix(std::vector<std::vector<ll>> &v) : std::vector<std::vector<ll>>(v) {}

	Matrix operator*(const Matrix &other)
	{
		size_t n = size();
		Matrix product(n);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				for (size_t k = 0; k < n; k++)
				{
					product[i][k] += (*this)[i][j] * other[j][k];
					product[i][k] %= MOD;
				}
			}
		}
		return product;
	}
};
Matrix big_mod(Matrix a, long long n)
{
	Matrix res = Matrix(a.size());
	for (int i = 0; i < (int)(a.size()); i++)
		res[i][i] = 1;
	if (n <= 0) return res;
	while (n)
	{
		if (n % 2)
		{
			res = res * a;
		}
		n /= 2;
		a = a * a;
	}
	return res;
}