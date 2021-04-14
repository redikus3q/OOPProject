#include <iostream>
#include <vector>
#include <string>

using namespace std;

///Am presupus ca nu se pot schimba datele unui card dupa ce a fost creat. Doar creditul. De dragul temei am facut un setter pt cvv oricum.
class card{

protected:
    static string banca;
    string nrCard;
    string numeDetinator;
    string dataExpirare;
    int CVV;
    double credit;

public:
    card(): nrCard(""), numeDetinator(""), dataExpirare(""), CVV(0), credit(0){}

    card(string a, string b, string c, int d): nrCard(a), numeDetinator(b), dataExpirare(c), CVV(d){}

    card(string a, string b, string c, int d, double e): nrCard(a), numeDetinator(b), dataExpirare(c), CVV(d), credit(e){}

    virtual ~card(){
        nrCard.clear();
        numeDetinator.clear();
        dataExpirare.clear();
    }

    friend istream& operator>>(istream& in, card& a){
        cout<<"Numar card: ";
        getline(in, a.nrCard);
        cout<<"Nume detinator: ";
        getline(in, a.numeDetinator);
        cout<<"Data expirare: ";
        getline(in, a.dataExpirare);
        cout<<"CVV: ";
        in>>a.CVV;
        while(!in || a.CVV<100 || a.CVV>999){
            in.clear();
            in.ignore(INT_MAX,'\n');
            cout<<"Introduceti un numar valabil"<<endl;
            in>>a.CVV;
        }
        cout<<"Credit: ";
        in>>a.credit;
        return in;
    }

    friend ostream& operator<<(ostream& out, card& a){
        if(a.nrCard==""){
            out<<"Card neinitializat."<<endl;
        }
        else{
            out<<"Numar card: "<<a.nrCard<<endl<<"Detinator: "<<a.numeDetinator<<endl<<"Data expirare: "<<a.dataExpirare<<endl<<"CVV: "<<a.CVV<<endl<<"Credit: "<<a.credit<<endl;
        }
        return out;
    }

    card operator=(card a){
        this->nrCard = a.nrCard;
        this->numeDetinator = a.numeDetinator;
        this->dataExpirare = a.dataExpirare;
        this->CVV = a.CVV;
        this->credit = a.credit;
        return *this;
    }

    int setCVV(int a){this->CVV=a;}
    int setCredit(int a){this->credit=a;}

    int getCVV(){return CVV;}
    string getNrCard(){return nrCard;}
    string getNumeDetinator(){return numeDetinator;}
    string getDataExpirare(){return dataExpirare;}
    double getCredit(){return credit;}

    static string getBanca(){return banca;}

    card(const card& a){
        this->nrCard = a.nrCard;
        this->numeDetinator = a.numeDetinator;
        this->dataExpirare = a.dataExpirare;
        this->CVV = a.CVV;
        this->credit = a.credit;
    }

    void deposit(double sum){
        this->credit += sum;
    }

};

class cardStandard: public card{

protected:
    int limitaExtragere;
    double comisionDepasireLimita;

public:
    cardStandard(): card(), limitaExtragere(0), comisionDepasireLimita(0){}

    cardStandard(string a, string b, string c, int d, int e, int f, double g): card(a, b, c, d, e), limitaExtragere(f), comisionDepasireLimita(g){}

    virtual ~cardStandard(){
        nrCard.clear();
        numeDetinator.clear();
        dataExpirare.clear();
    }

    friend istream& operator>>(istream& in, cardStandard& a){
        in>>(card&)a;
        cout<<"Limita extragere: ";
        in>>a.limitaExtragere;
        cout<<"Comision depasire limita: ";
        in>>a.comisionDepasireLimita;
        return in;
    }

    friend ostream& operator<<(ostream& out, cardStandard& a){
        out<<"Card standard"<<endl;
        out<<(card&)a;
        if(a.nrCard!=""){
            out<<"Limita extragere: "<<a.limitaExtragere<<endl<<"Comision depasire limita: "<<a.comisionDepasireLimita<<endl;
        }
        return out;
    }

    cardStandard operator=(cardStandard a){
        this->nrCard = a.nrCard;
        this->numeDetinator = a.numeDetinator;
        this->dataExpirare = a.dataExpirare;
        this->CVV = a.CVV;
        this->credit = a.credit;
        this->comisionDepasireLimita = a.comisionDepasireLimita;
        this->limitaExtragere = a.limitaExtragere;
        return *this;
    }

    void setLimitaExtragere(int a){this->limitaExtragere=a;}
    void setComisionDepasireLimita(int a){this->comisionDepasireLimita=a;}

    int getLimitaExtragere(){return this->limitaExtragere;}
    double getComisionDepasireLimita(){return this->comisionDepasireLimita;}

    virtual void extract(double sum){
        double c = this->getCredit();
        if(sum>c){
            cout<<"Nu aveti credit suficient."<<endl;
            return;
        }
        if(sum>this->limitaExtragere){
            this->setCredit(c-sum-this->comisionDepasireLimita);
            return;
        }
        this->setCredit(c-sum);
    }

};

class cardPremium: public cardStandard{

protected:
    double cashback;

public:
    cardPremium(): cardStandard(), cashback(0){}

    cardPremium(string a, string b, string c, int d, int e, int f, double g, double h): cardStandard(a, b, c, d, e, f, g), cashback(h){}

    cardPremium(const cardStandard&a): cardStandard(a), cashback(-1){}

    ~cardPremium(){
        nrCard.clear();
        numeDetinator.clear();
        dataExpirare.clear();
    }

    friend istream& operator>>(istream& in, cardPremium& a){
        in>>(cardStandard&)a;
        cout<<"Cashback: ";
        in>>a.cashback;
        return in;
    }

    friend ostream& operator<<(ostream& out, cardPremium& a){
        out<<"Card premium"<<endl;
        out<<(card&)a;
        if(a.nrCard!=""){
            out<<"Limita extragere: "<<a.limitaExtragere<<endl<<"Comision depasire limita: "<<a.comisionDepasireLimita<<endl<<"Cashback: "<<a.cashback<<endl;;
        }
        return out;
    }

    cardPremium operator=(cardPremium a){
        this->nrCard = a.nrCard;
        this->numeDetinator = a.numeDetinator;
        this->dataExpirare = a.dataExpirare;
        this->CVV = a.CVV;
        this->credit = a.credit;
        this->comisionDepasireLimita = a.comisionDepasireLimita;
        this->limitaExtragere = a.limitaExtragere;
        this->cashback = a.cashback;
        return *this;
    }

    void setCashback(int a){this->cashback=a;}

    double getCashback(){return this->cashback;}

    void extract(double sum){
        double c = this->getCredit();
        if(sum>c){
            cout<<"Nu aveti credit suficient."<<endl;
            return;
        }
        this->setCredit(c-sum+this->cashback/100*sum);
    }

};

string card::banca="BCR";


bool read(int &g, int siz){

    cin.clear();
    cin.ignore(INT_MAX,'\n');
    cin>>g;
    while(!cin || g>=siz || g<=-1 || siz==0){
        cout<<"Introduceti un numar valabil sau -1 sa iesiti."<<endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cin>>g;
        if(g==-1){
            cout<<"Ati iesit."<<endl;
            return 0;
        }
    }
    return 1;

}

bool readcvv(int &k){

    cin>>k;
    while(!cin || k<100 || k>999){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"Introduceti un numar valabil sau -1 sa iesiti."<<endl;
        cin>>k;
        if(k==-1){
            cout<<"Ati iesit."<<endl;
            return 0;
        }
    }
    return 1;

}

bool readint(int &k){

    cin>>k;
    while(!cin || k<0){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"Introduceti un numar valabil sau -1 sa iesiti."<<endl;
        cin>>k;
        if(k==-1){
            cout<<"Ati iesit."<<endl;
            return 0;
        }
    }
    return 1;

}

bool readbool(int &k){

    cin>>k;
    while(!cin || (k!=0 && k!=1)){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"Introduceti un numar valabil sau -1 sa iesiti."<<endl;
        cin>>k;
        if(k==-1){
            cout<<"Ati iesit."<<endl;
            return 0;
        }
    }
    return 1;

}

void optiuni(){

    cout<<"/------------------------------------------------------------------------\\"<<endl;
    cout<<"|  Optiuni meniu:                                                        |"<<endl;
    cout<<"|  Numarul 0 - Iesiti din aplicatie.                                     |"<<endl;
    cout<<"|  Numarul 1 - Adaugati card standard.                                   |"<<endl;
    cout<<"|  Numarul 2 - Adaugati card premium.                                    |"<<endl;
    cout<<"|  Numarul 3 - Eliminati card.                                           |"<<endl;
    cout<<"|  Numarul 4 - Modificati CVV-ul unui card adaugat anterior.             |"<<endl;
    cout<<"|  Numarul 5 - Afisati informatiile unui card adaugat anterior.          |"<<endl;
    cout<<"|  Numarul 6 - Afisati creditul unui card adaugat anterior.              |"<<endl;
    cout<<"|  Numarul 7 - Faceti doua carduri egale.                                |"<<endl;
    cout<<"|  Numarul 8 - Depozitati credit pe un card.                             |"<<endl;
    cout<<"|  Numarul 9 - Retrageti credit de pe un card.                           |"<<endl;
    cout<<"|  Numarul 10 - Faceti upgrade de la un card standard la unul premium.   |"<<endl;
    cout<<"|  Numarul 11 - Faceti downgrade de la un card premium la unul standard. |"<<endl;
    cout<<"|  Numarul 12 - Afisare carduri prezente pana acum.                      |"<<endl;
    cout<<"|  Numarul 13 - Adaugati mai multe carduri.                              |"<<endl;
    cout<<"|  Numarul 14 - Afisati banca la care sunteti racordat                   |"<<endl;
    cout<<"|  Numarul 15 - Reafisare optiuni meniu.                                 |"<<endl;
    cout<<"*------------------------------------------------------------------------*"<<endl;

}

void menu(){

    cout<<endl<<"                              Proiect carduri"<<endl;
    optiuni();
    int o, g, k;
    cardStandard aux1;
    cardPremium aux2;
    o=1;
    vector<cardPremium> v;
    while(o){
        cin>>o;
        if(!cin){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            o=-1;
        }
        switch(o){
            case 0:{
                break;
            }
            case 1:{
                cout<<"Adaugati card standard."<<endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin>>aux1;
                cardPremium aux2(aux1);
                v.push_back(aux2);
                cout<<"Adaugare reusita."<<endl;
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 2:{
                cout<<"Adaugati card premium."<<endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin>>aux2;
                v.push_back(aux2);
                cout<<"Adaugare reusita."<<endl;
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 3:{
                cout<<"Specificati numarul cardului pe care vreti sa il eliminati (din vector)."<<endl;
                if(read(g, v.size())==1){
                    v.erase(v.begin()+g);
                    cout<<"Eliminare reusita."<<endl;
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 4:{
                cout<<"Modificati CVV-ul unui card. Specificati numarul lui."<<endl;
                if(read(g, v.size())==1){
                    cout<<"Introduceti noul CVV. Trebuie sa fie un numar de 3 cifre pozitiv."<<endl;
                    if(readcvv(k)==1){
                        v[g].setCVV(k);
                        cout<<"Modificare reusita."<<endl;
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 5:{
                cout<<"Introduceti numarul corespunzator cardului pe care vreti sa-l afisati (din vector)."<<endl;
                if(read(g, v.size())==1){
                    if(v[g].getCashback()==-1){
                        cout<<(cardStandard&)v[g];
                    }
                    else{
                        cout<<v[g];
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 6:{
                cout<<"Introduceti numarul corespunzator cardului al carui credit vreti sa-l aflati."<<endl;
                if(read(g, v.size())==1){
                    cout<<"Credit: "<<v[g].getCredit()<<endl;
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 7:{
                cout<<"Introduceti numarul cardului care va fi suprascris. Informatiile acestuia vor fi pierdute."<<endl;
                if(read(g, v.size())==1){
                    cout<<"Introduceti numarul cardului ale carui informatii vor fi scrise peste cardul anterior."<<endl;
                    if(read(k, v.size())==1){
                        v[g]=v[k];
                        cout<<"Operatiune reusita"<<endl;
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl;
                break;
            }
            case 8:{
                cout<<"Introduceti numarul cardului pe care vreti sa depozitati credit."<<endl;
                if(read(g, v.size())==1){
                    cout<<"Introduceti suma dorita."<<endl;
                    if(readint(k)==1){
                        v[g].deposit(k);
                        cout<<"Operatiune reusita."<<endl;
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 9:{
                cout<<"Introduceti numarul cardului de pe care vreti sa retrageti credit."<<endl;
                if(read(g, v.size())==1){
                    cout<<"Introduceti suma dorita."<<endl;
                    if(readint(k)==1){
                        if(v[g].getCashback()==-1){
                            v[g].cardStandard::extract(k);
                        }
                        else{
                            v[g].extract(k);
                        }
                        cout<<"Retragere reusita."<<endl;
                    }
                }
                cout<<"Ati revenit la meniul principal"<<endl<<endl;
                break;
            }
            case 10:{
                cout<<"Introduceti numarul cardului pe care vreti sa il updragati."<<endl;
                if(read(g, v.size())==1){
                    cout<<"Introduceti cashbackul."<<endl;
                    if(readint(k)==1){
                        v[g].setCashback(k);
                        cout<<"Upgrade reusit."<<endl;
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 11:{
                cout<<"Introduceti numarul cardului pe care vreti sa il faceti standard."<<endl;
                if(read(g, v.size())==1){
                    v[g].setCashback(-1);
                    cout<<"Downgrade reusit."<<endl;
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 12:{
                for(cardPremium i:v){
                    if(i.getCashback()==-1){
                        cout<<(cardStandard&)aux1<<endl;
                    }
                    else{
                        cout<<i<<endl;
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 13:{
                cout<<"Introduceti numarul de carduri pe care vreti sa il adaugati"<<endl;
                if(readint(k)==1){
                    for(int i=0; i<k; ++i){
                        cout<<"Introduceti tipul cardului pe care vreti sa-l adaugati. '0' pentru standard sau '1' pentru premium."<<endl;
                        if(readbool(g)==1){
                            if(g==0){
                                cout<<"Adaugati card standard."<<endl;
                                cin.clear();
                                cin.ignore(INT_MAX,'\n');
                                cin>>aux1;
                                cardPremium aux2(aux1);
                                v.push_back(aux2);
                                cout<<"Adaugare reusita."<<endl;
                            }
                            else{
                                cout<<"Adaugati card premium."<<endl;
                                cin.clear();
                                cin.ignore(INT_MAX,'\n');
                                cin>>aux2;
                                v.push_back(aux2);
                                cout<<"Adaugare reusita."<<endl;
                            }
                        }
                    }
                }
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 14:{
                cout<<"Banca la care sunteti racordat este "<<card::getBanca()<<"."<<endl;
                cout<<"Ati revenit la meniul principal."<<endl<<endl;
                break;
            }
            case 15:{
                optiuni();
                break;
            }
            default:{
                cout<<"Nu exista o optiune pentru inputul introdus. Introduceti numarul 15 pentru a vedea optiunile."<<endl;
                break;
            }
        }
    }
}

int main(){

    menu();
    return 0;

}
