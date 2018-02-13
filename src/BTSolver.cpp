#include"BTSolver.hpp"

using namespace std;

// =====================================================================
// Constructors
// =====================================================================

BTSolver::BTSolver ( SudokuBoard input, Trail* _trail,  string val_sh, string var_sh, string cc )
: sudokuGrid( input.get_p(), input.get_q(), input.get_board() ), network( input )
{
	valHeuristics = val_sh;
	varHeuristics = var_sh;
	cChecks =  cc;

	trail = _trail;
}

// =====================================================================
// Consistency Checks
// =====================================================================

// Basic consistency check, no propagation done
bool BTSolver::assignmentsCheck ( void )
{
    // Why not
    /*
     * if(network.isConsistent())
     *      return false;
     * else
     *      return true;
     * */
	for ( Constraint c : network.getConstraints() )
		if ( ! c.isConsistent() )
			return false;

	return true;
}

/**
 * Part 1 TODO: Implement the Forward Checking Heuristic
 *
 * This function will do both Constraint Propagation and check
 * the consistency of the network
 *
 * (1) If a variable is assigned then eliminate that value from
 *     the square's neighbors.
 *
 * Note: remember to trail.push variables before you assign them
 * Return: true is assignment is consistent, false otherwise
 */
bool BTSolver::forwardChecking ( void )
{
    ConstraintNetwork::ConstraintRefSet constraintrefset = network.getModifiedConstraints();
    for(auto constraint: constraintrefset)
        for(Variable *var : constraint->vars)
        {
            if(var->isAssigned())
            {
                ConstraintNetwork::VariableSet neighbors = network.getNeighborsOfVariable(var);
                for(auto n : neighbors) {
                    trail->push(n);
                    n->removeValueFromDomain(var->getAssignment());
                    if(!assignmentsCheck())
                        return false;
                }
            }
        }
	return true;
}

/**
 * Part 2 TODO: Implement both of Norvig's Heuristics
 *
 * This function will do both Constraint Propagation and check
 * the consistency of the network
 *
 * (1) If a variable is assigned then eliminate that value from
 *     the square's neighbors.
 *
 * (2) If a constraint has only one possible place for a value
 *     then put the value there.
 *
 * Note: remember to trail.push variables before you assign them
 * Return: true is assignment is consistent, false otherwise
 */
bool BTSolver::norvigCheck ( void )
{
	return false;
}

/**
 * Optional TODO: Implement your own advanced Constraint Propagation
 *
 * Completing the three tourn heuristic will automatically enter
 * your program into a tournament.
 */
bool BTSolver::getTournCC ( void )
{
	return false;
}

// =====================================================================
// Variable Selectors
// =====================================================================

// Basic variable selector, returns first unassigned variable
Variable* BTSolver::getfirstUnassignedVariable ( void )
{
	for ( Variable* v : network.getVariables() )
		if ( !(v->isAssigned()) )
			return v;

	// Everything is assigned
	return nullptr;
}

/**
 * Part 1 TODO: Implement the Minimum Remaining Value Heuristic
 *
 * Return: The unassigned variable with the smallest domain
 */
Variable* BTSolver::getMRV ( void )
{
    vector <Variable * > vars;
    for (Variable * v : network.getVariables()) {
        if (!v->isAssigned()) {
            vars.push_back(v);
        }
    }
    if (!vars.empty()) {
        int minSize = vars[0]->size();
        Variable * minV = vars[0];
        for (int i = 0; i < vars.size(); i++) {
            if (minSize > vars[i]->size()) {
                minSize = vars[i]->size();
                minV = vars[i];
            }
        }
        return minV;
    }
    return nullptr;
/*
    Variable * next = getfirstUnassignedVariable();
    int current_domain_size = next->size();
    ConstraintNetwork::VariableSet variables = network.getVariables();
    for(Variable * v : variables){
        cout<<v->toString()<<endl;
        if(!v->isAssigned()){
            if(v->size() < current_domain_size){
                next = v;
                current_domain_size = v->size();
            }

        }
    }

    Variable * next;
    int current_domain_size = 0;
    if(trail->size()==0){
        next = getfirstUnassignedVariable();
//        cout<<next->toString()<<endl;

    } else {
        next = std::get<0>(trail->getTrailStack().top());
        cout<<next->toString()<<endl;
    }
    current_domain_size = next->size();
    ConstraintNetwork::VariableSet neignbors = network.getNeighborsOfVariable(next);
    for(auto n : neignbors){
        if(n->size() < current_domain_size){
            next = n;
            current_domain_size = n->size();
        }

    }

*/
/*
	int current_domain_size =0;
	ConstraintNetwork::ConstraintRefSet constraintrefset = network.getModifiedConstraints();
//    cout<<network.toString()<<endl;
	for(auto constraint: constraintrefset) {
        for (Variable *var : constraint->vars) {
 //           cout<<var->toString()<<endl;
            if (!var->isAssigned()) {
                cout<<var->toString()<<endl;
                ConstraintNetwork::VariableSet neighbors = network.getNeighborsOfVariable(var);
                for (auto n : neighbors) {
                    if (n->size() < current_domain_size) {
                        current_domain_size = n->size();
                        next = n;
                    }
                }
            }
        }
    }
    cout<<"entering mrv\n";
*/
}

/**
 * Part 2 TODO: Implement the Minimum Remaining Value Heuristic
 *                with Degree Heuristic as a Tie Breaker
 *
 * Return: The unassigned variable with, first, the smallest domain
 *         and, second, the most unassigned neighbors
 */
Variable* BTSolver::getDegree ( void )
{
	return nullptr;
}

/**
 * Part 2 TODO: Implement the Minimum Remaining Value Heuristic
 *                with Degree Heuristic as a Tie Breaker
 *
 * Return: The unassigned variable with the smallest domain and involved
 *             in the most constraints
 */
Variable* BTSolver::MRVwithTieBreaker ( void )
{
	return nullptr;
}

/**
 * Optional TODO: Implement your own advanced Variable Heuristic
 *
 * Completing the three tourn heuristic will automatically enter
 * your program into a tournament.
 */
Variable* BTSolver::getTournVar ( void )
{
	return nullptr;
}

// =====================================================================
// Variable Selectors
// =====================================================================

// Default Value Ordering
vector<int> BTSolver::getValuesInOrder ( Variable* v )
{
	vector<int> values = v->getDomain().getValues();
	sort( values.begin(), values.end() );
	return values;
}

/**
 * Part 1 TODO: Implement the Least Constraining Value Heuristic
 *
 * The Least constraining value is the one that will knock the most
 * values out of it's neighbors domain.
 *
 * Return: A list of v's domain sorted by the LCV heuristic
 *         The LCV is first and the MCV is last
 */
vector<int> BTSolver::getValuesLCVOrder ( Variable* v )
{
	return vector<int>();
}

/**
 * Part 1 TODO: Implement the Least Constraining Value Heuristic
 *
 * The Least constraining value is the one that will knock the most
 * values out of it's neighbors domain.
 *
 * Return: A list of v's domain sorted by the LCV heuristic
 *         The LCV is first and the MCV is last
 */
vector<int> BTSolver::getTournVal ( Variable* v )
{
	return vector<int>();
}

// =====================================================================
// Engine Functions
// =====================================================================

void BTSolver::solve ( void )
{
	if ( hasSolution )
		return;

	// Variable Selection
	Variable* v = selectNextVariable();

	if ( v == nullptr )
	{
		for ( Variable* var : network.getVariables() )
		{
			// If all variables haven't been assigned
			if ( ! ( var->isAssigned() ) )
			{
				cout << "Error" << endl;
				return;
			}
		}

		// Success
		hasSolution = true;
		return;
	}

	// Attempt to assign a value
	for ( int i : getNextValues( v ) )
	{
		// Store place in trail and push variable's state on trail
		trail->placeTrailMarker();
		trail->push( v );

		// Assign the value
		v->assignValue( i );

		// Propagate constraints, check consistency, recurse
		if ( checkConsistency() )
			solve();

		// If this assignment succeeded, return
		if ( hasSolution )
			return;

		// Otherwise backtrack
		trail->undo();
	}
}

bool BTSolver::checkConsistency ( void )
{
	if ( cChecks == "forwardChecking" )
		return forwardChecking();

	if ( cChecks == "norvigCheck" )
		return norvigCheck();

	if ( cChecks == "tournCC" )
		return getTournCC();

	return assignmentsCheck();
}

Variable* BTSolver::selectNextVariable ( void )
{
	if ( varHeuristics == "MinimumRemainingValue" )
		return getMRV();

	if ( varHeuristics == "Degree" )
		return getDegree();

	if ( varHeuristics == "MRVwithTieBreaker" )
		return MRVwithTieBreaker();

	if ( varHeuristics == "tournVar" )
		return getTournVar();

	return getfirstUnassignedVariable();
}

vector<int> BTSolver::getNextValues ( Variable* v )
{
	if ( valHeuristics == "LeastConstrainingValue" )
		return getValuesLCVOrder( v );

	if ( valHeuristics == "tournVal" )
		return getTournVal( v );

	return getValuesInOrder( v );
}

bool BTSolver::haveSolution ( void )
{
	return hasSolution;
}

SudokuBoard BTSolver::getSolution ( void )
{
	return network.toSudokuBoard ( sudokuGrid.get_p(), sudokuGrid.get_q() );
}

ConstraintNetwork BTSolver::getNetwork ( void )
{
	return network;
}
