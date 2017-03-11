#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

intal* create_intal(){
	intal* i;
	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}
	strcpy(i->s, "+0"); 
	i->n = 1;
	return i;
}

void delete_intal(intal** i){
	if (i == NULL) {
		return;
	}
	if (*i == NULL) {
		return;
	}
	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}
	free(*i);
	*i = NULL;
	return;
}

void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}
	n = strlen(str);
	if( (str[0] == '+') || (str[0] == '-') ) {
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
		i->n=n;
	} else {
		n++; //one extra for the + sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
		i->n=n;
	}
	return;
}

void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}
	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

intal* add_intal(intal* a, intal* b){
	if((a == NULL)&&(b == NULL))
	{
		return NULL;
	}
	else
	{
		if(a == NULL)
		{
			return(b);
		}
		else if(b == NULL)
		{
			return(a);
		}
		else
		{
			int l2=b->n;
			int l1=a->n;
			char* str;
			str=(char*)malloc(l1+1);
			for(int i=0;i<l1;i++)
			{
				str[i]=a->s[i];
			}
			str[l1]='\0';
			char* str1;
			str1=(char*)malloc(l2+1);
			for(int i=0;i<l2;i++)
			{
				str1[i]=b->s[i];
			}
			str1[l2]='\0';
			if(l1>l2)
			{
				char *s1;
				s1=(char*)malloc(l1+1);
				s1[0]=b->s[0];
				for(int i=0;i<l1-l2;i++)
				{
					s1[i+1]='0';
				}
				for(int i=l1-l2;i<l1;i++)
				{
					s1[i+1]=b->s[i-l1+l2+1];
				}
				s1[l1]='\0';
				intal* c=create_intal();
				read_intal(c,s1);
				if(c->s[0]!=a->s[0])
				{
					char* diff;
					diff = (char*)malloc(l1+1);
					diff[l1]='\0';
					for(int i=l1-1;i>0;i--)
					{	
					if(a->s[i]>c->s[i])
					{
					diff[i]=((a->s[i]-'0')-(c->s[i]-'0'))+'0';
					}
					else if(a->s[i]<c->s[i])
					{
					diff[i]=((a->s[i]-'0'+10)-(c->s[i]-'0'))+'0';
					if(a->s[i-1]!='0')
					{
						a->s[i-1]=(a->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(a->s[j]=='0')
						{
							a->s[j]='9';
							j--;
						}
						a->s[j]=(a->s[j]-'0'-1)+'0';
					}
					}
					else if(a->s[i]==c->s[i])
					{
						diff[i]='0';
					}
					}
					diff[0]=a->s[0];
					intal* diffout=create_intal();
					read_intal(diffout,diff);
					for(int i=0;i<l1;i++)
					{
						a->s[i]=str[i];
					}
					return diffout;
				}
				int carry=0;
				char* sum;
				sum = (char*)malloc(l1+2);
				sum[l1+1]='\0';
				for(int i=l1-1;i>0;i--)
				{
					sum[i+1]=(((a->s[i]-'0')+(c->s[i]-'0')+carry)%10)+'0';
					carry=((a->s[i]-'0')+(c->s[i]-'0')+carry)/10;
				}
				if(carry==0)
				{
					char* sum1;
					sum1 = (char*)malloc(l1+1);
					sum1[l1]='\0';
					for(int i=1;i<l1;i++)
					{
						sum1[i]=sum[i+1];
					}
					sum1[0]=a->s[0];
				intal* sumout=create_intal();
				read_intal(sumout,sum1);
				return sumout;
				}
				else
				{
				sum[1]='1';
				sum[0]=a->s[0];
				intal* sumout=create_intal();
				read_intal(sumout,sum);
				return sumout;
				}
			}
			else if(l1<l2)
			{
				char* t;
				t=(char*)malloc(l2+1);
				t[l2]='\0';
				t[0]=a->s[0];
				for(int i=0;i<l2-l1;i++)
				{
					t[i+1]='0';
				}
				for(int i=l2-l1;i<l2;i++)
				{
					t[i+1]=a->s[i+l1-l2+1];
				}
				intal* d=create_intal();
				read_intal(d,t);
				if(d->s[0]!=b->s[0])
				{
					char* diff;
					diff = (char*)malloc(l2+1);
					diff[l2]='\0';
					for(int i=l2-1;i>0;i--)
					{
					if(b->s[i]>d->s[i])
					{
					diff[i]=((b->s[i]-'0')-(d->s[i]-'0'))+'0';
					}
					else if(b->s[i]<d->s[i])
					{
					diff[i]=((b->s[i]-'0'+10)-(d->s[i]-'0'))+'0';
					if(b->s[i-1]!='0')
					{
						b->s[i-1]=(b->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(b->s[j]=='0')
						{
							b->s[j]='9';
							j--;
						}
						b->s[j]=(b->s[j]-'0'-1)+'0';
					}
					}
					else if(b->s[i]==d->s[i])
					{
						diff[i]='0';
					}
					}
					diff[0]=b->s[0];
					intal* diffout=create_intal();
					read_intal(diffout,diff);
					for(int i=0;i<l2;i++)
					{
						b->s[i]=str1[i];
					}
					return diffout;
				}
				int carry=0;
				char* sum;
				sum = (char*)malloc(l2+2);
				sum[l2+1]='\0';
				for(int i=l2-1;i>0;i--)
				{
					sum[i+1]=(((d->s[i]-'0')+(b->s[i]-'0')+carry)%10)+'0';
					carry=((d->s[i]-'0')+(b->s[i]-'0')+carry)/10;
				}
				if(carry==0)
				{
					char* sum1;
					sum1 = (char*)malloc(l2+1);
					sum1[l2]='\0';
					for(int i=1;i<l2;i++)
					{
						sum1[i]=sum[i+1];
					}
					sum1[0]=d->s[0];
				intal* sumout=create_intal();
				read_intal(sumout,sum1);
				return sumout;
				}
				else
				{	
				sum[1]='1';
				sum[0]=d->s[0];
				intal* sumout=create_intal();
				read_intal(sumout,sum);
				return sumout;
				}
			}
			else
			{
				if(a->s[0]!=b->s[0])
				{
					
					char *s1;
					s1=(char*)malloc(l1);
					s1[l1-1]='\0';
					char *s2;
					s2=(char*)malloc(l2);
					s2[l2-1]='\0';
					for(int k=0;k<l1-1;k++)
					{
						s1[k]=a->s[k+1];
					}
					for(int k1=0;k1<l2-1;k1++)
					{
						s2[k1]=b->s[k1+1];
					}
					if(strcmp(s1,s2)>0)
					{				
					char* diff;
					diff=(char*)malloc(l1+1);
					diff[l1]='\0';
					for(int i=l1-1;i>0;i--)
					{
					if(a->s[i]>b->s[i])
					{
					diff[i]=((a->s[i]-'0')-(b->s[i]-'0'))+'0';
					}
					else if(a->s[i]<b->s[i])
					{
					diff[i]=((a->s[i]-'0'+10)-(b->s[i]-'0'))+'0';
					if(a->s[i-1]!='0')
					{
						a->s[i-1]=(a->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(a->s[j]=='0')
						{
							a->s[j]='9';
							j--;
						}
						a->s[j]=(a->s[j]-'0'-1)+'0';
					}
					}
					else if(a->s[i]==b->s[i])
					{
						diff[i]='0';
					}
					}
					diff[0]=a->s[0];
					intal* diffout=create_intal();
					read_intal(diffout,diff);
					for(int i=0;i<l1;i++)
					{
						a->s[i]=str[i];
					}
					return diffout;
					}
					else if(strcmp(s1,s2)<0)
					{				
					char* diff;
					diff=(char*)malloc(l1+1);
					diff[l1]='\0';
					for(int i=l1-1;i>0;i--)
					{
					if(b->s[i]>a->s[i])
					{
					diff[i]=((b->s[i]-'0')-(a->s[i]-'0'))+'0';
					}
					else if(b->s[i]<a->s[i])
					{
					diff[i]=((b->s[i]-'0'+10)-(a->s[i]-'0'))+'0';
					if(b->s[i-1]!='0')
					{
						b->s[i-1]=(b->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(b->s[j]=='0')
						{
							b->s[j]='9';
							j--;
						}
						b->s[j]=(b->s[j]-'0'-1)+'0';
					}
					}
					else if(b->s[i]==a->s[i])
					{
						diff[i]='0';
					}
					}
					if(a->s[0]=='+')
					{
					diff[0]='-';
					}
					else
					{
					diff[0]='+';
					}
					intal* diffout=create_intal();
					read_intal(diffout,diff);
					for(int i=0;i<l2;i++)
					{
						b->s[i]=str1[i];
					}
					return diffout;
					}
					else
					{
					intal* diffout=create_intal();
					diffout->s="0";
					diffout->n=1;
					return diffout;
					}	
				}
				int carry=0;
				char* sum;
				sum=(char*)malloc(l1+2);
				sum[l1+1]='\0';
				for(int i=0;i<l1-1;i++)
				{
					sum[i]='0';
				}
				for(int i=l1-1;i>0;i--)
				{
					sum[i+1]=(((a->s[i]-'0')+(b->s[i]-'0')+carry)%10)+'0';
					carry=((a->s[i]-'0')+(b->s[i]-'0')+carry)/10;
				}
				if(carry==0)
				{
					char *sum1;
					sum1=(char*)malloc(l1+1);
					sum1[l1]='\0';
					for(int i=1;i<l1;i++)
					{
						sum1[i]=sum[i+1];
					}
					sum1[0]=a->s[0];
				intal* sumout=create_intal();
				read_intal(sumout,sum1);
				return sumout;
				}
				else
				{
					sum[1]='1';
					sum[0]=a->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum);
					return sumout;
				}
			}
				
		}		
	
	}
}

intal* subtract_intal(intal* a, intal* b){
	if((a == NULL)&&(b == NULL))
	{
		return NULL;
	}
	else
	{
		if(a == NULL)
		{
			b->s[0]='-';
			return(b);
		}
		else if(b == NULL)
		{
			return(a);
		}
		else
		{
			int l2=b->n;
			int l1=a->n;
			char* str;
			str=(char*)malloc(l1+1);
			str[l1]='\0';
			for(int i=0;i<l1;i++)
			{
				str[i]=a->s[i];
			}
			char* str1;
			str1=(char*)malloc(l2+1);
			str1[l2]='\0';
			for(int i=0;i<l2;i++)
			{
				str1[i]=b->s[i];
			}
			
			if(l1>l2)
			{
				char *s1;
				s1=(char*)malloc(l1+1);
				s1[l1]='\0';
				s1[0]=b->s[0];
				for(int i=0;i<l1-l2;i++)
				{
					s1[i+1]='0';
				}
				for(int i=l1-l2;i<l1;i++)
				{
					s1[i+1]=b->s[i-l1+l2+1];
				}
				intal* c=create_intal();
				read_intal(c,s1);
				if(c->s[0]!=a->s[0])
				{
					int carry=0;
					char* sum;
					sum = (char*)malloc(l1+2);
					sum[l1+1]='\0';
					for(int i=l1-1;i>0;i--)
					{
					sum[i+1]=(((a->s[i]-'0')+(c->s[i]-'0')+carry)%10)+'0';
					carry=((a->s[i]-'0')+(c->s[i]-'0')+carry)/10;
					}
					if(carry==0)
					{
					char* sum1;
					sum1 = (char*)malloc(l1+1);
					sum1[l1]='\0';
					for(int i=1;i<l1;i++)
					{
						sum1[i]=sum[i+1];
					}
					sum1[0]=a->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum1);
					return sumout;
					}
					else
					{
					sum[1]='1';
					sum[0]=a->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum);
					return sumout;
					}
				}
				char* diff;
				diff = (char*)malloc(l1+1);
				diff[l1]='\0';
				for(int i=l1-1;i>0;i--)
				{
					if(a->s[i]>c->s[i])
					{
					diff[i]=((a->s[i]-'0')-(c->s[i]-'0'))+'0';
					}
					else if(a->s[i]<c->s[i])
					{
					diff[i]=((a->s[i]-'0'+10)-(c->s[i]-'0'))+'0';
					if(a->s[i-1]!='0')
					{
						a->s[i-1]=(a->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(a->s[j]=='0')
						{
							a->s[j]='9';
							j--;
						}
						a->s[j]=(a->s[j]-'0'-1)+'0';
					}
					}
					else if(a->s[i]==c->s[i])
					{
						diff[i]='0';
					}
				}
				diff[0]=a->s[0];
				intal* diffout=create_intal();
				read_intal(diffout,diff);
				for(int i=0;i<l1;i++)
				{
					a->s[i]=str[i];
				}
				return diffout;	
			}
			else if(l1<l2)
			{
				char* t;
				t=(char*)malloc(l2+1);
				t[l2]='\0';
				t[0]=a->s[0];
				for(int i=0;i<l2-l1;i++)
				{
					t[i+1]='0';
				}
				for(int i=l2-l1;i<l2;i++)
				{
					t[i+1]=a->s[i+l1-l2+1];
				}
				intal* d=create_intal();
				read_intal(d,t);
				if(d->s[0]!=b->s[0])
				{
					int carry=0;
					char* sum;
					sum = (char*)malloc(l2+2);
					sum[l2+1]='\0';
					for(int i=l2-1;i>0;i--)
					{
					sum[i+1]=(((d->s[i]-'0')+(b->s[i]-'0')+carry)%10)+'0';
					carry=((d->s[i]-'0')+(b->s[i]-'0')+carry)/10;
					}	
					if(carry==0)
					{
					char* sum1;
					sum1 = (char*)malloc(l2+1);
					sum1[l2]='\0';
					for(int i=1;i<l2;i++)
					{
						sum1[i]=sum[i+1];
					}
					sum1[0]=d->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum1);
					return sumout;
					}
					else
					{
					sum[1]='1';	
					sum[0]=d->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum);
					return sumout;
					}
				}
				char* diff;
				diff = (char*)malloc(l2+1);
				diff[l2]='\0';
				for(int i=l2-1;i>0;i--)
				{
					if(b->s[i]>d->s[i])
					{
					diff[i]=((b->s[i]-'0')-(d->s[i]-'0'))+'0';
					}
					else if(b->s[i]<d->s[i])
					{
					diff[i]=((b->s[i]-'0'+10)-(d->s[i]-'0'))+'0';
					if(b->s[i-1]!='0')
					{
						b->s[i-1]=(b->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(b->s[j]=='0')
						{
							b->s[j]='9';
							j--;
						}
						b->s[j]=(b->s[j]-'0'-1)+'0';
					}
					}
					else if(b->s[i]==d->s[i])
					{
						diff[i]='0';
					}
				}
				if(d->s[0]=='+')
				{
				diff[0]='-';
				}
				else
				{
				diff[0]='+';
				}
				intal* diffout=create_intal();
				read_intal(diffout,diff);
				for(int i=0;i<l2;i++)
				{
					b->s[i]=str1[i];
				}
				return diffout;	
			}
			else
			{
				if(a->s[0]!=b->s[0])
				{
					int carry=0;
					char* sum;
					sum=(char*)malloc(l1+2);
					sum[l1+1]='\0';
					for(int i=0;i<l1-1;i++)
					{
					sum[i]='0';
					}
					for(int i=l1-1;i>0;i--)
					{
					sum[i+1]=(((a->s[i]-'0')+(b->s[i]-'0')+carry)%10)+'0';
					carry=((a->s[i]-'0')+(b->s[i]-'0')+carry)/10;
					}
					if(carry==0)
					{
					char *sum1;
					sum1=(char*)malloc(l1+1);
					sum1[l1]='\0';
					for(int i=1;i<l1;i++)
					{
						sum1[i]=sum[i+1];
					}
					sum1[0]=a->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum1);
					return sumout;
					}
					else
					{
					sum[1]='1';
					sum[0]=a->s[0];
					intal* sumout=create_intal();
					read_intal(sumout,sum);
					return sumout;
					}
				}
				if(strcmp(a->s,b->s)>0)
				{				
				char* diff;
				diff=(char*)malloc(l1+1);
				diff[l1]='\0';
				for(int i=l1-1;i>0;i--)
				{
					if(a->s[i]>b->s[i])
					{
					diff[i]=((a->s[i]-'0')-(b->s[i]-'0'))+'0';
					}
					else if(a->s[i]<b->s[i])
					{
					diff[i]=((a->s[i]-'0'+10)-(b->s[i]-'0'))+'0';
					if(a->s[i-1]!='0')
					{
						a->s[i-1]=(a->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(a->s[j]=='0')
						{
							a->s[j]='9';
							j--;
						}
						a->s[j]=(a->s[j]-'0'-1)+'0';
					}
					}
					else if(a->s[i]==b->s[i])
					{
						diff[i]='0';
					}
				}
				diff[0]=a->s[0];
				intal* diffout=create_intal();
				read_intal(diffout,diff);
				for(int i=0;i<l1;i++)
				{
					a->s[i]=str[i];
				}
				return diffout;
				}
				else if(strcmp(a->s,b->s)<0)
				{				
				char* diff;
				diff=(char*)malloc(l1+1);
				diff[l1]='\0';
				for(int i=l1-1;i>0;i--)
				{
					if(b->s[i]>a->s[i])
					{
					diff[i]=((b->s[i]-'0')-(a->s[i]-'0'))+'0';
					}
					else if(b->s[i]<a->s[i])
					{
					diff[i]=((b->s[i]-'0'+10)-(a->s[i]-'0'))+'0';
					if(b->s[i-1]!='0')
					{
						b->s[i-1]=(b->s[i-1]-'0'-1)+'0';
					}
					else
					{
						int j=i-1;
						while(b->s[j]=='0')
						{
							b->s[j]='9';
							j--;
						}
						b->s[j]=(b->s[j]-'0'-1)+'0';
					}
					}
					else if(b->s[i]==a->s[i])
					{
						diff[i]='0';
					}
				}
				if(a->s[0]=='+')
				{
				diff[0]='-';
				}
				else
				{
				diff[0]='+';
				}
				intal* diffout=create_intal();
				read_intal(diffout,diff);
				for(int i=0;i<l2;i++)
				{
					b->s[i]=str1[i];
				}
				return diffout;
				}
				else
				{
					intal* diffout=create_intal();
					diffout->s="0";
					diffout->n=1;
					return diffout;
				}	
			}
		}
	}
}

intal* multiply_intal(intal* a, intal* b){
					int l2=b->n;
					int l1=a->n;
					if((b->s[1]=='0')||(a->s[1]=='0'))
					{
						intal* mulout=create_intal();
						mulout->s="0";
						mulout->n=1;
						return mulout;
					}
					else
					{
						char *s3;
						s3=(char*)malloc(l1);
						s3[l1-1]='\0';
						for(int i=0;i<l1-1;i++)
						{
							s3[i]=a->s[i+1];
						}
						long long int pow=1;
						long long int s4=0;
						for(int k=l2-1;k>0;k--)
						{
							s4=s4+((b->s[k]-'0')*pow);
							pow=pow*10;	
						}
					char* s5;
					s5=(char*)malloc(l2+l1-1);
					s5[l2+l1-2]='\0';
					char* s6;
					s6=(char*)malloc(l2+l1);
					s6[l2+l1-1]='\0';
					for(int i=0;i<l2+l1-1;i++)
					{
						s6[i]='0';
					}
					if(((a->s[0]=='+')&&(b->s[0]=='+'))||((a->s[0]=='-')&&(b->s[0]=='-')))
					{
						s6[0]='+';	
					}
					else
					{
						s6[0]='-';	
					}
					char* s7;
					s7=(char*)malloc(l2+l1);
					s7[l2+l1-1]='\0';
					for(int i=0;i<l2+l1-1;i++)
					{
						s7[i]='0';
					}
					int inc=0;	
					while(s4!=0)
					{
						int carry=0;
						int carry1=0;						
						int x=s4%10;
						for(int i=0;i<l2+l1-2;i++)
						{
							s5[i]='0';
						}
						for(int i=l1-2;i>=0;i--)
						{
							s5[i+l2-1-inc]=(((s3[i]-'0')*x+carry)%10) + '0';
							carry=((s3[i]-'0')*x+carry)/10;	
						}
						if(carry!=0)
						{
							s5[l2-2-inc]=carry+'0';
						}
						for(int i=l2+l1-3;i>l2+l1-3-inc;i--)
						{
							s5[i]='0';
						}
						for(int i=l2+l1-3;i>=0;i--)
						{
							s7[i+1]=(((s6[i+1]-'0')+(s5[i]-'0')+carry1)%10)+'0';
							carry1=((s6[i+1]-'0')+(s5[i]-'0')+carry1)/10;
							s6[i+1]=s7[i+1];
						}
						s4=s4/10;
						inc++;
					}
					if(s6[1]=='0')
					{
					char* s8;
					int g=0;
					while(s6[g+1]=='0')
					{
						g++;
					}
					s8=(char*)malloc(l2+l1-g+1);
					s8[l2+l1-g]='\0';
					s8[0]=s6[0];
					for(int i=1;i<l2+l1-g;i++)
					{
						s8[i]=s6[i+g]; 						
					}
					
					intal* mulout=create_intal();
					read_intal(mulout,s8);	
					return mulout;
					}
					else
					{
					intal* mulout=create_intal();
					read_intal(mulout,s6);	
					return mulout;
					}	
				}
}	

long int divide_intal(intal* a, intal* b){
					int l2=b->n;
					int l1=a->n;
					char *s4;
					char *s3;
					if(b->s[1]=='0')
					{
						printf("Undefined\n");
						return -999;
					}
					else
					{
					if(l1>l2)
					{
						s3=(char*)malloc(l1+1);
						s4=(char*)malloc(l1+1);
						s3[l1]='\0';
						s4[l1]='\0';						
						for(int i=0;i<l1-l2;i++)
						{
							s4[i]='0';
						}
						for(int i=l1-l2;i<l1-1;i++)
						{
						s4[i]=b->s[i-l1+l2+1];
						}
						for(int k1=0;k1<l1;k1++)
						{
						s3[k1]=a->s[k1+1];
						}
					}
					else if(l2>l1)
					{
						s3=(char*)malloc(l2+1);
						s4=(char*)malloc(l2+1);
						s3[l2]='\0';
						s4[l2]='\0';
						for(int k1=0;k1<l2;k1++)
						{
						s4[k1]=b->s[k1+1];
						}
						for(int i=0;i<l2-l1;i++)
						{
							s3[i]='0';
						}
						for(int k=l2-l1;k<l2-1;k++)
						{
						s3[k]=a->s[k+l1-l2+1];
						}
					}
					else
					{
						s3=(char*)malloc(l1+1);
						s4=(char*)malloc(l2+1);
						s3[l1]='\0';
						s4[l2]='\0';
						for(int k1=0;k1<l1;k1++)
						{
						s3[k1]=a->s[k1+1];
						}
						for(int k1=0;k1<l2;k1++)
						{
						s4[k1]=b->s[k1+1];
						}
					}
					if(strcmp(s3,s4)<0)
					{
						int quotient=0;
						if(((a->s[0]=='+')&&(b->s[0]=='+'))||((a->s[0]=='-')&&(b->s[0]=='-')))
					{
						return quotient;
						
					}
					else
					{
						int value=-quotient;
						return value;	
					}
						
					}
					else if(strcmp(s3,s4)==0)
					{
						int quotient=1;
						if(((a->s[0]=='+')&&(b->s[0]=='+'))||((a->s[0]=='-')&&(b->s[0]=='-')))
					{
						return quotient;
						
					}
					else
					{
						int value=-quotient;
						return value;	
					}
						
					}
					else
					{
					int quotient=0;
					while(strcmp(s3,s4)>=0)
					{
						for(int i=l1-2;i>=0;i--)
							{
								if((s3[i]-'0')>(s4[i]-'0'))
								{
								s3[i]=((s3[i]-'0')-(s4[i]-'0'))+'0';
								}
								else if((s3[i]-'0')<(s4[i]-'0'))
								{
								s3[i]=((s3[i]-'0'+10)-(s4[i]-'0'))+'0';
								if(s3[i-1]!='0')
								{
								s3[i-1]=(s3[i-1]-'0'-1)+'0';
								}
								else
								{
								int j=i-1;
								while(s3[j]=='0')
								{
								s3[j]='9';
								j--;
								}
								s3[j]=(s3[j]-'0'-1)+'0';
								}
								}
								else if(s3[i]==s4[i])
								{
								s3[i]='0';
								}					
							}
							quotient++;
					}
					int c;
					int q=quotient;
					while(q!=0)
					{
						q=q/10;
						c++;
					}
					
					if(((a->s[0]=='+')&&(b->s[0]=='+'))||((a->s[0]=='-')&&(b->s[0]=='-')))
					{
						return quotient;
						
					}
					else
					{
						int value=-quotient;
						return value;	
					}
					
			}
		}
}
					
intal* pow_intal(intal* a, intal* b) {
					int l2=b->n;
					int l1=a->n;
					if(b->s[0]=='-')
					{
						printf("undefined\n");
						intal* powout=create_intal();
						read_intal(powout,"-999");
						return powout;
					}
					else if(b->s[1]=='0')
					{
						intal* powout=create_intal();
						read_intal(powout,"+1");
						return powout;
					}
					else
					{
						long long int s4=0;
						long long int pow=1;
						for(int k=l2-1;k>0;k--)
						{
							s4=s4+((b->s[k]-'0')*pow);
							pow=pow*10;	
						}
					char* s5;
					s5=(char*)malloc(200);
					s5="1";
					intal* powed=create_intal();
					read_intal(powed,s5);
					for(int i=0;i<s4;i++)
					{
						powed=multiply_intal(a,powed);		
					}
				return powed;
}
		
}