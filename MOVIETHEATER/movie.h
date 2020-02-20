//Team LOOP
//Rajesh Nishma Swasti Sudarshan
#ifndef MOVIE_H
#define MOVIE_H

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <string>
#include <vector>


using namespace std;
class movietheater{
public:
	vector<string> line;
	vector<string> id;
	vector<string> movie_name;
	vector<string> show_times;
	vector<string> price;

	movietheater();

	void deletemovie(const char *file_name, int n);
};


class Person:public Gtk::Window
{
	public:

		Person();
		virtual ~Person();

	protected:
		void manager_info();
		void customer_info();

		Gtk::Image image;
		Gtk::Button MANAGER;
   	Gtk::Button	CUSTOMER;
		Gtk::Button	exit;
		Gtk::Grid		grid;
};

class customer:public Gtk::Window{
private:
	movietheater m;

public:
	customer(int wallet);
	virtual ~customer();
	void display_showtimes();
	void book_ticket();
	void add_money();
	int wallet;
	int moneyadd;
	vector<string> timelist;
	string sel_movie_name;
	int pricepermovie;
	string time;
	int numtickets;
	int total_cost;
	int result;

};

class Manager:public Gtk::Window
{
	public:

		string moviename;
		string showtimes;
		string num;
	  string amount;


		string password;
		Manager(string filename);
		Manager();
		virtual ~Manager();
		void on_button_clicked();
    void Add_Movie();
		void Register();
		void Delete_Movie();
		void read_file();

	protected:
		void checkbox();
		void send_value();
		void close_button();
		Gtk::Box textbox;
		Gtk::Label label;
		Gtk::Box box;
		Gtk::Entry entry;
		Gtk::Button button_close,button_send;
		Gtk::CheckButton checkbutton;
};

class delete_window: public Gtk::Window{
public:
	movietheater r;
	delete_window();
	virtual ~delete_window();
	int select;

protected:
	void choose_delete();

	class Columns:public Gtk::TreeModel::ColumnRecord{
	public:

		Columns()
		{
			add(m_col_id);
			add(m_col_name);
		}

		Gtk::TreeModelColumn<int> m_col_id;
		Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	};

	Columns m_Columns;

	Gtk::Image image;
	Gtk::VBox vbox;
	Gtk::Label label;
	Gtk::ComboBox combo;
	Glib::RefPtr<Gtk::ListStore> r_tree;
};

class	Button_window	:	public	Gtk::Window
{
public:
	Button_window();
	virtual ~Button_window();
	vector<string> booked_seats;
	int res;
protected:
	void on_button_1();
	void on_button_2();
	void on_button_3();
	void on_button_4();
	void on_button_5();
	void on_button_6();
	void on_button_7();
	void on_button_8();
	void on_button_9();
	void on_button_10();
	void on_button_11();
	void on_button_12();
	void on_button_13();
	void on_button_14();
	void on_button_15();
	void on_button_16();
	void on_button_17();
	void on_button_18();
	void on_button_19();
	void on_button_20();
	void on_button_21();
	Gtk::Button	A1,A2,A3,A4,A5,B1,B2,B3,B4,B5,C1,C2,C3,C4,C5,D1,D2,D3,D4,D5;
	Gtk::Button Confirm;
	Gtk::Grid		grid;
};
#endif
