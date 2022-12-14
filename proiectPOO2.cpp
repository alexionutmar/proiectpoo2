//magazin alimentar
#include<iostream>
#pragma warning (disable:4996)
#include <string>
#include <vector>

using namespace std;

enum tipProd{
    LACTATE=1, FRUCTE=2, CARNE=3, BAUTURI=4, ALTELE=5
};

enum CALIF{
    CONTABIL=1, MANAGER=2, DIRECTOR=3
};

enum tipSoc{
    SA=1, SRL=2, SCA=3, SCS=4, SNC=5, PFA=6
};

class IFile
{
public:
    virtual void writeToFile(fstream& f) = 0;
    virtual void readFromFile(fstream& f) = 0;
};

class Alimentara{
private:
    tipSoc tipSocietate;
    char* denumire;
    bool platitoareTVA;
    int zileVanzareLuna;
    float* incasari;
    float capitalSocial;
    static int nrAlimentare;

public:
    Alimentara() {
        //constructor fara parametri
        nrAlimentare++;
        this->tipSocietate = tipSoc::SRL;
        this->denumire = new char[strlen("NA") + 1];
        strcpy(this->denumire, "NA");
        this->platitoareTVA = false;
        this->zileVanzareLuna=0;
        this->incasari = NULL;
        this->capitalSocial=0;
    }

    Alimentara(tipSoc tipSocietate, char* denumire, bool platitoareTVA,int zileVanzareLuna, float* incasari, float capitalSocial){
        //constructor cu toti parametrii
        nrAlimentare++;
        this->tipSocietate=tipSocietate;
        if(strlen(denumire)>1){
            this->denumire=new char(strlen(denumire));
            strcpy(this->denumire, denumire);
        }
        this->platitoareTVA=platitoareTVA;
        if(zileVanzareLuna>0&&zileVanzareLuna<32){
            this->zileVanzareLuna=zileVanzareLuna;
        }
        if (incasari!=NULL) {
            this->incasari=new float [this->zileVanzareLuna];
            for(int i=0;i<zileVanzareLuna;i++){
                this->incasari[i]=incasari[i];
            }
        }
        if(capitalSocial>0){
            this->capitalSocial=capitalSocial;
        }
    }

    Alimentara(const Alimentara& s) {
        //constructor de copiere
        nrAlimentare++;
        this->tipSocietate = s.tipSocietate;
        this->denumire = new char(strlen(s.denumire) );
        strcpy(this->denumire, s.denumire);
        this->platitoareTVA = s.platitoareTVA;
        this->zileVanzareLuna = s.zileVanzareLuna;
        this->incasari = new float[this->zileVanzareLuna];
        for (int i = 0; i < this->zileVanzareLuna; i++) {
            this->incasari[i] = s.incasari[i];
        }
        this->capitalSocial=s.capitalSocial;
    }

    Alimentara& operator=(const Alimentara& a){
        //operatorul = pentru alimentara
        if(this!=&a){
            this->tipSocietate=a.tipSocietate;
            if(strlen(a.denumire)>1){
                if(this->denumire!=NULL) delete[]this->denumire;
                this->denumire=new char(strlen(a.denumire));
                strcpy(this->denumire, a.denumire);
            }
            this->platitoareTVA=a.platitoareTVA;
            if(a.zileVanzareLuna>0&&a.zileVanzareLuna<32){
                this->zileVanzareLuna=a.zileVanzareLuna;
            }
            if(a.incasari!=NULL){
                if(this->incasari!=NULL) delete[]this->incasari;
                this->incasari=new float [this->zileVanzareLuna];
                for(int i=0;i<this->zileVanzareLuna;i++){
                    this->incasari[i]=a.incasari[i];
                }
            }
            if(capitalSocial>0){
                this->capitalSocial=a.capitalSocial;
            }
            return* this;
        }
    }

    ~Alimentara(){
        //destructor
        delete[]this->denumire;
        delete[]this->incasari;
        nrAlimentare--;
    }

    friend ostream& operator<<(ostream& out, Alimentara a){
        //operatorul <<
        out<<endl;
        string sc;
        if(a.tipSocietate==1){sc="SA";}
        else if(a.tipSocietate==2){sc="SRL";}
        else if(a.tipSocietate==3){sc="SCA";}
        else if(a.tipSocietate==4){sc="SCS";}
        else if(a.tipSocietate==5){sc="SNC";}
        else if(a.tipSocietate==6){sc="PFA";}
        out<<"\nAlimentara este o societate comerciala de tip: "<<sc<<endl;
        out<<"Denumirea acesteia este: "<<a.denumire<<endl;
        string tva;
        if(a.platitoareTVA==1){tva="PLATITOARE";}
        else if(a.platitoareTVA==0){tva="NEPLATITOARE";}
        out<<"Statusul acesteia de platitoare de TVA este: "<<tva<<endl;
        out<<"Alimentara a fost deschisa in "<<a.zileVanzareLuna<<" zile din luna"<<endl;
        for(int i=0;i<a.zileVanzareLuna;i++){
            out<<"In ziua "<<i+1<<" alimentara a avut incasari de "<<a.incasari[i]<<" lei,\t";
        }
        out<<endl;
        out<<"Capitalul social al alimentarei este de "<<a.capitalSocial<<" lei"<<endl;
        return out;
    }

    friend istream& operator>>(istream& in, Alimentara& a){
        //operatorul >>
        cout<<"\nDati tipul de societate comerciala (SA=1, SRL=2, SCA=3, SCS=4, SNC=5, PFA=6): ";
        in >> (int&)a.tipSocietate;
        cout<<"Dati denumirea alimentarei: ";
        in.ignore();
        char den[100];
        in.getline(den, 100);
        a.setDenumire(den);
        cout<<"\nDati statusul de platitoare de TVA a alimentarei (0=NEPLATITOARE, 1=PLATITOARE): ";
        in>>a.platitoareTVA;
        cout<<"\nDati numarul de zile din luna in care alimentara a fost deschisa: ";
        in>>a.zileVanzareLuna;
        for(int i=0;i<a.zileVanzareLuna;i++){
            cout<<"\nDati incasarile alimentarei pentru ziua "<<i+1<<": ";
            in>>a.incasari[i];
        }
        cout<<"\nDati capitalul social al alimentarei: ";
        in>>a.capitalSocial;
        return in;
    }

    const float operator[](int zi)const{
        //returneaza incasarile dintr-o anumita zi a lunii, index-ul este ziua-1
        return this->incasari[zi-1];
    }

    Alimentara operator+(float x){
        //operatorul +
        Alimentara a=*this;
        a.capitalSocial=this->capitalSocial+x;
        return a;
    }

    Alimentara operator-(float x){
        //operatorul -
        if(x<this->capitalSocial) {
            Alimentara a = *this;
            a.capitalSocial -= x;
            return a;
        }
    }

    Alimentara& operator++(){
        //operator ++ preincrementare
        float* inc = new float[this->zileVanzareLuna+1];
        for(int i=0;i<this->zileVanzareLuna;i++){
            inc[i]=this->incasari[i];
        }
        inc[this->zileVanzareLuna]=0;
        this->incasari=inc;
        this->zileVanzareLuna++;
        return *this;
    }

    Alimentara& operator++(int){
        //operator ++ postincrementare
        Alimentara a=*this;
        float* inc= new float[this->zileVanzareLuna+1];
        for(int i=0;i<this->zileVanzareLuna;i++){
            inc[i]=this->incasari[i];
        }
        inc[this->zileVanzareLuna]=0;
        this->zileVanzareLuna++;
        this->incasari=inc;

        return a;
    }

    bool operator>=(Alimentara a){
        return this->capitalSocial>=a.capitalSocial;
    }

    bool operator==(Alimentara a){
        //operator de comparatie
        return(this->platitoareTVA==a.platitoareTVA)&&
              (this->zileVanzareLuna==a.zileVanzareLuna)&&
              (this->capitalSocial==a.capitalSocial);
    }

    string getTipulSocietatii(){
        string sc;
        if(this->tipSocietate==1){sc="SA";}
        else if(this->tipSocietate==2){sc="SRL";}
        else if(this->tipSocietate==3){sc="SCA";}
        else if(this->tipSocietate==4){sc="SCS";}
        else if(this->tipSocietate==5){sc="SNC";}
        else if(this->tipSocietate==6){sc="PFA";}
        return sc;}

    char* getDenumire(){return this->denumire;}

    string getPlataTVA(){
        string tva;
        if(this->platitoareTVA==1){tva="PLATITOARE";}
        else if(this->platitoareTVA==0){tva="NEPLATITOARE";}
        return tva;}

    int getZileVanzare(){return this->zileVanzareLuna;}

    float* getIncasari(){return this->incasari;}

    float getCapitalSocial(){return this->capitalSocial;}

    static int getNrAlimentare(){return Alimentara::nrAlimentare;}

    void setTipulSocietatii(tipSoc tipSocietate){
        this->tipSocietate=tipSocietate;
    }

    void setDenumire(char* denumire){
        if(strlen(denumire)>1) {
            delete[] this->denumire;
            this->denumire = new char(strlen(denumire));
            strcpy(this->denumire, denumire);
        }
    }

    void setPlataTVA(bool platitoareTVA){
        this->platitoareTVA=platitoareTVA;
    }

    void setZileVanzare(int zileVanzareLuna){
        if(zileVanzareLuna>0 && zileVanzareLuna<32){
            this->zileVanzareLuna=zileVanzareLuna;
        }
    }

    void setIncasari(int zileVanzareLuna, float* incasari){
        if(incasari!=NULL&& zileVanzareLuna>0 && zileVanzareLuna<32){
            this->incasari=new float [zileVanzareLuna];
            for(int i=0;i<zileVanzareLuna;i++){
                this->incasari[i]=incasari[i];
            }
        }
    }

    void setCapitalSocial(float capitalSocial){
        if(capitalSocial>0){
            this->capitalSocial=capitalSocial;
        }
    }
};

int Alimentara::nrAlimentare=0;

class Produs{
private:
    const int codProdus;
    char* denumire;
    int stocLunaCurenta[31];
    tipProd tipProdus=ALTELE;
    float pret=0;
    static int stocuriProd[];

public:
    Produs(int codProdus):codProdus(codProdus){
        //constructor cu un parametru
        stocuriProd[4]++;
        this->denumire= new char[strlen("NA")+1];
        strcpy(this->denumire, "NA");
        for(int i=0;i<31;i++){
            this->stocLunaCurenta[i]=0;
        }
    }

    Produs(int codProdus, char* denumire, int* stocLunaCurenta, tipProd tipProdus, float pret):codProdus(codProdus){
        //constructor cu toti parametrii
        if(strlen(denumire)>1){
            this->denumire=new char [strlen(denumire)];
            strcpy(this->denumire, denumire);
        }
        if(stocLunaCurenta!=NULL){
            for(int i=0;i<31;i++){
                this->stocLunaCurenta[i]=stocLunaCurenta[i];
            }
        }
        this->tipProdus=tipProdus;
        if(this->tipProdus==1){stocuriProd[0]++;}
        else if(this->tipProdus==2){stocuriProd[1]++;}
        else if(this->tipProdus==3){stocuriProd[2]++;}
        else if(this->tipProdus==4){stocuriProd[3]++;}
        else if(this->tipProdus==5){stocuriProd[4]++;}
        if(pret>0) this->pret=pret;
    }

    Produs(const Produs& p):codProdus(p.codProdus){
        //constructor de copiere
        this->denumire=new char [strlen(p.denumire)];
        strcpy(this->denumire, p.denumire);
        for(int i=0;i<31;i++){
            this->stocLunaCurenta[i]=p.stocLunaCurenta[i];}
        this->tipProdus=p.tipProdus;
        if(this->tipProdus==1){stocuriProd[0]++;}
        else if(this->tipProdus==2){stocuriProd[1]++;}
        else if(this->tipProdus==3){stocuriProd[2]++;}
        else if(this->tipProdus==4){stocuriProd[3]++;}
        else if(this->tipProdus==5){stocuriProd[4]++;}
        this->pret=p.pret;
    }

    Produs& operator=(const Produs& p){
        //operatorul = pentru produs
        if(this!=&p){
            if(strlen(p.denumire)>1){
                this->denumire=new char [strlen(p.denumire)];
                strcpy(this->denumire, p.denumire);
            }
            if(p.stocLunaCurenta!=NULL){
                for(int i=0;i<31;i++){
                    this->stocLunaCurenta[i]=p.stocLunaCurenta[i];
                }
            }
            //stergem din stocurile totale tipul vechi aferent
            if(this->tipProdus==1){stocuriProd[0]--;}
            else if(this->tipProdus==2){stocuriProd[1]--;}
            else if(this->tipProdus==3){stocuriProd[2]--;}
            else if(this->tipProdus==4){stocuriProd[3]--;}
            else if(this->tipProdus==5){stocuriProd[4]--;}
            //atribuim tipul nou de produs
            this->tipProdus=p.tipProdus;
            //adaugam in stocurile totale tipul de produs nou atribuit
            if(this->tipProdus==1){stocuriProd[0]++;}
            else if(this->tipProdus==2){stocuriProd[1]++;}
            else if(this->tipProdus==3){stocuriProd[2]++;}
            else if(this->tipProdus==4){stocuriProd[3]++;}
            else if(this->tipProdus==5){stocuriProd[4]++;}
            if(pret>0) this->pret=p.pret;
        }
        return* this;
    }

    friend ostream& operator<<(ostream& out, Produs p){
        //operatorul<<
        out<<"Codul produsului este: "<<p.codProdus<<endl;
        out<<"Denumirea produsului este: "<<p.denumire<<endl;
        for(int i=0;i<31;i++){
            out<<"In ziua "<<i+1<<" a alimentara a avut pe stoc "<<p.stocLunaCurenta[i]<<" buc.,\t";
        }
        string tip;
        if(p.tipProdus==1){tip="LACTATE";}
        else if(p.tipProdus==2){tip="FRUCTE";}
        else if(p.tipProdus==3){tip="CARNE";}
        else if(p.tipProdus==4){tip="BAUTURI";}
        else if(p.tipProdus==5){tip="ALTELE";}
        out<<"\nTipul produsului este: "<<tip;
        out<<"\nPretul acestui produs este de "<<p.pret<<" lei"<<endl;
        return out;
    }

    friend istream& operator>>(istream& in, Produs& p){
        //operatorul >>
        cout<<"\nDenumirea produslui este: ";
        in.ignore();
        char buffer [100];
        in.getline(buffer, 100);
        p.setDenumire(buffer);
        int stocaux[31];
        for(int i=0;i<31;i++){
            cout<<"\nStocul produsului in ziua "<<i+1<<" este: ";
            in>>stocaux[i];
        }
        for(int i=0;i<31;i++){
            p.stocLunaCurenta[i]=stocaux[i];
        }
        cout<<"\nTipul produsului (LACTATE=1, FRUCTE=2, CARNE=3, BAUTURI=4, ALTELE=5) este:";
        in>>(int&)p.tipProdus;
        cout<<"\nPretul produslui: ";
        float aux;
        in>>aux;
        p.setPret(aux);

        return in;
    }

    const int operator[](int zi){
        //returneaza stocul produslui dintr-o anumita zi a lunii
        return this->stocLunaCurenta[zi-1];
    }

    Produs operator+(int x){
        //operatorul +
        Produs p=*this;
        pret+=x;
        return p;
    }

    Produs operator-(int x) {
        //operatorul -
        if (x < this->pret) {
            Produs p = *this;
            p.pret -= x;
            return p;
        }
    }

    Produs& operator++(){
        for(int i=0;i<31;i++) {
            this->stocLunaCurenta[i]++;
        }
        return *this;
    }

    Produs operator++(int){
        Produs p=*this;
        for(int i=0;i<31;i++) {
            p.stocLunaCurenta[i]++;}
        return p;
    }

    bool operator>=(Produs p){
        return this->pret>=p.pret;
    }

    bool operator==(Produs p){
        return (this->tipProdus==p.tipProdus)&&
               (this->pret==p.pret)&&
               (this->codProdus==p.codProdus);
    }

    ~Produs(){
        delete[] this->denumire;
        //daca produsul se sterge, il sergem si din stocuri
        if(this->tipProdus==1){stocuriProd[0]--;}
        else if(this->tipProdus==2){stocuriProd[1]--;}
        else if(this->tipProdus==3){stocuriProd[2]--;}
        else if(this->tipProdus==4){stocuriProd[3]--;}
        else if(this->tipProdus==5){stocuriProd[4]--;}
    }

    static int* getStocuriProduse(){return Produs::stocuriProd;}

    int getCodProdus(){return this->codProdus;}

    char* getDenumireProdus(){return this->denumire;}

    int* getStocCurent(){return this->stocLunaCurenta;}

    string getTipProdus(){
        string tip;
        if(this->tipProdus==1){tip="LACTATE";}
        else if(this->tipProdus==2){tip="FRUCTE";}
        else if(this->tipProdus){tip="CARNE";}
        else if(this->tipProdus){tip="BAUTURI";}
        else if(this->tipProdus){tip="ALTELE";}
        return tip;}

    float getPret(){return this->pret;}

    float setDenumire(char* denumire){
        if(strlen(denumire)>1) {
            delete[] this->denumire;
            this->denumire=new char[strlen(denumire)];
            strcpy(this->denumire, denumire);
        }
    }

    float setStocCurent(int ziLuna, float stocZi){
        //modifica stocul dintr-o anumita zi a lunii
        if(ziLuna>0&&ziLuna<32&&stocLunaCurenta!=NULL){
            for(int i=0;i<31;i++){
                this->stocLunaCurenta[ziLuna-1]=stocZi;
            }
        }
    }

    float setTipProdus(tipProd tipProdus){
        //stergem tipul vechi de produs din stocul de produse, pentru ca il schimbam
        if(this->tipProdus==1){stocuriProd[0]++;}
        else if(this->tipProdus==2){stocuriProd[1]--;}
        else if(this->tipProdus==3){stocuriProd[2]--;}
        else if(this->tipProdus==4){stocuriProd[3]--;}
        else if(this->tipProdus==5){stocuriProd[4]--;}

        this->tipProdus=tipProdus; //ia valoarea noua tipului de produs
        //adaugam valoarea noua la stocul de produse
        if(this->tipProdus==1){stocuriProd[0]++;}
        else if(this->tipProdus==2){stocuriProd[1]++;}
        else if(this->tipProdus==3){stocuriProd[2]++;}
        else if(this->tipProdus==4){stocuriProd[3]++;}
        else if(this->tipProdus==5){stocuriProd[4]++;}
    }

    void setPret(float pret){
        if(pret>0){
            this->pret = pret;
        }
    }
};

int Produs::stocuriProd[5]={0,0,0,0,0}; //[0]=lactate, [1]=fructe,...

class Angajat{
private:
    const string cnp;
    char* nume;
    char* prenume;
    int varsta;
    char* gen;
    int vechimeAni;
    int oreLucrateLuna[31];
    float salariu;
    static int nrAngajati;

public:

    Angajat(string cnp):cnp(cnp){
        //constructor cu un parametru
        this->nume=new char(strlen("Anonim")+1);
        strcpy(this->nume, "Anonim");
        this->prenume=new char(strlen("Anonim")+1);
        strcpy(this->prenume, "Anonim");
        this->varsta=0;
        this->gen=new char[strlen("NA")+1];
        strcpy(this->gen, "NA");
        this->vechimeAni=0;
        for(int i=0;i<31;i++)
            this->oreLucrateLuna[i]=0;
        this->salariu=0;
        nrAngajati++;
    }

    Angajat(string cnp,char* nume, char* prenume, int varsta, char* gen, int vechimeAni, int* oreLucrateLuna, float salariu):cnp(cnp){
        //constructor cu toti parametrii
        if(strlen(nume)>1){
            this->nume= new char(strlen(nume));
            strcpy(this->nume, nume);
        }
        if(strlen(prenume)>1){
            this->prenume= new char(strlen(prenume));
            strcpy(this->prenume, prenume);
        }
        if(varsta>0&&varsta<100){this->varsta=varsta;}
        if(strlen(gen)>1){
            this->gen= new char(strlen(gen));
            strcpy(this->gen, gen);
        }
        if(vechimeAni<100){this->vechimeAni=vechimeAni;}
        if(oreLucrateLuna!=NULL){
            for(int i=0;i<31;i++){
                this->oreLucrateLuna[i]=oreLucrateLuna[i];
            }
        }
        if(salariu>0){this->salariu=salariu;}
        nrAngajati++;
    }

    Angajat(const Angajat& a):cnp(a.cnp){
        //constructor de copiere
        this->nume= new char(strlen(a.nume));
        strcpy(this->nume, a.nume);
        this->prenume= new char(strlen(a.prenume));
        strcpy(this->prenume, a.prenume);
        this->varsta=a.varsta;
        this->gen= new char(strlen(a.gen));
        strcpy(this->gen, a.gen);
        this->vechimeAni=a.vechimeAni;
        for(int i=0;i<31;i++){
            this->oreLucrateLuna[i]=a.oreLucrateLuna[i];}
        this->salariu=a.salariu;
        nrAngajati++;
    }

    ~Angajat(){
        //destructor
        delete[] this->nume;
        delete[] this->prenume;
        delete[] this->gen;
        nrAngajati--;
    }

    Angajat& operator=(const Angajat& a){
        //operatorul =
        if(this!=&a) {
            if (strlen(nume) > 1) {
                delete[]this->nume;
                this->nume = new char(strlen(a.nume));
                strcpy(this->nume, a.nume);
            }
            if (strlen(prenume) > 1) {
                delete[] this->prenume;
                this->prenume = new char(strlen(a.prenume));
                strcpy(this->prenume, a.prenume);
            }
            if (a.varsta > 0 && a.varsta < 100) { this->varsta = a.varsta; }
            if (strlen(gen) > 1) {
                delete[] this->gen;
                this->gen = new char(strlen(a.gen));
                strcpy(this->gen, a.gen);
            }
            if (a.vechimeAni < 100) { this->vechimeAni = a.vechimeAni; }
            if (a.oreLucrateLuna != NULL) {
                for (int i = 0; i < 31; i++) {
                    this->oreLucrateLuna[i] = 0;
                }
                for (int i = 0; i < 31; i++) {
                    this->oreLucrateLuna[i] = a.oreLucrateLuna[i];
                }
            }
            if (a.salariu > 0) { this->salariu = a.salariu; }
        }
        return *this;
    }

    friend  ostream& operator <<(ostream& out, Angajat a){
        //operatorul <<
        out<<"\nCNP-ul angajatului: "<<a.cnp<<endl;
        out<<"Numele angajatului: "<<a.nume<<endl;
        out<<"Prenumele angajatului: "<<a.prenume<<endl;
        out<<"Varsta angajatului: "<<a.varsta<<" ani "<<endl;
        out<<"Genul angajatului: "<<a.gen<<endl;
        out<<"Vechimea angajatului in firma: "<<a.vechimeAni<<" ani"<<endl;
        for(int i=0;i<31;i++){
            out<<"Angajatul a lucrat in ziua "<<i+1<<" a lunii "<<a.oreLucrateLuna[i]<<" ore,\t";
        }
        out<<"\nSalariul angajatului este de: "<<a.salariu<<" lei"<<endl;
        return out;

    }

    friend istream& operator>>(istream& in, Angajat& a){
        //operatorul >>
        cout<<"\nNumele angajatului: ";
        in.ignore();
        char buffer[100];
        in.getline(buffer, 100);
        a.setNume(buffer);
        cout<<"\nPrenumele angajatului: ";
        in.ignore();
        char buffer2[100];
        in.getline(buffer2, 100);
        a.setPrenume(buffer2);
        int aux;
        cout<<"\nVarsta angajatului: ";
        in>>aux;
        a.setVarsta(aux);
        char buffer3[20];
        cout<<"\nGenul angajatului este: ";
        in>>buffer3;
        a.setGen(buffer3);
        int aux2;
        cout<<"\nAngajatul are o vechime in firma in ani de: ";
        in>>aux2;
        a.setVechimeAni(aux2);
        int aux3[31];
        for(int i=0;i<31;i++){
            cout<<"\nIn ziua "<<i+1<<" a lunii a lucrat un numar de ore de: ";
            in>>aux3[i];
        }
        for(int i=0;i<31;i++){
            a.oreLucrateLuna[i]=aux3[i];
        }
        float aux4;
        cout<<"\nAngajatul are un salariu de: ";
        in>>aux4;
        a.setSalariu(aux4);
        return in;
    }

    const int operator[](int zi){
        //returneaza numarul de ore lucrate de un angajat dintr-o anumita zi a lunii
        return this->oreLucrateLuna[zi-1];
    }

    Angajat operator+(int x){
        //operatorul +
        Angajat a=*this;
        a.vechimeAni+=x;
        return a;
    }

    Angajat operator-(int x){
        //operatorul
        if(x<this->vechimeAni) {
            Angajat a = *this;
            this->vechimeAni -= x;
            return a;
        }
    }

    Angajat& operator++(){
        //operator ++ preincrementare
        this->varsta++;
        return *this;
    }

    Angajat operator++(int){
        //operator++ postincrementare
        Angajat a = *this;
        this->varsta++;
        return a;
    }

    bool operator>=(Angajat a){
        return this->varsta>=a.varsta;
    }

    bool operator==(Angajat a){
        return (this->cnp==a.cnp);
    }

    static int getNrAngajati(){return Angajat::nrAngajati;}

    const string getCNP(){return this->cnp;}

    char* getNume(){return this->nume;}

    char* getPrenume(){return this->prenume;}

    int getVarsta(){return this->varsta;}

    char* getGen(){return this->gen;}

    int getVechimeAni(){return this->vechimeAni;}

    int* getOreLucrateLuna(){return this->oreLucrateLuna;}

    float getSalariu(){return this->salariu;}

    void setNume(char* nume){
        if(strlen(nume)>1) {
            delete[] this->nume;
            this->nume= new char(strlen(nume));
            strcpy(this->nume, nume);
        }
    }

    void setPrenume(char* prenume){
        if(strlen(prenume)>1) {
            delete[] this->prenume;
            this->prenume= new char(strlen(prenume));
            strcpy(this->prenume, prenume);
        }
    }

    void setVarsta(int varsta){
        if(varsta>0&& varsta<100){
            this->varsta=varsta;
        }
    }

    void setGen(char* gen){
        if(strlen(gen)>1){
            delete[]this->gen;
            this->gen=new char[strlen(gen)];
            strcpy(this->gen, gen);
        }
    }

    void setVechimeAni(int vechimeAni){
        if(vechimeAni<100){this->vechimeAni=vechimeAni;}
    }

    void setOreLucrateLuna(int zi, int oreLucrate){
        //modifica cate ore s-au lucrat intr-o anumita zi din luna
        if(zi>0&&zi<32&&oreLucrate>0&&oreLucrate<24){
            for(int i=0;i<31;i++){
                this->oreLucrateLuna[zi-1]=oreLucrate;
            }
        }
    }

    void setSalariu(float salariu){
        if(salariu>0){this->salariu=salariu;}
    }

};

int Angajat::nrAngajati=0;

class AngajatStudiiSup: public Angajat{
    CALIF calificare;
    int majorari[12]; //majorarile salariale procentuale din ultimele 12 luni
    int aniStudiiSup;
    static int nrAngStudiiSup;
public:
    AngajatStudiiSup(string cnp): Angajat(cnp){
        //constructor fara parametri
        this->calificare=CALIF::MANAGER;
        for(int i=0;i<12;i++){
            this->majorari[i]=0;
        }
        this->aniStudiiSup=2;
        nrAngStudiiSup++;
    }

    AngajatStudiiSup(string cnp,char* nume, char* prenume, int varsta, char* gen, int vechimeAni, int* oreLucrateLuna, float salariu, CALIF calificare, int* majorari, int aniStudiiSup):Angajat(cnp,nume,prenume,varsta,gen,vechimeAni,oreLucrateLuna,salariu) {
        //constructor cu toti parametrii pentru angajati cu studii superioare
        nrAngStudiiSup++;
        this->calificare = calificare;
        if (majorari != NULL) {
            for (int i = 0; i < 12; i++) {
                this->majorari[i] = majorari[i];
            }
        }
        if(aniStudiiSup>1){this->aniStudiiSup=aniStudiiSup;}
    }

    AngajatStudiiSup(Angajat a, CALIF calificare, int* majorari, int aniStudiiSup):Angajat(a){
        //constructor cu 4 parametrii, angajat, calificare, majorarile salariale procentuale pe ultimele 12 luni
        nrAngStudiiSup++;
        this->calificare=calificare;
        if (majorari != NULL) {
            for (int i = 0; i < 12; i++) {
                this->majorari[i] = majorari[i];
            }
        }
        if(aniStudiiSup>1){this->aniStudiiSup=aniStudiiSup;}
    }

    AngajatStudiiSup(const AngajatStudiiSup& a):Angajat(a){
        //constructor de copiere angajat studii superioare
        nrAngStudiiSup++;
        this->calificare=a.calificare;
        if (majorari != NULL) {
            for (int i = 0; i < 12; i++) {
                this->majorari[i] = a.majorari[i];
            }
        }
        this->aniStudiiSup=a.aniStudiiSup;
    }

    AngajatStudiiSup& operator=(const AngajatStudiiSup& a){
        //operator = pentru angajati cu studii superioare
        this->Angajat::operator=(a);
        this->calificare=a.calificare;
        if (majorari != NULL) {
            for (int i = 0; i < 12; i++) {
                this->majorari[i] = a.majorari[i];
            }
        }
        this->aniStudiiSup=a.aniStudiiSup;
        return *this;
    }

    friend ostream& operator<<(ostream& out, AngajatStudiiSup angs){
        //operator<< pentru angajatul cu studii superioare
        out<<(Angajat)angs;
        string post;
        if(angs.calificare==1){post="CONTABIL";}
        else if(angs.calificare){post="MANAGER";}
        else if(angs.calificare){post="DIRECTOR";}
        out<<"Postul angajatului cu studii superioare este: "<<post<<endl;
        for(int i=0;i<12;i++){
            cout<<"In luna "<<i+1<<" salariul angajatului cu studii superioare a crescut cu "<<angs.majorari[i]<<"%, \t";
        }
        out<<"Angajatul a urmat programe de studii superioare timp de "<<angs.aniStudiiSup<<" ani"<<endl;
        return out;
    }

    friend istream& operator>>(istream& in, AngajatStudiiSup& angs){
        cout<<endl;
        in>>static_cast<Angajat&>(angs);
        cout<<"\nCalificarea angajatului (CONTABIL=1, MANAGER=2, DIRECTOR=3) este: ";
        CALIF aux;
        in>>(int&)aux;
        angs.setCalificare(aux);
        for(int i=0;i<12;i++){
            cout<<"\nIn luna "<<i+1<<" salariul angajatului a crescut cu un procent de: ";
            in>>angs.majorari[i];
        }
        cout<<"Dati numarul de ani de studii superioare: ";
        int stud;
        in>>stud;
        angs.setNrAniStudSup(stud);
        return in;
    }

    const int operator[](int luna){
        //returneaza majorarea salariala dintr-o anumita luna
        return this->majorari[luna-1];
    }

    AngajatStudiiSup operator+(int x){
        //operator +
        AngajatStudiiSup angs=*this;
        angs.aniStudiiSup+=x;
        return angs;
    }

    AngajatStudiiSup operator-(int x){
        //operator -
        if(x<this->aniStudiiSup) {
            AngajatStudiiSup angs = *this;
            angs.aniStudiiSup -= x;
            return angs;
        }
    }

    AngajatStudiiSup& operator++(){
        //operator++ preincrementare
        this->aniStudiiSup++;
        return *this;
    }

    AngajatStudiiSup operator++(int){
        //operator++ postincrementare
        AngajatStudiiSup angs=*this;
        this->aniStudiiSup++;
        return angs;
    }

    bool operator>=(AngajatStudiiSup angs){
        return this->aniStudiiSup>=angs.aniStudiiSup;
    }

    bool operator==(AngajatStudiiSup angs){
        return (this->calificare==angs.calificare)&&(this->aniStudiiSup);
    }

    ~AngajatStudiiSup(){
        //destructor pentru angajati cu studii superioare
        nrAngStudiiSup--;
    }

    string getCalificare(){
        string post;
        if(this->calificare==1){post="CONTABIL";}
        else if(this->calificare){post="MANAGER";}
        else if(this->calificare){post="DIRECTOR";}
        return post;
    }

    int* getMajorari(){return this->majorari;}

    int getNrAniStudSup(){return this->aniStudiiSup;}

    void setCalificare(CALIF calificare){ this->calificare=calificare;}

    void setMajorari(int luna, int majorare){
        //modifica majorarea salariala procentuala dintr-o anumita luna
        this->majorari[luna-1]=majorare;
    }

    void setNrAniStudSup(int aniStudiiSup){
        if(aniStudiiSup>1){
            this->aniStudiiSup=aniStudiiSup;
        }
    }
};

int AngajatStudiiSup::nrAngStudiiSup=0;

class Furnizor{
private:
    tipSoc tipSocietate;
    char* denumire;
    int zileLivrariLuna;
    float* combustibilPretZi;
    int nrTipuriProdLivrate;
    Produs** listaOferta;
    int** prodLivrate;
    static int nrFurnizori;
public:
    Furnizor(){
        //constructor fara parametri
        this->tipSocietate=tipSoc::PFA;
        this->denumire=new char[strlen("NA")+1];
        strcpy(this->denumire, "NA");
        this->zileLivrariLuna=0;
        this->combustibilPretZi= NULL;
        this->nrTipuriProdLivrate=0;
        this->listaOferta=NULL;
        this->prodLivrate=NULL;
        nrFurnizori++;
    }

    Furnizor(tipSoc tipSocietate, char* denumire, int zileLivrariLuna, float* combustibilPretZi, int nrTipuriProdLivrate, Produs** listaOferta, int** prodLivrate){
        //constructor cu toti parametrii
        this->tipSocietate=tipSocietate;
        if(strlen(denumire)>1){
            this->denumire= new char[strlen(denumire)];
            strcpy(this->denumire, denumire);
        }
        if(zileLivrariLuna>0&&zileLivrariLuna<32){this->zileLivrariLuna=zileLivrariLuna;}
        if(combustibilPretZi!=NULL){
            this->combustibilPretZi = new float [zileLivrariLuna];
            for(int i=0;i<this->zileLivrariLuna;i++){
                this->combustibilPretZi[i]=combustibilPretZi[i];
            }
        }
        this->nrTipuriProdLivrate=nrTipuriProdLivrate;
        this->listaOferta= new Produs * [this->nrTipuriProdLivrate];
        if(listaOferta!=NULL) {
            for (int i = 0; i < this->nrTipuriProdLivrate; i++) {
                this->listaOferta[i] = new Produs (*listaOferta[i]);
            }
        }
        if(prodLivrate!=NULL){
            this->prodLivrate= new int*[this->zileLivrariLuna];
            for(int i=0;i<this->zileLivrariLuna;i++){
                this->prodLivrate[i]= new int[this->nrTipuriProdLivrate];
            }
            for(int i=0;i<this->zileLivrariLuna;i++){
                for(int j=0;j<this->nrTipuriProdLivrate;j++)
                    this->prodLivrate[i][j]=prodLivrate[i][j];
            }
        }
        nrFurnizori++;
    }

    Furnizor(const Furnizor& f){
        //constructor de copiere
        this->tipSocietate=f.tipSocietate;
        this->denumire= new char[strlen(f.denumire)];
        strcpy(this->denumire, f.denumire);
        this->zileLivrariLuna=f.zileLivrariLuna;
        this->combustibilPretZi = new float[f.zileLivrariLuna];
        for(int i=0;i<this->zileLivrariLuna;i++) {
            this->combustibilPretZi[i] = f.combustibilPretZi[i];
        }
        this->nrTipuriProdLivrate=f.nrTipuriProdLivrate;
        this->listaOferta= new Produs * [this->nrTipuriProdLivrate];
        for(int i=0;i<this->nrTipuriProdLivrate;i++){
            this->listaOferta[i]= new Produs(*f.listaOferta[i]);
        }
        this->prodLivrate= new int*[this->zileLivrariLuna];
        for(int i=0;i<this->zileLivrariLuna;i++){
            this->prodLivrate[i]= new int[this->nrTipuriProdLivrate];
        }
        for(int i=0;i<this->zileLivrariLuna;i++){
            for(int j=0;j<this->nrTipuriProdLivrate;j++)
                this->prodLivrate[i][j]=f.prodLivrate[i][j];
        }
        nrFurnizori++;
    }

    Furnizor& operator=(const Furnizor& f){
        //operatorul = pentru furnizori
        if(this!=&f){
            this->tipSocietate=f.tipSocietate;
            if(strlen(f.denumire)>1 && this->denumire!=NULL){
                delete[]this->denumire;
                this->denumire= new char[strlen(f.denumire)];
                strcpy(this->denumire, f.denumire);
            }
            if(f.zileLivrariLuna>0 && f.zileLivrariLuna<32) this->zileLivrariLuna=f.zileLivrariLuna;
            if(f.combustibilPretZi!=NULL&& f.zileLivrariLuna>0 && f.zileLivrariLuna<32) {
                if(this->combustibilPretZi!=NULL) delete[]this->combustibilPretZi;
                this->combustibilPretZi= new float[this->zileLivrariLuna];
                for (int i = 0; i < 31; i++) {
                    this->combustibilPretZi[i] = f.combustibilPretZi[i];
                }
            }
            if(f.nrTipuriProdLivrate>0){this->nrTipuriProdLivrate=f.nrTipuriProdLivrate;}
            if(f.listaOferta!=NULL) {
                delete[] this->listaOferta;
                this->listaOferta= new Produs * [this->nrTipuriProdLivrate];

                for (int i = 0; i < this->nrTipuriProdLivrate; i++) {
                    this->listaOferta[i] = new Produs(*f.listaOferta[i]);
                }
            }
            if(f.prodLivrate!=NULL && this->prodLivrate!=NULL){
                for(int i=0;i<this->zileLivrariLuna;i++){
                    delete this->prodLivrate[i];
                }
                delete[]this->prodLivrate;
                this->prodLivrate= new int*[this->zileLivrariLuna];
                for(int i=0;i<this->zileLivrariLuna;i++){
                    this->prodLivrate[i]= new int[this->nrTipuriProdLivrate];
                }
                for(int i=0;i<this->zileLivrariLuna;i++){
                    for(int j=0;j<this->nrTipuriProdLivrate;j++)
                        this->prodLivrate[i][j]=f.prodLivrate[i][j];
                }
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, Furnizor& f){
        out<<endl;
        string sc;
        if(f.tipSocietate==1){sc="SA";}
        else if(f.tipSocietate==2){sc="SRL";}
        else if(f.tipSocietate==3){sc="SCA";}
        else if(f.tipSocietate==4){sc="SCS";}
        else if(f.tipSocietate==5){sc="SNC";}
        else if(f.tipSocietate==6){sc="PFA";}
        out<<"\nTipul societatii comeriale ale furnizorului (SA=1, SRL=2, SCA=3, SCS=4, SNC=5, PFA=5): "<<sc<<endl;
        out<<"Denumire furnizor: "<<f.denumire<<endl;
        out<<"Furnizorul a livrat produse in "<<f.zileLivrariLuna<<" zile din luna"<<endl;
        for(int i=0;i<f.zileLivrariLuna;i++){
            out<<"In ziua "<<i+1<<" a lunii furnizorul a platit pe combustibil "<<f.combustibilPretZi[i]<<" lei,\t";
        }
        out<<"\nFurnizorul livreaza "<<f.nrTipuriProdLivrate<<" tipuri produse"<<endl;
        for(int i=0;i<f.nrTipuriProdLivrate;i++){
            out<<"Tipul "<<i+1<<" de produs livrat este "<<(f.listaOferta[i]->getDenumireProdus())<<",\t";}
        out<<endl;
        for(int i=0;i<f.nrTipuriProdLivrate;i++){
            out<<"\nInformatii despre tipul "<<i+1<<" de produs:"<<endl;
            out<<(*f.listaOferta[i]);
            out<<endl;
        }

        for(int i=0;i<f.zileLivrariLuna;i++){
            out<<"\nIn ziua "<<i+1<<" furnizorul a livrat:\t ";
            for(int j=0;j<f.nrTipuriProdLivrate;j++) {
                out << f.getProdLivrate()[i][j] << " buc. din produsul de tip " << f.listaOferta[j]->getDenumireProdus()<<", ";
            }
        }
        out<<endl;
        return out;
    }

    friend istream &operator>>(istream& in, Furnizor& f){
        cout<<"\nTipul societatii furnizorului (SA=1, SRL=2, SCA=3, SCS=4, SNC=5, PFA=6): ";
        in>>(int&)f.tipSocietate;
        cout<<"\nDenumirea furnizorului: ";
        in.ignore();
        char buffer[100];
        in.getline(buffer, 100);
        f.setDenumire(buffer);
        cout<<"\nNumarul de zile din luna in care firma a operat: ";
        int zile;
        in>>zile;
        f.setZileLivrari(zile);
        for(int i=0;i<f.zileLivrariLuna;i++){
            cout<<"\nIn ziua "<<i+1<<" a lunii furnizorul a platit pe combustibil suma de: ";
            in>>f.combustibilPretZi[i];
        }
        cout<<"\nNumarul produselor pe care le livreaza furnizorul: ";
        int aux;
        in>>aux;
        f.setNrTipProdFurnizate(aux);
        if(f.listaOferta!=NULL) delete[] f.listaOferta;
        f.listaOferta = new Produs * [f.nrTipuriProdLivrate];
        //in>>static_cast<Angajat&>(angs);

        std::vector<std::shared_ptr<Produs>> produse;
        for(int i=0;i<f.nrTipuriProdLivrate;i++){
            std::shared_ptr<Produs> prod = std::make_shared<Produs>(i);
            in >> *prod;
            produse.push_back(prod);
        }

        std::for_each(produse.begin(), produse.end(), [&](const auto item) {
            cout << "Produsele introduse: " << *item;
        });

        /*for(int i=0;i<f.nrTipuriProdLivrate;i++){
            cout<<"\nProdusul de tip "<<i+1<<" : ";
        }*/



        /*
        char den[100];
        tipProd tip;
        float p;
        for(int i=0;i<f.nrTipuriProdLivrate;i++){
            //introducem in variabile auxiliare date de la tastatura pentru produsele din interiorul listei
            cout<<"Pentru produsul de tip "<<i+1<<" introduceti denumirea: ";
            in>>den;
            cout<<"tipul de produs (LACTATE=1, FRUCTE=2, CARNE=3, BAUTURI=4, ALTELE=5): ";
            in>>(int&)tip;
            cout<<"pretul: ";
            in>>p;
            cout<<endl;
        }
        for(int i=0;i<f.nrTipuriProdLivrate;i++){
            //in interiorul listei cu oferte am dereferentiat produsele pe rand si le am schimbat valorile cu ce am introdus
            //am folosit setteri pentru validari
            (*f.listaOferta[i]).setDenumire(den);
            (*f.listaOferta[i]).setTipProdus(tip);
            (*f.listaOferta[i]).setPret(p);
        }*/
/*
        for(int i=0;i<f.zileLivrariLuna;i++){
            for(int j=0;j<f.nrTipuriProdLivrate;j++) {
                cout << "\nIn ziua " << i + 1 << " pentru produsul de tip " << j + 1
                     << " au fost livrate un numar de bucati de: ";
                in >> f.prodLivrate[i][j];
            }
        }
        */

        for(int i=0;i<f.zileLivrariLuna;i++){
            cout<<"\nIn ziua "<<i+1<<" furnizorul a livrat un numar de bucati ";
            for(int j=0;j<f.nrTipuriProdLivrate;j++){
                cout<<" din produsul "<<f.listaOferta[j]->getDenumireProdus()<<" de: ";
                in>>f.prodLivrate[i][j];
            }
        }
        return in;
    }

    const float operator[](int zi){
        //returneaza valoarea combustibilului consumat intr-o anumita zi a lunii
        return this->combustibilPretZi[zi-1];
    }

    Furnizor operator+(int x){
        //operator +
        Furnizor f=*this;
        f.nrTipuriProdLivrate+=x;
        return f;
    }

    Furnizor operator-(int x){
        //operator -
        if(x<this->nrTipuriProdLivrate) {
            Furnizor f = *this;
            f.nrTipuriProdLivrate -= x;
            return f;
        }
    }

    Furnizor& operator++(){
        this->nrTipuriProdLivrate++;
        return *this;
    }

    const Furnizor operator++(int){
        Furnizor f=*this;
        this->nrTipuriProdLivrate++;
        return f;
    }

    bool operator>=(const Furnizor& f)const{
        return this->nrTipuriProdLivrate>=f.nrTipuriProdLivrate;
    }

    bool operator==(const Furnizor& f){
        return (this->tipSocietate==f.tipSocietate)&&
               (this->nrTipuriProdLivrate==f.nrTipuriProdLivrate);
    }

    ~Furnizor(){
        //destructor
        delete[] this->denumire;
        delete[] this->listaOferta;
        for(int i=0;i<this->zileLivrariLuna;i++){
            delete this->prodLivrate[i];
        }
        delete[]this->prodLivrate;
        nrFurnizori--;
    }

    string getTipSocFurnizor(){
        string sc;
        if(this->tipSocietate==1){sc="SA";}
        else if(this->tipSocietate==2){sc="SRL";}
        else if(this->tipSocietate==3){sc="SCA";}
        else if(this->tipSocietate==4){sc="SCS";}
        else if(this->tipSocietate==5){sc="SNC";}
        else if(this->tipSocietate==6){sc="PFA";}
        return sc;}

    char* getDenumire(){return this->denumire;}

    int getNrZileLivrari()const {return this->zileLivrariLuna;}

    float* getcombustibilPretZi(){return this->combustibilPretZi;}

    int getNrTipProdFurnizate()const{return this->nrTipuriProdLivrate;}

    Produs** getProdOferta(){return this->listaOferta;}

    int** getProdLivrate(){return this->prodLivrate;}

    void setTipSocietate(tipSoc tipSocietate){
        this->tipSocietate=tipSocietate;
    }

    void setDenumire(char* denumire){
        if(strlen(denumire)>1) {
            delete[] this->denumire;
            this->denumire=new char[strlen(denumire)];
            strcpy(this->denumire, denumire);
        }
    }

    void setZileLivrari(int zileLivrariLuna){
        if(zileLivrariLuna>0 && zileLivrariLuna<32){
            this->zileLivrariLuna=zileLivrariLuna;
        }
    }

    void setCombustibilPretZi(int zi, float combustibilZi){
        //seteaza cate produse au fost livrate intr-o anumita zi a lunii
        if(zi>1 && zi<32 && combustibilZi>0){
            this->combustibilPretZi[zi-1]=combustibilZi;}
    }

    void setNrTipProdFurnizate(int nrTipuriProdLivrate){
        if(nrTipuriProdLivrate>0){this->nrTipuriProdLivrate=nrTipuriProdLivrate;}
    }

    void setProdLivrate(int zi, int tipProd, int nrProduseLivrate){
        this->prodLivrate[zi][tipProd]=nrProduseLivrate;
    }
};

int Furnizor::nrFurnizori=0;

int main(){
    //apel constructor fara parametri pentru alimentara
    Alimentara a1;
    //apel constructor cu toti parametrii pentru alimentara
    Alimentara a2(PFA, "Lidl", true, 28, new float[5]{200,100,300,50, 250}, 152345.76);
    //apel constructor de copiere pentru alimentara
    Alimentara a3(a2);
    //apel operator = pentru alimentara
    a1=a2;
    //apel operator << pentru alimentara
    cout<<a3;
    //apel operator>> pentru alimentara;
    //cin>>a1;
    cout<<endl;
    cout<<a1;
    //apel operator [] pentru alimentara
    cout<<"\nIncasarile din ziua 5: "<<a1[5]<<" lei"<<endl;
    //apel operator + pentru produs
    cout<<"\nCapital social initial: "<<a2.getCapitalSocial();
    cout<<", Capital social dupa operatorul +: "<<(a2+99).getCapitalSocial()<<endl;
    //apel operator - pentru produs
    cout<<"Capital social dupa operatorul -: "<<(a2-999).getCapitalSocial();
    //apel operator++ preincrementare
    ++a2;
    //apel operator postincrementare
    a3++;
    //apel operator >=
    if(a1>=a3){
        cout<<"\n\nAlimentara a1 are un stoc mai mare sau egal fata de alimentara a2";
    }else cout<<"\n\nAlimentara a1 are un stoc mai mic sau egal fata de alimentara a2";
    //apel operator ==
    if(a1==a1)cout<<"\n\nAlimentarele sunt identice";
    else cout<<"\n\nAlimentarele nu sunt identice";
    //getteri pentru alimentara
    cout<<"\n\nTipul societatii: "<<a2.getTipulSocietatii()<<endl;
    cout<<"Denumire: "<<a1.getDenumire()<<endl;
    cout<<"Statut platitoare de TVA: "<<a1.getPlataTVA()<<endl;
    cout<<"Alimentara a fost deschisa luna aceasta "<<a2.getZileVanzare()<<" zile"<<endl;
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" a lunii a incasat "<<a2.getIncasari()[i]<<" lei\t\t";
    }
    cout<<"\nCapitalul social al alimentarei este de "<<a3.getCapitalSocial()<<" lei"<<endl;
    cout<<"\n\nNumarul total de alimentare este de "<<Alimentara::getNrAlimentare()<<" alimentare"<<endl;
    //setteri + verificare functionalitate cu getteri pentru alimentara
    a2.setTipulSocietatii(SA);
    cout<<"\nAm schimbat tipul societatii in tipul: "<<a2.getTipulSocietatii()<<endl;
    a2.setDenumire("Kaufland");
    cout<<"Am schimbat denumirea alimentarei in: "<<a2.getDenumire()<<endl;
    a2.setPlataTVA(false);
    cout<<"Am schimbat statutul de platitoare de TVA: "<<a2.getPlataTVA()<<endl;
    a2.setZileVanzare(6);
    cout<<"Am schimbat numarul de zile din luna in care alimentara a fost deschisa in: "<<a2.getZileVanzare()<<endl;
    a2.setIncasari(6, new float[6]{168,226,139,23,32,48}); //am adaugat unn nou vector de incasari din 6 zile ale lunii
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" a lunii a incasat "<<a2.getIncasari()[i]<<" lei\t\t";
    }
    a2.setCapitalSocial(456765.87);
    cout<<"\nNoul capital social al alimentarei este de "<<a2.getCapitalSocial()<<" lei\n\n";
    //apel constructor cu un parametru pentru produs
    Produs p1(1000);
    //apel constructor cu toti parametrii pentru ptodus
    Produs p2(1001, "Iaurt", new int[7]{3,5,2,15,6,5,4}, LACTATE, 10.3);
    //apel constructor de copiere pentru produs
    Produs p3(p2);
    //apel operator= pentru produs
    p1=p3;
    //apel operator << pentru produs
    cout<<p1;
    //apel operator>> pentru produs
    //cin>>p2;
    cout<<endl;
    cout<<p2;
    //apel operator [] pentru produs;
    cout<<"\nStocul din ziua 3 a fost de "<<p2[3]<<" buc."<<endl;
    //operatorul + pentru produs
    cout<<"Pretul dupa operatorul +: "<<(p2+30).getPret()<<endl;
    //operatorul - pentru produs
    cout<<"Pretul dupa operatorul -: "<<(p3-1).getPret()<<endl;
    //operatorul ++ postincrementare pentru produs
    p2++;
    //operatorul ++preincrementare pentru po=rodus
    ++p3;
    //operatorul >= pentru produs
    if(p1>=p2) cout<<"\nProdusul p1 are pretul mai mare sau egal ca produsul p2";
    else cout<<"\nProdusul p1 are pretul mai mic sau egal ca produsul p2";
    //operatorul == pentru produs
    if(p1==p2)cout<<"\nProdusele sunt identice";
    else cout<<"\nProdusele nu sunt identice";
    //geteri pentru produs
    cout<<"\n\nCodul produsului: "<<p1.getCodProdus()<<endl;
    cout<<"Denumirea produsului: "<<p2.getDenumireProdus()<<endl;
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" a lunii am avut "<<p3.getStocCurent()[i]<<" buc.,\t";}
    cout<<"\nTipul produsului: "<<p2.getTipProdus()<<endl;
    cout<<"Pretul produsului: "<<p3.getPret()<<" lei"<<endl;
    cout<<"\nStocul produselor in functie de categorie este: ";
    for(int i=0;i<5;i++){
        cout<<Produs::getStocuriProduse()[i]<<" pentru categoria "<<i+1<<",\t";
    }
    cout<<endl;
    //setteri + verificare cu getteri pentru produs
    p1.setDenumire("Apa");
    cout<<"\nDenumirea noua a produsului: "<<p1.getDenumireProdus()<<endl;
    p2.setStocCurent(31, 13);
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" a lunii am avut "<<p2.getStocCurent()[i]<<" buc.\t";}
    p1.setTipProdus(BAUTURI);
    cout<<"\nTipul nou al produsului: "<<p1.getTipProdus()<<endl;
    p2.setPret(13.13);
    cout<<"Pretul nou al produsului: "<<p2.getPret()<<" lei"<<endl;
    //apel constructor cu un parametru pentru angajat
    Angajat ang1("1234567890987");
    //apel constructor cu toti parametrii pentru angajat
    Angajat ang2("0987654321234", "Popescu", "Ion", 45, "BARBAT", 11, new int[7]{4,4,4,4,4}, 10548.67);
    //apel constructor de copiere pentru angajat
    Angajat ang3(ang2);
    //apel operator = pentru angajat
    ang1=ang3;
    //apel operator << pentru angajat
    cout<<ang1;
    //apel operator >> pentru angajat + verificare
    //cin>>ang1;
    cout<<endl;
    cout<<ang1;
    //apel operator[] pentru angajat
    cout<<"\nAngajatul a lucrat in ziua 4 un numar de "<<ang1[4]<<" ore"<<endl;
    //apel operator+
    cout<<"\nVechime dupa operatorul +: "<<(ang1+2).getVechimeAni()<<endl;
    //apel operator -
    cout<<"Vechime dupa operatorul -: "<<(ang2-1).getVechimeAni()<<endl;
    //apel operator ++ pentru angajat si verificare
    cout<<"\nVarsta veche: "<<ang1.getVarsta()<<endl;
    ang1++;
    cout<<"Varsta noua: "<<ang1.getVarsta()<<endl;
    //apel operator >=
    if(ang1>=ang3)cout<<"\nAngajatul ang1 are varsta mai mare sau egala cu cea a angajatului ang3";
    else cout<<"\nAngajatul ang1 are varsta mai mica sau egala cu cea a angajatului ang3";
    //apel operator == angajat
    if(ang1==ang3)cout<<"\nAngajatii sunt aceiasi";
    else cout<<"\nAngajatii sunt diferiti";
    //getteri pentru angajat
    cout<<endl;
    cout<<"CNP-ul: "<<ang1.getCNP()<<endl;
    cout<<"Numele angajatului: "<<ang2.getNume()<<endl;
    cout<<"Prenumele Angajatului: "<<ang3.getPrenume()<<endl;
    cout<<"Varsta angajatului: "<<ang2.getVarsta()<<endl;
    cout<<"Genul angajatului: "<<ang3.getGen()<<endl;
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" a lucrat "<<ang2.getOreLucrateLuna()[i]<<" ore\t";}
    cout<<endl;
    cout<<"Salariul angajatului: "<<ang2.getSalariu()<<" lei"<<endl;
    //setteri + verificare cu getteri pentru angajat
    ang2.setNume("Ionescu");
    cout<<"\nNumele nou al angajatului: "<<ang2.getNume()<<endl;
    ang3.setPrenume("Marian");
    cout<<"Prenumele nou al angajatului: "<<ang3.getPrenume()<<endl;
    ang2.setVarsta(46);
    cout<<"Varsta noua a angajatului: "<<ang2.getVarsta()<<endl;
    ang1.setGen("FEMEIE");
    cout<<"Genul nou al angajatului: "<<ang1.getGen()<<endl;
    ang2.setOreLucrateLuna(8, 4);
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" a lucrat "<<ang2.getOreLucrateLuna()[i]<<" ore\t";}
    ang1.setSalariu(9876);
    cout<<"\nNoul salariu al angajatului: "<<ang1.getSalariu()<<endl;
    //apel constructor fara parametri pentru angajat cu studii superioare
    AngajatStudiiSup angs1("0987654321234");
    //apel constructor cu toti parametrii pentru angajat cu studii superioare
    AngajatStudiiSup angs2("0987654321234", "Vasile", "Marius", 22, "BARBAT", 1, new int[5]{6,6,6,6,6}, 7600.87, CONTABIL, new int[12]{10,0,0,5,0,0,0,0,10,0,0,0}, 4);
    //apel constructor de copiere pentru angajat cu studii superioare
    AngajatStudiiSup angs3(angs2);
    //apel constructor cu 4 parametri pentru angajat cu studii superioare
    AngajatStudiiSup angs4(angs1, CONTABIL, new int[12]{0,0,0,5,0,0,10,0,15,0,0,5}, 6);
    //apel operator = pentru angajat cu studii superioare
    angs1=angs2;
    //apel operator <<pentru angajatul cu studii superioare
    cout<<angs4;
    //apel operator >> pentru angajat cu studii superioare
    //cin>>angs1;
    cout<<endl;
    cout<<angs1;
    //apel operator [] pentru angajat cu studii superioare
    cout<<"\nPentru angajatul cu studii superioare salariul s-a majorat in luna 7 cu "<<angs4[7]<<endl;
    //apel operator + pentru angajat cu studii superioare
    cout<<"\nNumarul anilor de studiu dupa operatorul +: "<<(angs2+3).getNrAniStudSup()<<endl;
    //apel operator - pentru angajat cu studii superioare
    cout<<"Numarul anilor de studiu dupa oeratorul -: "<<(angs4-2).getNrAniStudSup()<<endl;
    //apel operator++ preincrementare
    ++angs2;
    //apel operator++ postincrementare
    angs3++;
    //apel operator>=
    if(angs1>=angs3) cout<<"\nAngajatul a1 a studiat mai multi sau acelasi numar de ani fata de angajatul a3";
    else cout<<"\nAngajatul a1 a studiat mai putini sau acelasi numar de ani fata de angajatul a3";
    //apel operator ==
    if(angs1==angs3)cout<<"\nAngajatii sunt identici";
    else cout<<"\nAngajatii sunt diferiti";
    //getter pentru angajat cu studii superioare
    cout<<"\nCalificarea angajatului cu studii superioare este: "<<angs1.getCalificare()<<endl;
    for(int i=0;i<12;i++){
        cout<<"In luna "<<i+1<<" a anului angajatul a avut o majorare salariala de "<<angs2.getMajorari()[i]<<"%, \t";
    }
    cout<<"\nAngajatul a urmat programe de studii superioare timp de "<<angs4.getNrAniStudSup()<<" ani"<<endl;
    //setter + verificare pentru angajat cu studii superioare
    angs1.setCalificare(MANAGER);
    cout<<"\n\nCalificarea schimbata a angajatului cu studii superioare este: "<<angs1.getCalificare()<<endl;
    angs2.setMajorari(3, 6);
    cout<<"\nSalariul a crescut in luna a 3-a cu "<<angs2.getMajorari()[2]<<"%"<<endl;
    angs4.setNrAniStudSup(8);
    cout<<"\nNumarul de ani de studiu modificat: "<<angs4.getNrAniStudSup()<<" ani"<<endl;
    //apel constructor fara parametri pentru furnizor
    Furnizor f1;
    //apel constructor cu toti parametrii pentru furnizor
    Produs* oferta[]={&p1,&p2,&p3};

    int **livrari = new int*[28];
    for(int i=0;i<28;i++){
        livrari[i]= new int [5];
    }

    for(int i=0;i<28;i++){
        for(int j=0;j<5;j++)
            livrari[i][j]=0;
    }

    Furnizor f2(SA, "Zaris", 28, new float[5]{2,6,7,8,9}, 3, oferta, livrari);
    //apel constructor de copiere pentru furnizor
    Furnizor f3(f2);
    //apel operator = pentru furnizor
    f1=f3;
    //apel operator<< pentru furnizor
    cout<<f2;
    //apel operator>> pentru furnizor
    cin>>f3;
    cout<<endl;
    cout<<f3;
    //apel operator [] pentru furnizor
    cout<<"In a 4-a zi a lunii furnizorul a livrat "<<f2[4]<<" produse"<<endl;
    //apel operator +
    cout<<"\nNumar tipuri produse furnizate dupa operatorul +: "<<(f2+2).getNrTipProdFurnizate()<<endl;
    //apel operator -
    cout<<"Numar tipuri produse furnizate dupa operatorul -: "<<(f3-1).getNrTipProdFurnizate()<<endl;
    //apel operator++ preincrementare
    ++f1;
    //apel operator++ postincrementare
    f2++;
    //apel operator >=
    if(f1>=f3) cout<<"\nFurnizorul f1 are o gama mai mare sau egala de produse fata de furnizorul f3";
    else cout<<"\nFurnizorul f1 are o gama mai mare sau egala de produse fata de furnizorul f3";
    //apel operator == furnizori
    if(f1==f3)cout<<"\nFurnizorii sunt identici";
    else cout<<"\nFurnizorii sunt diferiti";
    //getteri pentru furnizor
    cout<<endl;
    cout<<"\nTipul societatii furnizorului: "<<f2.getTipSocFurnizor()<<endl;
    cout<<"Denumirea furnizorului: "<<f1.getDenumire()<<endl;
    cout<<"Furnizorul a livrat produse in "<<f2.getNrZileLivrari()<<" zile din luna"<<endl;
    for(int i=0;i<31;i++){
        cout<<"In ziua "<<i+1<<" furnizorul a platit "<<f2.getcombustibilPretZi()[i]<<" lei pe combustibil,\t";}
    cout<<"Numarul tipurilor de produse furnizate de acest furnizor este de "<<f2.getNrTipProdFurnizate()<<" produse"<<endl;
    cout<<"Informatii despre primul produs furnizat:\n"<<(*f2.getProdOferta()[1])<<endl;
    //setteri + verificare pentru furnizor
    f1.setTipSocietate(SCS);
    cout<<"\n\nNoul tip de societate al furnizorului:"<<f1.getTipSocFurnizor()<<endl;
    f2.setDenumire("Romaria");
    cout<<"Noua denumire a furnizorului: "<<f2.getDenumire()<<endl;
    f2.setZileLivrari(27);
    cout<<"Furnizorul a livrat produse in "<<f2.getNrZileLivrari()<<" zile din luna"<<endl;
    f3.setCombustibilPretZi(6, 13);
    for(int i=0;i<31;i++){cout<<"In ziua "<<i+1<<" furnizorul a platit "<<f3.getcombustibilPretZi()[i]<<" lei pe combustibil,\t";}

    return 0;
}
