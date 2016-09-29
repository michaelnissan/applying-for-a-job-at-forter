#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check_equal(char*first,char*second) //actually checks if one is in the other
{
	int l,i;
	if(strlen(first)<strlen(second))
		l=strlen(first);
	else
		l=strlen(second);
	for(i=0;i<l;i++)
		if(first[i]!=second[i])
			return 0;
	return 1;
}

int miss_spell(char*first,char*second)
{
	//i didn't know how many use cases i need to look for (or what 
	//will be considered as a miss-spell, so i checked the only case
	// that was displayed. only when one letter has changed)
	if(strlen(first)!=strlen(second))
		return 0;
	int i,count=0,l;
	l=strlen(first);
	for(i=0;i<l;i++)
		if(first[i]!=second[i])
			count++;
	if(count==1)
		return 1;
	return 0;
}
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int nick_name(char*first,char*second)
{
	FILE* stream = fopen("nicknames.csv", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        char*line1=(char*)getfield(tmp, 1);
        char temp1[30];
        char temp2[30];
        int i=0,j=0,k=0;
        while(line1[i]!=',')
        	i++;
        i+=2;
        while(line1[i]!=',')
        {
        	temp1[j]=line1[i];
        	i++;
        	j++;
        }
        i+=2;
		while(line1[i]!='\n')
        {
        	temp2[k]=line1[i];
        	k++;
        	++i;
        }
       
        if((check_equal(first,temp1)&&check_equal(second,temp2))||((check_equal(first,temp2)&&check_equal(second,temp1))))
        {
        	return 1;
        }
        free(tmp);
    }
    return 0;

}
int countUniqueNames(char*billFirstName,char*billLastName,char*shipFirstName,char*shipLastName,char*billNameOnCard)
{
	if( ((check_equal(billFirstName,shipFirstName)) ||(nick_name(billFirstName,shipFirstName)) ||(miss_spell(billFirstName,shipFirstName)) )&&((check_equal(billLastName,shipLastName))||(miss_spell(billLastName,shipLastName))) )
		return 1;
	return 2;
}
int main()
{
	printf("%d \n",countUniqueNames("Michele","Egli","Deborah","Egli","Deborah Egli"));
	return 0;
}
