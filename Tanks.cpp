#include <iostream>
class Tank {
private:
	int initial_health_;
	int current_health_;
	double attack_;
	double defense_;
public:
	Tank() {

	}
	/*Tank(const std::string name) :name(name) {

	}*/
	void set_initial_health(int new_initial_health) {
		this->initial_health_ = new_initial_health;
	}
	void set_current_health(int new_current_health) {
		this->current_health_ = new_current_health;
	}
	void set_attack(double new_attack) {
		this->attack_ = new_attack;
	}
	void set_defense(double new_defense) {
		this->defense_ = new_defense;
	}
	int initial_health()const {
		return initial_health_;
	}
	int current_health() const {
		return current_health_;
	}
	double attack()const {
		return attack_;
	}
	double defense()const {
		return defense_;
	}
	void Input(Tank& tank, std::string const& name);
	bool Validate(const Tank& tank);
	bool IsAlive(const Tank& tank);
	bool Hit(const Tank& attacker, Tank& defender);
	void print_health_information(Tank& tank, std::string const& name)const;
	void ReportDeath(const std::string& name)const;
	~Tank() {}
};

int main()
{
	Tank tanks[2];
	Tank tank;
	const std::string name[2] = { "Tank1" , "Tank2" };
	//Tank tank();
	std::cout << "Velcome to tank battle.\n";
	tank.Input(tanks[0], name[0]);
	tank.Input(tanks[1], name[1]);
	int attacking_tank_no;
	while (true) {
		std::cout << "Enter the number of the attacking tank <1 or 2>.\n";
		std::cin >> attacking_tank_no;
		--attacking_tank_no; //make_index 0 based
		const Tank& attacker = tanks[attacking_tank_no];
		const int defending_tank_no = 1 - attacking_tank_no; //1 becomes 0; 0 becomes 1
		Tank& defender = tanks[defending_tank_no];
		if (tank.Hit(attacker, defender))
		{
			tank.ReportDeath(name[defending_tank_no]);
			break;
			break;
		}
		else
		{
			tank.print_health_information(tanks[0], name[0]);
			tank.print_health_information(tanks[1], name[1]);
		}
	}
}

void Tank::Input(Tank& tank, std::string const& name) {
	int initial_health;
	int current_health;
	double attack;
	double defense;
	do {
		std::cout << "Please enter the " << name << " tank's characteristics: health attack defense\n";
		std::cin >> initial_health;
		std::cin >> attack;
		std::cin >> defense;
		tank.set_initial_health(initial_health);
		tank.set_attack(attack);
		tank.set_defense(defense);
		tank.set_current_health(initial_health);
	} while (!Validate(tank));
}

bool Tank::Validate(const Tank& tank) {
	return tank.initial_health() > 0 && tank.attack() > 0 && tank.defense() >= 0. && tank.defense() <= 1.;
}

bool Tank::IsAlive(const Tank& tank)
{
	return tank.current_health() > 0;
}
bool Tank::Hit(const Tank& attacker, Tank& defender)
{
	const double attacker_strength = static_cast<double>(attacker.current_health()) / attacker.initial_health();
	const double damage = attacker.attack() * (1 - defender.defense()) * attacker_strength;
	defender.set_current_health(static_cast<int>(defender.current_health() - damage));
	return !IsAlive(defender);
}

void Tank::print_health_information(Tank& tank, std::string const& name) const {
	std::cout << name << " health: " << tank.current_health() << "\n";
}

void Tank::ReportDeath(const std::string& name)const
{
	std::cout << name << " is dead\n";
}