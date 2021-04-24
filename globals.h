#ifndef _GLOBALS
#define _GLOBALS

// Maximum named items in a room
#define MAX_ITEMS_PER_ROOM 5

// The maximum number of items you can carry
#define MAX_INV 5

// The number of rooms
#define MAX_ROOMS 4

// Handler for an input/command function.
typedef void (*actionPtr)(char *input);

// Handler for "using" an object
typedef void (*usePtr)(char *item);

// Handler to use to "take" an object
typedef void (*takePtr)(int id);

// Handler to use to "drop" an object
typedef void (*dropPtr)(int id);

// This structure contains the details of a single location.
//
// Our "game world" is made up of a collection of these locations.
typedef struct location
{
    // one-line description of the light-house
    char desc[100];

    // extended description of the light-house
    char edesc[512];

    // have we seen this?  If so we show the short-description
    // of the location when we enter it.
    int seen;

    // Items present in this location
    int items[MAX_ITEMS_PER_ROOM];

} location_t;



// This structure contains all the properties and details of a single item.
typedef struct object
{
    // The name of the item
    char name[17];

    // A one-line description of the item
    char desc[100];

    // function to call when this item is used.
    usePtr use;

    // function to call when this item is carried.
    usePtr use_carried;

    // Handler to pickup an object
    takePtr get_fn;

    // Handler to drop an object
    dropPtr drop_fn;

} object_t;



// Word contains a command the user can type
typedef struct word
{
    // The name of the command the user will enter
    char name[10];

    // Help information for this command, if present.
    char txt[32];

    // Is this hidden?
    int hidden;

    // The handler to invoke when that is typed
    actionPtr ptr;
} word_t;


// The player's location
extern int location;

// Count of elapsed turns
extern int turn;

// The player's inventory
extern int inv[MAX_INV];

// Dead? Won?
extern int dead;
extern int won;

// world locations
extern location_t world[];

// World items
extern object_t items[];

// Built-in commands
extern word_t dictionary[];


// Forward declarations

// utils.c
char *object_from_input(char *input);

// handlers.c
void call_fn(char *input);
void down_fn(char *input);
void drop_fn(char *input);
void examine_fn(char *input);
void get_fn(char *input);
void help_fn(char *input);
void inventory_fn(char *input);
void language_fn(char *input);
void look_fn(char *input);
void magic_fn(char *input);
void open_fn(char *input);
void quit_fn(char *input);
void up_fn(char *input);
void use_fn(char *input);


// items.c
int  is_object_present(char *name);
void location_add_item(char *name, int location);
void location_remove_item(char *name, int location);
void get_book(int id);
void get_torch(int id);
void get_torch_lit(int id);
void use_torch(char *txt);
void use_torch_carried(char *txt);
void get_mirror(int id);
void get_mirror_broken(int id);
void use_mirror(char *txt);
void get_generator(int id);
void use_generator(char *txt);
void use_generator_carried(char *txt);
void use_telephone(char *txt);
void drop_book(int id);
void drop_mirror(int id) ;
void drop_mirror_broken(int id) ;
void drop_torch(int id) ;
void drop_torch_lit(int id) ;
void drop_generator(int id);

// inventory.c
int inventory_has_item(char *name);
void inventory_take_item(char *name);
void inventory_drop_item(char *name);

#endif
