/* utils.h
 * A module of J-Pilot http://jpilot.org
 * 
 * Copyright (C) 1999-2002 by Judd Montgomery
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pi-datebook.h>
#include <pi-address.h>
#include <pi-todo.h>
#include <pi-memo.h>
#include <pi-file.h>
#include <gtk/gtk.h>

#include "libplugin.h"
#include "japanese.h"
#include "cp1250.h"
#include "russian.h"

#define PRINT_FILE_LINE printf("%s line %d\n", __FILE__, __LINE__)

#ifdef ENABLE_PROMETHEON
#define PN "CoPilot"
#else
#define PN "J-Pilot"
#endif

#ifdef ENABLE_PROMETHEON
#define EPN "copilot"
#else
#define EPN "jpilot"
#endif

#define	FPI_STRING	"-//Judd Montgomery//NONSGML "PN" "VERSION"//EN"

/*This is how often the clock updates in milliseconds */
#define CLOCK_TICK 1000

#define CATEGORY_ALL 300

#define SHADOW GTK_SHADOW_ETCHED_OUT

/*Used to mark the entry in the clist to add a record */
/* FIXME: Move to libplugin */
#define CLIST_NEW_ENTRY_DATA 100
#define CLIST_ADDING_ENTRY_DATA 101
#define CLIST_MIN_DATA 199

#define DIALOG_SAID_1           454
#define DIALOG_SAID_PRINT       454
#define DIALOG_SAID_FOURTH      454
#define DIALOG_SAID_CURRENT     454
#define DIALOG_SAID_2           455
#define DIALOG_SAID_LAST        455
#define DIALOG_SAID_ALL         455
#define DIALOG_SAID_3           456
#define DIALOG_SAID_CANCEL      456
/* Import dialog */
#define DIALOG_SAID_IMPORT_YES  455
#define DIALOG_SAID_IMPORT_ALL  456
#define DIALOG_SAID_IMPORT_SKIP 457
#define DIALOG_SAID_IMPORT_QUIT 458

#define CAL_DONE   100
#define CAL_CANCEL 101

#define PIXMAP_NOTE          100
#define PIXMAP_ALARM         101
#define PIXMAP_BOX_CHECK     102
#define PIXMAP_BOX_CHECKED   103
#define PIXMAP_FLOAT_CHECK   104
#define PIXMAP_FLOAT_CHECKED 105

#define SORT_ASCENDING       100
#define SORT_DESCENDING      101

/* Import defines */
#define MAX_IMPORT_TYPES     10 /* Must be more than the following types */
#define IMPORT_TYPE_UNKNOWN  99
#define IMPORT_TYPE_TEXT    100
#define IMPORT_TYPE_DAT     101
#define IMPORT_TYPE_CSV     102
#define IMPORT_TYPE_XML     103

/* Export defines */
#define EXPORT_TYPE_UNKNOWN    99
#define EXPORT_TYPE_TEXT      100
#define EXPORT_TYPE_DAT       101
#define EXPORT_TYPE_CSV       102
#define EXPORT_TYPE_XML       103
#define EXPORT_TYPE_VCARD     104
#define EXPORT_TYPE_ICALENDAR 105
#define EXPORT_TYPE_LDIF      106

/* Dat file types */
#define DAT_DATEBOOK_FILE    10
#define DAT_ADDRESS_FILE     11
#define DAT_TODO_FILE        12
#define DAT_MEMO_FILE        13

extern unsigned int glob_find_id;

typedef enum {
   DATEBOOK = 100L,
   ADDRESS,
   TODO,
   MEMO,
   REDRAW
} AppType;

typedef struct {
   PCRecType rt;
   unsigned int unique_id;
   unsigned char attrib;
   struct Appointment a;
} MyAppointment;

typedef struct AppointmentList_s {
   AppType app_type;
   struct AppointmentList_s *next;
   MyAppointment ma;
} AppointmentList;

typedef struct {
   PCRecType rt;
   unsigned int unique_id;
   unsigned char attrib;
   struct Address a;
} MyAddress;

typedef struct AddressList_s {
   AppType app_type;
   struct AddressList_s *next;
   MyAddress ma;
} AddressList;

typedef struct {
   PCRecType rt;
   unsigned int unique_id;
   unsigned char attrib;
   struct ToDo todo;
} MyToDo;

typedef struct ToDoList_s {
   AppType app_type;
   struct ToDoList_s *next;
   MyToDo mtodo;
} ToDoList;

typedef struct {
   PCRecType rt;
   unsigned int unique_id;
   unsigned char attrib;
   struct Memo memo;
} MyMemo;

typedef struct MemoList_s {
   AppType app_type;
   struct MemoList_s *next;
   MyMemo mmemo;
} MemoList;

struct search_record
{
   AppType app_type;
   int plugin_flag;
   unsigned int unique_id;
   struct search_record *next;
};

struct sorted_cats
{
   char *Pcat;
   int cat_num;
};

int cat_compare(const void *v1, const void *v2);

gint timeout_date(gpointer data);

int get_pixmaps(GtkWidget *widget,
		int which_one,
		GdkPixmap **out_pixmap,
		GdkBitmap **out_mask);

/*
 * This is a hack to add pixmaps in column titles.
 * Its a hack because it assumes things about GTK that are not exposed.
 */
int hack_clist_set_column_title_pixmap(GtkWidget *clist,
				       int column,
				       GtkWidget *pixmapwid);

int check_hidden_dir();

int read_gtkrc_file();

int get_home_file_name(char *file, char *full_name, int max_size);

FILE *jp_open_home_file(char *filename, char *mode);

int raw_header_to_header(RawDBHeader *rdbh, DBHeader *dbh);

int find_next_offset(mem_rec_header *mem_rh, long fpos,
		     unsigned int *next_offset,
		     unsigned char *attrib, unsigned int *unique_id);

/*The VP is a pointer to MyAddress, MyAppointment, etc. */
int delete_pc_record(AppType app_type, void *VP, int flag);

void get_month_info(int month, int day, int year, int *dow, int *ndim);

void get_this_month_info(int *dow, int *ndim);

time_t pilot_time_to_unix_time (unsigned long raw_time);

unsigned long unix_time_to_pilot_time (time_t t);

unsigned int bytes_to_bin(unsigned char *bytes, unsigned int num_bytes);

void free_mem_rec_header(mem_rec_header **mem_rh);

void print_string(char *str, int len);

int get_app_info(char *DB_name, unsigned char **buf, int *buf_size);

int cleanup_pc_files();

int setup_sync(unsigned int flags);

/* Found in jpilot.c */
void cb_sync(GtkWidget *widget, unsigned int flags);
void get_compile_options(char *string, int len);

/* Returns the number of the button that was pressed */
int dialog_generic(GtkWindow *main_window,
		   int w, int h,
		   char *title, char *frame_text,
		   char *text, int nob, char *button_text[]);

/*
 * Widget must be some widget used to get the main window from.
 * The main window passed in would be fastest.
 * This just calls dialog_generic with an OK button.
 */
int dialog_generic_ok(GtkWidget *widget,
		      char *title, char *frame_text, char *text);

/*
 * Widget must be some widget used to get the main window from.
 * The main window passed in would be fastest.
 * changed is MODIFY_FLAG, or NEW_FLAG
 */
int dialog_save_changed_record(GtkWidget *widget, int changed);

/* mon 0-11
 * day 1-31
 * year (year - 1900)
 * This function will bring up the cal at mon, day, year
 * After a new date is selected it will return mon, day, year
 */
int cal_dialog(GtkWindow *main_window,
	       const char *title, int monday_is_fdow,
	       int *mon, int *day, int *year);

int clist_find_id(GtkWidget *clist,
		  unsigned int unique_id,
		  int *found_at,
		  int *total_count);

int check_copy_DBs_to_home();

int jp_copy_file(char *src, char *dest);

/*search_gui.c */
void cb_search_gui(GtkWidget *widget, gpointer data);

/*install_gui.c */
int install_gui(int w, int h, int x, int y);
/*install_gui.c */
//gtk1 int install_append_line(char *line);
int install_append_line(const char *line);

/*import_gui.c */
void import_gui(GtkWidget *main_window, GtkWidget *main_pane,
		char *type_desc[], int type_int[],
		int (*import_callback)(GtkWidget *parent_window,
				       const char *file_path, int type));
int import_record_ask(GtkWidget *main_window, GtkWidget *pane,
		      char *text, struct CategoryAppInfo *cai,
		      char *old_cat_name,
		      int priv, int suggested_cat_num, int *new_cat_num);

/* could be in dat.h or import.h */
#define DAT_TYPE_INTEGER 1
#define DAT_TYPE_CSTRING 5
#define DAT_TYPE_DATE    3
#define DAT_TYPE_BOOLEAN 6
#define DAT_TYPE_REPEAT  8

/* Returns a dat type, or 0 */
int dat_check_if_dat_file(FILE *in);
int dat_get_appointments(FILE *in, AppointmentList **alist, struct CategoryAppInfo *ai);
int dat_get_addresses(FILE *in, AddressList **addrlist, struct CategoryAppInfo *ai);
int dat_get_todos(FILE *in, ToDoList **todolist, struct CategoryAppInfo *ai);
int dat_get_memos(FILE *in, MemoList **memolist, struct CategoryAppInfo *ai);

/*weekview_gui.c */
void cb_weekview_gui(GtkWidget *widget, gpointer data);

/*monthview_gui.c */
void cb_monthview_gui(GtkWidget *widget, gpointer data);

void free_search_record_list(struct search_record **sr);


int datebook_gui(GtkWidget *vbox, GtkWidget *hbox);
int address_gui(GtkWidget *vbox, GtkWidget *hbox);
int todo_gui(GtkWidget *vbox, GtkWidget *hbox);
int memo_gui(GtkWidget *vbox, GtkWidget *hbox);

int datebook_gui_cleanup();
int address_gui_cleanup();
int todo_gui_cleanup();
int memo_gui_cleanup();

/*
 * Copy src string into dest while escaping quotes with double quotes.
 * dest could be as long as strlen(src)*2.
 * Return value is the number of chars written to dest.
 */
int str_to_csv_str(char *dest, char *src);

/*
 * Do the opposite of str_to_csv_str, unescaping double quotes.
 * Return value is the number of chars written to dest.
 */
int csv_str_to_str(char *dest, char *src);

/*
 * Copy src string into dest while escaping carraige returns,
 * backslashes, commas and semicolons.  Also do line wrapping.
 * dest could be as long as strlen(src) * 2 + strlen(src) / 30.
 * Return value is the number of chars written to dest.
 */
int str_to_ical_str(char *, int, char *);

/*
 * Same as str_to_ical_str() except doesn't escape semicolons.
 */
int str_to_vcard_str(char *, int, char *);

/*
 * Parse the string and replace CR and LFs with spaces
 */
void remove_cr_lfs(char *str);

/*
 * Parse the string and replace CR and LFs with spaces
 * a null is written if len is reached
 */
void lstrncpy_remove_cr_lfs(char *dest, char *src, int len);

/*
 * Output LDIF format (RFC 2849) to file.
 * Name is name of item (e.g. "cn")
 * fmt ... is like printf.
 */
void ldif_out(FILE *f, char *name, char *fmt, ...);

/*
 * Output base64-encoded string to file
 */
void base64_out(FILE *, char *);

void cleanup_path(char *path);

int add_days_to_date(struct tm *date, int n);

int sub_days_from_date(struct tm *date, int n);

int add_months_to_date(struct tm *date, int n);

int sub_months_from_date(struct tm *date, int n);

int add_years_to_date(struct tm *date, int n);

int sub_years_from_date(struct tm *date, int n);

/*from jpilot.c */
void cb_app_button(GtkWidget *widget, gpointer data);

void call_plugin_gui(int number, int unique_id);

/*datebook_gui */
int datebook_refresh(int first);

/*address_gui */
int address_refresh();
int address_cycle_cat();
 
/*todo_gui */
int todo_refresh();
int todo_cycle_cat();

/*memo_gui */
int memo_refresh();
int memo_cycle_cat();

/* monthview_gui */
void monthview_gui(struct tm *date);

/* weekview_gui */
void weekview_gui(struct tm *date_in);

/* dialer.c */
int dialog_dial(GtkWindow *main_window, char *string, char *ext);

/* These are in utils.c for now */
/*
 * DB_name should be without filename ext, e.g. MemoDB
 * num is the number of records counted returned.
 */
int pdb_file_count_recs(char *DB_name, int *num);
/*
 * DB_name should be without filename ext, e.g. MemoDB
 * uid_in the the unique ID to remove from the pdb file
 */
int pdb_file_delete_record_by_id(char *DB_name, pi_uid_t uid_in);
/*
 * DB_name should be without filename ext, e.g. MemoDB
 * uid_in the the unique ID to modify from the pdb file
 * the other parameters are set in the pdb file for this record.
 */
int pdb_file_modify_record(char *DB_name, void *record_in, int size_in,
			   int attr_in, int cat_in, pi_uid_t uid_in);
/*
 * DB_name should be without filename ext, e.g. MemoDB
 * uid is unique id in
 * bufp is a copy of the raw record (unpacked) and should be freed by caller
 * sizep is size of bufp returned
 * idxp is the index in the file rec was found
 * attrp is the attributes
 * catp is the category (index)
 */
int pdb_file_read_record_by_id(char *DB_name, 
			       pi_uid_t uid,
			       void **bufp, int *sizep, int *idxp,
			       int *attrp, int * catp);
/*
 * DB_name should be without filename ext, e.g. MemoDB
 * bufp is the packed app info block
 * size_in is the size of bufp
 */
int pdb_file_write_app_block(char *DB_name, void *bufp, int size_in);


/* category.c */
/*
 * widget is a widget inside the main window used to get main window handle
 * db_name should be without filename ext, e.g. MemoDB
 * cai is the category app info.  This should be unpacked by the user since
 * category unpack functions are database specific.
 */
int edit_cats(GtkWidget *widget, char *db_name, struct CategoryAppInfo *cai);
/*
 * This changes every record with index old_index and changes it to new_index
 * returns the number of record's categories changed.
 */
int pdb_file_change_indexes(char *DB_name, int old_index, int new_index);
int edit_cats_change_cats_pc3(char *DB_name, int old_cat,
			      int new_cat);
int edit_cats_swap_cats_pc3(char *DB_name, int old_cat,
			    int new_cat);
int edit_cats_change_cats_pdb(char *DB_name, int old_cat, int new_cat);

  
int make_category_menu(GtkWidget **category_menu,
		       GtkWidget **cat_menu_item,
		       struct sorted_cats *sort_l,
		       void (*selection_callback)
		       (GtkWidget *item, int selection),
		       int add_an_all_item);

void multibyte_safe_strncpy(char *dst, char *src, size_t len);
char *multibyte_safe_memccpy(char *dst, const char *src, int c, size_t len);

/*************************************
 * convert char code 
 *************************************/
#define charset_j2p(buf, max_len, char_set)  {\
	if (char_set == CHAR_SET_JAPANESE) Euc2Sjis(buf, max_len);\
	if (char_set == CHAR_SET_1250) Lat2Win(buf,max_len);\
	if (char_set == CHAR_SET_1251) koi8_to_win1251(buf, max_len);\
	if (char_set == CHAR_SET_1251_B) win1251_to_koi8(buf, max_len);\
        if (char_set == CHAR_SET_1250UTF) UTF2Win(buf,max_len);}
#define charset_p2j(buf, max_len, char_set) {\
        if (char_set == CHAR_SET_JAPANESE) Sjis2Euc(buf, max_len);\
        if (char_set == CHAR_SET_1250) Win2Lat(buf,max_len);\
        if (char_set == CHAR_SET_1251) win1251_to_koi8(buf, max_len);\
        if (char_set == CHAR_SET_1251_B) koi8_to_win1251(buf, max_len);\
        if (char_set == CHAR_SET_1250UTF) Win2UTF(buf,max_len);}

void jp_charset_p2j(unsigned char *buf, int max_len);
void jp_charset_j2p(unsigned char *buf, int max_len);

#endif
