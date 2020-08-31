#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class IInchiriabil//Interfata
{
public:
	virtual float getPretChirie() = 0;
};

class Imobil : public IInchiriabil
{
protected:
	int nrCamere;
	float* suprafete;
	string adresa;
public:
	~Imobil()
	{
		if (this->suprafete != NULL)
			delete[] this->suprafete;
	}

	Imobil()
	{
		this->nrCamere = 0;
		this->suprafete = NULL;
		this->adresa = "Necunoscuta";
	}

	Imobil(int nrCamere, float* suprafete, string adresa)
	{
		this->nrCamere = nrCamere;
		this->suprafete = new float[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++)
			this->suprafete[i] = suprafete[i];
		this->adresa = adresa;
	}

	Imobil(const Imobil& im)
	{
		this->nrCamere = im.nrCamere;
		this->suprafete = new float[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++)
			this->suprafete[i] = im.suprafete[i];
		this->adresa = im.adresa;
	}

	Imobil operator=(const Imobil& im)
	{
		if (this->suprafete != NULL)
			delete[] this->suprafete;
		this->nrCamere = im.nrCamere;
		this->suprafete = new float[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++)
			this->suprafete[i] = im.suprafete[i];
		this->adresa = im.adresa;
		return *this;
	}

	friend ostream& operator<<(ostream& out, Imobil& im)
	{
		out << "\nNumar camere: " << im.nrCamere;
		out << "\nSuprafete camere: ";
		for (int i = 0; i < im.nrCamere; i++)
		{
			out << im.suprafete[i] << " ";
		}
		out << "\nAdresa: " << im.adresa;
		return out;
	}

	friend istream& operator >> (istream& in, Imobil& im)
	{
		cout << endl;
		char buffer[100];
		im.adresa = new char[strlen(buffer) + 1];
		cout << "\nAdresa: ";
		in.getline(buffer, 100);
		cout << "\nNumar camere: ";
		in >> im.nrCamere;
		if (im.suprafete != NULL)
			delete[] im.suprafete;
		im.suprafete = new float[im.nrCamere];
		cout << "\nSuprafata fiecarei camere: " << endl;
		for (int i = 0; i < im.nrCamere; i++)
			in >> im.suprafete[i];
		return in;
	}

	friend ifstream& operator >> (ifstream& in, Imobil& im)
	{
		cout << endl;
		char buffer[100];
		im.adresa = new char[strlen(buffer) + 1];
		cout << "\nAdresa: ";
		in.getline(buffer, 100);
		cout << "\nNumar camere: ";
		in >> im.nrCamere;
		if (im.suprafete != NULL)
			delete[] im.suprafete;
		im.suprafete = new float[im.nrCamere];
		cout << "\nSuprafata fiecarei camere: " << endl;
		for (int i = 0; i < im.nrCamere; i++)
			in >> im.suprafete[i];
		return in;
	}


	virtual float getPretChirie()
	{
		return this->nrCamere * 235;
	}

	void addToFile(fstream& file)
	{
		if (file.is_open())
		{
			//scriere nr camere apartament
			file.write((char*)&this->nrCamere, sizeof(int));

			//scriere suprafete apartament
			int dimensiune0 = this->nrCamere;
			file.write((char*)&dimensiune0, sizeof(int));
			file.write((char*)this->suprafete, dimensiune0);

			//scrire adresa apartament
			//scriere dimensiune string
			int dimensiune = this->adresa.length() + 1;
			file.write((char*)&dimensiune, sizeof(int));
			//scriere string in fisier
			file.write(this->adresa.data(), dimensiune);
		}
		else
			cout << "\nEroare";
	}

	void restoreFromFile(fstream& file)
	{
		if (file.is_open()) {
			int nrCamere;
			float* suprafete;
			string adresa;
			file.read((char*)&nrCamere, sizeof(int));
			int lungimeSir0 = nrCamere;
			file.read((char*)&suprafete, lungimeSir0);
			int lungimeSir;
			file.read((char*)&lungimeSir, sizeof(int));
			char buffer[100];
			file.read(buffer, lungimeSir);
			this->adresa = buffer;
		}
		else
			cout << "\nEroare la citire!";
	}
};

class Apartament : public Imobil
{
private:
	int etaj;
public:
	~Apartament()
	{

	}

	Apartament() :Imobil()
	{
		this->etaj = 0;
	}

	Apartament(int nrCamere, float* suprafete, string adresa, int etaj) :Imobil(nrCamere, suprafete, adresa)
	{
		this->etaj = etaj;
	}

	Apartament(Imobil im, int etaj) :Imobil(im)
	{
		this->etaj = etaj;
	}

	Apartament(const Apartament& a) :Imobil(a)
	{
		this->etaj = a.etaj;
	}

	Apartament operator=(const Apartament& a)
	{
		Imobil::operator=(a);
		this->etaj = a.etaj;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Apartament& a)
	{
		out << (Imobil)a;
		out << "\nEtajul: " << a.etaj;
		return out;
	}

	friend istream& operator >> (istream& in, Apartament& a)
	{
		in >> (Imobil)a;
		cout << "Etajul: ";
		in >> a.etaj;
		return in;
	}

	friend ifstream& operator >> (ifstream& in, Apartament& a)
	{
		in >> (Imobil)a;
		cout << "Etajul: ";
		in >> a.etaj;
		return in;
	}

	void addToFile(fstream& file)
	{
		if (file.is_open())
		{
			//cod apartament
			char cod = 'A';
			file.write(&cod, sizeof(char));

			//scriere nr camere apartament
			file.write((char*)&this->nrCamere, sizeof(int));

			//scriere suprafete apartament
			int dimensiune0 = this->nrCamere;
			file.write((char*)&dimensiune0, sizeof(int));
			file.write((char*)this->suprafete, dimensiune0);

			//scrire adresa apartament
			//scriere dimensiune string
			int dimensiune = this->adresa.length() + 1;
			file.write((char*)&dimensiune, sizeof(int));
			//scriere string in fisier
			file.write(this->adresa.data(), dimensiune);

			//scriere etaj apartament
			file.write((char*)&this->etaj, sizeof(int));
		}
		else
			cout << "\nEroare";
	}

	void restoreFromFile(fstream& file)
	{
		if (file.is_open()) {
			int nrCamere;
			float* suprafete;
			string adresa;
			int etaj;
			file.read((char*)&nrCamere, sizeof(int));
			int lungimeSir0 = nrCamere;
			file.read((char*)&suprafete, lungimeSir0);
			int lungimeSir;
			file.read((char*)&lungimeSir, sizeof(int));
			char buffer[100];
			file.read(buffer, lungimeSir);
			this->adresa = buffer;
			file.read((char*)&etaj, sizeof(int));
		}
		else
			cout << "\nEroare la citire!";
	}

};

class Casa : public Imobil
{
private:
	bool garaj;
public:
	~Casa()
	{

	}

	Casa() :Imobil()
	{
		this->garaj = false;
	}

	Casa(int nrCamere, float* suprafete, string adresa, bool garaj) :Imobil(nrCamere, suprafete, adresa)
	{
		this->garaj = garaj;
	}

	Casa(Imobil im, bool garaj) :Imobil(im)
	{
		this->garaj = garaj;
	}

	Casa(const Casa& c) :Imobil(c)
	{
		this->garaj = c.garaj;
	}

	Casa operator=(const Casa& c)
	{
		Imobil::operator=(c);
		this->garaj = c.garaj;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Casa& c)
	{
		out << (Imobil)c;
		out << "\nDispune de garaj? - ";
		if (c.garaj == true)
			out << "Da";
		else
			out << "Nu";
		return out;
	}

	friend istream& operator >> (istream& in, Casa& c)
	{
		in >> (Imobil)c;
		cout << "Casa are garaj? - ";
		in >> c.garaj;
		return in;
	}

	friend ifstream& operator >> (ifstream& in, Casa& c)
	{
		in >> (Imobil)c;
		cout << "Casa are garaj? - ";
		in >> c.garaj;
		return in;
	}

	float getPretChirie()
	{
		if (this->garaj == true)
			return (nrCamere * 235) + 150;
		else
			return nrCamere * 235;
	}

	void addToFile(fstream& file)
	{
		if (file.is_open())
		{
			//cod casa
			char cod = 'C';
			file.write(&cod, sizeof(char));

			//scriere nr camere casa
			file.write((char*)&this->nrCamere, sizeof(int));

			//scriere suprafete casa
			int dimensiune0 = this->nrCamere;
			file.write((char*)&dimensiune0, sizeof(int));
			file.write((char*)this->suprafete, dimensiune0);

			//scrire adresa casa
			//scriere dimensiune string
			int dimensiune = this->adresa.length() + 1;
			file.write((char*)&dimensiune, sizeof(int));
			//scriere string in fisier
			file.write(this->adresa.data(), dimensiune);

			//scriere garaj
			file.write((char*)&this->garaj, sizeof(bool));
		}
		else
			cout << "\nEroare";
	}

	void restoreFromFile(fstream& file)
	{
		if (file.is_open()) {
			int nrCamere;
			float* suprafete;
			string adresa;
			bool garaj;
			file.read((char*)&nrCamere, sizeof(int));
			int lungimeSir0 = nrCamere;
			file.read((char*)&suprafete, lungimeSir0);
			int lungimeSir;
			file.read((char*)&lungimeSir, sizeof(int));
			char buffer[100];
			file.read(buffer, lungimeSir);
			this->adresa = buffer;
			file.read((char*)&garaj, sizeof(bool));
		}
		else
			cout << "\nEroare la citire!";
	}


};

class Cartier
{
private:
	string numeCartier;
	int nrImobile;
	Imobil** imobile;
public:
	~Cartier()
	{
		if (this->imobile != NULL)
		{
			for (int i = 0; i < this->nrImobile; i++)
				delete this->imobile[i];
			delete[] this->imobile;
		}
	}

	Cartier()
	{
		this->numeCartier = "Necunoscut";
		this->nrImobile = 0;
		this->imobile = NULL;
	}

	Cartier(string numeCartier, int nrImobile, Imobil** imobile)
	{
		this->numeCartier = numeCartier;
		this->nrImobile = nrImobile;
		if (imobile != NULL)
		{
			this->imobile = new Imobil*[this->nrImobile];
			for (int i = 0; i < this->nrImobile; i++)
			{
				this->imobile[i] = new Imobil(*imobile[i]);
			}
		}
		else
			this->imobile = NULL;
	}

	Cartier(string numeCartier, int nrImobile, Imobil* imobile)
	{
		this->numeCartier = numeCartier;
		this->nrImobile = nrImobile;
		if (imobile != NULL)
		{
			this->imobile = new Imobil*[this->nrImobile];
			for (int i = 0; i < this->nrImobile; i++)
			{
				this->imobile[i] = new Imobil(imobile[i]);
			}
		}
		else
			this->imobile = NULL;
	}

	Cartier(const Cartier& ci)
	{
		this->numeCartier = ci.numeCartier;
		this->nrImobile = ci.nrImobile;
		if (ci.imobile != NULL)
		{
			this->imobile = new Imobil*[this->nrImobile];
			for (int i = 0; i < this->nrImobile; i++)
			{
				this->imobile[i] = new Imobil(*ci.imobile[i]);
			}
		}
		else
			this->imobile = NULL;
	}

	Cartier operator=(const Cartier& ci)
	{
		if (this->imobile != NULL)
		{
			for (int i = 0; i < this->nrImobile; i++)
				delete this->imobile[i];
			delete[] this->imobile;
		}
		this->numeCartier = ci.numeCartier;
		this->nrImobile = ci.nrImobile;
		if (ci.imobile != NULL)
		{
			this->imobile = new Imobil*[this->nrImobile];
			for (int i = 0; i < this->nrImobile; i++)
			{
				this->imobile[i] = new Imobil(*ci.imobile[i]);
			}
		}
		else
			this->imobile = NULL;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cartier& ci)
	{
		out << "\nCartier: " << ci.numeCartier;
		out << "\nNumar imobile: " << ci.nrImobile;
		out << "\nImobilele sunt: ";
		if (ci.imobile != NULL)
		{
			for (int i = 0; i < ci.nrImobile; i++)
				out << *ci.imobile[i] << " ";
		}
		return out;
	}

	Cartier(fstream& f)
	{
		if (f.is_open())
		{
			f.read((char*)&this->nrImobile, sizeof(int));
			for (int i = 0; i < this->nrImobile; i++)
			{
				char tip; //A sau C
				f.read(&tip, sizeof(char));
				if (tip == 'A')
					this->imobile[i] = new Apartament;
				else
					this->imobile[i] = new Casa;
				this->imobile[i]->restoreFromFile(f);
			}
		}
	}
};

void main()
{
	int lungime = 3;
	float suprafete[] = { 13.5, 15.7, 20 };
	Apartament a = Apartament(lungime, suprafete, "Strada Zorilor, nr. 33", 2);
	int lungime1 = 2;
	float suprafete1[] = { 20.5,18 };
	Apartament a1 = Apartament(lungime1, suprafete1, "Strada Arthur, nr. 21", 4);
	int lungime2 = 2;
	float suprafete2[] = { 20, 15.5 };
	Apartament a2 = Apartament(lungime2, suprafete2, "Strada Lalelelor, nr. 4", 1);

	int lungime3 = 2;
	float suprafete3[] = { 22.5,18 };
	Casa c = Casa(lungime3, suprafete3, "Strada Tineretii, nr. 1", 1);
	int lungime4 = 4;
	float suprafete4[] = { 12.5,15.8,20.5,15.5 };
	Casa c1 = Casa(lungime4, suprafete4, "Strada Vartej, nr. 107", 0);

	cout << a << endl << a1 << endl << c << endl << c1;
	cout << endl;
	cout << (Imobil)a2;
	cout << endl;

	Imobil* imobile0 = new Imobil[3];
	imobile0[0] = a;
	imobile0[1] = a1;
	imobile0[2] = c;
	cout << endl;
	cout << imobile0[0];
	Cartier ci0 = Cartier("Bravu", 3, imobile0);

	Imobil** imobile = new Imobil*[3];
	imobile[0] = &a;
	imobile[1] = &a1;
	imobile[2] = &c;
	cout << endl;
	Cartier ci = Cartier("Sudului", 3, imobile);
	cout << ci;

	//FISIERE TEXT
	ofstream fOut("date.txt");
	fOut << ci;
	ifstream fIn("date.txt");
	//fIn >> a;

	//FISIERE BINARE
	fstream fAp0("apartament0.bin", ios::out | ios::binary);
	fstream fAp("apartament0.bin", ios::in | ios::binary);
	a.addToFile(fAp0);
	c.restoreFromFile(fAp);
}