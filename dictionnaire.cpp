#include <iostream>
using namespace std;

struct Mot{
    string mot;
    Mot *next;
};

struct Index{
    char indice;
    Mot *val;
    Index *next;
};

Index *initIndex(){ // creation de ma tete de liste
    Index *tete = nullptr;
    return tete;
}

bool if_Existe(Index *ListeIndex, char index, Index **indiceExiste){ // Verifie si la valeur existe dans la liste
    Index *ptr = ListeIndex;

    while(ptr != nullptr){
        if(ptr->indice == index){ // Si la valeur est egale a l'index renvoie true
            *indiceExiste = ptr;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void rechercherIndex(Index **ListeIndex, char index, Index **val){ 
    /*Recherche si une valeur existe
    Si oui renvoie son addresse
    Si non on l'ajoute, puis renvoie son adress*/
    
    Index *ptr = *ListeIndex;
    if(if_Existe(ptr,  index, val)) return; // verifie si il existe et quitte la fonction

    Index *el = new Index; // Creation d'un nouveau element
    el->indice = index;
    el->val = nullptr;
    el->next = nullptr;

    *val = el; // Renvoie son adress

    if (*ListeIndex == nullptr){ // Si la liste est vide, modifie la tete
        *ListeIndex = el;
        return;
    }

    if (ptr->indice > index){ // Si la tete de la liste est superieur avec index, on permute pour respecter l'ordre alphabetique
        el->next = *ListeIndex;
        *ListeIndex = el;
        return;
    }
                   
    Index *prec = ptr; // Variable pour garder l'adress des elements avant
    ptr = ptr->next;

    while( (ptr != nullptr) && (ptr->indice < index) ){ // Parcourir la liste jusqu'a la fin ou si l'index est superieur a la valeur de ptr
        prec = ptr;
        ptr = ptr->next;
    }
    
    if ( ptr == nullptr){ // Si on arrive a la fin, c'est qu'on va ajouter a la fin
        prec->next = el;
        return;
    }
    
    el->next = prec->next; // Sinon on rajoute au milieu
    prec->next = el;    
}

bool rechercherMot(Index *ListeIndex, string mot){ // Verifie si le mot existe dans la liste
    Index *ptr ;
    rechercherIndex(&ListeIndex, mot[0], &ptr);
    
    Mot *ptr2 = ptr->val; //copie l'adresse des listes de mot de mot[0]
    while( (ptr2 != nullptr) && (ptr2->mot != mot) ) ptr2 = ptr2->next; // verifie chaque mot
    
    if (ptr2 == nullptr) return false; // si on est arrive a la fin, le mot n'existe pas
    return true; // Vrai car on a trouve le mot
}

void insererMot(Index **ListeIndex, string mot){
    if (rechercherMot(*ListeIndex, mot)) return; // Si le mot existe, on l'ajoute pas

    Index *ptr;
    rechercherIndex(ListeIndex, mot[0], &ptr); // Recherche l;index qui lui correspond

    Mot *ajoutMot = new Mot; // Creer un nouveau mot
    ajoutMot->mot = mot;

    // Ajoute le mot au debut de la chaine
    ajoutMot->next = ptr->val; 
    ptr->val = ajoutMot;   

}

void afficherMots(Index **ListeIndex, char car){ // Affiche les mots qui debutent par un caractere
    Index *ptr;

    rechercherIndex(ListeIndex, car, &ptr);// Recherche l'addresse de son indice
    if (ptr->val == nullptr) cout<<"Il y a aucun mot! "<<endl; // Si val de ptr est vide, donc le mot n'existe pas
    
    else{
        // Parcours tte la liste et affiche les valeurs
        int i = 0;
        Mot *mesMots = ptr->val;
        while(mesMots != nullptr){
            cout<<mesMots->mot<<endl;
            mesMots = mesMots->next;
            i++;
        }
        cout<<i<<" resultats"<<endl; // Nmbres de mot trouves
    }

}
void afficheIndex(Index *tete){ 
    Index *ptr = tete;
    while(ptr != nullptr){
        cout<<ptr->indice<<" ";
        ptr = ptr->next;
    }
}
int main(){
       
    bool START = true; // permet de debuter la session
    Index *Dictionnaire = initIndex(); // initialise le dictionnaire

    while(START){
        int choix;
        string mot = "";
        char charactere = ' ';
        Index *ptr;

        cout<<"Dictionnaire: "<<endl;
        cout<<"1. saisir et insérer dans le dictionnaire une série de mots terminée par -1;"<<endl;
        cout<<"2. saisir et rechercher un mot;"<<endl;
        cout<<"3. saisir un caractère et afficher le nombre de mots et les mots commençant par cette lettre;"<<endl;
        cout<<"4. afficher le dictionnaire et le nombre de mots dans le dictionnaire."<<endl;
        cout<<"Appuyer sur n'importe quel bouton pour quitter"<<endl;
        cout<<">> ";
        cin >>choix;

        switch (choix){
        case 1: 
            // Inserer des mots
            while(mot != "-1" ){
                cout<<"Ajout un mot: ";
                cin>>mot;
                if (mot == "-1") break;
                insererMot(&Dictionnaire, mot);
            }     
            break;
        
        case 2:
            // Recherche un mot
            cout<<"Recherche un mot: ";
            cin>>mot;
            if( !rechercherMot(Dictionnaire, mot)) cout<<"Le mot n'existe pas"<<endl;
            else cout<<"Mot Trouve"<<endl;
            break;
        
        case 3:
            // Affiche ts les mots commencant par un caracter
            cout<<"Recherche mot commencant par un caractere: ";
            cin>>charactere;
            afficherMots(&Dictionnaire,charactere);
            break;

        case 4:
            // Affiche ts les mots du dictionnaire
            cout<<"Les mots du Dictionnaire"<<endl;
            ptr = Dictionnaire;
            while(ptr != nullptr){
                cout<<ptr->indice<<": "<<endl;
                afficherMots(&Dictionnaire,ptr->indice);
                ptr = ptr->next;
                cout<<endl;

            }
            break;

        default:
            START = false;
            break;
        }
        cout<<endl;
    }

}



/*
void rechercherIndex(Index **ListeIndex, char index, Index **val){ 
    // Recherche si une valeur existe
    // Si oui renvoie son addresse
    // Si non on l'ajoute, puis renvoie son adress

    if (*ListeIndex == nullptr){
        Index *ptr = new Index;
        ptr->indice = index;
        ptr->val = nullptr;
        ptr->next = nullptr;
        *ListeIndex = ptr;
        *val = ptr;
    }

    else{

        Index *ptr = *ListeIndex;
        if(if_Existe(&ptr,  index, val)){
            
            cout<<endl;
        }

        
        else{
            Index *el = new Index;
            *val = el;
            el->indice = index;
            el->next = nullptr;
            if (ptr->indice > index){
                el->next = *ListeIndex;
                (*ListeIndex) = el;

            }
            else{
                
                Index *prec = ptr;
                ptr = ptr->next;
                while( (ptr != nullptr) && (ptr->indice < index) ){
                    prec = ptr;
                    ptr = ptr->next;
                }
                if ( ptr == nullptr){
                    prec->next = el;
                }
                else{
                    el->next = prec->next;
                    prec->next = el;
                    
                }
            }
        }

        
    }
}
*/


 // // ajoutMot->next = ptr->val;
    // // ptr->val = ajoutMot;

    // Mot *p = ptr->val;
    // if (p == nullptr){
    //     ptr->val = ajoutMot;
    // }
    // else{
    //     while (p->next != nullptr){
    //         p = p->next;
    //     }
    //     p->next = new Mot;
    //         p->next->mot = mot;
    //         ptr->next->next = nullptr;
    // }
