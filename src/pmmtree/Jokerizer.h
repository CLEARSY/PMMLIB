/******************************* CLEARSY **************************************
This file is part of BPARSERS
    Copyright (C) 2018 ClearSy (contact@clearsy.com)

    BPARSERS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; GNU General Public License version 3
    of the License

    BPARSERS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BPARSERS; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/
#ifndef JOKERIZER_H_
#define JOKERIZER_H_

#include<stack>
#include<utility>
#include<vector>

namespace theory
{
    class BNode;

    /** 
	@brief Performs jokerization on successive formulas

	A jokerizer is created by giving as arguments the depth in
	terms where jokers are to be introduced and a flag stating
	if integers are to be considered as interpreted (and should
	not be jokerized).

	A jokerizer may then be applied successively to BNode objects
	representing formulas. Jokerization is successful while there
	exists enough jokers to process the given formulas.

	There are 52 possible different jokers.

	Jokerizer introduce different jokers for the same symbol when
	it appears with different roles in the formulas. For instance
	quantified variables bound by two different quantifiers are
	associated to different jokers.

    */
class Jokerizer {

public:

    /** 
    @brief Constructor

    @param depth Depth where sub-terms are replaced by jokers.
    @param keepInt indicates if integer literals and identifiers
    have to be kept in the resulting formulas.
    */
    Jokerizer(int depth, bool keepInt);

    /**
    @brief Destructor
    */
    ~Jokerizer();

    /**
    @brief Processes a formula
    @param src the formula to be processed
    @return the jokerized formula
    */
    BNode* handle(BNode* src);
    /**
    @brief Tests if the jokerizer has free jokers available
    @note Initially there are 52 free jokers.
    */
    bool available() const;
    /**
    @brief The next joker available
    @return The character for the next free joker.
    @note Jokers are created from 'a' to 'z' then 'A' to 'Z'.
    */ 
    char nextJoker() const;

private:
    int depth;           ///< jokerization parameter
    bool keepInt;        ///< jokerization parameter
    char next_joker;     ///< next free available joker - if any
    std::vector<std::pair<BNode*, BNode* >> binding; ///< pairs jokers-terms

    /* Disable copy constructor */
    Jokerizer(const Jokerizer&) {}

    /**
       @brief sets next free joker as used, updates next free joker
    */
    void consumeJoker();

    /**
       @brief unbinds a joker and a term
       @param value the term that is unbound
       @note This does not free the joker, which becomes unavailable
       to jokerize formulas. This is useful to avoid using the same joker
       for different quantified variables or global operators.
    */
    void cancelBinding(const BNode* value);
    
    /**
       @brief associates a new joker to term
       @param value the term to be associated with a joker
       @return the joker term associated with value, or NULL if the
       pool of jokers is exhausted.
    */
    BNode* createBinding(BNode* value);

    /**
       @brief queries joker associated with term
       @param value the term
       @return the joker currently bound to term, or NULL if none
    */
    BNode* lookupBinding(BNode* value);

    /**
       @brief recursive implementation of jokerization
       @param src a term
       @param term the depth where jokers are introduced
       @param the quantified variables in scope
       @note terms containing quantified variables cannot be jokerized
    */
    BNode* handle_rec(BNode* src,
		      int depth,
		      std::vector<const BNode* >& bound);
};

};

#endif /*JOKERBINDING_H_*/

