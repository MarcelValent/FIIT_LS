//Marcel Valent
//FIIT STU LS 2020/2021
//DSA

//Red Black strom
// Prebrany kod zo stranky https://github.com/sebastiencs/red-black-tree
typedef enum rbcolor
{
	BLACK = 0,
	RED = 1
}t_rbcolor;

typedef unsigned int t_key;
typedef unsigned int t_value;

typedef struct s_rbnode
{
	t_key			key;
	t_value		value;
	t_rbcolor		color;
	struct s_rbnode	*left;
	struct s_rbnode	*right;

}t_rbnode;

int		get_key_RB(t_key key);
int		insert_RB(t_key key, t_value value);
void		erase_tree_RB(t_rbnode *node);
void		EraseRBTree();

//Prebrata HT
// Prebrany kod zo stranky https://github.com/qzchenwl/hashtable
typedef size_t HSIZE;

typedef struct hashnode {
	char *key;
	void *data;
	struct hashnode *next;
} ENTRY;

typedef struct hashtbl {
	HSIZE size;
	HSIZE count;
	ENTRY **nodes;
	HSIZE(*hashfunc)(const char *);
} HASHTBL;

void hashtbl_destroy();
int hashtbl_get(const char *key);
int hashtbl_insert_first(const char *key, void *data);
void hashtbl_create(HSIZE size);

// Moj AVL strom
typedef struct AVLTree {
	int num;
	short height;
	struct AVLTree *left;
	struct AVLTree *right;
}AVLtree;

int SearchAVL(int numInc);
int InsertAVL(int num);
void FreeAVLTree();
void FreeMyAVLTree(AVLtree *tree);

//Moja HT
typedef struct MyTable {
	int size;
	int usedSize;
	int *elements;
}myTable;

int SearchMyHT(int number);
int InsertMyHT(int number);
void FreeMyHT();