#ifndef MINES
#define MINES

inline constexpr const char* game_over_ascii =
            "\nGame Over!\n\n" \
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
            "\033[0m\n";

inline constexpr const char* game_won_ascii =
            "\nCongratulations! You beat the game!\n\n" \
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
            "\033[0m\n";


inline constexpr const char* colors[] = {
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

inline constexpr bool mode_coloured = true;
inline constexpr int max_array_length = 100; // maximum array length is 100 elements
inline constexpr int max_playing_field_size = 11; // maximum field size: 9 fields + 1 buffer on each side
inline constexpr int max_masked_field_size = 9; // maximum field size: 9 fields

enum commands {
    NONE = 0,
    OPEN = 1,
    MARK = 2,
    UNMARK = 3,
    QUIT = 4
};

enum color_idx {
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

struct Line {
public:
    char line[max_array_length] = {};

    Line() = default;
    Line(const char* str);

    char& operator[](int);
    const char& operator[](int) const;

    Line& operator=(const char*);
    Line& operator=(const Line&);

    bool operator==(const char*) const;
    bool operator==(const Line&) const;

    bool check_int();
    int to_int();

    // factories
    static Line get_word();
    static Line get_line();

private:
    Line& assign(const char*);
};

inline bool operator==(const char*, const Line&);

class Field final {
public:
    static Field& instance(const int, const int); // create instance with size and mine count
    static Field& instance(); // get instance after it has been created

    void print_table();

    bool  game_over();
    bool  game_won();

    Line open_func(int, int);
    Line mark_func(int, int);
    Line unmark_func(int, int);

    Field(const Field&)            = delete;
    Field& operator=(const Field&) = delete;
    Field(Field&&)                 = delete;
    Field& operator=(Field&&)      = delete;

    ~Field() = default;

private:
    Field(int, int); // private: only instance() constructs

    void open_tile(int, int);
    
    // static helper functions
    static void create_playing_field(Field&, int, int);
    static void create_masked_field(Field&, int);

    // member variables
    int arr_size;
    int mines;
    int playing_field[max_playing_field_size][max_playing_field_size] = {};
    int masked_field[max_masked_field_size][max_masked_field_size] = {};
};

// io_funcs.cpp
namespace console_io {
    commands read_cmd();
    int      read_int();
    int      get_table_size();
    int      get_mine_count(int);
}

#endif // !MINES
