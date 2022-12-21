/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
  for (int i = 0; i < HT_SIZE; i++) {
    (*table)[i] = NULL;
  }
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
  if (table == NULL) {
    return NULL;
  }
  int hash = get_hash(key);
  if ((*table)[hash] != NULL) {
    // try hash index in table
    if (strcmp((*table)[hash]->key, key) == 0) {
      return (*table)[hash];
    }
    // keep looking
    ht_item_t * item_ptr = (*table)[hash]->next; 
    while (item_ptr != NULL) {
      // check if current item is the right one
      if (strcmp(item_ptr->key, key) == 0) {
        return item_ptr;
      }    
      // go to the next item
      item_ptr = item_ptr->next;
    }
  }
  return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
  // search for new item in hash table
  int hash = get_hash(key);
  ht_item_t * tmp_item = ht_search(table, key);
  // if the item already exists, replace his value
  if (tmp_item != NULL) {
    // replace item in hashtable with new value
    tmp_item->key = key;
    tmp_item->value = value; 
  }
  else {
    // we need to create a new item
    ht_item_t * new_item = malloc(sizeof(ht_item_t));
    if (new_item != NULL) {
      new_item->key = key;
      new_item->value = value;
      new_item->next = (*table)[hash];
      (*table)[hash] = new_item;
    }
  }
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
  ht_item_t * item_ptr = ht_search(table, key);
  return &(item_ptr->value);
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {  
  int hash = get_hash(key);
  if ((*table)[hash] == NULL) {
    return;
  }
  ht_item_t * tmp_item = (*table)[hash];
  if (strcmp(((*table)[hash]->key), key) == 0) {
    free((*table)[hash]);
    (*table)[hash] = tmp_item; 
  }
  else {
    while (tmp_item->next != NULL) {
      if (strcmp(tmp_item->next->key, key) == 0) {
        ht_item_t * del_item = tmp_item->next;
        tmp_item->next = tmp_item->next->next;
        free(del_item);
        return;
      }    
      tmp_item = tmp_item->next;
    }  
  }
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
  for (int i = 0; i < HT_SIZE; i++) {
    // pass if there is nothing to delete
    if ((*table)[i] == NULL) {
      continue;
    }
    // when hash table has only one item at index 
    if ((*table)[i]->next == NULL) {
      free((*table)[i]);
      (*table)[i] = NULL;
      continue;
    }
    // else we must delete all of the items
    ht_item_t * tmp_item = (*table)[i]->next;
    while (tmp_item != NULL) {
      ht_item_t * next_item = tmp_item->next;
      free(tmp_item);
      // set to NULL
      tmp_item = NULL;
      // go to next item
      tmp_item = next_item;
    }
    (*table)[i] = NULL;
  }
}
