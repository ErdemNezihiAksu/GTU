#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_WORD_SIZE 12
#define MAX_WORD_COUNT 100
#define VECTOR_LENGTH 200
#define THRESHOLD 25

int ft_strlen(char *str) //stringin uzunluğunu bulmak için kulllanırız.
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_strcpy(char *dest, const char *src) //bir stringi başka bir string e kopyalamak için kullanırız.
{
    char *dest_ptr = dest;
    const char *src_ptr = src;

    while (*src_ptr != '\0')
    {
        *dest_ptr = *src_ptr;
        dest_ptr++;
        src_ptr++;
    }
    *dest_ptr = '\0';
}

int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE])//dictionary den kelimeleri okuyup dict arrayine koyar, okunan kelime sayısını döndürür.
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("Dictionary file could not opend!!\n");
        return -1;
    }
    char buffer[5000], p[12];
    int i = 0;

    fgets(buffer, sizeof(buffer), f); // ilk satırı atlayıp vectörlerin yazdığı kısma geliriz.
    while (fgets(buffer, sizeof(buffer), f) != NULL)//dosyanın sonuna kadar satır satır okuruz.
    {
        sscanf(buffer, "%[^ ]", dict[i]); //ilk satırın ilk kelmesini, dict arrayinin sıradaki indexine koyarız.
        if (ft_strlen(dict[i]) < MAX_WORD_SIZE)
            i++; //okunan kelime sayısını bir arttırırız.
    }
    dict[i][0] = '-'; //arrayin sonuna sentinal value yı koyarız.
    fclose(f);
    return i;
}

int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE], int occurances[])//input.txt deki her bir kelimeyi, kelime birden fala geçse de yalnızca bir tanesini arra ye koyar ve kaç kere geçtiğini occurances arrayinin aynı indexinde tutar, array e konulan kelime sayısını döndürür.
{
    char c;
    char word[MAX_WORD_SIZE], ignore[100][MAX_WORD_SIZE];
    int in_word = 0;
    int num_word = 0, ignore_word = 0;
    int num_letter = 0;
    int flag, flag1 = 0;
    FILE *f = fopen(ignore_file, "r");
    FILE *input = fopen(text_file, "r");

    if (input == NULL || f == NULL)
    {
        printf("Error occured while opening file!!\n");
        return -1;
    }
    while (fscanf(f, "%s", ignore[ignore_word]) != EOF) //ignore.txt teki kelimeleri bir ignore arrayinde tutarız.
    {
        ignore_word++;
    }
    do
    {
        c = fgetc(input);
        if (isspace(c) || ispunct(c) || c == -1)//okunan karakter eğer bir noktalama işareti,whitespapce veya EOF ise koşula girer.
        {
            flag = 0; // bu flag okunan kelimenin ignore.txt de olup olmadığını kontrol edicek.
            if (in_word) // eğer ilk koşula girilmeden önce bir kelimenin içindeysek bu koşula girer.
            {
                word[num_letter] = '\0'; //kelimeyi koyduğumuz arrayin son indexi /0 yapılır.
                if (flag1 == 0) // bu flag kelimenin 12 harf ten daha fazla olup olmadığını kontrol ediyor,eğer değilse koşula girer.
                {
                    for (int i = 0; i < ignore_word; i++)
                    {
                        if (strcmp(ignore[i], word) == 0) // kelimenin ignore.txt de olup olmadığı kontrol edilir. Eğer varsa flag 1 yapılır.
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)//eğer okunan kelime ignore.txt de yoksa bu koşula girilir.
                    {
                        for (int i = 0; i < num_word; i++)
                        {
                            if (strcmp(words[i], word) == 0) //şuana kadar okunan kelimeler tek tek gözden geçirilir, son kelime kaç txt de geçtiyse bu sayı occurances arrayinde tutulur.
                            {
                                flag = 1; //eğer okunan kelime daha önce txt de geçtiyse flag = 1 yapılır.
                                occurances[i]++;
                                break;
                            }
                        }
                        if (flag == 0) // eğer okunan kelime txt de ilk defa geçiyorsa bu koşula girer.
                        {
                            for (int i = 0; i <= num_letter; i++)
                            {
                                words[num_word][i] = word[i]; //okunan kelime words arrayine kopyalanır.
                            }
                            occurances[num_word]++; //okunan kelimenin occurances değeri 1 arttırılır.
                            num_word++; // okunan kelime sayısı arttırılır.
                        }
                    }
                }
                in_word = 0; //kelimenin dışına çıkılır.
                num_letter = 0;
                flag1 = 0;
                memset(word, 0, MAX_WORD_SIZE);
            }
        }
        else
        {
            in_word = 1; // kelimenin içine girilir.
            if (num_letter < MAX_WORD_SIZE - 1)
            {
                word[num_letter++] = c; //kelimenin harf sayısı 12 den küçük olduğu müddetçe kelime okunur.
            }
            else
                flag1 = 1; // eğer harf sayıs 12 yi geçerse flag1 =  1 yapılır.
        }
    } while (c != EOF);
    words[num_word][0] = '-'; //words ün sonuna sentinal value koyunur.
    fclose(f);
    fclose(input);
    return num_word;
}

double dissimilarity(const char *w1, const char *w2, const char dict[][MAX_WORD_SIZE], float threshold)//iki kelimenin vektör uzaklığını hesaplar, eğer threshold a eşit veya küçükse döndürür.
{
    int flag1 = 0, flag2 = 0, num_word = 0, i;
    FILE *f;
    double vector1[VECTOR_LENGTH] = {0}, vector2[VECTOR_LENGTH] = {0};
    double dissimilarity = 0;
    char word[MAX_WORD_SIZE], buffer[5000];

    while (strcmp(dict[num_word], "-") != 0) //bu while iki kelimeninde dictionary de geçip geçmediğini kontrol eder.
    {
        if (strcmp(dict[num_word], w1) == 0)
        {
            flag1 = 1;
        }
        else if (strcmp(dict[num_word], w2) == 0)
        {
            flag2 = 1;
        }
        if (flag1 == 1 && flag2 == 1)
            break;
        num_word++;
    }
    if (strcmp(dict[num_word], "-") == 0) //eğer kelimelerden en az biri dicitonary de geçmiyorsa -1 döndürür.
    {
        return -1;
    }
    f = fopen("dictionary.txt", "r");
    flag1 = 0;
    flag2 = 0;
    char *token;
    fgets(buffer, sizeof(buffer), f);//ilk satır atlanıp vectörlerin yazdığı kısma gelinir.
    while (fgets(buffer, sizeof(buffer), f) != NULL) // tüm vectörler okunana kadar devam eder.
    {
        token = buffer; //token pointer ı okunan satırın başını işaret eder.
        sscanf(token, "%s", word); //ilk kelime okunur
        while (*token != ' ') // token pointerı ilk vectör değerini gösterene kadar ilerletilir.
            token++;
        token++;
        if (strcmp(word, w1) == 0) // eğer okunan kelime w1 ise koşula girilir.
        {
            i = 0;
            while (*token != '\n' && *token != '\0')//token satır sonunu işaret edene kadar devam eder.
            {
                sscanf(token, "%lf", &vector1[i++]); // her bir vektör okunup vector1 e konur ve token pointer ı bir sonraki sayıyı işaret edene kadar ilerletilir.
                while (*token != ' ' && *token != '\n' && *token != '\0')
                    token++;
                if (*token == ' ')
                    token++;
            }
            flag1 = 1;
        }
        else if (strcmp(word, w2) == 0)//aynısı w2 için yapılır.
        {
            i = 0;
            while (*token != '\n' && *token != '\0')
            {
                sscanf(token, "%lf", &vector2[i++]);
                while (*token != ' ' && *token != '\n' && *token != '\0')
                    token++;
                if (*token == ' ')
                    token++;
            }
            flag2 = 1;
        }
        if (flag1 == 1 && flag2 == 1) // eğer aranan iki sayıda bulunup okunduysa döngüden çıkılır.
            break;
    }
    for (int j = 0; j < i; j++) //vektör uzaklığı hesaplanır.
    {
        dissimilarity += pow(vector1[j] - vector2[j], 2);
    }
    dissimilarity = sqrt(dissimilarity);
    memset(vector1, 0, VECTOR_LENGTH);
    memset(vector2, 0, VECTOR_LENGTH);
    if (dissimilarity <= threshold) //eğer uzaklık eşik değerie eşit veya küçükse döndürülür, değilse -1 döner.
        return dissimilarity;
    else
        return -1;
}

int histogram(const char words[][MAX_WORD_SIZE], char user_words[][MAX_WORD_SIZE], const int occurances[], const char dict[][MAX_WORD_SIZE], char hist[][MAX_WORD_SIZE + 25])
{
    int i = 0, j, scale = 1, prev_scale = 1, flag = 0, is_scale_changed = 0;
    double similarity = 0;

    while (user_words[i][0] != '-') //kullanıcın girdiği kelimelerin hepsi okunana kadar devam eder.
    {
    label:
        j = 0;
        if (flag == -1) //flag -1 ise girilen kelimenin kendisi ve en yakını txt de geçmiyordur. Bunu belirtmek için histogram arrayinin kelimeyle aynı indexine / işaretini koyarız.
        {
            hist[i][0] = '/';
            flag = 0;
        }
        else
        {
            while (words[j][0] != '-')//girilen kelime txt deki tüm kelimeler ile karşılaştırılır.
            {
                if (strcmp(words[j], user_words[i]) == 0) // eğer txt de o kelime bulunduysa koşula girer.
                {
                    if ((occurances[j] - 1) / 20 + 1 > scale)//kelimenin kaç kere txt de geçtiği bilgisi occurances arrayindedir.Bu bilgi kullanılarak scale hesaplanr.
                    {
                        prev_scale = scale;  //eğer hesaplanan scale mevcut scale dan büyükse koşula girer ve mevcut scale pre_scale olur.
                        scale = (occurances[j] - 1) / 20 + 1; //scale ise yeni scale olur.
                        is_scale_changed = 1; //scale ın değişltiği belirtilir.
                    }
                    if (flag == 0)//flag 0 ise girilen kelime txt de geçiyor demektir.
                    {
                        for (int x = 0; x < occurances[j] / scale; x++)
                        {
                            hist[i][x] = '*'; //hist arrayinin kelimeyi belirten indexine, scale göz önüne alınarak kaç kere geçtiyse okadar * konur
                        }
                    }
                    else if (flag == 1)//flag 1 ise kelime txt de geçmiyordur ama yakın kelimesi geçiyordur.
                    {
                        for (int x = 0; x < occurances[j] / scale; x++)
                        {
                            hist[i][x] = '+'; //hist arrayinin kelimeyi belirten indexine, scale göz önüne alınarak kaç kere geçtiyse okadar + konur
                        }
                        flag = 0;
                    }
                    if (is_scale_changed == 1) //eğer scale girilen kelimeyle değiştiyse koşula girer.
                    {
                        for (int x = 0; x < i; x++) //hist arrayinde şuanki kelimeye kadar bütün kelimelerin üstünden geçilir.
                        {
                            if (hist[x][0] != '/')//eğer yukarda belirtildiği üzere histin bir indexi '/' değilse koşula girer.
                            {
                                int len = ft_strlen(hist[x]) * prev_scale; //histin şuanki indexini * sayısıyla eski scale çarpılarak kelimenin kaç defa geçtiği hesaplanır.
                                hist[x][len / scale] = '\0'; //hist in kelimeyi belirten indexi yeni scale a göre ayarlanır.
                            }
                        }
                        is_scale_changed = 0;
                    }
                    break;
                }
                j++;
            }
        }
        if (words[j][0] == '-') //eğer girilen kelime txt de yoksa bu koşula girer.
        {
            int x = 0;
            char word[MAX_WORD_SIZE];//bu değişken girilen kelimeye en yakın kelimeyi tutacak
            double temp;
            while (dict[x][0] != '-')//yakın bir kelime aramak için dict teki kelimeler aranır.
            {
                if (strcmp(user_words[i], dict[x]) != 0)//eğer dict te bakılan kelime ile girilen kelime farklı ise koşula girer.
                {
                    temp = exp(-1 * (dissimilarity(user_words[i], dict[x], dict, THRESHOLD)));//dissimilarity fonksiyonun inverse fonksiyonu ile bir similarity değeri hesaplanır.
                    if (temp > similarity && temp != M_E) //eğer hesaplanan değer kelimeye şu ana kadar bulunan en yakın değer ise ve o değer 'e' sayısına eşit değil ise(bunun mantığı eğer girilen kelime dict te yazmıyorsa dissimilarity -1 döndürür ve bunun inverse fonksiyonuda e döndürür.) koşula girer.
                    {
                        similarity = temp; //similarity yeni hesaplanan değer olur.
                        ft_strcpy(word, dict[x]);// bulunan kelime word e kopyalanır.
                        flag = 1; //yakın bir kelimenin bulunduğunu belirtmek için flag 1 yapılır.
                    }
                }
                x++;
            }
            if (similarity == 0)//eğer yakın bir kelime bulunamazsa flag -1 yapılır.
                flag = -1;
            else
            {
                int a = 0;
                while(words[a][0] != '-' && strcmp(words[a],word) != 0)//bulunan yakın kelime txt de geçiyormu diye bakılır.
                {
                    a++;
                }
                if(words[a][0] == '-')//eğer geçmiyorsa flag -1 yapılır
                    flag = -1;
                else
                    ft_strcpy(user_words[i], word);//eğer geçiyorsa kullanıcın girdiği kelimelerin tutlduğu arraydeki o index, yakın kelime yapılır ve flag 1 de kalır.
            }
            similarity = 0;
            goto label; //kelimeyi histogram a çevirmek için başa dönülür.
        }
        i++;
    }
    hist[i][0] = '-';//array sentinal value ile sonlandırılır.

    if (scale > 1) //histogram bastırılır.
    {
        printf("Scale: %d", scale);
    }
    i = 0;
    while (user_words[i][0] != '-')
    {
        int space_count = ft_strlen(user_words[i]);
        printf("\n\"%s\"", user_words[i]);
        for (int i = 0; i < 16 - space_count; i++)
            printf(" ");
        if (hist[i][0] == '/')
            printf("%s", "NO MATCHES");
        else
            printf("%s", hist[i]);
        i++;
    }
    printf("\n");
    return scale; // scale döndürülür.
}

int main(int argc, char *argv[])
{
    char dict[5000][MAX_WORD_SIZE] = {0};
    char words[15000][MAX_WORD_SIZE] = {0};
    char hist[MAX_WORD_COUNT + 1][MAX_WORD_SIZE + 25] = {0};
    char user_words[MAX_WORD_COUNT + 1][MAX_WORD_SIZE] = {0};
    int occurances[15000] = {0};
    int text_count = 0, dict_count = 0, i = 0;

    text_count = read_text("input.txt", "ignore.txt", words, occurances); //input ve dictionary okunur.
    dict_count = read_dict("dictionary.txt", dict);

    printf("Enter word(s): ");
    do
    {
        scanf("%s", user_words[i]);
        if (i == MAX_WORD_COUNT - 1) //girilen kelimeler max_word_count u geçmemek kaydıyla array a alınır.
        {
            while (getchar() != '\n')
                ;
            i++;
            break;
        }
        i++;
    } while (getchar() != '\n');
    user_words[i][0] = '-';

    i = 0;
    if (user_words[1][0] == '-') //eğer yalnızca bir kelime girildiyse koşula girer.
    {
        int flag = 0;
        while (i < text_count)
        {
            if (strcmp(user_words[0], words[i]) == 0)//inputtaki kelimeler ile girilen kelime karşılaştırılır.
            {
                flag = 1; //eğer bir match bulunursa flag 1 yapılır.
                break;
            }
            i++;
        }
        if (flag == 1) //eğer kelime bulunduysa kaç kere geçtiği ekrana bastırılır.
        {
            printf("\"%s\" appers in \"input.txt\" %d times.\n", user_words[0], occurances[i]);
        }
        else //eğer kelime txt de geçmiyorsa...
        {
            char similar[MAX_WORD_SIZE] = {0};
            double similarity = 0;
            double temp;
            i = 0;
            while (dict[i][0] != '-') //yakın bir kelime bulmak için dict e bakılır.
            {
                if (strcmp(user_words[0], dict[i]) != 0)//eğer dict te okunan kelime ile girilen kelime farklı ise vectör hesaplaması yapar.
                {
                    temp = exp(-1 * (dissimilarity(user_words[0], dict[i], dict, THRESHOLD)));
                    if (temp > similarity && temp != M_E) //histogram fonksiyonunun aynısı.
                    {
                        similarity = temp;
                        ft_strcpy(similar, dict[i]);
                    }
                }
                i++;
            }
            if (similar[0] != '\0') //eğer yakın bir kelime bulunursa koşula girer.
            {
                i = 0;
                while (i < text_count)
                {
                    if (strcmp(similar, words[i]) == 0) //bulunan yakın kelime txt de geçiyormu diye bakılır.
                    {
                        break;
                    }
                    i++;
                }
                if (i != text_count) // eğer geçiyorsa kaç kere geçtiği yazdırılır.
                {
                    printf("\"%s\" does not appear in \"input.txt\" but \"%s\" appears %d times\n", user_words[0], similar, occurances[i]);
                }
                else // eğer geçmiyorsa kelimenin txt de geçmediği yazdırılır.
                {
                    printf("\"%s\" does not appear in \"input.txt\"\n", user_words[0]);
                }
            }
            else // eğer yakın bir kelime bulunamazsa da kelimenin txt de geçmediği yazdırılır.
            {
                printf("\"%s\" does not appear in \"input.txt\"\n", user_words[0]);
            }
        }
    }
    else // eğer birden fazla kelime girildiyse histogram çizdirmeye gidilir.
    {
        histogram(words, user_words, occurances, dict, hist);
    }
}