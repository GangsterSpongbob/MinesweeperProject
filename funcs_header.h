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

const bool mode_coloured = true;
const int max_array_length{ 100 }; // maximum array length is 100 elements

extern int arr_size, mines;
extern int** playing_field, ** masked_field;

int str_to_int(const char*);
bool compare(const char*, const char*), check_int(const char*), game_over(), game_won();
void free_array(int**&, const int&), clear_str(char*), open_tile(const int&, const int&);
void get_table_size(char*), get_mine_count(char*);
void set_message(char*, const char[]), get_line(char*), get_word(char*);
void mask_table(), populate_table(int), print_table();
char* open_func(const int&, const int&), * mark_func(const int&, const int&), * unmark_func(const int&, const int&);

#endif // !MINES
