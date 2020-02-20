//Team LOOP
//Rajesh Nishma Swasti Sudarshan

#include "movie.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <gtkmm/application.h>

using namespace std;

movietheater::movietheater(){
	std::ifstream inFile;
  std::string line_from_file,intermediate;
  inFile.open("movie.txt");

  if(!inFile.is_open()){
    std::cout<<"Unable to open file";
    exit(1);
  }

  while(!inFile.eof()){
    getline(inFile,line_from_file);
		line.push_back(line_from_file);
    std::stringstream delimit_line(line_from_file);
    getline(delimit_line,intermediate,'.');
    id.push_back(intermediate);

    getline(delimit_line,intermediate,',');
    movie_name.push_back(intermediate);

    getline(delimit_line,intermediate,',');
    show_times.push_back(intermediate);

    getline(delimit_line,intermediate);
    price.push_back(intermediate);
  }
}

void movietheater::deletemovie(const char *file_name, int n){
    ifstream is(file_name);
    ofstream ofs;
    ofs.open("newmovie.txt", ofstream::out);
    char c;
    int line_no = 1;
    while (is.get(c))
    {
        if (c == '\n')
        line_no++;
        if (line_no != n)
            ofs << c;
    }
    ofs.close();
    is.close();
    remove(file_name);
    rename("newmovie.txt", file_name);
}

Person::Person()
{
	resize(200,150);

  image.set("avengers.jpg");
	grid.attach(image,0,0,2,1);
	MANAGER.add_pixlabel("manager.jpg","MANAGER");
	MANAGER.signal_pressed().connect(sigc::mem_fun(*this,&Person::manager_info));
	grid.attach(MANAGER,0,1,1,1);
	CUSTOMER.add_pixlabel("customer.jpg","CUSTOMER");
	CUSTOMER.signal_pressed().connect(sigc::mem_fun(*this,&Person::customer_info));
	grid.attach(CUSTOMER,1,1,1,1);

	exit.add_pixlabel("exit.jpg","EXIT");
	exit.signal_pressed().connect(sigc::mem_fun(*this,&Person::close));
	grid.attach(exit,0,2,2,1);
	grid.show_all();	/*when	done	packing	buttons,	we	show	them*/
	add(grid);

}

Person::~Person()
{}

void Person::manager_info(){
		Manager m;
		Gtk::Main::run(m);
}

void Person::customer_info(){
	int choice=1;
	while(choice){
		customer c(2100);
		choice=c.result;
	switch (choice) {
	case 0:
		Gtk::MessageDialog *myMessageDialog;
		myMessageDialog = new Gtk::MessageDialog{"Are you sure you don't want to watch a movie?"};
		myMessageDialog->run();
		myMessageDialog->close();
		delete myMessageDialog;
		break;
  case 1:
		c.display_showtimes();
		break;

	case 2:
		c.book_ticket();
		break;

	case 3:
	  c.add_money();
		break;

	}
}
}

Manager::Manager():box(Gtk::ORIENTATION_VERTICAL),button_close("Exit"),checkbutton("Visible"),button_send("Send password")
{
		set_size_request(300,	200);
		set_title("---Password---");
		add(box);
		label.set_text("Enter	password:");
		box.pack_start(label);
		entry.set_max_length(50);
		entry.set_text("Enter	password");
		entry.select_region(0,	entry.get_text_length());
		box.pack_start(entry);
		box.pack_start(textbox);
		textbox.pack_start(checkbutton);
		checkbutton.signal_toggled().connect(sigc::mem_fun(*this,
														&Manager::checkbox)	);
		checkbutton.set_active(true);
		button_send.signal_clicked().connect(sigc::mem_fun(*this,
														&Manager::send_value));
		box.pack_start(button_send);
		button_close.signal_clicked().connect(sigc::mem_fun(*this,
														&Manager::close_button));
		box.pack_start(button_close);

		button_close.set_can_default();
	  button_close.grab_default();
	  show_all_children();
}

Manager::~Manager()
{

}

void	Manager::send_value()
{
	password=entry.get_text();
	if(password.compare("ABCD") == 0||password=="abcd")
	{

		Gtk::Window w;
		Gtk::Dialog *dialog = new Gtk::Dialog();
		dialog->set_transient_for(w);
		dialog->set_title("Enter info:");

		dialog->add_button("ADD A MOVIE",1);
		dialog->add_button("DELETE A MOVIE",2);
		dialog->add_button("EXIT",0);

		int res1=dialog->run();
		if(res1==1){
       Add_Movie();
			 Register();
		}

		else if(res1==2){

			delete_window	window;
			Gtk::Main::run(window);
		}
		dialog->close();
		delete dialog;
	}
	else
	{
		Gtk::MessageDialog dialog(*this,"Wrong password",false,Gtk::MESSAGE_INFO);
		dialog.run();
	}
}

void	Manager::checkbox()
{
	entry.set_visibility(checkbutton.get_active());
}

void	Manager::close_button()
{
	close();
}


void Manager::Add_Movie()
{

  Gtk::Window w;
  Gtk::Dialog *dialog=new Gtk::Dialog();
  dialog->set_transient_for(w);
  dialog->set_title("ADD A MOVIE");

  Gtk::Label *label = new Gtk::Label("Enter movie name");
	dialog->get_content_area()->pack_start(*label);
	label->show();

  dialog->add_button("Cancel",	0);
	dialog->add_button("OK",1);

	Gtk::Entry *entry_first = new Gtk::Entry();
	entry_first->set_text("movie_name");
	entry_first->set_max_length(50);
	entry_first->show();
  dialog->get_vbox()->pack_start(*entry_first);

  Gtk::Label *label1 = new Gtk::Label("Enter show times");
	dialog->get_content_area()->pack_start(*label1);
	label1->show();
	Gtk::Entry *entry_second = new Gtk::Entry();
	entry_second->set_text("show times");
	entry_second->set_max_length(50);
	entry_second->show();
  dialog->get_vbox()->pack_start(*entry_second);

  Gtk::Label *label2 = new Gtk::Label("Enter movie id");
	dialog->get_content_area()->pack_start(*label2);
	label2->show();
	Gtk::Entry	*entry_third = new Gtk::Entry();
	entry_third->set_text("id");
	entry_third->set_max_length(50);
	entry_third->show();
  dialog->get_vbox()->pack_start(*entry_third);

  Gtk::Label *label3 = new Gtk::Label("Enter price");
	dialog->get_content_area()->pack_start(*label3);
	label3->show();
	Gtk::Entry	*entry_last = new Gtk::Entry();
	entry_last->set_text("price");
	entry_last->set_max_length(50);
	entry_last->show();
  dialog->get_vbox()->pack_start(*entry_last);

  int result=dialog->run();
  if(result==0){
		hide();
	}
  moviename=entry_first->get_text();
  showtimes=entry_second->get_text();
  num=entry_third->get_text();
  amount=entry_last->get_text();

	std::ofstream outf;
	outf.open("movie.txt",std::ofstream::app);
	outf<<num<<"."<<moviename<<","<<showtimes<<","<<amount<<"\n";



  dialog->close();

  delete	dialog;
  delete	label;
  delete	entry_first;
  delete  entry_second;
  delete  entry_third;
  delete	entry_last;

}

void Manager::Register(){
	Gtk::MessageDialog	dialog(*this,	"Registered Movie!!",false,Gtk::MESSAGE_INFO);
	dialog.set_secondary_text("Movie	name: "+moviename+"\n"+"show times:	"+showtimes+"\nid:	"+num+"\namount:	"+amount);
	dialog.run();
	dialog.close();
}


delete_window::delete_window(){
	set_size_request(500,200);
	label.set_text("Please select the movie:");
	label.set_padding(10,10);
	vbox.pack_start(label);
	set_title("Select a movie");

	r_tree=Gtk::ListStore::create(m_Columns);
	combo.set_model(r_tree);

	Gtk::TreeModel::Row	row	=	*(r_tree->append());
	row[m_Columns.m_col_id]	=1;
	row[m_Columns.m_col_name]	=	r.movie_name[0];
	combo.set_active(row);

 for(int i=1;i<(r.id.size()-1);i++){
	row	=	*(r_tree->append());
	row[m_Columns.m_col_id]	=	i+1;
	row[m_Columns.m_col_name]	=	r.movie_name[i];
}

	combo.pack_start(m_Columns.m_col_id);
	combo.pack_start(m_Columns.m_col_name);
	vbox.pack_start(combo);
	add(vbox);

	combo.signal_changed().connect(	sigc::mem_fun(*this,	&delete_window::choose_delete));
	show_all_children();
}

delete_window::~delete_window()
{
}

void delete_window::choose_delete(){
	Gtk::TreeModel::iterator	iter	=	combo.get_active();
		if(iter)
		{
				Gtk::TreeModel::Row	row	=	*iter;
				if(row)
				{
						select	=	row[m_Columns.m_col_id];
						Glib::ustring	name	=	row[m_Columns.m_col_name];
						Gtk::Window	w;
						Gtk::Dialog	*dialog	=	new	Gtk::Dialog();
						dialog->set_transient_for(w);
						dialog->set_title("Information:");

						Gtk::Label	*label	=	new	Gtk::Label("Are you sure you want to delete "+name+" ?");
						dialog->get_content_area()->pack_start(*label);
					  label->set_padding(20,20);
						label->show();

						dialog->add_button("No",	0);
						dialog->add_button("yes",1);

						int result=dialog->run();

						if(result==1){
							r.deletemovie("movie.txt",select);
							hide();
						}
						dialog->close();
						delete(dialog);
				}
		}
		else
		std::cout	<<	"Invalid..."	<<	std::endl;
}

customer::customer(int wallet)
{
	this->wallet=wallet;
	Gtk::Dialog *menuDialog = Gtk::manage(new Gtk::Dialog());
	menuDialog->set_title("Movie Theater");
	Gtk::Label *menuLabel = Gtk::manage(new Gtk::Label("What do you want to do?"));
	menuDialog->get_content_area()->pack_start(*menuLabel);
	menuLabel->show();
	vector<string> buttons = {"Walk away","Display show times", "Book a ticket", "Add money to wallet"};
	for(int i=0; i<buttons.size(); i++){
		menuDialog->add_button(buttons[i],i);
	}
	menuDialog->set_default_response(0);
	result = menuDialog->run();
	menuDialog->close();
	delete menuDialog;
}

void customer::display_showtimes(){

		GtkWidget *window, *notebook, *label, *label2;
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

		notebook = gtk_notebook_new();
		gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
		for(int i = 0; i < (m.movie_name.size()-1); i += 1)
		{
				string s = "AVAILABLE SHOW TIMES\n";
				s += m.show_times[i];
				label = gtk_label_new(s.c_str());

				s = m.movie_name[i];

				label2 = gtk_label_new(s.c_str());

				gtk_notebook_append_page(GTK_NOTEBOOK(notebook), label, label2);
			}
			gtk_container_add(GTK_CONTAINER(window), notebook);


			gtk_widget_show_all(window);
			gtk_main();

}

void customer::book_ticket()
{
	cout<<wallet;
	Gtk::Dialog *menuDialog = Gtk::manage(new Gtk::Dialog());
	menuDialog->set_title("Movie Theater");
	Gtk::Label *menuLabel = Gtk::manage(new Gtk::Label("Select the movie"));
	menuDialog->get_content_area()->pack_start(*menuLabel);
	menuLabel->show();
	for(int i=0; i<m.movie_name[i].size(); i++){
		menuDialog->add_button(m.movie_name[i],i);
	}
	menuDialog->set_default_response(0);
	result=menuDialog->run();
	menuDialog->close();
	delete menuDialog;

	for(int i=0; i<m.movie_name[i].size(); i++){
		if(result==i){
			sel_movie_name=m.movie_name[i];
			string t=m.show_times[i];
			istringstream ss(t);

      do {
        string word;
        ss >> word;
   		timelist.push_back(word);
    } while (ss);
		}
	}

	Gtk::Dialog *menuDialog1 = Gtk::manage(new Gtk::Dialog());
	menuDialog1->set_title("Movie Theater");
	Gtk::Label *menuLabel1 = Gtk::manage(new Gtk::Label("Select the showtime"));
	menuDialog1->get_content_area()->pack_start(*menuLabel1);
	menuLabel1->show();
	for(int i=0; i<(timelist.size()-1); i++){
		menuDialog1->add_button(timelist[i],i);
	}
	menuDialog1->set_default_response(0);
	result=menuDialog1->run();
	menuDialog1->close();
	delete menuDialog1;
	for(int i=0; i<timelist.size(); i++){
		if(result==i){
			time=timelist[i];
		}
	}

	Gtk::Dialog *Dialog2 = Gtk::manage(new Gtk::Dialog());
	Dialog2->set_title("NUMBER OF TICKETS");
	Gtk::Label *label2 = Gtk::manage(new Gtk::Label("Insert number of tickets: "));
	Dialog2->get_content_area()->pack_start(*label2);
	label2->show();
	Gtk::Entry *Entry = Gtk::manage(new Gtk::Entry());
	Entry->set_text("Insert number of tickets");
	Entry->set_max_length(20);
	Entry->show();
	Dialog2->get_content_area()->pack_start(*Entry);
	std::vector<std::string> buttons = {"OK"};
	for(int i=0; i<buttons.size(); i++){
		Dialog2->add_button(buttons[i],i);
	}
	Dialog2->set_default_response(0);
	int result = Dialog2->run();
	numtickets = std::stoi(Entry->get_text());
	Dialog2->close();
	delete Dialog2;

	Button_window	w;
	Gtk::Main::run(w);

	for(int j=0;j<m.movie_name.size();j++){
		if(sel_movie_name==m.movie_name[j]){
		stringstream sso;
		sso<<m.price[j];
		sso>>pricepermovie;
		}
	}
	total_cost=numtickets*pricepermovie;
	cout<<total_cost;

	if(w.res==1){
		if(wallet<total_cost){
			string message="Insufficient payment...returning your payment\nPlease add money to your wallet.You currently only have $";
			message = message + to_string(wallet);
			Gtk::MessageDialog *m0;
			m0 = new Gtk::MessageDialog{message};
			m0->run();
			m0->close();
		  delete m0;
		}
		else{
			wallet -=total_cost;
			//cout<<wallet;
			string message1 = "Your ticket has been confirmed.\nPlease print your ticket.\nDETAILS:\nMovie name: ";
			message1 = message1+sel_movie_name + "\nShow time: "+time+"\ntotal cost: "+to_string(total_cost)+"\nBooked Seats: ";
			for(int i=0;i<w.booked_seats.size();i++){
				message1 += w.booked_seats[i];
				message1 += " ";
			}
		 Gtk::MessageDialog *m1;
		 m1 = new Gtk::MessageDialog{message1};
		 m1->run();
		 m1->close();
		 delete m1;
		}
	}

}


void customer::add_money()
{
	Gtk::Dialog *Dialog2 = Gtk::manage(new Gtk::Dialog());
	Dialog2->set_title("WELCOME !!");
	Gtk::Label *label2 = Gtk::manage(new Gtk::Label("HOW MUCH MONEY DO U WANT TO ADD ? "));
	Dialog2->get_content_area()->pack_start(*label2);
	label2->show();
	Gtk::Entry *Entry = Gtk::manage(new Gtk::Entry());
	Entry->set_text("$$$$$");
	Entry->set_max_length(20);
	Entry->show();
	Dialog2->get_content_area()->pack_start(*Entry);
	std::vector<std::string> buttons = {"OK"};
	for(int i=0; i<buttons.size(); i++){
		Dialog2->add_button(buttons[i],i);
	}
	Dialog2->set_default_response(0);
	result = Dialog2->run();
	wallet+= stoi(Entry->get_text());

	Dialog2->close();
	delete Dialog2;
}
customer::~customer()
{}

Button_window::Button_window(){
	set_title("SELECT THE SEATS");
	this->set_border_width(20);
	A1.add_label("A1");
	A1.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_1));
	grid.attach(A1,0,0,1,1);
	A2.add_label("A2");
	A2.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_2));
	grid.attach(A2,1,0,1,1);
	A3.add_label("A3");
	A3.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_3));
	grid.attach(A3,2,0,1,1);
	A4.add_label("A4");
	A4.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_4));
	grid.attach(A4,3,0,1,1);
	A5.add_label("A5");
	A5.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_5));
	grid.attach(A5,4,0,1,1);
	B1.add_label("B1");
	B1.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_6));
	grid.attach(B1,0,1,1,1);

	B2.add_label("B2");
	B2.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_7));
	grid.attach(B2,1,1,1,1);

	B3.add_label("B3");
	B3.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_8));
	grid.attach(B3,2,1,1,1);

	B4.add_label("B4");
	B4.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_9));
	grid.attach(B4,3,1,1,1);

	B5.add_label("B5");
	B5.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_10));
	grid.attach(B5,4,1,1,1);

	C1.add_label("C1");
	C1.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_11));
	grid.attach(C1,0,2,1,1);

	C2.add_label("C2");
	C2.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_12));
	grid.attach(C2,1,2,1,1);

	C3.add_label("C3");
	C3.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_13));
	grid.attach(C3,2,2,1,1);

	C4.add_label("C4");
	C4.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_14));
	grid.attach(C4,3,2,1,1);

	C5.add_label("C5");
	C5.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_15));
	grid.attach(C5,4,2,1,1);

	D1.add_label("D1");
	D1.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_16));
	grid.attach(D1,0,3,1,1);

	D2.add_label("D2");
	D2.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_17));
	grid.attach(D2,1,3,1,1);

	D3.add_label("D3");
	D3.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_18));
	grid.attach(D3,2,3,1,1);

	D4.add_label("D4");
	D4.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_19));
	grid.attach(D4,3,3,1,1);

	D5.add_label("D5");
	D5.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_20));
	grid.attach(D5,4,3,1,1);

	Confirm.add_label("Confirm");
	Confirm.signal_clicked().connect(sigc::mem_fun(*this,&Button_window::on_button_21));
	grid.attach(Confirm,0,4,3,1);

	add(grid);
	grid.show_all();
}

Button_window::~Button_window()
{}
void	Button_window::on_button_1()
{
	booked_seats.push_back("A1");
}
void	Button_window::on_button_2()
{
	booked_seats.push_back("A2");
}
void	Button_window::on_button_3()
{
	booked_seats.push_back("A3");
}
void	Button_window::on_button_4()
{
	booked_seats.push_back("A4");
}
void	Button_window::on_button_5()
{
	booked_seats.push_back("A5");
}
void	Button_window::on_button_6()
{
	booked_seats.push_back("B1");
}
void	Button_window::on_button_7()
{
	booked_seats.push_back("B2");
}
void	Button_window::on_button_8()
{
	booked_seats.push_back("B3");
}
void	Button_window::on_button_9()
{
	booked_seats.push_back("B4");
}
void	Button_window::on_button_10()
{
	booked_seats.push_back("B5");
}
void	Button_window::on_button_11()
{
	booked_seats.push_back("C1");
}
void	Button_window::on_button_12()
{
	booked_seats.push_back("C2");
}
void	Button_window::on_button_13()
{
	booked_seats.push_back("C3");
}
void	Button_window::on_button_14()
{
	booked_seats.push_back("C4");
}
void	Button_window::on_button_15()
{
	booked_seats.push_back("C5");
}
void	Button_window::on_button_16()
{
	booked_seats.push_back("D1");
}
void	Button_window::on_button_17()
{
	booked_seats.push_back("D2");
}
void	Button_window::on_button_18()
{
	booked_seats.push_back("D3");
}
void	Button_window::on_button_19()
{
	booked_seats.push_back("D4");
}
void	Button_window::on_button_20()
{
	booked_seats.push_back("D5");
}
void	Button_window::on_button_21()
{
	res=1;
	hide();
}
