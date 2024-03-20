#include <stddef.h>
#include "cnf.h"

// IZLO PROJEKT NO. 1 --- SAT SOLVER CONDITIONS 

//
// LOGIN: xvitulp00
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    // ZDE PRIDAT KOD

    // looping through all streets
    for (int step = 0; step < num_of_streets; ++step) {
                // create new clause
                Clause *ok = create_new_clause(formula);

                for (int i = 0; i < num_of_streets; i++) {
                        unsigned start = streets[i].crossroad_from;
                        unsigned end = streets[i].crossroad_to;



                        add_literal_to_clause(ok, true, step, start, end);
                }
        }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty

//add_literal_to_clause(ok, true, step, z, k);
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD

    for (int step = 0; step < num_of_streets; ++step) {
                for (int z = 0; z < num_of_crossroads; ++z) {
                        for (int k = 0; k < num_of_crossroads; ++k) {
                            for (int a = 0; a < num_of_crossroads; ++a) {
                                for (int b = 0; b < num_of_crossroads; ++b) {
                                    // must check this bcs wouldnt make sense
                                    if((a == z) && (b == k)) {
                                    } else {
                                        Clause *gg = create_new_clause(formula);

                                        add_literal_to_clause(gg, false, step, z, k);
                                        add_literal_to_clause(gg, false, step, a, b);
                                    }
                                }
                            }
                        }
                }
        }
}



// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);


    // ZDE PRIDAT KOD
    
    for (int step = 0; step < num_of_streets - 1; ++step) {
        for (int z = 0; z < num_of_crossroads; ++z) {
            for (int k = 0; k < num_of_crossroads; ++k) {

                Clause *tx = create_new_clause(formula);
                // we create one and then add to this 
                add_literal_to_clause(tx, false, step, z, k);

                for (int p = 0; p < num_of_crossroads; ++p) {
                    
                        add_literal_to_clause(tx, true, step+1, k, p);
                    }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    
    for (unsigned i = 0; i < num_of_streets; ++i) {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j) {
            if (i != j) {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z) {
                    for (unsigned k = 0; k < num_of_crossroads; ++k) {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}
