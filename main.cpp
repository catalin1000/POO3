#include <iostream>
#include <vector>
#include <typeinfo>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;
int maxi;
class Hrana ///animale pe care le poate manca
{
    string nume;
    float cost;
public:
    Hrana();
    Hrana(string,float);
    Hrana(const Hrana&);
    ///operatori
    Hrana operator =(const Hrana&);
    friend istream& operator >>(istream&, Hrana&);
    friend ostream& operator <<(ostream&, const Hrana&);
    string gettnume()
    {
        return this->nume;
    }
    float getcost() const
    {
        return this->cost;
    }
    ~Hrana() {}


};


class CitireSiAfisare
{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};


class Vietuitoare:public CitireSiAfisare
{
protected:
    string nume;
    int aniDurataViata;
    string culoare;
    list<Hrana> listaHrana; //
    float cost;

public:
    Vietuitoare();
    Vietuitoare(string,int,string,const list<Hrana>&,float);
    Vietuitoare(const Vietuitoare&);

    Vietuitoare& operator =(const Vietuitoare&);
    friend istream& operator >>(istream&, Vietuitoare&);
    friend ostream& operator <<(ostream&, const Vietuitoare&);

    virtual float pret() const=0;
    virtual int tipe() const=0;
    float getcost()
    {
        return this->cost;
    }
    string getnume()
    {
        return this->nume;
    }

    int getaniDurataViata()
    {
        return this->aniDurataViata;
    }

    string getculoare()
    {
        return this->culoare;
    }
    list<Hrana> getlistaHrana() const
    {

        return this->listaHrana;
    }

    istream& citire(istream& in)
    {
        in.get();
        cout<<"Introduceti numele: ";
        getline(in,this->nume);
        cout<<"Introduceti durata de viata in ani: ";
        in>>this->aniDurataViata;
        in.get();
        cout<<"Introduceti culoarea vietuitoarei: ";
        getline(in,this->culoare);
        cout<<"Introduceti costul vietuitoarei: ";
        in>>this->cost;

        if(!this->listaHrana.empty())
            this->listaHrana.clear();

        cout<<"1 pentru a introduce hrana si 0 pentru a nu mai adauga \n";
        bool alegere;
        while(cin>>alegere && alegere)
        {
            this->listaHrana.push_back(*(new Hrana()));
            in>>this->listaHrana.back();
            cout<<"1 pentru a introduce hrana si 0 pentru a nu mai adauga \n";
        }
        return in;

    }
    ostream& afisare(ostream& out) const
    {
        out<<endl;
        out<<"Nume: "<<this->nume<<endl;
        out<<"Durata de viata: "<<this->aniDurataViata<<endl;
        out<<"Culoarea: "<<this->culoare<<endl;
        out<<"Costul animalului este: "<<this->cost<<endl;
        out<<"Lista animalelor care sunt hrana:\n";
//        for(int i=0; i<this->listaHrana.size(); i++)
//            out<<this->listaHrana[i];
        for(auto it=this->listaHrana.begin(); it!=this->listaHrana.end(); ++it)
            out<<*it;
        ///out<<endl;
        return out;
    }
    virtual ~Vietuitoare()
    {
        if(!this->listaHrana.empty())
            this->listaHrana.clear();
    }

};

class VietuitoareTerestre:virtual public Vietuitoare
{
protected:
    int numarPicioare;
    bool coada;
    bool cusca;
public:
    VietuitoareTerestre();
    VietuitoareTerestre(string,int,string,const list<Hrana>&,float,int,bool,bool);
    VietuitoareTerestre(const VietuitoareTerestre&);
    bool operator < (const VietuitoareTerestre&);
    bool operator > (const VietuitoareTerestre&);





    VietuitoareTerestre& operator =(const VietuitoareTerestre&);
    ///friend istream& operator >>(istream&, VietuitoareTerestre&);
    /// friend ostream& operator <<(ostream&, const VietuitoareTerestre&);
    float pret()const;

    int tipe() const
    {
        return 1;
    }
    istream& citire(istream& in)
    {
        this->Vietuitoare::citire(in) ;
        ///in>>(Vietuitoare&)obj;
        cout<<"Introduceti numarul de membre: ";
        in>>this->numarPicioare;
        cout<<"Introduceti 1 daca are coada sau 0 in caz contrar\n";
        in>>this->coada;
        cout<<"Introduceti 1 daca are nevoie de cusca sau 0 in caz contrar\n";
        in>>this->cusca;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        this->Vietuitoare::afisare(out);
        ///out<<(Vietuitoare&)obj;
        out<<"Numar membre: "<<this->numarPicioare<<endl;
        if(this->coada)
            out<<"Animalul are coada."<<endl;
        else
            out<<"Animalul nu are coada."<<endl;
        if(this->cusca)
            out<<"Animalul are nevoie de cusca."<<endl;
        else
            out<<"Animalul nu are nevoie de cusca."<<endl;
        return out;
    }
    virtual ~VietuitoareTerestre() {}
};

class VietuitoareAcvatice:virtual public Vietuitoare
{

    bool coada2;
protected:
    string inmultire;
    bool solzi;

public:
    VietuitoareAcvatice();
    VietuitoareAcvatice(string,int,string,const list<Hrana>&,float,bool,string,bool);
    VietuitoareAcvatice(const VietuitoareAcvatice&);
    bool operator < (const VietuitoareAcvatice&);
    bool operator > (const VietuitoareAcvatice&);

    VietuitoareAcvatice& operator =(const VietuitoareAcvatice&);
    /// friend istream& operator >>(istream&, VietuitoareAcvatice&);
    /// friend ostream& operator <<(ostream&, const VietuitoareAcvatice&);
    float pret()const;

    int tipe() const
    {
        return 2;
    }
    istream& citire(istream& in)
    {
        this->Vietuitoare::citire(in) ;
        /// in>>(Vietuitoare&)obj;
        cout<<"Introduceti 1 daca are coada sau 0 in caz contrar\n";
        in>>this->coada2;
        in.get();
        cout<<"Introduceti tipul de inmultire: ";
        getline(in,this->inmultire);
        cout<<"Introduceti 1 daca are solzi sau 0 in caz contrar\n";
        in>>this->solzi;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        this->Vietuitoare::afisare(out);
        ///out<<(Vietuitoare&)obj;
        if(this->coada2)
            out<<"Animalul are coada."<<endl;
        else
            out<<"Animalul nu are coada."<<endl;
        out<<"Tipul de inmultire este: "<<this->inmultire<<endl;
        if(this->solzi)
            out<<"Animalul are solzi."<<endl;
        else
            out<<"Animalul nu are solzi."<<endl;
        return out;
    }
    virtual ~VietuitoareAcvatice() {}
};

class Amfibieni: public VietuitoareTerestre,public VietuitoareAcvatice
{
public:
    Amfibieni();
    Amfibieni(string,int,string,const list<Hrana>&,float,int,bool,string,bool);
    Amfibieni(const Amfibieni&);
    Amfibieni& operator=(Amfibieni&);

    bool operator < (const Amfibieni&);
    bool operator > (const Amfibieni&);

    /// in total 12
//    friend bool operator<(const VietuitoareTerestre&,const VietuitoareAcvatice&);
//    friend bool operator>(const VietuitoareTerestre&,const VietuitoareAcvatice&);
//    friend bool operator<(const VietuitoareAcvatice&,const VietuitoareTerestre&);
//    friend bool operator>(const VietuitoareAcvatice&,const VietuitoareTerestre&);
//
//    friend bool operator<(const VietuitoareTerestre&,const Amfibieni&);
//    friend bool operator>(const VietuitoareTerestre&,const Amfibieni&);
//    friend bool operator<(const Amfibieni&,const VietuitoareTerestre&);
//    friend bool operator>(const Amfibieni&,const VietuitoareTerestre&);
//
//
//
//    friend bool operator<(const Amfibieni&,const VietuitoareAcvatice&);
//    friend bool operator>(const Amfibieni&,const VietuitoareAcvatice&);
//    friend bool operator<(const VietuitoareAcvatice&,const Amfibieni&);
//    friend bool operator>(const VietuitoareAcvatice&,const Amfibieni&);

    float pret()const;

    int tipe() const
    {
        return 3;
    }
    istream& citire(istream& in)
    {
        this->Vietuitoare::citire(in) ;
        /// in>>(Vietuitoare&)obj;
        cout<<"Introduceti numarul de membre: ";
        in>>this->numarPicioare;
        cout<<"Introduceti 1 daca are coada sau 0 in caz contrar\n";
        in>>this->coada;
        in.get();
        cout<<"Introduceti tipul de inmultire: ";
        getline(in,this->inmultire);
        cout<<"Introduceti 1 daca are solzi sau 0 in caz contrar\n";
        in>>this->solzi;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        this->Vietuitoare::afisare(out);
        ///out<<(Vietuitoare&)obj;
        out<<"Numar membre: "<<this->numarPicioare<<endl;
        if(this->coada)
            out<<"Animalul are coada."<<endl;
        else
            out<<"Animalul nu are coada."<<endl;
        out<<"Tipul de inmultire este: "<<this->inmultire<<endl;
        if(this->solzi)
            out<<"Animalul are solzi."<<endl;
        else
            out<<"Animalul nu are solzi."<<endl;
        return out;
    }
    ~Amfibieni() {}

};

Amfibieni::Amfibieni():Vietuitoare(),VietuitoareTerestre(),VietuitoareAcvatice()
{
//    this->numarPicioare=0;
//    this->coada=false;
//    this->inmultire="anonima";
//    this->solzi=false;
}

Amfibieni::Amfibieni(string nume,int aniDurataViata,string culoare,const list<Hrana>& listaHrana,float cost,int numarPicioare,bool coada,string inmultire,bool solzi)
    :Vietuitoare(nume,aniDurataViata,culoare,listaHrana,cost),VietuitoareTerestre( nume, aniDurataViata, culoare, listaHrana, cost, numarPicioare, coada, cusca),
     VietuitoareAcvatice( nume, aniDurataViata, culoare, listaHrana, cost, coada, inmultire, solzi)
{
//    this->numarPicioare=numarPicioare;
//    this->coada=coada;
//    this->inmultire=inmultire;
//    this->solzi=solzi;
}
Amfibieni::Amfibieni(const Amfibieni& obj):Vietuitoare(obj),VietuitoareTerestre(obj),VietuitoareAcvatice(obj)
{
//    this->numarPicioare=obj.numarPicioare;
//    this->coada=obj.coada;
//    this->inmultire=obj.inmultire;
//    this->solzi=obj.solzi;
}
Amfibieni& Amfibieni::operator=(Amfibieni& obj)
{
    if(this!=&obj)
    {
        VietuitoareTerestre::operator=(obj);
        VietuitoareAcvatice::operator=(obj);
//        this->numarPicioare=obj.numarPicioare;
//        this->coada=obj.coada;
//        this->inmultire=obj.inmultire;
//        this->solzi=obj.solzi;
    }
    return *this;
}






istream& operator >>(istream& in,Vietuitoare& obj)
{
    return obj.citire(in);

}
ostream& operator <<(ostream& out,Vietuitoare& obj)
{
    return obj.afisare(out);
}

float Amfibieni::pret()const
{
    float mini=1000000;
    cout<<"Pretul pentru "<<this->nume<<" este: ";
    cout<<this->cost;
    cout<<"\nPretul minim pentru hrana este: ";
//    for(int i=0; i<this->listaHrana.size(); i++)
//        if(listaHrana[i].getcost()<mini)
//            mini=listaHrana[i].getcost();
    for(auto it=this->listaHrana.begin(); it!=this->listaHrana.end(); ++it)
        if((*it).getcost()<mini)
            mini=(*it).getcost();

    if(mini==1000000)
        mini=0;
    cout<<mini;

    cout<<"\nPretul pentru acvariu este 250\n";
    cout<<"Pretul total este: "<<mini+(this->cost)+250;
    cout<<endl;
    return (mini+(this->cost)+250);
}


float VietuitoareTerestre::pret()const
{
    float mini=1000000;
    cout<<"Pretul pentru "<<this->nume<<" este: ";
    cout<<this->cost;
    cout<<"\nPretul minim pentru hrana este: ";
//    for(int i=0; i<this->listaHrana.size(); i++)
//        if(listaHrana[i].getcost()<mini)
//            mini=listaHrana[i].getcost();
    for(auto it=this->listaHrana.begin(); it!=this->listaHrana.end(); ++it)
        if((*it).getcost()<mini)
            mini=(*it).getcost();

    if(mini==1000000)
        mini=0;
    cout<<mini;
    if(this->cusca)
    {
        cout<<"\nPretul pentru cusca este 200\n";
        cout<<"Pretul total este: "<<mini+(this->cost)+200;
        cout<<endl;
        return (mini+(this->cost)+200);
    }
    else
    {
        cout<<"\nPretul total este: "<<mini+(this->cost);
        cout<<endl;
        return (mini+(this->cost));
    }

}
float VietuitoareAcvatice::pret() const
{
    float mini=1000000;
    cout<<"Pretul pentru "<<this->nume<<" este: ";
    cout<<this->cost;
    cout<<"\nPretul minim pentru hrana este: ";
//    for(int i=0; i<this->listaHrana.size(); i++)
//        if(listaHrana[i].getcost()<mini)
//            mini=listaHrana[i].getcost();

    for(auto it=this->listaHrana.begin(); it!=this->listaHrana.end(); ++it)
        if((*it).getcost()<mini)
            mini=(*it).getcost();

    if(mini==1000000)
        mini=0;
    cout<<mini;

    cout<<"\nPretul pentru acvariu este 250\n";
    cout<<"Pretul total este: "<<mini+(this->cost)+250;
    cout<<endl;
    return (mini+(this->cost)+250);
}
Hrana::Hrana()
{
    this->nume="";
    this->cost=0;
}
Hrana::Hrana(string nume,float cost)
{
    this->nume=nume;
    this->cost=cost;
}
Hrana::Hrana(const Hrana& obj)
{
    this->nume=obj.nume;
    this->cost=obj.cost;
}
Hrana Hrana::operator=(const Hrana& obj)
{
    if(this!= &obj)
    {
        this->nume=obj.nume;
        this->cost=obj.cost;
    }
    return *this;

}
istream& operator >> (istream& in, Hrana& obj)
{
    in.get();
    cout<<"Introduceti numele animalului care poate fi hrana: ";
    getline(in,obj.nume);
    cout<<"Introduceti costul animalului care poate fi hrana: ";
    in>>obj.cost;
    ///cout<<endl;
    return in;
}
ostream& operator << (ostream& out, const Hrana& obj)
{
    out<<"Numele hranei este: ";
    out<<obj.nume<<endl;
    out<<"Costul pentru "<<obj.nume<<" este: ";
    out<<obj.cost<<endl;

    return out;
}


Vietuitoare::Vietuitoare()
{
    this->nume="Anonim";
    this->listaHrana= {};
    this->aniDurataViata=0;
    this->culoare="anonima";
    this->cost=0;
}
Vietuitoare::Vietuitoare(string nume,int aniDurataViata,string culoare,const list<Hrana>& listaHrana,float cost)
{
    this->nume=nume;
    this->listaHrana=listaHrana;
    this->aniDurataViata=aniDurataViata;
    this->culoare=culoare;
    this->cost=cost;
}
Vietuitoare::Vietuitoare(const Vietuitoare& obj)
{

    this->nume=obj.nume;
    this->listaHrana=obj.listaHrana;
    this->aniDurataViata=obj.aniDurataViata;
    this->culoare=obj.culoare;
    this->cost=obj.cost;

}
Vietuitoare& Vietuitoare::operator=(const Vietuitoare& obj)
{
    if(this!= &obj)
    {
        this->nume=obj.nume;
        this->listaHrana=obj.listaHrana;
        this->aniDurataViata=obj.aniDurataViata;
        this->culoare=obj.culoare;
        this->cost=obj.cost;
    }
    return *this;
}

//istream& citire(istream& in)
//{
//    cout<<"Introduceti numele: ";
//    in>>this->nume;
//    cout<<"Introduceti durata de viata in ani: ";
//    in>>this->aniDurataViata;
//    cout<<"Introduceti culoarea vietuitoarei: ";
//    in>>this->culoare;
//    cout<<"Introduceti costul vietuitoarei: ";
//    in>>this->cost;
//
//    if(!this->listaHrana.empty())
//        this->listaHrana.clear();
//
//        cout<<"1 pentru a introduce hrana si 0 pentru a nu mai adauga \n";
//        bool alegere;
//        while(cin>>alegere && alegere)
//        {
//            this->listaHrana.push_back(*(new Hrana()));
//            in>>this->listaHrana.back();
//            cout<<"1 pentru a introduce hrana si 0 pentru a nu mai adauga \n";
//        }
//        return in;
//
//}
//ostream& afisare(ostream& out) const
//{
//    out<<endl;
//    out<<"Nume: "<<obj.nume<<endl;
//    out<<"Durata de viata: "<<obj.aniDurataViata<<endl;
//    out<<"Culoarea: "<<obj.culoare<<endl;
//    out<<"Costul animalului este: "<<obj.cost<<endl;
//    out<<"Lista animalelor care sunt hrana:\n";
//    for(int i=0;i<obj.listaHrana.size();i++)
//        out<<obj.listaHrana[i];
//    ///out<<endl;
//    return out;
//}


bool VietuitoareTerestre::operator < (const VietuitoareTerestre& obj)
{
    return this->getlistaHrana().size()<obj.getlistaHrana().size();
}
bool VietuitoareTerestre::operator > (const VietuitoareTerestre& obj)

{
    return this->getlistaHrana().size()>obj.getlistaHrana().size();
}


bool Amfibieni::operator < (const Amfibieni&obj )
{
    return this->getlistaHrana().size()<obj.getlistaHrana().size();
}
bool Amfibieni::operator > (const Amfibieni&obj)
{
    return this->getlistaHrana().size()>obj.getlistaHrana().size();
}


bool VietuitoareAcvatice::operator < (const VietuitoareAcvatice& obj)
{
    return this->getlistaHrana().size()<obj.getlistaHrana().size();
}
bool VietuitoareAcvatice::operator > (const VietuitoareAcvatice& obj)

{
    return this->getlistaHrana().size()>obj.getlistaHrana().size();
}




// bool operator<(const VietuitoareTerestre& obj1,const VietuitoareAcvatice& obj2)
//{
//    return obj1.getlistaHrana().size()<obj2.getlistaHrana().size();
//}
//    friend bool operator>(const VietuitoareTerestre&,const VietuitoareAcvatice&)
//    friend bool operator<(const VietuitoareAcvatice&,const VietuitoareTerestre&)
//    friend bool operator>(const VietuitoareAcvatice&,const VietuitoareTerestre&)
//
//    friend bool operator<(const VietuitoareTerestre&,const Amfibieni&)
//    friend bool operator>(const VietuitoareTerestre&,const Amfibieni&)
//    friend bool operator<(const Amfibieni&,const VietuitoareTerestre&)
//    friend bool operator>(const Amfibieni&,const VietuitoareTerestre&)
//
//
//
//    friend bool operator<(const Amfibieni&,const VietuitoareAcvatice&)
//    friend bool operator>(const Amfibieni&,const VietuitoareAcvatice&)
//    friend bool operator<(const VietuitoareAcvatice&,const Amfibieni&)
//    friend bool operator>(const VietuitoareAcvatice&,const Amfibieni&)





VietuitoareTerestre::VietuitoareTerestre():Vietuitoare()
{
    this->numarPicioare=0;
    this->coada=false;
    this->cusca=false;
}
VietuitoareTerestre::VietuitoareTerestre(string nume,int aniDurataViata,string culoare,const list<Hrana>& listaHrana,float cost,int numarPicioare, bool coada, bool cusca):
    Vietuitoare(nume,aniDurataViata,culoare,listaHrana,cost)
{
    this->numarPicioare=numarPicioare;
    this->coada=coada;
    this->cusca=cusca;
}

VietuitoareTerestre::VietuitoareTerestre(const VietuitoareTerestre& obj):Vietuitoare(obj)
{
    this->numarPicioare=obj.numarPicioare;
    this->coada=obj.coada;
    this->cusca=obj.cusca;
}

VietuitoareTerestre& VietuitoareTerestre::operator=(const VietuitoareTerestre& obj)
{
    if(this!= &obj)
    {
        Vietuitoare::operator=(obj);
        this->numarPicioare=obj.numarPicioare;
        this->coada=obj.coada;
        this->cusca=obj.cusca;
    }
    return *this;
}
//istream& citire(istream& in)
//{
//    this->Vietuitoare::citire(in) ;
//    ///in>>(Vietuitoare&)obj;
//    cout<<"Introduceti numarul de membre: ";
//    in>>obj.numarPicioare;
//    cout<<"Introduceti 1 daca are coada sau 0 in caz contrar\n";
//    in>>obj.coada;
//    cout<<"Introduceti 1 daca are nevoie de cusca sau 0 in caz contrar\n";
//    in>>obj.cusca;
//    return in;
//}
// ostream& afisare(ostream& out) const
//{
//    this->Vietuitoare::afisare(out);
//    ///out<<(Vietuitoare&)obj;
//    out<<"Numar membre: "<<obj.numarPicioare<<endl;
//    if(obj.coada)
//    out<<"Animalul are coada."<<endl;
//    else
//    out<<"Animalul nu are coada."<<endl;
//    if(obj.cusca)
//    out<<"Animalul are nevoie de cusca."<<endl;
//    else
//    out<<"Animalul nu are nevoie de cusca."<<endl;
//    return out;
//}


VietuitoareAcvatice::VietuitoareAcvatice():Vietuitoare()
{
    this->coada2=false;
    this->inmultire="anonima";
    this->solzi=false;
}
VietuitoareAcvatice::VietuitoareAcvatice(string nume,int aniDurataViata,string culoare,const list<Hrana>& listaHrana,float cost,bool coada,string inmultire,bool solzi):
    Vietuitoare(nume,aniDurataViata,culoare,listaHrana,cost)
{
    this->coada2=coada;
    this->inmultire=inmultire;
    this->solzi=solzi;
}
VietuitoareAcvatice::VietuitoareAcvatice(const VietuitoareAcvatice& obj):Vietuitoare(obj)
{
    this->coada2=obj.coada2;
    this->inmultire=obj.inmultire;
    this->solzi=obj.solzi;
}
VietuitoareAcvatice& VietuitoareAcvatice::operator=(const VietuitoareAcvatice& obj)
{
    if(this!= &obj)
    {
        Vietuitoare::operator=(obj);
        this->coada2=obj.coada2;
        this->inmultire=obj.inmultire;
        this->solzi=obj.solzi;
    }
    return *this;
}
//istream& citire(istream& in)
//{
//    this->Vietuitoare::citire(in) ;
//   /// in>>(Vietuitoare&)obj;
//    cout<<"Introduceti 1 daca are coada sau 0 in caz contrar\n";
//    in>>obj.coada;
//    cout<<"Introduceti tipul de inmultire: ";
//    in>>obj.inmultire;
//    cout<<"Introduceti 1 daca are solzi sau 0 in caz contrar\n";
//    in>>obj.solzi;
//    return in;
//}
//ostream& afisare(ostream& out) const
//{
//    this->Vietuitoare::afisare(out);
//    ///out<<(Vietuitoare&)obj;
//    if(obj.coada)
//    out<<"Animalul are coada."<<endl;
//    else
//    out<<"Animalul nu are coada."<<endl;
//    out<<"Tipul de inmultire este: "<<obj.inmultire<<endl;
//    if(obj.solzi)
//    out<<"Animalul are solzi."<<endl;
//    else
//    out<<"Animalul nu are solzi."<<endl;
//    return out;
//}

















int pericol( list<Hrana> hranuri,vector<Vietuitoare*>animale)
{
//    for(int k=0;k<hranuri.size();k++)
//    for(int j=0; j<animale.size(); j++)
//    if(hranuri[k].gettnume()==animale[j]->getnume())
//    {
//        maxi++;
//       // hranuri=animale[j]->getlistaHrana();
//        copy(animale[j]->getlistaHrana().begin(), animale[j]->getlistaHrana().end(), back_inserter(hranuri));
//        pericol(hranuri,animale);
//    }
//    return maxi;
    for (auto it = hranuri.begin(); it != hranuri.end(); ++it)
        for(int j=0; j<animale.size(); j++)
            if((*it).gettnume()==animale[j]->getnume())
            {
                maxi++;
                //hranuri=animale[j]->getlistaHrana();
                // cout<<"lkas"<<endl;
                //copy(animale[j]->getlistaHrana().begin(), animale[j]->getlistaHrana().end(), back_inserter(hranuri));
                pericol(animale[j]->getlistaHrana(),animale);
            }
    return maxi;
}
template <class T>
float pret_nou(T obj)
{ float pret;
    list<Hrana>hranuri=obj.getlistaHrana();
                        auto pretul = hranuri.begin();
                if(typeid(obj)==typeid(VietuitoareTerestre))
                        pret=obj.getcost()+200+(*pretul).getcost();
                else
                    pret=obj.getcost()+250+(*pretul).getcost();
                return pret;

}


template <class T>
bool more_hungry(T a, T b)
{

    return a>b;


}

template<class T1, class T2>
bool more_hungry(T1 obj1, T2 obj2)
{


    return  obj1.getlistaHrana().size()>obj2.getlistaHrana().size();


}









class Primire
{
    static Primire *obiect;
    map<string, float> clienti;
    Primire()=default;
    Primire(const Primire&)=delete;
    static int nrOfInstance;
    vector<set<string>> animale_cumparate;
public:
    static Primire* getInstance()
    {
        nrOfInstance++;
        if(!obiect)
            obiect=new Primire();


        return obiect;
    }
    map<string,float> getClienti()
    {
        return this->clienti;
    }

    vector<set<string>> getAnimale() const
    {
        return this->animale_cumparate;
    }
    void Bine_ati_venit()
    {

        cout << "Introduceti numarul de clienti: ";
        int persoane;
        cin>>persoane;

        try
        {
            if(!persoane)
                throw -1;
            cout << "Numele persoanelor vor trebui introduse in ordine alfabetica!!\n";
            // int persoane1=persoane;
            cin.get();
            while(persoane)
            {


                cout << "Introduceti numele dumneavoastra: ";
                string client;

                getline(cin,client);
                cout << "Introduceti bugetul dumneavoastra alocat pentru aceasta sesiune de cumparaturi: ";
                float buget;
                cin >> buget;
                clienti[client]=buget;

                int numar;
                cout << "Introduceti numarul de animalele pe care ati dori sa le cumparati: ";
                cin >> numar;

                cout << "Introduceti animalele pe care ati dori sa le cumparati: \n";
                set<string> animalute;
                string animal;
                cin.get();
                for(int i=0; i<numar; ++i)
                {

                    getline(cin,animal);

                    animalute.insert(animal);

                }
//      for( const auto& element : animalute) {
//        cout << element << " ";

//
//for (auto itr = animalute.begin(); itr != animalute.end(); itr++) {
//        cout << *itr << " ";

                //}
                animale_cumparate.push_back(animalute);
                persoane--;
//              for (const auto& set : animale_cumparate) {
//        for (const auto& element : set) {
//            cout << element << " ";
//        }
//        cout << endl;
//    }
            }


        }
        catch(int)
        {
            cout << "Nu vom avea clienti!\n";
        }
    }
    ~Primire()
    {
        nrOfInstance--;
        if(nrOfInstance==0)
            if(obiect)
                delete obiect;

    }
};



Primire* Primire::obiect=0;
int Primire::nrOfInstance=0;





int main()
{

    Amfibieni b;
    VietuitoareAcvatice acv;
    VietuitoareTerestre ter;
    list<Hrana>hranuri1;
    hranuri1.push_back(Hrana("sarpe",34));
    string nume3="camila";

    Amfibieni camila("camila",30,"maro",hranuri1,450,4,1,"pui",0);

//cout<<a;

//cout<<more_hungry(camila,acv)<<endl;
//cout<<more_hungry(acv,acv)<<endl;

    Primire *inceput=inceput->getInstance();
    // cout<<inceput->a<<endl<<inceput<<endl;
    //  inceput->a=5;
    inceput->Bine_ati_venit();
    map<string, float> new_clienti=inceput->getClienti();
//    for(auto it = new_clienti.begin();it != new_clienti.end(); it++)
//        cout<<it->first<< " " << it->second<<endl;


    vector<set<string>>animale_preferate=inceput->getAnimale();


//    for (const auto& set : animale_preferate) {
//        for (const auto& element : set) {
//            cout << element << " ";
//        }
//        cout << endl;
//    }
    // cout<<inceput->clienti[]


//    produsPerisabil pp;
//    cin>>pp;
//    cout<<pp;
//    produsNePerisabil pn;
//    cout<<pn;
//    cout<<pp.pret();
//    produs* p=&pp;
//    p=(produs*)&pn;
//   (*p).f();
//    produs* l=new produsNePerisabil;
//    cout<<(*l).pret()<<endl;

    //    Amfibieni b;
    //    cin>>b;
    //    cout<<b;
    //    Vietuitoare* a= &b;
    //    a->pret();
//    VietuitoareAcvatice a,b;
//   cin>>a;
//    b=a;
//    cout<<b;
//    b.pret();

    Vietuitoare* anim;

    anim=new VietuitoareAcvatice();




//anim=new Amfibieni();


//try{
//
//    if(typeid(*anim)==typeid(VietuitoareAcvatice) && typeid(*anim)!=typeid(VietuitoareTerestre) && typeid(*anim)!=typeid(Amfibieni))
//    {
// throw 1;
//
//    }
//   throw "eroare";
//
//
//}
//
//catch(int)
//{
//    cout<<anim->pret();
//    cout<<endl;
//}
//
//catch(...)
//{
//    cout<<"Eroare datorita unei clase abstracte"<<endl;
//}
    cout << "\n\n                                    Magazinul s-a deschis!\n\n                                    Vom adauga animale!\n\n\n";
    vector<Vietuitoare*>animale;
    bool adaug;
    cout<<"Pentru a adauga un animal introduceti 1 sau 0 in caz contrar\n";
    cin>>adaug;
    while(adaug)
    {



        cout << "Ce animal vreti sa adaugati?\n";
        cout << "Pentru animal terestru apasati 1\n";
        cout << "Pentru animal acvatic apasati 2\n";
        cout << "Pentru amfibian apasati 3\n";
        int cerere;
        cin >> cerere;
        switch(cerere)
        {
        case 1:
        {
            animale.push_back(new VietuitoareTerestre());
            cin>>*animale.back();

            break;
        }

        case 2:
        {
            animale.push_back(new VietuitoareAcvatice());
            cin>>*animale.back();
            break;
        }

        case 3:
        {
            animale.push_back(new Amfibieni());
            cin>>*animale.back();
            break;
        }
        }
        cout<<"Pentru a adauga un animal introduceti 1 sau 0 in caz contrar\n";
        cin>>adaug;
    }

    cout<<"Pentru a face modificari introduceti 1 sau 0 in caz contrar\n";
    cin>>adaug;
    while(adaug)
    {


        cout << "Pentru adaugarea unui animal apasati 1\n";
        cout << "Pentru stergerea unui animal apasati 2\n";
        int alegere;
        cin>>alegere;
        if(alegere==1)
        {
            cout <<"Ce animal vreti sa adaugati?\n";
            cout << "Pentru animal terestru apasati 1\n";
            cout << "Pentru animal acvatic apasati 2\n";
            cout << "Pentru amfibian apasati 3\n";
            int cerere;
            cin >> cerere;
            switch(cerere)
            {
            case 1:
            {
                animale.push_back(new VietuitoareTerestre());
               cin>>dynamic_cast<VietuitoareTerestre&>(*animale.back());


                break;
            }

            case 2:
            {
                animale.push_back(new VietuitoareAcvatice());
                cin>>*(dynamic_cast<VietuitoareAcvatice*>(animale.back()));
                break;
            }

            case 3:
            {
                animale.push_back(new Amfibieni());
                cin>>*(dynamic_cast<Amfibieni*>(animale.back()));
                break;
            }
            }
        }
        if(alegere==2)
        {
            cout<<"Introduceti animalul pe care vreti sa il stergeti: \n";
            string animal;
            cin.get();
            getline(cin,animal);
            for(int i=0; i<animale.size(); i++)
                if(animale[i]->getnume()==animal)
                    animale.erase(animale.begin()+i);

        }



        cout<<"Pentru a face modificari introduceti 1 sau 0 in caz contrar\n";
        cin>>adaug;



    }


    {
        // aici venim cu meniul singleton si map-ul pentru clienti
//            cout << "Introduceit numele dumneavoastra: ";
//            string client;
//            cin.get();
//            getline(cin,client);
//            cout << "Introduceti bugetul dumneavoastra alocat pentru aceasta sesiune de cumparaturi: ";
//            float buget;
//            cin >> buget;
//            clienti[client]=buget;
//            animale_cumparate.insert(client);
    }
// for(int i=0; i<animale.size(); i++)
//        cout<<*animale[i];

    cout << "Pentru a cumpara animalele preferate apasati 1 iar pentru a cumpara alte animale apasati 2.\n";
    int principal;
    cin>>principal;

    if(principal==2)
    {


        cout << "Cate animale cautati?\n";
        int alegeri;
        cin>>alegeri;
        try
        {
            if(!alegeri)
                throw animale;
        }
        catch(...)
        {
            cout << "Magazinul este exclusiv pentru cumparatori!\n";
            return 0;
        }
        int indice=0;
        int v[alegeri+1];
        for(int c=0; c<alegeri; ++c)
        {



            cout << "Ce fel de animal cautati?\n";
            cout << "Pentru animal terestru apasati 1\n";
            cout << "Pentru animal acvatic apasati 2\n";
            cout << "Pentru amfibian apasati 3\n";
            int alegere1;
            try
            {

                cin >> alegere1;
                if(alegere1>3 || alegere1<1)
                    throw 10.3;

            }
            catch(double)
            {
                cout << "Ati apasat gresit\n";
            }






            int cerere;

            int ok=0;
            while(!ok)
            {
                cout << "Dupa ce criteriu cautati animalul?\n";
                cout << "Dupa longevitate apasati 1\n";
                cout << "Dupa culoare apasati 2\n";
                cout << "Dupa cost minim apasati 3\n";
                cout << "Dupa gradul de periculozitate apasati 4\n";
                cout << "Dupa nume apasati 5\n";
                cout << "Pentru a reveni la meniul anterior apasati 6\n";
                cin >> cerere;
                switch(cerere)
                {
                    int animal;

                case 1:
                {
                    int viata=0;


                    for(int i=0; i<animale.size(); i++)
                        if(viata<animale[i]->getaniDurataViata() && animale[i]->tipe()==alegere1)
                        {
                            ok=1;
                            viata=animale[i]->getaniDurataViata();
                            animal=i;
                        }
                    if(ok)
                    {

                        v[indice++]=animal;
//cout<<*animale[animal];
                    }
                    if(!ok)
                        cout << "Cautarea a esuat, va rugam reincercati\n";
                    break;
                }

                case 2:
                {
                    cout<<"Introduceti culoarea: ";
                    ok=0;
                    string culoare;
                    cin.get();
                    getline(cin,culoare);
                    for(int i=0; i<animale.size(); i++)
                        if(animale[i]->getculoare()==culoare &&  animale[i]->tipe()==alegere1)
                        {
                            ok++;
                            animal=i;

                        }
                    if(ok>1)
                    {
                        cout<<"Alegeti unul dintre urmatoarele animale cu culoarea "<<culoare<<" :";
                        for(int i=0; i<animale.size(); i++)
                            if(animale[i]->getculoare()==culoare &&  animale[i]->tipe()==alegere1)
                                cout<<animale[i]->getnume()<<" ";
                        cout<<"."<<endl;
                        string alegere2;
                        getline(cin,alegere2);
                        for(int i=0; i<animale.size(); i++)
                            if(animale[i]->getnume()==alegere2 &&  animale[i]->tipe()==alegere1)
                            {


                                animal=i;
                            }

                    }
                    if(ok)
                    {
                        v[indice++]=animal;
                        //cout<<*animale[animal];
                    }
                    if(!ok)
                        cout << "Cautarea a esuat, va rugam reincercati\n";


                    break;
                }

                case 3:
                {

                    int cost=1000000;
                    for(int i=0; i<animale.size(); i++)
                        if(cost>animale[i]->getcost() && animale[i]->tipe()==alegere1)
                        {
                            ok=1;
                            cost=animale[i]->getcost();
                            animal=i;

                        }
                    if(ok)
                    {
                        v[indice++]=animal;

                        //cout<<*animale[animal];
                    }
                    if(!ok)
                        cout << "Cautarea a esuat, va rugam reincercati\n";

                    break;
                }
                case 4:
                {
                    list<Hrana> hranuri;
                    int maxi1=0;
                    string nume1="";
                    // cout<<animale.size()<<endl<<endl;
                    for(int i=0; i<animale.size(); i++)
                    {
                        maxi=0;
                        hranuri=animale[i]->getlistaHrana();
//               for(auto it = hranuri.begin();it != hranuri.end();it++)
//                    cout<<(*it).gettnume()<<" ";

                        // copy(animale[i]->getlistaHrana().begin(), animale[i]->getlistaHrana().end(), back_inserter(hranuri));
                        // cout<<animale[i]->tipe()<<" "<<animale[i]->getnume() <<" "<<pericol(hranuri,animale)<<endl;
                        maxi=pericol(hranuri,animale);

                        if(maxi1<maxi && animale[i]->tipe()==alegere1)
                        {
                            maxi1=maxi;
                            nume1=animale[i]->getnume();
                            //cout<<nume1<<" "<<maxi1<<endl;
                            animal=i;

                        }
                    }

                    if(maxi1)
                    {
                        ok=1;
                        v[indice++]=animal;
                    }
                    else
                    {
                        cout<<"Toate animalele sunt la fel de periculoase.\n";

                    }
                    if(!ok)
                        cout << "Cautarea a esuat, va rugam reincercati.\n";
                    break;

                }
                case 5:
                {

                    cout << "Introduceti animalul:\n";
                    string alegere2;
                    cin.get();
                    getline(cin,alegere2);
                    for(int i=0; i<animale.size(); i++)
                        if(animale[i]->getnume()==alegere2 &&  animale[i]->tipe()==alegere1)
                        {
                            ok=1;
                            v[indice++]=i;
                            animal=i;
                        }
//                 if(ok)
                    //              cout<<*animale[animal];
                    if(!ok)
                        cout << "Cautarea a esuat, va rugam reincercati.\n";
                    break;
                }
                case 6:
                {
                    ok=1;
                    c--;
                }
                }

                //for(int i=0; i<animale.size(); i++)
                //   cout<<*animale[i];

            }
        }
        //for(int i=0;i<indice;++i)
        //  cout<<v[i]<<endl;
        float suma=0;
        for(int i=0; i<indice; ++i)
        {


            suma+=animale[v[i]]->pret();
            cout<<endl;
        }

        if(alegeri)
            cout<<"Pretul total pentru animale, hrana si accesorii este: "<<suma;
    }
    else if (principal==1)
    {
        int v[100];
        int indice=0;
        int iterar=0;
        bool faliment=false;
        int ok;

        for(auto it = new_clienti.begin(); it != new_clienti.end(); it++)
        {
            ///cout<<it->first<<endl;
            faliment=false;
            float buget=it->second;
            indice=0;
            ok=0;
            for(auto it2 = animale_preferate[iterar].begin(); it2 != animale_preferate[iterar].end(); it2++)
            {


                string alegere2=*it2;
                //    for (const auto& set : animale_preferate) {
//        for (const auto& element : set) {
//            cout << element << " ";
//        }


//                cin.get();
//            getline(cin,alegere2);
//alegere2=i;
                for(int i=0; i<animale.size(); i++)

                    if(animale[i]->getnume()==alegere2 )
                    {
                        ok=1;
                        list<Hrana>hranuri=animale[i]->getlistaHrana();
                        auto pretul = hranuri.begin();
                        if((typeid((*animale[i]))==typeid(VietuitoareTerestre) && buget<(animale[i]->getcost()+200+(*pretul).getcost()))|| buget<(animale[i]->getcost()+250+(*pretul).getcost()) )
                            faliment=true;
                        // if(typeid((*animale[i]))==typeid(VietuitoareTerestre))
                        // try{


                        if(typeid((*animale[i]))==typeid(VietuitoareTerestre) && buget>=(animale[i]->getcost()+200+(*pretul).getcost()))
                        {
                            v[indice++]=i;
                            buget-=(animale[i]->getcost()+200+(*pretul).getcost());
                            //break;
                        }
                        //  throw "eroare";
                        //}
                        else if (buget>=(animale[i]->getcost()+250+(*pretul).getcost()))
                        {
                            v[indice++]=i;
                            buget-=(animale[i]->getcost()+250+(*pretul).getcost());
                        }
                        break;
                    }



            }
            try
            {
                if(!ok)
                    throw 10;
                if(ok)
                    throw true;
            }
            catch(int)
            {
                cout << "\nAnimalele preferate ale domnului/doamnei "<<it->first<<" nu se gasesc in magazinul nostru.\n\n\n";
            }
            catch(bool)
            {

                try
                {
                    if(faliment)
                        throw "faliment error";
                    else
                    {
                        float suma=0;
                        for(int i=0; i<indice; ++i)
                        {


                            suma+=animale[v[i]]->pret();
                            cout<<endl;
                        }

                        cout << "Pentru domnul/doamna "<<it->first<<" pretul total pentru animale, hrana si accesorii este: "<<suma<<endl;
                    }
                }
                catch(const char*)
                {
                    cout << "Buget insuficient pentru domnul/doamna "<<it->first<<endl;
                }




            }
            iterar++;



        }
    }
}

/// - cerinte suplimentare folosire: map ( cheie client: buget disponibil ) , lista ( pentru vectorul animale ) , set ( pentru a tine minte animalele cumparate, nu vom avea voie sa cumparam un animal de 2 ori )
///, Meniu tip Singleton, metode template , try-catch ( spre exemplu cand pretul este 0 sau negativ, cand nu avem hrana la animal, si prin meniu, clinetul nu are bani ) , upcasting, downcasting
/// citire nume clienti , citire suma de bani ( folosind map )
/// supra-incarcarea operatorilor <,> pentru clase
/**
1
1
leu
20
galben
1200
1
girafa
500
1
leopard
700
0
4
1
1
1
2
balena
40
albastra
10000
1
plancton
20
0
1
pui
0
1
3
broasca
9
verde
40
1
musca
4.5
1
molusca
4
0
4
0
matase
0
1
1
girafa
30
galben
5200
1
lacuste
10.4
0
4
1
0
1
1
lacuste
20
verde
12
1
furnica
5
0
4
1
1
1
1
sarpe
120
galben
1000
1
leu
500
1
pui
70
0
0
1
1
1
3
crocodil
120
verde
1200
1
sarpe
500
1
leopard
700
0
4
1
1
0
0

**/
