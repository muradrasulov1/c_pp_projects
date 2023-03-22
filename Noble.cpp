//
//  Noble.cpp
//  hw07.cpp
//
//  Created by Fuad on 15.04.22.
//

#include "Noble.hpp"
#include "Protector.hpp"


#include <iostream>
#include <vector>
using namespace std;

namespace WarriorCraft{

Noble::Noble(const string& aname, double strengtH) : noble_name(aname), strength(strengtH),
                                able_to_operate(true){}

double Noble::get_strength() const{ return strength;}

string Noble::get_name() const{ return noble_name;}

void Noble::set_strength(double new_val){ //check if dead 
    if (new_val <= 0){
        strength = 0;
        able_to_operate = false;
    }else{
        strength = new_val;
    }
}


bool Noble::get_life_status(){return able_to_operate;}

void Noble::is_dead(){able_to_operate = false;}

void Noble::battle(Noble& opponent){
    cout << noble_name << " battles " << opponent.noble_name << endl;
    
    if(opponent.able_to_operate && able_to_operate){
        
        if (strength > opponent.strength){
            change_strength(opponent.get_strength());
            opponent.change_strength(strength);
            cout << noble_name << " defeats " << opponent.get_name() << endl;
        }
        else if (strength < opponent.strength){
            change_strength(opponent.get_strength());
            opponent.change_strength(strength);
            cout << opponent.get_name() << " defeats " << noble_name << endl;
        }
        else if (strength == opponent.strength){
            change_strength(opponent.get_strength());
            opponent.change_strength(strength);
            cout << "Mutual Annihilation: " << noble_name << " and " << opponent.noble_name << " die at each other's hands." << endl;
        }
    }
    else{
        if (able_to_operate){
            cout << "He's dead, " << noble_name << endl;
        }
        
        else if (opponent.able_to_operate){
            cout << "He's dead, " << opponent.noble_name << endl;
        }
        else{
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
    
}

Lord::Lord(const string& aname, double strengtH) : Noble(aname, 0) {}

bool Lord::hires(Protector& protector){
    if(get_life_status() == true) {
        if(protector.isHired() == false){
            army.push_back(&protector); // dereference the warrior and add to vector
            set_strength(get_strength() + protector.get_strength()); // add the new warrior
                                                                        // strength to total army strength
            protector.hireProtector(this); // change warrior job status to hired
            return true;
        }
        else{
            cerr << "Attempt to hire " << protector.get_name() << " by " << get_name() << " failed! " << endl;
            return false;
        }
    }
    else{
        cerr << get_name() << " is already dead! No Warriors can be hired" << endl;
        return false;
    }
}

bool Lord::fires(Protector& protector){
    size_t protecc_loc = army.size();
    if (get_life_status() == true) {
        if (protector.isHired() == true){
            set_strength(get_strength() - protector.get_strength());
            
            
            for (size_t idx = 0; idx < army.size(); idx++){ // iterate to find the position of the fired warrior
                if (army[idx] == &protector){
                    cout << "You don't work for me anymore " << protector.get_name()
                    << "! -- " << get_name() << "." << endl;
                    protecc_loc = idx; // set the loc of the fired warrior
                    break;
                }
            }
            for (size_t i = protecc_loc; i < army.size() - 1; i++){
                army[i] = army[i + 1]; // shift all the vector elements to left
                                        // to shift the fired warrior to right
                                        // the loop starts from the fired warrior loc to the right
            }
            
            army.pop_back(); // delete the fired warrior pointer from the vector
            protector.freeProtector(); // change warrior job status to fired
            return true;

        }
    }
    else{
        cerr << get_name() << " is already dead! No Warriors can be fired" << endl;
    }
    return false;
    
}

void Lord::change_strength(double new_val){
    double ratio = 0; // used for all scenarios
    if (new_val < get_strength()){ // noble stayed alive
        ratio = 1 - (new_val/get_strength());
    } else {
        set_strength(ratio); // noble died
    }
    for (Protector* protecc: army){
        protecc->defend(ratio); // adjust protectors accordingly
    }
}


size_t Lord::searchWarrior(const string& protector){
    // loop thru warriors p vector, if found the warr loc, return it, else vec size
    for (size_t i = 0; i < army.size(); ++i){
        if (army[i]->get_name() == protector){
            return i;
            
        }
    }
    return army.size();
}

bool Lord::runaway(Protector* escapist){ // delegated continuation of runaway method
    // finds escapist loc, removes from army and army strength, displays message
    
    // true if can run away, else false
    
    size_t protec_loc = searchWarrior(escapist->get_name());
    
    
    if (protec_loc != army.size()){
        
        
        set_strength(get_strength() - escapist->get_strength());

        for (size_t i = protec_loc; i < army.size() - 1; i++){
            army[i] = army[i + 1]; // shift all the vector elements to left
                                    // to shift the fired warrior to right
                                    // the loop starts from the fired warrior loc to the right
        }
        
        cout << escapist->get_name() << " flees in terror, abandoning his lord, "
        << get_name() << endl; // new output
        
        army.pop_back(); // delete the fired warrior pointer from the vector
        
        escapist->freeProtector(); // change warrior job status to fired
        return true;
    }
    
    return false;
}


PersonWithStrengthToFight::PersonWithStrengthToFight(const string& aname, double strengtH) : Noble(aname, strengtH) {}


void PersonWithStrengthToFight::change_strength(double new_val){
    cout << "UGH!" << endl;
    set_strength(get_strength() - new_val); //set_str covers cases when novel becomes dead and not
    
}

}
