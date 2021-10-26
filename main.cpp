/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:48:53 by tvachera          #+#    #+#             */
/*   Updated: 2021/10/26 21:47:10 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#define C_YELLOW "\e[33m"
#define C_RESET "\e[0m"
#define IT_TAB_SIZE 10

#ifndef FT
# define FT ft
# define LIB 1
#endif

#if LIB == 1
# include "iterator.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
# include "stack.hpp"
# include "vector.hpp"
# include "map.hpp"
# include "set.hpp"
#else
# include <iterator>
# include <type_traits>
# include <algorithm>
# include <utility>
# include <stack>
# include <vector>
# include <map>
# include <set>
#endif

#include "btree.hpp"

template <typename T>
typename FT::enable_if<FT::is_integral<T>::value, bool>::type	is_odd(T i)
{
	return (bool(i % 2));
}

bool mypredicate(int i, int j)
{
	return (i == j);
}

bool mycomp (char c1, char c2)
{
	return (std::tolower(c1) < std::tolower(c2));
}

bool fncomp(char lhs, char rhs)
{
	return (lhs < rhs);
}

bool fncomp(int lhs, int rhs)
{
	return (lhs < rhs);
}

struct classcomp
{
  	bool operator() (const char& lhs, const char& rhs) const
  	{
		return (lhs < rhs);
	}
  	bool operator() (const int& lhs, const int& rhs) const
  	{
		return (lhs < rhs);
	}
};

int main(void)
{
	std::cout << C_YELLOW << "\t\tREVERSE ITERATORS TESTS" << C_RESET << std::endl;
	{	// REVERSE ITERATOR TESTS
		FT::vector<int> myvector;
		typedef FT::vector<int>::iterator iter_type;

		for (int i = 0; i < 10; i++)
			myvector.push_back(i);
		iter_type	from(myvector.begin());
		iter_type	until(myvector.end());
		FT::reverse_iterator<iter_type> rev_from(until);
		FT::reverse_iterator<iter_type> rev_until(from);
		std::cout << "distance: " << FT::distance(rev_from, rev_until) << std::endl;
		while (rev_from != rev_until)
			std::cout << ' ' << *rev_from++;
		std::cout << std::endl;
		FT::reverse_iterator<iter_type> rev_from2(until);
		size_t	i = 0;
		while (i < IT_TAB_SIZE)
		{
			std::cout << ' ' << rev_from2[i];
			i++;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << C_YELLOW << "\t\tENABLE_IF & IS_INTEGRAL TESTS" << C_RESET << std::endl;
	{	// ENABLE_IF & IS_INTEGRAL TESTS
		short int	i = 1; // does not compile if type of i is not integral

		std::cout << std::boolalpha;
		std::cout << "i is odd: " << is_odd(i) << std::endl;
		std::cout << "is_integral:" << std::endl;
		std::cout << "char: " << FT::is_integral<char>::value << std::endl;
		std::cout << "int: " << FT::is_integral<int>::value << std::endl;
		std::cout << "float: " << FT::is_integral<float>::value << std::endl;
	}
	std::cout << std::endl << C_YELLOW << "\t\tEQUAL TESTS" << C_RESET << std::endl;
	{	// EQUAL TESTS
		int 				myints[] = {20, 40, 60, 80, 100};
		FT::vector<int>		myvector(myints, myints+5);

		if (FT::equal (myvector.begin(), myvector.end(), myints))
			std::cout << "The contents of both sequences are equal" << std::endl;
		else
			std::cout << "The contents of both sequences differ" << std::endl;
  		myvector[3]=81;
		if (FT::equal (myvector.begin(), myvector.end(), myints, mypredicate))
			std::cout << "The contents of both sequences are equal" << std::endl;
		else
			std::cout << "The contents of both sequences differ" << std::endl;
	}
	std::cout << std::endl << C_YELLOW << "\t\tLEXICOGRAPHICAL_COMPARE TESTS" << C_RESET << std::endl;
	{	// LEXICOGRAPHICAL_COMPARE TEST
		char foo[] = "Apple";
		char bar[] = "apartment";

		std::cout << std::boolalpha;
		std::cout << "Comparing \"" << foo << "\" and \"" << bar << "\" lexicographically:" << std::endl;
		std::cout << "Using default comparison (operator<): ";
		std::cout << FT::lexicographical_compare(foo, foo + 5, bar, bar + 9) << std::endl;
		std::cout << "Using mycomp as comparison object: ";
		std::cout << FT::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp) << std::endl;
	}
	std::cout << std::endl << C_YELLOW << "\t\tPAIR CLASS & MAKE_PAIR TESTS" << C_RESET << std::endl;
	{
		FT::pair<std::string,double>	product1;
		FT::pair<std::string,double>	product2("tomatoes", 2.30);
		FT::pair<std::string,double>	product3(product2);
		FT::pair<int,char>				foo (10, 'z');
		FT::pair<int,char>				bar (90, 'a');

		product1 = FT::make_pair(std::string("lightbulbs"), 0.99);
		product2.first = "shoes";
		product2.second = 39.90;
		std::cout << "The price of " << product1.first << " is $" << product1.second << std::endl;
		std::cout << "The price of " << product2.first << " is $" << product2.second << std::endl;
		std::cout << "The price of " << product3.first << " is $" << product3.second << std::endl;
		if (foo == bar)
			std::cout << "foo and bar are equal" << std::endl;
		if (foo != bar)
			std::cout << "foo and bar are not equal" << std::endl;
		if (foo < bar)
			std::cout << "foo is less than bar" << std::endl;
		if (foo > bar)
			std::cout << "foo is greater than bar" << std::endl;
  		if (foo <= bar)
		  	std::cout << "foo is less than or equal to bar" << std::endl;
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar" << std::endl;
	}
	std::cout << std::endl << C_YELLOW << "\t\tSTACK TESTS" << C_RESET << std::endl;
	{
		FT::stack<int>						first;
		FT::stack<int, FT::vector<int> >	second(FT::vector<int>(10, 20));
		FT::stack<int, FT::vector<int> >	third(FT::vector<int>(10, 42));

		std::cout << "size of first: " << first.size() << std::endl;
		std::cout << "size of second: " << second.size() << std::endl;
		std::cout << std::boolalpha;
		if (first.empty())
			std::cout << "first is empty. Cannot pop." << std::endl;
		else
		{
			std::cout << "first is not empty. Let's pop it." << std::endl;
			first.pop();
			std::cout << "size of first after pop: " << first.size() << std::endl;
		}
		if (second.empty())
			std::cout << "Second is empty. Cannot pop." << std::endl;
		else
		{
			std::cout << "Second is not empty. Let's pop it." << std::endl;
			second.pop();
			std::cout << "size of second after pop: " << second.size() << std::endl;
		}
		std::cout << "push 42 in both stacks..." << std::endl;
		first.push(42);
		second.push(42);
		std::cout << "first.top() is now " << first.top() << std::endl;
		std::cout << "second.top() is now " << second.top() << std::endl;
		if (second > third)
			std::cout << "second > third." << std::endl;
		if (second < third)
			std::cout << "second < third." << std::endl;
		if (second == third)
			std::cout << "second == third." << std::endl;
		if (second != third)
			std::cout << "second != third." << std::endl;
	}
	std::cout << std::endl << C_YELLOW << "\t\tVECTOR TESTS" << C_RESET << std::endl;
	{
		std::cout << std::endl << C_YELLOW << "VECTOR CONSTRUCTORS" << C_RESET << std::endl;
		{
  			FT::vector<int> first;                                // empty vector of ints
  			FT::vector<int> second (4,100);                       // four ints with value 100
  			FT::vector<int> third (second.begin(),second.end());  // iterating through second
  			FT::vector<int> fourth (third);                       // a copy of third

  			int myints[] = {16,2,77,29};
 			FT::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
  			std::cout << "The contents of fifth are:";
  			for (FT::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
   				std::cout << ' ' << *it;
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::ASSIGN" << C_RESET << std::endl;
		{
			FT::vector<int> first;
		  	FT::vector<int> second;
		  	FT::vector<int> third;

			first.assign (7,100);             // 7 ints with a value of 100
	  		FT::vector<int>::iterator it;
	  		it=first.begin()+1;
  			second.assign (it,first.end()-1); // the 5 central values of first
  			int myints[] = {1776,7,4};
  			third.assign (myints,myints+3);   // assigning from array.
  			std::cout << "Size of first: " << int (first.size()) << '\n';
  			std::cout << "Size of second: " << int (second.size()) << '\n';
  			std::cout << "Size of third: " << int (third.size()) << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::AT" << C_RESET << std::endl;
		{
			FT::vector<int> myvector (10);   // 10 zero-initialized ints

  			for (unsigned i=0; i<myvector.size(); i++)
  				myvector.at(i)=i;
			std::cout << "myvector contains:";
  			for (unsigned i=0; i<myvector.size(); i++)
    			std::cout << ' ' << myvector.at(i);
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::BACK" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

 			myvector.push_back(10);
			while (myvector.back() != 0)
  				myvector.push_back ( myvector.back() -1 );
  			std::cout << "myvector contains:";
  			for (unsigned i=0; i<myvector.size() ; i++)
    			std::cout << ' ' << myvector[i];
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::FRONT" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

			myvector.push_back(78);
 			std::cout << "myvector.front() is " << myvector.front() << '\n';
			myvector.push_back(16);
			myvector.front() -= myvector.back();
 			std::cout << "myvector.front() is now " << myvector.front() << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::BEGIN" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

 			myvector.push_back(10);
  			while (myvector.back() != 0)
  				myvector.push_back(myvector.back() -1);
  			std::cout << "myvector contains:";
  			for (unsigned i = 0; i < myvector.size() ; i++)
  				std::cout << ' ' << myvector[i];
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::END" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

			for (int i=1; i<=5; i++)
				myvector.push_back(i);
			std::cout << "myvector contains:";
			for (FT::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RBEGIN" << C_RESET << std::endl;
		{
			FT::vector<int> myvector (5);  // 5 default-constructed ints

			int i=0;
			FT::vector<int>::reverse_iterator rit = myvector.rbegin();
			for (; rit!= myvector.rend(); ++rit)
				*rit = ++i;
			std::cout << "myvector contains:";
			for (FT::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::REND" << C_RESET << std::endl;
		{
			 FT::vector<int> myvector (5);  // 5 default-constructed ints

			FT::vector<int>::reverse_iterator rit = myvector.rbegin();
			int i=0;
			for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
				*rit = ++i;
			std::cout << "myvector contains:";
			for (FT::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::CAPACITY VECTOR::SIZE VECTOR::MAX_SIZE" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

  			for (int i=0; i<100; i++)
			  	myvector.push_back(i);
  			std::cout << "size: " << (int) myvector.size() << '\n';
  			std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  			std::cout << "max_size: " << (int) myvector.max_size() << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::CLEAR" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;
			myvector.push_back (100);
			myvector.push_back (200);
			myvector.push_back (300);

			std::cout << "myvector contains before clear:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			myvector.clear();
			std::cout << "myvector contains after clear:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			myvector.push_back (1101);
			myvector.push_back (2202);
			std::cout << "myvector contains:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::EMPTY" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;
  			int sum(0);

			std::cout << std::boolalpha;
			std::cout << myvector.empty() << std::endl;
			for (int i=1;i<=10;i++)
				myvector.push_back(i);
			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}
			std::cout << "total: " << sum << '\n';
			std::cout << myvector.empty() << std::endl;
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::ERASE" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

			for (int i=1; i<=10; i++)
				myvector.push_back(i);
			std::cout << "myvector contains before erase:";
			for (unsigned i=0; i<myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			myvector.erase (myvector.begin()+5);
			myvector.erase (myvector.begin(),myvector.begin()+3);
			std::cout << "myvector contains after erase:";
			for (unsigned i=0; i<myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::GET_ALLOCATOR" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;
			int * p;
			unsigned int i;

			p = myvector.get_allocator().allocate(5);
			for (i=0; i<5; i++)
				myvector.get_allocator().construct(&p[i],i);
			std::cout << "The allocated array contains:";
			for (i=0; i<5; i++)
				std::cout << ' ' << p[i];
			std::cout << '\n';
			for (i=0; i<5; i++)
				myvector.get_allocator().destroy(&p[i]);
			myvector.get_allocator().deallocate(p,5);
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::INSERT" << C_RESET << std::endl;
		{
			FT::vector<int> myvector (3,100);
			FT::vector<int>::iterator it;

			it = myvector.begin();
			it = myvector.insert( it , 200 );
			myvector.insert(it,2,300);
			it = myvector.begin();
			FT::vector<int> anothervector (2,400);
			myvector.insert(it+2,anothervector.begin(),anothervector.end());
			int myarray [] = { 501,502,503 };
			myvector.insert(myvector.begin(), myarray, myarray+3);
			std::cout << "myvector contains:";
			for (it=myvector.begin(); it<myvector.end(); it++)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::OPERATOR=" << C_RESET << std::endl;
		{
			FT::vector<int> foo (3,0);
			FT::vector<int> bar (5,0);

			bar = foo;
			foo = FT::vector<int>();
			std::cout << "Size of foo: " << int(foo.size()) << '\n';
			std::cout << "Size of bar: " << int(bar.size()) << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::OPERATOR[]" << C_RESET << std::endl;
		{
			FT::vector<int> myvector (10);   // 10 zero-initialized elements
			FT::vector<int>::size_type sz = myvector.size();

			for (unsigned i=0; i<sz; i++)
				myvector[i]=i;
			for (unsigned i=0; i<sz/2; i++)
			{
				int temp;
				temp = myvector[sz-1-i];
				myvector[sz-1-i]=myvector[i];
				myvector[i]=temp;
			}
			std::cout << "myvector contains:";
			for (unsigned i=0; i<sz; i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::PUSH_BACK VECTOR::POP_BACK" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;
			int sum (0);

			myvector.push_back (100);
			myvector.push_back (200);
			myvector.push_back (300);
			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}
			std::cout << "The elements of myvector add up to " << sum << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RESERVE" << C_RESET << std::endl;
		{
			FT::vector<int>::size_type sz;
			FT::vector<int> bar;

			FT::vector<int> foo;
			sz = foo.capacity();
			std::cout << "making foo grow:\n";
			for (int i=0; i<100; ++i)
			{
				foo.push_back(i);
				if (sz!=foo.capacity())
				{
					sz = foo.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
			}
			sz = bar.capacity();
			bar.reserve(100);
			std::cout << "making bar grow:\n";
			for (int i=0; i<100; ++i)
			{
				bar.push_back(i);
				if (sz!=bar.capacity())
				{
					sz = bar.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
  			}
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RESIZE" << C_RESET << std::endl;
		{
			FT::vector<int> myvector;

			for (int i=1;i<10;i++)
				myvector.push_back(i);
			myvector.resize(5);
			myvector.resize(8,100);
			myvector.resize(12);
			std::cout << "myvector contains:";
			for (size_t i=0;i<myvector.size();i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::SWAP" << C_RESET << std::endl;
		{
			FT::vector<int> foo (3,100);
			FT::vector<int> bar (5,200);

			foo.swap(bar);
			std::cout << "foo contains:";
			for (unsigned i=0; i<foo.size(); i++)
				std::cout << ' ' << foo[i];
			std::cout << '\n';
			std::cout << "bar contains:";
			for (unsigned i=0; i<bar.size(); i++)
				std::cout << ' ' << bar[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::SWAP (NON MEMBER)" << C_RESET << std::endl;
		{
			FT::vector<int> foo (3,100);   // three ints with a value of 100
			FT::vector<int> bar (5,200);   // five ints with a value of 200

			foo.swap(bar);
			std::cout << "foo contains:";
			for (FT::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "bar contains:";
			for (FT::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RELATIONNAL_OP" << C_RESET << std::endl;
		{
			FT::vector<int> foo (3,100);   // three ints with a value of 100
  			FT::vector<int> bar (2,200);   // two ints with a value of 200

			if (foo==bar) std::cout << "foo and bar are equal\n";
			if (foo!=bar) std::cout << "foo and bar are not equal\n";
			if (foo< bar) std::cout << "foo is less than bar\n";
			if (foo> bar) std::cout << "foo is greater than bar\n";
			if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		}
	}
	std::cout << std::endl << C_YELLOW << "\t\tMAP TESTS" << C_RESET << std::endl;
	{
		std::cout << std::endl << C_YELLOW << "MAP CONSTRUCTORS" << C_RESET << std::endl;
		{
			FT::map<char,int> first;

			first['a']=10;
			first['b']=30;
			first['c']=50;
			first['d']=70;

			FT::map<char,int> second (first.begin(),first.end());

			FT::map<char,int> third (second);

			FT::map<char,int,classcomp> fourth;                 // class as Compare

			bool(*fn_pt)(char,char) = fncomp;
			FT::map<char,int,bool(*)(char,char)> fifth (fn_pt);
		}
		std::cout << std::endl << C_YELLOW << "MAP::begin && Map::end" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			mymap['b'] = 100;
			mymap['a'] = 200;
			mymap['c'] = 300;

			for (FT::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::rbegin && MAP::rend" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;

			// show content:
			FT::map<char,int>::reverse_iterator rit;
			for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::clear" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			mymap['x']=100;
			mymap['y']=200;
			mymap['z']=300;

			std::cout << "mymap contains:\n";
			for (FT::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			mymap.clear();
			mymap['a']=1101;
			mymap['b']=2202;

			std::cout << "mymap contains:\n";
			for (FT::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::count" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;
			char c;

			mymap ['a']=101;
			mymap ['c']=202;
			mymap ['f']=303;

			for (c='a'; c<'h'; c++)
			{
				std::cout << c;
				if (mymap.count(c)>0)
				std::cout << " is an element of mymap.\n";
				else 
				std::cout << " is not an element of mymap.\n";
			}
		}
		std::cout << std::endl << C_YELLOW << "MAP::empty" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;

			while (!mymap.empty())
			{
				std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
				mymap.erase(mymap.begin());
 			}
		}
		std::cout << std::endl << C_YELLOW << "MAP::equal_range" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;

			FT::pair<FT::map<char,int>::iterator,FT::map<char,int>::iterator> ret;
			ret = mymap.equal_range('b');

			std::cout << "lower bound points to: ";
			std::cout << ret.first->first << " => " << ret.first->second << '\n';

			std::cout << "upper bound points to: ";
			std::cout << ret.second->first << " => " << ret.second->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::erase" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;
			FT::map<char,int>::iterator it;

			// insert some values:
			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;
			mymap['d']=40;
			mymap['e']=50;
			mymap['f']=60;

			it=mymap.find('b');
			mymap.erase (it);                   // erasing by iterator

			mymap.erase ('c');                  // erasing by key

			it=mymap.find ('e');
			mymap.erase ( it, mymap.end() );    // erasing by range

			// show content:
			for (it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::find" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;
			FT::map<char,int>::iterator it;

			mymap['a']=50;
			mymap['b']=100;
			mymap['c']=150;
			mymap['d']=200;

			it = mymap.find('b');
			if (it != mymap.end())
				mymap.erase (it);

			// print content:
			std::cout << "elements in mymap:" << '\n';
			std::cout << "a => " << mymap.find('a')->second << '\n';
			std::cout << "c => " << mymap.find('c')->second << '\n';
			std::cout << "d => " << mymap.find('d')->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::get_allocator" << C_RESET << std::endl;
		{
			int psize;
			FT::map<char,int> mymap;
			FT::pair<const char,int>* p;

			// allocate an array of 5 elements using mymap's allocator:
			p=mymap.get_allocator().allocate(5);

			// assign some values to array
			psize = sizeof(FT::map<char,int>::value_type)*5;

			std::cout << "The allocated array has a size of " << psize << " bytes.\n";

			mymap.get_allocator().deallocate(p,5);		
		}
		std::cout << std::endl << C_YELLOW << "MAP::insert" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			// first insert function version (single parameter):
			mymap.insert ( FT::pair<char,int>('a',100) );
			mymap.insert ( FT::pair<char,int>('z',200) );

			FT::pair<FT::map<char,int>::iterator,bool> ret;
			ret = mymap.insert ( FT::pair<char,int>('z',500) );
			if (ret.second==false) {
				std::cout << "element 'z' already existed";
				std::cout << " with a value of " << ret.first->second << '\n';
			}

			// second insert function version (with hint position):
			FT::map<char,int>::iterator it = mymap.begin();
			mymap.insert (it, FT::pair<char,int>('b',300));  // max efficiency inserting
			mymap.insert (it, FT::pair<char,int>('c',400));  // no max efficiency inserting

			// third insert function version (range insertion):
			FT::map<char,int> anothermap;
			anothermap.insert(mymap.begin(),mymap.find('c'));

			// showing contents:
			std::cout << "mymap contains:\n";
			for (it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "anothermap contains:\n";
			for (it=anothermap.begin(); it!=anothermap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::key_comp" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			FT::map<char,int>::key_compare mycomp = mymap.key_comp();

			mymap['a']=100;
			mymap['b']=200;
			mymap['c']=300;

			std::cout << "mymap contains:\n";

			char highest = mymap.rbegin()->first;     // key value of last element

			FT::map<char,int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
			} while ( mycomp((*it++).first, highest) );

			std::cout << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::lower_bound && MAP::upper_bound" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;
			FT::map<char,int>::iterator itlow,itup;

			mymap['a']=20;
			mymap['b']=40;
			mymap['c']=60;
			mymap['d']=80;
			mymap['e']=100;

			itlow=mymap.lower_bound ('b');  // itlow points to b
			itup=mymap.upper_bound ('d');   // itup points to e (not d!)

			mymap.erase(itlow,itup);        // erases [itlow,itup)

			// print content:
			for (FT::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::max_size" << C_RESET << std::endl;
		{
			int i;
			FT::map<int,int> mymap;

			if (mymap.max_size()>1000)
			{
				for (i=0; i<1000; i++) mymap[i]=0;
				std::cout << "The map contains 1000 elements.\n";
			}
 			 else std::cout << "The map could not hold 1000 elements.\n";		
		}
		std::cout << std::endl << C_YELLOW << "MAP::operator=" << C_RESET << std::endl;
		{
			FT::map<char,int> first;
			FT::map<char,int> second;

			first['x']=8;
			first['y']=16;
			first['z']=32;

			second=first;                // second now contains 3 ints
			first=FT::map<char,int>();  // and first is now empty

			std::cout << "Size of first: " << first.size() << '\n';
			std::cout << "Size of second: " << second.size() << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::operator[]" << C_RESET << std::endl;
		{
			FT::map<char,std::string> mymap;

			mymap['a']="an element";
			mymap['b']="another element";
			mymap['c']=mymap['b'];

			std::cout << "mymap['a'] is " << mymap['a'] << '\n';
			std::cout << "mymap['b'] is " << mymap['b'] << '\n';
			std::cout << "mymap['c'] is " << mymap['c'] << '\n';
			std::cout << "mymap['d'] is " << mymap['d'] << '\n';

 			 std::cout << "mymap now contains " << mymap.size() << " elements.\n";
		}
		std::cout << std::endl << C_YELLOW << "MAP::size" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;
			mymap['a']=101;
			mymap['b']=202;
			mymap['c']=302;

			std::cout << "mymap.size() is " << mymap.size() << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::swap" << C_RESET << std::endl;
		{
			FT::map<char,int> foo,bar;

			foo['x']=100;
			foo['y']=200;

			bar['a']=11;
			bar['b']=22;
			bar['c']=33;

			foo.swap(bar);

			std::cout << "foo contains:\n";
			for (FT::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "bar contains:\n";
			for (FT::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';	
		}
		std::cout << std::endl << C_YELLOW << "MAP::value_comp" << C_RESET << std::endl;
		{
			FT::map<char,int> mymap;

			mymap['x']=1001;
			mymap['y']=2002;
			mymap['z']=3003;

			std::cout << "mymap contains:\n";

			FT::pair<char,int> highest = *mymap.rbegin();          // last element

			FT::map<char,int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
 			} while ( mymap.value_comp()(*it++, highest) );
		}
		std::cout << std::endl << C_YELLOW << "Map relationnals operators" << C_RESET << std::endl;
		{
			FT::map<char,int> foo,bar;
			foo['a']=100;
			foo['b']=200;
			bar['a']=10;
			bar['z']=1000;

			// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
			if (foo==bar) std::cout << "foo and bar are equal\n";
			if (foo!=bar) std::cout << "foo and bar are not equal\n";
			if (foo< bar) std::cout << "foo is less than bar\n";
			if (foo> bar) std::cout << "foo is greater than bar\n";
			if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";	
		}
	}
	std::cout << std::endl << C_YELLOW << "\t\tSET TESTS" << C_RESET << std::endl;
	{
		std::cout << std::endl << C_YELLOW << "SET CONSTRUCTORS" << C_RESET << std::endl;
		{
			FT::set<int> first;                           // empty set of ints

			int myints[]= {10,20,30,40,50};
			FT::set<int> second (myints,myints+5);        // range

			FT::set<int> third (second);                  // a copy of second

			FT::set<int> fourth (second.begin(), second.end());  // iterator ctor.

			FT::set<int,classcomp> fifth;                 // class as Compare

			bool(*fn_pt)(int,int) = fncomp;
			FT::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare
		}
		std::cout << std::endl << C_YELLOW << "SET::begin && set::end" << C_RESET << std::endl;
		{
			int myints[] = {75,23,65,42,13};
			FT::set<int> myset (myints,myints+5);

			std::cout << "myset contains:";
			for (FT::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;

			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::rbegin && SET::rend" << C_RESET << std::endl;
		{
			int myints[] = {21,64,17,78,49};
			FT::set<int> myset (myints,myints+5);

			FT::set<int>::reverse_iterator rit;

			std::cout << "myset contains:";
			for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
				std::cout << ' ' << *rit;

			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::clear" << C_RESET << std::endl;
		{
			FT::set<int> myset;

			myset.insert (100);
			myset.insert (200);
			myset.insert (300);

			std::cout << "myset contains:";
			for (FT::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';

			myset.clear();
			myset.insert (1101);
			myset.insert (2202);

			std::cout << "myset contains:";
			for (FT::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "SET::count" << C_RESET << std::endl;
		{
			FT::set<int> myset;

			// set some initial values:
			for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

			for (int i=0; i<10; ++i)
			{
				std::cout << i;
				if (myset.count(i)!=0)
				std::cout << " is an element of myset.\n";
				else
				std::cout << " is not an element of myset.\n";
			}		
		}
		std::cout << std::endl << C_YELLOW << "SET::empty" << C_RESET << std::endl;
		{
			FT::set<int> myset;

			myset.insert(20);
			myset.insert(30);
			myset.insert(10);

			std::cout << "myset contains:";
			while (!myset.empty())
			{
				std::cout << ' ' << *myset.begin();
				myset.erase(myset.begin());
			}
			std::cout << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "SET::equal_range" << C_RESET << std::endl;
		{
			FT::set<int> myset;

			for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

			FT::pair<FT::set<int>::const_iterator,FT::set<int>::const_iterator> ret;
			ret = myset.equal_range(30);

			std::cout << "the lower bound points to: " << *ret.first << '\n';
 			 std::cout << "the upper bound points to: " << *ret.second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::erase" << C_RESET << std::endl;
		{
			FT::set<int> myset;
			FT::set<int>::iterator it;

			// insert some values:
			for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

			it = myset.begin();
			++it;                                         // "it" points now to 20

			myset.erase (it);

			myset.erase (40);

			it = myset.find (60);
			myset.erase (it, myset.end());

			std::cout << "myset contains:";
			for (it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::find" << C_RESET << std::endl;
		{
			FT::set<int> myset;
			FT::set<int>::iterator it;

			// set some initial values:
			for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

			it=myset.find(20);
			myset.erase (it);
			myset.erase (myset.find(40));

			std::cout << "myset contains:";
			for (it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;
 			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::get_allocator" << C_RESET << std::endl;
		{
			FT::set<int> myset;
			int * p;
			unsigned int i;

			// allocate an array of 5 elements using myset's allocator:
			p=myset.get_allocator().allocate(5);

			// assign some values to array
			for (i=0; i<5; i++) p[i]=(i+1)*10;

			std::cout << "The allocated array contains:";
			for (i=0; i<5; i++) std::cout << ' ' << p[i];
			std::cout << '\n';

			myset.get_allocator().deallocate(p,5);		
		}
		std::cout << std::endl << C_YELLOW << "SET::insert" << C_RESET << std::endl;
		{
			FT::set<int> myset;
			FT::set<int>::iterator it;
			FT::pair<FT::set<int>::iterator,bool> ret;

			// set some initial values:
			for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

			ret = myset.insert(20);               // no new element inserted

			if (ret.second==false) it=ret.first;  // "it" now points to element 20

			myset.insert (it,25);                 // max efficiency inserting
			myset.insert (it,24);                 // max efficiency inserting
			myset.insert (it,26);                 // no max efficiency inserting

			int myints[]= {5,10,15};              // 10 already in set, not inserted
			myset.insert (myints,myints+3);

			std::cout << "myset contains:";
			for (it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::key_comp" << C_RESET << std::endl;
		{
			FT::set<int> myset;
			int highest;

			FT::set<int>::key_compare mycomp = myset.key_comp();

			for (int i=0; i<=5; i++) myset.insert(i);

			std::cout << "myset contains:";

			highest=*myset.rbegin();
			FT::set<int>::iterator it=myset.begin();
			do {
				std::cout << ' ' << *it;
			} while ( mycomp(*(++it),highest) );

			std::cout << '\n';	
		}
		std::cout << std::endl << C_YELLOW << "SET::lower_bound && SET::upper_bound" << C_RESET << std::endl;
		{
			FT::set<int> myset;
			FT::set<int>::iterator itlow,itup;

			for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

			itlow=myset.lower_bound (30);                //       ^
			itup=myset.upper_bound (60);                 //                   ^

			myset.erase(itlow,itup);                     // 10 20 70 80 90

			std::cout << "myset contains:";
			for (FT::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::max_size" << C_RESET << std::endl;
		{
			int i;
			FT::set<int> myset;

			if (myset.max_size()>1000)
			{
				for (i=0; i<1000; i++) myset.insert(i);
				std::cout << "The set contains 1000 elements.\n";
			}
			else std::cout << "The set could not hold 1000 elements.\n";
		}
		std::cout << std::endl << C_YELLOW << "SET::operator=" << C_RESET << std::endl;
		{
			int myints[]={ 12,82,37,64,15 };
			FT::set<int> first (myints,myints+5);   // set with 5 ints
			FT::set<int> second;                    // empty set

			second = first;                          // now second contains the 5 ints	
			first = FT::set<int>();                 // and first is empty

			std::cout << "Size of first: " << int (first.size()) << '\n';
			std::cout << "Size of second: " << int (second.size()) << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET::size" << C_RESET << std::endl;
		{
			FT::set<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i=0; i<10; ++i) myints.insert(i);
			std::cout << "1. size: " << myints.size() << '\n';

			myints.insert (100);
			std::cout << "2. size: " << myints.size() << '\n';

			myints.erase(5);
			std::cout << "3. size: " << myints.size() << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "SET::swap" << C_RESET << std::endl;
		{
			int myints[]={12,75,10,32,20,25};
			FT::set<int> first (myints,myints+3);     // 10,12,75
			FT::set<int> second (myints+3,myints+6);  // 20,25,32

			first.swap(second);

			std::cout << "first contains:";
			for (FT::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';

			std::cout << "second contains:";
			for (FT::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "SET::value_comp" << C_RESET << std::endl;
		{
			FT::set<int> myset;

			FT::set<int>::value_compare mycomp = myset.value_comp();

			for (int i=0; i<=5; i++) myset.insert(i);

			std::cout << "myset contains:";

			int highest=*myset.rbegin();
			FT::set<int>::iterator it=myset.begin();
			do {
				std::cout << ' ' << *it;
			} while ( mycomp(*(++it),highest) );

  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "SET relational operators" << C_RESET << std::endl;
		{
			FT::set<int> foo,bar;
			foo.insert(10);
			bar.insert(20);
			bar.insert(30);
			foo.insert(40);

			// foo ({10,40}) vs bar ({20,30}):
			if (foo==bar) std::cout << "foo and bar are equal\n";
			if (foo!=bar) std::cout << "foo and bar are not equal\n";
			if (foo< bar) std::cout << "foo is less than bar\n";
			if (foo> bar) std::cout << "foo is greater than bar\n";
			if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";	
		}
	}
	return (0);
}
