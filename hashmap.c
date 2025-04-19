#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {


}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

    size_t old_capacidad = map->capacity;
    Pair** old_buckets = map->buckets;

    size_t capacidad_nueva = old_capacidad * 2;
    map->buckets = (Pair**)calloc(capacidad_nueva,sizeof(Pair*));
    map->capacity = capacidad_nueva;
    map->size = 0;
    map->current = -1;

    for (size_t i = 0; i < old_capacidad; i++)
    {
        if(old_buckets[i] != NULL && old_buckets[i]->key != NULL)
        {
            insertMap(map,old_buckets[i]->key,old_buckets[i]->value);
        }
    }

    free(old_buckets);
}


HashMap * createMap(long capacity) {
    HashMap* mapa = (HashMap*)malloc(sizeof(HashMap));
    mapa->buckets = (Pair**)calloc(capacity, sizeof(Pair*));

    mapa->size = 0;
    mapa->capacity = capacity;
    mapa->current = -1;
    
    return mapa;
}

void eraseMap(HashMap * map,  char * key) { 
    if(map == NULL || key == NULL) return;  
    
    size_t posicion = hash(key,map->capacity);

    for (size_t i = posicion ; i < map->capacity; i++)
    {
        long pos = i % map->capacity;

        if (map->buckets[pos] == NULL)
            return;
        
        if (map->buckets[pos]->key != NULL && is_equal(map->buckets[pos]->key,key))
        {
            map->buckets[pos]->key = NULL;
            map->size --;
            return;
        }
    }
    


}

Pair * searchMap(HashMap * map,  char * key) {   
    size_t poscision = hash(key,map->capacity);

    for (size_t k = poscision; k < map->capacity;k++)
    {
        size_t pos = k % map->capacity;
        if (map->buckets[pos] == NULL)
        {
            return NULL;
        }
        if(map->buckets[pos] != NULL && is_equal(map->buckets[pos]->key,key))
        {
            map->current = pos;
            return map->buckets[pos];
        }
        
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {
    if (map == NULL) return NULL;

    for (size_t i = 0; i < map->capacity; i++)
    {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL)
        {
            map->current = i;
            return map->buckets[i];
        }
    }
    

    return NULL;
}

Pair * nextMap(HashMap * map) {

    for (size_t i = map->current+1; i < map->capacity; i++)
    {
        if(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
        {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}
