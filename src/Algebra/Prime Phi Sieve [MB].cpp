#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct PrimePhiSieve
{
private:
	ll n;
	vector<ll> primes, phi;
	vector<bool> is_prime;

public:
	PrimePhiSieve() {}
	
	PrimePhiSieve(ll n)
	{
		this->n = n, is_prime.resize(n + 5, true), phi.resize(n + 5, 1);
		phi_sieve();
	}
	void phi_sieve()
	{
		is_prime[0] = is_prime[1] = false;

		for (ll i = 1; i <= n; i++)
			phi[i] = i;

		for (ll i = 1; i <= n; i++)
			if (is_prime[i])
			{
				primes.push_back(i);
				phi[i] *= (i - 1), phi[i] /= i;

				for (ll j = i + i; j <= n; j += i)
					is_prime[j] = false, phi[j] /= i, phi[j] *= (i - 1);
			}
	}

	ll get_divisors_count(int number, int divisor)
	{
		return phi[number / divisor];
	}

	vector<pll> factorize(ll num)
	{
		vector<pll> a;
		for (int i = 0; i < (int)primes.size() && primes[i] * 1LL * primes[i] <= num; i++)
			if (num % primes[i] == 0)
			{
				int cnt = 0;
				while (num % primes[i] == 0)
					cnt++, num /= primes[i];
				a.push_back({primes[i], cnt});
			}

		if (num != 1)
			a.push_back({num, 1});
		return a;
	}

	ll get_phi(int n)
	{
		return phi[n];
	}
	// (n/p) * (p-1) => n- (n/p);
	void segmented_phi_sieve(ll l, ll r)
	{
		vector<ll> current_phi(r - l + 1);
		vector<ll> left_over_prime(r - l + 1);

		for (ll i = l; i <= r; i++)
			current_phi[i - l] = i, left_over_prime[i - l] = i;

		for (ll p : primes)
		{
			ll to = ((l + p - 1) / p) * p;

			if (to == p)
				to += p;

			for (ll i = to; i <= r; i += p)
			{
				while (left_over_prime[i - l] % p == 0)
					left_over_prime[i - l] /= p;
				current_phi[i - l] -= current_phi[i - l] / p;
			}
		}

		for (ll i = l; i <= r; i++)
		{
			if (left_over_prime[i - l] > 1)
				current_phi[i - l] -= current_phi[i - l] / left_over_prime[i - l];
			cout << current_phi[i - l] << endl;
		}
	}

	ll phi_sqrt(ll n)
	{
		ll res = n;

		for (ll i = 1; i * i <= n; i++)
		{
			if (n % i == 0)
			{
				res /= i;
				res *= (i - 1);

				while (n % i == 0)
					n /= i;
			}
		}

		if (n > 1)
			res /= n, res *= (n - 1);
		return res;
	}
};