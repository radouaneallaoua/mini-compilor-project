#ifndef TABLEDESYMBOLES_H_INCLUDED
#define TABLEDESYMBOLES_H_INCLUDED


#include <vector>
#include <string>

using namespace std;

class Identificateur{
public:
    virtual string getNom()=0;
    virtual bool estFonction()=0;

};

class Variable : public Identificateur{
    private:
        string nom;
        string type;
        bool estTableau;
    public:
        Variable(string nom, string type, bool estTableau){
            this->nom = nom;
            this->type = type;
            this->estTableau = estTableau;
        }

        string getNom(){
            return this->nom;
        }
        string getType(){
            return this->type;
        }
        bool getEstTableau(){
            return this->estTableau;
        }
        bool estFonction(){
            return false;
        }
};

class Fonction : public Identificateur{
private:
    string nom;
    string typeRetour;
    vector<Variable*> arguments;//on a change le type Identificateur=>Variable =>pour l'utiliser dans listExpressions
    vector<Variable*> variablesLocales;
   public:
    Fonction (string nom, string typeRetour): nom(nom), typeRetour(typeRetour), arguments(), variablesLocales(){
    }
    ~Fonction(){
        for(int i=0;i<arguments.size();i++)
        {
            delete this->arguments[i];
        }
        for(int i=0;i<variablesLocales.size();i++)
        {
            delete this->variablesLocales[i];
        }
    }
    string getNom(){
        return this->nom;
    }
    string getTypeRetour(){
        return this->typeRetour;
    }
    void ajouterArgument(string nom, string type, bool estTableau){
        this->arguments.push_back(new Variable(nom, type, estTableau));
    }
    void ajouterVariableLocale(string nom, string type, bool estTableau){
        this->variablesLocales.push_back(new Variable(nom, type, estTableau));
    }

    Variable* rechercheArgument(string nomArgument){
        for(int i=0; i<this->arguments.size(); i++){
            if(this->arguments[i]->getNom() == nomArgument)
                return this->arguments[i];
        }
        return nullptr;
    }

    Variable* rechercheVariableLocale(string nomVariableLocale){
        for(int i=0; i<this->variablesLocales.size(); i++){
            if(this->variablesLocales[i]->getNom() == nomVariableLocale)
                return this->variablesLocales[i];
        }
        return nullptr;
    }

    int nombreArguments(){
        return this->arguments.size();
    }
     bool estFonction(){
        return true;
    }
     vector<Variable*> getArguments(){
         return this->arguments;
     }
    vector<Variable*> getVariablesLocales(){
        return this->variablesLocales;
    }

};



#endif // TABLEDESYMBOLES_H_INCLUDED
