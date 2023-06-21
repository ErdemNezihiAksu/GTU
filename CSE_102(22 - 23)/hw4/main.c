#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void print_menu()
{
   FILE *f = fopen("menu.txt","r");
   char c;
   int i = 1; // bu değişken yemeklerin sırasını yazdırmak için
   
   printf("Yemek Listesi: \n"); 
   while(fgetc(f) != '\n'); // product ve price yazan satırı atlamak için bir döngü açarız
 
   while(feof(f) == 0)
   {
        printf("%2d. ",i); //yemeğin kaçıncı sırada olduğunu bastırırız.

        while(c != ' ') //yemeğin ismini bastırırız
        {
            c = fgetc(f);
            printf("%c",c);
        }        
        while(c != '\n' && feof(f) == 0) //yemeğin ismini bastırdıktan sonra bir alt satıra geçmek için döngü açarız. \n görene kadar karakter ilerletir.
        {
            c = fgetc(f);
        }
        i++; //öbür yemeğe geçtiğimiz için i yi arttırırız.
        printf("\n");
   }
   printf("\n\n"); // en son tüm listeyi yazdırdıktan sonra okuması rahat olsun diye.
   fclose(f);
}

void write_on_receipt(int servings,int product,int digit_count,float*total,FILE*f, FILE *f2) // receipt.txt üzerine yemeğin servis sayısı, ismi ve fiyatını yazdırır.
{
    float price;
    fseek(f2,0,SEEK_SET);			//dosyayı en baştan okumak için fseek kullanırız
    for(int i = 0; i < product; i++)		//menüde seçilen product ın olduğu satıra gitmek için nested loop kullanırız.
    {
        while(fgetc(f2) != '\n');
    }
    if(servings > 1)				//eğer servis sayısı 1 den falza ise yemeğin adından önce dosyaya servis sayısını yazdırırız ve ardından gelicek boşluk sayısını ona göre ayarlarız.
    {
        fprintf(f,"%d*",servings);
        for(int i = 0; i<15-digit_count;i++)
        fprintf(f,"%c",fgetc(f2));
    }
    else					//eğer servis sayısı 1 ise yemeğin adını yazdırıp belirli sayıda boşluk bırakırız.
    {
        for(int i = 0; i<16;i++)
        fprintf(f,"%c",fgetc(f2));
    }
    fscanf(f2,"%f",&price);			//menu.txt den price ı float cinsinde okuruz
    fprintf(f,"%20.2f\n",price*servings);	//receipt.txt ye price * servings değerini yazdırırız.
    *total += servings*price;			//total fiyatı güncelleriz.
}

void make_receipt()
{
    int product, servings;
    float price,total = 0, discount1= 0, discount2= 0; //discount1=student discount, discount2 = 150tl discount
    char student;				//are you a student? sorusunun cevabını tutmak için bu değişkeni tanımlarız.
    char *str = (char*)malloc(sizeof(char)*80); //zamanı yazdırmak için bir pointer kullanırız.
    time_t t;
    FILE *f, *f2;

    t = time(NULL);
    strftime(str,80,"%d.%m.%Y/%H:%M",localtime(&t));
    f = fopen("receipt.txt","w");
    f2 = fopen("menu.txt","r");
    fprintf(f,"210104004063         %s\n\n",str);
    fprintf(f,"----------------------------------------\n\n");
    fprintf(f,"Product                      Price (TL)\n\n");
    fprintf(f,"----------------------------------------\n\n");

    while(1)
    {
        label1:
        printf("Please choose a product(1-10): ");
        scanf("%d",&product);
        if(product < 1 || product > 10)				//1 ile 10 arasında bir ürün girilmezse yeniden sorar
        {
            printf("Please enter a valid input!!\n");
            goto label1;
        }
        label2:
        printf("How many servings do you want? ");
        scanf("%d",&servings);
        if(servings < 0) 					//servis sayısı 0 dan azsa yeniden sorar
        {
            printf("Please enter a valid input!!\n");
            goto label2;
        }
        if(servings == 0)					//servis 0 ise döngüden çıkar
        break;
	
	int digit_count = 0;
	if(servings > 1)
	{
            int temp = servings;
            while(temp > 0)					//eğer servis 1 den büyük ise receipt te yemeğin adından sonra gelicek boşluk sayısını hesaplamak için servis in basamak sayısını hesaplarız.			
            {
               temp /= 10;
               digit_count++;
            }
	}
        write_on_receipt(servings,product,digit_count,&total,f,f2);
    }
    fprintf(f,"%-10s %25.2f\n","Total:",total);	// total fiyatı txt ye yazdırır.
    label3:
    printf("Are you a student? (Y/N): ");
    scanf(" %c",&student);
    if(student != 'Y' && student != 'N')	//Yes veya No dan farklı bir cevap girilirse yeniden sorar
    {
        printf("Please enter a valid input!!\n");
        goto label3;
    }
    if(student == 'Y')
    {
        discount1 = total*12.5/100;
        fprintf(f,"Student discount: %18.2f\n",discount1*-1);	//öğrenciyse discount ı total fiyat üzerinden uygular ve txt ye "-discount" olarak yazdırır.
    }
    if(total >= 150)
    {
        discount2 = total/10;
        fprintf(f,"150 TL discount: %19.2f\n",discount2*-1);	//total fiyat 150 tl ve üstü ise total fiyat üzerinden bir indirim yapar ve txt ye "-discount" olarak yazdırır.
    }
    total -= discount1 + discount2;
    fprintf(f,"----------------------------------------\n\n");
    fprintf(f,"Price: %29.2f\n",total);				//fiyatın son halini yazdırır.
    fprintf(f,"Price + VAT: %23.2f\n",total + total*18/100);	//fiyat + kdv yi yazdırır.
    fclose(f);
}

void print_recipt()
{
    char c;
    FILE *f= fopen("receipt.txt","r");

    printf("\n\n");
    while(feof(f) == 0)	//dosyanın sonuna gelene kadar tüm karakterleri yazdırır.
    {
        c = fgetc(f);
	if(c != -1)    //EOF karakterini "<?>" biçiminde sona basıyor.Bu karakteri yazmaması için bu koşul kullanılır.
        printf("%c",c);
    }
    fclose(f);
}
int main()
{
    printf("Welcome to our restaurant <3\n\n");
    print_menu(); //menüdeki ürünlerin ismini (yemek listesi) terminale yazdırır.
    make_receipt(); //fişi hazırlar.
    print_recipt(); // fişi ekrana yazdırır.

    printf("\n\n-----Rock,Paper,Scissors-----\n\n");
    int user_select, comp_select;
    char yes_or_no;
    srand(time(NULL)); //random fonksiyonun farklı sayılar üretmesi için

    while(1)
    {
        label:
        printf("Please make a choice!\n1: Rock, 2: Paper, 3: Scissors\n");
        scanf("%d",&user_select);
        if(user_select < 1 || user_select > 3)
        {
            printf("Please enter a valid value!!\n");
            goto label;
        }
        comp_select = rand()%3 + 1; //üretilen sayıyı 1 ile 3 arasında tutarız.

        switch (user_select)	//kullanıcının seçimini yazdırır.
        {
        case 1:
            printf("You chose Rock.");
            break;
        case 2:
            printf("You chose Paper.");
            break;
        case 3:
            printf("You chose Scissors.");
            break;
        default:
            break;
        }
        switch (comp_select)	//bilgisayarın seçimini yazdırır.
        {
        case 1:
            printf("I chose Rock.");
            break;
        case 2:
            printf("I chose Paper.");
            break;
        case 3:
            printf("I chose Scissors.");
            break;
        default:
            break;
        }
        if(user_select == 1) //kullanıcının rock seçtiği durumları düzenler.
        {
            if(comp_select == 1)
            printf("It's a tie!\n");
            else if(comp_select == 2)
            printf("I won!\n");
            else
            printf("You won!\n");
        }
        else if(user_select == 2)	//kullanıcının paper seçtiği durumları düzenler.
        {
            if(comp_select == 2)
            printf("It's a tie!\n");
            else if(comp_select == 1)
            printf("You won!\n");
            else
            printf("I won!\n");
        }
        else				//kullanıcının scissors seçtiği durumları düzenler.
        {
            if(comp_select == 3)
            printf("It's a tie!\n");
            else if(comp_select == 2)
            printf("You won!\n");
            else
            printf("I won!\n");
        }
        label1:
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c",&yes_or_no);
        if(yes_or_no!= 'Y' && yes_or_no != 'N')
        {
            printf("Please enter a valid input!!\n");
            goto label1;
        }
        if(yes_or_no == 'N') // Bir daha oynanmak istenmiyorsa döngüyü kırar.
        break;
    }

}
