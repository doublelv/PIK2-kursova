#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct drug
{
  int nomenclature_number;
  char *name;
  double price;
  char *creation_date;
  struct drug *next;
} drug;

drug *create_drug(int num, char* name, double price, char* cr_date);                       // DONE
drug *push_to_head(drug *head, int nomenclature, char* name, double price, char* cr_date); // not tested
drug *push_to_tail(drug *head, int nomenclature, char* name, double price, char* cr_date); // not tested
void delete_drug_by_number(drug *head, int number);                                         // TO DO
int get_list_lenght(drug *head);                                                           // TO DO
int get_drug_index_by_nomeclature(drug *head, int nomenclature);                           // TO DO
int get_drug_index_by_name(drug *head, char* name );                                       // TO DO
void print_list(drug *head);                                                               // DONE
void print_drug(drug *drug);                                                               // DONE
void delete_list(drug *head);

int main(void)
{
  drug *lekarstvo = create_drug(10, "ala", 4.99, "01/01/2021");
  lekarstvo->next = create_drug(20, "bala", 10, "02/01/2021");
  lekarstvo->next->next = create_drug(30, "baldsdasa", 20, "02/01/2021");
  print_list(lekarstvo);

  delete_drug_by_number(lekarstvo, 20);
  printf("20 should be deleted\n");
  print_list(lekarstvo);

  delete_list(lekarstvo);
  return 0;
}

drug *create_drug(int num, char* name, double price, char* cr_date)
{
  drug *drug = malloc(sizeof(drug));
  drug->nomenclature_number = num;
  drug->name = malloc(strlen(name) + 1);
  drug->name = name;
  drug->price = price;
  drug->creation_date = malloc(strlen(cr_date) + 1);
  drug->creation_date = cr_date;
  drug->next = NULL;
  return drug;
}

drug *push_to_head(drug *head, int nomenclature, char* name, double price, char* cr_date)
{
  drug *new_head = create_drug(nomenclature, name, price, cr_date);
  new_head->next = head;
  printf("Added ");
  print_drug(new_head);
  return new_head;
}

drug *push_to_tail(drug *head, int nomenclature, char* name, double price, char* cr_date)
{
  drug *tmp = head;
  while(tmp != NULL)
  {
    tmp = tmp->next;
  }
  tmp = create_drug(nomenclature, name, price, cr_date);
  printf("Added ");
  print_drug(tmp);
  return head;
}

void delete_drug_by_number(drug *head, int number)
{
  //ne raboti s head-a
  drug *tmp = head;
  drug* prev;
  while(tmp->nomenclature_number != number)
  {
    prev = tmp;
    tmp = tmp->next;
  }
  prev->next = tmp->next;
  free(tmp);
}

void print_list(drug *head)
{
  drug *tmp;
  if(head == NULL)
  {
    printf("Empty list\n");
    return;
  }

  tmp = head;
  while(tmp)
  {
    print_drug(tmp);
    tmp = tmp->next;
  }
}

void print_drug(drug *drug)
{
  printf("Number %d with name %s and price %.2f was created on %s\n", drug->nomenclature_number, drug->name, drug->price, drug->creation_date);
}

void delete_list(drug *head)
{
  drug *tmp;
  while(head)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}
