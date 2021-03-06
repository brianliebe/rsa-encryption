#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

typedef struct rsa_key {
	int key;
	int n;
} rsa_key;

int rsa_greatest_common_divisor(int a, int b) {
	while (true) {
		if (a == 0) return b;
		b %= a;
		if (b == 0) return a;
		a %= b;
	}
	return 0;
}

int rsa_least_common_multiple(int a, int b) {
	int gcd = rsa_greatest_common_divisor(a, b);
	return gcd ? (a / gcd * b) : 0;
}

int rsa_find_ekey(int t) {
	srand(time(NULL));
	std::vector<int> possible_keys;
	for (int e = 2; e < t; e++) {
		if (rsa_greatest_common_divisor(e, t) == 1) {
			possible_keys.push_back(e);
		}
	}
	std::random_shuffle(possible_keys.begin(), possible_keys.end());
	return possible_keys.size() ? possible_keys[0] : 0;
}

int rsa_find_dkey(int e_key, int t) {
	int d_key = 2;
	while (true) {
		if (fmod(d_key * e_key, t) == 1) return d_key;
		else d_key++;
	}
}

std::vector<int> rsa_encrypt(rsa_key key, std::string message) {
	std::vector<int> encrypted;
	for (int i = 0; i < message.length(); i++) {
		double val = fmod(pow(message[i], key.key), key.n);
		std::cout << "Enc: " << val << std::endl;
		encrypted.push_back((int)val);
	}
	return encrypted;
}

std::string rsa_decrypt(rsa_key key, std::vector<int> encrypted) {
	std::string message;
	for (unsigned int i = 0; i < encrypted.size(); i++) {
		std::cout << pow(encrypted[i], key.key) << std::endl;
		double val = fmod(pow(encrypted[i], key.key), key.n);
		std::cout << "Dec: " << val << std::endl;
		message += val;
	}
	return message;
}

int main (int argc, char **argv) {
	int prime_p = 3;
	int prime_q = 7;

	int n = prime_p *prime_q;
	int totient = rsa_least_common_multiple(prime_p - 1, prime_q - 1);
	std::cout << "Totient: " << totient << std::endl;
	int e_key = rsa_find_ekey((prime_p-1) * (prime_q-1));
	std::cout << "E_key: " << e_key << std::endl;
	int d_key = rsa_find_dkey(e_key, totient);
	std::cout << "D_key: " << d_key << std::endl;

	rsa_key public_key;
	rsa_key private_key;

	public_key.key = e_key;
	public_key.n = n;
	private_key.key = d_key;
	private_key.n = n;

	char ch = 't';
	std::cout << (int)ch << std::endl;

	std::vector<int> encrypted = rsa_encrypt(public_key, "t");
	std::string decrypted = rsa_decrypt(private_key, encrypted);
	std::cout << decrypted << std::endl;
}