#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>
#include<iostream>
#include<fstream>

using namespace std;
void gotoxy(int x, int y){
	HANDLE hCon;
	COORD dwPos;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}
void OcultarCursor(){
	HANDLE hCon;
	CONSOLE_CURSOR_INFO cci;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cci.dwSize = 100;
	cci.bVisible = FALSE;	
	
	SetConsoleCursorInfo(hCon,&cci);
}
void pintar_limites(){
	for(int i=2;i<78;i++){
		gotoxy(i,3);
		printf("%c",205);
		gotoxy(i,35);
		printf("%c",205);
	}
	for(int i=4;i<35;i++){
		gotoxy(2,i);
		printf("%c",186);
		gotoxy(77,i);
		printf("%c",186);
	}
	gotoxy(2,3);
	printf("%c",201);
	gotoxy(2,35);
	printf("%c",200);
	gotoxy(77,3);
	printf("%c",187);
	gotoxy(77,35);
	printf("%c",188);
}




class PLAYER{
	int x,y;
	int vida;
public:
	PLAYER(int _x, int _y, int _vida):x(_x),y(_y),vida(_vida){}
	int X(){return x;}
	int Y(){return y;}
	int V(){return vida;}
	void pintar();
	void borrar();
	void mover();
	void vid();
	void stage();
	void morir();
};

void PLAYER::morir(){
	borrar();
	x=1;
	y=1;
}

void PLAYER::vid(){
	vida--;
}

void PLAYER::pintar(){
	gotoxy(x,y);
	printf("%c",219);
}
void PLAYER::borrar(){
	gotoxy(x-1,y);
	printf("  ");
}
void PLAYER::mover(){
	if(kbhit()){
		char tecla=getch();
		borrar();
		if(tecla=='a' && x>4){
			x--;
		}
		if(tecla=='w'&& y>4){
			y--;
		}
		if(tecla=='d'&&x<75){
			x++;
		}
		if(tecla=='s'&&y<34){
			y++;
		}
		pintar();
	}
}
class WALL{
	int x,y;
public:
	WALL(int _x, int _y):x(_x),y(_y){}
	int X(){return x;}
	int Y(){return y;}
	void pintar();
	void choque(class PLAYER & P);
	void borrar();
};

void WALL::borrar(){
	gotoxy(x,y);
	printf(" ");
	x=1;
	y=1;
}

void WALL::pintar(){
	gotoxy(x,y);
	printf("%c",178);
}
void WALL::choque(class PLAYER & P){
	if(x==P.X() && y==P.Y()){
		P.vid();
	}
}

class NSTAGE{
	int x,y;
public:
	NSTAGE(int _x, int _y):x(_x),y(_y){}
	int X(){return x;}
	int Y(){return y;}
	void pintar();
	
};

void NSTAGE::pintar(){
	gotoxy(x,y);
	printf("%c",176);
}

class BOTON{
	int x,y;
public:
	BOTON(int _x, int _y):x(_x),y(_y){}
	int X(){return x;}
	int Y(){return y;}
	void pintar();
	void borrar();
};

void BOTON::pintar(){
	gotoxy(x,y);
	printf("%c",193);
}

void BOTON::borrar(){
	x=1;
	y=1;
	gotoxy(x,y);
	printf(" ");
}

class AMMO{
	int x,y,p,f;
	bool direccion, d;
public:
	AMMO(int _x, int _y, bool _direccion,bool _d, int _p, int _f):x(_x),y(_y),direccion(_direccion),d(_d),p(_p),f(_f){}
	int X(){return x;}
	int Y(){return y;}
	void pintar();
	void mover();
	void borrar();
	void choque(class PLAYER & P);
};

void AMMO::pintar(){
	gotoxy(x,y);
	printf("%c",254);
}
void AMMO::borrar(){
	gotoxy(x,y);
	printf(" ");
}

void AMMO::mover(){
	int i=0, s=0, h=0, m=0;
	if (direccion==true){
		
		for(i=0;i<1000;i++){
			gotoxy(0,0);
			cout<<" ";
		}
		if((x<f)&&(d==false)){
			borrar();
			x++;
			pintar();
		}
		else if(x==f){
			borrar();
			x--;
			pintar();
			d=true;
		}
		else if((d==true)&&(x>p)){
			borrar();
			x--;
			pintar();
		}
		else if((x==p)&&(d==true)){
			borrar();
			x++;
			pintar();
			d=false;
		}
		
		
	}
	if (direccion==false){
		
		for(i=0;i<1000;i++){
			gotoxy(0,0);
			cout<<" ";
		}
		if((y<f)&&(d==false)){
			borrar();
			y++;
			pintar();
		}
		else if(y==f){
			borrar();
			y--;
			pintar();
			d=true;
		}
		else if((d==true)&&(y>p)){
			borrar();
			y--;
			pintar();
		}
		else if((y==p)&&(d==true)){
			borrar();
			y++;
			pintar();
			d=false;
		}
		
		
	}
	
	
}
void AMMO::choque(class PLAYER & P){
	if(direccion==true){
		if((x==P.X() && y==P.Y())||(x==P.X()-1 && y==P.Y())||(x==P.X()+1 && y==P.Y())){
			P.vid();
		}
	}
	if(direccion==false){
		if((x==P.X() && y==P.Y())||(x==P.X() && y==P.Y()-1)||(x==P.X() && y==P.Y()+1)){
			P.vid();
		}
	}
}



class STAGES{
	int s;
public:
	STAGES(int _s):s(_s){}
	int S(){return s;}
	void St();
	int Stage1();
	int Stage2();
	int Stage3();
	int Stage4();
	int Stage5();
	int Stage6();
};

void STAGES::St(){
	s++;
}

int STAGES::Stage1(){
	bool stage_over=false;
	int i=0;
	pintar_limites();
	OcultarCursor();
	list<WALL*> W;
	list<WALL*>::iterator itW;
	
	if(s==0){
		
		system("cls");
		pintar_limites();
		gotoxy(2,2);
		cout<<"STAGE 1";
		gotoxy(15,2);
		printf("Muevete con WASD             Tu objetivo es llegar a %c",176);
		PLAYER P(10,10,1);
		P.pintar();
		NSTAGE N(75,34);
		for(i=0;i<30;i++){
			W.push_back(new WALL(15,4+i));
		}
		while(!stage_over){
			P.mover();
			N.pintar();
			for(itW = W.begin();itW != W.end(); itW++){
				(*itW)->pintar();
				(*itW)->choque(P);
				
			}
			if(P.V()==0){
				system("cls");
				Stage1();
			}
			if(P.X()==N.X() && P.Y()==N.Y()){
				Stage2();
				
			}	
		}
	}

	
}
int STAGES::Stage2(){
	int i=0;
	bool stage_over=false;
	system("cls");
	pintar_limites();
	OcultarCursor();
	list<WALL*> W;
	list<WALL*>::iterator itW;
	gotoxy(2,2);
	cout<<"STAGE 2";
	gotoxy(15,2);
	printf("ESTAS ENCERRADO        %c es un boton",193);
	PLAYER P(10,10,1);
	P.pintar();
	BOTON B(34,20);
	B.pintar();
	NSTAGE N(75,34);
	for(i=0;i<20;i++){
		W.push_back(new WALL(35,4+i));
	}
	for(i=0;i<10;i++){
		W.push_back(new WALL(35,25+i));
	}
	for(itW = W.begin();itW != W.end(); itW++){
		(*itW)->pintar();
		
	}
	WALL X(35,24);
	X.pintar();
	while(!stage_over){
		P.mover();
		N.pintar();
		X.choque(P);
		for(itW = W.begin();itW != W.end(); itW++){
			(*itW)->choque(P);
			
		}
		if((P.X()==B.X() && P.Y()==B.Y())){
			X.borrar();
			B.borrar();
			P.pintar();
		}
		if(P.V()==0){
			system("cls");
			Stage2();
		}
		if(P.X()==N.X() && P.Y()==N.Y()){
			St();
			Stage3();
			
		}	
	}
	
}


int STAGES::Stage3(){
	int i=0;
	bool stage_over=false;
	system("cls");
	pintar_limites();
	OcultarCursor();
	list<WALL*> W;
	list<WALL*>::iterator itW;
	gotoxy(2,2);
	cout<<"STAGE 3";
	gotoxy(15,2);
	printf(" ",193);
	PLAYER P(10,10,1);
	P.pintar();
	BOTON B(75,4);
	B.pintar();
	BOTON B2(4,34);
	B2.pintar();
	NSTAGE N(75,34);
	for(i=0;i<20;i++){
		W.push_back(new WALL(3+i,25));
	}
	for(i=0;i<10;i++){
		W.push_back(new WALL(24,25+i));
	}
	for(i=0;i<10;i++){
		W.push_back(new WALL(66+i,25));
	}
	for(i=0;i<10;i++){
		W.push_back(new WALL(64,25+i));
	}
	WALL X2(65,25);
	X2.pintar();
	WALL X(23,25);
	X.pintar();
	while(!stage_over){
		P.mover();
		N.pintar();
		X.choque(P);
		X2.choque(P);
		for(itW = W.begin();itW != W.end(); itW++){
			(*itW)->choque(P);
			(*itW)->pintar();
			
		}
		if((P.X()==B.X() && P.Y()==B.Y())){
			X.borrar();
			B.borrar();
			P.pintar();
		}
		if((P.X()==B2.X() && P.Y()==B2.Y())){
			X2.borrar();
			B2.borrar();
			P.pintar();
		}
		
		if(P.V()==0){
			system("cls");
			Stage3();
		}
		if(P.X()==N.X() && P.Y()==N.Y()){
			St();
			Stage4();
			
		}	
	}
	
	
	
}
int STAGES::Stage4(){
	int i=0;
	bool stage_over=false;
	system("cls");
	pintar_limites();
	OcultarCursor();
	gotoxy(2,2);
	cout<<"STAGE 4";
	gotoxy(15,2);
	printf("Mira un amiguito %c           Cuidado que muerde ",254);
	PLAYER P(10,10,1);
	P.pintar();
	NSTAGE N(75,34);
	AMMO A(4,20,true,false,4,74);
	while(!stage_over){
		P.mover();
		N.pintar();
		A.pintar();
		A.mover();
		A.choque(P);
		if(P.V()==0){
			system("cls");
			Stage4();
		}
		if(P.X()==N.X() && P.Y()==N.Y()){
			St();
			Stage5();
			
		}	
	}
}
int STAGES::Stage5(){
	int i=0;
	bool stage_over=false;
	system("cls");
	pintar_limites();
	OcultarCursor();
	gotoxy(2,2);
	cout<<"STAGE 5";
	gotoxy(15,2);
	printf(" ",254);
	PLAYER P(10,10,1);
	P.pintar();
	NSTAGE N(75,34);
	AMMO A(30,20,false,false,4,34);
	while(!stage_over){
		P.mover();
		N.pintar();
		A.pintar();
		A.mover();
		A.choque(P);
		if(P.V()==0){
			system("cls");
			Stage5();
		}
		if(P.X()==N.X() && P.Y()==N.Y()){
			St();
			Stage6();
			
		}	
	}
}

int STAGES::Stage6(){
	int i=0;
	bool stage_over=false;
	system("cls");
	pintar_limites();
	OcultarCursor();
	gotoxy(2,2);
	cout<<"STAGE 6";
	gotoxy(15,2);
	printf(" ",254);
	PLAYER P(10,10,1);
	P.pintar();
	NSTAGE N(75,34);
	AMMO A(65,10,true,false,65,75);
	list<WALL*> W;
	list<WALL*>::iterator itW;
	BOTON B(75,14);
	B.pintar();
	BOTON B2(4,34);
	B2.pintar();
	for(i=0;i<10;i++){
		W.push_back(new WALL(66+i,25));
	}
	for(i=0;i<10;i++){
		W.push_back(new WALL(64,25+i));
	}
	for(i=0;i<10;i++){
		W.push_back(new WALL(64,5+i));
	}
	for(i=0;i<12;i++){
		W.push_back(new WALL(64+i,15));
	}
	WALL X(64,4);
	WALL X2(65,25);
	X.pintar();
	X2.pintar();
	while(!stage_over){
		for(itW = W.begin();itW != W.end(); itW++){
			(*itW)->choque(P);
			(*itW)->pintar();
			
		}
		P.mover();
		N.pintar();
		A.pintar();
		A.mover();
		A.choque(P);
		if((P.X()==B.X() && P.Y()==B.Y())){
			X2.borrar();
			B.borrar();
			P.pintar();
		}
		if((P.X()==B2.X() && P.Y()==B2.Y())){
			X.borrar();
			B2.borrar();
			P.pintar();
		}
		if(P.V()==0){
			system("cls");
			Stage6();
		}
		if(P.X()==N.X() && P.Y()==N.Y()){
			St();
			
		}	
	}
}

int main(){
	int i=0;
	bool game_over=false, stage1=false;
	pintar_limites();
	OcultarCursor();
	STAGES S(0);
	
	if(!game_over){
		S.Stage1();
	}
	main();
}
