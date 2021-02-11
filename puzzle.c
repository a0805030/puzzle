#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define IN int *n, int *m, int *k
#define SC(x) x=getch()
#define CL system("cls"), printf("\n\n\n")

void ho(IN);
void su1(IN);
void su2(IN);
void ar(int *a, int n, int *i1, int *j1);
char ma(int x);
void mo(int *a, int n, int *i1, int *j1, int x, int *t);
void sw(int *x, int *y);
void pr(int *a, int n, int k, int t);
char in(int k);

int main(){
	int n=4, m=1, k=1, i;
	char x;
	do{
		int t=0;
		ho(&n, &m, &k);
		int a[n*n], i1=n-1, j1=n-1;
		ar(a, n, &i1, &j1);
		while(1){
			pr(a, n, k, t);
			for(i=0; i<n*n; i++){
				if(*(a+i)==i+1){
					continue;
				}
					break;
			}
			if(i==n*n){
				printf("\n\t축하합니다.\n\n");
				break;
			}
			x=in(m);
			if(x=='p'){
				CL;
				printf("\t일시정지\n\n");
				printf("\ta. 게임으로 돌아가기\n");
				printf("\tb. 게임 끝내기\n\t");
				do{
					SC(x);
				}while(x!='a'&&x!='b');
				if(x=='a'){
					continue;
				}
				CL;
				break;
			}
			mo(a, n, &i1, &j1, x, &t);
		}
		printf("\t다시 하시겠습니까?\ty/n");
		do{
			SC(x);
		}while(x!='y'&&x!='n');
	}while(x=='y');
	CL;
	return 0;
}

void ho(IN){
	char x;
	do{
		CL;
		printf("\t숫자 그림퍼즐\n\n\ta. 시작하기\n\tb. 설정\n\t");
		SC(x);
		if(x=='b'){
			su1(n, m, k);
		}
	}while(x!='a');
}

void su1(IN){
	char x;
	do{
		CL;
		printf("\t설정\n\n");
		printf("\t%-20s : %10d\n", "a. 행과 열의 수", *n);
		printf("\t%-20s : %10s\n", "b. 조작법", (*m!=0)?"방향키":"WASD");
		printf("\t%-20s : %10c\n", "c. 시행 횟수 표시", (*k!=0)?'O':'X');
		printf("\td. 홈으로 돌아가기\n\t");
		SC(x);
		if(x=='a'){
			su2(n, m, k); 
		}
		else if(x=='b'){
			*m=1-*m;
		}
		else if(x=='c'){
			*k=1-*k;
		}
	}while(x!='d');
}

void su2(IN){
	do{
		CL;
		printf("\t원하시는 행과 열의 수를 입력해수세요");
		printf("(2부터 9까지의 정수)\n\n");
		printf("\t");
		scanf("%d", n);
	}while(*n<2||*n>9);
}

void ar(int *a, int n, int *i1, int *j1){
	int i, t;
	char x;
	for(i=0; i<n*n; i++){
		*(a+i)=i+1;
	}
	srand(time(NULL));
	for(i=0; i<100*n*n; i++){
		x=ma(rand()%4);
		mo(a, n, i1, j1, x, &t);
	}
}

char ma(int x){
	if(x==0||x==72){
		return 'w';
	}
	else if(x==1||x==80){
		return 's';
	}
	else if(x==2||x==75){
		return 'a';
	}
	else if(x==3||x==77){
		return 'd';
	}
}

void mo(int *a, int n, int *i1, int *j1, int x, int *t){
	int i2, j2;
	i2=(x=='w')?*i1+1:(x=='s')?*i1-1:*i1;
	j2=(x=='a')?*j1+1:(x=='d')?*j1-1:*j1;
	if(0<=i2&&i2<n&&0<=j2&&j2<n){
		sw((a+n*(*i1)+*j1), (a+n*i2+j2));
		sw(i1, &i2);
		sw(j1, &j2);
		*t+=1;
	}
}

void sw(int *x, int *y){
	int te;
	te=*x;
	*x=*y;
	*y=te;
}

void pr(int *a, int n, int k, int t){
	int i, j;
	CL;
	for(i=0; i<=2*n; i++){
		printf("\t");
		printf((i%2==0)?" ":"|");
		for(j=0; j<n; j++){
			if(i%2==0){
				printf("---- ");
			}
			else{
				(*(a+n*(i-1)/2+j)!=n*n)?printf(" %2d |", *(a+n*(i-1)/2+j)): printf("    |");
			}
		}
		if(i==1){
			printf("\t일시정지  : p");
		}
		if(i==2&&k!=0){
			printf("\t시행 횟수 : %d회", t);
		}
		printf("\n");
	}
	printf("\t");
}

char in(int m){
	int i=0;
	char x;
	SC(x);
	while(1){
		if(x=='p'){
			break;
		}
		else{
			if(m!=0){
				if(x==0xe0){
					SC(x);
					continue;
				}
				else{
					SC(x);
					if(x==72||x==80||x==75||x==77){
						x=ma(x);
						break;
					}
					else{
						SC(x);
						continue;
					}
				}
			}
			if(m==0){
				if(x=='w'||x=='s'||x=='a'||x=='d'){
					break;
				}
				else{
					SC(x);
					continue;
				}
			}
		}
	}
	return x;
}
