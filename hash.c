/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 * Author: Aayan Shah
 * Created: 10-10-2026
 * Version: 1.0
 * 
 * Description: as described
 * 
 */
#include "hash.h"
#include "queue.h"

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))

static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;
  
  if (len <= 0 || data == NULL)
		return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

typedef struct hashtable{
  uint32_t size;
  queue_t **table;
}

// Make a hash table i.e. just an array of queues
hashtable_t *hopen(uint32_t hsize){
  hashtable_t_priv* hp;
  uint32_t i;

  if(hsize<=0){
    return NULL;
  }

  hp = (hashtable_t_priv*)malloc(sizeof(hashtable_t_priv));

  if(hp == NULL) return NULL;
  
  hp->table = (queue_t**)calloc(hsize, sizeof(queue_t**));

  if(hp->table == NULL){
    free(hp);
    return NULL;
  }

  hp->size = hsize;

  // for that one cased when making a queue fails
  for (int i = 0; i < hsize; i++){
    hp->table[i] = qopen();

    if(hp->table[i] == NULL){
      while(i>0){
        i--;
        qclose(hp->table[i]);
      }
      free(hp->table);
      free(hp);
      return NULL;
    }
  }
  return (hashtable_t*)hp;
}


// delete the hash table
void hclose(hashtable_t *htp){

}