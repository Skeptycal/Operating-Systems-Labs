#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

//Test fillArgs
//int runLine(char* cmd);

int i=-1;
int debug=1;
int fd;


int runSingle(char* cmd){
	//i.e. "printenv --gdfgd 2"
  //or    "/bin/ls"
  //Make 2 of "printenv --gdfgd" go to output
    int i=-1;
    
/**/int dirFlag=0;
    
//IF executive contains a '/'
//THEN dirFlag = 1
    int lastSlash=-1;
    int firstSpace=-1;
    lastSlash=firstSpace=-1;
    lastSlash=-1;
    int stop=-1;
    char* exename;
    int numberOfSpaces=0;

    for(i=0;i<strlen(cmd);i++){
        if(cmd[i]=='/' && stop==0){
            lastSlash=i;
	    for(;;){}
	}
        if((cmd[i]==' '||cmd[i]=='\0')&& stop==0){
            firstSpace=i;
            stop=1;
	}
        if(cmd[i]==' '){
	    numberOfSpaces++;
        }
    }
    printf("num of spaces=%d\n",numberOfSpaces);

    if(lastSlash==-1){
        //Set dirFlag
        dirFlag=0;
    }else{
         // 0123456789
         //"/bin/ls -a"
         //     lS fS
         //     4  7
        //printf("the strincmd[");
	 
        //Take from first space to last integer
        exename=malloc(sizeof(char)*(firstSpace-lastSlash+1));

		printf("firstSpace-lastSlash = %d\n",firstSpace-lastSlash);
        //if(exename!=NULL){	
		strncpy(exename,cmd[lastSlash],firstSpace-lastSlash);
        //}
        
        //Set dirFlag
        dirFlag=1;
    }
    




//Make array of args
    //Get number of args              FOR NULL
    //int numberOfArgs=numberOfSpaces+1+1;
    
    
    //Array for each offset of each space
	    //"printenv --gdfgd"
	    //         \0
	    // 0123456789012345
    int** nulls = malloc(sizeof(int)*numberOfSpaces);
    if(nulls==NULL){
		perror("Mallocing nulls failed.\n");
		exit(-1);
    }

    int nullInd=0;
    for(i=0;i<strlen(cmd);i++){
        if((cmd[i]==' ')){
            *(nulls+nullInd)=i;
	    nullInd++;
        }
    }

    printf("The first space is located at %d, should be at 8\n",*(nulls));
    printf("The second space is located at %d, should be at 14\n",*(nulls+1));


    //Make each space='\0'
    int gg;
    char put='\0';
    char* tempString = malloc(sizeof(char)*strlen(cmd)+1);
    strcpy(tempString,cmd);
    for(i=0;i<numberOfSpaces;i++){
		gg=*(nulls+i);
        *(tempString+gg)=put;
    }
    
    printf("The char is now '%x'.\n",*(tempString+gg));
    
    
												//1 for NULL
												//1 for the Zero-ith Arg
    int** args = malloc(sizeof(int)*numberOfSpaces+2);
//Make args point to each one of the *(tempString+*(nulls+(0 to <#ofSpace))
    int counter;



/**///if not dirFlag
 
    //Make first point to beginning
    *(args)=&*(tempString);
    printf("*arg #0 is %s\n",*(args));

    //Fill args 0 to n-1
    for(counter=0;counter<numberOfSpaces;counter++){
	   	gg=*(nulls+counter);
		gg++;
		//tempString+gg is char after null
		*(args+counter+1)=&*(tempString+gg);
		
		printf("*arg #%d is %s\n",counter+1,*(args+counter+1));
    }
    
    //Make last point to NULL
    *(args+numberOfSpaces+1)=NULL;
    printf("*arg #%d is %s\n",numberOfSpaces+1,*(args+numberOfSpaces+1)); 
    
    
    printf("\nstop here\n");
    fflush(NULL);
    //execvp(*(args),args);
    
    
    
    return(0);
}




int main(int argc, char ** argv, char **envp){
	//printenv --gdfgd 2>err
	char* cmd = "printenv --gdf gd";
	printf("The command:%s\n",cmd);
	runSingle(cmd);
	return(0);
}


//Wrap if last char is number
//i.e. "printenv --gdfgd 2"
//int result = runSingle(cmd);















/*
//Run Prototype:	
int runLine(char* cmd){
	int hmm;	
	//Get how many meta
	for(i=0;i<length(cmd);i++)
		if(cmd[i]=='<' || ch=='>')
			hmm++;
	
	//Make array to hold where the metas are in the array (+1 for \0)
	int metaOS[] = malloc(sizeof(int)*(hmm+1));
	
	//Make array to hold what type of meta is at each index (+1 for \0)
	int metaT[] = malloc(sizeof(int)*(hmm+1));
	
	//Array Index
	int metaAI=0;
	
	//Put WHERE in metaOS and put WHAT in metaT
	for(i=0;i<length(cmd);i++){
		if(cmd[i]=='<' || cmd[i]=='>')
			metaOS[metaAI]=i;
		if(cmd[i]=='<')//LESS    THAN = 1
			metaT[metaAI]=1;
		if(cmd[i]=='>')//GREATER THAN = 2
			metaT[metaAI]=2;
		metaAI++;
	}
	
	//Null byte is the last metacharacter
	metaOS[metaAI]=strlen(mons);
	metaT[metaAI]=0;
	
	//Reset metaArrayIndex to zero
	metaAI=0;
	int lastIndex=0;
	////////////////////////////////////
	////////////////////////////////////
	//Execute       each      argument//
	////////////////////////////////////
	////////////////////////////////////
	START:
	if(metaAI!=hmm){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//If next meta is LESS    THAN >
		if(metaT[metaAI]==1){
			
			//Malloc command string on the left
			char* cmd = malloc(sizeof(char)*(metaOS[metaAI]-lastIndex));
			strncpy(cmd,cmd[lastIndex],metaOS[metaAI]-lastIndex);
			
			//Malloc file string on the right
			char* file = malloc(sizeof(char)*(metaOS[metaAI+1]-metaOS[metaAI]));
			strncpy(file,cmd[metaAI],metaOS[metaAI+1]-metaOS[metaAI]);
			
			
			
		//Open file
			fd = open(file, O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		  	//CHECK FOR FAILURE
		  	if (fd < 0) {
				perror("Creating %s failed.\n",file);
				exit(-1);
			}
			
			
			
		//Write to file
			//Save stdout
			int oldout = dup(1);
			
			//All output goes to fd.
			dup2(fd,1);
			
			//Fork			
			pid_t pid = fork();
			//CHECK FOR FAILURE	
			if (pid < 0) {					
				perror("Fork in metaT[metaAI]==1 LESS THAN failed.\n");			
				exit(-1);			
			}			
			
		//The child's code
			if(pid == 0){
				/*
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * *		
				
				//Wrap if last char is number
				//i.e. "printenv --gdfgd 2"
				int result = runSingle(cmd);
				if(result==-1){
					printf("Unfortunatly cmd failed to run.");
				}
				close(fd);
				/*
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * 
				 * *		
				
			}else{
				wait(NULL);
			}
			
			
			//Close file
			close(fd);
			
			//Restore stdout
			dup2(oldout, 1);
			
			
			
			
			
			
			
			
			
			

		}

		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//If next meta is GREATER THAN <
		if(metaT[metaAI]==2){
			
			
			//Open right as input
			//IT HAS TO BE A FILE
			metaOS[metaAI+1]-metaOS[metaAI]
			
			//Write into left, IT HAS TO BE A COMMAND
			
		}
		
		lastIndex=metaOS[metaAI];
		metaAI++;
		goto START
	}
	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(metaAI==0)
		runSingle(cmd);
	
	
	
	
	free(metaOS);
	free(metaT);
}
*/

//Test run()

/*
//Run Prototype:	
int run(char* cmd, int numOArgs){	
	int numOArgs = getNumOArgs(cmd);		
	char** argList = malloc(sizeof(int)*numOArgs);	
	fillArgs(argList,cmd);	
	if(!dirFlag){
			//Loop through PATH? Probably not.
			execvp(arg0,argList);//man says "const char *file, char *const argv[]"
	}	
	else{
		execv(dir token, argList);
	}
	free(argList);
}
*/


/*
//Fills argList with each command by splitting by ' '
void fillArgs(char** argList, char* cmd, int numArgs){
	int i=0;//Global i might be effected
	//WATCH FOR DANGLING POINTERS
	
	char* currArg = &argList;
	
	for(strtok(cmd,' ')){
		if(numArgs==i){
			//if(currArg is a number)
			//****dup entire function to the number**** somecommand 2>err.log
		}
		if contains '/'{
			dirFlag=1;
			dir = malloc(sizeof(char)*length(tok)+1);
			strncpy(dir,tok,sizeof(char)*length(tok));
		}else{
			//Malloc length and put it in argList
			currArg = malloc(sizeof(char)*length(tok)+1);
			strncpy(currArg,tok,sizeof(char)*length(currArg));
		}
		currArg++;
		i++;
	}
}
*/

//Test open("outfilePipes", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
//Test fork setenv effecting parent some how
