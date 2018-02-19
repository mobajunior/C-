/*
Nom: Moussa 
Ni: A00170392

Devoir8: Tic-Tac-To

Mon heureustique prendra en compte les ouvertures des joueurs tant que les 3 jetons ne sont pas plaçés. Lorque les trois jetons 
sont mon heureustique prendra en compte la mobilité des jetons de chaque joueur et la possibilité d'un joueur d'aligner des 3 jetons


*/


#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <functional>

using namespace std;


struct jeton							//cette structure définira le format du Tic-Tac-To
{
	deque <string> player;				//position de tous les jetons
	deque <int> X;						//position des jetons de l'ordinateur
	deque <int> O;						//position des jetons de l'humain
	int pos;							//position des puzzles fils
	int fils;							//position du père
	int poids;							//coût du Tic-Tac-To
}
;

class Tictacto
{
private:
	deque <deque<jeton>> user;					//deque qui va contenir la raçine, les fils et les petits fils
	int initialisation;							//variable pour définir lorsque les 3 jetons sont plaçés
	int value;
	int bestscore;

public:
	
	//int pere;
	int nb_fils;					//Nombre de fils pour chaque un père Tictato
	int Ouverture(jeton);
	int Blocaque(jeton);
	int Alignement (jeton);
	void Pere (int);					//Va ddonner le bon déplacement du jeton de l'ordinateur
	void Deplacement();
	//void Minmax(int, int);
	void MoveGen();						//générateur de mouvements 
	//int Static (int, int);
	bool LegalMove(int, int);		//les déplacements de jetons légaux
	void board();					//Affichage
	void Result(int );				//retourne le meilleur coût de l'ordinateur
	void MinMax();
	//void Affichage();

	Tictacto()			//initialisation du tic-tac-to
	{
		//pere=0;
		nb_fils=0;
		initialisation=0;
		value=0;
		bestscore=-10000;
		
		deque<jeton> P_N0;
		jeton N0;

		for(int i=0; i<9; i++)
		{
			string s= to_string(i);
			N0.player.push_back(s);
			N0.fils=-1;
			
		}
		P_N0.push_back(N0);
		user.push_back(P_N0);

		user[0][0].pos=0;
		user[0][0].poids=0;

	}
	
};

bool ComparatorPoids(const jeton& a, const jeton& b)
{
	return a.poids>=b.poids;
}





void Tictacto::board()
{
	system("cls");
	//cout << "\n\n\tTic Tac Toe\n\n";

	cout << "     |     |     " << endl;
	cout << "  " << "0" << "  |  " << "1" << "  |  " << "2" << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << "3" << "  |  " << "4" << "  |  " << "5" << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << "6" << "  |  " << "7" << "  |  " << "8" << endl;

	cout << "     |     |     " << endl << endl;

	cout << "\n\n\tTic Tac Toe\n\n";


	cout << "Computer (X)  -  Humain (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << user[0][0].player[0] << "  |  " << user[0][0].player[1] << "  |  " << user[0][0].player[2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << user[0][0].player[3] << "  |  " << user[0][0].player[4] << "  |  " << user[0][0].player[5] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << user[0][0].player[6] << "  |  " << user[0][0].player[7] << "  |  " << user[0][0].player[8] << endl;

	cout << "     |     |     " << endl << endl;
}



bool Tictacto::LegalMove(int old, int newest)
{
	if(old%3==0 )
	{
		if ((old+3==newest) || (old-3==newest) || (old+1==newest) || newest==4)
		{
			return true;
		}
			
	}

		 if(old>=6 && old<=8)
	{

		if((old+1==newest) || (old-1==newest) || (old-3==newest) || newest==4)
		{
			return true;
		}

		
	}

	 if( (old+1)%3==0)
	{
		if ((old+3==newest) || (old-3==newest)  || (old-1==newest) || (newest==4))
				{
					return true;
				}
		
	}

	 if(old>=0 && old<=2)
	{
		if ((old+1==newest) || (old-1==newest) || (old+3==newest) || (newest==4) )
		{
			return true;
		}
		
	}

	 if (old==4)
	{
		return true;
	}



	else return false;

	
}

void Tictacto::Pere(int coord)			//retourne le tic-tac-to fils qui a le meilleur coût
{
	while(user[coord][0].fils>0)			//tant qu'on est pas arrivé au fils de la raçine qui a le meilleur coût
	{
		 Pere(user[user[coord][0].fils][0].fils);
	}
	user[0][0]=user[coord][0];
	board();
	user.erase(user.begin()+1, user.end());
	user[0].erase(user[0].begin()+1, user[0].end());
	user[0][0].poids=0;
	if(user[0][0].X.size()==3 && Alignement(user[0][0])==100)
	{
		cout<<"Vous avez perdu"<<endl;
		
	}
	else if(user[0][0].X.size()==3 && Alignement(user[0][0])==-100)
	{
		cout<<"Vous avez gagne"<<endl;
	}
	//else  MinMax();
}


void Tictacto::Result( int p)			//petit fils qui a le meilleur coût
{
	int cout=0;
	deque<jeton> best;
	int grandP=user[p][0].fils;
	if(user[0][0].X.size()<3)				//Si les 3 jetons ne sonts pas encore plaçés, on compare les coûts des petits fils 
	{
		for ( unsigned int i=1; i<user[grandP].size(); i++)
		{
			for(unsigned int j=1; j<user[grandP+i].size(); j++)
		{
			jeton temp;
			user[grandP+i][j].poids+=Ouverture(user[grandP+i][j])*10;			//pour les coûts des fils on regarde juste les ouvertures
			temp=user[grandP+i][j];
			
			best.push_back(temp);
		}
			sort(best.begin(), best.end(),  [](jeton s1, jeton s2) {return s1.poids > s2.poids;});
			best.erase (best.begin()+1, best.end());
			
		}
		
		user[best[0].fils][0].poids=best[0].poids;					//puis on prend le meilleur 
		Pere(best[0].fils);											//et on regarde le cheminement qui mène à son père
	}

	else				//si les trois jetons sont placés
	
	
	{
		for (unsigned int i=1; i<user.size(); i++)
		{
			
			for(unsigned int j=1; j<user[grandP+i].size(); j++)
		{
			jeton temp;
			user[grandP+i][j].poids+=(Alignement(user[grandP+i][j])+ Blocaque(user[grandP+i][j]))*10;		//on regarde la mobilité et la possibilités d'aligner les 3 jetons ou de bloquer l'alignement de l'humain
			temp=user[grandP+i][j];
			best.push_back(temp);
		}
			sort(best.begin(), best.end(), [](jeton s1, jeton s2) {return s1.poids > s2.poids;});
			best.erase (best.begin()+1, best.end());
			
		}
		
		user[best[0].fils][0].poids=best[0].poids;
		Pere(best[0].fils);

	}


}

void Tictacto::MinMax()
{
	while( Alignement(user[0][0])!=100 ||  Alignement(user[0][0])==-100)			//tant qu'il ya pas victoire on continue
	{
	
	Deplacement();
	MoveGen();
	}
	if( Alignement(user[0][0])==100)
	{
		cout<<"Vous avez perdu"<<endl;
		
	}
	else if( Alignement(user[0][0])==-100)
	{
		cout<<"Vous avez gagne"<<endl;
	}
	//else  MinMax();
}




void Tictacto::Deplacement()
{
	int pos=0;
	int new_pos=0;
	if(initialisation<3)
	{
	board();
	cout<<"Veuillez entrer position voulue: ";
	cin>> pos;
	cout<<endl<<endl;
	user[0][0].player.at(pos)="O";
	user[0][0].O.push_back(pos);
	board();
	initialisation++;
	}

	else
	{
		cout<<"selectioner la possition du jeton: ";
		cin>>pos;
		if  (user[0][0].player.at(pos)!="O")
		{
			cout<<"Veuillez entrer une bonne position"<<endl;
			Deplacement();
		}
		else
		{
			cout<<"Veuillez entrer la nouvelle position";
			cin>> new_pos;
			if((user[0][0].player.at(new_pos)!="O" && user[0][0].player.at(new_pos)!="X") && (LegalMove(pos, new_pos)==true))
			{

				if(user[0][0].player.at(new_pos)!="O" && user[0][0].player.at(new_pos)!="X")
				{
					string s= to_string(pos);
					user[0][0].player.at(pos)=s;
					user[0][0].player.at(new_pos)="O";
					for(int i=0; i<3; i++)
					{
					if(user[0][0].O[i]==pos)
						{
							user[0][0].O[i]=new_pos;
							i*=3;
						}
					
					}

					board();
				}


				else 
				{
					cout<<"Deplacement non legal"<<endl<<endl;
					 Deplacement();
				}

			

		}
			else 
			{
				cout<<"Mauvaise entree"<<endl;
				Deplacement();
			}
		}


		cout<<endl<<endl;

	}

}

int Tictacto::Ouverture(jeton Noeud)				//possibilité d'aligner ses 3 jetons
{
	
	int libreX=0;
	int libreO=0;
	int reussieX=0;
	int reussieO=0;

	for(int i=0; i<7; i++)
	{
		
		if(i!=4 && i!=5)
		{
		libreX=0;
		libreO=0;
		
		if((i%3==0))
		{
			for (int j=0; j<3; j++)
			{
				if(/*Noeud.player[i+j]=="X" &&*/ Noeud.player[i+j]!="O" )
				{
					libreX++;
				}

				if(/*Noeud.player[i+j]=="O" &&*/ Noeud.player[i+j]!="X")
				{
					libreO++;
				}

				


			}

			
			if( libreX==3 ) reussieX++;
			if (libreO==3) reussieO++;
			//if ((aligneO=2 && aligneX==1)|| (aligneO=1 && aligneX==2)) resultX+=50;
			

		
		}
		 libreX=0;
		 libreO=0;

		if(i>=0 && i<=2)
		{
			for (int j=0; j<7; j+=3)
			{
				if(/*Noeud.player[i+j]=="X" &&*/ Noeud.player[i+j]!="O"  )
				{
					libreX++;
				}

				if(/*Noeud.player[i+j]=="O" &&*/ Noeud.player[i+j]!="X")
				{
					libreO++;
				}

				


			}

			
			if( libreX==3 ) reussieX++ ;
			if (libreO==3) reussieO++ ;
			//if ((libreO=2 && libreX==1)|| (libreO=1 && libreX==2)) resultX+=50;
			

		}
		libreX=0;
		 libreO=0;


		if(i==0)
		{
			for (int j=0; j<9; j+=4)
			{
				if(/*Noeud.player[i+j]=="X" &&*/ Noeud.player[i+j]!="O")
				{
					libreX++;
				}

				if(/*Noeud.player[i+j]=="O" &&*/ Noeud.player[i+j]!="X")
				{
					libreO++;
				}




			}

			
			if( libreX==3 ) reussieX++;
			if (libreO==3) reussieO++;
			//if ((aligneO=2 && aligneX==1)|| (aligneO=1 && aligneX==2)) resultX+=50;
			

		}

		 libreX=0;
		 libreO=0;

		if(i==2)
		{
			for (int j=0; j<5; j+=2)
			{
				if(/*Noeud.player[i+j]=="X" &&*/ Noeud.player[i+j]!="O")
				{
					libreX++;
				}

				if(/*Noeud.player[i+j]=="O" &&*/ Noeud.player[i+j]!="X")
				{
					libreO++;
				}


			}

			
			if( libreX==3 ) reussieX++;
			if (libreO==3) reussieO++;
			//if ((aligneO=2 && aligneX==1)|| (aligneO=1 && aligneX==2)) resultX+=50;
			

		}

	}
	}

	return reussieX-reussieO;

}


int Tictacto::Blocaque(jeton Noeud)			//blocage de jetons
{
		int bloqueX=0;
		int bloqueO=0;

	for(int i=0; i<3; i++)
	{
		

		if((Noeud.X[i]==0) && (Noeud.player[1]=="O" || Noeud.player[1]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X") && (Noeud.player[3]=="O" || Noeud.player[3]=="X"))
			bloqueX++;
		if((Noeud.O[i]==1) && (Noeud.player[2]=="O" || Noeud.player[2]=="X") && (Noeud.player[0]=="O" || Noeud.player[0]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;


		if((Noeud.X[i]==1) && (Noeud.player[2]=="O" || Noeud.player[2]=="X") && (Noeud.player[0]=="O" || Noeud.player[0]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==1) && (Noeud.player[2]=="O" || Noeud.player[2]=="X") && (Noeud.player[0]=="O" || Noeud.player[0]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

		if((Noeud.X[i]==2) && (Noeud.player[1]=="O" || Noeud.player[1]=="X") && (Noeud.player[5]=="O" || Noeud.player[5]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==2) && (Noeud.player[1]=="O" || Noeud.player[1]=="X") && (Noeud.player[5]=="O" || Noeud.player[5]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

		if((Noeud.X[i]==3) && (Noeud.player[0]=="O" || Noeud.player[0]=="X") && (Noeud.player[6]=="O" || Noeud.player[6]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==3) && (Noeud.player[0]=="O" || Noeud.player[0]=="X") && (Noeud.player[6]=="O" || Noeud.player[6]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

		if((Noeud.X[i]==5) && (Noeud.player[2]=="O" || Noeud.player[2]=="X") && (Noeud.player[8]=="O" || Noeud.player[8]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==5) && (Noeud.player[2]=="O" || Noeud.player[2]=="X") && (Noeud.player[8]=="O" || Noeud.player[8]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

		if((Noeud.X[i]==6) && (Noeud.player[3]=="O" || Noeud.player[3]=="X") && (Noeud.player[7]=="O" || Noeud.player[7]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==6) && (Noeud.player[3]=="O" || Noeud.player[3]=="X") && (Noeud.player[7]=="O" || Noeud.player[7]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

		if((Noeud.X[i]==7) && (Noeud.player[6]=="O" || Noeud.player[6]=="X") && (Noeud.player[8]=="O" || Noeud.player[8]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==7) && (Noeud.player[6]=="O" || Noeud.player[6]=="X") && (Noeud.player[8]=="O" || Noeud.player[8]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

		if((Noeud.X[i]==8) && (Noeud.player[5]=="O" || Noeud.player[5]=="X") && (Noeud.player[7]=="O" || Noeud.player[7]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueX++;
		if((Noeud.O[i]==8) && (Noeud.player[5]=="O" || Noeud.player[5]=="X") && (Noeud.player[7]=="O" || Noeud.player[7]=="X") && (Noeud.player[4]=="O" || Noeud.player[4]=="X"))
			bloqueO++;

	}

	return bloqueO-bloqueX;

}

int Tictacto::Alignement(jeton Noeud)		//si on bloque l'alignement des 3 jetons de l'humain, on lui donne un bonus, si l'ordinateur aligne ses 3 jetons on lui donne un bonus plus important
{
	int aligneX=0;
	int aligneO=0;
	int resultX=0;
	//int resultO=0;


	sort(Noeud.X.begin(), Noeud.X.end());
	sort(Noeud.O.begin(), Noeud.O.end());
	for(int i=0; i<7; i++)
	{
		
		if(i!=4 && i!=5)
		{
			aligneX=0;
			aligneO=0;
		
		if((i%3==0))
		{
			for (int j=0; j<3; j++)
			{
				if(Noeud.player[i+j]=="X")
				{
					aligneX++;
				}

				if(Noeud.player[i+j]=="O")
				{
					aligneO++;
				}


			}
			if( aligneX==3 ) return 100;
			if (aligneO==3) return -100;
			if ((aligneO==2 && aligneX==1))/*|| (aligneO==1 && aligneX==2))*/ resultX+=1;
			

		}

		aligneX=0;
		aligneO=0;

		if(i>=0 && i<=2)
		{
			for (int j=0; j<7; j+=3)
			{
				if(Noeud.player[i+j]=="X")
				{
					aligneX++;
				}

				if(Noeud.player[i+j]=="O")
				{
					aligneO++;
				}


			}
			if( aligneX==3 ) return 100;
			if (aligneO==3) return -100;
			if ((aligneO==2 && aligneX==1)) /*|| (aligneO==1 && aligneX==2))*/ resultX+=1;
			

		}

		aligneX=0;
		aligneO=0;


		if(i==0)
		{
			for (int j=0; j<9; j+=4)
			{
				if(Noeud.player[i+j]=="X")
				{
					aligneX++;
				}

				if(Noeud.player[i+j]=="O")
				{
					aligneO++;
				}


			}
			if( aligneX==3 ) return 100;
			if (aligneO==3) return -100;
			if ((aligneO==2 && aligneX==1))/*|| (aligneO==1 && aligneX==2))*/ resultX+=1;
			

		}

		aligneX=0;
		aligneO=0;

		if(i==2)
		{
			for (int j=0; j<5; j+=2)
			{
				if(Noeud.player[i+j]=="X")
				{
					aligneX++;
				}

				if(Noeud.player[i+j]=="O")
				{
					aligneO++;
				}


			}
			if( aligneX==3 ) return 100;
			if (aligneO==3) return -100;
			if ((aligneO==2 && aligneX==1)) /*|| (aligneO==1 && aligneX==2))*/ resultX+=1;
			

		}
		aligneX=0;
		aligneO=0;

	}
	}

	return resultX;

}


void Tictacto::MoveGen()//deque <int> a)			//générateur des fils et des petits fils
{
	//int x, y=0;
	int level=0;
	int pere=0;
	//int ouverture=0;
	//int bloque=0;
	//int aligne=0;

	if (user[0][0].X.size()<3)
	{
		//while(user[pere][nb_fils].X.size()<=3)
		//{
		
		for (int i=0; i<9; i++)
		{
			if ((user[0][0].player[i]!="X") && (user[0][0].player[i]!="O"))
			{
				int p=0;
				jeton temp=user[pere][0];
				temp.player[i]="X";
				user[pere].push_back(temp);
				nb_fils++;
					user[pere][nb_fils].X.push_back(i);
					user[pere][nb_fils].pos=nb_fils;
					user[pere][nb_fils].fils=pere;
					p=Alignement(temp);
					if( Alignement(temp)==100) user[pere][nb_fils].poids+=500;
					else if( Alignement(temp)==-100) user[pere][nb_fils].poids+=-100;

					else  user[pere][nb_fils].poids+=p*10;
					//temp=user[pere][nb_fils];
					//ouverture= Ouverture(temp);
					//user[pere][nb_fils].poids=ouverture*10;

					//pere=nb_fils;
					//nb_fils++;
					
			}
		}
		nb_fils=0;
		//pere++;
		if(initialisation<=2)
		{
		for(unsigned int j=1; j<user[level].size(); j++)
		{
			jeton Ntemp=user[level][j];
			Ntemp.fils=level;
			deque<jeton> Gtemp;
			Gtemp.push_back(Ntemp);
			user.push_back(Gtemp);
			//nb_fils++;
			pere++;
			for (int i=0; i<9; i++)
			{
			if (user[pere][0].player[i]!="X" && user[pere][0].player[i]!="O")
			{
				jeton temp=user[pere][0];
				temp.player[i]="O";
				user[pere].push_back(temp);
				nb_fils++;
				user[pere][nb_fils].O.push_back(i);
				user[pere][nb_fils].pos=nb_fils;
				user[pere][nb_fils].fils=pere;
					
			}
			}
			nb_fils=0;
	}

		Result(pere);
	}
		
		
	}

	 if (initialisation==3)
	{
		
		if(user[0][0].X.size()==3)
		{
		for(unsigned int i=0; i<user[level][0].X.size(); i++)
		{
			for(int j=0; j<9; j++)
			{
				if(LegalMove(user[pere][0].X[i], j)==true && (user[pere][0].player[j]!="X" && user[pere][0].player[j]!="O"))
				{
				int p=0;
				string s= to_string(user[pere][0].X[i]);
				jeton temp=user[pere][0];
				temp.player[user[0][0].X[i]]=s;
				temp.player[j]="X";
				user[pere].push_back(temp);
				nb_fils++;
				user[pere][nb_fils].X[i]=j;
				user[pere][nb_fils].pos=nb_fils;
				user[pere][nb_fils].fils=pere;
				p=Alignement(temp);
				if( Alignement(temp)==100) user[pere][nb_fils].poids+=500;
				else if( Alignement(temp)==-100) user[pere][nb_fils].poids+=-100;
				else  user[pere][nb_fils].poids+=p*10;
				}

			}
			//nb_fils=0;
			//pere++;
		}
		}
		nb_fils=0;

		if( Alignement(user[0][0])!=100)
		for(unsigned int j=1; j<user[level].size(); j++)
		{
			jeton Ntemp=user[level][j];
			Ntemp.fils=level;
			deque<jeton> Gtemp;
			Gtemp.push_back(Ntemp);
			user.push_back(Gtemp);
			//nb_fils++;
			pere++;
			for (unsigned int i=0; i<user[pere][0].O.size(); i++)
			{
				for(int k=0; k<9; k++)
				{
			//if (user[pere][0].player[i]!="X" && user[pere][0].player[i]!="O")
			if(LegalMove(user[pere][0].O[i], k)==true && (user[pere][0].player[k]!="X" && user[pere][0].player[k]!="O"))
			{
				
				string s= to_string(user[pere][0].O[i]);
				jeton temp=user[pere][0];
				temp.player[user[pere][0].O[i]]=s;
				temp.player[k]="O";
				user[pere].push_back(temp);
				nb_fils++;
				user[pere][nb_fils].O[i]=k;
				user[pere][nb_fils].pos=nb_fils;
				user[pere][nb_fils].fils=pere;
				//if(Alignement(temp)>0 && Alignement(temp)!=100) user[pere][nb_fils].poids+=100;
				//else if (Alignement(temp)==-100) user[pere][nb_fils].poids-=100;

				}
					
			}
			}
			nb_fils=0;
	}

		Result(pere);

	}


}

int main()
{
	Tictacto f;
	f.MinMax();

	system("pause");
	return 0;

}



