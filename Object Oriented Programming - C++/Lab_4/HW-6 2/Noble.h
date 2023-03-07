//
// Created by Suvir Wadhwa on 02/11/21.
//

#ifndef HW_6_NOBLE_H
#define HW_6_NOBLE_H
#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Warrior;

    class Noble { // Class noble, creates a Noble and enables it to
        // add warriors, fire them, and make one noble battle another.
        friend std::ostream &operator<<(std::ostream &os, const Noble &nob);

    public:
        Noble(const std::string &noble_name);

        bool hire(Warrior &warr);

        bool fire(Warrior &warr);

        const std::string &getName() const;

        void remove_warrior(Warrior *warr);

        void battle(Noble &enemy);

        void kill_warriors(const std::vector<Warrior*>& warrior);

    private:
        bool dead = false;
        double strength;
        std::string name;
        std::vector<Warrior *> warriors;
    };

    void change_warriors_strength(std::vector<Warrior*>& warr, double& strength1, double& strength2);
}

#endif //HW_6_NOBLE_H
