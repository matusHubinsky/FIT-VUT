/* Matus Hubinsky - xhubin04 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_LENGHT 100
#define MAX_CHARACTER 126
#define MIN_CHARACTER 32


enum levels {LVL1=1, LVL2=2, LVL3=3, LVL4=4};


typedef struct Stats
{
    long sum;
    long min;
    long number;    
    long symbols[MAX_CHARACTER];
} Stats;


typedef struct s_line
{
    char * ptr;
    bool valid;

} S_line;


/* Porovnavanie dvoch poli charov. Ak sa nerovna ich dlzka, nemozu byt rovnake. */ 
bool compareCharArrays(char cArr1[], char cArr2[])
{
    long lenght1 = 0;
    long lenght2 = 0;

    for (int i = 0; cArr1[i] != '\0'; i++) lenght1++; 
    for (int i = 0; cArr2[i] != '\0'; i++) lenght2++;

    if (lenght1 != lenght2) return false;

    for (int i = 0; i < lenght1; i++)
    {
        if (cArr1[i] != cArr2[i]) return false;
    }
    return true;
}


/* Vrati dlzku pola znakov */
int getLength(char line[])
{
    int lenght = 0;
    for (int i = 0; line[i] != '\0'; i++) lenght++;
    return lenght + 1;
}



/* Funkcia nacitava postupne cely riadok, dokedy nanarazy na koniec suboru, riadku, stringu alebo nedosiahne maximalnu dlzku */ 
struct s_line manageInput(S_line s_line, char character, char line[])
{
    int i = 0;
    int ord = character;
    s_line.valid = true;
    while ((i <= MAX_LENGHT) && (character != EOF) && (character != '\n') && (character != '\0'))    
    {
        if ((ord < MIN_CHARACTER) || (ord > MAX_CHARACTER)) s_line.valid = false;     
        line[i] = character;
        i++;
        character = getchar();
        ord = character;
    }
    if (i <= MAX_LENGHT) line[i] = '\0';
    else s_line.valid = false;
    char * cptr = line; 
    s_line.ptr = cptr;
    return s_line;
}


/* Prva podmienka, splni sa ak najde jeden maly a jeden velky znak*/ 
bool firstCondition(char line[], long lenght)
{
    bool small = false; 
    bool big = false;

    for (int i = 0; i < lenght; i++)
    {
        int ord = (int)line[i];
        if ((ord >= 'A') && (ord <= 'Z')) big = true;
        else if ((ord >= 'a') && (ord <= 'z')) small = true;
        
        if ((small == true) && (big == true)) 
        {
            return true;
        }
    }
    return false;    
}


/* Drhua podmienka, je splnena ak najde tolko znakov zo skupin ako udava vstupny parameter*/ 
bool secondCondition(long param, char line[], long lenght)
{
    bool small = false;
    bool big = false;
    bool number = false;
    bool special = false;

    for (int i = 0; i < lenght; i++)
    {
        int ord = (int)line[i];
        if ((ord >= 'A') && (ord <= 'Z')) big = true;
        else if ((ord >= 'a') && (ord <= 'z')) small = true;
        else if ((ord >= '0') && (ord <= '9')) number = true;
        else if ((ord >= ' ') && (ord <= '~')) special = true;
    
        int approved = (int)small + (int)big + (int)number + (int)special;
        if (param <= 4)
        {
            if (approved >= param) return true;  
        } 
        if (param > 4)
        {
            if (approved == 4) return true;  
        } 
    }
    return false; 
}


/* Tretia podmineka, staci raz prejst cele heslo, zapisujem si pocet rovnakych po sebe iducich znakov.
Ak sa znak nezhoduje s predoslym, nastavim pocet podobnych znakov na 1. 
V pripade ze je vstupny parameter dlhsi ako heslo, cast hesla nemozem porovnavat
a podmienka plati. */ 
bool thirdCondition(long param, char line[], long lenght)
{
    int number = 1;
    if (param > lenght) return true;
    for (int i = 1; i < lenght; i++)
    {
        if (line[i-1] == line[i]) number++;
        else if (number >= param) return false; 
        else number = 1;
    }
    return true;
}


/* Plati len ked sa cast hesla dlzky vstupneho parametru rovna inej casti hesla.
V pripade ze je vstupny parameter dlhsi ako heslo, cast hesla nemozem porovnavat
a podmienka plati. */
bool fourthCondition(long param, char line[], long lenght)
{
    bool valid;

    if (param > lenght) return true;

    for (int i = 0; i < lenght; i++)
    {
        for (long j = 0; j < lenght; j++)
        {
            valid = true;
            int k = 0;
            for (long p = 0; p < param; p++)
            {       
                if ((line[i + p] == line[j + p]) && (j != i))
                {   
                    valid = false;
                    k++;
                }
                else
                {
                    valid = true;
                }
            }
            if (valid == false && k == param)
            {
                return false;                    
            } 
        }
    }
    return true;
}


/* Funkcia na kontrolu hesla, heslo musi vzdy splnat vsetky predosle podmienky.
Ak ich nesplna, rovno vratim false. */
bool checkPassword(long level, long param, char line[], long lenght)
{
    bool valid = false;

    if (level >= LVL1)
    {
        if (firstCondition(line, lenght)) valid = true;   
        else return false;
    }
    if (level >= LVL2)
    {
        if (secondCondition(param, line, lenght)) valid = true;
        else return false;
    }
    if (level >= LVL3)
    {
        if (thirdCondition(param, line, lenght)) valid = true;
        else return false;
    }
    if (level == LVL4)
    {
        if (fourthCondition(param, line, lenght)) valid = true;
        else return false;
    }
    return valid;
}


/* Funkcia na priebezne ukladanie statistik hesiel ktore presli testom na podmienky */
struct Stats updateStats(Stats stats, char line[], long lenght)
{
    int ord;
    for (int i = 0; i < lenght; i++)
    {
        ord = (int)line[i];
        if ((stats.symbols[ord] == 0) && (ord >= ' ') && (ord <= '~')) stats.symbols[ord]++;
    }
    if (lenght < stats.min) stats.min = lenght - 1;
    stats.sum += (lenght - 1);
    stats.number++;
    return stats;
}


/* Vynulovanie datovej struktury Stats */
struct Stats prepareStats(Stats stats)
{
    stats.min = MAX_LENGHT;
    stats.number = 0;
    stats.sum = 0;
    for (int i = 0; i < MAX_CHARACTER; i++) stats.symbols[i] = 0;
    return stats;
}


/* Vypis statisik */
void printStats(Stats stats)
{
    long sum_symbols = 0;
    float priemer;
    for (int i = 0; i < MAX_CHARACTER; i++) sum_symbols += stats.symbols[i];
    
    if (sum_symbols != 0)
    {
        priemer = (float)stats.sum / (float)stats.number;
    }
    else 
    {
        priemer = 0.0f;
        stats.min = 0;
    }   
    printf("Statistika:\n");
    printf("Ruznych znaku: %li\n", sum_symbols);
    printf("Minimalni delka: %li\n", stats.min);
    printf("Prumerna delka: %.1f\n", priemer);
}


/* Kontrouje ci sa vo vstupnych parametroch nevyskytuju znaky ine ako cisla */
bool onlyNumbers(char line[])
{
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] < '0' || line[i] > '9') return false;
    }
    return true;
}


/* Kontrola roznych edge casov pri ktorych program nemoze pokracovat */
bool error_handling(long param, long level, char *argv[])
{
    if (onlyNumbers(argv[1]) == false)
    {
        fprintf(stderr, "Level nie je cislo\n");
        return false;                
    }
    if (onlyNumbers(argv[2]) == false)
    {
        fprintf(stderr, "Parameter nie je cislo\n");
        return false;        
    }
    if ((level <= 0) || (level >= 5))
    {
        fprintf(stderr, "Level nie je v rozmedzi 1 a 4\n");
        return false;  
    } 
    if (param == 0)
    {
        fprintf(stderr, "Parameter je rovny 0\n");
        return false;
    } 
    return true;
}


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Malo argumentov\n");
        return 1;        
    }
    Stats stats;
    S_line s_line;
    
    long number = argc;
    char * end;
    long level = strtoul(argv[1], &end, 10);
    long param = strtoul(argv[2], &end, 10);

    if (error_handling(param, level, argv) == false) return 1;

    if (param < 1)
    {
        param = MAX_LENGHT;
    }
    if (number == 4)
    {
        if (compareCharArrays(argv[3], "--stats"))
        {
            stats = prepareStats(stats);
        }
        else
        {
            fprintf(stderr, "Stats ma zly argumen\n");  
            return 1; 
        }
    }
    else if (number > 4) 
    {
        fprintf(stderr, "Vela argumentov \n");  
        return 1;
    }
    char character;
    character = getchar();
    while ((character != EOF))
    {
        char line[MAX_LENGHT];
        s_line= manageInput(s_line, character, line);
        char * lineptr = s_line.ptr;
        if (s_line.valid != false) 
        {
            int lenght = getLength(line);
            stats = updateStats(stats, line, lenght);
            if (checkPassword(level, param, line, lenght)) printf("%s\n", lineptr);
        }
        else
        {
            fprintf(stderr, "Chyba na vstupe\n");
            return 1;        
        }
        character = getchar();
    }
    if (number >= 4) printStats(stats);
    return 0;
}