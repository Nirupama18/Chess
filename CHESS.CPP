#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
int gd = 9;        //initgraph
int gm = 2;
int  c= 2;
int	check_i,check_j,x_coord=3,y_coord=3;
int	black=0,white=0;
/*	whenever it is their turn they will be 0 whenever it is not they
	they will be 1

	check_i and check_j will hold values of coordinates and will be used
	to traverse the squares leading up to the square that the user selects
	the square the user selects is in i,j

	x_coord,y_coord hold the original coordinates of the rook
	before it is moved
*/
int	check=0; // if king can no longer move
int	piece=0,square=0;
int	colour;
const	int	N=8;
int	a[N][N]={0};
int 	cx,cy,m,n,i=3,j=3,p,q,u,v;//u is for checkmate condition
int	flag=0;
class 	mouse
{
		REGS regs;
		int no_buttons;
	public:
		void show_mouse();
		void get_status();
		void hide_mouse();
		mouse()
		{
			regs.x.ax=0;
			int86(0x33,&regs,&regs);
			if(regs.x.ax==0xfff)no_buttons=regs.x.bx;
			//cout<<"Error initializing mouse";
		}
}ob;
void mouse::show_mouse()
{
	regs.x.ax=0x01;
	int86(0x33,&regs,&regs);
}
void mouse::hide_mouse()
{
	regs.x.ax=0x02;
	int86(0x33,&regs,&regs);
}
void mouse::get_status()
{
			regs.x.ax=0x03;
			int86(0x33,&regs,&regs);
			delay(500);
			while(m!=1)
			{
				regs.x.ax=0x03;
				int86(0x33,&regs,&regs);
				m=regs.x.bx;
				cx=regs.x.cx;
				cy=regs.x.dx;
			}
			delay(500);
			m=0;

}
void	print(char	na[]);
void	initialise() // blacks are positive and whites are -ve
{
//	print("initialising");
	for(int	i=0;i<8;i++)
	{
			for(int	j=0;j<8;j++)
			{
				if(i==1) a[i][j]=1;
				if(i==6) a[i][j]=-1; //pawns
				if(i==0)
				{
					if (j==0||j==7)
					a[i][j]=5;         //rook
				  else	if (j==1||j==6)
					a[i][j]=4;         //bishop
				  else	if (j==2||j==5)
					a[i][j]=3;         //knight
				  else	if (j==3) a[i][j]=9;   //queen
				  else	if (j==4) a[i][j]=10;  //king
		      //CHECK IF POSITION OF QUEEN AND KING ARE CORRECT
				}
				if (i==7)
				{
					if (j==0||j==7)
					a[i][j]=-5;         //rook
					if (j==1||j==6)
					a[i][j]=-4;         //bishop
					if (j==2||j==5)
					a[i][j]=-3;         //knight
					if (j==3) a[i][j]=-9;   //queen
					if (j==4) a[i][j]=-10;  //king
					//CHECK THE RULES

				}
			}
	}
}
void	print(char	na[50])
{
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	setfillstyle(SOLID_FILL,BLACK);
	outtextxy(100,10,na);
	delay(1500);
      bar(5,10,500,50);
      //		bar(50,10,300,50);
}
void	display_square(int	a,int	b)
{
	if ((a%2==0 && b%2 ==0) || (a%2!=0 &&
	b%2!=0)) setfillstyle(SOLID_FILL,CYAN);

	else if ((a%2!=0 && b%2 ==0)||(a%2==0 &&
	b%2!=0)) setfillstyle(SOLID_FILL,RED);
	bar(a*50+50,b*50+50,a*50+100,b*50+100);
}
void 	display_pawn(int	left,int	top, int	colour)
{
		display_square(y_coord,x_coord);
		display_square(j,i);
			setcolor(colour);
			setfillstyle(SOLID_FILL,colour);
			fillellipse(left+25,top+18,13,0);
			pieslice(left+25,top+10,0,360,8);
			line(left+10,top+40,left+40, top+40);
	       int	poly[]={left+25,top+18,left+10,top+40,left+40,top+40,
			left+25,top+18};
			fillpoly(3,poly);
}
void	display_rook(int	left,int	top, int	colour)
{
		display_square(y_coord,x_coord);
		display_square(j,i);

	setfillstyle(SOLID_FILL,colour);
	setcolor(colour);
	bar(left+11,top+8,left+16,top+15);
	bar(left+21,top+8,left+29,top+15);    //middle
	bar(left+34,top+8,left+39,top+15);
	bar(left+11,top+15,left+39,top+23);
	bar(left+18,top+23,left+32,top+38);
	fillellipse(left+25,top+41,16,5);
//	bar(left+10,top+38,left+40,top+45);
}
void	display_knight(int	left,int	top, int	colour)
{
		display_square(y_coord,x_coord);
		display_square(j,i);

	setfillstyle(SOLID_FILL,colour);
	setcolor(colour);
	int	stallion[]={left+25, top+5,left+23, top+8,left+20, top+10,
	left+15, top+18, left+17, top+20, left+22, top+15, left+21, top+27,
	left+17, top+30, left+15, top+35, left+35, top+35, left+29, top+27,
	left+27, top+13, left+25, top+5};
	fillpoly(12,stallion);
	bar(left+15, top+35, left+35, top+40);
}
void	display_bishop(int	left,int	top, int	colour)
{
		display_square(y_coord,x_coord);
		display_square(j,i);

	setfillstyle(SOLID_FILL,colour);
	setcolor(colour);
	pieslice(left+25, top+5,0,360, 3);
	int	di[]={ left+25, top+5,left+20, top+10, left+25, top+15,
	left+30, top+10,left+25, top+5};
	fillpoly(5,di);
	int	tri[]={ left+25, top+15, left+15, top+40, left+35,top+40,
	left+25, top+15};
	fillpoly(4,tri);
	fillellipse(left+25, top+18, 10, 5);
	fillellipse( left+25, top+40, 15, 4);
}
void	display_queen(int	left,int	top, int	colour)
{
		display_square(y_coord,x_coord);
		display_square(j,i);

	setfillstyle(SOLID_FILL,colour);
	setcolor(colour);
/*	int poly[]={left+15,top+40,left+10,top+30,left+20,top+40,left+40,
	top+20,left+30,top+40,left+50,top+30,left+30,top+40,left+15,top+40};
	fillpoly(8,poly);
 */	int poly[]={left+14,top+40,left+7,top+20,left+20,top+35,left+25,
	top+10,left+30,top+35,left+43,top+20,left+36,top+40,left+14,top+40};
	fillpoly(8,poly);
	fillellipse(left+25,top+40,15,4);
/*	int poly[]={left+50,top+50,left+40,top+30,left+60,top+40,left+70,
	top+20,left+80,top+40,left+100,top+30,left+90,top+50,left+50,top+50};
	fillpoly(8,poly);
			    */
}
void	display_king(int	left,int	top, int	colour)
{
		display_square(y_coord,x_coord);
		display_square(j,i);

	setfillstyle(SOLID_FILL,colour);
	setcolor(colour);
	bar(left+22, top+10, left+28, top+32); //middle
	bar(left+10, top+18, left+40, top+23);
	bar(left+10, top+32, left+40, top+40);
 //	fillellipse(left+15,top+36,15,4);
}
void	pawn_graphics()
{
	int	i=1; colour=0;// black piece
	for(int	j=0;j<8 ;j++,i+=50)
	{
		display_pawn(j*50+50,100, colour);
	}
	i=6; colour=15; //white piece
	for(	j=0;j<8;j++)
	{
		display_pawn(j*50+50,350, colour);
	}
}
void	rook_graphics()
{
	colour=0;
	display_rook(50, 50, colour);
	display_rook(400, 50, colour);
	colour=15 ;
	display_rook(400, 400, colour);
	display_rook(50, 400, colour);
}
void	bishop_graphics()
{
	display_bishop(150, 50, 0);
	display_bishop(300, 50, 0);
	display_bishop(150, 400, 15);
	display_bishop(300, 400, 15);
}
void	knight_graphics()
{ //DOUBLE CHECK THE FUNCTIONS
	display_knight(100, 50, 0);
	display_knight(350, 50, 0);
	display_knight(100, 400, 15);
	display_knight(350, 400, 15);
}
void	queen_graphics()
{
	display_queen(200, 50, 0);
	display_queen(200, 400, 15);
}
void	king_graphics()
{
	display_king(250, 50, 0);
	display_king(250, 400, 15);
}
void	checkmate_black_for_knight(int	&checkmate)
{
/*	if (( p + 2 ) > 7) || ( p - 2 ) < 0)
	{
		if (( q + 1 ) > 7 ) || ( q - 1 ) < 0 ) checkmate++;
	}
	if (( p + 1 ) > 7) || ( p - 1 ) < 0)
	{
		if (( q + 2 ) > 7 ) || ( q - 2 ) < 0 ) checkmate++;
	}
	else     {       */
	for(check_i=0; check_i<8 && checkmate==0 ;check_i++)
	{
	   for(check_j=0; check_j<8 && checkmate==0 ;check_j++)
	   {
		if(check_i==p+2||check_i==p-2)
		{
			if (check_j==q+1||check_j==q-1)
			{
				if ( a[check_i][check_j]==-4)
				checkmate=1;
			}
		}
		else if (check_i==p+1||check_i==p-1)
		{
			if(check_j==q+2||check_j==q-2)
			{
				if ( a[check_i][check_j]==-4)
				 checkmate=1;
			}
		}
	   }
	}
       // }
}

int	check_mate_black_king(int	p,int	q)
// checkmate for black king
/* passing values of all nine positions
from anyone of the positions it cant move bc theres a black piece blocking
checkmate++
if it can't move bc its outside also checkmate++
*/
{
	int	xx=0, checkmate=0;               //testing for p+1,q+1
  //	if (p+1>7 && q+1>8) checkmate++;
 //	else if (a[p][q]>0)checkmate++;
  //	else
  //	{
//	cout<<checkmate;
	for(check_i= p + 1,check_j= q + 1; check_i<8 && check_j<8 &&
	checkmate==0 && xx==0; check_i++, check_j++)
	{
		if (a[check_i][check_j]!=0)
		{       xx=1;
			if (a[check_i][check_j]==-3||a[check_i][check_j]==-9)
			checkmate=1;
		}
	}// cout<<checkmate<<" "<<a[check_i][check_j];
  //	}
//	if (p-1<0 && q+1>7) checkmate++;
   //	else if (a[p][q]>0) checkmate++;
  //	else
    //	{
	for(xx=0, check_i = p - 1, check_j = q + 1; check_i>=0 && check_j<8 &&
	checkmate==0 && xx==0; check_i-- , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3||
		      a[check_i][check_j] == -9 )
		      checkmate=1;
		}

	}  // cout<<checkmate<<" ";
      //	}
    //	if (p-1<0 && q-1<0) checkmate++;
    //	else
    //	{
	for(xx=0, check_i = p - 1, check_j = q - 1; check_i>=0 && check_j>=0 &&
	checkmate==0 && xx==0; check_i-- , check_j--)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3 ||
		       a[check_i][check_j] == -9 )
			checkmate=1;
		}
	}  // cout<<checkmate<<" ";
    //	}
//	if (p+1>7 && q-1<0)
//	else
//	{
	for(xx=0, check_i = p + 1, check_j = q - 1; check_i<8 && check_j>=0 &&
	checkmate==0 && xx==0; check_i++ , check_j--)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3||
		       a[check_i][check_j] == -9 )
		       checkmate=1;
		}
//	}
	} // cout<<checkmate<<" "; // MISTAKE IN THE WHITE KING FN
	// checking for rook and queen on four directions
//	if (p+1>7) checkmate++;
//	else
//	{
	for(xx=0, check_i = p + 1, check_j = q ; check_i<8 &&
	 checkmate==0 && xx==0; check_i++ )
	{
		if( a[check_i][check_j]!=0)
		{
			xx=1;
			if	( a[check_i][check_j] == -5 ||
			 a[check_i][check_j] == -9 )
			 checkmate=1;
		}
	} // cout<<checkmate<<" ";
//	if (p-1<0) checkmate++;
//	else
//	{
	for(xx=0, check_i = p - 1, check_j = q ; check_i>=0 &&
	checkmate==0 && xx==0; check_i-- )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 ||
			 a[check_i][check_j] == -9 )
			 checkmate=1;
		}
	} // cout<<checkmate<<" ";
//	}
//	if (q+1>7)
//	else
//	{
	for(xx=0, check_i = p , check_j = q + 1 ; check_j<8 &&
	checkmate==0 && xx==0; check_j++ )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 ||
			a[check_i][check_j] == -9 )
			 checkmate=1;
		}
	} // cout<<checkmate<<" ";
//	}
//	if (q-1<0)
//	else
//	{
	for(xx=0, check_i = p , check_j = q - 1 ; check_j>=0 &&
	checkmate==0 && xx==0; check_j-- )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 ||
			a[check_i][check_j] == -9 )
			 checkmate=1;
		}
	} // cout<<checkmate<<" ";
//	}
	if (checkmate==0) checkmate_black_for_knight(checkmate);
	//pawn
//	if( p + 1 > 7 && (q + 1 > 7 || q - 1 < 0)) checkmate++
 //	else   cout<<checkmate<<" ";
	if (checkmate==0)
	{
		if (a[p+1][q+1]==-1|| a[p+1][q-1]==-1)
		checkmate=1;
	}   //   cout<<checkmate<<" "<<"pawn";
	return checkmate;

}
void	checkmate_white_for_knight(int	&checkmate)
{
	for(check_i=0; check_i<8 && checkmate==0 ;check_i++)
	{
	   for(check_j=0; check_j<8 && checkmate==0 ;check_j++)
	   {
		if(check_i==m+2||check_i==m-2)
		{
			if (check_j==n+1||check_j==n-1)
			{
				if ( a[check_i][check_j]==4)
			       checkmate++;
			}
		}
		else if (check_i==m+1||check_i==m-1)
		{
			if(check_j==n+2||check_j==n-2)
			{
				if ( a[check_i][check_j]==4)
				 checkmate++;
			}
		}
	   }
	}
}
int	check_mate_white_king()  // checkmate for white king
{
	int	xx=0, checkmate=0;
	for(check_i= p + 1,check_j= q + 1; check_i<8 && check_j<8 &&
	checkmate==0 && xx==0; check_i++, check_j++)
	{
		if (a[check_i][check_j]!=0)
		{       xx=1;
			if (a[check_i][check_j]==3||a[check_i][check_j]==9)
			checkmate=1;
		}
	}
	for(xx=0, check_i = p - 1, check_j = q + 1; check_i>=0 && check_j<8 &&
	 xx==0; check_i-- , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == 3||
		      a[check_i][check_j] == 9 )
		      checkmate++;
		}

	}
	for(xx=0, check_i = p - 1, check_j = q - 1; check_i>=0 && check_j>=0 &&
	 xx==0; check_i-- , check_j--)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == 3 ||
		       a[check_i][check_j] == 9 )
			checkmate++;
		}
	}
	for(xx=0, check_i = p + 1, check_j = q - 1; check_i<8 && check_j>=0 &&
	 xx==0; check_i++ , check_j--)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == 3||
		       a[check_i][check_j] == 9 )
		       checkmate++;
		}
	}
	// checking for rook and queen on four directions
	for(xx=0, check_i = p + 1, check_j = q ; check_i<8 &&
	 xx==0; check_i++ )
	{
		if( a[check_i][check_j]!=0)
		{
			xx=1;
			if	( a[check_i][check_j] == 5 ||
			 a[check_i++][check_j] == 9 )
			 checkmate++;
		}
	}
	for(xx=0, check_i = p - 1, check_j = q ; check_i>=0 &&
	 xx==0; check_i-- )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 ||
			 a[check_i][check_j] == 9 )
			 checkmate++;
		}
	}
	for(xx=0, check_i = p , check_j = q + 1 ; check_j<8 &&
	 xx==0; check_j++ )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 ||
			a[check_i][check_j] == 9 )
			 checkmate++;
		}
	}
	for(xx=0, check_i = p , check_j = q - 1 ; check_j>=0 &&
	 xx==0; check_j-- )
	{
		if( a[check_i][check_j]!=0)
		{        xx=1;
			if	( a[check_i][check_j] == 5 ||
			a[check_i][check_j] == 9 )
			 checkmate++;
		}
	}
	if (checkmate==0) checkmate_white_for_knight(checkmate);
	if (checkmate==0)    //pawn
	{
		if (a[m-1][n-1]==1|| a[m-1][n+1]==1)
		 checkmate++;
	}
	return checkmate;
}

// CHECKMATE FN
void	CHECKMATE()
{
	if ( (p+1>7 || q+1>7 ) || a[p+1][q+1]>0) u=1;
		else u = check_mate_black_king(p+1,q+1);
//	if (u==0) print("0");

	if ( p+1>7 || a[p+1][q]>0 ) u++;
		else u = u + check_mate_black_king(p+1,q);

	if (( p+1>7 || q-1<0 )|| a[p+1][q-1]>0) u++;
		else u = u + check_mate_black_king(p+1,q-1);

	if ( q+1>7 || a[p][q+1]>0) u++;
		else u = u + check_mate_black_king(p,q+1);

/*	if ((p+1>7 && q+1>7)|| a[p+1][q+1]>0) u=1;
		else*/  u = u + check_mate_black_king(p,q);

	if (( q-1<0 )|| a[p][q-1]>0) u++;
		else u = u + check_mate_black_king(p,q-1);

//	cout<<p-1<<" "<<q+1<<" /";
	if (( p-1<0 || q+1 > 7) || a[p-1][q+1]>0) u++;
		else u = u + check_mate_black_king(p-1,q+1);

	if ((p-1<0 )|| a[p-1][q]>0) u++;
		else u = u + check_mate_black_king(p-1,q);

	if ((p-1<0 || q-1<0) || a[p-1][q-1]>0) u++;
		else u = u + check_mate_black_king(p-1,q-1);

	if (u==9)
	{
		print("CHECKMATE");
		setfillstyle(SOLID_FILL,BLACK);
		bar(50,50,450,450);

		(200,200,"WHITE WINS");  delay(100);
		exit(0);
	}

	v = check_mate_white_king();

	if (v==9)
	{
		print("CHECKMATE");
		setfillstyle(SOLID_FILL,BLACK);
		bar(50,50,450,450);
		outtextxy(200,200,"BLACK WINS");    delay(100);
		exit(0);
	}

//	CHECK();

}

void	check_for_knight_abc()
{
	setcolor(15);
	for(check_i=0; check_i<8 && check==0 ;check_i++)
	{
	   for(check_j=0; check_j<8 && check==0 ;check_j++)
	   {
		if(check_i==p+2||check_i==p-2)
		{
			if (check_j==q+1||check_j==q-1)
			{
				if ( a[check_i][check_j]==-4)
				{print("CHECK by white knight");check=1;}
			}
		}
		else if (check_i==p+1||check_i==p-1)
		{
			if(check_j==q+2||check_j==q-2)
			{
				if ( a[check_i][check_j]==-4)
				{print("CHECK by white knight"); check=1;}
			}
		}
	   }
	}
}
void	abc() // checking for black king
{
	check=0;  setcolor(15);    int	xx=0;
	// Checking for bishop and queen on diagonals
	for( check_i = p + 1, check_j = q + 1; check_i<8 && check_j<8 &&
	check==0 && xx==0; check_i++ , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3 )
			{	print("Check by white bishop"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	for(xx=0, check_i = p - 1, check_j = q + 1; check_i>=0 && check_j<8 &&
	check==0 && xx==0; check_i-- , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3 )
			{	print("Check by white bishop"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}

	}
	for(xx=0, check_i = p - 1, check_j = q - 1; check_i>=0 && check_j>=0 &&
	check==0 && xx==0; check_i-- , check_j--)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3 )
			{	print("Check by white bishop"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	for(xx=0, check_i = p + 1, check_j = q - 1; check_i<8 && check_j<8 &&
	check==0 && xx==0; check_i++ , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{     xx=1;
		      if	( a[check_i][check_j] == -3 )
			{	print("Check by white bishop"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	// checking for rook and queen on four directions
	for(xx=0, check_i = p + 1, check_j = q ; check_i<8 &&
	check==0 && xx==0; check_i++ )
	{
		if( a[check_i][check_j]!=0)
		{
			xx=1;
			if	( a[check_i][check_j] == -5 )
			{	print("Check by white rook"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	for(xx=0, check_i = p + 1, check_j = q ; check_i<8 &&
	check==0 && xx==0; check_i++ )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 )
			{	print("Check by white rook"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	for(xx=0, check_i = p - 1, check_j = q ; check_i>=0 &&
	check==0 && xx==0; check_i-- )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 )
			{	print("Check by white rook"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	for(xx=0, check_i = p , check_j = q + 1 ; check_j<8 &&
	check==0 && xx==0; check_j++ )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 )
			{	print("Check by white rook"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	for(xx=0, check_i = p , check_j = q - 1 ; check_j>=0 &&
	check==0 && xx==0; check_j-- )
	{
		if( a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == -5 )
			{	print("Check by white rook"); check=1;}
			else if 	( a[check_i][check_j] == -9 )
			{	print("Check by white queen"); check=1;}
		}
	}
	if (check==0) check_for_knight_abc();
	if (check==0)    //pawn
	{
		if (a[p+1][q+1]==-1|| a[p+1][q-1]==-1)
		{ setcolor(15);print("CHECK by white pawn"); check=1;}
	}
}
void	check_for_knight_def()
{
	setcolor(15);
	for(check_i=0; check_i<8 && check==0 ;check_i++)
	{
	   for(check_j=0; check_j<8 && check==0 ;check_j++)
	   {
		if(check_i==m+2||check_i==m-2)
		{
			if (check_j==n+1||check_j==n-1)
			{
				if ( a[check_i][check_j]==4)
				{print("CHECK by black knight");check=1;}
			}
		}
		else if (check_i==m+1||check_i==m-1)
		{
			if(check_j==n+2||check_j==n-2)
			{
				if ( a[check_i][check_j]==4)
				{print("CHECK by black knight"); check=1;}
			}
		}
	   }
	}
}

void	def() // checking for white king
{
	check=0;  setcolor(15); int	xx=0;
	// Checking for bishop and queen on diagonals
	for( check_i = m + 1, check_j = n + 1; check_i<8 && check_j<8 &&
	check==0 && xx==0; check_i++ , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{	xx=1;
			if	( a[check_i][check_j] == 3 )
			{	print("Check by black bishop"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	for(xx=0, check_i = m - 1, check_j = n + 1; check_i>=0 && check_j<8 &&
	check==0 && xx==0; check_i-- , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{	xx=1;
			if	( a[check_i][check_j] == 3 )
			{	print("Check by black bishop"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	for(xx=0, check_i = m - 1, check_j = n - 1; check_i>=0 && check_j>=0 &&
	check==0 && xx==0; check_i-- , check_j--)
	{
		if(a[check_i][check_j]!=0)
		{	xx=1;
			if	( a[check_i][check_j] == 3 )
			{	print("Check by black bishop"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	for(xx=0, check_i = m + 1, check_j = n - 1; check_i<8 && check_j<8 &&
	check==0 && xx==0; check_i++ , check_j++)
	{
		if(a[check_i][check_j]!=0)
		{	xx=1;
			if	( a[check_i][check_j] == 3 )
			{	print("Check by black bishop"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	// checking for rook and queen on four directions
	for(xx=0, check_i = m + 1, check_j = n ; check_i<8 &&
	check==0 && xx==0; check_i++ )
	{
		if(a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 )
			{	print("Check by black rook"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	for(xx=0, check_i = m + 1, check_j = n ; check_i<8 &&
	check==0 && xx==0; check_i++ )
	{
		if(a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 )
			{	print("Check by black rook"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	for(xx=0, check_i = m - 1, check_j = n ; check_i>=0 &&
	check==0 && xx==0; check_i-- )
	{
		if(a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 )
			{	print("Check by black rook"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}

	}
	for(xx=0, check_i = m , check_j = n + 1 ; check_j<8 &&
	check==0 && xx==0; check_j++ )
	{
		if(a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 )
			{	print("Check by black rook"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	for( check_i = m , check_j = n - 1 ; check_j>=0 &&
	check==0 ; check_j-- )
	{
		if(a[check_i][check_j]!=0)
		{       xx=1;
			if	( a[check_i][check_j] == 5 )
			{	print("Check by black rook"); check=1;}
			else if 	( a[check_i][check_j] == 9 )
			{	print("Check by black queen"); check=1;}
		}
	}
	if (check==0) check_for_knight_def();
	if (check==0)    //pawn
	{
		if (a[m-1][n-1]==1|| a[m-1][n+1]==1)
		{ setcolor(15);print("CHECK by black pawn"); check=1;}
	}
}

void	CHECK()
{
	print(" Check function");
	for(int	i=0 ; i<8 ; i++)
	{
		for(int	j=0 ; j<8 ; j++)
		{
				if (a[i][j]==-10) { m=i;n=j;}
				else if (a[i][j]==10)  { p=i;q=j;}
		}

	}
	abc();
	def();
	CHECKMATE();

/*     //	cout<< a[m][n]<<" "<< a[p][q];
	setcolor(15);
	print("checking for a black king");
	CHECK1(p,q);
	setcolor(15);
	print("checking for a white king");
	CHECK1(m,n);
     //	if (check==1) check_mate();       */
}

//PAWN FUNCTIONS
void	pawn_promotion()
{
	if ((black==0 && i==7) || (white==0 && i==0))
	{
		outtextxy(450,10,"PAWN PROMOTION");
		 setcolor(RED);
		bar(480, 70,590,100);
		bar(480, 110,590,140);
		bar(480, 150,590,180);
		bar(480, 190,590,220);
		 setcolor(15);
		outtextxy( 500, 70,"ROOK");
		outtextxy( 500, 110,"BISHOP");
		outtextxy( 500, 150,"KNIGHT");
		outtextxy( 500, 190,"QUEEN");
	flag=0;
	ob.show_mouse();
	do
	{
		delay(50);
		ob.get_status();
		delay(100);
		if (cx>=480 && cx<=590)
		{
			if (cy>=70 && cy<=100)
			{if (black==0) a[i][j]=5; else if (white==0) a[i][j]=-5;
			flag=1;}
			else if ( cy>=110 && cy<=140)
			{if (black==0) a[i][j]=3; else if (white==0) a[i][j]=-3;
			flag=1;}
			else if (cy>=150 && cy<=180)
			{if (black==0) a[i][j]=4; else if (white==0) a[i][j]=-4;
			flag=1;}
			else if (cy>=190 && cy<=220)
			{if (black==0) a[i][j]=9; else if (white==0) a[i][j]=-9;
			flag=1;}
		}
	}while(flag==0);
	bar(480,70,590,220);
       }
       else return;
}
int	move_white_pawn()
{
	if (i==x_coord-1 && j==y_coord)
	{
		if(a[i][j]==0)
		{
			ob.hide_mouse();
			display_pawn(j*50+50,i*50+50,colour);
			ob.show_mouse();
			a[i][j]=a[x_coord][y_coord];
			a[x_coord][y_coord]=0;
			pawn_promotion();
			CHECK();
			flag=1;
		}
	   //	else if (a[i][j]<0||a[i][j]>0)
	     //	print("PIECE CANNOT BE MOVED");
	}
	else if ((i==x_coord-1 && j==y_coord-1)
	|| (i==x_coord-1 && j==y_coord+1))
	{
		if(a[i][j]>0)
		{
			ob.hide_mouse();
			display_pawn(j*50+50,i*50+50,colour);
			ob.show_mouse();
			a[i][j]=a[x_coord][y_coord];
			a[x_coord][y_coord]=0;
			pawn_promotion();
			CHECK();
			flag=1;
		}
	       //	else print("PIECE CANNOT BE MOVED");
	}
	else if (x_coord==1||x_coord==6)
	{
		if (i==x_coord-2 && y_coord==j)
		{
			ob.hide_mouse();
			display_pawn(j*50+50,i*50+50,colour);
			ob.show_mouse();
			a[i][j]=a[x_coord][y_coord];
			a[x_coord][y_coord]=0;
			CHECK();
			pawn_promotion();
			flag=1;
		}
	}
     //	else { print("PIECE CANNOT BE MOVED") ;return 1;}
	if (flag==0) {setcolor(15);print("PIECE CANNOT BE MOVED ");return 1;}
	else if (flag==1) return 0;
}
int	move_black_pawn()
{
	if (i==x_coord+1 && j==y_coord)
	{
		if(a[i][j]==0)
		{
			ob.hide_mouse();
			display_pawn(j*50+50,i*50+50,colour);
			ob.show_mouse();
			a[i][j]=a[x_coord][y_coord];
			a[x_coord][y_coord]=0;
			CHECK();
			pawn_promotion();
			flag=1;
		}
	//	else if (a[i][j]<0||a[i][j]>0)   flag=0;
	       //	print("PIECE CANNOT BE MOVED");
	}
	else if ((i==x_coord+1 && j==y_coord+1)
	|| (i==x_coord+1 && j==y_coord-1))
	{
		if( a[i][j]<0)
		{
			ob.hide_mouse();
			display_pawn(j*50+50,i*50+50,colour);
			ob.show_mouse();
			a[i][j]=a[x_coord][y_coord];
			a[x_coord][y_coord]=0;
			CHECK();
			pawn_promotion();
			flag=1;
		}
	}
	else if (x_coord==1||x_coord==6)
	{
		if (i==x_coord+2 && y_coord==j)
		{
			ob.hide_mouse();
			display_pawn(j*50+50,i*50+50,colour);
			ob.show_mouse();
			a[i][j]=a[x_coord][y_coord];
			a[x_coord][y_coord]=0;
			CHECK();
			pawn_promotion();
			flag=1;
		}
	}
	if (flag==0) {setcolor(15);print("PIECE CANNOT BE MOVED");return 1;}
	else if (flag==1) return 0;
}
/*	Difference between black and white pieces
	1. black is +ve and white is -ve
	2. i, x_coord increases in black and and decreases in white moving
	   forward
*/
// ROOK FUNCTIONS
       // MAKE SURE THERE R NO LOGICAL ERRORS IN FLAG
       // CHECK FOR THE ERRORS IN QUEEN
void	move_i_inc()
{
		check_i=x_coord+1 ;check_j=y_coord ;
		/*
		When the square that the user selects is reached
		it will come out of the loop

		If an opponents piece is also encountered it will replace
		the piece and come out of the loop

		provided that the previous squares dont have either your
		pawn or the users pawn
		*/
		for(;check_i<=i&&flag==0 ;check_i++)
		{
			if (check_i==i&&check_j==j)
			{
				if(black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}// make these change in all the fns
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}// make these change in all the fns
				}
				flag=1;
			}
			else if (a[check_i][check_j]!=0) flag=2;
		}
}
void	move_i_dec()
{
		check_i=x_coord-1 ;check_j=y_coord ;
		for(;check_i>=i&&flag==0;check_i--)
		{
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}else if (a[check_i][check_j]!=0) flag=2;
		}
}
void	move_j_inc()
{
		check_i=x_coord ;check_j=y_coord+1 ;
		for(;check_j<=j&&flag==0;check_j++)
		{
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}else if (a[check_i][check_j]!=0) flag=2;
		}
}
void	move_j_dec()
{
		check_i=x_coord ;check_j=y_coord-1 ;
		for(;check_j>=j&&flag==0;check_j--)
		{
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_rook(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}else if (a[check_i][check_j]!=0) flag=2;
		}
}
int	check_rook()
{
	/* checking if the rook can move to the selected square
	 if flag is assigned with 1 it means that rook can be moved to
	 that square and the loop can stop checking
	*/
		check_i=x_coord;check_j=y_coord;
		for(;check_i<8&&flag==0;check_i++)
		{
			if (check_i==i && check_j==j)
			{
				move_i_inc();
			}
		}
		for(check_i=x_coord,check_j=y_coord;check_j<8&&flag==0;
		check_j++)
		{
			if (check_i==i && check_j==j)
			{
				move_j_inc();
			}
		}
		for(check_i=x_coord,check_j=y_coord;check_i>=0&&flag==0;
		check_i--)
		{
			if (check_i==i && check_j==j)
			{
				move_i_dec();
			}
		}
		for(check_i=x_coord,check_j=y_coord;check_j>=0&&flag==0;
		check_j--)
		{
			if (check_i==i && check_j==j)
			{
				move_j_dec();
			}
		}

      if (flag==0||flag==2)
      { setcolor(15);
	print("PIECE CANNOT BE MOVED");
	return 1;
      }
      else return 0;
}

// BISHOP FUNCTIONS

void	move_i_inc_j_inc()
{
		check_i=x_coord+1 ;check_j=y_coord+1 ;
		/*
		When the square that the user selects is reached
		it will come out of the loop

		When another piece is also encountered it will come out of
		the loop

		provided that the previous squares dont have either your
		pawn or the users pawn
		*/
		for(;check_i<=i&&check_j<=j&&flag==0 ;check_i++,
		check_j++)
		{
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}else if (a[check_i][check_j]!=0) flag=2;
		}
}
void	move_i_inc_j_dec()
{
		check_i=x_coord+1 ;check_j=y_coord-1 ;
		for(;check_i<=i&&check_j>=j&&flag==0;check_i++,
		check_j--)
		{
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}else if (a[check_i][check_j]!=0) flag=2;
		}
}
void   move_i_dec_j_inc()
{
		check_i = x_coord-1; check_j = y_coord+1;
		for(;check_i>=i&&check_j<=j&&flag==0;check_i--,
		check_j++)
		{
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i] [j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}
			else if (a[check_i][check_j]!=0) flag=2;
		}
}
void	move_i_dec_j_dec()
{
		check_i=x_coord-1 ;check_j=y_coord-1 ;flag=0;
		for(;check_i>=i&&check_j>=j&&flag==0;check_i--,
		check_j--)
		{ // cout<< a[check_i][check_j]<<" "; delay(500);
			if (check_i==i&&check_j==j)
			{
				if (black==0)
				{
					if (a[i][j]<=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				else if (white==0)
				{
					if (a[i][j]>=0)
					{
						ob.hide_mouse();
						if(a[x_coord][y_coord]==9||
						a[x_coord][y_coord]==-9)
						{display_queen(j*50+50,i*50+50,colour);}
						else display_bishop(j*50+50,i*50+50,colour);
						ob.show_mouse();
						a[i][j]=a[x_coord][y_coord];
						a[x_coord][y_coord]=0;
						CHECK();
					}
				}
				flag=1;
			}
			else if (a[check_i][check_j]!=0)
			 flag=2;
		}       cout<<flag;
}
int	check_bishop()
{
	/* checking if the bishop can move to the selected square
	 if flag is assigned with 1 it means that bishop can be moved to
	 that square and the loop can stop checking
	*/      check_i=x_coord;check_j=y_coord;
		for(;check_i<8&&check_j<8&&flag==0;check_i++,
		check_j++)
		{
			if (check_i==i && check_j==j)
			{
				move_i_inc_j_inc();
			}
		}
		for(check_i=x_coord,check_j=y_coord;check_i<8&&check_j>=0
		&&flag==0;check_i++,check_j--)
		{
			if (check_i==i && check_j==j)
			{
				move_i_inc_j_dec();
			}
		}
		for( check_i=x_coord,check_j=y_coord;check_i>=0&&check_j<8
		&&flag==0;check_i--,check_j++)
		{
			if (check_i==i && check_j==j)
			{
				move_i_dec_j_inc();
			}
		}
		for( check_i=x_coord,check_j=y_coord;check_i>=0&&check_j>=0
		&&flag==0;check_i--,check_j--)
		{
			if (check_i==i && check_j==j)
			{
				move_i_dec_j_dec();
			}
		}
      if (flag==0||flag==2)
      { setcolor(15);
	print("PIECE CANNOT BE MOVED"); return 1;
      }
      else if (flag==1) return 0;
}
//KNIGHT FUNCTIONS  done
void	move_knight()
{
	ob.hide_mouse();
	display_knight(j*50+50,i*50+50,colour);
	 if (black==0) setcolor(15);
	ob.show_mouse();
	a[i][j]=a[x_coord][y_coord];
	a[x_coord][y_coord]=0;
	CHECK();
}
int	check_knight()  //knight done
{
	if(i==x_coord+2||i==x_coord-2)
	{
		if (j==y_coord+1||j==y_coord-1)
	      {	move_knight(); flag=1;  }
	}
	else if (i==x_coord+1||i==x_coord-1)
	{
		if(j==y_coord+2||j==y_coord-2)//||j==y_coord+1||j==y_coord-1))
	      {	move_knight();flag=1;}
	}
	if(flag==1) return 0; else return 1;
}
//QUEEN FUNCTIONS
int	check_queen()
{
	check_i=x_coord;check_j=y_coord;
	for( ;check_i<8 && check_j <8 && flag==0 ; check_i++,check_j++)
	{
		if (check_i==i && check_j==j)
		{
			move_i_inc_j_inc();
		}
	}
	for(check_i=x_coord,check_j=y_coord;check_i<8&&check_j>=0
	&&flag==0;check_i++,check_j--)
	{
		if (check_i==i && check_j==j)
		{
			move_i_inc_j_dec();
		}
	}
	for( check_i=x_coord,check_j=y_coord;check_i>=0&&check_j<8
	&&flag==0;check_i--,check_j++)
	{
		if (check_i==i && check_j==j)
		{
			move_i_dec_j_inc();
		}
	}
	for( check_i=x_coord,check_j=y_coord;check_i>=0&&check_j>=0
	&&flag==0;check_i--,check_j--)
	{
		if (check_i==i && check_j==j)
		{
			move_i_dec_j_dec();
		}
	}
	for(check_i=x_coord,check_j=y_coord;check_i<8&&flag==0;
	check_i++)
	{
		if (check_i==i && check_j==j)
		{
			move_i_inc();
		}
	}
	for(check_i=x_coord,check_j=y_coord;check_j<8&&flag==0;
	check_j++)
	{
		if (check_i==i && check_j==j)
		{
			move_j_inc();
		}
	}
	for(check_i=x_coord,check_j=y_coord;check_i>=0&&flag==0;
	check_i--)
	{
		if (check_i==i && check_j==j)
		{
			move_i_dec();
		}
	}
	for(check_i=x_coord,check_j=y_coord;check_j>=0&&flag==0;
	check_j--)
	{
		if (check_i==i && check_j==j)
		{
			move_j_dec();
		}
	}

      if (flag==0||flag==2)
      {
	setcolor(15);
	print("PIECE CANNOT BE MOVED");
	return 1;
      }
      else return 0;
}
// KING FUNCTIONS
void	move_king()
{
	ob.hide_mouse();
	display_king(j*50+50,i*50+50,colour);
	ob.show_mouse();
	a[i][j]=a[x_coord][y_coord];
	a[x_coord][y_coord]=0;
	CHECK();
}
int	check_king()
{
	if (i==x_coord+1||i==x_coord-1)
	{
		if (j==y_coord+1||j==y_coord-1||j==y_coord)
		{
			move_king();flag=1;
		}
	}
	else if (i==x_coord)
	{
		if (j==y_coord-1||j==y_coord+1);
		{
			move_king();flag=1;
		}
	}
	if (flag==0){setcolor(15);print("PIECE CANNOT BE MOVED"); return 1;}
	else return 0;
}
void	display_choose_another_piece()
{
	setfillstyle(SOLID_FILL,RED);
	bar(480,295,580,370);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(495,290,"choose");
	outtextxy(490,315,"another");
	outtextxy(495,340,"piece");
}
void	redo()
{
	while(cx<=580 && cx>=480  && cy<=370 && cy>=295 )
	{
		delay(20);print("choosing another piece");
		ob.get_status();
		delay(20);print("chosen");
		x_coord = (cy / 50) - 1 ; y_coord = (cx / 50) -1 ;
	};
}
void	check_quit()
{
	if (cx>=480 && cx<=580 && cy>=400 && cy<=450) exit(0);
}
void	quit_chess()
{
	setfillstyle(SOLID_FILL,RED);
	bar(480,400,580,450);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(510,410,"QUIT");
}
void	select_white_piece()
{
	do
	{       setcolor(15);
		print("SELECT A PIECE");
		ob.show_mouse();
		delay(20);
		ob.get_status();
		delay(20);
		redo();
		check_quit();
		x_coord = (cy / 50) - 1 ; y_coord = (cx / 50) -1 ;
	}while(cx<50 || cy<50 || cx>450 || cy>450 ||
	(a[x_coord][y_coord]>=0));
      /*	x_coord = cx % 50 ; y_coord = cy % 50 ;
	if (a[x_coord][y_coord]>=0) return 0;
	else	return 1;        //make changes        */
}
void	select_black_piece()
{

	do
	{       setcolor(15);
		print("SELECT A BLACK PIECE");
		ob.show_mouse();
		delay(20);
		ob.get_status();
		delay(20);
		redo();
		check_quit();
		x_coord = (cy / 50)-1 ; y_coord = (cx / 50)-1 ;
	}while(cx<50 || cy<50 || cx>450 || cy>450 || (a[x_coord][y_coord]<=0));
    /*	x_coord = cx % 50 ; y_coord = cy % 50 ;
	if (a[x_coord][y_coord]<0) return 1;
	else	return 0;          */
}
void	select_square()
{
	if(black==0)
	{
		do
		{       setcolor(15);
			print("SELECT SQUARE FOR BLACKS TURN");
			ob.show_mouse();
			delay(20);
			ob.get_status();
			delay(20);
			redo();
			check_quit();
			i = (cy / 50) - 1; j = (cx / 50) - 1;

		}while(a[i][j]>0 || cx<50 || cy<50 || cx>450 || cy>450);
	/*cannot choose a square that has a black piece
	in it, if square with black piece is chosen, it will enter loop again
	if cx>=50 && cy>=50 && cx<=450 && cy<=450  is given it will be an
	infinite loop
	*/
	}
	else if (white==0)
	{
		do
		{       setcolor(15);
			print("SELECT SQUARE FOR WHITES TURN");
			delay(20);
			ob.get_status();
			delay(20);
			redo();
			check_quit();
			i = (cy / 50) - 1 ; j = (cx / 50) - 1;

		}while(a[i][j]<0 || cx<50 || cy<50 || cx>450 || cy>450);
	/*cannot choose a square that has a black piece
	in it */
	}
		do
		{
			if (square==1)
			{
				setcolor(15);
				print("SELECT ANOTHER SQUARE");
				ob.show_mouse();
				delay(20);
				ob.get_status();
				delay(20);
				redo();
				check_quit();
				i = (cy / 50) - 1; j = (cx / 50) - 1;
			}
		if (a[x_coord][y_coord]==-1) square=move_white_pawn();
		else if (a[x_coord][y_coord]==1) square=move_black_pawn();
		else if (a[x_coord][y_coord]==-5||a[x_coord][y_coord]==5)
			square=check_rook();
		else if (a[x_coord][y_coord]==3||a[x_coord][y_coord]==-3)
			square=check_bishop();
		else if (a[x_coord][y_coord]==4||a[x_coord][y_coord]==-4)
			square=check_knight();
		else if (a[x_coord][y_coord]==9||a[x_coord][y_coord]==-9)
			square=check_queen();
		else if (a[x_coord][y_coord]==10||a[x_coord][y_coord]==-10)
			square=check_king();
		flag=0;
		}while(square==1);

}
void	blacks_turn_whites_turn()
{     	 if (black==0) setcolor(15);
	print("SWITCHING");
	if (black==0) black=1;
	else if (black==1) black=0;
	if (white==0) white=1;
	else if (white==1) white=0;
}
void board()
{
      /*	int gd = 9;
	int gm = 2;   */
	int  c= 2;
//	clrscr();
//	initgraph( &gd, &gm, "C:\\TURBOC3\\BGI");   // shifted to main
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
	outtextxy(0,50,"Chess");
	for(int i = 50;i<450;i+=50)
	{
		for(int j = 50;j<450;j+=50)
		{
		     if (c%2==0) setfillstyle(1,CYAN);
			else setfillstyle(1, RED);
		     bar(i,j,i+50,j+50);
		     delay(10);

		     c++;
		}
		c++;
       }
}
//DONE EXCEPT FOR SHOW MOUSE
void	main()
{
	initgraph( &gd, &gm, "C:\\TURBOC3\\BGI");
	board();        // displays chess board on screen
	initialise();

     quit_chess();
     queen_graphics();
     king_graphics();
     rook_graphics();
     bishop_graphics();
     knight_graphics();
     pawn_graphics();
     display_choose_another_piece();

     print("START");
     for (black=1;;)
     {
		if (black==0)
		{
			colour=0;ob.show_mouse();ob.hide_mouse();setcolor(15);
			print("BLACK'S TURN");
			ob.show_mouse();
		 //	while( piece==0 )
		   //	{
				select_black_piece();
			       //	if (piece==0) print("SELECT BLACK PIECE");
				// piece is 0 if user selects an empty square
				// or a square with a black piece
		     //	}// the text has to disappear
			ob.hide_mouse();
			ob.show_mouse();
			select_square();
			ob.hide_mouse();
		}
		else if (white==0)
		{
			colour=15;
			ob.show_mouse();ob.hide_mouse();setcolor(15);
			print("WHITE'S TURN");
			ob.show_mouse();
		      //	while( piece==0 )
		       //	{
			       //	piece=
				select_white_piece();
			 //	if (piece==0) print("SELECT A WHITE PIECE");

		   //	}// the text has to disappear
			ob.hide_mouse();
			ob.show_mouse();
			select_square();
			ob.hide_mouse();
		}
		square=0; piece=0;
		blacks_turn_whites_turn();
     }
     getch();
     closegraph();

}