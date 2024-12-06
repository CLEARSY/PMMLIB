/******************************* CLEARSY **************************************
This file is part of BPARSERS
    Copyright (C) 2008 ClearSy (contact@clearsy.com)

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
#ifndef JOKERINSTANCIATION_H_
#define JOKERINSTANCIATION_H_

#include<stack>
#include<utility>
#include<vector>

namespace theory
{
class NodeWriter;

/** A class used to associate jokers with their instanciations, which
are abstract nodes of the tree. It is implemented using an
associative table of Instanciation. It manages instanciation history using a counter,
and is able to recover to any state of previous instanciation
@see Instanciation*/
class JokerInstanciation {

public:

	/** Creates a new JokerInstanciation object */
	JokerInstanciation();

    /** Default implementation for copy constructor */

	/** Destroys current object */
	~JokerInstanciation();

	/** Indicates if the given joker is instanciated
	@param joker_id : The joker to be considered
	@return True if the given joker is instanciated, otherwise no */
	bool isInstanciated(char joker_id) const;

	/** Returns the instanciation of a given joker
	@param joker_id: The joker we want the instanciation of
	@return The instanciation of the given joker, and NULL if it hasn't
	been initialised */
	const BNode *getInstanciation(char joker_id) const;

	/** Returns the joker a given node is instancied to
	 * @param value : The node we want the instanciation of
	@param joker_id: The joker the given node is instancied to
	@return true if the given node is instanciated */
	bool hasInstanciation(const BNode *value, char* joker_id) const;

    /** Allows to come back to a previous instanciation state
     * the parameter old_id has to be less than or equal to the current id.
     *
     * @param old_id : The numeric value of the step we wish to go back to */
    void restoreToCounter(int old_id);

    /** Comes back to the initial state */
    void reset();

    /**
	 * Sets the instanciation associated to a joker character
	 *
	 * @param joker_id : The joker to be considered
	 * @param value : The instanciation of the joker
	 **/
	void setInstanciation(char joker_id, const BNode *value);

	/**
     * Tries matching the given pattern with the given source tree.
     * If the match succeeds, the state of the object is changed
     * so that jokers are instanciated to reference to the corresponding
     * part of source.
     * Otherwise, the state of the object is unchanged.
	 * The current JokerInstanciation can be already partly
     * instantiated.
	 *
     * @param pattern the pattern containing the jokers, in a tree representation
     * @param term the source to match
	 * @return the tree depth if the match succeeded, -1 otherwise
	 */
    int match(const BNode *pattern, const BNode *term);

    /**
     * Tries matching the given pattern with the given source text.
     * If the match succeeds, the state of the object is changed
     * so that jokers are instanciated to reference to the corresponding
     * part of source.
     * Otherwise, the state of the object is unchanged.
     * The current JokerInstanciation can be already partly
     * instantiated.
     *
     * @param pattern the pattern containing the jokers, in textual form
     * @param source the source to match
     * @return the tree depth if the match succeeded, -1 otherwise
     */
    int match(const std::string& pattern, const BNode *source);

    /**
	 * Jokerize a given source.
	 * if level=0 every leaf of source is replaced by a joker
	 * if level>0 the leaf at the given level in the tree are replaced by a joker
	 * if level=-1 the jokerization is optimal, that is
	 * aa+bb <= ff(aa+bb) will be jokerized in a <= b(a)
	 * @param source the source to jokerize
	 * @param level the level of jokerization
	 * @return the resulting pattern
	 */
	BNode* jokerize(const BNode *source, int level);

    /** @todo remove memory leaks in this method */
    BNode* jokerize_from(const BNode *source, int level, char *j, bool keepLiteralInt);
    BNode* jokerize_from2(const BNode *source, int level, char *j, bool keepLiteralInt);


	BNode* applyInstanciation(const BNode *source);

	/**
	 * Tries matching pattern in a subexpression of source
	 *
	 * @param pattern the pattern
	 * @param source the source
	 * @return the tree depth if the match succeeded, -1 otherwise
	 */
	int matchSubExpression(const BNode *pattern, const BNode *source);

	void writeContent(NodeWriter &w);

	const BNode* operator [] (char c) const { return getInstanciation(c); }

    friend std::ostream& operator<< (std::ostream& o, const theory::JokerInstanciation& j);

    /**
     * @brief push stores the current state of the object on a history stack
     */
    void push();
    /**
     * @brief pop reverts the object to the state on top of the history stack
     */
    void pop();

private:
    std::vector< const BNode* > instantiation;
    std::vector< int > level;
    std::stack< std::pair< std::vector< char >*, int > > history;

    /**
     * Table containing the different instanciations
     */
    int currentId;

    /**
     * Number of instanciations that are stored within the table
     */
    static const int INSTANTIATION_COUNT = 26 * 2;

    /**
     * Returns the index corresponding to the given joker within the table
     * @param c the joker char
     * @return the index of the corresponding instanciation within the table
     */
    static int getIndex(char c);
    /**
     * Returns the character corresponding to the given index within the
     * instanciation table
     * @param index the index within the table
     * @return the corresponding joker char
     */
    static char getCharFromIndex(int index);

    bool hasInstanciation(const BNode *value, char& joker_id) const;

    /**
     * @brief has_joker tests the presence of joker in an expression
     * @param source the root node for the representation of an expression
     * @return true iff the representation contains a joker, at any depth
     */
    bool has_joker(const BNode *source);

    bool find(const BNode *source, std::vector< const BNode* >& nodes);
    /**
     * @brief should_jokerize returns true when the given node is an identifier
     * @note we do not want jokerized expressions to contain model identifiers.
     * @param source root node of a term
     */
    bool should_jokerize(const BNode *source);

    int internalMatch(const BNode *pattern, const BNode *term, std::vector<char> &jokers);
    BNode* jokerize_algo1(const BNode *source, int level, char* j, bool keepLiteralInt = false);
	BNode* jokerize_algo2(const BNode *source, const BNode *current, char* j);
    /**
     * @brief jokerize_algo3
     * @param source a predicate representation
     * @param level requested depth
     * @param j largest joker used so far (alphabetical order)
     * @param keepLiteralInt instructs how to handle integer literals
     * @param bound contains terms corresponding to quantified variables
     *
     * @return representation of the jokerization of source up to the
     * given level, taking into account the current state of the
     * object (mapping existing jokers to terms). The level constraint
     * is not taken into account when the current sub-term contains a
     * quantified variable. In that case, its top level symbol is
     * jokerized and its sub-terms are jokerized.
     * If a bound variable identifier is the same as that of a
     * global function or another bound variable, the same joker is
     * kept.
     *
     * @note If the source term contains nested quantified variables,
     * the vector bound is used to store those variables. The
     * variables are popped away from the vector before the method
     * returns, so the contents of bound should be the same before and
     * after the call.
     */
    BNode* jokerize_algo3(const BNode *source, int level, char* j, bool keepLiteralInt, std::vector< const BNode* >& bound);

    BNode* jokerize_joker(char *j);
	bool jokerize_allChildsWithSameOccurence(const BNode *source, const BNode *current, int occ);

};

std::ostream& operator << (std::ostream& o, const theory::JokerInstanciation& j);
};

#endif /*JOKERINSTANCIATION_H_*/

