#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

struct details
{
      unsigned long long mobile;
      float wallet;
};

int money_transfer(struct details,float );
void services(struct details);
void pay(struct details);
void recharge(struct details );
void shopping(struct details );

void money(unsigned long long);

void signup(FILE*);
char* login(FILE *);
void info(char [],FILE *);
void read(char []);


int main ()
{
      clock_t start;clock_t end;
      start=clock();
      char ch,id[100];
      int wallet=1000;
      //unsigned long long num;
      system("cls");
      printf("\n");
      printf("%95s","======= Welcome to E-transfer - A Digital Wallet Company =======\n\n");

      time_t curtime;
      time(&curtime);
      char *time=ctime(&curtime);
      printf("\t\t\t\t\t\t\t\t\t\t%s\n\n", time);

      FILE *fp = fopen ("data.csv", "a+");
      if(fp==NULL) printf("Cannot open the file!");
      else
      {
            //fprintf(fp,"Id,Password,Name,ID Card Number,UPI,Card Number,Expire Date,CVV"); // Running the program for 1st time
            printf("%90s","Do you have an account\n\n\t  Press 1 for login");
            printf("%75s","Press 2 for signup\n\n");
            scanf("%c",&ch);

            if(ch=='2')
            {
                  signup(fp);
                  return 0;
            }
            else if(ch=='1')
            {
                  strcpy(id,login(fp));
                  //printf("\n\nId=%s\n",id);
            }

            else
            {
                  printf("Wrong Input\n");
                  return 0;
            }

      }
      fclose(fp);

redo:
      system("cls");
      printf("\n\n\t  Press 1 to avail services");
      printf("%70s","Press 2 to view your details\n\n");
      printf("%68s","Any other key to exit\n\n");

      while(ch=getchar() != '\n');

      scanf("%c",&ch);

      if(ch=='1')
      {
            money(atoi(id));
      }

      else if(ch=='2')
      {
            read(id);
            printf("\n\n\n\n\tPress any key to continue...");
            getch();//holds the screen
            goto redo;
      }

      else
      {
            printf("\n\t\t\t\tTHANK YOU FOR USING OUR SEVICE !! COME BACK AGAIN..\n");
      }

      end=clock();
      double duration=((double)end-start)/CLOCKS_PER_SEC;
      printf("\nTime of execution = %.2f sec\n",duration );
}


void read(char user[])
{
      FILE *fp=fopen("data.csv","r");
      FILE *fptr=fopen("login.txt","r");
      char line[500],*id,first[500],line2[200];

      strcpy(first,fgets(line,500,fp));

      printf("\n%s\n",first);

      while(fgets(line,500,fp)!=NULL)
      {
            strcpy(line2,line);
            id=strtok(line,",");
            if(strcmp(id,user)==0) printf("%s",line2);
      }

      for(int n=0;n<2;n++)
      {
            fgets(line,200,fptr);
            printf("\n\nPerson%d \n\t %6s",n+1,line);
            fseek(fptr,1,1);
      }
      fclose(fp);
      fclose(fptr);
}

void money(unsigned long long number1)
{
      system("cls");
      struct details person1={number1,1000};

      FILE *fptr=fopen("login.txt","a+");

      /*fprintf(fptr,"%llu\t%.2f\n",person1.mobile,person1.wallet);
      fscanf(fptr,"%llu\t%f\n",&person1.mobile,&person1.wallet);*/
      
      printf("\nID of person1 = %llu\t\tAmount in wallet = %.2f\n\n",person1.mobile,person1.wallet);

      services(person1);
      fclose(fptr);
}


void services(struct details person1)
{
      int service;

      //printf("Available balance in your wallet=%f\n",person1.wallet);

      printf("%75s","The following services are provided by us\n\n");
      printf("1.Pay\n2.Mobile recharge\n3.Shopping\n\n");

      printf("Enter the sl no. of the service you want = ");
      scanf("%d",&service);

      switch(service)
      {
            case 1:
                  pay(person1);
                  break;
            case 2:
                  recharge(person1);
                  break;
            case 3:
                  shopping(person1);
                  break;
      }
}


int money_transfer(struct details person1,float amount)
{
      char ch;
      float temp,paid;
      unsigned long long num;
      float n;
      struct details person2={2343,1000};


      printf("\nID of person2 to transfer money = %llu\n",person2.mobile);
      printf("Current Balance in person2 wallet = %.2f\n",person2.wallet);

      FILE *fptr1=fopen("login.txt","a+");




      if (amount < person1.wallet)
      {
            person1.wallet=person1.wallet-amount;
            fseek(fptr1,-ftell(fptr1),SEEK_CUR);

            fprintf(fptr1,"%llu\t%.2f\n",person1.mobile,person1.wallet);
            fscanf(fptr1,"%llu\t%f\n",&person1.mobile,&person1.wallet);

            printf("\n****************************************************************\n");
            printf("\nPerson1 : \n");
            printf("\tID = %llu\tAvailable Balance = %.2f\n",person1.mobile,person1.wallet);

            person2.wallet=person2.wallet+amount;

            fprintf(fptr1,"%llu\t%.2f\n",person2.mobile,person2.wallet);
            fscanf(fptr1,"%llu\t%f\n",&person2.mobile,&person2.wallet);

            printf("\nPerson2 : \n");
            printf("\tID = %llu\tAvailable Balance = %.2f\n",person2.mobile,person2.wallet);
            printf("\n****************************************************************\n");

            printf("\nPayment successful!\n");

            temp=person1.wallet;
            return temp;
      }

      else
      {
            printf("\nYou entered amount greater than your balance\n\n");
            //add money to your wallet (ketan)
            printf("Do you want to continue to pay (y/n) = ");

            while((ch=getchar())!='\n' ) ;
            while((ch=getchar())=='y' )
            {
                  printf("\nEnter the amount to recharge in your wallet = ");
                  scanf("%f",&n);

                  person1.wallet=person1.wallet+n;
                  printf("\nAvailable Balance after recharge = %.2f",person1.wallet);
                  pay(person1);
            }

      }
      amount=0;

      fclose(fptr1);
      //printf("%f\n",person1.wallet );
      temp=person1.wallet;
      return temp;
}


void pay(struct details person1)
{

      float paid,amount;
      char ch;
      printf("\nEnter the amount = ");
      scanf("%f",&amount);
      paid=money_transfer(person1,amount);

      //printf("\nAvailable balance in your wallet=%.2f\n",paid);
}


void recharge(struct details person1)
{
      int choice;
      float paid;

      printf("%65s","The available plans are:\n\n");
      printf("1. Unlimited Local,STD + Roaming calls along with"
      " 1.5GB/day data and 100 SMS/day for 82 days => Rs.499\n");
      printf("2. Unlimited Local,STD + Roaming calls along with"
      " 1GB/day data and 100 SMS/day for 84 days => Rs.399\n");
      printf("3. Unlimited Local,STD + Roaming calls along with"
      " 2GB/day data and 100(Local+National) SMS/day for 28 days => Rs.249\n");
      printf("4. Unlimited Local,STD + Roaming calls along with"
      " 3GB/day data and 100(Local+National) SMS/day for 82 days => Rs.558\n");
      printf("5. 6GB data, validity of unlimited pack "
      "or 7 days validity if not on unlimited pack => Rs.92\n\n");

      scanf("%d",&choice);
      switch (choice)
      {
            case 1:
                  paid=money_transfer(person1,499);
                  printf("Available balance in your wallet=%.2f\n",paid);
                  break;

            case 2:
                  paid=money_transfer(person1,399);
                  printf("Available balance in your wallet=%.2f\n",paid);
                  break;

            case 3:
                  paid=money_transfer(person1,249);
                  printf("Available balance in your wallet=%.2f\n",paid);
                  break;

            case 4:
                  paid=money_transfer(person1,558);
                  printf("Available balance in your wallet=%.2f\n",paid);
                  break;

            case 5:
                  paid=money_transfer(person1,92);
                  printf("Available balance in your wallet=%.2f\n",paid);
                  break;

            default: printf("\nWrong Input!!\n");

      }

}



void shopping(struct details person1)
{
       static int totalCost;
       float paid;
       int i,j,choice,c=1,a[9],cost[9];
       for(i=0;i<9;i++)
       a[i]=0;

       char str[100];
       char items[9][100]={
       "Sandisk 16 GB  ",
       "Logitech Mouse ",
       "Pendrve 16 GB  ",
       "Adidas         ",
       "Nike           ",
       "Leecooper      ",
       "Mi Note 3      ",
       "Nokia 3        ",
       "Samsung        "
       };
       printf("\nPlease Enter Your Name = ");
       scanf("%s",str);
       system("cls");
       printf("\n\t\t\t\tHello %s, Welcome to our Online Shopping.\n\n",str);
       do{
        //C is 1 by default
        if(c==1){
        printf("Enter\n1 - Computer Accessories\n2 - Shoes\n3 - Mobiles\nAny other number to exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
         case 1:
         {
          int accessoriesChoice;
          printf("\nEnter\n1 - Sandisk 16 GB - Rs.355\n2 - Logitech Mouse- Rs.500\n3 - Pendrive 16 GB - Rs.550\nAny other number to exit\n");
          scanf("%d",&accessoriesChoice);
          cost[0]=355;
          cost[1]=500;
          cost[2]=550;
          switch(accessoriesChoice)
          {
           case 1:
           {
            int num;
            printf("\nYou chose Sandisk 16GB with Rs.355.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[0]++;
             totalCost+=355;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           case 2:
           {
            int num;
            printf("\nYou chose Logitech Mouse with Rs.500.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[1]++;
             totalCost+=500;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           case 3:
           {
            int num;
            printf("\nYou chose Pendrive 16GB with Rs.550.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[2]++;
             totalCost+=550;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           default:{
            printf("\nExit from Computer Accesories\n");
            break;
           }
          }
          break;
         }
         case 2:
         {
          int shoesChoice;
          printf("\nEnter\n1 - Adidas - Rs.3550\n2 - Nike - Rs.5000\n3 - Leecooper - Rs.2800\nAny other number to exit\n");
          scanf("%d",&shoesChoice);
          cost[3]=3550;
          cost[4]=5000;
          cost[5]=2800;
          switch(shoesChoice)
          {
           case 1:
           {
            int num;
            printf("\nYou chose Adidas Shoes for Rs.3550.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[3]++;
             totalCost+=3550;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           case 2:
           {
            int num;
            printf("\nYou chose Nike Shoes for Rs.5000.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[4]++;
             totalCost+=5000;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           case 3:
           {
            int num;
            printf("\nYou chose Leecooper Shoes for Rs.2800.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[5]++;
             totalCost+=2800;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           default:{
            printf("\nExit from Shoes Category\n");
            break;
           }
          }
          break;
         }
         case 3:
         {
          int mobileChoice;
          printf("\nEnter\n1 - Mi Note 3 - Rs.11000\n2 - Nokia 3 - Rs.9866\n3 - Samsung - Rs.12800\nAny other number to exit\n");
          scanf("%d",&mobileChoice);
          cost[6]=11000;
          cost[7]=9866;
          cost[8]=12800;
          switch(mobileChoice)
          {
           case 1:
           {
            int num;
            printf("\nYou chose to buy Mi Note 3 for Rs.11000.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[6]++;
             totalCost+=11000;
            }
            printf("Your Cost in Cart = %d\n",totalCost);
            break;
           }
           case 2:
           {
            int num;
            printf("\nYou chose to buy Nokia 3 for Rs.9866.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[7]++;
             totalCost+=9866;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           case 3:
           {
            int num;
            printf("\nYou chose to buy Samsung for Rs.12800.Are you sure to buy.If 'Yes' Enter 1 else any number\n");
            scanf("%d",&num);
            if(num==1)
            {
             a[8]++;
             totalCost+=12800;
            }
            printf("Your Cost in Cart = %d\n\n",totalCost);
            break;
           }
           default:{
            printf("\nExit from Mobile Category\n");
            break;
           }
          }
          break;
         }
         default:
         {
          printf("\nEnter Valid Categories Choice\n");
          break;
         }
        }
        printf("\n****************************************************************\n");
        printf("%s's cart\n",str);
        printf("Id\tItems\t\t\tQuantity\t\t\tCost\n");
        for(i=0;i<9;i++)
        {
         if(a[i]!=0)
         {
          printf("%d\t%s\t\t%d\t\t\t%d\n",i,items[i],a[i],(cost[i]*a[i]));
         }
        }
         printf("\n****************************************************************\n");
        printf("Total Cost\t\t\t\t\t\t%d\n",totalCost);
        printf("\nIf you wish to buy anything more Enter\n1 to Add Item\n2 to Delete Items \nAny other number to Exit\n\n");
        scanf("%d",&c);
       }
        if(c==2)
        {
         int id;
         printf("\nEnter id to delete item\n");
         scanf("%d",&id);
         if(id<9&&id>0){
         totalCost=totalCost-(cost[id]*a[id]);
         a[id]=0;
         }
         else{
          printf("\nEnter Valid id\n");
         }

             printf("\nRevised Items \n");
             printf("Id\tItems\t\t\tQuantity\t\t\tCost\n");
                  for(i=0;i<9;i++)
            {
           if(a[i]!=0)
            {
          printf("%d\t%s\t\t%d\t\t%d\n",i,items[i],a[i],(cost[i]*a[i]));
            }
           }
              printf("\nTotal Cost\t\t\t\t\t\t%d\n",totalCost);
              printf("If you wish to buy anything more Enter\n1 to Add Item\n2 to Delete Items \nAny other number to Exit\n");
           scanf("%d",&c);
        }

       }while(c==1 || c==2);
       printf("\nYour Final Cost is %d\n",totalCost);
       printf("\n\t\t\t\tThanks %s for Choosing Us and Visit us again.\n",str);

       paid=money_transfer(person1,totalCost);
       printf("\nAvailable balance in your wallet=%.2f\n",paid);

}


void signup(FILE *fp)
{
      char userid[30];
	char userpass[30];
	char name[30];
      char cardnum[20],upi[15],card[50],expire[50],cvv[10];
      int s;

      fseek(fp,0,2);
      printf("\n****************************************************************\n");
      printf("\nEnter userid(phone number) = ");
      scanf("%s",userid);
      printf("Enter password = ");
      scanf("%s",userpass);
      printf("Enter your name = ");
      scanf("%s",name);
      printf("\n****************************************************************\n");
      printf("\n\t\t\t You have successfully signed up \n");

      printf("\n\n\t\t\t\tPress any key to continue...");
      getch();//holds the screen;
      system("cls");

      printf("\n****************************************************************\n\n");
      printf("As per RBI guidelines,provide us more details to ensure benefits\n\nSelect an appropriate number below \n");
      printf("1.PAN card\n2.AADHAR CARD\n3.DRIVING LICENCE\n4.PASSPORT\n5.NREGA JOB CARD\n");
      scanf("%d",&s);

      if(s==1)
      {
          printf("\nEnter the 10 digit unique number in the card = ");
          scanf("%s",cardnum);
      }

      else if(s==2)
      {
          printf("\nEnter the 12 digit unique number in the AADHAR CARD = ");
          scanf("%s",cardnum);
      }
      else if(s==3)
      {
          printf("\nEnter the 13 digit unique number in the DRIVING LICENCE = ");
          scanf("%s",cardnum);
      }

      else if(s==4)
      {
          printf("\nEnter the 8 digit unique number in the passport = ");
          scanf("%s",cardnum);
      }
      else if(s==5)
      {
          printf("\nEnter the 18 digit unique number in the NREGA JOB CARD = ");
          scanf("%s",cardnum);
      }
      else
      {
         printf("\nWrong Input\n\n");
         return;
      }

      printf("\nEnter a 3 digit number to set your UPI ID = ");
      scanf("%s",upi);
      printf("\n****************************************************************\n\n");
      printf("\n\t\t\t You have successfully entered your KYC details \n\n");

      printf("\n\n\t\t\t\tPress any key to continue...");
      getch();//holds the screen;
      system("cls");

      printf("\n****************************************************************\n\n");
      printf("We require your bank details!!! \n\n");
      printf("Select any one of the Payment options\n");
      printf("\n1.Debit card\n2.Credit CARD\n");
      scanf("%d",&s);

      if(s==1)
      {
          printf("\nEnter the 16 digit unique number in the debit card = ");
          scanf("%s",card);
          printf("\nEnter the expire date(MM/YY) = ");
          scanf("%s",expire);
          printf("\nEnter the 3 digit CVV number = ");
          scanf("%s",cvv);
      }

      else if(s==2)
      {
            printf("\nEnter the 16 digit unique number in the credit card = ");
            scanf("%s",card);
            printf("\nEnter the expire date(MM/YY) = ");
            scanf("%s",expire);
            printf("\nEnter the 3 digit CVV number = ");
            scanf("%s",cvv);
      }

      else
      {
         printf("Wrong Input\n\n");
         return;
      }

      printf("\n****************************************************************\n\n");
      printf("\n\t\t\t You have successfully entered your card details details \n\n");

                printf("\t\t\t\t\tYour wallet balance = 1000\n\n");

      getch();//holds the screen;

      fprintf(fp,"\n%s,%s,%s,%s,%s,%s,%s,%s",userid,userpass,name,cardnum,upi,card,expire,cvv);


}


char* login(FILE *fp)
{
      char *loginid,*loginpass;
      char line[500];
      char userid[30];
	char userpass[30];
      int a=0,i=0;
      char c=' ';
      //char code[10];
      do
      {
            system("cls");
            printf("\n                            =========================  LOGIN FORM  =========================   \n\n");

            printf(" \n           ENTER USERNAME:-");
            scanf("%s", userid);
            printf(" \n           ENTER PASSWORD:-");
            while(i<10)
            {
                userpass[i]=getch();
                c=userpass[i];
                if(c==13) break;
                else printf("*");
                i++;
            }
            userpass[i]='\0';
            //char code=pword;
            i=0;
            //scanf("%s",&pword);

            fgets(line,500,fp);
            while(fgets(line,500,fp)!=NULL)
            {
                  loginid=strtok(line,",");
                  loginpass=strtok(NULL,",");

                  if(strcmp(userid,loginid)==0 && strcmp(userpass,loginpass)==0)
                  {
                        printf("  \n\n\n  \t\t\t\t     WELCOME TO OUR SYSTEM !!!! LOGIN IS SUCCESSFUL");
                        printf("\n\n\n\n\tPress any key to continue...");
                        getch();//holds the screen
                        return loginid;
                  }
            }

            printf("\n\n                                              SORRY !!!!  LOGIN IS UNSUCCESSFUL \n\n");
            printf("                                                       Available Try = %d\n",2-a);
            a++;
            fseek(fp,0,0);
            getch();//holds the screen

      } while(a<=2);

      if (a>2)
      {
            printf("\nSorry you have entered the wrong username and password for three times!!!");
            getch();

      }
}
