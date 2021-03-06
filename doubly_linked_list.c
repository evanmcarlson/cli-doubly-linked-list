/* Evan Carlson
 * 20463800
 *
 * doubly_linked_list.c
 *
 * Implement a sorted linked list of strings with operations Insert
 * in alphabetical order, Print, Member, Delete, Free_list.
 * The list nodes are doubly linked.
 *
 * Input:    Single character lower case letters to indicate operations,
 *           possibly followed by value needed by operation -- e.g. 'i'
 *           followed by "hello" to insert the string "hello" -- no
 *           double or single quotes.
 *
 * Output:   Results of operations.
 *
 * Compile:  gcc -g -Wall -o doubly_linked_list doubly_linked_list.c
 *
 * Run:      ./doubly_linked_list
 *
 */

/* You may not add any new header file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Max 99 chars + '\0' */
#define STRING_MAX 100

typedef struct list_node_s {
    char*  data;
    struct list_node_s* prev_p;
    struct list_node_s* next_p;
} node;

/* Pointers to the head and tail of the list */
struct list_s {
    struct list_node_s* h_p;
    struct list_node_s* t_p;
};

void Insert(struct list_s* list_p, char string[]);
void Print(struct list_s* list_p);
int  Member(struct list_s* list_p, char string[]);
void Delete(struct list_s* list_p, char string[]);
void Free_list(struct list_s* list_p);
char Get_command(void);
void Get_string(char string[]);
void Free_node(struct list_node_s* node_p);
struct list_node_s* Allocate_node(int size);
void Print_node(char title[], struct list_node_s* node_p);


/*-----------------------------------------------------------------*/
int main(void) {
    char          command;
    char          string[STRING_MAX];
    struct list_s list ;
    
    list.h_p = list.t_p = NULL;
    /* start with empty list */
    
    command = Get_command();
    while (command != 'q' && command != 'Q') {
        switch (command) {
            case 'i':
            case 'I':
                Get_string(string);
                Insert(&list, string);
                break;
            case 'p':
            case 'P':
                Print(&list);
                break;
            case 'm':
            case 'M':
                Get_string(string);
                if (Member(&list, string))
                    printf("%s is in the list\n", string);
                else
                    printf("%s is not in the list\n", string);
                break;
            case 'd':
            case 'D':
                Get_string(string);
                Delete(&list, string);
                break;
            case 'f':
            case 'F':
                Free_list(&list);
                break;
            default:
                printf("There is no %c command\n", command);
                printf("Please try again\n");
        }
        command = Get_command();
    }
    Free_list(&list);
    
    return 0;
}  /* main */


/*-----------------------------------------------------------------*/
/* Function:   Allocate_node
 * Purpose:    Allocate storage for a list node
 * Input arg:  size = number of chars needed in data member (including
 *                storage for the terminating null)
 * Return val: Pointer to the new node
 */
struct list_node_s* Allocate_node(int size) {
    node* nodeptr = (node*) malloc(sizeof(node));
    nodeptr->data = (char*) malloc(size * sizeof(char));
    return nodeptr;
}  /* Allocate_node */


/*-----------------------------------------------------------------*/
/* Function:   Insert
 * Purpose:    Insert new node in correct alphabetical location in list
 * Input arg:  string = new string to be added to list
 * In/out arg: list_p = pointer to struct storing head and tail ptrs
 * Note:       If the string is already in the list, print a message
 *                and return, leaving list unchanged
 */
void Insert(struct list_s* list_p, char string[]) {
    int len = (int) strlen(string) + 1;
    node* newNode = Allocate_node(len); // allocate memory
    newNode->data = string;
    newNode->next_p = NULL;
    
    if(list_p->h_p == NULL) { // first element
        list_p->h_p = newNode; // set node to both head and tail nodes
        list_p->t_p = newNode;
        list_p->h_p->prev_p = NULL; // previous node NULL
        return;
    }
    else if(list_p->h_p != NULL && list_p->h_p == list_p->t_p) { // only one element in list
        if(strcmp(list_p->h_p->data, newNode->data) <= 0) {
            newNode->next_p = list_p->h_p; // insert newNode before head
            list_p->h_p = newNode;
        } else {
            list_p->h_p->next_p = newNode; // insert newNode after head
            list_p->t_p = newNode;
        }
    }
    else if(strcmp(list_p->t_p->data, newNode->data) >= 0) { // insert after tail
        list_p->t_p->next_p = newNode;
        list_p->t_p = newNode;
    }
    else {  // find elements location in list
        node* current = list_p->h_p;
        while(current != NULL) {
            if(strcmp(current->data, newNode->data) >= 0) {
                newNode->next_p = current->next_p;
                current->next_p = newNode;
            }
            current = current->next_p;
        }
    }
}  /* Insert */

/*-----------------------------------------------------------------*/
/* Function:   Print
 * Purpose:    Print the contents of the nodes in the list
 * Input arg:  list_p = pointers to first and last nodes in list
 *
 * Hint: The implementation of this function (below) shows how
 * to traverse a linked list.
 */
void Print(struct list_s* list_p) {
    struct list_node_s* curr_p = list_p->h_p;
    
    printf("list = ");
    
    while (curr_p != NULL) {
        printf("%s ", curr_p->data);
        curr_p = curr_p->next_p;
    }
    printf("\n");
}  /* Print */


/*-----------------------------------------------------------------*/
/* Function:   Member
 * Purpose:    Search list for string
 * Input args: string = string to search for
 *             list_p = pointers to first and last nodes in list
 * Return val: 1, if string is in the list, 0 otherwise
 */
int  Member(struct list_s* list_p, char string[]) {
    node *current = list_p->h_p;
    while(current != NULL) {
        if(strcmp(current->data, string) == 0) {
            return 1;
        }
        current = current->next_p;
    }
    return 0;
}  /* Member */


/*-----------------------------------------------------------------*/
/* Function:   Free_node
 * Purpose:    Free storage used by a node of the list
 * In/out arg: node_p = pointer to node to be freed
 */
void Free_node(struct list_node_s* node_p) {
    free(node_p->data);
    free(node_p);
}  /* Free_node */


/*-----------------------------------------------------------------*/
/* Function:   Delete
 * Purpose:    Delete node containing string.
 * Input arg:  string = string to be deleted
 * In/out arg  list_p = pointers to head and tail of list
 * Note:       If the string is in the list, it will be unique.  So
 *             at most one node will be deleted.  If the string isn't
 *             in the list, the function just prints a message and
 *             returns, leaving the list unchanged.
 */
void Delete(struct list_s* list_p, char string[]) {
    // no elements
    node *temp = NULL;
    if(list_p->h_p == NULL) {
        printf("List is empty\n");
        return;
    }
    // one element
    if(list_p->h_p->next_p == NULL) {
        if(strcmp(list_p->h_p->data, string) == 0) {
            temp = list_p->h_p;
            list_p->h_p = NULL;
            return;
        }
        else {
            printf("'%s' not found\n", string);
            return;
        }
    }
    // multiple elements
    if(strcmp(list_p->h_p->data, string) == 0) {
        temp = list_p->h_p;
        list_p->h_p = list_p->h_p->next_p;
        list_p->h_p->prev_p = NULL;
        return;
    }
    temp=list_p->h_p->next_p;
    while(temp->next_p != NULL) {
        if(strcmp(temp->data, string) == 0) {
            temp->prev_p->next_p = temp->next_p;
            temp->next_p->prev_p = temp->prev_p;
            return;
        }
        temp = temp->next_p;
    }
    if(strcmp(temp->data, string) == 0) {
        temp->prev_p->next_p = NULL;
        return;
    }
    
    printf("'%s' not found\n", string);
}  /* Delete */

/*-----------------------------------------------------------------*/
/* Function:   Free_list
 * Purpose:    Free storage used by list
 * In/out arg: list_p = pointers to head and tail of list
 */
void Free_list(struct list_s* list_p) {
    node *current = list_p->h_p;
    // empty list
    if(current == NULL) {
        printf("List is empty\n");
        return;
    }
    // filled list
    while(current != NULL) {
        node* temp = current->next_p;
        Free_node(current);
        current = temp;
    }
}  /* Free_list */


/*-----------------------------------------------------------------*/
/* Function:   Get_command
 * Purpose:    Find and return the next non-whitespace character in
 *             the input stream
 * Return val: The next non-whitespace character in stdin
 */
char Get_command(void) {
    char c;
    
    printf("Please enter a command (i, d, m, p, f, q):  ");
    /* Put the space before the %c so scanf will skip white space */
    scanf(" %c", &c);
    return c;
}  /* Get_command */

/*-----------------------------------------------------------------*/
/* Function:   Get_string
 * Purpose:    Read the next string in stdin (delimited by whitespace)
 * Out arg:    string = next string in stdin
 */
void Get_string(char string[]) {
    
    printf("Please enter a string:  ");
    scanf("%s", string);
}  /* Get_string */


/*-----------------------------------------------------------------*/
/* Function:  Print_node
 * Purpose:   Print the data member in a node or NULL if the
 *            pointer is NULL
 * In args:   title:  name of the node
 *            node_p:  pointer to node
 */
void Print_node(char title[], struct list_node_s* node_p) {
    printf("%s = ", title);
    if (node_p != NULL)
        printf("%s\n", node_p->data);
    else
        printf("NULL\n");
}  /* Print_node */

