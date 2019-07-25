#include "../../lib_files/std_lib_facilities.h"
struct God {
	God(const string& n, const string& m, const string& v, const string& w)
		:name{ n }, mythology{ m }, vehicle{ v }, weapon{ w }{}

	string name;
	string mythology;
	string vehicle;
	string weapon;
};

class Link {
public:
	Link(God g, Link* p = nullptr, Link* s = nullptr)
		:god{ g }, prev{ p }, succ{ s }{}

	God god;
	
	Link* insert(Link* n);
	Link* add(Link* n);		//insert n after p; return n
	Link* add_ordered(Link* n);
	Link* erase();
	Link* find(const string& s);
	const Link* find(const string& s) const;
	Link* advance(int n);
	
	Link* next() const { return succ; }
	Link* previous() const { return prev; }
private:
	Link* prev;
	Link* succ;
};
Link* Link::insert(Link* n)		//insert n before p(this); return n
{
	if (!n) return this;
	
	n->succ = this;					//p(this) comes after n
	if (prev) prev->succ = n;		//if not a nullptr p(this)'s predecessor successor becomes n
	n->prev = prev;					//p(this)'s predecessor becomes n's predecessor
	prev = n;						//n becomes p(this)'s predecessor
	return n;
}

Link* Link::add(Link* n)		//insert n after p(this); return p
{
	if (!n) return this;
	
	n->prev = this;					//n comes after p(this)
	if (succ) succ->prev = n;		//if not a nullptr p(this)'s succesor predecessor becomes n
	n->succ = succ;					//p(this)'s succesor becomes n's successor
	succ = n;						//n becomes p(this)'s successor
	return n;
}

Link* Link::add_ordered(Link* n)
{
	if (!n) return this;
	Link* p = this;
	bool before = false;
	while (n->god.name < p->god.name) {
		if (!before) before = true;
		if (!p->prev) break;
		else p = p->prev;
	}

	while (p->succ && n->god.name > p->god.name) p = p->succ;

	if (before) {
		cout << static_cast<int>(n->god.name[0]) << " < " << static_cast<int>(p->god.name[0]) << " insert(" << n->god.name << ") before " << p->god.name << "\n";
		p = p->insert(n);
	}
	else {
		cout << static_cast<int>(n->god.name[0]) << " > " << static_cast<int>(p->god.name[0]) << " add(" << n->god.name << ") after " << p->god.name << "\n";
		p = p->add(n);
	}

	return p;
}

Link* Link::erase()		//remove p from the list, return p's successor
{
	Link* p = this;
	
	if (p->succ) p->succ->prev = p->prev;	//p's succesor predecessor becomes p's predecessor
	if (p->prev) p->prev->succ = p->succ;	//p's predecessor succesor becomes p's succesor
	return p->succ;
}

Link* Link::find(const string& s)	//find s in list
{
	Link* p = this;
	while (p) {
		if (p->god.name == s) return p;
		p = p->succ;			
	}
	return nullptr;					//s not found 
}

const Link* Link::find(const string& s) const
{
	const Link* p = this;
	while (this) {
		if (p->god.name == s) return p;
		p = p->succ;
	}
	return nullptr;
}

Link* Link::advance(int n)		//advance n i list (negative is backward)
{
	Link* p = this;
	if (0 < n) {
		while (n--) {			//post-increment yelds value before increment as its value
			if (!p->succ) return nullptr;
			p = p->succ;
		}
	}
	else if (n < 0) {
		while (n++) {			//while default is if not 0
			if (!p->prev) return nullptr;
			p = p->prev;
		}
	}
	return p;
}

void print_all(Link* p)
{
	if (!p) return;
	while (p->previous()) p = p->previous();
	
	while (true) {
		cout	<< "\tName: "		<< p->god.name << "\n"
				<< "\tMythology: "	<< p->god.mythology << "\n"
				<< "\tVehicle: "	<< p->god.vehicle << "\n"
				<< "\tWeapon: "		<< p->god.weapon << "\n\n";
		
		if (p->next())p = p->next();
		else break;
	}
	
}

Link* sort_by_myth(Link* n, string s)
{
	while (n->previous()) n = n->previous();
	Link* p = nullptr;
	while (true) {
		if (n->god.mythology == s) {
			cout << n->god.name << " mythology is " << s << "\n";
			if (!p) {
				p = new Link(n->god); 
				cout << "p = new Link(" << n->god.name << ");\n";
			}
			else {
				
				p = p->add_ordered(new Link(n->god));
				cout << " add_ordered(" << p->god.name << ")\n";
				/*print_all(p);*/
			}
		}	
		if (!n->next()) break;  
		n = n->next(); 
		 
		
	}
	return p;
}

void god_list()
{
	cout << "---------Unordered list---------\n";
	Link* godlist = new Link{ God{ "Thor", "Norse", "Cart drawn by two goats", "The hammer Mjolnir" } };
	/*godlist = godlist->add(new Link{ God{ "Odin", "Norse", "The eightlegged horse Sleipnir", "The spear Gungnir" } });
	godlist = godlist->add(new Link{ God{ "Zeus", "Greek", "", "Lightning"  } });
	godlist = godlist->add(new Link{ God{ "Mercury", "Roman", "", "Caduceus staff" } });
	godlist = godlist->add(new Link{ God{ "Jupiter", "Roman", "", "Staff" } });
	godlist = godlist->add(new Link{ God{ "Loki", "Norse", "", "Trickery"  } });
	godlist = godlist->add(new Link{ God{ "Mars", "Roman", "", "Spear" } });
	godlist = godlist->add(new Link{ God{ "Poseidon", "Greek", "", "Storms and earthquakes" } });
	godlist = godlist->add(new Link{ God{ "Athena", "Greek", "", "Spear" } });
	godlist = godlist->add(new Link{ God{ "Hephaistos", "Greek", "", "Hammer" } });
	godlist = godlist->add(new Link{ God{ "Tyr", "Norse", "", "Sword" } });*/
	godlist = godlist->add_ordered(new Link{ God{ "Poseidon", "Greek", "", "Storms and earthquakes" } });
	godlist = godlist->add_ordered(new Link{ God{ "Odin", "Norse", "The eightlegged horse Sleipnir", "The spear Gungnir" } });
	godlist = godlist->add_ordered(new Link{ God{ "Zeus", "Greek", "", "Lightning" } });
	godlist = godlist->add_ordered(new Link{ God{ "Tyr", "Norse", "", "Sword" } }); 
	godlist = godlist->add_ordered(new Link{ God{ "Mercury", "Roman", "", "Caduceus staff" } });
	godlist = godlist->add_ordered(new Link{ God{ "Jupiter", "Roman", "", "Staff" } });
	godlist = godlist->add_ordered(new Link{ God{ "Loki", "Norse", "", "Trickery" } });
	godlist = godlist->add_ordered(new Link{ God{ "Mars", "Roman", "", "Spear" } });
	godlist = godlist->add_ordered(new Link{ God{ "Athena", "Greek", "", "Spear" } });
	godlist = godlist->add_ordered(new Link{ God{ "Hephaistos", "Greek", "", "Hammer" } });

	print_all(godlist);
	/*cout << "---------Ordered list---------\n";
	Link* norse_gods = sort_by_myth(godlist, "Norse");
	Link* greek_gods = sort_by_myth(godlist, "Greek");
	Link* roman_gods = sort_by_myth(godlist, "Roman");
	delete godlist;
	cout << "---------Norse---------\n";
	print_all(norse_gods);
	cout << "---------Greek---------\n";
	print_all(greek_gods);
	cout << "---------Roman---------\n";
	print_all(roman_gods);
	cout << '\n';*/

	/*delete norse_gods;
	delete greek_gods;
	delete roman_gods;*/

}
int main()
try {

	god_list();
	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "exception\n";
}
