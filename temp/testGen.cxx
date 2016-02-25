/*
 * testGen.cxx
 * 
 * Copyright 2015 Unknown <demikandr@demikandr-laptop>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <random>

int main(int argc, char **argv)
{
	typedef std::mt19937 MyRNG; 
	MyRNG rng;
	std::uniform_int_distribution<int> uint_dist1(0, 27);
	
	int n,m;
	std::cin >> n >> m;
	std::uniform_int_distribution<int> uint_dist(0,n-1);
	for (int i=0; i < n; ++i) {
		std::cout <<((char) ('a'+ uint_dist1(rng)));
	}
	std::cout << std::endl << m << std::endl;
	for (int i=0;i<m; ++i ){
		int l1,r1,l2,r2;
		l1= uint_dist(rng);
		r1= uint_dist(rng);
		l2= uint_dist(rng);
		r2= uint_dist(rng);
		if (l1>r1) {
			std::swap(l1,r1);
		}
		if (l2>r2) {
			std::swap(l2, r2);
		}
		std::cout << l1 <<' ' <<  r1 << ' ' << l2 << ' ' <<  r2 << std::endl;
	}
	return 0;
}

