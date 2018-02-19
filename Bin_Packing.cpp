/*
Nom: Moussa B�
NI: A00170392

Devoir 3

*/

/*
Programme consistant � faire le Bin Packing best fit
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





class off_line								//classe ou nos m�thodes vont nous permettre defaire le Bin Packing
{
	
public:
	
	int taille;														// taille de notre tableau de valeurs tri�es
	int nb;							//Nombre de ben cr�s
	vector< float>  ben;				//vecteur qui va contenir nos ben
	vector<float> tab_tri;			//vecteur qui va  contenir les valeurs tri�es issues du fichier
	 void put_in();					//m�thode qui va nous permettre de cr�er nos bens
	void tri(float);				//M�thode qui va trier nos valeurs issues du fichier
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




void off_line::tri(float val)				//tri des valeeurs re�ues du fichier
{
	
	tab_tri.push_back(val);					//on ins�re dans notre tableau issue la valeur du fichier
	taille++;								//on incr�mente la taille du vecteur
	sort(tab_tri.begin(),tab_tri.end(),myfunction);		//puis on fait le tri
	

}


 void off_line:: put_in()				
{
	
	int i=0;					//la variable i va d�terminer la position du ben
	int j=0;					//la variable j va d�terminer la posiion de la valeur tri�e choisie
	int reset=0;

	if(ben.empty())				//si le vecteur des bens est vide, on ins�re la premi�re valeur du tableau tri� dans le vecteur ben
		{
		ben.push_back(tab_tri.at(0));
		cout<<"Bin (0) a ete cree, valeurs comprises: "<<tab_tri.at(0)<<endl;
		cout<<"Place restante: "<<1-ben[i]<<endl<<endl;
		nb++;										//on incr�mente le nombre de ben

		tab_tri.erase(tab_tri.begin());				//puis on efface la valeur du tableau tri�
		taille--;									//et on diminue la taille du tableau tri�
		
	}
	
	while(!tab_tri.empty())						//tant le tableau tri� n'est pas vide
	{
		while(i<nb && taille>0)						//tant qu'on a pas essay� de combiner tous les ben avec les valeurs du tableau tri�
		{
			if(ben[i]+tab_tri[j]<=1)			//si la valeur contenue dans le ben addition�e � une des valeurs contenues dans le tableau est inf�rieure � 1
			{
				
				ben[i]=ben[i]+tab_tri[j];		//on remplit le ben
				cout<<"Bin ("<<i<<"), valeur ajoutee: "<<tab_tri.at(0)<<endl;
				cout<<"Place restante: "<<1-ben[i]<<endl<<endl;
				
				sort(ben.begin(),ben.end(), myfunction);	//on  fait un tri, pour d�terminer le cas le plus serr�

				tab_tri.erase(tab_tri.begin()+j);			//on efface la valeur prise du tableau tri�
				taille--;
				i=nb;						//on affecte j � taille pour sortir de la boucle

				reset=0;						//on met reset � 0, pour parcourir les ben les plus serr�s
				
			}
			else							//sinon on met le reset � -1, pour aller au ben suivants
			{
				reset=-1;
				i++;
			}

		}
		
		
		if(taille>0 && reset==-1  )				// si le reset est � -1
		{
			


			if(nb==i)							// si on a parcouru tous les bens
			{
				cout<<endl<<endl;
			
				ben.push_back(tab_tri.at(0));					//on prend la premi�re valeur du tableau tri� et on l'ins�re dans le ben � la derni�re position
				cout<<"Bin ("<<nb<<") a ete cree, valeur comprise: "<<tab_tri.at(0)<<endl;
				cout<<"Place restante: "<<1-ben[i]<<endl<<endl;

				nb++;												//on augmente le nombre de ben
				tab_tri.erase(tab_tri.begin());						//et on l'efface du tableau
				taille--;
		
			}
			i=0;
			j=0;												//pour reparcourir le tableau tri�
		
		}


		
		else	if(taille!=0 && reset==0)				//sinon
		{
			i=0;									//on met le i � 0 pour parcourir de nouveau tous les ben selon les plus serr�s
			j=0;
		}
		
	}



}


int main()
{
	off_line f;						//instanciation de la classe off_line
	ifstream lire;					//lecture du fichier
	lire.open("fichier.txt");		//ouverture du fichier
	string ligne;					//recup�ration de la ligne
	float val;						//stockage temporaire de nos valeurs
	char virgule;					//stockage temporaire de virgules
	
	while(!lire.eof())					//tant qu'on a pas sini de lire le fichier
	{
	getline(lire,ligne);				//on recup�re la ligne
	stringstream ss(ligne);

	while(ss>>val>>virgule)					//tant qu'on peut ins�rer des valeurs de notre fichiers
	{
		f.tri(val);					//on fait le tri dans notre vector tab_tri
		
	}
	}
	lire.close();					//on ferme le fichier
	f.put_in();						//on appelle � la m�thode put_in, pour remplir nos bens
	f.affichage();

	
	return 0;
}

