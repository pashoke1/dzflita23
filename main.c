#include <stdio.h>
#include <stdlib.h>


int main(void){
     int NumV=0;
     int NumN=0;
     int c;
	 FILE *MatrFile=fopen("matr.txt", "r");
	 if(MatrFile==NULL){
        printf("No such File");
     }else{
        while(!feof(MatrFile)){              
            if((fgetc(MatrFile))==';'){
                NumV++;
            }
        } 
        fclose(MatrFile);
        FILE *MatrFile=fopen("matr.txt", "r");
        while((c=fgetc(MatrFile))!=';'){
            if(c==',')
                NumN++;
        }
        NumN++;
        fclose(MatrFile);
        int Arr [NumV][NumN]; // матрица инцидентности
        MatrFile=fopen("matr.txt", "r");
        for(int i=0;i<NumV;i++){
            int j=0;
            while((c=fgetc(MatrFile))!=';')
                fscanf(MatrFile,"%d",&Arr[i][j++]);
        }
        fclose(MatrFile);

    
        char VertNames[NumV]; // массив вершин
        for (int i = 0; i < NumV; i++)
            VertNames[i]='a' +i;
        char Connect[NumN][2];// массив соединенных вершин
        for (int j = 0; j < NumN; j++){
            int k=0;
            for (int i = 0; i < NumV; i++){
                if(Arr[i][j]<0)
                    Connect[j][1]=VertNames[i];
                if (Arr[i][j]>0)
                    Connect[j][k++]=VertNames[i];   
             }
        }
        printf("\n");
        for (int i = 0; i < NumN; i++){
	        for (int j = 0; j < 2; j++){
                if(!Connect[i][j]){
                    Connect[i][j]=Connect[i][j-1];
                }
		        printf("%c ",Connect[i][j]);
            }
            printf("\n");
	    }  

       

        FILE *GraphFile=fopen("graph.dot", "w");
        if(GraphFile==NULL){
            printf("Problem with making a file");
        }else{
            printf("File is read\n");
            fprintf(GraphFile,"graph graf {\n");
             for (int i = 0; i < NumV; i++){
                    fprintf(GraphFile,"%c ;\n",VertNames[i]);
            }
            for (int i = 0; i < NumN; i++){
                    fprintf(GraphFile,"%c -- %c ;\n",Connect[i][0],Connect[i][1]);
            }
            fprintf(GraphFile,"}\n");
            fclose(GraphFile);
            system("dot -Tpng graph.dot -o graph.png");
            system("graph.png");
        }
        


        if(NumN>(((NumV-1)*(NumV-2))/2)){
            printf("This graph is connected\n");
        }else{
            printf("This graph is not connected\n");
        }
    }
    // scanf("%c");
 return 0;
}
