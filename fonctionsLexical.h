#ifndef FONCTIONSLEXICAL_H_INCLUDED
#define FONCTIONSLEXICAL_H_INCLUDED
#define NOMBRE_DES_MOTS_CLES 10
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

enum uniteLexicale   //une enumeration contenant les unitees  lexicale
{
    PTVIR, VIR, ACOLOVR, ACOLFRM, PLUS, MOINS, MULTI, CROOVR, CROFRM, PAROVR, PARFRM,
    SUPEG, SUP, INFEG, INF, EGAL, AFFECT, DIF, NOT, AND, OR, COMMENT, DIV,
    CONSTINT, CONSTCHAINE, MOTCLE, IDENT, ERREUR
};
//==========================================================================
typedef struct    //la la form de la paire a retourner dans chaque appel de la fonction  uniteSuivante()
{
    uniteLexicale unite;
    string lexeme;
} paireUniteSuivante;
paireUniteSuivante uniteSuivante(char& c);
paireUniteSuivante uniteSuivanteSansCommentaire(char& c){
    paireUniteSuivante p = uniteSuivante(c);
    return (p.unite == COMMENT) ? uniteSuivante(c):p;
}


//==========================================================================
string motsCles[10]= {"int","void","chaine","for","while","if","return","else","lire","ecrire"}; //tableau contenant les mots cles
//==========================================================================
typedef struct noeud  //representation d'un noeud de hachage
{
    string chaine;
    struct noeud* suivant;
} Noeud;
//==========================================================================
typedef struct table_mots_cles
{
    Noeud* sommet;
} table_mots_cles;
//==========================================================================
table_mots_cles tableDeHashage[NOMBRE_DES_MOTS_CLES]; //table de hachage des mots cles
//==========================================================================
/*int hashing(string chaine) //fonction de hachage d'une chaine de caracteres
{
    int code=0;
    for(int i=0; i<chaine.size(); i++)
    {
        code=code+static_cast<int>(chaine[i]);
    }
    return code%NOMBRE_DES_MOTS_CLES;  //code entre 0---9
}*/

unsigned long long hashing(const std::string& str) {
    const  int p = 31; // Prime number to avoid collisions
    const  int m = 1e9 + 9; // Large prime number to avoid overflow

    long long hash_value = 0;
    long long p_pow = 1;

    for (char c : str) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash_value%NOMBRE_DES_MOTS_CLES;
}

//==========================================================================
void insererDansLaTableDeHashage(string chaine) //inserer dans la table de hachage des mots cles un noeud de hachage
{
    int code=hashing(chaine);
    Noeud* noeud =new Noeud;
    if(tableDeHashage[code].sommet==NULL)
    {
        noeud->chaine=chaine;
        noeud->suivant=NULL;
        tableDeHashage[code].sommet=noeud;
    }
    else
    {
        noeud->chaine=chaine;
        noeud->suivant=tableDeHashage[code].sommet;
        tableDeHashage[code].sommet=noeud;
    }
}
//==========================================================================
void remplirTableMotsClesHachee() //remplissage des noeud de hachage des
{
    for(int i=0; i<NOMBRE_DES_MOTS_CLES; i++)
    {
        insererDansLaTableDeHashage(motsCles[i]);
    }

}
//==========================================================================
int hash_search(string chaine) //retourne le code de hachage de "chaine" si c'est un mot cle
{
    //-1 sinon(identificateur)
    int code= hashing(chaine);
    for(Noeud* q=tableDeHashage[code].sommet; q!=NULL; q=q->suivant)
    {
        int size_mot_cle=(q->chaine).size();
        int size_char=chaine.size();
        if(size_char==size_mot_cle)  //si le mot recherche a la meme longueur que le mot cle hachee
        {
            int flag=0;
            for(int  i=0; i<size_char; i++)
            {
                if(q->chaine[i]!=chaine[i])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                return code;
            }
        }
    }
    return -1;
}

//==========================================================================
void afficherTableDeHachage() //affichage de la table de hachage des mots cles
{
    for(int i=0 ; i<NOMBRE_DES_MOTS_CLES; i++)
    {
        printf("%d) \n",i);
        if(tableDeHashage[i].sommet!=NULL)
        {
            Noeud *n=tableDeHashage[i].sommet;
            while(n!=NULL)
            {
                printf("| < %s > |\n",n->chaine);
                n=n->suivant;
            }
        }
    }
}
//==========================================================================
string lireContenu(char* nomFichier)  //fonction qui permet de retourner le contenu
{
    //d'un fichier texte  sous forme chaine de caractere
    ifstream fichier(nomFichier);
    if (fichier.is_open()){
        stringstream contenuFichier;
        contenuFichier << fichier.rdbuf();
        fichier.close();
        return contenuFichier.str();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier : " << nomFichier <<endl;
    }
}
//==========================================================================
string codeSource=lireContenu("C:\\Users\\ALLAOUA\\Desktop\\versionFinaleFinale\\codeSource.txt");//contenu du fichier a lire
int indice=0;//une variable globale determinant la position du caractere a lire dans la chaine codeSource
//==========================================================================
string donnerUniteLexicale(int nombre) //fonction qui permet de donner l'unite lexicale
//a partir de son code dans l'enumeration uniteLexicale ci-dessus
{
    switch(nombre)
    {
    case 0:
        return "PTVIR";
    case 1:
        return "VIR";
    case 2:
        return "ACOLOVR";
    case 3:
        return "ACOLFRM";
    case 4:
        return "PLUS";
    case 5:
        return "MOINS";
    case 6:
        return "MULTI";
    case 7:
        return "CROOVR";
    case 8:
        return "CROFRM";
    case 9:
        return "PAROVR";
    case 10:
        return "PARFRM";
    case 11:
        return "SUPEG";
    case 12:
        return "SUP";
    case 13:
        return "INFEG";
    case 14:
        return "INF";
    case 15:
        return "EGAL";
    case 16:
        return "AFFECT";
    case 17:
        return "DIF";
    case 18:
        return "NOT";
    case 19:
        return "AND";
    case 20:
        return "OR";
    case 21:
        return "COMMENT";
    case 22:
        return "DIV";
    case 23:
        return "CONSTINT";
    case 24:
        return "CONSTCHAINE";
    case 25:
        return "MOTCLE";
    case 26:
        return "IDENT";
    case 27:
        return "ERREUR";
    }
}


//==========================================================================
bool estBlanc(char c)
{
    return (c=='\n' || c=='\t' || c==' ');
}
//==========================================================================
char lireCar()
{
    return codeSource[indice++];
}
//==========================================================================
bool estChiffre(char c)
{
    return ('0'<=c && c<='9');
}
//==========================================================================
bool estLettre(char c)
{
    return ('A'<=c && c<='Z' || 'a'<=c && c<='z' );
}
//==========================================================================
paireUniteSuivante uniteSuivante(char& c)  //la fonction principale qui lire les unites lexicales identifiees dans le codeSource
{
    while(estBlanc(c))
    {
        c = lireCar();
    }
    switch(c)
    {
    case ';':
    {
        c = lireCar();
        paireUniteSuivante paire{PTVIR, ";"};
        return(paire);
    }
    case ',':
    {
        c = lireCar();
        paireUniteSuivante paire{VIR, ","};
        return(paire);
    }
    case '{':
    {
        c = lireCar();
        paireUniteSuivante paire{ACOLOVR, "{"};
        return(paire);
    }
    case '}':
    {
        c = lireCar();
        paireUniteSuivante paire{ACOLFRM, "}"};
        return(paire);
    }
    case '[':
    {
        c = lireCar();
        paireUniteSuivante paire{CROOVR, "["};
        return(paire);
    }
    case ']':
    {
        c = lireCar();
        paireUniteSuivante paire{CROFRM, "]"};
        return(paire);
    }
    case '(':
    {
        c = lireCar();
        paireUniteSuivante paire{PAROVR, "("};
        return(paire);
    }
    case ')':
    {
        c = lireCar();
        paireUniteSuivante paire{PARFRM, ")"};
        return(paire);
    }
    case '+':
    {
        c = lireCar();
        paireUniteSuivante paire{PLUS, "+"};
        return(paire);
    }
    case '-':
    {
        c = lireCar();
        paireUniteSuivante paire{MOINS, "-"};
        return(paire);
    }
    case '*':
    {
        c = lireCar();
        paireUniteSuivante paire{MULTI, "*"};
        return(paire);
    }
    case '>':
    {
        c = lireCar();
        if (c=='=')
        {
            c=lireCar();
            paireUniteSuivante paire{SUPEG, ">="};
            return(paire);
        }
        else
        {
            paireUniteSuivante paire{SUP, ">"};
            return paire;
        }
    }
    case '<':
    {
        c = lireCar();

        if (c=='=')
        {
            c=lireCar();
            paireUniteSuivante paire{INFEG, "<="};
            return(paire);
        }
        else
        {
            paireUniteSuivante paire{INF, "<"};
            return paire;
        }
    }
    case '=':
    {
        c = lireCar();

        if (c=='=')
        {
            c=lireCar();
            paireUniteSuivante paire{EGAL, "=="};
            return(paire);
        }
        else
        {
            paireUniteSuivante paire{AFFECT, "="};
            return paire;
        }
    }
    case '!':
    {
        c = lireCar();
        if (c=='=')
        {
            c=lireCar();
            paireUniteSuivante paire{DIF, "!="};
            return(paire);
        }
        else
        {
            paireUniteSuivante paire{NOT, "!"};
            return paire;
        }
    }
    case '&':
    {
        c = lireCar();
        if (c=='&')
        {
            c=lireCar();
            paireUniteSuivante paire{AND, "&&"};
            return(paire);
        }
        else
        {
            paireUniteSuivante paire{ERREUR, "'&' attendue"};
            return(paire);
        }
    }
    case '|':
    {
        c = lireCar();
        if (c=='|')
        {
            c=lireCar();
            paireUniteSuivante paire{OR, "||"};
            return(paire);
        }
        else
        {
            paireUniteSuivante paire{ERREUR, "'|' attendue"};
            return(paire);
        }
    }
    //////////////////////////////
    case '/':
    {
        c = lireCar();
        if (c=='*')
        {
            c=lireCar();
            string lexeme="";
commentRepeat:
            while(c!='*' && indice<=codeSource.size())
            {
                lexeme+=c;
                c=lireCar();
            }
            if(c=='*')
            {
                lexeme+=c;
                c = lireCar();
                while(c=='*')
                {
                    lexeme+=c;
                    c=lireCar();
                }
                if(c=='/')
                {
                    lexeme=lexeme.erase(lexeme.size()-1);
                    c=lireCar();
                    paireUniteSuivante paire{COMMENT, lexeme};
                    return(paire);
                }
                if(indice-1==codeSource.size())
                {
                    paireUniteSuivante paire{ERREUR, "commentaire incomplet"};
                    return(paire);
                }
                else
                {
                    lexeme+=c;
                    c=lireCar();
                    goto commentRepeat;
                }
            }
            if(indice-1==codeSource.size())
            {
                paireUniteSuivante paire{ERREUR, "commentaire incomplet"};
                return(paire);
            }

        }
        else
        {
            paireUniteSuivante paire{DIV, "/"};
            return(paire);
        }
    }
    ///////////////////////////////////
    case '"':
    {
        c=lireCar();
        string chaine="";

        while(c!='"' && indice<=codeSource.size())
        {
            chaine+=c;
            c=lireCar();
        }
        if(indice-1==codeSource.size())
        {
            paireUniteSuivante paire{ERREUR, "chaine non achevee"};
            return(paire);
        }
        else
        {
            c=lireCar();
            paireUniteSuivante paire{CONSTCHAINE, chaine};
            return(paire);
        }
    }

    default:
    {
        if(estChiffre(c))
        {
            string nombre="";
            nombre+=c;
            c=lireCar();
            while(estChiffre(c))
            {
                nombre+=c;
                c=lireCar();
            }
            paireUniteSuivante paire{CONSTINT, nombre};
            return(paire);
        }
        else if(estLettre(c))
        {
            string identOuCle="";
            identOuCle+=c;
            c=lireCar();
            while(estChiffre(c) || estLettre(c) || c=='_')
            {
                identOuCle+=c;
                c=lireCar();
            }

            for(char& v : identOuCle)
            {
                v = tolower(v);
            }
            if(hash_search(identOuCle)==-1)
            {
                paireUniteSuivante paire{IDENT, identOuCle};
                return(paire);
            }
            else
            {
                paireUniteSuivante paire{MOTCLE, identOuCle};
                return(paire);
            }
        }
        else
        {
            c=lireCar();
            if(c!='\n')
            {
                paireUniteSuivante paire{ERREUR, "caractere inattendu"};
                return(paire);
            }

        }
    }
    }

}
paireUniteSuivante motCourant;
extern char c;

#endif // FONCTIONSLEXICAL_H_INCLUDED
