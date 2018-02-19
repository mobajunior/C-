/*																Devoir 2


	Nom: Moussa B�
    NI: A00170392	

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
	vector<pair<int,int> > *f;		//d�claration d'un pointeur de type vecteur

public:
	graphe(int const V)				//constructeur qui va d�terminer notre nombre de vertex
	{
		Vertex=V;
		tab= new int [Vertex];				//tableau qui va contenir les noeuds p�res
		for(int i=0; i<Vertex; i++)
		{
			tab[i]=-1;
		}

		this->Vertex= Vertex;
		f= new vector<pair<int,int> > [Vertex];			//cr�ation des vecteurs ou on va ins�rer les p�res et leurs fils ou voisins
	};

	~graphe()		//destructeur
	{
		delete f;
	};
	
	void voisin(int , int , int );			//Cr�ation d'un vecteur ou on va ins�rer en premier les p�re en premier et ensuite ses fils avec les co�ts 
	void Dijkstra(int );					//D�finition de l'alogorithme  Dijkstra
	void cheminement(int);					//d�termine le chemin choisi

};

void graphe::cheminement(int destination)		//fonction qui renvoie les p�res et la racine
{
	if (tab[destination]>=0)					//tant qu'on a pas trouv� la racine, on fait appel � la fonction r�cursive
	{
		cout<<tab[destination]<<"<-";
		return cheminement(tab[destination]);
	}
	else cout<<"Depart";
	cout<<endl<<"====================================================="<<endl<<endl;

}


void graphe::voisin(int v1, int v2, int cout)
	{
		f[v1].push_back(make_pair(v2,cout));		//cr�ation de listes des p�res avec leurs fils
	}

void graphe::Dijkstra(int depart)
{
	int poids[15];									//initialisation d'un tableau qui va contenir les  co�ts des trajets
	bool visite[15];								//initialisation qui va indiquer si un vertex est visit� ou non
	int fils=0;										//variable repr�sentant les fils des vertex p�res
	int pere=depart;


	priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;		//liste qui nous permet de trier les co�ts les plus petits

		
		for(int i = 0; i < Vertex; i++)			//Au d�buts aucuns des vertexs n'ait visit�
		{
			poids[i] = 999;
			visite[i] = false;
		}

		
		poids[depart] = 0;					//le poids de la source est initialis�e � 0
		
		
		pq.push(make_pair(poids[depart], depart));			//insertion de la source dans le vecteur pq

		while(!pq.empty() )		//tant qu'on a pas visit� tous les vertex ou qu'on pas trouv� la destination
		{
			pair<int, int> v = pq.top();					//v d�termine le co�t le plus petit dans le vecteur pq
			pere = v.second;							//pere repr�sente le vertex destination qui a le c��t le plus petit

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
		
				visite[pere] = true;							//Apr�s l'avoir retir� de la liste, on le marque visit� puis on regarde le co�t de ses enfants
				
				vector<pair<int, int> >::iterator it;		//d�finition d'un it�rateur
				for(it = f[pere].begin(); it != f[pere].end(); it++)		//tant qu'on a pas parcouru tous les fils du p�ere
				{
			
					fils = it->first;									//Vertex(fils)
					int cout_arc = it->second;								//co�t arc pour aller du p�re vers le fils

					if(poids[fils] > (poids[pere] + cout_arc))				//si le poids du fils  est sup�rieur � la somme du poids du p�re et de l'arc
					{
					
						poids[fils] = poids[pere] + cout_arc;					//on d�finit le nouvel poids du fils
						pq.push(make_pair(poids[fils], fils));					//et on l'ins�re dans la 
						tab[fils]=pere;
					}
				}
		}
	}
	
int main()
{
	int source=0;				//variable qui d�termine choix de la source
	

	graphe D(15);				//r�f�rence de notre graphe
	ifstream lire("fichier.txt");
	
	while(!lire.eof())			//lecture de notre fichier texte
	{
		string ligne;			//variable qui va recup�rer les lignes de notre fichier
		getline (lire,ligne);
		stringstream ss(ligne);		//flux qui va r�cup�rer les variable de notre fichier
		
		
		int vertex=0;
		ss >> vertex;				//la premi�re variable de la ligne va repr�senter le p�re
		cout<<"Vertex "<<vertex<<": ";
		int voisin, arc;			//variable voisin qui correspond aux fils du p�re et arc d�termine le co�t de l'arc
			char parenthese;		//variable qui crrespond au charact�re parenth�se

		while(ss>>voisin>>parenthese>>arc>>parenthese)		//tant que la ligne n'est pas finie, on recup�re les variables puis on l'ins�ere dans des listes de vecteur
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

	

	

	D.Dijkstra(source); cout<< endl;		//affichage du co�t

	
	return 0;
}



