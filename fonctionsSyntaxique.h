#ifndef FONCTIONSSYNTAXIQUE_H_INCLUDED
#define FONCTIONSSYNTAXIQUE_H_INCLUDED
#include "fonctionsLexical.h"
#include "fonctionsSemantique.h"

void programme();
void programmePrime(string typeIdentificateur, string nomIdentificateur);
void declarationFonction();
void listeDeclarations();
void listeDeclarationsPrime();
void listeDeclarateurs(string typeIdentificateur);
void listeDeclarateursPrime(string typeIdentificateur);
void declarateur(string typeIdentificateur);
bool declarateurPrime(string typeIdentificateur, string nomIdentificateur);
string type();
void listeParms();
void listeParmsPrime();
void parm();
void listeInstructions();
void listeInstructionsPrime();
void instruction();
void terme(string nomIdentificateur);
void iteration();
void selection();
void selectionPrime();
void saut();
void sautPrime();
void affectation();
int bloc();
string variable();
void variablePrime(Variable* var);
string expression();
string  termePrime(string nomIdentificateur);
string expressionPrime();
void listeExpressions(Fonction* fun);
void listeExpressionsPrime(vector<string>& argRencontres );
void condition();
void conditionPrime();
void conditionDeuxPrime();
string binaryOp();
void binaryRel();
void binaryComp();
//==============================fonctions synatxiques============
void programme(){

    string typeIdentificateur;  // sémantique
    string nomIdentificateur;  // sémantique

    if(motCourant.unite==MOTCLE && motCourant.lexeme=="int"){
        typeIdentificateur = "int"; // sémantique
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            nomIdentificateur = motCourant.lexeme; // sémantique
            motCourant=uniteSuivanteSansCommentaire(c);
            programmePrime(typeIdentificateur, nomIdentificateur);
        } else {
            cout<<"erreur identificateur attendu : R1"<<endl;
            exit(0);
        }
    } else if(motCourant.unite==MOTCLE && motCourant.lexeme=="chaine"){
        typeIdentificateur = "chaine";
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            nomIdentificateur = motCourant.lexeme;
            motCourant=uniteSuivanteSansCommentaire(c);
            programmePrime(typeIdentificateur,nomIdentificateur);
        } else {
            cout<<"erreur identificateur attendu : R1"<<endl;
        }
    } else if(motCourant.unite==MOTCLE && motCourant.lexeme=="void"){
        typeIdentificateur = "void";
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            nomIdentificateur = motCourant.lexeme; // sémantique
            if(identificateurExisteDansTS(nomIdentificateur)){
                cout<<"ERREUR: identificateur deja definit"<<endl;
                exit(0);
            }else{
                ajouterFonction(nomIdentificateur,typeIdentificateur,tableDeSymboles);
            }
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite==PAROVR){
                motCourant=uniteSuivanteSansCommentaire(c);
                listeParms();
                if(motCourant.unite==PARFRM){
                    motCourant=uniteSuivanteSansCommentaire(c);
                    if(motCourant.unite==ACOLOVR){
                        motCourant=uniteSuivanteSansCommentaire(c);
                        listeDeclarations();
                        listeInstructions();
                        if(motCourant.unite==ACOLFRM){
                            motCourant=uniteSuivanteSansCommentaire(c);
                            declarationFonction();
                        }else {
                            cout<<"erreur } attendu  : R1    1"<<endl;
                        }
                    }else {
                        cout<<"erreur { attendu  : R1"<<endl;
                    }
                }else {
                    cout<<"erreur ) attendu : R1   1"<<endl;
                }
        }else {
            cout<<"erreur ( attendu : R1"<<endl;
        }
    }
    }
}
//==========================================================================
void programmePrime(string typeIdentificateur, string nomIdentificateur){
    if(motCourant.unite == CROOVR || motCourant.unite==PTVIR || motCourant.unite==VIR){

        bool variableAjoute = declarateurPrime(typeIdentificateur, nomIdentificateur);
        if(!variableAjoute){
            if(!identificateurExisteDansTS(nomIdentificateur)){
                ajouterVariable(nomIdentificateur,typeIdentificateur,false,tableDeSymboles);
            }else if(!tableDeSymboles[tableDeSymboles.size()-1]->estFonction() && !dynamic_cast<Variable*>(tableDeSymboles[tableDeSymboles.size()-1])->getEstTableau()){
                  cout<<"ERREUR: variable declaree 2 fois"<<endl;
                  exit(0);
            }
        }
        listeDeclarateursPrime(typeIdentificateur);
        if(motCourant.unite==PTVIR){
            motCourant=uniteSuivanteSansCommentaire(c);
            programme();
        } else {
            cout<<"erreur ; attendue : R2";
            exit(0);
        }
    } else if (motCourant.unite==PAROVR){
        if(identificateurExisteDansTS(nomIdentificateur)){
                cout<<"ERREUR: identificateur deja definit"<<endl;
                exit(0);
            }else{
                ajouterFonction(nomIdentificateur,typeIdentificateur,tableDeSymboles);

            }
        motCourant=uniteSuivanteSansCommentaire(c);
        listeParms();
        if(motCourant.unite==PARFRM){
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite==ACOLOVR){
                motCourant=uniteSuivanteSansCommentaire(c);
                listeDeclarations();
                listeInstructions();
                if(motCourant.unite==ACOLFRM){
                    motCourant=uniteSuivanteSansCommentaire(c);
                    declarationFonction();
                }else {
                    cout<<"erreur } attendue : R2    "<<endl;
                }
            }else {
                cout<<"erreur { attendue : R2"<<endl;
            }
        }else {
                cout<<"erreur ) attendue : R2"<<endl;
            }
    }else {
            cout<<"erreur ; ou [ ou ( attendue : R2"<<endl;
        }
}
//==========================================================================
void declarationFonction(){
    if(motCourant.unite==MOTCLE && motCourant.lexeme=="int"){
        string typeRetour = motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            string nomIdentificateur = motCourant.lexeme;
            if(identificateurExisteDansTS(nomIdentificateur)){
                cout<<"ERREUR: identificateur deja definit"<<endl;
                exit(0);
            }else{
                ajouterFonction(nomIdentificateur,typeRetour,tableDeSymboles);

            }
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite==PAROVR){
                motCourant=uniteSuivanteSansCommentaire(c);
                listeParms();
                if(motCourant.unite==PARFRM){
                    motCourant=uniteSuivanteSansCommentaire(c);
                    if(motCourant.unite==ACOLOVR){
                        motCourant=uniteSuivanteSansCommentaire(c);
                        listeDeclarations();
                        listeInstructions();
                        if(motCourant.unite==ACOLFRM){
                            motCourant=uniteSuivanteSansCommentaire(c);
                            declarationFonction();
                        }else {
                            cout<<"erreur } attendu  : R1    2"<<endl;
                        }
                    }else {
                        cout<<"erreur { attendu  : R1 "<<endl;
                    }
                }else {
                    cout<<"erreur ) attendu : R1    2"<<endl;
                }
        }else {
            cout<<"erreur ( attendu : R1"<<endl;
        }
    }
    } else if(motCourant.unite==MOTCLE && motCourant.lexeme=="chaine"){
        string typeRetour = motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            string nomIdentificateur = motCourant.lexeme;
            if(identificateurExisteDansTS(nomIdentificateur)){
                cout<<"ERREUR: identificateur deja definit"<<endl;
                exit(0);
            }else{
                ajouterFonction(nomIdentificateur,typeRetour,tableDeSymboles);
            }
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite==PAROVR){
                motCourant=uniteSuivanteSansCommentaire(c);
                listeParms();
                if(motCourant.unite==PARFRM){
                    motCourant=uniteSuivanteSansCommentaire(c);
                    if(motCourant.unite==ACOLOVR){
                        motCourant=uniteSuivanteSansCommentaire(c);
                        listeDeclarations();
                        listeInstructions();
                        motCourant=uniteSuivanteSansCommentaire(c);
                        if(motCourant.unite==ACOLFRM){
                            motCourant=uniteSuivanteSansCommentaire(c);
                            declarationFonction();
                        }else {
                            cout<<"erreur } attendu  : R1       3"<<endl;
                        }
                    }else {
                        cout<<"erreur { attendu  : R1"<<endl;
                    }
                }else {
                    cout<<"erreur ) attendu : R1     3"<<endl;
                }
        }else {
            cout<<"erreur ( attendu : R1"<<endl;
        }
    }
    } else if(motCourant.unite==MOTCLE && motCourant.lexeme=="void"){
        string typeRetour = motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            string nomIdentificateur = motCourant.lexeme;
            if(identificateurExisteDansTS(nomIdentificateur)){
                cout<<"ERREUR: identificateur deja definit"<<endl;
                exit(0);
            }else{
                ajouterFonction(nomIdentificateur,typeRetour,tableDeSymboles);
            }
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite==PAROVR){
                motCourant=uniteSuivanteSansCommentaire(c);
                listeParms();
                if(motCourant.unite==PARFRM){
                    motCourant=uniteSuivanteSansCommentaire(c);
                    if(motCourant.unite==ACOLOVR){
                        motCourant=uniteSuivanteSansCommentaire(c);
                        listeDeclarations();
                        listeInstructions();
                        motCourant=uniteSuivanteSansCommentaire(c);
                        if(motCourant.unite==ACOLFRM){
                            motCourant=uniteSuivanteSansCommentaire(c);
                            declarationFonction();
                        }else {
                            cout<<"erreur } attendu  : R1     4"<<endl;
                        }
                    }else {
                        cout<<"erreur { attendu  : R1"<<endl;
                    }
                }else {
                    cout<<"erreur ) attendu : R1     4"<<endl;
                }
        }else {
            cout<<"erreur ( attendu : R1"<<endl;
        }
    }
    }
}
//==========================================================================
void listeDeclarations()
{
    listeDeclarationsPrime();
}
//==========================================================================
void listeDeclarationsPrime(){
    string  typeIdentificateur;
    if(motCourant.unite==MOTCLE && motCourant.lexeme=="int"){
        typeIdentificateur= motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        listeDeclarateurs(typeIdentificateur);
        if(motCourant.unite==PTVIR){
            motCourant=uniteSuivanteSansCommentaire(c);
            listeDeclarationsPrime();
        }else{
            cout<<"erreur de compilation: Point virgule attendue R3"<<endl;
        }
    }
    else if(motCourant.unite==MOTCLE && motCourant.lexeme=="chaine")
    {
        typeIdentificateur= motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        listeDeclarateurs(typeIdentificateur);
        if(motCourant.unite==PTVIR)
        {
            motCourant=uniteSuivanteSansCommentaire(c);
            listeDeclarationsPrime();
        }
        else
        {
            cout<<"erreur de compilation: Point virgule attendue R3"<<endl;
        }
    }
}
//==========================================================================
void listeDeclarateurs(string typeIdentificateur){
    if(motCourant.unite==IDENT)
    {
        declarateur(typeIdentificateur);
        listeDeclarateursPrime(typeIdentificateur);
    }
}
//==========================================================================
void listeDeclarateursPrime(string typeIdentificateur)
{
    if(motCourant.unite==VIR)
    {
        motCourant=uniteSuivanteSansCommentaire(c);
        declarateur(typeIdentificateur);
        listeDeclarateursPrime(typeIdentificateur);
    }

}
//==========================================================================
void declarateur(string typeIdentificateur)
{
    string nomIdentificateur;
    if(motCourant.unite==IDENT)
    {
        nomIdentificateur=motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        bool variableAjoutee= declarateurPrime(typeIdentificateur,nomIdentificateur);
        if(!variableAjoutee){
            if(!tableDeSymboles[tableDeSymboles.size()-1]->estFonction()){
                if(identificateurExisteDansTS(nomIdentificateur)){
                    cout<<"Erreur identifiteur est declare 2 fois"<<endl;
                    exit(0);
                }else{
                     ajouterVariable(nomIdentificateur, typeIdentificateur, false,tableDeSymboles);
                }
            }else{

                Fonction* fun =dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
                if(fun->rechercheVariableLocale(nomIdentificateur)){ //verifier aussi les arguments
                    cout<<"Erreur "<< nomIdentificateur<<"est declare 2 fois"<<endl;
                    exit(0);
                }else{
                     fun->ajouterVariableLocale(nomIdentificateur, typeIdentificateur, false);
                }
            }
        }
    } else {
        cout<<"erreur, identificateur attendu"<<endl;
    }

}
//==========================================================================
bool declarateurPrime(string typeIdentificateur, string nomIdentificateur)
{
    bool variableAjoutee=false;
    if(motCourant.unite==CROOVR)
    {
        if(!tableDeSymboles[tableDeSymboles.size()-1]->estFonction()){
            if(identificateurExisteDansTS(nomIdentificateur)){
                cout<<"Erreur identifiteur est declare 2 fois"<<endl;
                exit(0);
            }else{
                 ajouterVariable(nomIdentificateur, typeIdentificateur, true,tableDeSymboles);
            }
            variableAjoutee=true;
        }else{
            Fonction* fun =dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
            if(fun->rechercheVariableLocale(nomIdentificateur)){ //verifier aussi les arguments
                cout<<"Erreur "<< nomIdentificateur<<"est declare 2 fois"<<endl;
                exit(0);
            }else{
                 fun->ajouterVariableLocale(nomIdentificateur, typeIdentificateur, true);                 variableAjoutee=true;
            }
            variableAjoutee=true;
        }
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==CONSTINT)
        {
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite== CROFRM)
            {
                motCourant=uniteSuivanteSansCommentaire(c);
            }
            else
            {
                cout<<"erreur ] attendu :R10"<<endl;

            }
        }
        else
        {
            cout<<"erreur CONSTINT attendu  : R10"<<endl;
        }
    }
    return variableAjoutee;

}

//==========================================================================
string type(){
    if(motCourant.unite==MOTCLE && (motCourant.lexeme=="void")){
         motCourant=uniteSuivanteSansCommentaire(c);
         return "void";
    }else if(motCourant.unite==MOTCLE && (motCourant.lexeme=="int")){
         motCourant=uniteSuivanteSansCommentaire(c);
         return "int";
    }else if(motCourant.unite==MOTCLE && (motCourant.lexeme=="chaine")){
         motCourant=uniteSuivanteSansCommentaire(c);
         return "chaine";
    }else{
        cout<<"erreur type attendu : R12"<<endl;
    }
}
//==========================================================================
void listeParms(){
    if(motCourant.unite==MOTCLE && (motCourant.lexeme == "int" || motCourant.lexeme=="chaine")){
        parm();
        listeParmsPrime();
    } //epsilon
}
//================================================

void listeParmsPrime(){
    if(motCourant.unite==VIR){
        motCourant=uniteSuivanteSansCommentaire(c);
        parm();
        listeParmsPrime();
    }
    //epsilon
}
//==========================================================================
void parm(){
    string nomArgument;
    string typeArgument;
    if(motCourant.unite==MOTCLE && motCourant.lexeme=="int"){
        typeArgument="int";
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
             nomArgument=motCourant.lexeme;
             Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
            if(!fun->rechercheArgument(nomArgument)){
                fun->ajouterArgument(nomArgument,typeArgument,false);
            }else{
                cout<<"ERREUR: argument declare 2 fois"<<endl;
            }
            motCourant=uniteSuivanteSansCommentaire(c);
        }else {
            cout<<"erreur identificateur attendu  : R15"<<endl;
        }
    }else if(motCourant.unite==MOTCLE && motCourant.lexeme=="chaine"){
        typeArgument="chaine";
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==IDENT){
            nomArgument=motCourant.lexeme;
            Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
            if(!fun->rechercheArgument(nomArgument)){
                fun->ajouterArgument(nomArgument,typeArgument,false);
            }else{
                cout<<"ERREUR: argument declare 2 fois"<<endl;
                exit(0);
            }
            motCourant=uniteSuivanteSansCommentaire(c);
        }else {
            cout<<"erreur identificateur attendu  : R15"<<endl ;
        }
    } else {
        cout<<"erreur 'int' ou 'chaine' attendus  : R15"<<endl;
    }
}
//==========================================================================
void listeInstructions(){
    if((motCourant.unite==MOTCLE && (motCourant.lexeme=="for" || motCourant.lexeme=="while" || motCourant.lexeme=="if" || motCourant.lexeme=="return") ) || motCourant.unite==ACOLOVR || motCourant.unite==IDENT){
        listeInstructionsPrime();
        if(!typeRetourVerifie && !bloc()){
            Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
            if(fun->getTypeRetour()!="void"){
                cout<<"ERREUR: la fonction <<"<<fun->getNom()<<">> doit contenir une instruction 'return'"<<endl;
                exit(0);
            }
        }else{
            typeRetourVerifie=false;
        }

    }
}
//==========================================================================
void listeInstructionsPrime(){
     Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
     string typeRetour=fun->getTypeRetour();
     if(typeRetour=="void"){
         if((motCourant.unite==MOTCLE && (motCourant.lexeme=="for" || motCourant.lexeme=="while" || motCourant.lexeme=="if" || motCourant.lexeme=="return") ) || motCourant.unite==ACOLOVR || motCourant.unite==IDENT){
            instruction();
            listeInstructionsPrime();
         }
     }else{
         if(!typeRetourVerifie){
            if((motCourant.unite==MOTCLE && (motCourant.lexeme=="for" || motCourant.lexeme=="while" || motCourant.lexeme=="if" || motCourant.lexeme=="return") ) || motCourant.unite==ACOLOVR || motCourant.unite==IDENT){
                instruction();
                listeInstructionsPrime();
            }
         }

     }
}
//==========================================================================
void instruction(){
    if(motCourant.unite==MOTCLE && (motCourant.lexeme=="for" || motCourant.lexeme=="while")){
        iteration();
    }else if(motCourant.unite==MOTCLE && motCourant.lexeme=="if"){
        selection();
    }else if(motCourant.unite==MOTCLE && motCourant.lexeme=="return"){
        typeRetourVerifie=true;
        saut();
    }else if(motCourant.unite==ACOLOVR){
        bloc();
    }else if(motCourant.unite==IDENT){
        string nomIdentificateur=motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
        terme(nomIdentificateur);
    }
}
//==========================================================================
void terme(string nomIdentificateur){
    if(motCourant.unite==CROOVR || motCourant.unite==AFFECT){
        Variable* var=estDefinitPourFonction(nomIdentificateur,tableDeSymboles);
        if(!var){
            exit(0);
        }else{
            variablePrime(var);
        }
        if(motCourant.unite==AFFECT){
            motCourant=uniteSuivanteSansCommentaire(c);
            string typeExpression2=expression();///les operandes ont le meme type
             if(var->getType()!=typeExpression2){
                cout<<"ERREUR: incompatibilite de types"<<endl;
                 exit(0);
             }
            if(motCourant.unite==PTVIR){
                motCourant=uniteSuivanteSansCommentaire(c);
            }else {
                cout<<"erreur ; attendu  : R19"<<endl;
            }
        }else {
            cout<<"erreur = attendu  : R19"<<endl;
        }
    }else if(motCourant.unite==PAROVR){
        //appel fonction
        motCourant=uniteSuivanteSansCommentaire(c);
        Identificateur* fun=identificateurExisteDansTS(nomIdentificateur);
        if(!fun){
            cout<<"Fonction n'est pas definit"<<endl;
            exit(0);
        }else{
            if(!fun->estFonction()){
                cout<<"ERREUR :"<<fun->getNom()<<"n'est pas une fonction"<<endl;
                exit(0);
            }
        }
        listeExpressions(dynamic_cast<Fonction*>(fun));
        if(motCourant.unite==PARFRM){
            motCourant=uniteSuivanteSansCommentaire(c);
            if(motCourant.unite==PTVIR){
                motCourant=uniteSuivanteSansCommentaire(c);
            }else {
                cout<<"erreur ; attendu  : R19"<<endl;
            }
        }else{cout<<"erreur ) attendu : R19"<<endl;}
    }else {
        cout<<"erreur [ ou ( ou = attendu  : R19"<<endl;
    }
}
//==========================================================================
void iteration(){
    if(motCourant.unite==MOTCLE && motCourant.lexeme=="for"){
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite == PAROVR ){
            motCourant=uniteSuivanteSansCommentaire(c);
            affectation();
            if(motCourant.unite == PTVIR){
                motCourant=uniteSuivanteSansCommentaire(c);
                condition();
                if(motCourant.unite ==PTVIR){
                    motCourant=uniteSuivanteSansCommentaire(c);
                    affectation();
                    if(motCourant.unite == PARFRM){
                        motCourant=uniteSuivanteSansCommentaire(c);
                        instruction();
                    } else {
                        cout<<"erreur ) attendue  : R20"<<endl;
                    }
                } else {
                    cout<<"erreur ; attendue  : R20"<<endl;
                }
            } else {
                cout<<" erreur ; attendue  : R20" <<endl;
            }
        } else {
            cout<<" erreur ( attendue  : R20"<<endl;
        }
    } else if( motCourant.unite==MOTCLE && motCourant.lexeme== "while"){
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==PAROVR){
            motCourant=uniteSuivanteSansCommentaire(c);
            condition();
            if(motCourant.unite == PARFRM ){
                motCourant=uniteSuivanteSansCommentaire(c);
                instruction();
            } else {
                cout<<"erreur ) attendue  : R20"<<endl;
            }
        } else {
            cout<<"erreur ( attendue  : R20"<<endl;
        }
    } else {
        cout<<"erreur for ou while attendus"<<endl;
    }
}
//==========================================================================
void selection(){
    if(motCourant.unite ==MOTCLE && motCourant.lexeme == "if"){
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==PAROVR){
            motCourant=uniteSuivanteSansCommentaire(c);
            condition();
            if(motCourant.unite==PARFRM){
                motCourant=uniteSuivanteSansCommentaire(c);
                instruction();
                selectionPrime();
            }else{
                cout<<"erreur ) attendu  : R21"<<endl;
            }
        }else{
            cout<<"erreur ( attendu  : R21"<<endl;
        }
    } else {
        cout<<"erreur 'if' attendue  : R21"<<endl;
    }
}

//================================================**
void selectionPrime(){
    if(motCourant.unite==MOTCLE && motCourant.lexeme=="else"){
        motCourant=uniteSuivanteSansCommentaire(c);
        instruction();
    }
    //tout autre sera un epsilon donc on ne lit rien pour cette fonction

}
//==========================================================================
void saut(){
    if(motCourant.unite == MOTCLE && motCourant.lexeme == "return"){
        motCourant=uniteSuivanteSansCommentaire(c);
        sautPrime();
    } else{
        cout<<"erreur 'return' attendue R23"<<endl;
        //exit(0);
    }
}
//==========================================================================
void sautPrime(){
    Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
    if(motCourant.unite==PTVIR){
        if(fun->getTypeRetour()!="void"){
            cout<<"ERREUR: type de retour de la fonction "<<fun->getNom()<<" est void"<<endl;
            exit(0);
        }
        motCourant=uniteSuivanteSansCommentaire(c);
    } else if (motCourant.unite == PAROVR || motCourant.unite==MOINS || motCourant.unite==IDENT || motCourant.unite==CONSTINT || motCourant.unite==CONSTCHAINE){
        if(fun->getTypeRetour()!="void"){
            string typeExpression= expression();
            if(typeExpression!=fun->getTypeRetour()){
                 cout<<"ERREUR: type de retour de la fonction <<"<<fun->getNom()<<">> est incompatible"<<endl;
                 exit(0);
            }
            if(motCourant.unite==PTVIR){
                motCourant=uniteSuivanteSansCommentaire(c);
            } else{
                cout<<"erreur ; attendue R24"<<endl;
            }
        }else{
              cout<<"ERREUR: type de retour de la fonction "<<fun->getNom()<<" est void"<<endl;
              exit(0);
        }
    } else {
        cout<<"erreur ; ou premier de <expression> attendus R24"<<endl;
    }
}
//==========================================================================
void affectation(){
    if(motCourant.unite == IDENT){
        string lValueType=variable();
        if(motCourant.unite==AFFECT){
            motCourant=uniteSuivanteSansCommentaire(c);
            string rValueType=expression();//recuperer le type d'evaluation
            if(lValueType!=rValueType){
                cout<<"ERREUR:affectation avec types incompatibles"<<endl;
                exit(0);
            }
        } else{
            cout<<"erreur, = attendue R25"<<endl;
        }
    } else {
        cout<<"erreur, identificateur attendu R25"<<endl;
    }
}
//==========================================================================
int bloc(){
    static int estDansLeBloc=0;
    if(motCourant.unite == ACOLOVR){
        estDansLeBloc++;
        motCourant=uniteSuivanteSansCommentaire(c);
        listeInstructions();
        if(motCourant.unite == ACOLFRM){
            estDansLeBloc--;
            motCourant=uniteSuivanteSansCommentaire(c);

        } else{
            cout<<"erreur } attendue R26"<<endl;
        }
    } //else{
        //cout<<"erreur { attendue R26"<<endl;
    //}


    return estDansLeBloc;
}
//==========================================================================
string variable(){
    string nomIdentificateur;
    string typeIdentificateur;
    if(motCourant.unite == IDENT){
        nomIdentificateur=motCourant.lexeme;
        Fonction* fun=dynamic_cast<Fonction*>(tableDeSymboles[tableDeSymboles.size()-1]);
        Variable* var=fun->rechercheVariableLocale(nomIdentificateur);
        if(!var){
            var=fun->rechercheArgument(nomIdentificateur);
            if(!var){
                if(!identificateurExisteDansTS(nomIdentificateur)){
                    cout<<"ERREUR: la variable| "<<motCourant.lexeme<<" | est non declaree"<<endl;
                    typeIdentificateur="";
                }
                else{
                    var = dynamic_cast<Variable*>(identificateurExisteDansTS(nomIdentificateur));
                    typeIdentificateur= var->getType();
                }
            } else {
                typeIdentificateur= var->getType();
            }
        }else{
            typeIdentificateur= var->getType();
        }

        motCourant=uniteSuivanteSansCommentaire(c);
        variablePrime(var);
        return typeIdentificateur;
    } else {
        cout<<"erreur, identificateur attendu R28"<<endl;
        return "";
    }
}
//==========================================================================
void variablePrime(Variable* var){
    if(motCourant.unite == CROOVR){
        if(!var->getEstTableau()){
             cout<<"ERREUR: la variable| "<<var->getNom()<<" | n'est pas un tableau"<<endl;
             exit(0);
        }
        motCourant=uniteSuivanteSansCommentaire(c);
        string typeExpression=expression();
        if(typeExpression!="int"){
            cout<<"ERREUR: indice de tableau n'est pas entier"<<endl;
            exit(0);
        }
        if(motCourant.unite==CROFRM){
            motCourant=uniteSuivanteSansCommentaire(c);
        } else {
            cout<<"erreur, ] attendue R29"<<endl;
        }
    }else{
        if(var->getEstTableau()){
             cout<<"ERREUR: la variable| "<<var->getNom()<<" | est un tableau"<<endl;
             exit(0);
        }
    }
}
//===========================================================
void binaryComp()
{
    if(motCourant.unite==INF || motCourant.unite==SUP || motCourant.unite==INFEG || motCourant.unite==SUPEG || motCourant.unite==EGAL || motCourant.unite==DIF){
        motCourant=uniteSuivanteSansCommentaire(c);
    }else{
        cout<<"erreur '<' || '>' ||'<=' || '>=' || '==' || '!=' R40"<<endl;
    }
}

//==========================================================================
string binaryOp()
{
    string operation="";
    if(motCourant.unite==PLUS || motCourant.unite==MOINS || motCourant.unite==MULTI||motCourant.unite==DIV){
        operation=motCourant.lexeme;
        motCourant=uniteSuivanteSansCommentaire(c);
    }else{
        cout<<"erreur '+' || '-' ||'*' || '/' R38"<<endl;
    }
    return operation;
}
//==========================================================================
void binaryRel()
{
    if(motCourant.unite==AND || motCourant.unite==OR){
        motCourant=uniteSuivanteSansCommentaire(c);
    }else{
        cout<<"erreur '&&' || '||' attendu R39"<<endl;
    }
}
//==========================================================================
void conditionDeuxPrime(){
    if(motCourant.unite==AND || motCourant.unite==OR){
        binaryRel();
        conditionPrime();
        conditionDeuxPrime();
    }
}
//==========================================================================
void conditionPrime(){
    if(motCourant.unite==NOT){
        motCourant=uniteSuivanteSansCommentaire(c);
        if(motCourant.unite==PAROVR){
            motCourant=uniteSuivanteSansCommentaire(c);
            condition();
            if(motCourant.unite==PARFRM){
                motCourant=uniteSuivanteSansCommentaire(c);
            }else{
                cout<<"erreur: ')' attendue R36"<<endl;
            }
        }else{
            cout<<"erreur: '(' attendue R36"<<endl;
        }
    }else if(motCourant.unite==PAROVR || motCourant.unite==MOINS || motCourant.unite==CONSTINT || motCourant.unite==IDENT){
           string typeExpression1= expression();
           if(typeExpression1=="void"){
            cout<<"ERREUR: comparaison incompatible avec 'void'"<<endl;
            exit(0);
           }
           binaryComp();
           string typeExpression2=expression();
           if(typeExpression2=="void"){
                cout<<"ERREUR: comparaison incompatible avec 'void'"<<endl;
                exit(0);
           }
    }else{
        cout<<"erreur ( ou - ou constante ou identificateur ou ! attendus R36" <<endl;
    }
}
//==========================================================================
void condition(){
    if(motCourant.unite == NOT ||motCourant.unite ==PAROVR ||motCourant.unite ==MOINS ||motCourant.unite ==IDENT ||motCourant.unite ==CONSTINT){
        conditionPrime();
        conditionDeuxPrime();
    }
}

//==========================================================================
void listeExpressions(Fonction* fun){
     if(motCourant.unite==PAROVR || motCourant.unite==MOINS || motCourant.unite==IDENT ||motCourant.unite==CONSTCHAINE ||  motCourant.unite==CONSTINT  ){
         vector<string> argRencontres; //un vecteur contenant les types des arguments recontres de la fonction (implicitement nombre aussi des arg)
         string typeExpression=expression();
         argRencontres.push_back(typeExpression);
         listeExpressionsPrime(argRencontres);
         if(argRencontres.size()==fun->nombreArguments()){
            for(int i=0;i<argRencontres.size();i++){
                Variable* var=dynamic_cast<Variable*>(fun->getArguments()[i]);
                if(argRencontres[i]!=var->getType()){
                    cout<<"ERREUR: type d'argument "<<i+1<<" dans l'appel de la fonction <<"<<fun->getNom()<<">> n'est pas compatible" <<endl;
                    exit(0);
                }
            }
         }else{
             cout<<"ERREUR: appel de la fonction <<"<<fun->getNom()<<">> avec un nombre d'arguments differents"<<endl;
             exit(0);
         }
     }
}

//==========================================================================
void listeExpressionsPrime(vector<string>& argRencontres ){
    if(motCourant.unite==VIR){
        motCourant=uniteSuivanteSansCommentaire(c);
        string typeExpression=expression();
        argRencontres.push_back(typeExpression);
        listeExpressionsPrime(argRencontres);
    }
}
//==========================================================================
string  termePrime(string nomIdentificateur)
{
    if(motCourant.unite==CROOVR ){
        Variable* var=estDefinitPourFonction(nomIdentificateur,tableDeSymboles);
        if(!var)
        {
            cout<<"variable n'est pas definit"<<endl;
            exit(0);
        }
        else
        {
            variablePrime(var);
        }
         string typeVariable= expressionPrime();
         if(typeVariable==""){
                return var->getType();
          }else{
              if(typeVariable!=var->getType()){
                cout<<"ERREUR :types incompatibles"<<endl;
                 exit(0);
              }else{
                  return typeVariable;
              }
          }

    }
    else if(motCourant.unite==PLUS || motCourant.unite==MOINS ||motCourant.unite==MULTI ||motCourant.unite==DIV )
    {
        Variable* var=estDefinitPourFonction(nomIdentificateur,tableDeSymboles);
        if(!var)
        {
            cout<<"variable n'est pas definit"<<endl;
            exit(0);
        }
        else
        {
            if(var->getEstTableau())
            {
                cout<<"operation incompatible avec le type tableau"<<endl;
                exit(0);
            }
        }
         string typeVariable= expressionPrime();
         if(typeVariable==""){
                return var->getType();
          }else{
              if(typeVariable!=var->getType()){
                cout<<"ERREUR :types incompatibles"<<endl;
                 exit(0);
              }else{
                  return typeVariable;
              }
          }
    }else if(motCourant.unite==PAROVR){
        Identificateur* fun=identificateurExisteDansTS(nomIdentificateur);
        if(!fun){
            cout<<"Fonction n'est pas definit"<<endl;
            exit(0);
        }else{
            if(!fun->estFonction()){
                cout<<"ERREUR :"<<fun->getNom()<<"n'est pas une fonction"<<endl;
                exit(0);
            }
        }
        motCourant=uniteSuivanteSansCommentaire(c);
        listeExpressions(dynamic_cast<Fonction*>(fun));
        if(motCourant.unite==PARFRM){
              motCourant=uniteSuivanteSansCommentaire(c);
              string typeRetourFonction=dynamic_cast<Fonction*>(fun)->getTypeRetour();
              string typeCompatible=expressionPrime();
              if(typeCompatible==""){
                return typeRetourFonction;
              }else{
                  if(typeRetourFonction!=typeCompatible){
                    cout<<"ERREUR :types incompatibles"<<endl;
                     exit(0);
                  }else{
                      return typeRetourFonction;
                  }
              }
        }else{
            cout<<"erreur: ')' attendue R31"<<endl;
        }
    }
    Variable* var=estDefinitPourFonction(nomIdentificateur,tableDeSymboles);
    return var->getType();
}
//==========================================================================
string expression(){
    string typeExpression1;
    if(motCourant.unite==PAROVR){
        motCourant=uniteSuivanteSansCommentaire(c);
        typeExpression1=expression();
        if(motCourant.unite==PARFRM){
            motCourant=uniteSuivanteSansCommentaire(c);
            string typeExpression2=expressionPrime();
            if(typeExpression2!=""){
                if(typeExpression1!=typeExpression2){
                   cout<<"ERREUR:operation binaire sur deux type differents"<<endl;
                   exit(0);
                }
                return typeExpression2;
            }else{
                return typeExpression1;
            }

        }else{
            cout<<"erreur: ')' attendue R30"<<endl;
        }
    }else if(motCourant.unite==MOINS){
         motCourant=uniteSuivanteSansCommentaire(c);
         typeExpression1=expression();
         if(typeExpression1!="int"){
            cout<<"ERREUR: incompatibilite avec le signe '-'"<<endl;
            exit(0);
         }
         string typeExpression2=expressionPrime();
         if(typeExpression2==""){
            return typeExpression1;
         }else{
             if(typeExpression1==typeExpression2){
                return typeExpression2;
             }else{
                 cout<<"ERREUR: incompatibilite de types"<<endl;
                 exit(0);
             }
         }
    }else if(motCourant.unite==IDENT){
         string nomIdentificateur=motCourant.lexeme;
         motCourant=uniteSuivanteSansCommentaire(c);
         typeExpression1=termePrime(nomIdentificateur);
         return typeExpression1;
    }else if(motCourant.unite==CONSTINT){
         string typeExpression;
         typeExpression="int";
         motCourant=uniteSuivanteSansCommentaire(c);
         typeExpression1=expressionPrime();
         if(typeExpression1==""){
            return  typeExpression;
         }else{
             if(typeExpression==typeExpression1){
                return typeExpression;
             }else{
                 cout<<"ERREUR: incompatibilite de types"<<endl;
                 exit(0);
             }
         }
    }else if(motCourant.unite==CONSTCHAINE){
         string typeExpression;
         typeExpression="chaine";
         motCourant=uniteSuivanteSansCommentaire(c);
         typeExpression1=expressionPrime();
         if(typeExpression1==""){
            return  typeExpression;
         }else{
             if(typeExpression==typeExpression1){
                return typeExpression;
             }else{
                 cout<<"ERREUR: incompatibilite de types"<<endl;
                 exit(0);
             }
         }
    }else{
        cout<<"erreur: '(' || '-' || 'identificateur' || 'constint' attendue R30"<<endl;
    }
}
//==========================================================================
string expressionPrime(){
    if(motCourant.unite==PLUS || motCourant.unite==MOINS ||motCourant.unite==MULTI ||motCourant.unite==DIV){
        string operation=binaryOp(); //verification de "+" de  la concatenation entre chaines
        string typeSuivant=expression();
        string type3= expressionPrime();
        if(type3==""){
            return typeSuivant;
        }
        if(type3!=typeSuivant){
               cout<<"ERREUR :Les operandes sont de types imcompatible"<<endl;
               exit(0);
        }else{
            if(operation!="+"){
                 if(typeSuivant=="chaine"){ //eliminer autre que le "+"
                     cout<<"ERREUR :les operartions binaires ne peuvent pas s'effectuer sur des chaines "<<endl;
                     exit(0);
                }
            }
        }
    }else{
        return "";
    }
}


#endif // FONCTIONSSYNTAXIQUE_H_INCLUDED
