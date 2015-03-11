#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<string.h>
//#include<iostream>
#include<conio.h>

/*               Arvore AVL com funções de inserção, exclusão e leitura da arvore
                 Desenvolvido por Lucas Martins de Oliveira 
                 Ciência da Computação - Universidade Federal da Fronteira Sul - UFFS
                 Estruturas de Dados - Prof. Marco Aurélio Spohr
*/         

typedef struct node{            // inicia a estrutura NODE
       int key, height;         
       struct node *father;     
       struct node *left;       
       struct node *right;      
              }NODE;            

void treeInsert(int value);                        // função que insere os nós
int treeSearch(NODE *x, int k);                    // função de pesquisa da árvore
void iterativeTreeSearch(NODE *x, int k);          // função de pesquisa da árvore, mais rápida na maioria dos computadores
int treeMinimum(NODE *x);                          // funcão que passa o menor valor na árvore
int treeMaximum(NODE *x);                          // função que passo o maior valor na árvore
int treeSuccessor(NODE *x);                        // acha o sucessor do número desejado
int treePredecessor(NODE *x);                      // acha o predecessor do número desejado
void transplant(NODE *u, NODE *v);                 // refaz os arranjos da árvore
void treeDelete();                                 // deleta um valor da árvore
int treeRead();                                    // facilita a leitura na // testes no algoritmo
int menu();                                        // menu de acesso
void treeBalance(NODE *z);
void nodeHeight(NODE *z);
void rotateLeft(NODE *x,NODE *y, int r2);
void rotateRight(NODE *x, NODE *y, int r2);
void preOrder(NODE *x);
void inorder(NODE *x);
void postOrder(NODE *x);
void visit(NODE *x);
     

NODE *root;                                        // cria um ponteiro global que aponta para a raiz
NODE *search = NULL;                               // ponteiro global search, usada para pesquisas

main(){                                            // inicio da execusão principal
   int value;
       printf("\n**Inicializing the root**\n");
       printf("\nEnter a value for the new node: ");
       scanf("%d", &value);
       treeInsert(value);                               
       menu();
       getch();                                     
       system("pause");
       return(0);
       }

int menu(){
    int value;
    system("cls");
    int option;
             printf("\n--------------MENU--------------");
             printf("\n1 -> Insert node                ");
             printf("\n2 -> Delete node                ");
             printf("\n3 -> Exit                       ");
             printf("\n------------Tree AVL------------");
             printf("\nEnter the option that you want: ");
             scanf("%d", &option);
                          
             switch(option){
                             case 1:{
                                  system("cls");
                                     printf("\n**Inserting a new node**\n");
                                     printf("\nEnter a value for the new node: ");
                                     scanf("%d", &value);
                                     iterativeTreeSearch(root, value);
                                               if(search == NULL){
                                                         treeInsert(value);
                                                         }
                                               else{
                                                    printf("\nInsertion invalid !! This amount is already inserted.");
                                                    getch();
                                                    }   
                                     menu();
                                  break;
                                  }
                             
                             case 2:{
                                  system("cls");
                                     printf("\n**Deleting a node**\n");
                                     printf("\nEnter the amount you wish to delete: ");
                                     scanf("%d", &value);
                                     iterativeTreeSearch(root, value);
                                                  if(search != NULL){
                                                       treeDelete();
                                                            
                                                            }
                                                  else{
                                                       printf("\nNode not found !!");
                                                       }
                                                  getch(); 
                                     menu();
                                  break;
                                  }
                             
                             case 3:{
                                  printf("\nThanks for your participation\n");
                                  break;
                                  }
                             
                             case 4:{
                                  system("cls");
                                  printf("\nWhat node you want visit? ");
                                     //scanf("%d", &value);
                                     //iterativeTreeSearch(root, value);
                                     //treeRead(); 
                                     preOrder(root);
                                     //for()
                                                
                                     getch();           
                                     menu();
                                  break;
                                  }
                             
                             default: {
                                      printf("\nInvalid option. Try again !!\n");
                                      getch();
                                      menu();
                                     break;
                                     }
                             }   
}

//  ***Inserção na arvore, seguindo o modelo do Cormen***      
void treeInsert(int value){
     NODE *x, *y, *z;        
     y = NULL;               
     x = root;               

                 z = ( NODE *) malloc ( sizeof ( NODE ));           // aloca memoria do novo nó
                 z->left = z->right = z->father = NULL;             
                 z->height = 0;
                 z->key = value;                                         
                      while(x != NULL){                             // so nao ocorre na primeira inserção
                               y = x;                               
                                  if(z->key < x->key){              
                                             x = x->left;           
                                             }                      
                                  else{                             
                                       x = x->right;                
                                       } } 
                               z->father = y;       
                      if(y == NULL){                                
                            root = z;                               
                            
                            }                                       
                      else if(z->key < y->key){                     
                           y->left = z;                             
                           nodeHeight(z);
                           treeBalance(z);
                           }                                        
                           else{                                    
                                y->right = z;                       
                                nodeHeight(z);
                                treeBalance(z);
                                }                                   
                 printf("\n**Insertion completed successfully !!\n\n");
                 getch();
      }                                                             

      // faz pesquisa na árvore   // implementada mas sem uso por sua baixa eficiência 0(h) h = altura  
int treeSearch(NODE *x, int k){                       
       if((x == 0)||(k == x->key)){                   
             search = x;                              
             return 0;                                
             }                                        
       if(k < x->key){                                
            return treeSearch(x->left, k);            
            }                                          
       else{                                          
            return treeSearch(x->right, k);           
            }                                              
     }                                                

       // pesquisa na árvore
void iterativeTreeSearch(NODE *x, int k){             
           while((x != NULL)&&(k != x->key)){         
                    if(k < x->key){                   
                         x = x->left;                 
                         }                            
                    else{                             
                         x = x->right;                
                         }                            
           }                                          
         search = x;                                  
     }                                                

       //pesquisa o menor valor da arvore                                                                                               
int treeMinimum(NODE *x){                                                                                                                                          
     while(x->left != NULL){                          
                   x = x->left;                       
                   }                                  
           search = x;                                
           }                                          

           //pesquisa o maior valor da arvore
int treeMaximum(NODE *x){                             
     while(x->right != NULL){                         
                   x = x->right;                      
                   }                                  
           search = x;                                
           }                                          
          
          //pesquisa o sucessor do nó desejado 
int treeSuccessor(NODE *x){                           
    NODE *y;                                          
    if(x->right != NULL){                              
               return treeMinimum(x->right);          
               }                                      
    y = x->father;                                    
    while((y != NULL)&&(x == y->right)){              
             x = y;                                   
             y = y->father;                           
                          }                           
    search = y;                                       
    }
           //pesquisa o predecessor do nó desejado 
int treePredecessor(NODE *x){                         
    NODE *y;                                          
    if(x->left != NULL){                               
               return treeMaximum(x->left);           
                             }                        
    y = x->father;                                    
    while((y != NULL)&&(x == y->left)){               
             x = y;                                   
             y = y->father;                           
             }                                        
    search = y;                                       
    }

void treeDelete(){                                    // deve ser usada após a execusão da função: iterativeTreeSearch()
    NODE *y, *z;                                      
    z = search;                                       
         if(z->left == NULL){                         
                    transplant(z,z->right);           
                    }                                 
         else if(z->right == NULL){                   
                    transplant(z,z->left);            
                    }                                 
         else{                                        
              treeMinimum(z->right);                  
              y = search;                             
                if (y->father != z){                  
                       transplant(y,y->right);        
                       y->right = z->right;           
                       y->left->father = y;           
                       }                              
              transplant(z,y);                        
              y->left = z->left;                      
              y->left->father = y;                    
    }
    //postOrder();                                                 
    //preOrder(z);
    treeMinimum(root);
    treeMaximum(search);
    nodeHeight(search);
    treeBalance(search);
    treeMaximum(root);
    treeMinimum(search);
    nodeHeight(search);
    treeBalance(search);
    //postOrder(z);
    
    free(z);                                          
}                                                     
    
void transplant(NODE *u, NODE *v){                    //inicializa função com dois ponteiros
         if(u->father == NULL){                       
                       root = v;                      
                       }                              
         else if(u == u->father->left){               
                   u->father->left = v;               
                   }                                  
         else{                                        
              u->father->right = v;                   
              }                                       
         
         if(v != NULL){                               
              v->father = u->father;                  
              }                                       
         }                                            

           // Calcula a altura dos nós
void nodeHeight(NODE *z){                             // calcula a altura de cada nó apartir do nó inserido até a raiz                      
                                     // inicializa a variavel contador em 0
     while(z != NULL){                                // enquanto z for diferente de nulo, então:
                                     // altura do nó seja igual ao contador
             if((z->right != NULL)&&(z->left != NULL)){
                              if((z->right->height >= z->left->height)){
                                           z->height = z->right->height +1;
                                           }
                              if((z->right->height <= z->left->height)){
                                           z->height = z->left->height +1;
                                           }
                              }
             else{
                              if(z->right != NULL){
                                          z->height = z->right->height +1;
                                          }
                              if(z->left != NULL){
                                          z->height = z->left->height +1;
                                          }                       
                  }     
                              if((z->right == NULL)&&(z->left==NULL)){
                                           z->height = 0;
                                           }
                        printf("\nz-> = %d = %d", z->key, z->height);            
                z = z->father;                        
             }                                             
     }                                                
     
     // calcula o balanceamento de cada nó e organiza as rotações necessarias
void treeBalance(NODE *z){                            
     z->height = 0;                                   
     NODE *y;                                         
     int balance, r2;                                 
         while(z != 0){                                      
         balance = 0;                                             
             if((z->left == NULL)&&(z->right != NULL)){                
                 balance =-1 - z->right->height;                       
                             }                                         
             if((z->right == NULL)&&(z->left != NULL)){                
                 balance = z->left->height + 1;                        
                                }                                      
             if((z->right != NULL)&&(z->left != NULL)){                
             balance = z->left->height - z->right->height;             // calcula balanceamento(esquerda - direita)
                     }                                                 
                     if((balance > 1)||(balance < -1)){                
                             if(balance > 1){                          
                                        y = z->left;                   
                                  if(y->left == NULL){                   
                                             r2 = 1;                     
                                             rotateLeft(z,y,r2);         
                                             r2 = 0;                     
                                             rotateRight(z,z->left, r2);                                          
                                             }                               
                                  else{                                  
                                             r2 = 0;                     
                                             rotateRight(z,z->left, r2); 
                                            }}                           
                             if(balance < -1){                                                      
                                        y = z->right;                    
                                    if(y->right == NULL){                
                                             r2 = 1;                     
                                             rotateRight(z,y, r2);       
                                             r2 = 0;                     
                                             rotateLeft(z,z->right, r2); 
                                          }                              
                                    else{                                
                                             r2 = 0;                     
                                             rotateLeft(z,z->right, r2); 
                                             }}}                         
         z = z->father;                                                  
     }                                                                     
}                                                                        

            // executa a rotação a esquerda e recalcula a altura
void rotateLeft(NODE *x,NODE *y, int r2){                                // recebe como parametros o nó desejado/ variação do nó(filhos ou pai conforme necessario), e se vai ser rotação simples ou dupla
     NODE *w = x, *z = y->right;                                           
          
          if(r2 == 1){                                                   
              x->left = z;                                               
              z->father = w;                                             
              z->left = y;                                               
              y->father = z;                                             
              y->right = NULL;
              
          }                                                                            
          else{                                                          
               if(x->father != NULL){                                    
                            x->father->right = y;                        
                            }                                            
          else{                                                          
               root = y;                                                 
               }                                                         
          if(y->left != NULL){                                           
                     y->left->father = w;                                
                     }                                                   
             y->father = w->father;                                      
             x->right = y->left;                                         
             x->father = y;                                              
             y->left = w;                                                
          }                                                              
          z->height = 0;
          
     if(r2 == 0){                                                        
           treeMinimum(x);                                               
           treeMaximum(search);
           search->height = 0;                                           
           nodeHeight(search);                                           
           treeBalance(search);
           treeMaximum(y->left);                                         
           treeMinimum(search);
           search->height = 0;                                           
           nodeHeight(search);                                           
           treeBalance(search);
           //nodeHeight(x);
            
           }                                                             
     }                                                                   

           // executa a rotação a direita e recalcula a altura                                                                   
void rotateRight(NODE *x, NODE *y, int r2){;                              
     NODE *w = x, *z = y->left;                                            
          
          if(r2 == 1){                                                   
              x->right = z;                                              
              z->father = w;                                             
              z->right = y;                                              
              y->father = z;                                             
              y->left = NULL;
              
              }                                                          
              
          else{                                                          
               if(x->father != NULL){                                    
               x->father->left = y;                                      
               }                                                         
          else{                                                          
               root = y;                                                 
               }                                                         
          if(y->right != NULL){                                          
                      y->right->father = w;                              
                      }                                                 
             y->father = w->father;                                      
             x->left = y->right;                                         
             x->father = y;                                              
             y->right = w;                                               
          }                                                              
          z->height = 0;
          
     if(r2 == 0){                                                        // só entra se esta for uma rotação simples ou a segunda rotação de uma dupla
     treeMinimum(x);                                                     // encontra o ponto minimo apartir do nó
     treeMaximum(search);
     search->height = 0;                                                 // altura do nó no ponto minimo é 0
     nodeHeight(search);                                                 // calcula a altura do nó apartir do ponto minimo
     treeBalance(search);
     treeMaximum(y->right);                                              // encontra o ponto maximo apartir do nó
     treeMinimum(search);
     search->height = 0;                                                 // altura do nó no ponto maximo é 0
     nodeHeight(search);                                                 // calcula a altura do nó apartir do ponto maximo
     treeBalance(search);
     //nodeHeight(x);
     }                                                                   
}                                                                        

         // função utilizada para testes
int treeRead(){
     if(search == NULL){
                    printf("\nNode invalid");
                    return 0;
                    }
     else{
                    printf("\nkey = %d", search->key);
                    //printf("\nID = %d", search);
                    printf("\nHeight = %d", search->height);
                    //printf("\nFather = %d", search->father);
                    //printf("\nLeft = %d", search->left);
                    //printf("\nRight = %d", search->right);
                    }
     if(search->father == NULL){
                    printf("\nFather pointer is NULL");
                    }
     else{
                    printf("\nFather key = %d", search->father->key);
                    //printf("\nID = %d", search->father);
                    printf("\nFather height = %d", search->father->height);
                    //printf("\nFather = %d", search->father->father);
                    //printf("\nLeft = %d", search->father->left);
                    //printf("\nRight = %d", search->father->right);
                    }
     if(search->left == NULL){
                    printf("\nFilho da esquerda aponta para vetor nulo");
                    }
     else{
                    printf("\nFilho esquerda = %d", search->left->key);
                    //printf("\nID = %d", search->left);
                    printf("\nleft height = %d", search->left->height);
                    //printf("\nFather = %d", search->left->father);
                    //printf("\nLeft = %d", search->left->left);
                    //printf("\nRight = %d", search->left->right);
                    }
     if(search->right == NULL){
                    printf("\nFilho da direita aponta para vetor nulo");
                    }
     else{
                    printf("\nFilho direita = %d", search->right->key);
                    //printf("\nID = %d", search->right);
                    printf("\nRight height = %d", search->right->height);
                    //printf("\nFather = %d", search->right->father);
                    //printf("\nLeft = %d", search->right->left);
                    //printf("\nRight = %d", search->right->right);
                    }
     //printf("\nRaiz = %d", root);
     }

void preOrder(NODE *x){
  if(x != NULL){
    preOrder(x->left);
    preOrder(x->right);
  }
}

void visit(NODE *x){
  printf("\nno visitado = %d ", x->key);
  if(x->father != NULL){
            printf("(%d) ", x->father->key);
               }
  printf("weight = %d ", x->height);
}

void inorder(NODE *x){
  if(x != NULL){
    inorder(x->left);
    visit(x);
    inorder(x->right);
  }
}

void postOrder(NODE *x){
  if(x != NULL){
    postOrder(x->left);
    postOrder(x->right);
    nodeHeight(x);
    treeBalance(x);
  }
}


