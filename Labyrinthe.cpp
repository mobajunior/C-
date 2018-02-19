/*
Devoir1: Labyrinthe

Nom: Moussa BA
NI: A00170392

Projet visant à créer un labyrinthe de dimension 5*5 en utilisant union by size
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct cellule			//structure va contenir de notre tableau de labyrinte va contenir un état le père ou la racine d'un noeud
						//et une valeur qui indique la position
{
	int value;
	int state;
};

class labyrinthe			
{
private:
	int taille_laby;			//taille labyrinte sur une dimension
	int taille_dessin;			//taille dessin de notre graphe
	cellule *laby;				//pointeur laby de type structure pour créer notre tableau de labyrinthe
	string *b;					//pointeur b de type pour créer notre grphe

public:
	labyrinthe()				//constructeur
	{
		taille_laby=25;					//initialisation de notre tableau de labyrinthe 
		laby= new cellule [taille_laby];

	int cpt1=0;					//
	for (int j=0; j<25; j++)
	{
		laby[j].value=cpt1++;
		laby[j].state=-1;					// si state est négatif, cela indique que le noeud est une raçine 
											// au début tous les noeuds sont des racines
	}

	taille_dessin=40;						//innitialisation de notre tableau de graphe
	b= new string [taille_dessin];			

	
	for (int j=0; j<40; j++)
	{
		b[j]="";
	}
	};
	~labyrinthe()
	{
		delete laby;
		delete b;
	};
	bool same_class(int, int);				//pour déterminer si les noeuds sont dans le même ensemble
	bool finish();							//si entrée est reliée avec sortie, le labyrinthe a été créé
	void union_by_size(int, int);			//fait l'union de deux cellules voisines
	void detruire_mur(int , int);			//destruit mur de deux cellules voisines
	void graphe();							//affichage du labyrinthe
	int find_f(int);						//retourne la racine
	int voisin_aleatoire(int);				//retourne aléatoirement orientation des voisins 

};

int labyrinthe:: voisin_aleatoire(int i)
{
	int N, S, W, E,pos;
	int tab[4]={0};
	pos=i;
	int x=0;
	N=-5;
	S=5;
	W=-1;
	E=1;

	if (pos % 5==0)			//définit voisins de la première colonne du labyrinthe
	{
		if(pos==0)
		{
			tab[0]=E;
			tab[1]=S;
			x=rand()%2;
			return tab[x];
		}

		else if (pos==20)
		{
			tab[0]=N;
			tab[1]=E;
			x=rand()%2;
			return tab[x];
		}

		else 
		{
			tab[0]=N;
			tab[1]=S;
			tab[2]=E;
			x=rand()%3;
			return tab[x];
		}
	}

	else if (pos<5 && pos>0)		//définit voisins de la première 
	{
		if (pos==4)
		{
			tab[0]=S;
			tab[1]=W;
			x=rand()%2;
			return tab[x];
		}

		else
		{
			tab[0]=S;
			tab[1]=E;
			tab[2]=W;
			x=rand()%3;
			return tab[x];
		}
	}

	else if(((pos+1)%5)==0)			//définit voisin de la quatrième colonne
	{
		if(pos==24)
		{
			tab[0]=N;
			tab[1]=W;
			x=rand()%2;
			return tab[x];
		}
		else
		{
			tab[0]=S;
			tab[1]=W;
			tab[2]=N;
			x=rand()%3;
			return tab[x];
		}
	}

	else if(pos>=21 && pos<=23)		//définit voisins de la quatrième ligne
	{
		tab[0]=E;
		tab[1]=W;
		tab[2]=N;
		x=rand()%3;
		return tab[x];
	}

	else							//définit les voisins des autres cellules du laby
	{
		tab[0]=S;
		tab[1]=W;
		tab[2]=N;
		tab[3]=E;
		x=rand()%4;
		return tab[x];
	}
}
int labyrinthe:: find_f(int i)			//retourne la racine de la cellule
{
	int x=i;
	if (laby[x].state<0)				//si c'est inférieur à 0, c'est une raçine
	{
		return x;						//on retourne la position
	}
	else return find_f(laby[x].state);	//sinon tant qu'on apas trouvé la raçine de la cellule, on fait une autre recherche
}
void labyrinthe:: graphe()		//on numérote chaque mur du du labyrinthe
{
	cout<<"========================================"<<endl; 
	int p=0;
	int s=0;
	for (int i=0; i<5; i++)			//si les murs sont de forme vertical
	{
		for (int j=0; j<=3; j++)
		{
			p=(9*i)+j;
			if (b[p]=="-1")			//si c'est moins -1 on casse le mur
			{
				b[p]="	 ";
			}
			else
			b[p]="	|";
			
		}
		
	}

	for (int i=0; i<4; i++)			// si les murs sont de forme horizontale
	{
		for (int j=0; j<=4; j++)
		{
			s=(4+ 9*i)+j;
			if (b[s]=="-1")
			{
				b[s]="        ";
			}
			else
			b[s]  ="========";
			
		}
		
	}
	

	for(int k=0; k<40; k++)				//affichage du labyrinthe
	{
		if (k==0 || k==9 || k == 18 || k==27 || k==36)
		{
			cout<<"|"<<b[k];
		}

		else if(k==3 || k==12 || k==21 || k==30 || k==39)
		{
			cout<< b[k]<<"	|";
			cout<<endl;
		}
		else if(k==8 || k==17 || k==26 || k==35)
		{
			cout<< b [k];
			cout<<endl;

		}
		else
		cout<< b[k];
		
	}
	cout<<"========================================";
	cout<<endl;

}
void labyrinthe:: detruire_mur(int i, int orientation)
{
	int N, S, W, E;				//orientation Nord, Sud, Ouest, Est
	int pos=0;
	N=-5;
	S=5;
	W=-1;
	E=1;
	int temp= i/5;				//indique la ligne où se trouve la cellule

	if (orientation==W)		
	{
		pos=(i+temp*4)-1;
		b[pos]="-1";
	}

	else if (orientation==S)
	{
		pos=(i+temp*4)+4;
		b[pos]="-1";
	}

	else if (orientation==N)
	{
		pos=(i+temp*4)-5;
		b[pos]="-1";
	}

	else if (orientation==E)
	{
		pos=(i+temp*4);
		b[pos]="-1";
	}
}

void labyrinthe:: union_by_size(int i, int orientation)
{
	int racine1=0;				//retourne racine de la cellule choisie
	int racine2=0;				//retourne racine de la cellule voisine
	int pos=i;				
	int j= orientation;
	int voisin= i+orientation;

	racine1=find_f(pos);
	racine2=find_f(voisin);

	if(laby[racine1].state< laby[racine2].state)			//si la cellule choisie a plus d'enfants que sa voisine
	{
		laby[racine1].state+=laby[racine2].state;			//on décrémente le state de la cellule choisie pour indiquer qu'on a augmenter son nombre d'enfants
		laby[racine2].state=laby[racine1].value;			//la voisine va avoir comme père la cellule choisie
		detruire_mur(pos , j);								//et on détruit le mur
		cout<<"Union entre "<<pos<<" et "<<voisin<<endl;
	}
	else													//sinon on fait inversément
		{
			laby[racine2].state += laby[racine1].state;
		laby[racine1].state = laby[racine2].value;
		detruire_mur(pos , j);
		cout<<"Union entre "<<pos<<" et "<<voisin<<endl;
	}
	cout<<endl<<endl;
}



bool labyrinthe::same_class( int pos, int orientation)		//si les deux cellules sont dans le même ensemble on retourne true sinon false
{
	int x=pos;
	int temp= pos +orientation;
	if (find_f(x)==find_f(temp))					//si les deux cellules ont la même raçine
		return false;
	else return true;
}



bool labyrinthe::finish()
{
 	if(find_f(0)==find_f(24))				//si arrivée et départ sont connectés
		return true;
	else return false;
}


int main()
{
	srand(time(NULL));
	labyrinthe l;				//Pour instancier le labyrinthe
	int nb_temp=0;
	int direction=0;

	l.graphe();					//affichage labyrinthe
	cout<<endl<<endl;

	cout<<"creation labyrinthe"<<endl<<endl;
	

	while(!l.finish())				//tant qu arrivée et départ ne sont pas connectés
	{
		direction=l.voisin_aleatoire(nb_temp);			//génération d'une orientation aléatoire, donnant position des cellules voisines

		while(! l.same_class(nb_temp, direction))		//si deux cellules dans la même classe
		{
			nb_temp = rand()%25;						//on cherche une nouvelle cellule
			direction=l.voisin_aleatoire(nb_temp);
		}
		l.union_by_size(nb_temp, direction);			//on fait l'union 
		nb_temp=rand()%25;								//on cherche une nouvelle cellule
		
	}
	l.graphe();
	
	return 0;


}
	