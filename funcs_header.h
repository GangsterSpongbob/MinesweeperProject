#ifndef MINES
#define MINES

#define GAME_OVER_ASCII \
			"\033[32m" \
			"      NO!                          MNO!\n" \
			"     MNO!!                        MNNOO!\n" \
			"   MMNO!                           MNNOO!!\n" \
			" MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!!\n" \
			" !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO!\n" \
			"       ! MMMMMMMMMMMMMPPPPOOOOIII! !\n" \
			"        MMMMMMMMMMMMPPPPPOOOOOOII!!\n" \
			"        MMMMMOOOOOOPPPPPPPPOOOOMII!\n" \
			"        MMMMM..    OPPMMP    .,OMI!\n" \
			"        MMMM::   o.,OPMP,.o   ::I!!\n" \
			"          NNM:::.,,OOPM!P,.::::!!\n" \
			"         MMNNNNNOOOOPMO!!IIPPO!!O!\n" \
			"         MMMMMNNNNOO:!!:!!IPPPPOO!\n" \
			"          MMMMMNNOOMMNNIIIPPPOO!!\n" \
			"             MMMONNMMNNNIIIOO!\n" \
			"           MN MOMMMNNNIIIIIO! OO\n" \
			"          MNO! IiiiiiiiiiiiI OOOO\n" \
			"     NNN.MNO!   O!!!!!!!!!O   OONO NO!\n" \
			"    MNNNNNO!    OOOOOOOOOOO    MMNNON!\n" \
			"      MNNNNO!    PPPPPPPPP    MMNON!\n" \
			"         OO!                   ON!" \
            "\033[0m\n"

#define GAME_WON_ASCII \
			"\033[33m" \
			"             ___________\n" \
			"            \'._==_==_=_.\'\n" \
			"            .-\\:      /-.\n" \
			"           | (|:.     |) |\n" \
			"            \'-|:.     |-\'\n" \
			"              \\::.    /\n" \
			"               \'::. .\'\n" \
			"                 ) (\n" \
			"               _.\' \'._\n" \
			"              `\"\"\"\"\"\"\"`" \
            "\033[0m\n"


enum commands {
    NONE = 0,
    OPEN = 1,
    MARK = 2,
    UNMARK = 3,
    QUIT = 4
};

enum colors {
    RED = 0,
    BLUE = 1,
    GREEN = 2,
    LIGHT_RED = 3,
    MAGENTA = 4,
    YELLOW = 5,
    CYAN = 6,
    LIGHT_GREEN = 7,
    LIGHT_MAGENTA = 8,
    GREY = 9,
    RESET = 10
};

constexpr const char* color_codes[] = {
    "\033[31m",  // RED
    "\033[94m",  // BLUE
    "\033[92m",  // GREEN
    "\033[91m",  // LIGHT RED
    "\033[35m",  // MAGENTA
    "\033[33m",  // YELLOW
    "\033[36m",  // CYAN
    "\033[32m",  // LIGHT GREEN
    "\033[95m",  // LIGHT MAGENTA
    "\033[100m", // GREY
    "\033[0m",   // RESET
};

const bool mode_coloured = true;
const int max_array_length{ 100 }; // maximum array length is 100 elements

extern int arr_size, mines;
extern int** playing_field, ** masked_field;

void clear_str(char*);
void set_message(char*, const char[]);
bool compare(const char*, const char*);
bool check_int(const char*);
int  str_to_int(const char*);

void     print_table();
void     get_line(char*);
commands read_cmd();
int      read_int();
void     get_table_size(char*);
void     get_mine_count(char*);

void  free_array(int**&, const int&);
void  open_tile(const int&, const int&);
bool  game_over();
bool  game_won();
void  mask_table();
void  populate_table(int);
char* open_func(const int&, const int&);
char* mark_func(const int&, const int&);
char* unmark_func(const int&, const int&);

#endif // !MINES
