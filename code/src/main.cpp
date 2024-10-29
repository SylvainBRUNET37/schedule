#define CHEMIN_DOSSIER_DONNEES "./data/"
#define NOM_FICHIER_LISTE_FICHIER_DONNEES "data.txt"
#define NOM_FICHIER_LISTE_SORTIE "sortie.txt"

#define RELEASE
//#define TEST

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

#include "../headers/solution/Instance.hpp"
#include "../headers/solution/Solution.hpp"
#include "../headers/algorithm/HeuristicAlgorithm.h"

using namespace std;

#ifdef RELEASE

int Resolution(Instance * instance);

int main(int argc, const char * argv[])
{
    try
    {
        string s_tmp;
        string s_chemin=CHEMIN_DOSSIER_DONNEES;
        s_chemin.append(NOM_FICHIER_LISTE_FICHIER_DONNEES);
        
        ifstream fichier(s_chemin.c_str(), std::ios::in);std::ofstream fichier_Sortie_Resume;
        s_chemin=CHEMIN_DOSSIER_DONNEES;
        s_chemin.append(NOM_FICHIER_LISTE_SORTIE);
        ofstream fichier_Sortie(s_chemin.c_str(), std::ios::out | std::ios::app);

        if(fichier)
        {
            if(fichier_Sortie)
            {
                fichier_Sortie<<"Fichier donnees\t Tps de resolution \t Best solution"<<endl;
                getline(fichier,s_tmp);
                while(s_tmp!="")
                {
                    Instance * instance = new Instance();
                    chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
                    chrono::duration<double> elapsed;
                    int i_best_solution_score=0;
                    s_chemin=CHEMIN_DOSSIER_DONNEES;
                    cout<< "Resolution de "<<s_tmp<<endl;
                    s_chemin.append(s_tmp);
                    s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\r'), s_chemin.end());
                    s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\n'), s_chemin.end());
                    
                    instance->chargement_Instance(s_chemin);
                    chrono_start = chrono::system_clock::now();
                    i_best_solution_score=Resolution(instance);
                    cout<< "Fin de resolution de "<<s_tmp<<endl;
                    chrono_end = chrono::system_clock::now();
                    elapsed=chrono_end-chrono_start;
                    fichier_Sortie<<s_chemin <<"\t"<<elapsed.count()<<"\t"<< i_best_solution_score <<endl;
                    s_tmp="";
                    getline(fichier,s_tmp);
                    delete instance;
                }
                fichier_Sortie.close();
            }
            else
            {
                cout<<"Erreur lecture des donnees : chemin vers la sortie non valide. "<<endl;
            }
            fichier.close();
        }
        else
        {
            cout<<"Erreur lecture des donnees : chemin listant l'ensemble des donnees non valide. "<<endl;
        }
    }
    
    catch(string err)
    {
        cout << "Erreur fatale : " <<endl;
        cout << err <<endl;
    }
    return 0;
}

void displayMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) { // Parcourir chaque ligne
        for (int value : row) {       // Parcourir chaque élément de la ligne
            std::cout << value << " "; // Afficher l'élément
        }
        std::cout << std::endl;         // Nouvelle ligne après chaque ligne de la matrice
    }
}

void displayArray(const std::vector<int>& array) {
    for (const auto& value : array)
        std::cout << value << " ";
    std::cout << std::endl;
}

int Resolution(Instance * instance)
{
    HeuristicAlgorithm algo(*instance);

    int i_val_Retour_Fct_obj=0;

    Solution* uneSolution = algo.run();

    //displayMatrix(uneSolution->v_v_IdShift_Par_Personne_et_Jour);

    //uneSolution->Verification_Solution(instance);
    
    i_val_Retour_Fct_obj=uneSolution->i_valeur_fonction_objectif;

    return i_val_Retour_Fct_obj;
}
#endif

#ifdef TEST

int main()
{
    Instance instance;
    HeuristicAlgorithm algo(instance);

    return 0;
}

#endif