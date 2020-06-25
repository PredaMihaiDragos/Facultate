/* Preda Mihai-Dragos 135
MSBuild Visual Studio (c++17)
Marian Lupascu
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <functional>

using namespace std;

//clasa pentru a afisa ceva (in fisier, consola...)
template<typename OutType = ostream>
class Logger
{
public:
	Logger(OutType *to);
	Logger(const Logger& oth) = delete;
	Logger& operator=(const Logger& oth) = delete;
	virtual ~Logger(); //destructor virtual pentru a putea mosteni din ea
protected:
	OutType* out;
	void Log(const string& toLog);
	void Log(int x);
};

//clasa pentru a afisa un string intr-un fisier
class FileLogger :
	public Logger<ofstream>
{
public:
	FileLogger(const string& fileName);
	virtual ~FileLogger();  //destructor virtual pentru a putea mosteni din ea
};

//clasa pentru a afisa ceva in consola
class ConsoleLogger :
	public Logger<ostream>
{
public:
	ConsoleLogger();
	virtual ~ConsoleLogger(); //destructor virtual pentru a putea mosteni din ea
	friend ConsoleLogger& operator<< (ConsoleLogger& logger, const std::string& str);
	friend ConsoleLogger& operator<< (ConsoleLogger& logger, int x);
};

//clasa pentru a afisa un string intr-un fisier
class StringLogger :
	public virtual FileLogger
{
public:
	StringLogger();
	virtual ~StringLogger(); //destructor virtual pentru a putea mosteni din ea
	friend StringLogger& operator<< (StringLogger& logger, const std::string& str);
};

//clasa pentru a afisa o exceptie intr-un fisier
class ExceptionLogger :
	public virtual FileLogger
{
public:
	ExceptionLogger();
	virtual ~ExceptionLogger(); //destructor virtual pentru a putea mosteni din ea
	friend ExceptionLogger& operator<< (ExceptionLogger& logger, std::exception& ex);
};

//mostenire diamant: clasa asta poate afisa si stringuri si exceptii
//design pattern: singleton
//clasa final: nu vom mosteni niciodata din ea
class EventLogger final:
	public StringLogger,
	public ExceptionLogger
{
public:
	static EventLogger& GetInstance(); 
	EventLogger(const EventLogger&) = delete;
	EventLogger& operator= (const EventLogger&) = delete;
private:
	EventLogger();
};

//clasa pentru a citi ceva (din fisier, din consola...)
template<typename T, typename InType = istream>
class Reader
{
public:
	Reader(InType* from);
	Reader(const Reader& oth) = delete;
	Reader& operator=(const Reader& oth) = delete;
	virtual ~Reader(); //destructor virtual pentru a putea mosteni din ea
protected:
	InType* in;
	T Read();
};

//clasa pentru a citi ceva din fisier
template<typename T>
class FileReader :
	public Reader<T, ifstream>
{
public:
	FileReader(const string& fileName);
	virtual ~FileReader(); //destructor virtual pentru a putea mosteni din ea
};

//clasa pentru a citi un string din consola (cu restrictii de lungime)
class ConsoleStringReader :
	public Reader<string>
{
public:
	ConsoleStringReader(int lgMin = 0, int lgMax = INT_MAX);
	virtual ~ConsoleStringReader(); //destructor virtual pentru a putea mosteni din ea
	friend ConsoleStringReader& operator>> (ConsoleStringReader& logger, string &str);
private:
	int lgMin, lgMax;
};

//clasa pentru a citi un int din consola (cu restrictii)
class ConsoleIntReader :
	public Reader<int>
{
public:
	ConsoleIntReader(int valMin = INT_MIN, int valMax = INT_MAX);
	virtual ~ConsoleIntReader(); //destructor virtual pentru a putea mosteni din ea
	friend ConsoleIntReader& operator>> (ConsoleIntReader& logger, int& x);
private:
	int valMin, valMax;
};


/* de aici incepe efectiv problema */
class Produs
{
public:
	virtual int GetPret() const = 0;
	virtual ~Produs();
};


class Masca :
	public Produs
{
public:
	Masca();
	Masca(const string& tip);
	virtual ~Masca();
	string GetTip();
protected:
	string tip;
};

class MascaChirurgicala :
	public Masca
{
public:
	MascaChirurgicala();
	MascaChirurgicala(const string& tip, const string& culoare, int nr_pliuri);
	friend ostream& operator<< (ostream& ofs, const MascaChirurgicala& current);
	friend istream& operator>> (istream& ifs, MascaChirurgicala& current);
	virtual ~MascaChirurgicala();
	int GetPret() const override;
	void AddModel(const string& model);
	bool AreModel() const;
private:
	string culoare;
	int nr_pliuri;
	string model;
	static const int PRET_FFP1 = 5;
	static const int PRET_FFP2 = 10;
	static const int PRET_FFP3 = 15;
};

class MascaPolicarbonat :
	public Masca
{
public:
	MascaPolicarbonat();
	MascaPolicarbonat(const string& prindere);
	friend ostream& operator<< (ostream& ofs, const MascaPolicarbonat& current);
	friend istream& operator>> (istream& ifs, MascaPolicarbonat& current);
	virtual ~MascaPolicarbonat();
	int GetPret() const override;
private:
	string prindere;
	static const int PRET = 20;
};

class Dezinfectant :
	public Produs
{
public:
	Dezinfectant();
	Dezinfectant(int nr_ucise, const vector<string>& ingrediente, const vector<string>& suprafete);
	virtual ~Dezinfectant();
	double eficienta() const;
	void SetReteta(int nr_ucise, const vector<string>& ingrediente, const vector<string>& suprafete); //modifica reteta unui dezinfectant
	virtual int GetTotalSpecii() const = 0;
	int GetPret() const override;
private:
	int nr_ucise;
	vector<string> ingrediente;
	vector<string> suprafete;
};

class DezinfectantBacterii :
	public virtual Dezinfectant
{
public:
	DezinfectantBacterii();
	DezinfectantBacterii(int nr_ucise, const vector<string> ingrediente, const vector<string>& suprafete);
	virtual ~DezinfectantBacterii();
	int GetTotalSpecii() const override;
protected:
	static const int TotalBacterii = 1000000000;
};

class DezinfectantVirusuri :
	public virtual Dezinfectant
{
public:
	DezinfectantVirusuri();
	DezinfectantVirusuri(int nr_ucise, const vector<string> ingrediente, const vector<string>& suprafete);
	virtual ~DezinfectantVirusuri();
	int GetTotalSpecii() const override;
protected:
	static const int TotalVirusuri = 100000000;
};

class DezinfectantFungi :
	public virtual Dezinfectant
{
public:
	DezinfectantFungi();
	DezinfectantFungi(int nr_ucise, const vector<string> ingrediente, const vector<string>& suprafete);
	virtual ~DezinfectantFungi();
	int GetTotalSpecii() const override;
protected:
	static const int TotalFungi = 1500000;
};

//Mostenire in diamant!!!
class DezinfectantMicroorganisme :
	public DezinfectantBacterii,
	public DezinfectantVirusuri,
	public DezinfectantFungi
{
public:
	virtual ~DezinfectantMicroorganisme();
	int GetTotalSpecii() const override;
private:
};

template<typename T1, typename T2, typename T3>
class triplet
{
protected:
	T1 x;
	T2 y;
	T3 z;
public:
	T1 GetX() const;
	T2 GetY() const;
	T3 GetZ() const;
	void SetX(T1 x);
	void SetY(T2 y);
	void SetZ(T3 z);
	triplet(T1 x = 0, T2 y = 0, T3 z = 0);
	virtual ~triplet();
};

class Data :
	public triplet<int, int, int>
{
public:
	int GetZi() const;
	int GetLuna() const;
	int GetAn() const;
	void SetZi(int zi);
	void SetLuna(int luna);
	void SetAn(int an);
	string Stringify() const;
	Data(int zi = 0, int luna = 0, int an = 0);
	virtual ~Data();
};


class Achizitie
{
public:
	Achizitie(int zi = 0, int luna = 0, int an = 0, string nume = "Nedefinit");
	void operator +=(Produs* p);
	string nume();
	bool operator<(const Achizitie& oth);
	bool operator==(const Achizitie& oth);
	vector<Produs*> GetProds() const;
	Data GetData() const;
	int GetVal() const;
private:
	int val;
	string name;
	Data data;
	vector<Produs*> prods;
};

class Arhiva
{
public:
	static Arhiva& GetInstance();
	Arhiva(const Arhiva&) = delete;
	Arhiva& operator=(const Arhiva&) = delete;
	void AddAchizitie(Achizitie* a);
	Dezinfectant* GetBest();
	int GetVenit(int luna) const;
	int GetVenitModel() const; //afiseaza venitul mastilor chirurgicale cu model
	int GetTVA(int an) const;
	string GetWorstDay() const; //afiseaza ziua cu cele mai slabe venituri
	string GetBestClient() const; //afiseaza cel mai fidel client
private:
	Arhiva();
	vector<Achizitie*> achizitii;
};

int main()
{
	EventLogger &log = EventLogger::GetInstance();
	log << "A inceput programul!\n";

	try
	{
		MascaChirurgicala mc1, mc2("ffp2", "verde brotacel", 55), mc3(mc1), mc4, mc5;
		mc4 = mc2;
		std::cin >> mc5;
		std::cout << mc1 << mc2;
		MascaPolicarbonat* mp1 = new MascaPolicarbonat(), * mp2 = new MascaPolicarbonat();
		MascaPolicarbonat* mp3 = new MascaPolicarbonat("elastic");
		std::cin >> *mp1 >> *mp2;
		std::cout << *mp3;
		Dezinfectant* d1 = new DezinfectantBacterii(100000000, std::vector<string>({ "sulfati non-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil" }), std::vector<std::string>({ "lemn", "sticla", "metal", "ceramica", "marmura" }));
		Dezinfectant* d2 = new DezinfectantVirusuri(50000000, std::vector<string>({ "Alkil Dimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal" }), std::vector<std::string>({ "lemn", "sticla", "ceramica", "marmura" }));
		Dezinfectant* d3 = new DezinfectantFungi(1400000, std::vector<string>({ "Alkil Etil Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal" }), std::vector<std::string>({ "sticla", "plastic" }));
		std::cout << d1->eficienta() << " " << d2->eficienta() << " " << d3->eficienta() << "\n";

		Achizitie* a1 = new Achizitie(26, 5, 2020, "PlushBio SRL");
		*a1 += mp1; //se adauga masca de policarbonat mp1 in lista de masti achizitionate
		*a1 += (&mc1); //se adauga masca chirugicala mc1 in lista
		*a1 += d3; // se adauga dezinfectantu de fungi d3 in lista de dezinfectanti achizitionati
		Achizitie* a2 = new Achizitie(25, 5, 2020, "Gucci");
		*a2 += d1;
		*a2 += d2;
		*a2 += d2;
		Achizitie a3, a4(*a1);
		a3 = *a2;
		if (*a1 < *a2) {
			std::cout << a1->nume() << " are valoarea facturii mai mica.\n";
		}
		else if (*a1 == *a2) {
			std::cout << a1->nume() << " si " << a2->nume() << " au aceasi valoare a facturii.\n";
		}
		else {
			std::cout << a2->nume() << " are valoarea facturii mai mica.\n";
		}

		Arhiva& arhiva = Arhiva::GetInstance();
		arhiva.AddAchizitie(a1);
		arhiva.AddAchizitie(a2);
		arhiva.AddAchizitie(&a3);
		arhiva.AddAchizitie(&a4);

		cout << arhiva.GetVenit(10);
		/*
		restul nu le-am mai scris aici sa nu omor main-ul, sunt functii din clasa Arhiva
		*/

		delete mp1;
		delete mp2;
		delete mp3;
		delete d1;
		delete d2;
		delete d3;
		delete a1;
		delete a2;
	}
	catch (exception& e)
	{
		log << e;
	}
	log << "S-a terminat programul!\n";
	return 0;
}

template<typename OutType>
Logger<OutType>::Logger(OutType* to) :
	out(to)
{
}

template<typename OutType>
Logger<OutType>::~Logger()
{
}

template<typename OutType>
void Logger<OutType>::Log(const string& toLog)
{
	*out << toLog;
}

template<typename OutType>
void Logger<OutType>::Log(int x)
{
	*out << x;
}

//stringloggerul va afisa direct in "strings.log"
StringLogger::StringLogger() :
	FileLogger("strings.log")
{
}

StringLogger::~StringLogger()
{
}

//exceptionloggerul va afisa direct in "exceptions.log"
ExceptionLogger::ExceptionLogger() :
	FileLogger("exceptions.log")
{
}

ExceptionLogger::~ExceptionLogger()
{
}

//filelogger-ul deschide un fisier in constructor
FileLogger::FileLogger(const string& fileName) :
	Logger(new ofstream(fileName))
{
}

//destructor file logger: inchidem fisierul deschis in constructor si il eliberam din memorie
FileLogger::~FileLogger()
{
	out->close();
	delete out;
}

//consoleLoggerul va afisa in consola (&cout)
ConsoleLogger::ConsoleLogger() :
	Logger(&cout)
{
}

ConsoleLogger::~ConsoleLogger()
{
}

//operator pentru afisarea in consola a unui string
ConsoleLogger& operator<<(ConsoleLogger& logger, const std::string& str)
{
	logger.Log(str);
	return logger;
}

//operator pentru afisarea in consola a unui int
ConsoleLogger& operator<<(ConsoleLogger& logger, int x)
{
	logger.Log(x);
	return logger;
}

//operator pentru afisarea unui string
StringLogger& operator<<(StringLogger& logger, const std::string& str)
{
	logger.Log("String message: " + str);
	return logger;
}

//operator pentru afisarea unei exceptii
ExceptionLogger& operator<<(ExceptionLogger& logger, std::exception& ex)
{
	string text = ex.what();
	//in functie de tipul exceptiei, afisam tipul acesteia si what-ul ei
	//RTTI
	if (const auto e = dynamic_cast<const bad_exception*>(&ex))
		logger.Log("Bad exception: " + text);
	else if (const auto e = dynamic_cast<const logic_error*>(&ex))
		logger.Log("Logic error: " + text);
	else if (const auto e = dynamic_cast<const runtime_error*>(&ex))
		logger.Log("Runtime error: " + text);
	else
		logger.Log("Other error: " + text);
	return logger;
}

//operator pentru citirea unui string din consola
ConsoleStringReader& operator>>(ConsoleStringReader& logger, string& str)
{
	str = logger.Read();
	//daca nu respecta criteriile de lungime, aruncam o exceptie
	if (str.size() < logger.lgMin || str.size() > logger.lgMax)
		throw length_error("Valoarea introdusa trebuie sa aiba lungimea intre " + 
			                to_string(logger.lgMin) + " si " + to_string(logger.lgMax));
	return logger;
}

//operator pentru citiera unui int din consola
ConsoleIntReader& operator>>(ConsoleIntReader& logger, int& x)
{
	x = logger.Read();
	//daca nu se incadreaza in restrictii, aruncam o exceptie
	if(x < logger.valMin || x > logger.valMax)
		throw range_error("Valoarea introdusa trebuie sa fie intre " +
			               to_string(logger.valMin) + " si " + to_string(logger.valMax)); 
	return logger;
}

ostream& operator<<(ostream& ofs, const MascaChirurgicala& current)
{
	ofs << "Tip: " << current.tip << "\n";
	ofs << "Culoare: " << current.culoare << "\n";
	ofs << "Nr pliuri: " << current.nr_pliuri << "\n";
	return ofs;
}

istream& operator>>(istream& ifs, MascaChirurgicala& current)
{
	ConsoleLogger console;
	console << "Tip: ";
	ifs >> current.tip;
	console << "Culoare: ";
	ifs >> current.culoare;
	console << "Nr pliuri: ";
	ifs >> current.nr_pliuri;
	return ifs;
}

ostream& operator<<(ostream& ofs, const MascaPolicarbonat& current)
{
	ofs << "Tip prindere: " << current.prindere << "\n";
	return ofs;
}

istream& operator>>(istream& ifs, MascaPolicarbonat& current)
{
	ConsoleLogger console;
	console << "Tip prindere: ";
	ifs >> current.prindere;
	return ifs;
}

//functia GetInstance a Singletonului
EventLogger& EventLogger::GetInstance()
{
	static EventLogger instance;
	return instance;
}

//FileLogger-ul afiseaza direct in logs.txt
EventLogger::EventLogger() :
	FileLogger("logs.txt")
{
}

template<typename T, typename InType>
Reader<T, InType>::Reader(InType* from) :
	in(from)
{
}

template<typename T, typename InType>
Reader<T, InType>::~Reader()
{
}

template<typename T, typename InType>
T Reader<T, InType>::Read()
{
	T ret;
	(*in) >> ret;
	return ret;
}

//deschidem un nou fisier cu numele "filename" pentru a citi
template<typename T>
FileReader<T>::FileReader(const string& fileName) :
	Reader(new ifstream(fileName))
{
}

//inchidem fisierul deschis si il eliberam din memorie
template<typename T>
FileReader<T>::~FileReader()
{
	Reader<T, ifstream>::in->close();
	delete Reader<T, ifstream>::in;
}

ConsoleStringReader::ConsoleStringReader(int lgMin, int lgMax) :
	Reader(&cin),
	lgMin(lgMin),
	lgMax(lgMax)
{
}

ConsoleStringReader::~ConsoleStringReader()
{
}

ConsoleIntReader::ConsoleIntReader(int valMin, int valMax):
	Reader(&cin),
	valMin(valMin),
	valMax(valMax)
{
}

ConsoleIntReader::~ConsoleIntReader()
{
}

Produs::~Produs()
{
}

Masca::Masca() :
	tip("Nedefinit")
{
}

Masca::Masca(const string& tip) :
	tip(tip)
{
}

Masca::~Masca()
{
}

string Masca::GetTip()
{
	return tip;
}

MascaChirurgicala::MascaChirurgicala() :
	culoare("Nedefinita"),
	nr_pliuri(-1),
	model("")
{
}

MascaChirurgicala::MascaChirurgicala(const string& tip, const string& culoare, int nr_pliuri) :
	Masca(tip),
	culoare(culoare),
	nr_pliuri(nr_pliuri),
	model("")
{
}

MascaChirurgicala::~MascaChirurgicala()
{
}

int MascaChirurgicala::GetPret() const
{
	int pret;
	if (tip == "ffp1")
		pret = PRET_FFP1;
	else if (tip == "ffp2")
		pret = PRET_FFP2;
	else if (tip == "ffp3")
		pret = PRET_FFP3;
	else 
		throw runtime_error("Tip invalid!");
	if (AreModel())
		pret += pret / 2;
	return pret;
}

void MascaChirurgicala::AddModel(const string& model)
{
	this->model = model;
}

bool MascaChirurgicala::AreModel() const
{
	return model.size() > 0;
}

Dezinfectant::Dezinfectant() :
	nr_ucise(-1),
	ingrediente(vector<string>()),
	suprafete(vector<string>())
{
}

Dezinfectant::Dezinfectant(int nr_ucise, const vector<string>& ingrediente, const vector<string>& suprafete) :
	nr_ucise(nr_ucise),
	ingrediente(ingrediente),
	suprafete(suprafete)
{
}

Dezinfectant::~Dezinfectant()
{
}

double Dezinfectant::eficienta() const
{
	int specii = GetTotalSpecii();
	return static_cast<double>(nr_ucise) / static_cast<double>(specii);
}

void Dezinfectant::SetReteta(int nr_ucise, const vector<string>& ingrediente, const vector<string>& suprafete)
{
	this->nr_ucise = nr_ucise;
	this->ingrediente = ingrediente;
	this->suprafete = suprafete;
}

int Dezinfectant::GetPret() const
{
	double ef = eficienta();
	if (ef < 90.0 / 100.0)
		return 10;
	if (ef < 95.0 / 100.0)
		return 20;
	if (ef < 97.5 / 100.0)
		return 30;
	if (ef < 99.0 / 100)
		return 40;
	if (ef < 99.99 / 100)
		return 50;
	throw runtime_error("Bad eficienta");
}

DezinfectantBacterii::DezinfectantBacterii()
{
}

DezinfectantBacterii::DezinfectantBacterii(int nr_ucise, const vector<string> ingrediente, const vector<string>& suprafete) :
	Dezinfectant(nr_ucise, ingrediente, suprafete)
{
}

DezinfectantBacterii::~DezinfectantBacterii()
{
}

int DezinfectantBacterii::GetTotalSpecii() const
{
	return TotalBacterii;
}

DezinfectantVirusuri::DezinfectantVirusuri()
{
}

DezinfectantVirusuri::DezinfectantVirusuri(int nr_ucise, const vector<string> ingrediente, const vector<string>& suprafete) :
	Dezinfectant(nr_ucise, ingrediente, suprafete)
{
}

DezinfectantVirusuri::~DezinfectantVirusuri()
{
}

int DezinfectantVirusuri::GetTotalSpecii() const
{
	return TotalVirusuri;
}

DezinfectantFungi::DezinfectantFungi()
{
}

DezinfectantFungi::DezinfectantFungi(int nr_ucise, const vector<string> ingrediente, const vector<string>& suprafete) :
	Dezinfectant(nr_ucise, ingrediente, suprafete)
{
}

DezinfectantFungi::~DezinfectantFungi()
{
}

int DezinfectantFungi::GetTotalSpecii() const
{
	return TotalFungi;
}

DezinfectantMicroorganisme::~DezinfectantMicroorganisme()
{
}

int DezinfectantMicroorganisme::GetTotalSpecii() const
{
	return TotalBacterii + TotalVirusuri + TotalFungi;
}

MascaPolicarbonat::MascaPolicarbonat() :
	Masca("ffp0"),
	prindere("Nedefinit")
{
}

MascaPolicarbonat::MascaPolicarbonat(const string& prindere) :
	Masca("ffp0"),
	prindere(prindere)
{
}

MascaPolicarbonat::~MascaPolicarbonat()
{
}

int MascaPolicarbonat::GetPret() const
{
	return PRET;
}

template<typename T1, typename T2, typename T3>
T1 triplet<T1, T2, T3>::GetX() const
{
	return x;
}

template<typename T1, typename T2, typename T3>
T2 triplet<T1, T2, T3>::GetY() const
{
	return y;
}

template<typename T1, typename T2, typename T3>
T3 triplet<T1, T2, T3>::GetZ() const
{
	return z;
}

template<typename T1, typename T2, typename T3>
void triplet<T1, T2, T3>::SetY(T2 y)
{
	this->y = y;
}

template<typename T1, typename T2, typename T3>
void triplet<T1, T2, T3>::SetZ(T3 z)
{
	this->z = z;
}

template<typename T1, typename T2, typename T3>
triplet<T1, T2, T3>::triplet(T1 x, T2 y, T3 z) :
	x(x),
	y(y),
	z(z)
{
}

template<typename T1, typename T2, typename T3>
triplet<T1, T2, T3>::~triplet()
{
}

template<typename T1, typename T2, typename T3>
void triplet<T1, T2, T3>::SetX(T1 x)
{
	this->x = x;
}

Data::~Data()
{
}

int Data::GetZi() const
{
	return x;
}

int Data::GetLuna() const
{
	return y;
}

int Data::GetAn() const
{
	return z;
}

void Data::SetZi(int zi)
{
	x = zi;
}

void Data::SetLuna(int luna)
{
	y = luna;
}

void Data::SetAn(int an)
{
	z = an;
}

string Data::Stringify() const
{
	return to_string(x) + "/" + to_string(y) + "/" + to_string(z);
}

Data::Data(int zi, int luna, int an) :
	triplet(zi, luna, an)
{
}

Achizitie::Achizitie(int zi, int luna, int an, string nume)
{
	data = Data(zi, luna, an);
	name = nume;
}

void Achizitie::operator+=(Produs* p)
{
	val += p->GetPret();
	prods.push_back(p);
}

string Achizitie::nume()
{
	return name;
}

bool Achizitie::operator<(const Achizitie& oth)
{
	return val < oth.val;
}

bool Achizitie::operator==(const Achizitie& oth)
{
	return val == oth.val;
}

vector<Produs*> Achizitie::GetProds() const
{
	return prods;
}

Data Achizitie::GetData() const
{
	return data;
}

int Achizitie::GetVal() const
{
	return val;
}

Arhiva& Arhiva::GetInstance()
{
	static Arhiva instance;
	return instance;
}


void Arhiva::AddAchizitie(Achizitie* a)
{
	achizitii.push_back(a);
}

Dezinfectant* Arhiva::GetBest()
{
	Dezinfectant* best = nullptr;
	double bestEficienta = 0.0;
	for (auto* ac : achizitii)
	{
		for (auto* p : ac->GetProds())
		{
			if (auto dez = dynamic_cast<Dezinfectant*>(p))
			{
				if (dez->eficienta() > bestEficienta)
				{
					bestEficienta = dez->eficienta();
					best = dez;
				}
			}
		}
	}
	return best;
}

int Arhiva::GetVenit(int luna) const
{
	int ret = 0;
	for (auto* ac : achizitii)
		if (ac->GetData().GetLuna() == luna)
			ret += ac->GetVal();
	return ret;
}

int Arhiva::GetVenitModel() const
{
	int venit = 0;
	for (auto* ac : achizitii)
	{
		for (auto* p : ac->GetProds())
		{
			if (auto masca = dynamic_cast<MascaChirurgicala*>(p))
			{
				if (masca->AreModel())
					venit += masca->GetPret();
			}
		}
	}
	return venit;
}

int Arhiva::GetTVA(int an) const
{
	int venit = 0;
	for (auto* ac : achizitii)
		if (ac->GetData().GetAn() == an)
			venit += ac->GetVal();
	return 19 * venit / 100;
}

string Arhiva::GetWorstDay() const
{
	unordered_map<string, int> venit;
	for (auto* ac : achizitii)
		venit[ac->GetData().Stringify()] += ac->GetVal();
	pair<string, int> worstDay = make_pair("", INT_MAX);
	for (const auto& p : venit)
		if (p.second < worstDay.second)
			worstDay = p;
	return worstDay.first;
}

string Arhiva::GetBestClient() const
{
	unordered_map<string, int> venit; 
	for (auto* ac : achizitii)
		venit[ac->nume()] += ac->GetVal();
	
	pair<string, int> bestClient = make_pair("", -1);
	for (const auto& p : venit)
		if (p.second > bestClient.second)
			bestClient = p;
	return bestClient.first;
}

Arhiva::Arhiva()
{
}
