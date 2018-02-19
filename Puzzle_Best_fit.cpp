//Devoir6
//Nom: Moussa Bâ
//Ni: A00170392

/* Devoir Puzzle: consistantant à mettre tous les jetons blancs à droite des jetons noirs.
Pour cele mon heureustique va estimer une fois qu'il a développé un noeud et a créé des fils, le fils qui va généré plus de jetons noirs à gauches des jetons blancs lorqu'on déplace un jeton
*/


#include <iostream>
#include <deque>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
#include <string>
#include <functional>

using namespace std;

struct Node											//Node va définir l'état du Puzzle créé
{
	deque  <string > color;						// il va contenir les différentes couleurs et l'espace
	int pos_blank;								//il va mémoriser en tous temps la position de l'espace
	int best;									//la variable best représente l'estimation de jetons noirs qui sera à droite des blancs								
	int fils;									//la variable fils détermine la position du père du noeud
	 bool operator==(const Node& m) const 
	 {
        return (m.color == color);
     }

	  bool operator<(const Node& m) const {
        return (m.best >best);
    }

	 

};


class tab_Puzzle
{
private:
	
	deque < deque <Node> > Puzzle;				//Puzzle va déterminer tous les Noeuds qu'on a développés
	deque < deque <Node> > close;				//close détermine tous les noeuds qu'on a développés et pour lesquels on créé des fils
		
	int nb_P;								//nb_P détermine la position du Noeud
	

public:
	
	
	deque <int> temp;						//temp pour stocker les pères qui vont mener à la solution pour l'affichage				
	
	tab_Puzzle()						//constructeur
	{
		nb_P=1;					//Initialisation du premier Noeus et des jetons qu'il va recevoir
		
		deque <Node>  P0_N;
		Node P0;
	
		for(int i=0; i<7; i++)
		{
			
			string t;
			if (i==0)
			{
				P0.color.push_front("E");
			}

			else if (i<4)
			{
				P0.color.push_front("N");
			}

			else if (i<7)
			{
				P0.color.push_front("B");
			}
			
			t.erase(t.begin());
			
		}
		
			P0_N.push_front(P0);
			Puzzle.push_front(P0_N);
			Puzzle[0].at(0).best=0;
			Puzzle[0].at(0).pos_blank=6;
			Puzzle[0].at(0).fils=-1;					//fils est mis à -1, pour indiquer qu'il est le noeud raçine

	};

	priority_queue<Node> make_Node(int);				//Méthode pour générer des noeuds
	void heureustique();								//Heureustique qu'on va utilser pour trouver la solution finale
	bool win(int);										//Méthode qui vérifie que tous les jetons noirs sont à droite des blancs
	bool find(int, int);								//Regarde si un noeuds n'est pas semblable aux noeuds déjà développés
	void nbNoir(int,int);								//Méthode pour estimer le nombre de jetons à gauche 
	void affichage();
	void stock(int);									//Méthode pour stocker les pères de la solutions finales


};



bool operator ==(deque <deque <Node>> P1,  deque <deque <Node>> P2)				//comparateur des couleurs de deux noeuds
{
	int j=0;
	for(int i=0; i<7; i++)
	{
		if(P1[0][0].color.at(i)==P2[0][0].color.at(i))
		{
			j++;
		}
	}

	if(j==7)
		return true;

};


void tab_Puzzle::nbNoir(int pere, int fils)					//reçcout le père et le fils comme paramètres
{
	bool white= false;
	
	int i =Puzzle[pere].at(fils).pos_blank;
	int j=0;
	int cpt1,cpt2,k,l=0;
	cpt2=cpt1=k=l=i;
	
	deque<string> pos =Puzzle[pere].at(fils).color;

	
		cpt1=i-1;;
	while (cpt1>=0) 			//tant qu'on a pas parcouru tous les jetons qui se trouvent à droite de l'espace
	{
		if(pos[cpt1]=="N")						//À chaque fois qu'on trouve un jeton, on incrémente le compteur
		{
				if(cpt1==0 )					
			{
				if (white==true && cpt1+3<=i)		//Dans le cas spécial  ou un jeton noir se trouve au bout et qu'il se trouve à côté d'un blanc
													//Si on a la possibilité de le mettre dans l'estame on augmente son estimation, vue qu'un jeton noir est déjà en place
				{
				Puzzle[pere].at(fils).best+=j;
				}
				
			}

			white=false;
			j++;
		}
		else if(pos[cpt1]=="B")					//À chaque qu'on trouve un jeton blanc on qu'i peut aller dans l'espace, on initialise l'estimation
		{
			if(white==false)				
			{
			Puzzle[pere].at(fils).best+=j;
			j=0;
			white=true;
			}
			else
				j++;
			
		}
		cpt1--;
	}
	
	white=false;
	
	j=0;

	
	cpt2=k+1;
	while (cpt2<7  )				//On fait de même pour la partie droite
	{
		if(pos[cpt2]=="N")
		{
			if(cpt2==6)
			{
				if(white==true && cpt2-3<=k)
			{
				Puzzle[pere].at(fils).best+=j;
			}

			}
			white=false;
			j++;
		}
		else if(pos[cpt2]=="B")
		{
			if (white==false)
			{
			Puzzle[pere].at(fils).best+=j;
			j=0;
			white=true;
			}
			else
				j++;
			//white=true;
		}

		cpt2++;
	}
	
}




bool tab_Puzzle:: find (int pere, int pos)				//on voit si un noeud développé n'est pas semblable aux noeuds close
{
	unsigned int i=0;
	while(i<close[0].size())
		{
			if(Puzzle[pere].at(pos)==close[0][i])
			{
				return true;
			}
			i++;
		}
		 return false;

}


bool tab_Puzzle::win(int pere)			//Méthode qui voit si tous les jetons blancs sont à droite ddes jetons noirs
{
	int j=0;
	
	for (int i=4; i<7; i++)
	{
		if(Puzzle[pere].at(0).color[i]=="B")
		{
			j++;
		}

	}
	if(j==3) return true;

}

priority_queue<Node> tab_Puzzle::make_Node(int pere)
{
	
	int i =Puzzle[pere].at(0).pos_blank;				//Puzzle père
	int j=0;											//compteur
	
	string temp;
	if( i-1>=0)									//si le jeton qui se trouve à droite de l'espace peut rentrer
	{
		
		Puzzle[pere].push_back((Puzzle[pere].at(0)));				//On créée un noeud semblable au père
		j++;
		temp=Puzzle[pere].at(j).color[i-1];							//et on échange les positions des jetons
		Puzzle[pere].at(j).color[i-1]=Puzzle[pere].at(j).color[i];
		Puzzle[pere].at(j).color[i]=temp;
		
		if(find(pere,j))
		{
			Puzzle[pere].erase(Puzzle[pere].begin()+j);				//si ce noeud est semblable à un noeud close, on l'efface
			j--;
		}

		else																				//sinon on initialise ses paramàtres
		{
		close[0].push_back(Puzzle[pere][j]);							//on le met dans close pour dire qu c'est déjà vu
		Puzzle[pere].at(j).pos_blank=i-1;								//initialisation de la position de l'espace
		Puzzle[pere].at(j).best=0;										
		Puzzle[pere].at(j).fils=pere;									//initialisation du père

		nbNoir(pere,j);													//initialisation de l'estimation
		}
		

	}

	//On fait de même pour les autres jeton qui peuvent rentrer dans l'esspace

	if(i+1<7 )
	{
		
		Puzzle[pere].push_back((Puzzle[pere].at(0)));
		j++;
		temp=Puzzle[pere].at(j).color[i+1];
		Puzzle[pere].at(j).color[i+1]=Puzzle[pere].at(j).color[i];
		Puzzle[pere].at(j).color[i]=temp;

		if(find(pere,j))
		{
			Puzzle[pere].erase(Puzzle[pere].begin()+j);
			j--;
		}
		else
		{
		close[0].push_back(Puzzle[pere][j]);
		Puzzle[pere].at(j).pos_blank=i+1;
		Puzzle[pere].at(j).best=0;
		Puzzle[pere].at(j).fils=pere;

		nbNoir(pere,j);
		}
		

	}

	if( i-2>=0)
	{
		
		Puzzle[pere].push_back((Puzzle[pere].at(0)));
		j++;

		temp=Puzzle[pere].at(j).color[i-2];
		Puzzle[pere].at(j).color[i-2]=Puzzle[pere].at(j).color[i];
		Puzzle[pere].at(j).color[i]=temp;
		

		if(find(pere,j))
		{
			Puzzle[pere].erase(Puzzle[pere].begin()+j);
			j--;
		}
		else
		{
		close[0].push_back(Puzzle[pere][j]);
		Puzzle[pere].at(j).pos_blank=i-2;
		Puzzle[pere].at(j).best=0;
		
		Puzzle[pere].at(j).fils=pere;
		
		nbNoir(pere,j);
		}
	}

	if(i+2<7 )
	{
		
		Puzzle[pere].push_back((Puzzle[pere].at(0)));
		j++;

		temp=Puzzle[pere].at(j).color[i+2];
		Puzzle[pere].at(j).color[i+2]=Puzzle[pere].at(j).color[i];
		Puzzle[pere].at(j).color[i]=temp;
		
		if(find(pere,j))
		{
			Puzzle[pere].erase(Puzzle[pere].begin()+j);
			j--;
		}
		else
		{
		close[0].push_back(Puzzle[pere][j]);
		Puzzle[pere].at(j).pos_blank=i+2;
		Puzzle[pere].at(j).best=0;
		
		Puzzle[pere].at(j).fils=pere;

		nbNoir(pere,j);
		}
	}

	if( i-3>=0)
	{
		
		Puzzle[pere].push_back((Puzzle[pere].at(0)));
		j++;

		temp=Puzzle[pere].at(j).color[i-3];
		Puzzle[pere].at(j).color[i-3]=Puzzle[pere].at(j).color[i];
		Puzzle[pere].at(j).color[i]=temp;

		if(find(pere,j))
		{
			Puzzle[pere].erase(Puzzle[pere].begin()+j);
			j--;
		}
		else
		{
		close[0].push_back(Puzzle[pere][j]);
		Puzzle[pere].at(j).pos_blank=i-3;
		Puzzle[pere].at(j).best=0;
		
		Puzzle[pere].at(j).fils=pere;
		
		nbNoir(pere,j);
		}
	}

	if(i+3<7 )
	{
		
		Puzzle[pere].push_back((Puzzle[pere].at(0)));
		j++;

		temp=Puzzle[pere].at(j).color[i+3];
		Puzzle[pere].at(j).color[i+3]=Puzzle[pere].at(j).color[i];
		Puzzle[pere].at(j).color[i]=temp;

		if(find(pere,j))
		{
			Puzzle[pere].erase(Puzzle[pere].begin()+j);
			j--;
		}
		else
		{
		close[0].push_back(Puzzle[pere][j]);
		Puzzle[pere].at(j).pos_blank=i+3;
		Puzzle[pere].at(j).best=0;
		
		Puzzle[pere].at(j).fils=pere;
		
		nbNoir(pere,j);
		}
	}
	
	int cpt=1;
	priority_queue<Node> q;

	for(cpt=1; cpt<=j; cpt++ )			//puis on trie le estimation en fonction du plus grand
	{
		q.push(Puzzle[pere].at(cpt));
	}
	return q;



}

void tab_Puzzle::stock(int p)
{
	while (Puzzle[p][0].fils!=-1)			//tant qu'on est pas arrivé à la raçine, on stocke les pères dans un vecteurs
	{
		temp.push_front(p);
		return stock(Puzzle[p][0].fils);
	}

}


void tab_Puzzle::affichage()
{
	cout<<"Win!"<<endl<<endl;
	for(int i=0; i<7; i++)
		{
			cout<<Puzzle[0][0].color[i];
		}
	cout<<endl<<endl;
	while(!temp.empty())
	{
		for(int i=0; i<7; i++)
		{
			cout<<Puzzle[temp.at(0)][0].color[i];				//Affichage des pères jusqu'à la solution finale
		}
		cout<<endl<<endl;
		temp.erase(temp.begin());
	}
}


void tab_Puzzle::heureustique()
{
	int pere=0;
	
	priority_queue<Node> pq;
	Node temp1=Puzzle[0].at(0);					//Noeud de départ
	pq.push(temp1);

	while(!pq.empty())							//tant que c'est pas vide
	{
		if(!close.empty())					//Si on a pas encore examiné de noeud
		{
		Node v= pq.top();					//on prend le Noeud qui a la meilleure estimation
		deque<Node> temp2;					
		temp2.push_back(v);					
		Puzzle.push_back(temp2);				//on l'insère dans le puzzle
		temp2.erase(temp2.begin());				
		pere=nb_P;								//on définit l'id du Noeud
		nb_P++;
		}
		else								//sinon on l'insère dans le marque vu			
		{
			close.push_back(Puzzle[pere]);
		}

		pq.pop();						//et on le retire de la priority queue

		if (win(pere)==true)				//Si on a gagné, on sort 
		{
			stock(pere);
			break;
		}
		else								//sinon
		{
			
			priority_queue<Node> pq2;

			pq2=make_Node(pere);
			while(!pq2.empty())
			{
				Node temp;
				temp= pq2.top();
				pq.push(temp);							//on insère les Noeuds développés dans la priority queue pq, selon les meilleures estimations
				pq2.pop();
			}
			

		}

	}
	if(pq.empty())
	{
	cout<<"Solution pas trouvee"<<endl;
	}
}

int main()
{
	tab_Puzzle P;				//Instanciation de la classe
	P.heureustique();			//Appel de la méthode heuristique
	P.affichage();				//Affichage

	
	return 0;
}
