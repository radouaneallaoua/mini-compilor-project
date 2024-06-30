#ifndef FONCTIONSSEMANTIQUE_H_INCLUDED
#define FONCTIONSSEMANTIQUE_H_INCLUDED
#include "variablesGlobales.h"
//==========================================================================
void ajouterFonction(string nom, string typeRetour, vector<Identificateur*> &tableDeSymboles){
    tableDeSymboles.push_back(new Fonction(nom, typeRetour));
}

//==========================================================================
Identificateur* identificateurExisteDansTS(string nom){
        for(int i=0; i<tableDeSymboles.size(); i++){
            if(tableDeSymboles[i]->getNom() == nom)
                return tableDeSymboles[i];
        }
        return nullptr;
}



//==========================================================================
Variable* estDefinitPourFonction(string nomIdentificateur,vector<Identificateur* > &tableDeSymboles){
        Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
        Variable* var=fun->rechercheVariableLocale(nomIdentificateur);   //
        if(!var){
               var=fun->rechercheArgument(nomIdentificateur);
               if(!var){
                    if(!identificateurExisteDansTS(nomIdentificateur)){
                        cout<<"ERREUR :variable |"<<nomIdentificateur<<" | est non declaree"<<endl;
                        exit(0);
                        return nullptr;
                    }else{
                       if(!identificateurExisteDansTS(nomIdentificateur)->estFonction()){
                           var=dynamic_cast<Variable*>(identificateurExisteDansTS(nomIdentificateur));
                           return var;
                       }else{
                           cout<<"ERREUR:affectation a une fonction n'est pas possible"<<endl;
                           exit(0);
                           return nullptr;
                       }
                    }
            }else{
                return var;
            }
        }else{
             return var;
        }

}
//==========================================================================
void afficherTS()
{
    cout<<"===================la table de symboles===================="<<endl<<endl;
    cout<<"***** Variables globales *****"<<endl;

    for(int i=0; i<tableDeSymboles.size(); i++)
    {
        if(tableDeSymboles[i]->estFonction())
        {
            cout<<"\n***** Fonction:  "<<tableDeSymboles[i]->getNom()<<" *****"<<endl;
            Fonction* fun =dynamic_cast<Fonction*>(tableDeSymboles[i]);
            vector<Variable*> arguments=fun->getArguments();
            vector<Variable*> variable=fun->getVariablesLocales();
            cout<<"\t***Type de retour***"<<endl;
            cout<<"\t\t"<<fun->getTypeRetour()<<endl;
            cout<<"\t*** Arguments ***"<<endl;
            if(arguments.size()==0)
            {
                cout<<"\t\tpas d'arguments"<<endl;
            }
            else
            {
                for(int j=0; j<arguments.size(); j++)
                {
                    cout<<"\t\t"<<arguments[j]->getNom()<<" de type "<<arguments[j]->getType()<<endl;
                }
            }

            cout<<"\t*** Variables locales ***"<<endl;
            if(variable.size()==0)
            {
                cout<<"\t\t pas de variables"<<endl;
            }
            else
            {
                for(int j=0; j<variable.size(); j++)
                {
                    cout<<"\t\t"<<variable[j]->getNom()<<"   ==> "<<variable[j]->getType();
                    if(variable[j]->getEstTableau()){
                        cout<<" ==> tableau"<<endl;
                    }else{
                        cout<<endl;
                    }
                }
            }


        }else{
            cout<<"\t"<<tableDeSymboles[i]->getNom()<<" ==>";
            Variable* var = dynamic_cast<Variable*>(tableDeSymboles[i]);
            if(var->getEstTableau()){
                cout<<" tableau de type "<<var->getType()<<endl;
            }else{
                cout<<" variable de type "<<var->getType()<<endl;
            }
        }


    }
     cout<<"\n==========================================================="<<endl;
}
void ajouterVariable(string nom, string typeIdentificateur, bool estTableau, vector<Identificateur* > &tableDeSymboles){
    tableDeSymboles.push_back(new Variable(nom,typeIdentificateur,estTableau));
}
#endif // FONCTIONSSEMANTIQUE_H_INCLUDED
