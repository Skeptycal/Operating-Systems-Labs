#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int runSingle(char* cmd2);

int main(int argc, char ** argv, char **envp){
	//char* cmd = "/bin/ls ";
	//char* cmd = "/bin/ls *.o";
	char* cmd = "/bin/ls";
	//char* cmd = "printenv --gdfgd 2";
	//char* cmd = "printenv --gdf gd";
	printf("The command:%s\n",cmd);
	runSingle(cmd);
	return(0);
}

int runSingle(char* cmd2){
//i.e. "printenv --gdfgd 2"
//or    "/bin/ls"
//Make 2 of "printenv --gdfgd" go to output
    //
    int total=0;
    int weHadTo=0;
    int oldout;
    //
    int debug=1;
    //
    char* cmd = malloc(sizeof(char)*strlen(cmd2)+1);
    strcpy(cmd,cmd2);

    if(strlen(cmd)!=strlen(cmd2)){
        printf("OH SHIT WE GOT PROBLEMS. MALLOC ONE LESS");
    }
    
    int i=-1;
    int lastSlash=-1;
    int firstSpace=-1;
    lastSlash=firstSpace=-1;
    lastSlash=-1;
    char* exename;
    int numberOfSpaces=0;
    int lastSpace=-1;
/////////////////////////////
//IF executive contains a '/'
//THEN dirFlag = 1
    int dirFlag=0;
/////////////////////////////
    
    ///////////
    //Make copy of cmd that's modifiable
    //ghi
    //B
    
    //1.Loop through cmd
    //2.Get index of the lastSlash
    //3.Get index of the firstSpace
    //4.Get index of the lastSpace
    int stop=0;
    for(i=0;i<strlen(cmd);i++){
	if(debug)
		printf("cmd[%d]=%c\n",i,cmd[i]);
        if(cmd[i]=='/' && stop!=1){
            lastSlash=i;
            dirFlag=1;
        }
        if((cmd[i]==' '||cmd[i]=='\0')&&stop!=1){
            firstSpace=i;
            stop=1;
        }
        if(cmd[i]==' '){
            lastSpace=i;
            numberOfSpaces++;
        }
    }
    
     
    if(debug){
	printf("dirFlag=%d\n",dirFlag);
	printf("lastSlash=%d\tfirstSpace=%d\n",lastSlash,firstSpace);
    }
    
    //If there is a space in the program check if the last argument is a number B
    if(lastSpace!=-1){
	char maybeNumber;
	int i=1;
	int charAsNum;
        //Loop through lastSpace to ' ' or '\0
        while(1){
	    //printf("ghi This infinite loop");
            //int i=1;
            maybeNumber=cmd[lastSpace+i];
            charAsNum=(int)maybeNumber;
	    
	    if(debug){
	    	printf("The currChar is %x\ni is %d",maybeNumber,i);
            	printf("charAsNum is %d\n",charAsNum);	
	    }

	    //need to account for lower case

	    //If it is not a number
            if(maybeNumber>57 || maybeNumber<48){
                //We don't have to pipe it
		
                break;
            }
            
            if(i>1&&charAsNum==0){//maybeNumber=='\0'&&i>1){
		if(debug)
			printf("We had to\n");
                weHadTo=1;
                
                //Make lastSpace NULL
                *(cmd+lastSpace)='\0';
                /*
                char put='\0';
                for(i=0;i<numberOfSpaces;i++){
                    gg=*(nulls+i);
                    *(cmd+gg)=put;
                }
                */
                //char nullinLastSpace='\0';
                
                //Based on the numberFlag
                int iInEndIf;
                int singleDigit;
                for(iInEndIf=1;iInEndIf<i;iInEndIf++){
                    //274 
                    //i=4
                    //(lastSpace+(i-iInEndIf)
                    
                    //(lastSpace+(i-1) is 4)
                    //(lastSpace+(i-2) is 7)
                    //(lastSpace+(i-3) is 2)
                    
                    //Get number of each char
                    singleDigit=(int)((lastSpace+(i-iInEndIf))-48);
                    //(lastSpace+(i-1) is 4) = 
                    //(lastSpace+(i-2) is 7) = 
                    //(lastSpace+(i-3) is 2) = 
                    
                    //Get the whole
                    int addZeroes;
                    for(addZeroes=0;addZeroes<iInEndIf;addZeroes++){
                        //(lastSpace+(i-1) * 10^(iInEndIf-1)
                        
                        //(lastSpace+(i-1) is 4) * 1
                        //(lastSpace+(i-2) is 7) * 10
                        //(lastSpace+(i-3) is 2) * 100
                        singleDigit*=10;
                    }
                    total+=singleDigit;
                    if(debug){
                        printf("Total is now %d\n",total);
                        fflush(NULL);
                    }
                }
                //Save stdout
                oldout = dup(1);
                
                //All output goes to fd.
                dup2(total,1);
                
                break;
            }
            i++;
        }
    }
    if(debug){
	    printf("AFTER WEHADTO\n");
		printf("lastSlash=%d\tfirstSpace=%d\n",lastSlash,firstSpace);
		printf("num of spaces=%d\n",numberOfSpaces);
	}
    if(!dirFlag){}
    else{
        // 0123456789
        //"/bin/ls -a"
        //     lS fS
        //     4  7
        

	   // 0123456789
        //"/bin/ls"
        //     lS
        //     4  
	//fS = -1


    //malloc for exename
	int hmm4exe;
	if(firstSpace==-1){
	    	//We have no spaces
		
		//malloc strlen-lS
		hmm4exe=strlen(cmd)-lastSlash;
	}else{
		//We have a space
		
		//malloc fS-lS
		hmm4exe=firstSpace-lastSlash;
	}
        exename=malloc(sizeof(char)*hmm4exe+1);
        
	if(debug){
		printf("\n***hmm4exe=%d***\n",hmm4exe);
	}
	
	printf("AFTER MALLOC\nfirstSpace=%d\tlastSlash=%d\thmm4exe= %d\n",firstSpace,lastSlash,hmm4exe);
	strncpy(exename,(cmd+lastSlash+1),hmm4exe);
	char als=*(cmd+lastSlash+1);
	printf("\n\nals=%c\n\n\n",als);
	fflush(NULL);

    //strncpy(exename,(cmd+lastSlash+1),hmm4exe);
	
	if(debug)
            printf("Executable name is %s\n\n",exename);
    }

//Make array of args
    //Get number of args              FOR NULL
    //int numberOfArgs=numberOfSpaces+1+1;
    
    
    //Array for each offset of each space
	    //"printenv --gdfgd"
	    //         \0
	    // 0123456789012345
    int** nulls;
    int gg;   
	if(numberOfSpaces!=0){
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
	
	    printf("strlen of cmd is %d\ncmd is %s\n",strlen(cmd),cmd);
	    //printf("The first space is located at %d, should be at 8\n",*(nulls));
	    //printf("The second space is located at %d, should be at 14\n",*(nulls+1));
	
	
	    //Make each space='\0'
	    char put='\0';
	    for(i=0;i<numberOfSpaces;i++){
			gg=*(nulls+i);
	        *(cmd+gg)=put;
	    }
	    
	    printf("The char is now '%x'.\n",*(cmd+gg));
	}else{
		nulls = malloc(sizeof(int)*10);
	}    
    
												//1 for NULL
												//1 for the Zero-ith Arg
    int** args = malloc(sizeof(int)*numberOfSpaces+2);
//Make args point to each one of the *(cmd+*(nulls+(0 to <#ofSpace))
    int counter;



    if(dirFlag){
        //Make first point to the exename
        *(args)=&*(exename);
    }
    if(!dirFlag){
        //Make first point to beginning
        *(args)=&*(cmd);
    }
    if(debug){
        printf("*arg #0 is %s\n",*(args));
    }
    
    //Fill args 0 to n-1
    for(counter=0;counter<numberOfSpaces;counter++){
	   	gg=*(nulls+counter);
		gg++;
		//cmd+gg is char after null
		*(args+counter+1)=&*(cmd+gg);
		
		printf("*arg #%d is %s\n",counter+1,*(args+counter+1));
    }
    
    //Make last point to NULL
    *(args+numberOfSpaces+1)=NULL;
    printf("*arg #%d is %s\n",numberOfSpaces+1,*(args+numberOfSpaces+1)); 
    

    pid_t pid = fork();
    //CHECK FOR FAILURE	
    if (pid < 0) {					
        perror("Fork failed.\n");			
        exit(-1);			
    }			
    
    if(dirFlag&&debug)
	printf("It's going to pass %s as the first arg to execv",cmd);
    
    //IF child THEN  exec
    if(pid==0){
        if(dirFlag){
            execv(cmd,args);
            close(total);
        }
        if(!dirFlag){
            execvp(*(args),args);
            close(total);
        }
    }else{
        wait(NULL);
                
        if(weHadTo){
            //Close file
            close(total);
            //Restore stdout
            dup2(oldout, 1);
        }
    }
    
    return(0);
}