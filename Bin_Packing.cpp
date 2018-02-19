/*
Nom: Moussa Bâ
NI: A00170392

Devoir 3

*/

/*
Programme consistant à faire le Bin Packing best fit
*/

#include <iostream>
#include <deque>
#include <string>
#include <fstream>
#include <functional>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;





class off_line								//classe ou nos méthodes vont nous permettre defaire le Bin Packing
{
	
public:
	
	int taille;														// taille de notre tableau de valeurs triées
	int nb;							//Nombre de ben crés
	vector< float>  ben;				//vecteur qui va contenir nos ben
	vector<float> tab_tri;			//vecteur qui va  contenir les valeurs triées issues du fichier
	 void put_in();					//méthode qui va nous permettre de créer nos bens
	void tri(float);				//Méthode qui va trier nos valeurs issues du fichier
	void affichage();
	


	off_line()						//constructeur
	{
		taille=0;
		nb=0;
	}


};

bool myfunction (float i,float j) { return (i>j); };

void off_line::affichage()					//Affichage
{
	int nb=0;
	vector<float>::iterator it;
	for(it=ben.begin();it!=ben.end(); it++)
	{
		cout<<"Bin ("<<nb<<")"<<" final: "<<*it<<"                          "<<"Espace restante: "<<1-*it<<endl;
		nb++;
	}

}




void off_line::tri(float val)				//tri des valeeurs reçues du fichier
{
	
	tab_tri.push_back(val);					//on insère dans notre tableau issue la valeur du fichier
	taille++;								//on incrémente la taille du vecteur
	sort(tab_tri.begin(),tab_tri.end(),myfunction);		//puis on fait le tri
	

}


 void off_line:: put_in()				
{
	
	int i=0;					//la variable i va déterminer la position du ben
	int j=0;					//la variable j va déterminer la posiion de la valeur triée choisie
	int reset=0;

	if(ben.empty())				//si le vecteur des bens est vide, on insère la première valeur du tableau trié dans le vecteur ben
		{
		ben.push_back(tab_tri.at(0));
		cout<<"Bin (0) a ete cree, valeurs comprises: "<<tab_tri.at(0)<<endl;
		cout<<"Place restante: "<<1-ben[i]<<endl<<endl;
		nb++;										//on incrémente le nombre de ben

		tab_tri.erase(tab_tri.begin());				//puis on efface la valeur du tableau trié
		taille--;									//et on diminue la taille du tableau trié
		
	}
	
	while(!tab_tri.empty())						//tant le tableau trié n'est pas vide
	{
		while(i<nb && taille>0)						//tant qu'on a pas essayé de combiner tous les ben avec les valeurs du tableau trié
		{
			if(ben[i]+tab_tri[j]<=1)			//si la valeur contenue dans le ben additionée à une des valeurs contenues dans le tableau est inférieure à 1
			{
				
				ben[i]=ben[i]+tab_tri[j];		//on remplit le ben
				cout<<"Bin ("<<i<<"), valeur ajoutee: "<<tab_tri.at(0)<<endl;
				cout<<"Place restante: "<<1-ben[i]<<endl<<endl;
				
				sort(ben.begin(),ben.end(), myfunction);	//on  fait un tri, pour déterminer le cas le plus serré

				tab_tri.erase(tab_tri.begin()+j);			//on efface la valeur prise du tableau trié
				taille--;
				i=nb;						//on affecte j à taille pour sortir de la boucle

				reset=0;						//on met reset à 0, pour parcourir les ben les plus serrés
				
			}
			else							//sinon on met le reset à -1, pour aller au ben suivants
			{
				reset=-1;
				i++;
			}

		}
		
		
		if(taille>0 && reset==-1  )				// si le reset est à -1
		{
			


			if(nb==i)							// si on a parcouru tous les bens
			{
				cout<<endl<<endl;
			
				ben.push_back(tab_tri.at(0));					//on prend la première valeur du tableau trié et on l'insère dans le ben à la dernière position
				cout<<"Bin ("<<nb<<") a ete cree, valeur comprise: "<<tab_tri.at(0)<<endl;
				cout<<"Place restante: "<<1-ben[i]<<endl<<endl;

				nb++;												//on augmente le nombre de ben
				tab_tri.erase(tab_tri.begin());						//et on l'efface du tableau
				taille--;
		
			}
			i=0;
			j=0;												//pour reparcourir le tableau trié
		
		}


		
		else	if(taille!=0 && reset==0)				//sinon
		{
			i=0;									//on met le i à 0 pour parcourir de nouveau tous les ben selon les plus serrés
			j=0;
		}
		
	}



}


int main()
{
	off_line f;						//instanciation de la classe off_line
	ifstream lire;					//lecture du fichier
	lire.open("fichier.txt");		//ouverture du fichier
	string ligne;					//recupération de la ligne
	float val;						//stockage temporaire de nos valeurs
	char virgule;					//stockage temporaire de virgules
	
	while(!lire.eof())					//tant qu'on a pas sini de lire le fichier
	{
	getline(lire,ligne);				//on recupère la ligne
	stringstream ss(ligne);

	while(ss>>val>>virgule)					//tant qu'on peut insérer des valeurs de notre fichiers
	{
		f.tri(val);					//on fait le tri dans notre vector tab_tri
		
	}
	}
	lire.close();					//on ferme le fichier
	f.put_in();						//on appelle à la méthode put_in, pour remplir nos bens
	f.affichage();

	
	return 0;
}

