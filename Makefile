all:
	g++ rsa-encryption.cpp -o rsa

clean:
	rm -f a.out rsa
