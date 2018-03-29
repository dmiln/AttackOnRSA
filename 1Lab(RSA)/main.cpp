#include <iostream>
#include <fstream>
#include <Windows.h>
#include "big.h"
#include "flash.h"
#include "BigArray.h"
extern "C"
{
	#include "miracl.h"
}

Miracl precision(500, 10);

Big euler(Big *Nprimes, Big &N, int count);
Big inv(Big&, Big&);
Big evkl(Big &e, Big &euler);
Big eulerTheorem(Big &e, Big &euler, Big &euler1);
int stringNumber(char *);
void readFile(Big* array, int count, char* path);

int main()
{
	Big e, N, Neuler,Euler;
	int NprimesNumber =stringNumber("factor.txt"),eulerCounter=  stringNumber("eulerFactor.txt");

	Big*Nprimes = new Big[NprimesNumber], *EuPrimes = new Big[eulerCounter];
	readFile(Nprimes, NprimesNumber,"factor.txt");

	ifstream fCipher("Cipher.txt");

	fCipher >> N;
	fCipher >> e;

	cout << "N = " << N << endl;
	cout << "e = " << e << endl;

	cout << "N Multipliers:" << endl;
	for (int i = 0; i < NprimesNumber; i++)
		cout << "Nprimes[" << i << "] = " << *(Nprimes + i) << endl;

	fCipher.close();

	Neuler = euler(Nprimes, N, NprimesNumber);

	readFile(EuPrimes, eulerCounter, "eulerFactor.txt");
	Euler= euler(EuPrimes, Neuler, eulerCounter);

	inv(e, Neuler);

	evkl(e, Neuler);
	
	eulerTheorem(e, Euler, Neuler);

	delete[]Nprimes; 
	delete[]EuPrimes;
	getchar();
	return 0;
}

Big euler(Big *Nprimes, Big &N, int count)
{
	ofstream fout;
	printf("\n");
	printf("-----------------------");
	printf("\n");

	Big  current = *(Nprimes), answer = 1;
	Flash e(N, 1);
	for (int j = 1; j < count; j++)
	{
		if (current != *(Nprimes + j))
		{
			Flash x(1, current);
			x = 1 - x;
			e *= x;
			current = *(Nprimes + j);
			if (j == count - 1)
			{
				Flash x(1, current);
				x = 1 - x;
				e *= x;
				//x.~Flash();
			}
			//x.~Flash();
		}

	}

	answer = e.num();
	fout.open("euler.txt", ios_base::out);
	cout << "Euler = " << answer << endl;
	fout << answer;
	//e.~Flash();
	return answer;
}

void readFile(Big* array,int count,char* path)
{
	ifstream f(path);
	for(int i=0;i<count;i++)
	{
		f >> *(array+i);
	}
	f.close();

}

int stringNumber(char* path) 
{
	int count = 0;
	ifstream f(path);
	Big x = 1;
	while (!f.eof())
	{
		count++;
		f >> x;
	}
	f.close();
	return count-1;
}

Big inv(Big& e, Big& euler)
{
	cout << "--------------------INVERSION--------------------" << endl;
	Big d;
	ofstream fout;
	d = inverse(e, euler);
	fout.open("inverse.txt", ios_base::out);
	fout << d;
	fout.close();
	cout << "d=" << d << endl;
	return d;
}

Big evkl(Big &e, Big &euler)
{
	cout << "--------------------EVKLID--------------------" << endl;
	Big D;
	big d=mirvar(1);
	ofstream fout;
	xgcd(e.getbig(), euler.getbig(), d, d, d);
	D = d;
	fout.open("evkl.txt", ios_base::out);
	fout << D;
	fout.close();
	cout << "d=" << D << endl;
	mirkill(d);
	return D;
}

Big eulerTheorem(Big &e, Big &euler, Big &euler1)
{
	cout << "--------------------EULER THEOREM--------------------" << endl;
	Big d,E;
	ofstream fout;
	d=pow(e, euler-1, euler1);  // x^m mod n
	fout.open("eulerTheor.txt", ios_base::out);
	fout << d;
	fout.close();
	cout << "d=" << d << endl;
	return d;
}