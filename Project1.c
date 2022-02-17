//CS222 Project 1
//I'Zayah Griffin
# include <stdio.h>
# include <time.h>
# include <stdlib.h>

double ending(double q, int r[]):
{
	printf("Your current bankroll is %d\n", q);
	printf("You won %d time(s)\n", r[0]);
	printf("You loss %d time(s)\n", r[1]);
	printf("You bet-for %d time(s)\n", r[2]);
	printf("You bet-against %d time(s)\n", r[3]);
}
	
double rolling()
{
  int b,c;
  long my_random_num = 0; // declare your own var to hold random number

  srandom((unsigned int)(time(NULL))); 
  // "Seed" the random number generator with the current time 
  my_random_num = random();
  b = ( 1+my_random_num % 6);
  return b;
}
double playing(double bankroll, double amount, int status[], char letd)
{
	double a,b,c,point,d,e,f;
	char letg;
	printf("Your betting minimum is 5.00 and your betting maximum is %d", bankroll);
	printf("How much would you like to bet?");
	scanf("%lf", &amount);
	printf("Lets Roll!");
	system("stty raw -echo"); getchar(); system("stty cooked echo");
	a = rolling();
	printf("Your first roll was %d!", a);
	printf("Lets Roll Again!");
	system("stty raw -echo"); getchar(); system("stty cooked echo");
	b = rolling();
	printf("Your first roll was %d!", a);
	c = a+b;
	printf("Your Total is %d!", c);
	if(letd == "F" || letd == "f"){
		if(c == 7 || c == 11){
			printf("You Won!");
			status[0] += 1;
			bankroll += amount;
		}
		else if( c == 2 || c == 3 || c == 12){
			printf("You Lost!");
			status[1] += 1;
			bankroll -= amount;
		}
		else{
			point = c;
			printf("Would you like to double the bet");
			printf("Enter y for yes or n for no");
			scanf(" %c", letg);
			if(letg == 'Y' || letg == 'y'){
				amount *= 2;
			}
			while( f != point || f !=7){
				d = rolling();
				e = rolling();
				f = d+e;
			}
			if (f == point){
				printf("You Won!");
				status[0] += 1;
				bankroll += amount;
			}
			if (f == 7){
				printf("You Lost!");
				status[1] += 1;
				bankroll -= amount;
			}
		}
	}
	if(letd == "A" || letd == "a"){
		if(c == 7 || c == 11){
			printf("You Lost!");
			status[1] += 1;
			bankroll -= amount;
		}
		else if( c == 2 || c == 3 || c == 12){
			printf("You Win!");
			status[0] += 1;
			bankroll += amount;
			}
		else{
			point = c; 
			printf("Would you like to double the bet");
			printf("Enter y for yes or n for no");
			scanf("%c", letg);
			if(letg == 'Y' || letg == 'y')
				amount *= 2;
			while( f != point || f !=7){
				d = rolling();
				e = rolling();
				f = d+e;
			}
			if (f == point){
				printf("You Lost!");
				status[1] += 1;
				bankroll -= amount;
			}
			if (f == 7){
				printf("You Win!");
				status[0] += 1;
				bankroll += amount;
			}
		}
	}
}

int
main(void)
{
double bankroll; //current amount of money
double amount; //amount the player will bet
int status[4]; // (win,loss, bet-for, bet-against)
char letd, letc;


array[0] = 0;
array[1] = 0;
array[2] = 0;
array[3] = 0;

printf("Would you like to bet-for or bet-against.\n");
printf("Press f for bet-for or press a for bet-against");
scanf(" %c", &letd)

while( letd ==  "f" || letd == "F" || letd == "a" || letd == "A") /*while condition that continues as long as the input is F,f,A,or a*/
{
switch(letd)
{
	case 'F' : /* When the input is F,f */
	case 'f' :
	  status[2] += 1;
	  playing(bankroll,amount,status[],letd);
	  break;
    case 'A' : /* When the input is A,a */
    case 'a' :
	  status[3] += 1;
	  playing(bankroll,amount,status[],letd);
        break;
	default : /* When the input is not F,f,A, or a */
	  printf("Sorry we don't know what your betting!\n");
	  return 0;
}
//End
if(bankroll > 0){
	printf("press q to quit of c to continue")
	scanf(" %c", &letc);
}
else{
	return ending(bankroll, status[]);
}
if(letc == 'c' || letc == 'C'){
	beginning();
}
else{
	return ending(bankroll, status[]); 
}
}
}