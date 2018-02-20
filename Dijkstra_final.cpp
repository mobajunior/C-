																Devoir 2
//Nom: Moussa Bâ
/*
Programmation de Dijkstra
*/



#include <iostream>
#include <queue>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


class graphe					//initialisation de notre graphe
{
private:
	 int Vertex;				//Vertex d/termine les noeuds
	 int *tab;					//pointeur vers un tableau
	vector<pair<int,int> > *f;		//déclaration d'un pointeur de type vecteur

public:
	graphe(int const V)				//constructeur qui va déterminer notre nombre de vertex
	{
		Vertex=V;
		tab= new int [Vertex];				//tableau qui va contenir les noeuds pères
		for(int i=0; i<Vertex; i++)
		{
			tab[i]=-1;
		}

		this->Vertex= Vertex;
		f= new vector<pair<int,int> > [Vertex];			//création des vecteurs ou on va insérer les pères et leurs fils ou voisins
	};

	~graphe()		//destructeur
	{
		delete f;
	};
	
	void voisin(int , int , int );			//Création d'un vecteur ou on va insérer en premier les père en premier et ensuite ses fils avec les coûts 
	void Dijkstra(int );					//Définition de l'alogorithme  Dijkstra
	void cheminement(int);					//détermine le chemin choisi

};

void graphe::cheminement(int destination)		//fonction qui renvoie les pères et la racine
{
	if (tab[destination]>=0)					//tant qu'on a pas trouvé la racine, on fait appel à la fonction récursive
	{
		cout<<tab[destination]<<"<-";
		return cheminement(tab[destination]);
	}
	else cout<<"Depart";
	cout<<endl<<"====================================================="<<endl<<endl;

}


void graphe::voisin(int v1, int v2, int cout)
	{
		f[v1].push_back(make_pair(v2,cout));		//création de listes des pères avec leurs fils
	}

void graphe::Dijkstra(int depart)
{
	int poids[15];									//initialisation d'un tableau qui va contenir les  coûts des trajets
	bool visite[15];								//initialisation qui va indiquer si un vertex est visité ou non
	int fils=0;										//variable représentant les fils des vertex pères
	int pere=depart;


	priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;		//liste qui nous permet de trier les coûts les plus petits

		
		for(int i = 0; i < Vertex; i++)			//Au débuts aucuns des vertexs n'ait visité
		{
			poids[i] = 999;
			visite[i] = false;
		}

		
		poids[depart] = 0;					//le poids de la source est initialisée à 0
		
		
		pq.push(make_pair(poids[depart], depart));			//insertion de la source dans le vecteur pq

		while(!pq.empty() )		//tant qu'on a pas visité tous les vertex ou qu'on pas trouvé la destination
		{
			pair<int, int> v = pq.top();					//v détermine le coût le plus petit dans le vecteur pq
			pere = v.second;							//pere représente le vertex destination qui a le côût le plus petit

			if (visite[pere]==false)					
			{
			cout<<"cout minimum du trajet pour acces("<<pere<<")= "<<poids[pere]<<endl<<endl;
			
				if (pere!=depart)
			{
				cout<<pere<<"<-";
				cheminement(pere);
			}
			}
			
			pq.pop();										//on le retire de la liste
		
				visite[pere] = true;							//Après l'avoir retiré de la liste, on le marque visité puis on regarde le coût de ses enfants
				
				vector<pair<int, int> >::iterator it;		//définition d'un itérateur
				for(it = f[pere].begin(); it != f[pere].end(); it++)		//tant qu'on a pas parcouru tous les fils du pèere
				{
			
					fils = it->first;									//Vertex(fils)
					int cout_arc = it->second;								//coût arc pour aller du père vers le fils

					if(poids[fils] > (poids[pere] + cout_arc))				//si le poids du fils  est supérieur à la somme du poids du père et de l'arc
					{
					
						poids[fils] = poids[pere] + cout_arc;					//on définit le nouvel poids du fils
						pq.push(make_pair(poids[fils], fils));					//et on l'insère dans la 
						tab[fils]=pere;
					}
				}
		}
	}
	
int main()
{
	int source=0;				//variable qui détermine choix de la source
	

	graphe D(15);				//référence de notre graphe
	ifstream lire("fichier.txt");
	
	while(!lire.eof())			//lecture de notre fichier texte
	{
		string ligne;			//variable qui va recupérer les lignes de notre fichier
		getline (lire,ligne);
		stringstream ss(ligne);		//flux qui va récupérer les variable de notre fichier
		
		
		int vertex=0;
		ss >> vertex;				//la première variable de la ligne va représenter le père
		cout<<"Vertex "<<vertex<<": ";
		int voisin, arc;			//variable voisin qui correspond aux fils du père et arc détermine le coût de l'arc
			char parenthese;		//variable qui crrespond au charactère parenthèse

		while(ss>>voisin>>parenthese>>arc>>parenthese)		//tant que la ligne n'est pas finie, on recupère les variables puis on l'insèere dans des listes de vecteur
		{
			cout<<voisin<<" ("<<arc<<")  ";
			D.voisin(vertex,voisin,arc);
		}
		cout<<endl<<endl;
		ss.clear();

	}
	cout<<endl;

	cout<<"Choisissez une source: ";
	cin>>source;
	cout<<endl;

	

	

	D.Dijkstra(source); cout<< endl;		//affichage du coût

	
	return 0;
}



