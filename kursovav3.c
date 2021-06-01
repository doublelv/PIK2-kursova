#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct drug_data
{
  int nomenclature_number;
  char name[30];
  double price;
  char creation_date[20];
} drug_data;

typedef struct drug
{
  drug_data data;
  struct drug *next;
}drug;

void menu();
void test_case_1();
void test_case_2();
void test_case_3();
void test_case_4();
void test_case_5();

drug_data create_drug_data(int num, char *name, double price, char *cr_date);
drug *create_drug(int num, char *name, double price, char *cr_date);
drug *push_to_head(drug *head, int nomenclature, char* name, double price, char* cr_date);
drug *push_to_tail(drug *head, int nomenclature, char* name, double price, char* cr_date);
drug *delete_drug_by_number(drug *head, int number);
void print_drug(drug *drug);
void print_drug_from_list(drug* head, int number);
void print_list(drug *head);
void change_price(drug *head, char *drug_name, double price);
void delete_list(drug *head);

void save_data(drug *head);
drug *read_data();

int main()
{
  menu();
  return 0;
}

void menu()
{
  int choice = -1;
  while(choice != 0)
  {
    printf("Enter a test case(1-5/0-exit): ");
    scanf("%d", &choice);
    switch (choice) {
      case 0:
        break;
      case 1:
      test_case_1();
        break;
      case 2:
      test_case_2();
        break;
      case 3:
      test_case_3();
        break;
      case 4:
      test_case_4();
        break;
      case 5:
      test_case_5();
        break;
      default:
        printf("Invalid number!\n");
        break;
    }
  }
}

void test_case_1()                                                                        // test case for create_drug(), print_list(), delete_drug_by_number().
{
  printf("\n");
  printf("-Testing create_drug(), print_list(), delete_drug_by_number().\n");
  drug *list_lekarstva = create_drug(10, "ala", 4.99, "01/01/2021");
  list_lekarstva->next = create_drug(20, "bala", 10, "02/01/2021");
  list_lekarstva->next->next = create_drug(30, "baldsdasa", 20, "03/01/2021");
  printf("-Should print 3 elements:\n");
  print_list(list_lekarstva);
  delete_drug_by_number(list_lekarstva, 20);
  printf("-Second element deleted, should print the first and last:\n");
  print_list(list_lekarstva);
  delete_list(list_lekarstva);
  printf("\n");
}

void test_case_2()                                                                        // test case for push_to_head() and push_to_tail()
{
  printf("\n");
  printf("-Testing push_to_head() and push_to_tail().\n");
  drug *list_lekarstva = create_drug(20, "evtino", 4.99, "01/01/2021");
  list_lekarstva = push_to_head(list_lekarstva, 10, "sredno", 10, "02/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 30, "skupo", 20, "03/01/2021");
  printf("-Should print 3 elements:\n");
  print_list(list_lekarstva);
  delete_list(list_lekarstva);
  printf("\n");
}

void test_case_3()                                                                        // test case for change_price()
{
  printf("\n");
  printf("-Testing change_price().\n");
  drug *list_lekarstva = create_drug(10, "ala", 4.99, "01/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 20, "bala", 10, "02/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 30, "baldsdasa", 20, "03/01/2021");
  printf("-Original elements:\n");
  print_list(list_lekarstva);
  change_price(list_lekarstva, "ala", 1.9);
  change_price(list_lekarstva, "bala", 1);
  change_price(list_lekarstva, "baldsdasa", 3.0);
  change_price(list_lekarstva, "this", 3.0);
  printf("-Elements should have different prices.\n");
  print_list(list_lekarstva);
  delete_list(list_lekarstva);
  printf("\n");
}

void test_case_4()                                                                        // test case for print_drug_from_list()
{
  printf("\n");
  printf("-Testing print_drug_from_list().\n-Should print ONLY number 30:\n");
  drug *list_lekarstva = create_drug(10, "ala", 4.99, "01/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 20, "bala", 10, "02/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 30, "baldsdasa", 20, "03/01/2021");
  print_drug_from_list(list_lekarstva, 30);
  delete_list(list_lekarstva);
  printf("\n");
}

void test_case_5()                                                                        // test case for save_data() and read_data()
{
  printf("\n");
  printf("-Testing save_data() and read_data()\n-Should print elements from 10 to 40, read from the read_data() function:\n");
  drug *list_lekarstva = create_drug(10, "ala", 4.99, "01/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 20, "bala", 10, "02/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 30, "baldsdasa", 20, "03/01/2021");
  list_lekarstva = push_to_tail(list_lekarstva, 40, "bal", 100, "04/01/2021");

  save_data(list_lekarstva);
  delete_list(list_lekarstva);

  drug *procheten_list = read_data();
  print_list(procheten_list);
  delete_list(procheten_list);
  printf("\n");
}

drug_data create_drug_data(int num, char *name, double price, char *cr_date)              // creates data and returns it to create_drug
{
  drug_data data;
  data.nomenclature_number = num;
  strcpy(data.name, name);
  data.price = price;
  strcpy(data.creation_date, cr_date);
  return data;
}

drug *create_drug(int num, char *name, double price, char *cr_date)                       // creates an instance of a drug and returns it
{
  drug *drug = malloc(sizeof(struct drug));
  drug->data = create_drug_data(num, name, price, cr_date);
  drug->next = NULL;
  return drug;
}

drug *push_to_head(drug *head, int nomenclature, char* name, double price, char* cr_date) // pushes a drug to the head and returns a pointer to it
{
  drug *new_head = create_drug(nomenclature, name, price, cr_date);
  new_head->next = head;
  return new_head;
}

drug *push_to_tail(drug *head, int nomenclature, char* name, double price, char* cr_date) // pushes a drug to the tail and returns a pointer to the head
{
  drug *tmp = head;
  while(tmp->next != NULL)
  {
    tmp = tmp->next;
  }
  tmp->next = create_drug(nomenclature, name, price, cr_date);
  return head;
}

drug *delete_drug_by_number(drug *head, int number)                                       // deletest the drug with a specified number
{
  drug *tmp = head;
  drug *prev;

  if(head->data.nomenclature_number == number)
  {
    head = head->next;
    printf("--Purged ");
    print_drug(tmp);
    free(tmp);
  }
  else
  {
    while(tmp->data.nomenclature_number != number)
    {
      prev = tmp;
      tmp = tmp->next;
    }
    prev->next = tmp->next;
    printf("--Purged ");
    print_drug(tmp);
    free(tmp);
  }
  return head;
}

void print_drug(drug *drug)                                                               // prints the specific drug
{
  printf("Number %d with name %s and price %.2f was created on %s\n", drug->data.nomenclature_number, drug->data.name, drug->data.price, drug->data.creation_date);
}

void print_drug_from_list(drug* head, int number)                                         // prints the drug with a specific number from a list
{
  drug *tmp = head;
  int found = 0;
  while(tmp != NULL)
  {
    if(tmp->data.nomenclature_number == number)
    {
      found = 1;
      break;
    }
    tmp = tmp->next;
  }
  if(found == 1)
  {
    print_drug(tmp);
  }
  else
  {
    printf("No drug with number '%d'\n", number);
  }
}

void print_list(drug *head)                                                               // prints the list, containg drugs
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

void change_price(drug *head, char *drug_name, double price)                              // changes the price of the drug with the specified name
{
  drug *tmp = head;
  int found = 0;
  int compare = 1;
  while(tmp!= NULL)
  {
    compare = strcmp(tmp->data.name, drug_name);
    if(compare == 0)
    {
      found = 1;
      break;
    }
    tmp = tmp->next;
  }

  if(found == 1)
  {
    tmp->data.price = price;
  }
  else
  {
    printf("No drug with name '%s'\n", drug_name);
  }
}

void delete_list(drug *head)                                                              // deletes the specified list of drugs
{
  drug *tmp = head;

  while(head != NULL)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}

void save_data(drug *head)                                                                // saves the drug list to data.bin
{
  FILE *fptr;
  drug *tmp = head;

  if((fptr = fopen("data.bin", "wb")) == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  while(tmp != NULL)
  {
    fwrite(&tmp->data, sizeof(struct drug_data), 1, fptr);
    tmp = tmp->next;
  }
  fclose(fptr);
}

drug *read_data()                                                                         // reads and writed every drug from data.bin to a list and returns it
{
  FILE *fptr;
  drug *tmp = malloc(sizeof(struct drug));
  drug *head = tmp;
  drug *end;

  if((fptr = fopen("data.bin", "rb")) == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  fread(&tmp->data, sizeof(struct drug_data), 1, fptr);

  while(1)
  {
    if(feof(fptr)) {break;}
    tmp->next = malloc(sizeof(struct drug));
    end = tmp;
    tmp = tmp->next;
    fread(&tmp->data, sizeof(struct drug_data), 1, fptr);
  }

  fclose(fptr);

  end->next = NULL;
  free(tmp);

  return head;
}
