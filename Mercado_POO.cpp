#include <iostream>
#include <vector>

using namespace std;

//DEFINIÇÃO DAS CLASSES
class Produto{
    public:
        //construtor
        Produto(string n, float p, int q);
        //Getters
        string getNome();
        float getPreco();
        int getQtd();
        //Setters
        void setNome(string n);
        void setPreco(float p);
        void setQtd(int qtd);
        void imprime();
    private:
        string nome;
        float preco;
        int qtd;
};
class Estoque {
    public:
    void adicionaProduto(string n,float p,int qtd);
    Produto* buscaProduto(string n, int qtd);
    void retiraProduto(string n, int qtd);
    void imprime();
    int tam();
    private:
    vector<Produto*> obj;
};
class Carrinho: public Estoque {
    public:
        Carrinho(Estoque* estoque);
        void adicionaItem(string n, int qtd);
        void finalizaCompra();
        float calculaTotal();
        void imprime();
        Produto* buscaItem(string nome,int qtd);
    private:
        std::vector<Produto*> obj;
        Estoque *aux;
};
// DECLARAÇÃO DAS CLASSES
//construtor
Produto::Produto(string n, float p, int q){
    nome = n;
    preco = p;
    qtd = q;
};
void Produto::imprime(){
    cout << "Nome: " << this->nome << endl;
    cout << "Preço: " << this->preco << endl;
    cout << "Quantidade: " << this->qtd << endl; 
}
//Getters
string Produto::getNome(){return this->nome;}
float Produto::getPreco(){return this->preco;}
int Produto::getQtd(){return this->qtd;}
//Setters
void Produto::setNome(string n){this->nome = n;}
void Produto::setPreco(float p){this->preco = p;}
void Produto::setQtd(int qtd) {this->qtd = qtd;}

void Estoque::adicionaProduto(std::string n,float p,int qtd){
    for(int i=0;i<obj.size();i++){
        if(obj[i]->getNome() == n){
            obj[i]->setPreco(p);
            obj[i]->setQtd(obj[i]->getQtd() + qtd);
            return;
        }
    }
    Produto *prod = new Produto(n,p,qtd);
    obj.push_back(prod);
}

Produto* Estoque::buscaProduto(string n, int qtd){
    for(int i=0;i < obj.size(); i++){
        if(obj[i]->getNome() == n && obj[i]->getQtd() >= qtd){
            return obj[i];
        }
    }
    return NULL;
}

void Estoque::retiraProduto(string n, int qtd){
    for(int i=0;i<obj.size();i++){
        if(obj[i]->getNome() == n){
            obj[i]->setQtd(obj[i]->getQtd()-qtd);
        }
    }
}

void Estoque::imprime(){
    for(int i=0;i<obj.size();i++){
        cout << "Nome: " << obj[i]->getNome() << endl;
        cout << "Preço: " << obj[i]->getPreco() << endl;
        cout << "Quantidade: " << obj[i]->getQtd() << endl << endl;
    }
}

int Estoque::tam(){
    return obj.size();
}

Carrinho::Carrinho(Estoque* estoque){
    aux = estoque;
}
void Carrinho::adicionaItem(string n, int qtd){
    Produto *p = aux->buscaProduto(n,qtd);
    Produto *q = new Produto(p->getNome(),p->getPreco(),qtd);
    obj.push_back(q);
}
void Carrinho::finalizaCompra(){
    for(int i=0;i<obj.size();i++){
        aux->retiraProduto(obj[i]->getNome(),obj[i]->getQtd());
    }
}
float Carrinho::calculaTotal(){
    float soma = 0;
    for(int i=0;i<obj.size();i++){
        soma = soma + (obj[i]->getPreco()*obj[i]->getQtd());
    }
    return soma;
}
void Carrinho::imprime(){
    for(int i=0;i<obj.size();i++){
        cout << "Nome: " << obj[i]->getNome() << endl;
        cout << "Preço: " << obj[i]->getPreco() << endl;
        cout << "Quantidade: " << obj[i]->getQtd() << endl << endl;
    }
}
Produto* Carrinho::buscaItem(string nome,int qtd){
    for(int i=0;i < obj.size(); i++){
        if(obj[i]->getNome() == nome && obj[i]->getQtd() >= qtd){
            return obj[i];
        }
    }
    return NULL;
}
//PROGRAMA PRINCIPAL
void menu(){
    cout << " ---------- Mercado do Zé ---------- " << endl;
    int op = 0;
    string nome;
    float preco;
    int qtd=0;

    Estoque *e = new Estoque();
    Carrinho *c = new Carrinho(e);

    while(op != 9){
        cout << "1- Adicionar produto no estoque" << endl;
        cout << "2- Adicionar produto no carrinho" << endl;
        cout << "3- Mostrar produtos do estoque" << endl;
        cout << "4- Mostrar produtos do carrinho" << endl;
        cout << "5- Finalizar compra" << endl;
        cout << "9- Encerrar programa" << endl;
        cout << "Digite uma das opções acima: ";
        cin >> op;

        switch(op){
            case 1:
                cout << "Digite o nome do produto a ser cadastrado no estoque: ";
                cin >> nome;
                if(e->buscaProduto(nome, qtd) != NULL){
                    cout << "Produto já cadastrado" << endl;
                    break;
                }
                cout << "Digite o preço do produto: ";
                cin >> preco;
                cout << "Digite a quantidade do produto: ";
                cin >> qtd;
                e->adicionaProduto(nome,preco,qtd);
                break;
            case 2:
                cout << "Digite o nome do produto a ser adicionado no carrinho: ";
                cin >> nome;
                cout << "Digite a quantidade: ";
                cin >> qtd;
                c->adicionaItem(nome, qtd);
                break;
            case 3:
                cout << "---------- Estoque ----------" << endl;
                e->imprime();
                break;
            case 4:
                cout << "---------- Carrinho ----------" << endl;
                c->imprime();
                break;
            case 5:
                c->finalizaCompra();
                cout << " Valor final: " << c->calculaTotal();
                op = 9;
                break;
            case 9:
                break;
            default:
                break;
        }
    }
}

int main(){
menu();
return 0;
}