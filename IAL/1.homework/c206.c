/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/*           Daniel Dolejška, září 2022                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,
**      DLL_Dispose ........ zrušení všech prvků seznamu,
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,
**      DLL_InsertLast ..... vložení prvku na konec seznamu,
**      DLL_First .......... nastavení aktivity na první prvek,
**      DLL_Last ........... nastavení aktivity na poslední prvek,
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,
**      DLL_GetLast ........ vrací hodnotu posledního prvku,
**      DLL_DeleteFirst .... zruší první prvek seznamu,
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,
**      DLL_Next ........... posune aktivitu na další prvek seznamu,
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
 * uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c206.h"

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init( DLList *list ) {
    list -> firstElement = NULL;
    list -> activeElement = NULL;
    list -> lastElement = NULL;
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose( DLList *list ) {
    DLLElementPtr currentElementptr;
    // načítam prvý prvok
    currentElementptr = list -> firstElement;
    while (currentElementptr != NULL) {
        // a vymazávam všetky prvky, dokedy sa nedostanem na koniec
        DLLElementPtr tmpElementptr = currentElementptr -> nextElement;
        free(currentElementptr);
        currentElementptr = tmpElementptr;
    }
    // prvý, aktívny a posledný prvok nastavím do rovnakého stavu ako po inicializácií
    list -> firstElement = NULL;
    list -> activeElement = NULL;
    list -> lastElement = NULL;
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst( DLList *list, int data ) {
    DLLElementPtr newElementptr = malloc(sizeof(struct DLLElement));
    // kontrola či alikoácia prebehla úspešne
    if (newElementptr == NULL) {
        DLL_Error();
        return;
    }
    newElementptr -> data = data;
    newElementptr -> nextElement = list -> firstElement;
    newElementptr -> previousElement = NULL;
    // overime či zoznam má už prvý prvok
    if (list -> firstElement != NULL) {
        // ľavý sused posledného prvku bude nový prvok
        list -> firstElement -> previousElement = newElementptr;    
    }
    else {
        // nový prvok bude zároveň aj posledný 
        list -> lastElement = newElementptr;        
    }
    // na miesto prvého prvku sa dá nový prvok
    list -> firstElement = newElementptr;
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast( DLList *list, int data ) {
    DLLElementPtr newElementptr = malloc(sizeof(struct DLLElement));
    // kontrola či alikoácia prebehla úspešne
    if (newElementptr == NULL) {
        DLL_Error();
        return;
    }
    newElementptr -> data = data;
    newElementptr -> nextElement = NULL;
    newElementptr -> previousElement = list -> lastElement;
    // ak list má posledný prvok
    if (list -> lastElement != NULL) {
        // pravý sused posledného prvku bude nový prvok
        list -> lastElement -> nextElement = newElementptr;
    }
    else {
        // nový prvok je zároveň aj posledný
        list -> firstElement = newElementptr;
    }
    // na miesto posledného prvku sa dá prvý prvok
    list -> lastElement = newElementptr;
}

/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First( DLList *list ) {
    list -> activeElement = list -> firstElement;
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last( DLList *list ) {
	list -> activeElement = list -> lastElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst( DLList *list, int *dataPtr ) {
    // konrola existencie prvého prvku
    if (list -> firstElement == NULL) {
        DLL_Error();
        return;
    }
    *dataPtr = list -> firstElement -> data;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast( DLList *list, int *dataPtr ) {
    // kontrola existencie posledného prvku
    if (list -> lastElement == NULL) {
        DLL_Error();
        return;
    }
    *dataPtr = list -> lastElement -> data;
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteFirst( DLList *list ) {
    // kontrola existencie prvého prvku
    if (list -> firstElement == NULL) {
        return;
    }
    if (list -> activeElement == list -> firstElement) {
        list -> activeElement = NULL;
    }
    DLLElementPtr tmpElementptr = list -> firstElement;
    if (list -> firstElement == list -> lastElement) {
        list -> firstElement = NULL;
        list -> lastElement = NULL;
    }
    else {
        list -> firstElement = list -> firstElement -> nextElement;
        list -> firstElement -> previousElement = NULL;
    }
    free(tmpElementptr);
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast( DLList *list ) {
    // kontrola existencie posledného prvku
    if (list -> lastElement == NULL) {
        return;
    }
    if (list -> activeElement == list -> lastElement) {
        list -> activeElement = NULL;
    }
    DLLElementPtr tmpElementptr = list -> lastElement;
    if (list -> firstElement == list -> lastElement) {
        list -> firstElement = NULL;
        list -> lastElement = NULL;
    }
    else {
        list -> lastElement = list -> lastElement -> previousElement;
        list -> lastElement -> nextElement = NULL;
    }
    free(tmpElementptr);
}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter( DLList *list ) {
    // kontrola či list nieje aktǘine alebo či posledný prvok je zároveň aktívnym
    if (list -> activeElement == NULL || list -> lastElement == list -> activeElement) {
        return;
    }
    if (list -> activeElement -> nextElement != NULL) {
        DLLElementPtr tmpElementptr;
        tmpElementptr = list -> activeElement -> nextElement;
        // zrušenie posledného
        list -> activeElement -> nextElement = tmpElementptr -> nextElement;
        if (tmpElementptr == list -> lastElement) {
            // potrebujeme zrušiť posledný, posledný bude aktívny
            list -> lastElement = list -> activeElement;
        }
        else {
            // prvku za zrušeným, nastavíme predchádzajúci na aktívny prvok
            tmpElementptr -> nextElement -> previousElement = list -> activeElement;
        }
        free(tmpElementptr);
    }
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore( DLList *list ) {
     // kontrola či list nieje aktǘine alebo či prvý  prvok je zároveň aktívnym
    if (list -> activeElement == NULL || list -> firstElement == list -> activeElement) {
        return;
    }    
    if (list -> activeElement -> previousElement != NULL) {
        DLLElementPtr tmpElementptr; 
        tmpElementptr = list -> activeElement -> previousElement;
        // zrušenie posledného, nahradenie za prvok za posledným
        list -> activeElement -> previousElement = tmpElementptr -> previousElement;
        if (tmpElementptr == list -> firstElement) {
            // potrebujeme zrušiť prvý, prvý bude aktívny
            list -> firstElement = list -> activeElement;
        }
        else {
            // prvku za zrušeným, nastavíme predchádzajúci na aktívny prvok
            tmpElementptr -> previousElement -> nextElement = list -> activeElement;
        }   
        free(tmpElementptr);
    }
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter( DLList *list, int data ) {
    // pokiaľ zoznam nieje aktívny, nič sa nedeje
    if (list -> activeElement == NULL) {
        return;
    }
    DLLElementPtr newElementptr = malloc(sizeof(struct DLLElement));
    // kontrola allokacie pamäti
    if (newElementptr == NULL) {
        DLL_Error();
        return;
    }
    newElementptr -> data = data;
    // nasledujuci prvok bude prvok za aktívnym prvkom
    newElementptr -> nextElement = list -> activeElement -> nextElement;
    // predchádzajúci prvok je aktívny prvok
    newElementptr -> previousElement = list -> activeElement;
    // za aktívnym prvkom je teraz nový prvok
    list -> activeElement -> nextElement = newElementptr; 
    
    // ak je aktívny prvok zároveň aj posledným prvkom 
    if (list -> activeElement == list -> lastElement) {
        // prvý prvok bude zároveň aj posledným
        list -> lastElement = newElementptr;
    }
    else {
        // ľavý sused pravého suseda nového prvku musí byť nový prvok
        newElementptr -> nextElement -> previousElement = newElementptr;
    }
}

/**
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore( DLList *list, int data ) {
    // pokiaľ zoznam nieje aktívny, nič sa nedeje
    if (list -> activeElement == NULL) {
        return;
    }   
    // kontrola alokácie pamäti
    DLLElementPtr newElementptr = malloc(sizeof(struct DLLElement));
    if (newElementptr == NULL) {
        DLL_Error();
        return;
    }
    newElementptr -> data = data;
    // pravý sused nového prvku bude aktívny prvok
    newElementptr -> nextElement = list -> activeElement;
    // ľavý sused nového prvku bude ľavým susedom aktívneho prvku
    newElementptr -> previousElement = list -> activeElement -> previousElement;
    // pred aktívny prvok príde nový prvok
    list -> activeElement -> previousElement = newElementptr; 
    // ak je aktívny prvok prvým prvokm
    if (list -> activeElement == list -> firstElement) {
        // nový prvok je prvým prvkom zoznamu
        list -> firstElement = newElementptr;
    }
    else {
        // 
        newElementptr -> previousElement -> nextElement = newElementptr;
    }
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue( DLList *list, int *dataPtr ) {
    // kontrola aktivity zoznamu
    if (list -> activeElement == NULL) {
        DLL_Error();
        return;
    }
    *dataPtr = list -> activeElement -> data;
}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue( DLList *list, int data ) {
    // kontrola aktivity zoznamu
    if (list -> activeElement == NULL) {
        return;
    }
    list -> activeElement -> data = data;
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Next( DLList *list ) {
    if (list -> activeElement == NULL) {
        return;
    }
    list -> activeElement = list -> activeElement -> nextElement;        
}


/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous( DLList *list ) {
    // kontrola aktivity zoznamu
    if (list -> activeElement == NULL) {
        return;
    }
    list -> activeElement = list -> activeElement -> previousElement;   
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive( DLList *list ) {
    return list -> activeElement != NULL;
}

/* Konec c206.c */
