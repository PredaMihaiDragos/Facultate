#include <iostream>
#include <cmath>
using namespace std;
 
class Masina
protected:
float greutate;
float viteza;
int an;
string nume;
public:
   Masina(float g = 0, float v = 0, int a = 0, string n = ""): greutate(g),
                                                               viteza(v),
                                                               an(a),
                                                               nume(n)
   {}
   virtual float CalculAutonmie() = 0;
 
};
 
class MasinaElectrica : public Masina {
protected:
    float capacitateBaterie;
 
public:
    MasinaElectrica(float g = 0, float v = 0, int a = 0, string n = "", float cb = 0): Masina(g, v, a, n),                                                                     capacitateBaterie(cb)
    {}
 
    float CalculAutonomie() {
        return this->capacitateBaterie / (this->greutate * this->greutate);
    }
 
};
 
class MasinaCarburant: public Masina {
private:
protected:
   float capacitateRezervor;
   string tipCombustibil;
public:
   MasinaCarburant(float _g = 0, float _v = 0, int _an = 0, string _n = "", float _cr = 0, string _tC = ""):
       Masina(_g, _v, _an, _n), capacitateRezervor(_cr), tipCombustibil(_tC){}
  
   float calculAutonomie(){
       return capacitateRezervor / sqrt(greutate);
   }
 
};
 
 
 
int main()
{
 
}

/// HEREEEEEEE

#include <bits/stdc++.h>
 
class Masina
{
protected:
    float greutate, viteza;
    int an;
    std::string nume;
public:
    Masina(float g = 0, float v = 0, int a = 0, std::string n = ""): greutate(g),
                                                                viteza(v),
                                                                an(a),
                                                                nume(n){}
    virtual float calculAutonomie() = 0;
 
    virtual ~Masina()
    {}
};
 
class Electrica: virtual public Masina
{
protected:
    float capacitateBaterie;
public:
    Electrica(float g = 0, float v = 0, int a = 0, std::string n = "", float cb = 0): Masina(g, v, a, n),
                                                                                      capacitateBaterie(cb){}
    float calculAutonomie(){ return capacitateBaterie / (greutate * greutate); }
};
 
 
class Carburant: virtual public Masina
{
private:
    std::string combustibil;
protected:
    float capacitateRezervor;
public:
    Carburant(float g = 0, float v = 0, int a = 0, std::string n = "", float cr = 0, std::string c = ""): Masina(g, v, a, n),
                                                                                                        combustibil(c),
                                                                                                        capacitateRezervor(cr)
                                                                                                {}
    float calculAutonomie(){ return capacitateRezervor / sqrt(greutate); }
};
 
class Hibrida: public Electrica, public Carburant
{
public:
    Hibrida(float g = 0, float v = 0, int a = 0, std::string n = "", float cr = 0, float cb = 0): Masina(g, v, a, n),
                                                                                                  Electrica(g, v, a, n, cb),
                                                                                                  Carburant(g, v, a, n, cr, "benzina"){}
    float calculAutonomie(){ return Carburant::calculAutonomie() + Electrica::calculAutonomie();}
};
 
class Tranzactie
{
private:
    std::string numeClient;
    std::string dataAchizitie;
    std::vector<Masina*> listaMasini;
 
    void freeMasini()
    {
        for (auto ptr : listaMasini)
            delete ptr;
    }
 
public:
    Tranzactie(std::string nc = "Anonim", std::string date = "") : numeClient(nc),
                                                                   dataAchizitie(date)
    {}
 
    void addMasina(Masina* masina) 
    {
        if (Hibrida* ptr = dynamic_cast<Hibrida*>(masina))
            listaMasini.push_back(new Hibrida(*ptr));
        else if (Electrica* ptr = dynamic_cast<Electrica*>(masina))
            listaMasini.push_back(new Electrica(*ptr));
        else if (Carburant* ptr = dynamic_cast<Carburant*>(masina))
            listaMasini.push_back(new Carburant(*ptr));
    }
 
    Tranzactie(const Tranzactie& tr) : numeClient(tr.numeClient),
                                       dataAchizitie(tr.dataAchizitie)
    {
        for (auto ptr : tr.listaMasini)
            addMasina(ptr);
    }
 
    Tranzactie& operator = (const Tranzactie& tr)
    {
        freeMasini();
        numeClient = tr.numeClient;
        dataAchizitie = tr.dataAchizitie;
        for (auto ptr : tr.listaMasini)
            addMasina(ptr);
        return *this;
    }
 
    ~Tranzactie()
    {
        freeMasini();
    }
};
 
int main()
{
    Tranzactie tr;
    Tranzactie tr1; 
 
    Hibrida mHibrid;
 
 
    std::cout<<'\n';
    return 0;
}
 

class Manager {
private:
   vector <Tranzactie> tranzactii;
   static Manager* instance;
 
   Manager() {}
   Manager(const Manager&) = delete;
   Manager& operator = (const Manager&) = delete;
 
public:
   static Manager* get_instance() {
       if (!instance) instance = new Manager;
       return instance;
   }
 
   void addTranzactie(const Tranzactie& tr) {
       tranzactii.push_back(tr);
   }
};
 
Manager* Manager::instance = nullptr;

//----------------

#include <bits/stdc++.h>
 
class Masina
{
protected:
    float greutate, viteza;
    int an;
    std::string nume;
public:
    Masina(float g = 0, float v = 0, int a = 0, std::string n = ""): greutate(g),
                                                                viteza(v),
                                                                an(a),
                                                                nume(n){}
    virtual float calculAutonomie() = 0;
    inline void SetViteza(float v) { viteza = v; }
    inline float GetViteza() const { return viteza; }
    inline std::string getNume()const
    {
        return nume;
    }
    virtual ~Masina()
    {}
    
};
 
class Electrica: virtual public Masina
{
protected:
    float capacitateBaterie;
public:
    Electrica(float g = 0, float v = 0, int a = 0, std::string n = "", float cb = 0): Masina(g, v, a, n),
                                                                                      capacitateBaterie(cb){}
    float calculAutonomie(){ return capacitateBaterie / (greutate * greutate); }
};
 
 
class Carburant: virtual public Masina
{
private:
    std::string combustibil;
protected:
    float capacitateRezervor;
public:
    Carburant(float g = 0, float v = 0, int a = 0, std::string n = "", float cr = 0, std::string c = ""): Masina(g, v, a, n),
                                                                                                        combustibil(c),
                                                                                                        capacitateRezervor(cr)
                                                                                                {}
    float calculAutonomie(){ return capacitateRezervor / sqrt(greutate); }
};
 
class Hibrida: public Electrica, public Carburant
{
public:
    Hibrida(float g = 0, float v = 0, int a = 0, std::string n = "", float cr = 0, float cb = 0): Masina(g, v, a, n),
                                                                                                  Electrica(g, v, a, n, cb),
                                                                                                  Carburant(g, v, a, n, cr, "benzina"){}
    float calculAutonomie(){ return Carburant::calculAutonomie() + Electrica::calculAutonomie();}
};
 
class Tranzactie
{
private:
    std::string numeClient;
    std::string dataAchizitie;
    std::vector<Masina*> listaMasini;
 
    void freeMasini()
    {
        for (auto ptr : listaMasini)
            delete ptr;
    }
 
public:
    Tranzactie(std::string nc = "Anonim", std::string date = "") : numeClient(nc),
                                                                   dataAchizitie(date)
    {}
 
    void addMasina(Masina* masina) 
    {
        if (Hibrida* ptr = dynamic_cast<Hibrida*>(masina))
            listaMasini.push_back(new Hibrida(*ptr));
        else if (Electrica* ptr = dynamic_cast<Electrica*>(masina))
            listaMasini.push_back(new Electrica(*ptr));
        else if (Carburant* ptr = dynamic_cast<Carburant*>(masina))
            listaMasini.push_back(new Carburant(*ptr));
    }
 
    Tranzactie(const Tranzactie& tr) : numeClient(tr.numeClient),
                                       dataAchizitie(tr.dataAchizitie)
    {
        for (auto ptr : tr.listaMasini)
            addMasina(ptr);
    }
 
    Tranzactie& operator = (const Tranzactie& tr)
    {
        freeMasini();
        numeClient = tr.numeClient;
        dataAchizitie = tr.dataAchizitie;
        for (auto ptr : tr.listaMasini)
            addMasina(ptr);
        return *this;
    }

    inline const std::vector<Masina*>& getMasini() const
    {
        return listaMasini;
    }
 
    ~Tranzactie()
    {
        freeMasini();
    }
};
 
int main()
{
    Tranzactie tr;
    Tranzactie tr1; 
 
    Hibrida mHibrid;
 
 
    std::cout<<'\n';
    return 0;
}
 

class Manager {
private:
   std::vector <Tranzactie> tranzactii;
   static Manager* instance;
 
   Manager() {}
   Manager(const Manager&) = delete;
   Manager& operator = (const Manager&) = delete;
 
public:

    std::string get_most_sold()
    {
        std::unordered_map <std::string, int> mapp;
        for (auto& tranzactie: tranzactii)
            for(auto& masina:tranzactie.getMasini())
            {
                mapp[masina->getNume()] ++;
            }
        int Max = 0;
        std::string ans;
        for (auto& it: mapp)
            if (it.second > Max)
                ans = it.first, Max = it.second;
        return ans;
    } 

   static Manager* get_instance() {
       if (!instance) instance = new Manager;
       return instance;
   }
 
   void addTranzactie(const Tranzactie& tr) {
       tranzactii.push_back(tr);
   }

   void AddProcent(const std::string &nume, int procent)
   {
        for (auto& tranzactie: tranzactii)
            for(auto& masina:tranzactie.getMasini())
            {
                if(masina->getNume() == nume)
                    masina->SetViteza(masina->getViteza() + 1.0f * procent/100 * masina->getViteza());
            }
   }
};
 
Manager* Manager::instance = nullptr;
