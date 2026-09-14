







































































































































































































































































































































































































































































































operator pop_value, push, efun0, efun1, efun2, efun3, efunv;

operator number, real, long, byte, nbyte, string, short_string, const0, const1;

operator aggregate, aggregate_assoc;




operator branch_when_zero, branch_when_non_zero, branch;
operator bbranch_when_zero, bbranch_when_non_zero, bbranch;

operator branch_ne, branch_ge, branch_le, branch_eq, bbranch_lt;

operator foreach, next_foreach, exit_foreach;
operator loop_cond_local, loop_cond_number;
operator loop_incr;
operator while_dec;

operator lor, land;

operator catch, end_catch;
operator time_expression, end_time_expression;

operator switch;

operator call_function_by_address, call_inherited, return, return_zero;


operator eq, ne, le, lt, ge, gt;

operator inc, dec, pre_inc, post_inc, pre_dec, post_dec;

operator transfer_local;


operator local, local_lvalue;
operator global, global_lvalue;
operator member, member_lvalue;
operator index, index_lvalue;
operator rindex, rindex_lvalue;
operator nn_range, nn_range_lvalue, rn_range, rn_range_lvalue;
operator rr_range, rr_range_lvalue, nr_range, nr_range_lvalue;
operator ne_range, re_range;


operator add_eq, sub_eq, and_eq, or_eq, xor_eq, lsh_eq, rsh_eq, mult_eq;
operator div_eq, mod_eq, assign;

operator void_add_eq, void_assign, void_assign_local;

operator add, subtract, multiply, divide, mod, and, or, xor, lsh, rsh;
operator not, negate, compl;

operator function_constructor;
operator simul_efun;

operator sscanf;
operator parse_command;

operator new_class, new_empty_class;
operator expand_varargs;
























unknown call_other(object | string | object *, string | mixed *,...);

mixed evaluate (mixed, ...);

object this_object();






#pragma allow_dot_call

string getuid(object default:F_THIS_OBJECT);


int to_int(string | float | int | buffer);
float to_float(string | float | int);


string to_json(mixed);
mixed from_json(string | buffer);


#pragma no_dot_call

object clone_object(string, ...);
function bind(function, object);
object this_player(int default: 0);
object this_interactive this_player( int default: 1);
object this_user this_player( int default: 0);
mixed previous_object(int default: 0);
void destruct(object);
object *all_previous_objects previous_object(int default: -1);
mixed *call_stack(int default: 0);
int sizeof(mixed);
int strlen sizeof(string);

#pragma allow_dot_call
string file_name(object default: F_THIS_OBJECT);
int len sizeof(mixed);
string capitalize(string);
string upper_case(string);
string lower_case(string);
string replace_string(string, string, string,...);
string repeat_string(string, int);
string envsubst(string);
string *explode(string, string);
mixed implode(mixed *, string | function, void | mixed);
#pragma no_dot_call

int call_out(string | function, int,...);
int member_array(mixed, string | mixed *, void | int);
int input_to(string | function,...);
int random(int);

#pragma allow_dot_call
object environment(void | object);
object *all_inventory(object default: F_THIS_OBJECT);
object first_inventory(object|string default: F_THIS_OBJECT);
object next_inventory(object default: F_THIS_OBJECT);
#pragma no_dot_call
object *deep_inventory(object default: F_THIS_OBJECT);

void say(string, void | object | object *);
void tell_room(object | string, string | object | int | float, void | object *);
object present(object | string, void | object);
void move_object(object | string);

void add_action(string | function, string | string *, void | int, ...);
string query_verb();
int command(string);
int remove_action(string, string);
mixed *commands();
void disable_commands();
void enable_commands();
void set_living_name(string);
object *livings();
object find_living(string);
object find_player(string);
void notify_fail(string | function);

int restore_object(string, void | int);
int save_object(string, void | int);
string save_variable(mixed);
mixed restore_variable(string);
object *users();
mixed *get_dir(string, int default: 0);
#pragma allow_dot_call
	int strcmp (string, string);
	string c_str (string);
	int strsrch (string, string | int, int default: 0);
	string strwrap (string, int, int|void);
#pragma no_dot_call



void write(mixed);
void tell_object(object, string);
void shout(string);
void receive(string);
void message(mixed, mixed, string | string * | object | object *,
	          void | object | object *);



object find_object(string, int default: 0);
object load_object find_object(string, int default: 1);
int find_call_out(int|string);



mapping allocate_mapping (int);
#pragma allow_dot_call
mixed *values(mapping);
mixed *keys(mapping);
mixed match_path(mapping, string);
#pragma no_dot_call
void map_delete(mapping, mixed);

string typeof(mixed);
#pragma allow_dot_call
	
	int clonep(mixed default: F_THIS_OBJECT);
	int intp(mixed);
	int undefinedp(mixed);
	int nullp undefinedp(mixed);
	int floatp(mixed);
	int stringp(mixed);
	int virtualp(object default: F_THIS_OBJECT);
	int functionp(mixed);
	int pointerp(mixed);
	int arrayp pointerp(mixed);
	int mapp(mixed);
	int objectp(mixed);
	int classp(mixed);
	string type typeof(mixed);

	
	int bufferp(mixed);
	
#pragma no_dot_call

int inherits(string, object);
void replace_program(string);


buffer allocate_buffer(int);

#pragma allow_dot_call
mixed regexp(string | string *, string, void | int);
mixed *reg_assoc(string, string *, mixed *, mixed | void);
#pragma no_dot_call
mixed *allocate(int);
mixed *call_out_info();


#pragma allow_dot_call
int crc32 (string | buffer);
#pragma no_dot_call




mixed read_buffer (string | buffer, void | int, void | int);
int write_buffer (string | buffer, int, string | buffer | int);


int write_file(string, string, void | int);
int rename(string, string);
int write_bytes(string, int, string);

int file_size(string);
string read_bytes(string, void | int, void | int);
string read_file(string, void | int, void | int);
int cp(string, string);

int link(string, string);
int mkdir(string);
int rm(string);
int rmdir(string);



#pragma allow_dot_call
	string clear_bit(string, int);
	int test_bit(string, int);
	string set_bit(string, int);
	int next_bit(string, int);

	string crypt(string, string | int);
	string oldcrypt(string, string | int);
#pragma no_dot_call

string ctime(int);
mixed *localtime(int);

int exec(object, object);
string function_exists(string, void | object, void | int);
object *objects(void | string | function, void | object);

string query_host_name();
int query_idle (object default:F_THIS_OBJECT);
string query_ip_name (void | object);
string query_ip_number (void | object);
int query_ip_port (void | object);
int query_heart_beat (object default:F_THIS_OBJECT);


object query_snoop(object default:F_THIS_OBJECT);
object query_snooping(object default:F_THIS_OBJECT);
object snoop(object, void | object);

int remove_call_out(int | void | string);
void set_heart_beat(int);
void set_hide(int);
void set_reset(object, void | int);

int tail(string);
void throw(mixed);
int time();
int uptime();

mixed *sort_array(mixed *, int | string | function, ...);
mixed *unique_array(mixed *, string | function, void | mixed);
mapping unique_mapping(mixed *, string | function, ...);
string *shallow_inherit_list(object default:F_THIS_OBJECT);
#pragma allow_dot_call
mixed *sort sort_array(mixed *, int | string | function, ...);
mixed *unique unique_array(mixed *, string | function, void | mixed);
mapping transform unique_mapping(mixed *, string | function, ...);
string *inherit_list shallow_inherit_list(object default:F_THIS_OBJECT);
#pragma no_dot_call
string *deep_inherit_list(object default:F_THIS_OBJECT);

void printf(string, ...);

#pragma allow_dot_call
string sprintf(string,...);
#pragma no_dot_call

mixed *stat(string, int default: 0);




#pragma allow_dot_call
	int interactive(object default:F_THIS_OBJECT);
	int living (object default:F_THIS_OBJECT);
	int userp(object default:F_THIS_OBJECT);
#pragma no_dot_call
string in_edit(object default:F_THIS_OBJECT);
int in_input(object default:F_THIS_OBJECT);
int wizardp(object default:F_THIS_OBJECT);

void enable_wizard();
void disable_wizard();

object master();




#pragma allow_dot_call
	int memory_info(object | void);
#pragma no_dot_call

mixed get_config(int);

int get_char(string | function,...);
object *children(string);

void reload_object(object);

void error(string);

mapping rusage();

void flush_messages (void | object);

void ed (string | void, string | void, string | int | void, int | void);


string cache_stats();


#pragma allow_dot_call
mixed filter(mixed * | mapping, string | function, ...);
mixed *map(string | mapping | mixed *, string | function, ...);
#pragma no_dot_call
mixed filter_array filter(mixed *, string | function, ...);
mapping filter_mapping filter(mapping, string | function, ...);
mapping map_mapping map(mapping, string | function, ...);
mixed *map_array map(mixed *, string | function, ...);




string malloc_status();
string mud_status (int default: 0);
void dumpallobj (string | void);

string dump_file_descriptors();
string query_load_average();

string origin();



int reclaim_objects();

int set_eval_limit(int);
int reset_eval_cost set_eval_limit(int default: 0);
int eval_cost set_eval_limit(int default: -1);
int max_eval_cost set_eval_limit(int default: 1);





int resolve (string, string);

mixed query_notify_fail();
object *named_livings();

#pragma allow_dot_call
	mixed copy(mixed);
	string *functions(object, int default: 0);
	string *variables(object, int default: 0);
	object function_owner(function);
#pragma no_dot_call

object *heart_beats();



int file_length (string);
int replaceable (object, void | string *);
string program_info (void | object);
void store_variable (string, mixed);
mixed fetch_variable (string);
void remove_interactive (object default: F_THIS_OBJECT);
void debug_message (string);
mapping memory_summary ();
mixed debug_info (int, object);
void dump_prog (object, ...);

#pragma allow_dot_call
	int refs(mixed);
	float cos(float);
	float sin(float);
	float tan(float);
	float asin(float);
	float acos(float);
	float atan(float);
	float sqrt(float);
	float log(float);
	float pow(float, float);
	float exp(float);
	float floor(float);
	float ceil(float);
#pragma no_dot_call





int socket_create(int, string | function, string | function | void);
int socket_bind(int, int);
int socket_listen(int, string | function);
int socket_accept(int, string | function, string | function);
int socket_connect(int, string, string | function, string | function);
int socket_write(int, mixed, string | void);
int socket_close(int);
int socket_release(int, object, string | function);
int socket_acquire(int, string | function, string | function, string | function);
string socket_error(int);
string socket_address(int | object);
string dump_socket_status();











int export_uid(object);
#pragma allow_dot_call
string geteuid(function | object default:F_THIS_OBJECT);
#pragma no_dot_call
int seteuid(string | int);


void shutdown (void | int);
