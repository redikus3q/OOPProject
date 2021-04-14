#include <iostream>
#include <vector>
using namespace std;

class polinom{

    int grad;
    vector<double> coef;

public:
    polinom(){
        this->grad=0;
    }

    polinom(int a){
        if(a<0){
            this->grad=0;
            this->coef.push_back(0);
        }
        else{
            this->grad=a;
            for(int i=0; i<=this->grad; ++i){
                this->coef.push_back(0);
            }
        }
    }

    polinom(int a, vector<double> b){
        if(a<0){
            this->grad=0;
            this->coef.push_back(0);
        }
        else{
            this->grad=a;
            for(int i=0; i<=this->grad; ++i){
                this->coef.push_back(b[i]);
            }
        }
    }

    polinom (const polinom &a){
        this->grad=a.grad;
        this->coef=a.coef;
    }

    ~polinom(){
        this->coef.clear();
        this->coef.shrink_to_fit();
    }

    void set_grad(int a){
        if(a<0){
            a=0;
            coef.clear();
            coef.shrink_to_fit();
            coef.push_back(0);
            return;
        }
        this->grad=a;
        this->coef.resize(a+1, 0);
    }

    void set_coef(vector<double> a){
        if(a.empty()==1){
            this->coef.push_back(0);
            this->grad=0;
            return;
        }
        this->coef=a;
        this->grad=a.size()-1;
    }

    int get_grad(){
        return this->grad;
    }

    vector<double> get_coef(){
        return this->coef;
    }

    double get_val(double x){
        double pow=1;
        double rez=0;
        for(int i=0; i<=this->grad;++i){
            rez=this->coef[i] * pow + rez;
            pow=pow*x;
        }
        return rez;
    }

    friend istream& operator>>(istream& in, polinom& a){
        cout<<"Gradul: ";
        in>>a.grad;
        if(!in){
            in.clear();
            in.ignore(INT_MAX,'\n');
            a.grad=-1;
        }
        if(a.grad<0){
            a.grad=0;
            a.coef.push_back(0);
            return in;
        }
        int temp;
        cout<<"Coeficientii: ";
        for(int i=0;i<=a.grad; i++){
            in>>temp;
            a.coef.push_back(temp);
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, polinom& a){
        if ((a.coef.size()==1 && a.coef[0]==0) || a.coef.size()==0){
            out<<"Polinom nul";
            return out;
        }
        out<<"Polinom de grad "<<a.grad<<" cu coeficientii ";
        for(int i=0;i<=a.grad;i++){
            out<<a.coef[i]<<" ";
        }
        return out;
    }

    void shrink(polinom& a){
        int i=a.grad;
        while(i>=0){
            if(a.coef[i]==0){
                a.grad--;
            }
            else{
                break;
            }
            i--;
        }
        if(i==-1){
            a.coef.clear();
            a.coef.shrink_to_fit();
            a.coef.push_back(0);
        }
    }

    polinom operator+(polinom a){
        polinom temp(*this);
        polinom fin;
        fin.grad=max(temp.grad, a.grad);
        int i;
        for(i=0; i<=min(temp.grad, a.grad); ++i){
            fin.coef.push_back(temp.coef[i]+a.coef[i]);
        }
        if(temp.grad>a.grad){
            while(i<=fin.grad){
                fin.coef.push_back(temp.coef[i]);
                i++;
            }
        }
        else{
            while(i<=fin.grad){
                fin.coef.push_back(a.coef[i]);
                i++;
            }
        }
        shrink(fin);
        return fin;
    }

    polinom operator-(polinom a){
        polinom temp(*this);
        polinom fin;
        fin.grad=max(temp.grad, a.grad);
        int i;
        for(i=0; i<=min(temp.grad, a.grad); ++i){
            fin.coef.push_back(temp.coef[i]-a.coef[i]);
        }
        if(temp.grad>a.grad){
            while(i<=fin.grad){
                fin.coef.push_back(temp.coef[i]);
                i++;
            }
        }
        else{
            while(i<=fin.grad){
                fin.coef.push_back(-a.coef[i]);
                i++;
            }
        }
        shrink(fin);
        return fin;
    }

    polinom operator*(polinom a){
        polinom temp(*this);
        polinom fin(temp.grad+a.grad);
        int k;
        for(int i=temp.grad; i>=0; --i){
            k=i+a.grad;
            for(int j=a.grad; j>=0; --j){
                fin.coef[k]+=temp.coef[i]*a.coef[j];
                k--;
            }
        }
        shrink(fin);
        return fin;
    }

};

void optiuni(){

    cout<<"Optiuni meniu:"<<endl;
    cout<<"Numarul 0 - Iesiti din aplicatie"<<endl;
    cout<<"Numarul 1 - Adaugati polinom. Specificati gradul, apoi coeficientii."<<endl;
    cout<<"Numarul 2 - Eliminati polinom."<<endl;
    cout<<"Numarul 3 - Modificati gradul unui polinom adaugat anterior."<<endl;
    cout<<"Numarul 4 - Modificati coeficientii unui polinom adaugat anterior."<<endl;
    cout<<"Numarul 5 - Afisati gradul unui polinom adaugat anterior."<<endl;
    cout<<"Numarul 6 - Afisati coeficientii unui polinom adaugat anterior."<<endl;
    cout<<"Numarul 7 - Suma intre doua polinoame adaugate anterior."<<endl;
    cout<<"Numarul 8 - Diferenta intre doua polinoame adaugate anterior."<<endl;
    cout<<"Numarul 9 - Imnultire intre doua polinoame adaugate anterior."<<endl;
    cout<<"Numarul 10 - Afisare polinoame prezente pana acum."<<endl;
    cout<<"Numarul 11 - Afisati un anumit polinom."<<endl;
    cout<<"Numarul 12 - Adaugati mai multe polinoame."<<endl;
    cout<<"Numarul 13 - Reafisare optiuni meniu."<<endl;

}

bool read(int &g, int siz){

    cin>>g;
    while(!cin || g>=siz || g<-1){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"Introduceti un numar valabil sau -1 sa iesiti."<<endl;
        cin>>g;
        if(g==-1){
            cout<<"Ati iesit."<<endl;
            return 0;
        }
    }
    return 1;

}

bool read1(int &g){

    cin>>g;
    while(!cin || g<-1){
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"Introduceti un numar valabil sau -1 sa iesiti."<<endl;
        cin>>g;
        if(g==-1){
            cout<<"Ati iesit."<<endl;
            return 0;
        }
    }
    return 1;

}

bool readmore(int g, vector<polinom> &x){

    int i;
    polinom(aux);
    for(i=0;i<g;i++){
        cin>>aux;
        x.push_back(aux);
    }

}

void menu(){

    cout<<"Primul coeficient este cel al monomului de grad 0."<<endl;
    cout<<"Pentru operatii, setteri, getteri mentionati numarul polinomului care vreti sa fie modificat in ordinea in care au fost introduse polinoamele."<<endl;
    cout<<"Numaratoarea polinoamelor incepe de la 0."<<endl;
    optiuni();
    int g,i,o,x;
    double temp;
    vector<double> c;
    vector<polinom> poli;
    polinom aux;
    o=1;
    while(o){
        cin>>o;
        if(!cin){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            o=-1;
        }
        switch(o){
            aux.~polinom();
            case 0:{
                break;
            }
            case 1:{
                polinom aux;
                cout<<"Adaugati polinom. Specificati gradul, apoi coeficientii. Orice alt caracter pentru grad in afara de numere pozitive va adauga polinomul nul."<<endl;
                cin>>aux;
                poli.push_back(aux);
                cout<<"Adaugare reusita."<<endl;
                break;
            }
            case 2:{
                cout<<"Eliminati un polinom. Specificati numarul lui."<<endl;
                if(read(g, poli.size())==1){
                    poli.erase(poli.begin()+g);
                    cout<<"Eliminare reusita."<<endl;
                }
                break;
            }
            case 3:{
                cout<<"Modificati gradul unui polinom. Specificati numarul lui."<<endl;
                if(read(g, poli.size())==1){
                    cout<<"Introduceti gradul."<<endl;
                    if(read1(x)==1){
                        poli[g].set_grad(x);
                        cout<<"Modificare reusita."<<endl;
                    }
                }
                break;
            }
            case 4:{
                cout<<"Modificati coeficientii unui polinom. Specificati numarul lui."<<endl;
                if(read(g, poli.size())==1){
                    cout<<"Introduceti coeficientii."<<endl;
                    for(i=0;i<=poli[g].get_grad();i++){
                        cin>>x;
                        c.push_back(x);
                    }
                    poli[g].set_coef(c);
                    cout<<"Modificare reusita."<<endl;
                }
                break;
            }
            case 5:{
                cout<<"Afisati gradul unui polinom. Specificati numarul lui."<<endl;
                if(read(g, poli.size())==1){
                    cout<<"Grad: "<<poli[g].get_grad()<<endl;
                }
                break;
            }
            case 6:{
                cout<<"Afisati coeficientii unui polinom. Specificati numarul lui."<<endl;
                if(read(g, poli.size())==1){
                    cout<<"Coeficienti: ";
                    for(auto i: poli[g].get_coef()){
                        cout<<i<<" ";
                    }
                    cout<<endl;
                }
                break;
            }
            case 7:{
                cout<<"Primul polinom: ";
                if(read(g, poli.size())==1){
                    cout<<"Al doilea polinom: ";
                    if(read(x, poli.size())==1){
                        aux=poli[g]+poli[x];
                        cout<<"Suma polinoamelor: "<<aux<<endl;
                    }
                }
                break;
            }
            case 8:{
                cout<<"Primul polinom: ";
                if(read(g, poli.size())==1){
                    cout<<"Al doilea polinom: ";
                    if(read(x, poli.size())==1){
                        aux=poli[g]-poli[x];
                        cout<<"Diferenta polinoamelor: "<<aux<<endl;
                    }
                }
                break;
            }
            case 9:{
                cout<<"Primul polinom: ";
                if(read(g, poli.size())==1){
                    cout<<"Al doilea polinom: ";
                    if(read(x, poli.size())==1){
                        aux=poli[g]*poli[x];
                        cout<<"Produsul polinoamelor: "<<aux<<endl;
                    }
                }
                break;
            }
            case 10:{
                for(auto i: poli){
                    cout<<i<<endl;
                }
                break;
            }
            case 11:{
                cout<<"Afisati polinom. Specificati numarul lui."<<endl;
                if(read(g, poli.size())==1){
                    cout<<poli[g]<<endl;
                }
                break;
            }
            case 12:{
                cout<<"Introduceti numarul de elemente pe care vreti sa-l adaugati."<<endl;
                if(read1(g)==1){
                    readmore(g, poli);
                    cout<<"Adaugare reusita."<<endl;
                }
                break;
            }
            case 13:{
                optiuni();
                break;
            }
            default:{
                cout<<"Nu exista o optiune pentru tasta apasata. Introduceti numarul 13 pentru a vedea optiunile."<<endl;
                break;
            }
        }
    }
}

int main(){

    menu();
    return 0;

}
