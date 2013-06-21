/*
 * Author: NagaChaitanya Vellanki
 *
 * Hash table example
 */

#include <errno.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  ENTRY item;
  ENTRY *found_item;

  /* create hash table */
  if(hcreate(3) == 0) {
    printf("Error on hcreate, %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  item.key = "1";
  item.data = "foo";
  hsearch(item, ENTER);

  item.key = "2";
  item.data = "bar";
  hsearch(item, ENTER);

  item.key = "3";
  item.data = "goo";
  hsearch(item, ENTER);

  item.key = "4";
  item.data = "bird";

  // created a hash table of size 3, ideally entering a 4th item should
  // return NULL but if it does not the system must have a created a hash
  // table of bigger size for performance reasons
  if(hsearch(item, ENTER) == NULL) {
    printf("Erron on hsearch, %s\n", strerror(errno));
  }

  item.key = "2";
  found_item = hsearch(item, FIND);
  if(found_item != NULL) {
    printf("key: %s, data: %s\n", found_item->key, (char *)found_item->data);
  } else {
    printf("key: %s was not found\n", item.key);
  }

  item.key = "5";
  found_item = hsearch(item, FIND);
  if(found_item != NULL) {
    printf("key: %s, data: %s\n", found_item->key, (char *)found_item->data);
  } else {
    printf("key: %s was not found\n", item.key);
  }

  hdestroy();
  exit(EXIT_SUCCESS);
}
