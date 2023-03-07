//
// Created by Suvir Wadhwa on 18/11/21.
//

#include <iostream>
#include <vector>
#include <string>

#ifndef HW07_PROTECTOR_H
#define HW07_PROTECTOR_H

namespace WarriorCraft {
    class Protector {
    public:
        Protector(const std::string &prot_name,
                  int prot_strength);

        virtual void defend() const = 0;

        bool isHired() const;

        void setLord(Lord *myLord);

        void runaway();

        double getStrength() const;

        void setStrength(double stren);

        bool isDead() const;

        void setDead();

        std::string getName() const;

    protected:
        std::string getLordName() const;

    private:
        Lord *lord = nullptr;
        std::string name;
        double strength;
        bool dead = false;
    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string &wiz_name, int wiz_strength);

        void defend() const override;
    };

    class Warrior : public Protector {
    public:
        Warrior(const std::string &warr_name, int warr_strength);

    private:
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string &arch_name, int arch_strength);

        void defend() const override;

    private:
        //
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string &sword_name, int sword_strength);

        void defend() const override;

    private:
    };

}

#endif //HW07_PROTECTOR_H
