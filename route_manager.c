/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

void user_case1(const char* file_name, char *arg1, char* arg2){         //User case 1 that provides 4 arguments in command line
    FILE *fp;
    fp = fopen(file_name, "r");  //opening the csv file 

    if (fp == NULL) {
        perror("Error opening file");      //check if the file exists
        exit (1);
    }

    FILE *output;
    output = fopen("output.txt", "w");       //opening the output.txt file

     if (output == NULL) {
         perror("Error opening file");      //check if the output file exists
         exit (1);
     }
 
     char line[1000];                       //initializing a line 
     char *token;                          //initializing a token to store the components of line

     int flag = 0;                                 //flag will check if there is any similar result found in the file

     while (fgets(line, 1000, fp) != NULL) {      //looping through the file
         
         char tokens[13][200];                   //initializing array that will store all the fields of the line
         char line_new[1000];                   //Creating duplicate line that will copy the current line
         strcpy(line_new, line);

         token = strtok(line_new,",");        //Getting the first token of the string line
         int i = 0;                          //Taking care of array index
         while (token!= NULL){
             strcpy(tokens[i],token);
             token = strtok(NULL,",");
             i++;
         }

         if (strcmp(tokens[1],arg1)==0 && strcmp(tokens[10],arg2)==0){
            if (flag==0){
                 fprintf(output, "FLIGHTS TO %s BY %s (%s):\n", tokens[10], tokens[0], tokens[1]);  //Printing this line only once
            }
            fprintf(output, "FROM: %s, %s, %s TO: %s (%s), %s\n", tokens[6], tokens[4], tokens[5], tokens[8], tokens[11], tokens[9]);  
            flag++;
           
        }   
         
     }

     if (flag == 0) {
        fprintf(output, "NO RESULTS FOUND.\n");    //If our flag is 0 that means no results are found
    }


    
     fclose(output);          //Closing both input csv file and output file
     fclose(fp);
     exit(0);
    
}

void user_case2(const char* file_name, char *arg1, char* arg2, char *arg3){
    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit (1);
    }

    FILE *output;
    output = fopen("output.txt", "w");           

     if (output == NULL) {
         perror("Error opening file");
         exit (1);
     }
 
     char line[1000];                                            //Same steps as in user case 1 
     char *token;

     int flag = 0;

     while (fgets(line, 1000, fp) != NULL) {
         
         char tokens[13][200];
         char line_new[1000];
         strcpy(line_new, line);
         token = strtok(line_new,",");
         int i = 0;
         while (token!= NULL){
             strcpy(tokens[i],token);
             token = strtok(NULL,",");
             i++;
         }

         if (strcmp(tokens[5],arg1)==0 && strcmp(tokens[10],arg2)==0 && strcmp(tokens[9],arg3)==0){      //Cmparing with 3 arguments provided in user case 2
            if (flag==0){
                 fprintf(output, "FLIGHTS FROM %s TO %s, %s:\n", tokens[5], tokens[9], tokens[10]);        //printing according to case 2
            }
            fprintf(output, "AIRLINE: %s (%s) ORIGIN: %s (%s), %s\n", tokens[0],tokens[1],tokens[3], tokens[6], tokens[4]);
            flag++;   
        }     
     }

     if (flag==0) {
        fprintf(output, "NO RESULTS FOUND.\n");
    }

     fclose(output);
     fclose(fp);
     exit(0);
    
}

void user_case3(const char* file_name, char *arg1, char* arg2, char* arg3, char* arg4){
    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit (1);
    }

    FILE *output;
    output = fopen("output.txt", "w");

     if (output == NULL) {
         perror("Error opening file");
         exit (1);                                       //Similar steps in above user cases 
     }
 
     char line[1000];
     char *token;

     int flag = 0;

     while (fgets(line, 1000, fp) != NULL) {
         
         char tokens[13][200];
         char line_new[1000];
         strcpy(line_new, line);
         token = strtok(line_new,",");
         int i = 0;
         while (token!= NULL){
             strcpy(tokens[i],token);
             token = strtok(NULL,",");
             i++;
         }
         if (strcmp(tokens[4],arg1)==0 && strcmp(tokens[5],arg2)==0 && strcmp(tokens[9],arg3)==0 && strcmp(tokens[10],arg4)==0){     //Comparing with 4 arguments
            if (flag==0){
                 fprintf(output, "FLIGHTS FROM %s, %s TO %s, %s:\n", tokens[4], tokens[5], tokens[9], tokens[10]);       //Printing according to the case 3
            }
            fprintf(output, "AIRLINE: %s (%s) ROUTE: %s-%s\n", tokens[0], tokens[1], tokens[6], tokens[11]);
            flag++;  
        }      
     }

     if (flag == 0) {
        fprintf(output, "NO RESULTS FOUND.\n");
    }

     fclose(output);
     fclose(fp);
     exit(0);
    
}


int main(int argc, char *argv[])
{
    char *airline;
    char *dcountry;          //Initializing variables that will store the arguments provided 
    char *scountry;
    char *dcity;
    char *scity;
    char *fname;
    char* DELIMITER = "="; //used to split the arguments provided 

    fname = strtok(argv[1],DELIMITER);
    fname = strtok(NULL, DELIMITER);      //Storing the file name

    switch(argc){
        case 4:                                     //Handling the user case 1
            airline = strtok(argv[2], DELIMITER);
            airline = strtok(NULL, DELIMITER);
            dcountry = strtok(argv[3], DELIMITER);
            dcountry = strtok(NULL, DELIMITER);

            user_case1(fname, airline, dcountry);    //Calling user_case1
            break;
    
        case 5:                                      //Handling the user case 2
            scountry = strtok(argv[2], DELIMITER);
            scountry = strtok(NULL, DELIMITER);
            dcity = strtok(argv[3], DELIMITER);
            dcity = strtok(NULL, DELIMITER);
            dcountry = strtok(argv[4], DELIMITER);
            dcountry = strtok(NULL, DELIMITER);

            user_case2(fname, scountry, dcountry, dcity);      //Calling the user_case2
            break;

        case 6:                                       //Handling the user case 3
           scity = strtok(argv[2], DELIMITER);
           scity = strtok(NULL, DELIMITER);

           scountry = strtok(argv[3], DELIMITER);
           scountry = strtok(NULL, DELIMITER);

           dcity = strtok(argv[4], DELIMITER);
           dcity = strtok(NULL, DELIMITER);

           dcountry = strtok(argv[5], DELIMITER);
           dcountry = strtok(NULL, DELIMITER);

           user_case3(fname, scity, scountry, dcity, dcountry);       //Calling the user_case3 
     }
    return 0;
}
  