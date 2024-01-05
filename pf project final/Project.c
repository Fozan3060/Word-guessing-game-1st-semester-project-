#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
#include<string.h> 
#include<windows.h>

#define MAX_GUESS_TIME_E 30
#define MAX_GUESS_TIME_M 20
#define MAX_GUESS_TIME_H 15

#define RED   FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE  FOREGROUND_BLUE
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define LIGHT_BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
// Function to set text color
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


int isTimeUp(time_t startTime, int seconds) {
    time_t currentTime = time(NULL);
    double elapsedSeconds = difftime(currentTime, startTime);
    return (elapsedSeconds >= seconds);
}
//function for all top 5 scores of all time
struct high_scores {
    char playername[20];
    int score;
};

struct high_scores highscores[5];

void sort_struct() {
    int i, j, temp;
    char t[20];

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            if (highscores[j].score < highscores[j + 1].score) {
                // Sorting
                temp = highscores[j].score;
                highscores[j].score = highscores[j + 1].score;
                highscores[j + 1].score = temp;
                // Also moving the name
                strcpy(t, highscores[j].playername);
                strcpy(highscores[j].playername, highscores[j + 1].playername);
                strcpy(highscores[j + 1].playername, t);
            }
        }
    }
}

void replace(char name[20], int score) {
    int i = 0, lowest = 99999, lowest_index;

    for (i = 0; i < 5; i++) {
        if (highscores[i].score < lowest) {
            lowest_index = i;
            lowest = highscores[i].score;
        }
    }
    // comparing the lowest score with the input if curr<lowest then update the lowest_index
    if (score > lowest) {
        highscores[lowest_index].score = score;
        strcpy(highscores[lowest_index].playername, name);
    }
}

void print_struct() {
    int i;
    for (i = 0; i < 5; i++) {
        printf("%s : %d\n", highscores[i].playername, highscores[i].score);
    }
}
void welcome(){
printf("\n\n");
printf("           X         X         X   XXXXXXXX   X          XXXXXXXX   XXXXXXXX   X         X   XXXXXXXX \n");
printf("            X       X X       X    X          X          X          X      X   X X     X X   X\n");
printf("             X     X   X     X     XXXXXXXX   X          X          X      X   X  X   X  X   XXXXXXXX \n");
printf("              X   X     X   X      X          X          X          X      X   X   X X   X   X\n");
printf("               X X       X X       XXXXXXXX   XXXXXXXX   XXXXXXXX   XXXXXXXX   X    X    X   XXXXXXXX \n");
printf("\n\n");
}
void rules(){
	printf("RULES : \n") ;
    printf("-About Difficulty Modes\n") ;
    printf("i.Easy(small words which are easy to guess)\n") ;
    printf("ii.Medium(small words | good vocab required to guess)\n") ;
    printf("iii.Hard(long word | difficult to guess | hard meaning)\n") ; 
    printf("---------------------------------------------------------\n") ;
    printf("-Scoring Criteria\n") ;
    printf("i.Easy mode(max score =100 | for every wrong guess -5 | usage of hint -5)\n") ;
    printf("ii.Medium mode(max score =125 | for every wrong guess -10 | usage of hint -10)\n") ;
    printf("iii.Hard mode(max score =150 | for every wrong guess -15  usage of hint -15)\n") ;
    printf("---------------------------------------------------------\n") ;
    printf("If time limit exceeded but correct guess\n");
    printf("i.Easy mode(max score= 50) | for every wrong guess -5 \n");
    printf("ii.Medium mode(max score= 58) | for every wrong guess -5 \n");
    printf("iii.Hard mode(max score= 75) | for every wrong guess -5 \n");
}
void Exit (){
	printf("|----------------------------------------------------------------------------------------------------------------|\n");
                    printf("  XXXXXXXXX   X       X   XXXXXXXX    XX     X   X   X       X     X   XXXXXXXX  X     X\n");
                    printf("     X        X       X   X      X    X X    X   X  X        X     X   X      X  X     X\n");
                    printf("     X        X       X   X      X    X  X   X   X X         X     X   X      X  X     X\n");
                    printf("     X        XXXXXXXXX   XXXXXXXX    X   X  X   XX          XXXXXXX   X      X  X     X\n");
                    printf("     X        X       X   X      X    X    X X   X X            X      X      X  X     X\n");
                    printf("     X        X       X   X      X    X     XX   X  X           X      X      X  X     X\n");
                    printf("     X        X       X   X      X    X      X   X   X          X      XXXXXXXX  XXXXXXX\n");
	printf("|----------------------------------------------------------------------------------------------------------------|\n");
	printf("Team Members\n") ;
	printf("1.Majid Raza (23k-0601)\n") ;
	printf("2.Yuneeb Azam(23k-0733)\n") ;
	printf("3.Fozan Javaid(23k-0605) \n") ; 
}
void changeword(char word[]) {
    int num, len = strlen(word);
    char temp;

    num = rand() % 3 + 1; // generates random number between 1 and 3
    
    switch (num) {
        case 1:
            // reverses the whole word
            strrev(word);
//            printf("Reversed word: %s\n", word);
            break;
        case 2:
            // swapping characters
            if (len <= 5) {
                temp = word[0];
                word[0] = word[len - 1];
                word[len - 1] = temp;
//                printf("Swapped word: %s\n", word);
            }
else {
            strrev(word);
//            printf("Reversed word: %s\n", word);
            }

            break;
            
        case 3: 
            if (len >= 6){
            	temp = word[0];
            	word[0] = word[len - 1];
            	word[len - 1] = temp;
            	temp = word[2];
            	word[2] = word[len-3];
            	word[len-3] = temp;
//            	printf("Swapped word: %s\n", word);
 			}
 			else{
 			temp = word[0];
 			word[0] = word[len - 1];
 			word[len-1] = temp;
 		}
 			break;

   }
}
//global
char name[20];
int h_score;
FILE *fp = NULL ;

int main (){
	system("color 03") ; 
	int choice , exit = 0  ; 
	welcome() ;
	while(1){
			printf("----------------------\n") ;
		printf("1.Play Game\n") ;
			printf("----------------------\n") ;
		printf("2.Rules\n"); 
			printf("----------------------\n") ;
		printf("3.Top 5 scores of All time\n") ;
			printf("----------------------\n") ;
		printf("4.Exit\n") ; 
			printf("----------------------\n") ;
		scanf("%d",&choice) ;
		switch(choice){
			case 1: 
//				printf("Game code whole\n") ;
				    // Defining variables
			printf("---------------------------------\n") ;
			system("cls") ; 
		    setTextColor(LIGHT_BLUE);
    int max, i, attempts = 3,userexit = 1,totalscore=0,score=0;
    char hint[100], word[32], orgword[32], guess[32] ;
	char playername[100];
    char diffmode;
    srand(time(NULL));
    FILE *filepointer;
//    printf("WELCOME TO OUR WORD GUESSING GAME\n");
//    printf("---------------------------------\n") ;
 	int name_exit = 0 ; 
 	printf("Enter player name : ") ;
 	getchar() ; 
	gets(playername) ;
	while(1){
		name_exit=0;
		for(i=0;i<strlen(playername);i++){
			if(playername[i] == 32){
				name_exit = 1;
			}
		}
		if(name_exit ==1){
			printf("Error!Enter without spaces\n") ;
			printf("Enter player name : ") ;
			gets(playername) ; 
		}
		else
			break ; 
	}
//    printf("You entered: %s\n", playername);
    
//  	printf("Enter your first name : ") ;
//  	getch
//  	gets(playername) ;
    while(userexit == 1) {
    	attempts = 3;
    	score=0;
    printf("Select your difficulty mode\n");
    printf("1. Easy (press 'e' on keyboard)\n");
    printf("2. Medium (press 'm' on keyboard)\n");
    printf("3. Hard (press 'h' on keyboard)\n");
    
  	while(1){
  		scanf(" %c", &diffmode);
  		if (diffmode == 'e' || diffmode == 'm' || diffmode == 'h' ||
            diffmode == 'E' || diffmode == 'M' || diffmode == 'H') {
            	break ;
	  	}
	  	else{
	  		printf("Invalid difficulty mode\n") ;
	  	 }
	  }
//    scanf(" %c", &diffmode);
    
    switch(diffmode) {
    
        case 'e':   
        case 'E': 
        filepointer = fopen("easy.txt", "r");	
            max = rand() % 55 + 1;
            for(i = 1; i <= max; i++) {
                fgets(word, sizeof(word), filepointer);
                fgets(hint, sizeof(hint), filepointer);
            } 
            // Remove newline characters from word and hint
            word[strcspn(word, "\n")] = '\0';
            hint[strcspn(hint, "\n")] = '\0';
            
            // Prepare lowercase version of the original word
            strcpy(orgword, word);
            strlwr(orgword);
            // Reverse the mixed word for the user to guess
            strrev(word);
            
            printf("GUESS THE FOLLOWING WORD : %s\n", strupr(word)); 
            int exit = 1, hints = 1;
            //timer start
            time_t startTime = time(NULL);	
            printf("You have %d seconds to guess the word.\n", MAX_GUESS_TIME_E);
            while (exit == 1 && attempts != 0 && !isTimeUp(startTime, MAX_GUESS_TIME_E)) {

                printf("\t\nEnter your guess or press 'h' for hint\n");
                scanf("%s", guess);
                strlwr(guess);
                if (strcmp(guess, "h") == 0) { 
                    switch(hints) {
                        case 1:
                            printf("\n\"%s\"\n", hint);
                            hints--;
                            break;
                        case 0:
                            printf("\t\nNo hints remaining\n");
                            break;
                    }
                } else if (strcmp(guess, orgword) == 0) {
                	setTextColor(GREEN);
                    printf("\"RIGHT GUESS\"\n");
                    setTextColor(LIGHT_BLUE);
                    exit = 0;  
                }
                else if (strcmp(guess, orgword) == 0 && (isTimeUp(startTime, MAX_GUESS_TIME_E))){
                	setTextColor(RED);
					printf("RIGHT GUESS BUT TIME IS UP\n");
					setTextColor(LIGHT_BLUE);
                	exit = 0;
				}
				 else {
                    attempts--;
                    setTextColor(RED);
                    printf("\tWrong guess (attempts remaining = %d)\n", attempts);
                    setTextColor(LIGHT_BLUE);
                }
                if (isTimeUp(startTime, MAX_GUESS_TIME_E)){
                	setTextColor(RED);
                	printf("Your time is up!\n");
                	setTextColor(LIGHT_BLUE);
                	exit = 0;
				}
                
			        
        }
            //scoring the user 
                               //criteria for hint -5 and for everywrong attempt = -5

            if(hints == 0 && !isTimeUp(startTime, MAX_GUESS_TIME_E)) {
            	switch(attempts){   
            		case 3 :
            			score = 95 ;
            		    break  ; 
            		case 2 : 
            		    score=  90;
            		    break ;
            		case  1 :
            			score = 85;
				}
			}
			else if(hints ==1 && !isTimeUp(startTime, MAX_GUESS_TIME_E)){
					switch(attempts){
            		case 3 :
            			score = 100 ;
            		    break  ; 
            		case 2 : 
            		    score=  95;
            		    break ;
            		case 1 :
            			score = 90 ;
				}
				
			}
			// Deduct 50% of the score with additional 5 points as a penalty for exceeding the time limit.
			if (isTimeUp(startTime, MAX_GUESS_TIME_E) && strcmp(guess, orgword) == 0) {
			    switch(attempts){
            		case 3 :
            			score = 50 ;
            		    break  ; 
            		case 2 : 
            		    score=  45;
            		    break ;
            		case 1 :
            			score = 40;
				}
			    }
  		    break ; 
  		    
        //Now doing it for medium 
        case 'm':
        case 'M':
        filepointer = fopen("medium.txt", "r");	
            max = rand() % 55 + 1;
            for(i = 1; i <= max; i++) {
                fgets(word, sizeof(word), filepointer);
                fgets(hint, sizeof(hint), filepointer);
            } 
            // Remove newline characters from word and hint
            word[strcspn(word, "\n")] = '\0';
            hint[strcspn(hint, "\n")] = '\0';
            
            // Prepare lowercase version of the original word
            strcpy(orgword, word);
            strlwr(orgword);
            // Reverse the mixed word for the user to guess
            changeword(word);
            //timer start
            startTime = time(NULL);	
            printf("You have %d seconds to guess the word.\n", MAX_GUESS_TIME_M);
            
            printf("GUESS THE FOLLOWING WORD : %s\n", strupr(word)); 
  			exit = 1; hints = 1;
            while (exit == 1 && attempts != 0) {
                printf("\t\nEnter your guess or press 'h' for hint\n");
                scanf("%s", guess);
                strlwr(guess);
                if (strcmp(guess, "h") == 0) { 
                    switch(hints) {
                        case 1:
                            printf("\n\"%s\"\n", hint);
                            hints--;
                            break;
                        case 0:
                            printf("\t\nNo hints remaining\n");
                            break;
                    }
                } else if (strcmp(guess, orgword) == 0) {
                	setTextColor(GREEN);
                    printf("\"RIGHT GUESS\"\n");
                    setTextColor(LIGHT_BLUE);
                    exit = 0;  
                } else {
                    attempts--;
                    setTextColor(RED);
                    printf("\tWrong guess (attempts remaining = %d)\n", attempts);
                    setTextColor(LIGHT_BLUE);
                }
                  if (isTimeUp(startTime, MAX_GUESS_TIME_M)){
                  	setTextColor(RED);
                	printf("Your time is up!\n");
                	setTextColor(LIGHT_BLUE);
                	exit = 0;
				}
                
            }
            //scoring the user 
                        //criteria for hint -10 and for everywrong attempt = -10
            if(hints == 0 && !isTimeUp(startTime, MAX_GUESS_TIME_M)) {
            	switch(attempts){   
            		case 3 :
            			score = 115 ;
            		    break  ; 
            		case 2 : 
            		    score=  105;
            		    break ;
            		case  1 :
            			score = 95;   
				}
			}
			else if(hints ==1 && !isTimeUp(startTime, MAX_GUESS_TIME_M)){
					switch(attempts){
            		case 3 :
            			score = 125 ;
            		    break  ; 
            		case 2 : 
            		    score=  115;
            		    break ;
            		case 1 :
            			score = 105;
				}
				
			}
			// Deduct 50% of the score with additional 5 points as a penalty for exceeding the time limit.
			if (isTimeUp(startTime, MAX_GUESS_TIME_M) && strcmp(guess, orgword) == 0) {
			    switch(attempts){
            		case 3 :
            			score = 58 ;
            		    break  ; 
            		case 2 : 
            		    score=  53;
            		    break ;
            		case 1 :
            			score = 48;
				}
			    }
  			printf("\nYour score is %d\n",score) ;  
  			break ;
		 //now for hard
		case 'h': 
		case 'H':
        filepointer = fopen("hard.txt", "r");	
            max = rand() % 55 + 1;
            for(i = 1; i <= max; i++) {
                fgets(word, sizeof(word), filepointer);
                fgets(hint, sizeof(hint), filepointer);
            } 
            // Remove newline characters from word and hint
            word[strcspn(word, "\n")] = '\0';
            hint[strcspn(hint, "\n")] = '\0';
            
            // Prepare lowercase version of the original word
            strcpy(orgword, word);
            strlwr(orgword);
            // Reverse the mixed word for the user to guess
            changeword(word);
            //timer start
            startTime = time(NULL);	
            printf("You have %d seconds to guess the word.\n", MAX_GUESS_TIME_H);
            
            printf("GUESS THE FOLLOWING WORD : %s\n", strupr(word)); 
    	exit = 1; hints = 1;	
            while (exit == 1 && attempts != 0) {
                printf("\t\nEnter your guess or press 'h' for hint\n");
                scanf("%s", guess);
                strlwr(guess);
                if (strcmp(guess, "h") == 0) { 
                    switch(hints) {
                        case 1:
                            printf("\n\"%s\"\n", hint);
                            hints--;
                            break;
                        case 0:
                            printf("\t\nNo hints remaining\n");
                            break;
                    }
                } else if (strcmp(guess, orgword) == 0) {
                	setTextColor(GREEN);
                    printf("\"RIGHT GUESS\"\n");
                    setTextColor(LIGHT_BLUE);
                    exit = 0;  
                } else {
                    attempts--;
                    setTextColor(RED);
                    printf("\tWrong guess (attempts remaining = %d)\n", attempts);
                    setTextColor(LIGHT_BLUE);
                }
                if (isTimeUp(startTime, MAX_GUESS_TIME_H)){
                	setTextColor(RED);
                	printf("Your time is up!\n");
                	setTextColor(LIGHT_BLUE);
                	exit = 0;
				}
            }
            //scoring the user 
                        //criteria for hint -15 and for everywrong attempt = -15
            if(hints == 0 && !isTimeUp(startTime, MAX_GUESS_TIME_H)) {
            	switch(attempts){   
            		case 3 :
            			score = 135 ;
            		    break  ; 
            		case 2 : 
            		    score=  120;
            		    break ;
            		case  1 :
            			score = 105;
				}
			}
			else if(hints ==1 && !isTimeUp(startTime, MAX_GUESS_TIME_H)){
					switch(attempts){
            		case 3 :
            			score = 150 ;
            		    break  ; 
            		case 2 : 
            		    score=  135;
            		    break ;
            		case 1 :
            			score = 120;
				}
			}
			// Deduct 50% of the score with additional 5 points as a penalty for exceeding the time limit.
  		if (isTimeUp(startTime, MAX_GUESS_TIME_H) && strcmp(guess, orgword) == 0) {
			    switch(attempts){
            		case 3 :
            			score = 70 ;
            		    break  ; 
            		case 2 : 
            		    score=  65;
            		    break ;
            		case 1 :
            			score = 60;
				}
			}
		 break ;  
      
    }
         totalscore+=score  ; 
		 printf("%s your score is %d\n",playername,score) ;
         printf("To continue enter 1 or enter 2 to exit\n") ;
         scanf("%d",&userexit) ;
       
}
 printf("%s your all time score is %d \n",playername,totalscore) ; 
    fclose(filepointer);
		    	//top 5 players append
		    		
				    fp = fopen("scores.txt", "r");
				    if (fp == NULL) {
				        printf("Error opening file.\n");
//				        exit(1);
				    }
				    for (i = 0; i < 5; i++) {
				        fscanf(fp, "%s", name);
				        fscanf(fp, "%d", &h_score);
				        strcpy(highscores[i].playername, name);
				        highscores[i].score = h_score;
				    }
				    fclose(fp);
				    //the data has been read in the struct
//				    sort_struct();
//				    printf("Original high scores:\n");
//				    print_struct();
					replace(playername,totalscore);
					sort_struct() ; 
					//now writing the update struct back into the file
					fp =fopen("scores.txt","w") ;
					for(i=0;i<5;i++){
						strcpy(name,highscores[i].playername) ;
						h_score = highscores[i].score ;
						fprintf(fp,"%s\n",name) ;
						fprintf(fp,"%d\n",h_score) ;
					}
					fclose(fp) ;
//				    printf("\nAfter replacement:\n");
//				    print_struct();
				break ;
			case 2 : 
				system("cls") ; 
				rules() ;
				break ;
			case 3 : 
				system("cls") ; 
				printf("Top 5 scores of All TIME :\n") ;
				//read data from the top 5 scores files	
				   	FILE *fp ;
				    fp = fopen("scores.txt", "r");
				    if (fp == NULL) {
				        printf("Error opening file.\n");
//				        exit(1);
				    }
				    for (i = 0; i < 5; i++) {
				        fscanf(fp, "%s", name);
				        fscanf(fp, "%d", &h_score);
				        strcpy(highscores[i].playername, name);
				        highscores[i].score = h_score;
				    }
				    fclose(fp);  
					print_struct();
				    //the data has been read in the struct
//				    sort_struct();
//				    printf("Original high scores:\n");
//				    print_struct();
//					replace(playername,totalscore);
//					sort_struct() ; 
//					//now writing the update struct back into the file
//					fp =fopen("scores.txt","w") ;
//					for(i=0;i<5;i++){
//						strcpy(name,highscores[i].playername) ;
//						h_score = highscores[i].score ;
//						fprintf(fp,"%s\n",name) ;
//						fprintf(fp,"%d\n",h_score) ;
//					}
//					fclose(fp) ;
//				    printf("\nAfter replacement:\n");
//				    print_struct();
				break ;
			case 4 : 
				exit = 1;
				system("cls") ;
				Exit() ; 
				break ;
		}
		if(exit ==1 ){
			break  ; 
		}
	}
}
