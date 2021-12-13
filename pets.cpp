#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
using namespace std;
int main()
{
	multimap <string, string>  petname,ownertype,namepet,typeowner;
	multimap <string, int> agetype;
	set<string> owners,types;
	multiset<string> oset,tset;
	ostringstream o,ost;
	ifstream input;
	input.open("input.txt");
	bool err = 1;
	string s, t, u, v, str,os,st;
	int w;
	while (getline(input, s, ','))
	{
		o.str("");
		ost.str("");
		getline(input, t, ',');
        	getline(input, u, ',');
	    	getline(input, v);
		w=stoi(v);
		o << t << u;
		os = o.str();
		ost << s << t;
		st = ost.str();
		oset.insert(os);
		tset.insert(st);
		owners.insert(s);
		types.insert(t);
		agetype.insert(make_pair(t, w));
		if (oset.count(os) == 1)
		{
			petname.insert(make_pair(u, t));
			namepet.insert(make_pair(t, u));
		}
		if (tset.count(st) == 1)
		{
			ownertype.insert(make_pair(s, t));
			typeowner.insert(make_pair(t, s));
		}
	}
	pair <multimap<string, string>::iterator, multimap<string, string>::iterator> ret;
	pair <multimap<string, int>::iterator, multimap<string, int>::iterator> r;
	
	int menu;
	cout << "1 count species of animals each owner has\n2 owners and names by species\n3 count species of animals for a specific name\n4 oldest and youngest of every species\n5 to quit\n";
	do {
		int max = -1;
		int min = 999999;
		cin >> menu;
		switch (menu)
		{
		case 1:
			for (set<string>::iterator its = owners.begin(); its !=owners.end() ; its++)
			{
				string e(*its);
				cout << e << " has " << ownertype.count(e)<<" different species"<<endl;
			}
			break;
		case 2:
			cout << "Enter pet species\n";
			cin >> str;
			ret = typeowner.equal_range(str);
			cout << str<<" owners:";
			for (multimap<string, string>::iterator itis = ret.first; itis != ret.second; ++itis)
			{
				err = 0;
				std::cout << ' ' << itis->second;
			}
			cout << '\n';
			ret = namepet.equal_range(str);
			cout << str << " names:";
			for (multimap<string, string>::iterator itis = ret.first; itis != ret.second; ++itis)
				cout << ' ' << itis->second;
			cout << '\n';
			if (err == 1)
			{
				cout << str << "s don't exist\n";
			}
			break;
		case 3:
			cout << "Enter pet name\n";
		    cin>>str;
			cout << petname.count(str) <<" species of animals named "<<str<< endl;
			if (petname.count(str) == 0)
			{
				cout << "An unpopular name\n";
			}
			break;
		case 4:
			for (set<string>::iterator its = types.begin(); its != types.end(); its++)
			{
                string e(*its);
				cout << e<<":";
				r = agetype.equal_range(e);
				for (multimap<string, int>::iterator itis = r.first; itis != r.second; ++itis)
				{
					int z = itis->second;
					if (z < min)
					{
						min = z;
					}
					if (z > max)
					{
						max = z;
					}
				}
				cout << " oldest is "<<max<< ", youngest is " <<min<< endl;
				max = -1;
				min = 99999;
			}
			break;
		case 5:
			cout << "Program ended\n";
			break;
		default:
			cout << "Invalid input, try again\n";
			cin.clear();
			cin.get();
			break;
		}
	}
	while (menu != 5);
	return 0;
}
