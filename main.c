#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef struct list{
    int32_t data;
    struct list* next;
}list;
void push(list** head,int32_t newData){
    list* newEl = (list*)malloc(sizeof(list));
    newEl->data = newData;
    newEl->next = (*head);
    (*head) = newEl;
}
void freeList(list* head){
    list* currentEl;
    while(head !=NULL){
        currentEl=head;
        head=head->next;
        free(currentEl);
    }

}
void print(list* head,FILE* nomefile){
    list*current=head;
    while (current !=NULL){
        if(current->next !=NULL) fprintf(nomefile,"%i ",current->data);
        else fprintf(nomefile,"%i",current->data);
        current=current->next;

    }
}

 typedef struct car{
     int autonomy;
     struct car* next;

 }car;
void carInsert(car** head,int32_t new){
    car* new_car=(car*)malloc(sizeof(car));
    new_car->autonomy= new;
    new_car->next=(*head);
    (*head)=new_car;
}
int32_t deleteCar(car **head,int32_t key){
    car* temp;
    int32_t flag=0;
    if((*head)==NULL) return 0;
    if ((*head)->autonomy == key) {
            temp = *head;
            (*head) = (*head)->next;
            free(temp);
            flag = 1;

        }

    else{
        car* corrente=(*head);
        while(corrente->next != NULL){
            if(corrente->next->autonomy == key){
                temp=corrente->next;
                corrente->next=corrente->next->next;
                free(temp);
                flag=1;
                break;
            }
            else corrente=corrente->next;
        }

    }
    return flag;
}

int32_t maxAutonomyCar(car* head){
    int32_t max=0;
    while(head!=NULL){
        if(head->autonomy > max) max=head->autonomy;
        head=head->next;
    }
    return max;
}
void freeListOfCar(car* head){
    car* currentEl;
    while(head !=NULL){
        currentEl=head;
        head=head->next;
        free(currentEl);
    }

}




typedef struct nodeStation{
    int32_t distance;
    int32_t max_autonomy_car;
    struct car *park;
    struct nodeStation *left, *right,*parent;
}nodeStation;
nodeStation *newNodeStation(int32_t miles){
    nodeStation *station= (nodeStation *)malloc(sizeof(nodeStation));
    station->distance=miles;
    station->park=NULL;
    station->left =NULL;
    station->right =NULL;
    station->parent = NULL;
    return station;
}

void tree_insert(nodeStation** root,nodeStation* z){//funge!!!!
    nodeStation* y = NULL;
    nodeStation* x=(*root);
    while (x!= NULL){
        y=x;
        if(z->distance < x->distance) x= x->left;
        else x=x->right;
    }
    z->parent= y;
    if(y==NULL) (*root)=z;
    else if ( z->distance < y->distance) y->left=z;
    else y->right=z;

}
nodeStation* minValue(nodeStation* station){
    nodeStation* current = station;
    while(current->left != NULL){
        current= current->left;
    }
    return current;
}
nodeStation* maxValue(nodeStation* station){
    nodeStation* current=station;
    while(current->right != NULL){
        current=current->right;
    }
    return current;
}
nodeStation* inOrderSuccessor(nodeStation* n){
    if(n->right !=NULL) return minValue(n->right);
    nodeStation* p= n->parent;
    while (p != NULL && n == p->right){
        n = p;
        p = p->parent;
    }
    return p;

}

nodeStation* inOrderPredecessor(nodeStation* n){
    if(n->left != NULL) return maxValue(n->left);
    nodeStation* p = n->parent;
    while(p!= NULL && n == p->left){
        n = p;
        p = p->parent;
    }
    return p;
}
nodeStation* search(nodeStation* root,int32_t miles){
    if( root==NULL || root->distance==miles)
        return root;
    if(root->distance < miles)
        return search(root->right , miles);
    else return search(root->left, miles);
}

void Transplant(nodeStation** root,nodeStation* u,nodeStation* v){
    if ( u->parent==NULL) *root=v;
    else if (u==u->parent->left) u->parent->left=v;
    else u->parent->right=v;
    if(v!=NULL) v->parent=u->parent;
}
void Tree_delete(nodeStation** root,nodeStation* z) {
    nodeStation *y = NULL;
    if (z->left == NULL){
        Transplant(root, z, z->right);
        free(z);
    }
    else if (z->right == NULL) {
        Transplant(root, z, z->left);
        free(z);
    }
    else {
        y = minValue(z->right);
        if(y!=z->right){
            Transplant(root,y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        Transplant(root,z,y);
        y->left=z->left;
        y->left->parent=y;
        free(z);

    }
}
typedef struct bufferNodi{
    nodeStation * node;
    struct bufferNodi* next;
}bufferNodi;
void printContrario(bufferNodi* head,FILE* nomefile,int32_t fine){
    if(head==NULL) return;
    printContrario(head->next,nomefile,fine);
    if(head->node->distance==fine)fprintf(nomefile,"%i",head->node->distance);
    else fprintf(nomefile,"%i ",head->node->distance);
}
void freeBuffer(bufferNodi * head){
    bufferNodi * currentEl;
    while(head !=NULL){
        currentEl=head;
        head=head->next;
        free(currentEl);
    }

}













void pianificaPercorsoDiretto(int32_t inizio,int32_t fine,nodeStation* root,FILE* nomefile) {//implementa il maxvalue direttamente nei nodi station
    if (inizio < fine) {
        nodeStation *start = search(root, inizio);
        nodeStation *current = start;
        nodeStation *temp = NULL;
        struct list** head_refe=NULL;
        struct list* head=NULL;
        int bool=0;
        int flag=0;
        head_refe=&head;
        //int32_t maxAutonomyStart = MaxValue(start->park);
        int32_t final = fine;
        int32_t sum = 0;
        push(head_refe,fine);
        while (start->distance + start->max_autonomy_car < final) {
            bool = 1;
            while (sum < final) {
                temp = inOrderSuccessor(current);
                sum = temp->distance + temp->max_autonomy_car;
                current = temp;
            }
            if (temp->distance == final) {
                fprintf(nomefile,"%s", "nessun percorso\n");
                flag=1;
                break;
            }
            else {
                push(head_refe, temp->distance);
                final = temp->distance;
                sum = 0;
                current = start;
            }
        }
        if (bool==1) push(head_refe,inizio);
        if(flag!=1) {
            print(head,nomefile);
            fprintf(nomefile,"\n");
        }

        freeList(head);

    }

}
void pianificaPercorsoContrario(nodeStation *inizio,nodeStation *fine,FILE* namefile){
    int32_t distanzaInizio=inizio->distance;
    int32_t distazaFinale=fine->distance;
    nodeStation* current=inizio;
    nodeStation* lastAdd=NULL;
    nodeStation *temp = inOrderPredecessor(inizio);
    int32_t dist=(inOrderPredecessor(inizio))->distance;
    int32_t curMax=distanzaInizio;
    int32_t count=0;
    //inserisco subito l'inizio
    bufferNodi *head=(bufferNodi*)malloc(sizeof(bufferNodi));
    head->node=inizio;
    head->next=NULL;

    int flag=0;

    while(flag==0) {
        while (dist >= (current->distance - current->max_autonomy_car)) {
            if (temp->distance==distazaFinale){
                flag=1;
                break;
            }
            if (temp->distance - temp->max_autonomy_car < curMax) {//cur max è ipoteticamente ultimo max aggiunto
                curMax = temp->distance - temp->max_autonomy_car;
                lastAdd = temp;
            }
            temp= inOrderPredecessor(temp);

            dist = temp->distance;


        }
        if(flag==0) {
            //lastadd è null se il piu vantaggioso aggiunto è anche l'ultimo raggiungibile dal precedente nella sequenza di visite
            if(lastAdd==NULL || lastAdd->distance - lastAdd->max_autonomy_car > dist){
                fprintf(namefile,"%s","nessun percorso\n");
                return;
            }//caso percorso impossibile;
            current = lastAdd;
            bufferNodi* new_bufferEL=(bufferNodi*)malloc(sizeof(bufferNodi));
            new_bufferEL->node=lastAdd;
            new_bufferEL->next=head;
            head=new_bufferEL;

            count++;
            curMax = distanzaInizio;
            dist = lastAdd->distance;
            lastAdd=NULL;
        }
        if(flag==1 && count==0){
            fprintf(namefile,"%i %i\n",inizio->distance,fine->distance);

            return;
        } //direttamente collegate
    }
    //aggiungo il finale(smallest)
    bufferNodi* nodoFinale=(bufferNodi*)malloc(sizeof(bufferNodi));
    nodoFinale->node=fine;
    nodoFinale->next=head;
    head=nodoFinale;
    bufferNodi *stampa=head;
    nodeStation *temporaneo=head->node; //per tenere info del precedente
    head=head->next; //parto da quello dopo al finale(sto andando dal piu piccolo al piu grande).In teoria qua è sempre!=NULL,son sempre almeno inizio e fine
    nodeStation *corrente=head->node;
    while(head->next!=NULL) {
        do {
            corrente = inOrderPredecessor(corrente);
            int32_t sum = corrente->distance - corrente->max_autonomy_car;
            if (sum <= temporaneo->distance &&
                (head->next->node->distance - head->next->node->max_autonomy_car) <= corrente->distance) {
                head->node = corrente;
            }

        } while(corrente!=temporaneo);
        //printf("%i ",head->node->distance);

        temporaneo=head->node;
        head=head->next;
        corrente=head->node;
    }
    printContrario(stampa,namefile,fine->distance);
    fprintf(namefile,"\n");
    freeBuffer(stampa);






}




int main() {
    //FILE *file = fopen("C:\\Users\\39340\\Downloads\\archivio_test_aperti\\open_107.txt", "r");
    FILE *fileO=stdout; //fopen("C:\\Users\\39340\\OneDrive\\Desktop\\testAPI\\API.OUT.txt","w");

    char istruction[25];
    int32_t distance, numberOfCars, autonomy;
    int32_t autonomies[512];
    int32_t start, finish;
    nodeStation *ROOT = NULL;




    while (!feof(stdin)) {
        if(fscanf(stdin, "%s", istruction)==0){
            return 0;
        }
        if (strcmp(istruction, "aggiungi-stazione") == 0) {
            //aggiungi stazione
            if (fscanf(stdin, "%i %i", &distance, &numberOfCars) == 2) {
                for (int i = 0; i < numberOfCars; i++) {
                    if(fscanf(stdin, "%i", &autonomies[i])==0){
                        return 0;
                    }
                }
                if (search(ROOT, distance) != NULL) fprintf(stdout,"%s", "non aggiunta\n");
                else {
                    nodeStation *temp = newNodeStation(distance);
                    tree_insert(&ROOT, temp);
                    int32_t max = 0;
                    for (int y = 0; y < numberOfCars; y++) {
                        carInsert(&(temp->park), autonomies[y]);
                        if (autonomies[y] >= max) max = autonomies[y];
                    }
                    temp->max_autonomy_car = max;
                    fprintf(stdout,"%s", "aggiunta\n");
                }


            }

        }
        if (strcmp(istruction, "demolisci-stazione") == 0) {
            //demolisci stazione
            if (fscanf(stdin, "%i", &distance) ==1) {
                nodeStation *temp = search(ROOT, distance);
                if (temp != NULL) {
                    freeListOfCar(temp->park);
                    temp->park = NULL;
                    Tree_delete(&ROOT, temp);
                    fprintf(stdout,"%s", "demolita\n");

                } else fprintf(stdout,"%s", "non demolita\n");
            }

        }
        if (strcmp(istruction, "aggiungi-auto") == 0) {
            //aggiungi auto
            if (fscanf(stdin, "%i %i", &distance, &autonomy) == 2) {
                nodeStation *temp = search(ROOT, distance);
                if (temp != NULL) {
                    carInsert(&(temp->park), autonomy);
                    if (temp->max_autonomy_car < autonomy) temp->max_autonomy_car = autonomy;
                    fprintf(stdout,"%s", "aggiunta\n");
                } else fprintf(stdout,"%s", "non aggiunta\n");
            }
        }
        if (strcmp(istruction, "rottama-auto") == 0) {
            if (fscanf(stdin, "%i %i", &distance, &autonomy) == 2) {
                nodeStation *temp = search(ROOT, distance);
                if (temp != NULL) {
                    int32_t flag = deleteCar(&(temp->park), autonomy);
                    if (flag == 0) fprintf(stdout,"%s", "non rottamata\n");
                    else {
                        if (temp->max_autonomy_car == autonomy) temp->max_autonomy_car = maxAutonomyCar(temp->park);
                        fprintf(stdout,"%s", "rottamata\n");
                    }
                } else fprintf(stdout,"%s", "non rottamata\n");
            }


        }
        if (strcmp(istruction, "pianifica-percorso") == 0) {

            if (fscanf(stdin, "%i %i", &start, &finish) ==2) {
                if(start<finish) pianificaPercorsoDiretto(start, finish, ROOT,fileO);
                else {
                    nodeStation *iniziale= search(ROOT,start);
                    nodeStation *finale= search(ROOT,finish);

                    pianificaPercorsoContrario(iniziale,finale,fileO);
                    //printf("\n");//occhio new line alla fine
                }
            }



            }
        }


    }